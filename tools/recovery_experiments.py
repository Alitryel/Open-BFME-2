#!/usr/bin/env python3
"""Private, input-checked compiler experiments; never a landing verifier.

Called by recovery_lab.py. The cache holds objects and diagnostics only. Normal
whole-file gates, identity/provenance review and hooks remain mandatory.
"""
import argparse
import bisect
import contextlib
import difflib
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import uuid

from portable_lock import lock, unlock

VERSION = 1
_FLAG_INPUTS = {}


def digest(path):
    value = hashlib.sha256()
    with Path(path).open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            value.update(chunk)
    return value.hexdigest()


def json_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()


def current_command(build, source, output):
    """A long-lived experiment process must not inherit stale region decisions."""
    flags = getattr(build, "flag_defaults", None)
    if flags is not None:
        with flags._cache_lock:
            signature = tuple((str(path), digest(path) if path.is_file() else None)
                              for path in (flags.REGIONS, flags.OVERRIDES, flags.FUNCTIONS))
            if _FLAG_INPUTS.get(str(build.ROOT)) != signature:
                flags._cache.clear()
                _FLAG_INPUTS[str(build.ROOT)] = signature
            return build.compiler_command(source, output)
    return build.compiler_command(source, output)


def atomic_json(path, value):
    temporary = path.with_name(path.name + "." + uuid.uuid4().hex + ".tmp")
    try:
        temporary.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        os.replace(temporary, path)
    finally:
        temporary.unlink(missing_ok=True)


def inputs(build, source, command, env, symbol, rva, size):
    """Hash bytes, not timestamps. Environment values are never written to disk."""
    root = build.ROOT
    files = {source, build.EXE, build.FUNCTIONS, build.SYMBOLS}
    regions = root / "reverse/retail_inventory/flag_regions.csv"
    if regions.is_file():
        files.add(regions)
    if getattr(build, "MANIFEST", None) is not None:
        files.add(build.MANIFEST)
    files.update((root / "tools").glob("*.py"))
    # All local ledgers/policies are conservative inputs to symbol resolution.
    for pattern in ("*.csv", "*.tsv", "*.txt"):
        files.update((root / "reverse").glob(pattern))
    for argument in command:
        path = Path(argument)
        if path.is_file() and path.suffix.lower() in (".exe", ".dll"):
            files.add(path)
            # VC's frontend/backend are DLLs next to cl.exe. Hash them as well
            # as the driver; command spelling alone cannot identify codegen.
            files.update(path.parent.glob("*.dll"))
    for relative in json.loads(env.get("BFME_COMPILER_INPUTS", "{}")):
        files.add(root / relative)
    return {
        "version": VERSION, "symbol": symbol, "rva": rva, "size": size,
        "source": str(source),
        "command": ["-Fo<private-output>" if part.startswith(("-Fo", "/Fo")) else part
                    for part in command],
        "environment": json_digest(dict(env)),
        "files": {str(path): digest(path) for path in sorted(files, key=str)},
    }


def stable_preprocessor_inputs(snapshot, source, compiler_output, receipts):
    """The real compile opened the same unchanged files as the initial probe."""
    if snapshot is None:
        return False
    try:
        if receipts.opened_paths(source, compiler_output.encode("latin-1", errors="replace")) != set(snapshot["files"]):
            return False
        for name, expected in snapshot["files"].items():
            stat = Path(name).stat()
            generation = [stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns]
            if digest(name) != expected or generation != snapshot["generations"][name]:
                return False
        return True
    except (OSError, ValueError, KeyError):
        return False


def instruction_diff(compiled, target, rva):
    try:
        import capstone
    except ImportError:
        return []
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decode = lambda data: [f"{i.address - rva:04x}: {i.mnemonic} {i.op_str}".rstrip()
                           for i in md.disasm(data, rva)]
    return list(difflib.unified_diff(decode(target), decode(compiled),
                                    fromfile="retail", tofile="candidate", lineterm=""))[:120]


def evaluate(build, source, output, symbol, rva, size):
    # The CLI normally has a fresh process; callers may also run several trials
    # in one Python process while master or a ledger moves between them.
    for name in ("exe_image", "ledger_entry_points", "_ledger_bodies"):
        clear = getattr(getattr(build, name, None), "cache_clear", None)
        if clear:
            clear()
    row = {"name": symbol, "source": source.relative_to(build.ROOT).as_posix(),
           "target_rva": f"0x{rva:08X}", "target_size": str(size),
           "status": "matched", "notes": ""}
    symbol_map = build.load_symbol_map()
    patch = build.compile_function(row, symbol_map, output, allow_weak=False)
    body, relocs, info = build.read_object_symbol_bytes(output, symbol, size,
                                                      code_only=True, detail=True)
    stat = output.stat()
    starts = build._function_starts(str(output), stat.st_mtime_ns, stat.st_size).get(info["section"], [])
    index = bisect.bisect_right(starts, info["value"])
    end = starts[index] if index < len(starts) else info["section_size"]
    emitted_size = len(body[:end - info["value"]].rstrip(b"\xcc"))
    extent = build.body_extent_problems(row, patch, symbol_map, output, [])
    compiled, target = patch["bytes"], patch["target"]
    first = next((i for i, (a, b) in enumerate(zip(compiled, target)) if a != b), None)
    if first is None and len(compiled) != len(target):
        first = min(len(compiled), len(target))
    # compile_function copies DIR32 operands from retail. Until the ordinary
    # string/float/import/data checks run, such a comparison is not exactness.
    unchecked = [list(reloc) for reloc in relocs if reloc[0] < size and reloc[1] == build.DIR32]
    unsupported = [list(reloc) for reloc in relocs
                   if reloc[0] < size and reloc[1] not in (build.DIR32, build.REL32)]
    exact = (compiled == target and emitted_size == size and not extent
             and not patch["unresolved"] and not patch["masked"] and not unchecked and not unsupported)
    return {
        "diagnostic_only": True, "landing_verified": False, "candidate_exact": exact,
        "bytes_match": compiled == target, "emitted_size": emitted_size, "claimed_size": size,
        "first_mismatch": first, "compiled_hex": compiled.hex(), "retail_hex": target.hex(),
        "unresolved": list(patch["unresolved"]), "masked": bool(patch["masked"]),
        "unchecked_dir32": unchecked, "unsupported_relocations": unsupported,
        "relocations": [list(reloc) for reloc in relocs if reloc[0] < emitted_size],
        "extent_problems": [list(problem) for problem in extent],
        "instruction_diff": instruction_diff(compiled, target, rva),
    }


def reusable(build, source, entry, key):
    try:
        meta = json.loads((entry / "cache.json").read_text(encoding="utf-8"))
        output = (entry / meta["object"]).resolve()
        if (meta.get("version") != VERSION or meta.get("key") != key
                or not output.is_relative_to(entry.resolve())
                or digest(output) != meta["object_sha256"]
                or not build.compile_is_current(source, output, strict=True)):
            return None
        return output
    except (OSError, ValueError, KeyError, TypeError, SystemExit):
        return None


def run_experiment(source, symbol, rva, size, *, cache=None, force=False, timeout=120, build_module=None):
    if build_module is None:
        import build as build_module
    build = build_module
    root = build.ROOT.resolve()
    source = Path(source).resolve()
    cache = Path(cache or root / "build" / "recovery-experiments").resolve()
    if (not source.is_relative_to(root) or source.suffix.lower() not in (".cpp", ".cc", ".cxx", ".c")
            or not source.is_file()):
        raise ValueError("source must be a complete C/C++ file inside this checkout")
    if (not cache.is_relative_to(root / "build") or cache == root / "build"
            or cache.is_relative_to(root / "build" / "match")):
        raise ValueError("cache must be a private directory under this checkout's build/, outside build/match")
    if not symbol or not 0 <= rva <= 0xFFFFFFFF or size <= 0 or rva + size > 0x100000000 or timeout <= 0:
        raise ValueError("require a symbol, a valid 32-bit RVA, positive size and timeout")
    if hasattr(build, "verify_baseline"):
        with contextlib.redirect_stdout(sys.stderr):
            build.verify_baseline()
    cache.mkdir(parents=True, exist_ok=True)
    command, env = current_command(build, source, cache / "placeholder.obj")
    before = inputs(build, source, command, env, symbol, rva, size)
    key = json_digest(before)
    entry = cache / key
    entry.mkdir(exist_ok=True)
    with (entry / "entry.lock").open("a+b") as handle:
        if handle.tell() == 0:
            handle.write(b"\0")
            handle.flush()
        lock(handle, exclusive=True)
        try:
            if inputs(build, source, command, env, symbol, rva, size) != before:
                raise ValueError("inputs changed while waiting for the experiment lock; retry")
            output = None if force else reusable(build, source, entry, key)
            hit = output is not None
            cacheable = hit
            if output is None:
                run = entry / ("run-" + uuid.uuid4().hex[:12])
                run.mkdir()
                output = run / "candidate.obj"
                command, env = current_command(build, source, output)
                inventory = build.search_inventory(source, command, env)
                import census_receipts
                try:
                    probe = census_receipts.snapshot(source, command, env)
                except (OSError, ValueError, SystemExit):
                    probe = None
                try:
                    compiled = subprocess.run(command + ["-showIncludes"], cwd=root, env=env,
                                              stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                              text=True, errors="replace", timeout=timeout)
                except subprocess.TimeoutExpired as error:
                    (run / "compile.log").write_text(str(error), encoding="utf-8")
                    return {"diagnostic_only": True, "landing_verified": False, "candidate_exact": False,
                            "status": "compile-timeout", "cache_hit": False, "cache_key": key,
                            "artifact_dir": str(run)}
                log = compiled.stdout or ""
                (run / "compile.log").write_text(log, encoding="utf-8")
                if compiled.returncode != 0 or not output.is_file():
                    return {"diagnostic_only": True, "landing_verified": False, "candidate_exact": False,
                            "status": "compile-error", "returncode": compiled.returncode,
                            "cache_hit": False, "cache_key": key, "artifact_dir": str(run)}
                try:
                    build._write_deps_sidecar(source, output, build._cmd_fingerprint(command, env), log,
                                             True, command, env, inventory, [])
                    cacheable = (stable_preprocessor_inputs(probe, source, log, census_receipts)
                                 and build.compile_is_current(source, output, strict=True))
                except (OSError, ValueError, SystemExit):
                    cacheable = False
            try:
                result = evaluate(build, source, output, symbol, rva, size)
                result["status"] = "candidate-exact" if result["candidate_exact"] else "needs-work"
            except (OSError, ValueError, SystemExit) as error:
                result = {"diagnostic_only": True, "landing_verified": False, "candidate_exact": False,
                          "status": "evaluation-error", "error": str(error)}
            # A changing ledger, compiler, source or include cannot bless either
            # a new result or an otherwise valid cached object.
            after_command, after_env = current_command(build, source, output)
            stable = (inputs(build, source, after_command, after_env, symbol, rva, size) == before
                      and build.compile_is_current(source, output, strict=True))
            if not stable:
                result.update(candidate_exact=False, status="inputs-unproven-or-changed")
            result.update(cache_hit=hit, cache_key=key, cacheable=bool(cacheable and stable),
                          source=str(source), symbol=symbol, rva=f"0x{rva:08X}", object=str(output),
                          artifact_dir=str(output.parent),
                          required_next="Identity/provenance review; install the candidate in its proper Code/ file, "
                          "run ./build.sh on that whole file and all normal hooks before landing.")
            atomic_json(output.parent / "result.json", result)
            if cacheable and stable:
                atomic_json(entry / "cache.json", {"version": VERSION, "key": key,
                            "object": output.relative_to(entry).as_posix(), "object_sha256": digest(output)})
            return result
        finally:
            unlock(handle)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="complete candidate translation unit; preserve its include context")
    parser.add_argument("--symbol", required=True, help="exact decorated COFF symbol")
    parser.add_argument("--rva", required=True, type=lambda value: int(value, 0))
    parser.add_argument("--size", required=True, type=int, help="proven complete retail body extent")
    parser.add_argument("--cache", type=Path, help="private cache below this checkout's build/")
    parser.add_argument("--force", action="store_true", help="compile again even when a receipt proves reuse")
    parser.add_argument("--timeout", type=float, default=120)
    args = parser.parse_args(argv)
    try:
        result = run_experiment(args.source, args.symbol, args.rva, args.size,
                                cache=args.cache, force=args.force, timeout=args.timeout)
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print(json.dumps(result, indent=2, sort_keys=True))
    # An exact diagnostic does not signal a passed landing gate.
    return 0 if result["status"] not in ("compile-error", "compile-timeout", "evaluation-error") else 1


if __name__ == "__main__":
    raise SystemExit(main())
