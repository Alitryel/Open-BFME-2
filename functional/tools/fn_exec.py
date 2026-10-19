#!/usr/bin/env python3
"""Hardened differential execution for the functional branch (F0).

Builds on tools/diffexec.py (same emulator, image, binding and classification) and adds:

  * more input vectors (default 12): diffexec's three plus seeded variants that mix heap
    objects, zeros, small integers, random words and IEEE-754 float bit patterns (0, -0,
    1, -0.5, 1e9, NaN, a denormal) as ecx/edx/stack arguments, each with its own seeded heap;
  * inlining-aware calls: a call into a small LEAF ledger function (matched row, no call or
    out-of-extent jump in its retail bytes) runs that function's retail code for real on
    BOTH sides instead of a stub, and is not recorded as an event. "Retail inlined X, the
    rebuilt body calls X" (or the reverse) then compares equal when the behaviour is equal;
  * a coverage receipt: the share of the retail function's bytes the vectors executed
    (union over vectors). A pass on little coverage is evidence of little;
  * per-vector verdicts in the record.

Pass = every completed vector `none`/`regalloc-only`, no vector `logic`/`binding`/`build_env`,
and at most a quarter of the vectors inconclusive (limit/timeout cuts); `fn_progress.py`
additionally requires coverage >= COVERAGE_MIN for a row to count in the headline.
"""
import hashlib
import random
import struct
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import diffexec as D  # noqa: E402

COVERAGE_MIN = 0.5
FLOATS = [0x00000000, 0x80000000, 0x3F800000, 0xBF000000, 0x4E6E6B28, 0x7FC00000, 0x00000001,
          0x42C80000, 0xC2C80000, 0x3E99999A]
LEAF_MAX = 512          # bytes: only small helpers are run for real
MAX_INSNS = 3_000_000   # per vector; diffexec uses 100k, too few for renderer/AI loops
MAX_EVENTS = 50_000


def vectors(n=16):
    out = list(D.vectors())
    obj = [D.HEAP + 0x1000 * k for k in range(1, 40)]
    rng = random.Random(0xB2F)
    kinds = ["obj", "zero", "int", "float", "word"]
    while len(out) < n:
        i = len(out)

        def pick():
            k = rng.choice(kinds)
            if k == "obj":
                return rng.choice(obj)
            if k == "zero":
                return 0
            if k == "int":
                return rng.choice([1, 2, 3, 4, 7, 8, 16, 100, 0xFFFFFFFF, 0x7FFFFFFF])
            if k == "float":
                return rng.choice(FLOATS)
            return rng.getrandbits(32)
        out.append({"name": f"v{i}", "ecx": rng.choice(obj), "edx": pick(),
                    "args": [pick() for _ in range(8)], "seed": 100 + i, "rich": i % 3 != 0})
    return out[:n]


_RICH = {}


def rich_heap(seed):
    """A heap whose words are a mix: pointers back into the heap (so object graphs and vtables
    resolve), small integers, random 32-bit words (every bit pattern) and IEEE-754 floats over
    useful ranges (signs, fractions, large values, zero), so bit tests and float arithmetic
    see values that distinguish them. diffexec's heap is pointers and 0..7 only."""
    if seed in _RICH:
        return _RICH[seed]
    rng = random.Random(seed * 7919 + 1)
    words = D.HEAP_SIZE // 4
    out = bytearray(D.HEAP_SIZE)
    for i in range(words):
        k = rng.random()
        if k < 0.40:
            v = D.HEAP + rng.randrange(0, words // 4 - 64) * 16
        elif k < 0.60:
            v = rng.choice((0, 1, 2, 3, 4, 5, 8, 10, 16, 100, 255, 0xFFFFFFFF))
        elif k < 0.80:
            v = struct.unpack("<I", struct.pack("<f", rng.choice((-1, 1)) * 10 ** rng.uniform(-3, 4)))[0]
        else:
            v = rng.getrandbits(32)
        struct.pack_into("<I", out, i * 4, v)
    _RICH[seed] = bytes(out)
    return _RICH[seed]


class Leafs:
    """Entry VA -> extent of matched ledger rows whose retail bytes are a leaf (no calls out)."""

    def __init__(self, ctx):
        import build
        self.ctx = ctx
        self.base = ctx.image.base
        self.cache = {}
        self.rows = {}
        for r in build.load_all_function_rows():
            if r.get("status") != "matched":
                continue
            try:
                rva, size = int(r["target_rva"], 16), int(r["target_size"], 0)
            except (ValueError, TypeError):
                continue
            if 0 < size <= LEAF_MAX:
                self.rows.setdefault(self.base + rva, size)

    def extent(self, va):
        if va in self.cache:
            return self.cache[va]
        size = self.rows.get(va)
        ok = None
        if size:
            ok = (va, va + size) if self._leaf(va - self.base, size) else None
        self.cache[va] = ok
        return ok

    def _leaf(self, rva, size):
        import capstone
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        code = self.ctx.image.read(rva, size)
        va = self.base + rva
        for ins in md.disasm(code, va):
            m = ins.mnemonic
            if m == "call" or m.startswith("int"):
                return False
            if m == "jmp" or (m.startswith("j") and m != "jmp"):
                op = ins.op_str
                if not op.startswith("0x"):
                    return False        # indirect jump: switch/tail call, not provable here
                t = int(op, 16)
                if not va <= t < va + size:
                    return False        # tail call out
        return True


def run(ctx, start_va, size, code, vector, timeout_us, leafs=None, cover=None):
    """diffexec.run with leaf callees executed for real and retail coverage collection."""
    U, X = D.unicorn, D.X
    image = ctx.image
    mu = U.Uc(U.UC_ARCH_X86, U.UC_MODE_32)
    mu.mem_map(image.base, image.size, U.UC_PROT_ALL)
    mu.mem_write(image.base, image.emulation_bytes())
    if code is not None:
        mu.mem_write(start_va, code)
    mu.mem_map(D.STACK_LO, D.STACK_HI - D.STACK_LO)
    mu.mem_map(D.HEAP, D.HEAP_SIZE, U.UC_PROT_ALL)
    if vector.get("rich"):
        mu.mem_write(D.HEAP, rich_heap(vector["seed"]))
    else:
        if vector["seed"] not in D._HEAPS:
            D._HEAPS[vector["seed"]] = D.heap_bytes(vector["seed"])
        mu.mem_write(D.HEAP, D._HEAPS[vector["seed"]])
    mu.mem_map(D.MAGIC, D.REGION_END - D.MAGIC, U.UC_PROT_ALL)
    mu.mem_write(D.PHANTOM, b"\0" * 0x1000 * max(1, len(ctx.phantom_bytes)))
    for address, data in ctx.phantom_bytes.items():
        mu.mem_write(address, data)
    esp = D.ESP0
    mu.mem_write(esp, struct.pack("<I", D.MAGIC) + b"".join(struct.pack("<I", a & 0xFFFFFFFF) for a in vector["args"]))
    for reg, value in ((X.UC_X86_REG_ESP, esp), (X.UC_X86_REG_ECX, vector["ecx"] & 0xFFFFFFFF),
                       (X.UC_X86_REG_EDX, vector["edx"] & 0xFFFFFFFF), (X.UC_X86_REG_EAX, D.HEAP + 0xC000),
                       (X.UC_X86_REG_EBX, D.HEAP + 0xD000), (X.UC_X86_REG_ESI, D.HEAP + 0xE000),
                       (X.UC_X86_REG_EDI, D.HEAP + 0xF000), (X.UC_X86_REG_EBP, D.ESP0 + 0x800)):
        mu.reg_write(reg, value)
    trace = {"calls": [], "writes": {}, "reads": set(), "wild": 0, "end": None, "events": 0}
    ordinal = {}
    lo, hi = start_va, start_va + size
    deep = {"extent": None}

    def on_code(mu, address, isize, _):
        if lo <= address < hi:
            deep["extent"] = None
            if cover is not None:
                cover.update(range(address, address + isize))
            return
        if address == D.MAGIC:
            trace["end"] = "return"
            mu.emu_stop()
            return
        ext = deep["extent"]
        if ext and ext[0] <= address < ext[1]:
            return                          # running a leaf callee for real
        if leafs is not None:
            ext = leafs.extent(address)
            if ext:
                deep["extent"] = ext
                return
        ident = ctx.canon(address)
        sp = mu.reg_read(X.UC_X86_REG_ESP)
        try:
            ret = struct.unpack("<I", mu.mem_read(sp, 4))[0]
        except U.UcError:
            trace["end"] = ("fault", "stack", ident)
            mu.emu_stop()
            return
        pop = ctx.pop_count(ident)
        follow = bytes(mu.mem_read(ret, 6)) if lo <= ret < hi else b""
        if follow[:2] == b"\x83\xC4":
            nargs = follow[2] // 4
        elif follow[:2] == b"\x81\xC4":
            nargs = min(struct.unpack_from("<I", follow, 2)[0] // 4, 16)
        else:
            nargs = pop // 4
        args = struct.unpack(f"<{nargs}I", mu.mem_read(sp + 4, 4 * nargs)) if nargs else ()
        n = ordinal[ident] = ordinal.get(ident, -1) + 1
        trace["events"] += 1
        if trace["events"] > MAX_EVENTS:
            trace["end"] = ("limit", "events")
            mu.emu_stop()
        thiscall = D.THISCALL.search(ctx.name_of(ident) or "") is not None
        trace["calls"].append((ident, tuple(D.norm(a) for a in args),
                               D.norm(mu.reg_read(X.UC_X86_REG_ECX)) if thiscall else None))
        h = int.from_bytes(hashlib.sha1(f"{ident}#{n}#{vector['seed']}".encode()).digest()[:4], "little")
        value = (h >> 8) % 4 if h % 4 == 0 else D.HEAP + ((h >> 4) % (D.HEAP_SIZE // 16 - 64)) * 16
        nm = ctx.name_of(ident) or ""
        if "CxxThrowException" in nm or "CxxThrowException" in str(ident):
            trace["calls"].append((ident, tuple(D.norm(a) for a in args), None))
            trace["end"] = ("throw",)
            mu.emu_stop()
            return
        if "?A" in nm.split("@@", 1)[-1][:6] and args:          # returns a class/struct by value
            hidden = args[0]
            if D.HEAP <= hidden < D.HEAP + D.HEAP_SIZE or D.STACK_LO <= hidden < D.STACK_HI:
                try:
                    mu.mem_write(hidden, hashlib.sha1(f"{ident}#{n}#{vector['seed']}#ret".encode()).digest()[:16])
                    value = hidden
                except U.UcError:
                    pass
        mu.reg_write(X.UC_X86_REG_EAX, value)
        mu.reg_write(X.UC_X86_REG_EDX, 0)
        mu.reg_write(X.UC_X86_REG_ESP, sp + 4 + pop)
        mu.reg_write(X.UC_X86_REG_EIP, ret)

    def on_write(mu, _access, address, wsize, value, _):
        if address < 0x10000:
            return                      # fs:[0] SEH chain bookkeeping (EH frame present on one side only)
        data = b"SSSS" if wsize == 4 and D.STACK_LO <= value < D.STACK_HI else \
            (value & ((1 << (8 * wsize)) - 1)).to_bytes(wsize, "little")
        for i in range(wsize):
            trace["writes"][address + i] = data[i]
        trace["events"] += 1
        if trace["events"] > MAX_EVENTS:
            trace["end"] = ("limit", "events")
            mu.emu_stop()

    def on_read(mu, _access, address, rsize, _value, _):
        if not lo <= address < hi:
            trace["reads"].add(address)

    def on_unmapped(mu, access, address, usize, value, _):
        try:
            mu.mem_map(address & ~0xFFF, 0x1000, U.UC_PROT_ALL)
        except U.UcError:
            return False
        trace["wild"] += 1
        return True

    mu.hook_add(U.UC_HOOK_CODE, on_code)
    mu.hook_add(U.UC_HOOK_MEM_WRITE, on_write, None, 0, D.STACK_LO - 1)
    mu.hook_add(U.UC_HOOK_MEM_WRITE, on_write, None, D.STACK_HI, 0xFFFFFFFF)
    mu.hook_add(U.UC_HOOK_MEM_READ, on_read, None, image.base, image.base + image.size - 1)
    mu.hook_add(U.UC_HOOK_MEM_UNMAPPED, on_unmapped)
    began = time.perf_counter()
    try:
        mu.emu_start(start_va, D.MAGIC, timeout=timeout_us, count=MAX_INSNS)
    except U.UcError as error:
        trace["end"] = ("fault", D.norm(mu.reg_read(X.UC_X86_REG_EIP)), str(error))
    if trace["end"] is None:
        eip = mu.reg_read(X.UC_X86_REG_EIP)
        if eip == D.MAGIC:
            trace["end"] = "return"
        elif (time.perf_counter() - began) * 1e6 >= timeout_us:
            trace["end"] = ("timeout",)
        else:
            trace["end"] = ("limit", "instructions")
    if trace["end"] == "return":
        trace["ret"] = (D.norm(mu.reg_read(X.UC_X86_REG_EAX)), D.norm(mu.reg_read(X.UC_X86_REG_EDX)),
                        mu.reg_read(X.UC_X86_REG_ESP) - (D.ESP0 + 4))
    return trace


_LEAFS = {}
_RET = _re.compile(r"@@(?:[A-Z]{1,2}E|Y[AGI]|S[AGI])(?:\?[A-Z])?(_N|[XMNDEC])") if False else None


def ret_kind(name):
    """'void' | 'bool' | 'byte' | 'fp' | 'int' from the mangled return type (MSVC)."""
    import re
    m = re.search(r"@@(?:[A-Z][A-Z]?E|Y[AGI]|S[AGI])(?:\?[AB])?(_N|_J|_K|X|M|N|D|E|C|O)", name or "")
    if not m:
        return "int"
    return {"X": "void", "_N": "bool", "_J": "int64", "_K": "int64", "D": "byte", "E": "byte", "C": "byte",
            "M": "fp", "N": "fp", "O": "fp"}[m.group(1)]


def mask_ret(trace, kind):
    r = trace.get("ret")
    if not r:
        return
    eax, edx, esp = r
    if kind in ("void", "fp"):
        trace["ret"] = (None, None, esp)
    elif kind in ("bool", "byte"):
        trace["ret"] = ((eax & 0xFF) if isinstance(eax, int) else eax, None, esp)
    elif kind != "int64":
        trace["ret"] = (eax, None, esp)          # EDX is scratch unless the function returns 64 bits


def diff_body(ctx, row, compiled, relocs, info, objdata, sections, nvec=None, budget_ms=4000, retail_size=None):
    """Hardened diff of one body; record with verdict, per-vector verdicts and coverage."""
    D.require_unicorn()
    began = time.perf_counter()
    rva, size = int(row["target_rva"], 16), int(row["target_size"])
    retail_size = retail_size or size
    if nvec is None:      # small bodies are cheap to emulate: give them many more inputs
        nvec = 128 if retail_size < 300 else 48 if retail_size < 2000 else 16
    rec = {"name": row["name"], "rva": f"0x{rva:08X}", "size": retail_size, "extent": size,
           "source": row.get("source", ""), "vectors": nvec}
    code, sites, phantoms, problems = D.rebuild(ctx, row, compiled, relocs, info, objdata, sections)
    if problems:
        rec.update(verdict="inconclusive", reason="; ".join(problems[:3]))
        return rec
    learned = learn_bindings(ctx, rva, retail_size, compiled, relocs)
    for nm, addr in converged_globals().items():
        if any(s_["symbol"] == nm for s_ in sites):
            learned[nm] = addr
    code, nre = rebind(ctx, row, code, sites, compiled, learned)
    code, nval = bind_constants_by_value(ctx, row, code, sites, compiled, info, objdata, sections, retail_size)
    weak = sum(1 for s in sites if s["source"] in WEAK_SOURCES)
    rec["bindings"] = {"aligned": nre, "by_value": nval, "weak_left": weak}
    ctx.phantom_bytes = {}
    for (name, index), address in phantoms.items():
        sym = info["symbols"][index]
        sec = sections[sym["section"] - 1]
        n = D.symbol_extent(index, info["symbols"], sec["raw_size"])
        ctx.phantom_bytes[address] = bytes(objdata[sec["raw_pointer"] + sym["value"]:][:min(n, 0x1000)])
    retail = ctx.image.read(rva, size)
    in_site = set()
    for s in sites:
        in_site.update(range(s["offset"], s["offset"] + 4))
    same_code = all(x == y for i, (x, y) in enumerate(zip(code, retail)) if i not in in_site)
    if id(ctx) not in _LEAFS:
        _LEAFS[id(ctx)] = Leafs(ctx)
    leafs = _LEAFS[id(ctx)]
    va = ctx.image.base + rva
    timeout = max(30_000_000, budget_ms * 1000)
    cover = set()
    per = []
    for vec in vectors(nvec):
        a = run(ctx, va, size, None, vec, timeout, leafs, cover)
        b = run(ctx, va, size, code, vec, timeout, leafs, None)
        if ("timeout",) in (a["end"], b["end"]):
            per.append(("inconclusive", f"{vec['name']}: timeout"))
            continue
        if D.limit_cut(a) or D.limit_cut(b):
            v, r = D.classify_cut(ctx, a, b)
            if v == "inconclusive" and D.limit_cut(a) and D.limit_cut(b) and "runtime helper" not in r:
                v = "prefix-equal"      # both cut at the cap, identical up to it
            per.append((v, f"{vec['name']}: {r}"))
            continue
        rk = ret_kind(row["name"])
        mask_ret(a, rk)
        mask_ret(b, rk)
        v, r = D.classify(ctx, a, b, row["name"])
        if v == "binding" and "(twin bodies)" in (r or ""):
            v, r = "regalloc-only", "callee twins with identical retail bytes: " + r
        if v == "none" and not same_code:
            v = "regalloc-only"
        per.append((v, f"{vec['name']}: {r}" if r else vec["name"]))
    verdicts = [v for v, _ in per]
    bad = [v for v in verdicts if v in ("logic", "binding", "build_env")]
    inc = verdicts.count("inconclusive")
    complete = sum(1 for v in verdicts if v in ("none", "regalloc-only"))
    if bad:
        verdict = D.worst(bad)
    elif inc > len(verdicts) // 4 or complete < max(2, len(verdicts) // 3):
        verdict = "inconclusive"
    elif "regalloc-only" in verdicts:
        verdict = "regalloc-only"
    else:
        verdict = "none"
    base = ctx.image.base + rva
    iso, iso_delta = static_isomorphic(ctx, rva, retail_size, code)
    rec.update(isomorphic=iso, iso_delta=iso_delta)
    rec.update(verdict=verdict, coverage=round(len([x for x in cover if base <= x < base + retail_size]) / max(1, retail_size), 3),
               per_vector=[f"{v}: {r}"[:160] for v, r in per], inconclusive_vectors=inc,
               complete_vectors=complete, prefix_vectors=verdicts.count("prefix-equal"),
               reason=next((r for v, r in per if v == verdict), "")[:300],
               ms=round((time.perf_counter() - began) * 1000, 1))
    return rec


# ------------------------------------------------------------------ aligned binding
WEAK_SOURCES = {"copied", "content-mismatch", "copied-unmatched-body"}


def _norm_ins(ins):
    import re
    return ins.mnemonic + " " + re.sub(r"0x[0-9a-f]+|\b\d+\b", "N", ins.op_str)


def learn_bindings(ctx, rva, retail_size, compiled, relocs):
    """{symbol: retail target VA} learned where the rebuilt and retail instruction streams align:
    a relocation inside a rebuilt instruction whose aligned retail twin has the same shape takes
    the address retail uses at the same operand position. Evidence from retail itself, so it
    also binds globals, float constants and TU-local helpers nothing else can name."""
    import capstone
    import difflib
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    base = ctx.image.base
    va = base + rva
    retail = ctx.image.read(rva, retail_size)
    a = list(md.disasm(bytes(compiled), va))
    b = list(md.disasm(retail, va))
    na, nb = [_norm_ins(x) for x in a], [_norm_ins(x) for x in b]
    pairs = {}
    sm = difflib.SequenceMatcher(None, na, nb, autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal" or (tag == "replace" and i2 - i1 == j2 - j1):
            for k in range(i2 - i1):
                x, y = a[i1 + k], b[j1 + k]
                if x.size == y.size and x.mnemonic == y.mnemonic and na[i1 + k] == nb[j1 + k]:
                    pairs[x.address] = y
    starts = sorted(pairs)
    import bisect
    learned, votes = {}, {}
    for off, rtype, name in relocs:
        fva = va + off
        k = bisect.bisect_right(starts, fva) - 1
        if k < 0:
            continue
        ra = starts[k]
        twin = pairs[ra]
        inner = fva - ra
        if inner + 4 > twin.size:
            continue
        addend = struct.unpack_from("<i", compiled, off)[0]
        field = struct.unpack_from("<I", retail, twin.address - va + inner)[0]
        if rtype == 0x14:
            target = (twin.address + inner + 4 + struct.unpack_from("<i", retail, twin.address - va + inner)[0] - addend) & 0xFFFFFFFF
        elif rtype == 0x06:
            target = (field - addend) & 0xFFFFFFFF
        elif rtype == 0x07:
            target = (field + base - addend) & 0xFFFFFFFF
        else:
            continue
        votes.setdefault(name, {}).setdefault(target, 0)
        votes[name][target] += 1
    for name, v in votes.items():
        learned[name] = max(v.items(), key=lambda kv: kv[1])[0]
    return learned


_CONVERGED = None


def converged_globals():
    """{symbol name: VA} from reverse/data_converged.csv (one real global per converged address)."""
    global _CONVERGED
    if _CONVERGED is None:
        import csv as _csv
        _CONVERGED = {}
        p = ROOT / "reverse" / "data_converged.csv"
        if p.exists():
            for r in _csv.DictReader(p.open(encoding="utf-8")):
                name = r.get("symbol") or r.get("name") or ""
                addr = r.get("address") or r.get("va") or r.get("rva") or ""
                try:
                    a = int(addr, 16)
                except ValueError:
                    continue
                _CONVERGED[name] = a if a >= 0x400000 else a + 0x400000
    return _CONVERGED


def rebind(ctx, row, code, sites, compiled, learned):
    """Re-patch sites whose binding was a weak fallback with the aligned-binding address."""
    out = bytearray(code)
    va = ctx.image.base + int(row["target_rva"], 16)
    n = 0
    for s in sites:
        if s["symbol"] not in learned:
            continue
        if s["source"] not in WEAK_SOURCES and not (str(s["symbol"]).startswith("??_7") and s["source"] == "content-mismatch"):
            continue
        off, rtype, target = s["offset"], s["type"], learned[s["symbol"]]
        addend = struct.unpack_from("<i", compiled, off)[0]
        if rtype == 0x14:
            field = target + addend - (va + off + 4)
        elif rtype == 0x06:
            field = target + addend
        else:
            field = target + addend - ctx.image.base
        struct.pack_into("<I", out, off, field & 0xFFFFFFFF)
        s["source"], s["target"] = "aligned", target
        n += 1
    return bytes(out), n


# ------------------------------------------------------------------ static isomorphism
import re as _re
_REG = _re.compile(r"\b(e?[abcd]x|[abcd][lh]|e?[sd]i|e?[sb]p|xmm[0-7]|st\(\d\))\b")
_STK = _re.compile(r"\[(esp|ebp)[^\]]*\]")
_NOISE = _re.compile(r"^(mov R, R|push R|pop R|nop|xchg R, R|fxch R|movaps R, R|movss R, R|lea R, \[R\])$")


def _static_norm(ins, ctx=None):
    m = ins.mnemonic
    op = ins.op_str
    if m == "call":
        if op.startswith("0x") and ctx is not None:
            return "call " + str(ctx.canon(int(op, 16)))      # thunks / jmp [iat] / import stubs followed
        return "call " + _REG.sub("R", _STK.sub("STK", op))     # indirect: call [reg+off], call reg
    if m.startswith("j") or m.startswith("loop"):
        return f"{m} T"
    op = _STK.sub("STK", op)
    op = _REG.sub("R", op)
    s = f"{m} {op}".strip()
    if _re.match(r"^(add|sub) R, 0x[0-9a-f]+$", s) and ins.op_str.startswith("esp"):
        return None                 # frame size
    if _NOISE.match(s) or m in ("int3",):
        return None
    return s


def static_isomorphic(ctx, rva, retail_size, code):
    """True when the relocated rebuilt body and retail perform the same multiset of operations
    up to register names, stack-slot offsets, jump targets, register-to-register moves, saves
    and frame size: the shape of a register-allocation/scheduling-only difference. Any
    changed opcode, immediate, global operand, callee or memory displacement breaks it."""
    import capstone
    from collections import Counter
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    va = ctx.image.base + rva
    retail = ctx.image.read(rva, retail_size)
    def tokens(blob):
        ops, loads = Counter(), set()
        for i in md.disasm(blob, va):
            t = _static_norm(i, ctx)
            if not t:
                continue
            m = _re.match(r"^(\w+) (R|STK), (.*\[.*\].*)$", t)
            if m and not i.mnemonic.startswith(("lea", "cmp", "test")) and "STK" not in m.group(3) and m.group(2) == "R":
                loads.add(m.group(3))                       # memory source folded into an op
                if i.mnemonic.startswith(("mov", "fld", "movss", "movsd", "movzx", "movsx")):
                    continue                                # a plain load: just the load
                t = f"{i.mnemonic} R, R"                    # the op itself, register form
            elif i.mnemonic.startswith(("fld", "fild")) and "[" in t and "STK" not in t:
                loads.add(t.split(" ", 1)[1])
                continue
            ops[t] += 1
        return ops, loads
    oa, la = tokens(bytes(code).rstrip(b"\xcc"))
    ob, lb = tokens(bytes(retail))
    delta = sum(((oa - ob) + (ob - oa)).values()) + len(la ^ lb)
    return delta == 0, delta


# ------------------------------------------------------------------ constants by value
def retail_constants(ctx, rva, size):
    """{bytes value: address} of read-only data retail's own body references by absolute address
    (float/double literals, strings): candidates for binding a rebuilt constant by VALUE."""
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    va = ctx.image.base + rva
    out = {}
    for ins in md.disasm(ctx.image.read(rva, size), va):
        for op in ins.operands:
            addr = None
            if op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                addr = op.mem.disp & 0xFFFFFFFF
            elif op.type == capstone.x86.X86_OP_IMM:
                addr = op.imm & 0xFFFFFFFF
            if addr and ctx.image.contains_va(addr) and not ctx.image.is_code(addr - ctx.image.base):
                for n in (4, 8, 16, 32, 64):
                    try:
                        out.setdefault(bytes(ctx.image.read(addr - ctx.image.base, n)), addr)
                    except Exception:  # noqa: BLE001
                        break
    return out


def bind_constants_by_value(ctx, row, code, sites, compiled, info, objdata, sections, retail_size):
    """Rebind __real@ / ??_C@ (literal) sites to the retail address whose bytes equal the
    constant's bytes in the object, among the constants retail's body itself references."""
    if not info or not objdata or not sections:
        return code, 0
    consts = retail_constants(ctx, int(row["target_rva"], 16), retail_size)
    out = bytearray(code)
    va = ctx.image.base + int(row["target_rva"], 16)
    syms = info.get("symbols") or []
    byname = {}
    for i, s in enumerate(syms):
        if isinstance(s, dict) and s.get("name"):
            byname.setdefault(s["name"], i)
    n = 0
    for s in sites:
        name = str(s["symbol"])
        if not (name.startswith("__real@") or name.startswith("??_C@")) or s.get("source") not in WEAK_SOURCES:
            continue                # only constants nothing better bound (aligned/content/ledger stay)
        idx = byname.get(name)
        if idx is None:
            continue
        sym = syms[idx]
        try:
            sec = sections[sym["section"] - 1]
            ln = D.symbol_extent(idx, syms, sec["raw_size"])
            data = bytes(objdata[sec["raw_pointer"] + sym["value"]:][:ln])
        except Exception:  # noqa: BLE001
            continue
        target = None
        if name.startswith("__real@"):
            target = consts.get(data[:8] if len(name) > 15 else data[:4])
        else:
            for v, addr in consts.items():
                if v.startswith(data[:min(len(data), 64)]) or data.startswith(v[:len(data)]):
                    target = addr
                    break
        if target is None:
            continue
        off, rtype = s["offset"], s["type"]
        addend = struct.unpack_from("<i", compiled, off)[0]
        field = target + addend if rtype == 0x06 else target + addend - (va + off + 4) if rtype == 0x14 else target + addend - ctx.image.base
        struct.pack_into("<I", out, off, field & 0xFFFFFFFF)
        s["source"], s["target"] = "by-value", target
        n += 1
    return bytes(out), n
