#!/usr/bin/env python3
"""Move units off the hand-written DirectX stand-ins onto the imported SDK.

The DirectX 9.0c SDK of August 2005 is a compatible reconstruction input, not a
recovered build input: game.dat imports d3dx9_27.dll and this release's
d3dx9core.h defines D3DX_SDK_VERSION 27 (vendor/dxsdk-aug2005/PROVENANCE.txt;
tools/build.py dxsdk_root checks it). SDK declarations a unit
compiles against should come from it rather than from a byte-matched
reconstruction such as reference/shims/d3d8_shim_validated.h and the
reference/shims/sweep/{d3d8,d3dx8*,D3DXMath,dinput,dxerr8}.h routes into it.

`scan` finds the ledger units that open such a stand-in (a header under
reference/shims/ named like an SDK header, or the validated shim itself), then
recompiles each one against the real headers and compares every row that
matches today with retail through build.py's own comparison:

  trial `sdk`       -I <SDK>/Include ahead of the unit's own
                    paths: what the `// dxsdk` marker does, nothing else;
  trial `sdk+psdk`  the same plus the toolchain's PlatformSDK headers
                    (`// platformsdk`), which the real SDK headers need;
  trial `rewrite`   the unit and the game headers it reads rewritten from the
                    DirectX 8 spellings the shim kept (d3d8.h, IDirect3DDevice8,
                    D3DCAPS8, an explicit shim path, ...) to the SDK's DirectX 9
                    ones, in a scratch overlay; ledger names are mapped the same
                    way. Nothing in the tree is edited.

Each unit gets one class in reverse/dx_migration_queue.tsv:

  as-is       `// dxsdk` alone keeps every row byte-true and no stand-in opens
  as-is+psdk  as-is, with `// platformsdk` as well
  mechanical  the `rewrite` trial is byte-true: the edit is the listed renames
              (and, for ledger rows whose mangled names carry a DirectX 8 type,
              a rename of those rows)
  dx8-observed  an untouched trial is byte-true but opens the SDK's DirectX 8
              headers (d3d8.h, ...): DX8 headers observed, compatibility
              unresolved. Served after the classes above, for per-body
              assessment of whether retail's unit read those headers
  mismatch    a trial compiles stand-in free but a row differs; `detail` names
              the first row and byte offset
  blocked     no trial compiles stand-in free; `detail` is the first error or
              the stand-in still opened

  python3 tools/dx_migration.py scan [SOURCE...]     # writes the queue (all units)
  python3 tools/dx_migration.py next [--class C]     # one unit to migrate next
  python3 tools/dx_migration.py stats                # queue totals

Scratch objects live under build/dx_migration/; the shared build/match objects
are only ever written by the ledger's own compile command.
"""
import argparse
import concurrent.futures
import csv
import json
import os
import re
import shutil
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

QUEUE = ROOT / "reverse" / "dx_migration_queue.tsv"
SCRATCH = ROOT / "build" / "dx_migration"
SHIM_ROOT = ROOT / "reference" / "shims"
HEADER_SUFFIXES = (".h", ".hpp", ".inl", ".inc")
SOURCE_SUFFIXES = (".cpp", ".c")
FIELDS = ("source", "class", "rows", "matched_rows", "shims", "sdk", "edits", "detail")
CLASSES = ("as-is", "as-is+psdk", "mechanical", "dx8-observed", "mismatch", "blocked")
SERVED = ("as-is", "as-is+psdk", "mechanical", "dx8-observed")
# The SDK still ships the DirectX 8 headers. A byte match through them neither
# proves nor refutes that retail's unit read them; each body needs a look.
DX8_SDK_HEADERS = {"d3d8.h", "d3d8types.h", "d3d8caps.h", "dxerr8.h"}
DX8_NOTE = "DX8 headers observed; compatibility unresolved"

# Stand-ins named for headers the SDK does not ship (the DirectX 8 D3DX the
# shim imitates) plus the validated shim every route leads to.
_EXTRA_STANDIN_NAMES = {"d3dx8.h", "d3dx8core.h", "d3dx8math.h", "d3dx8mesh.h",
                        "d3dx8tex.h", "d3dxmath.h", "d3d8_shim_validated.h"}

INCLUDE_LINE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*([<"])([^>"]+)[>"]', re.M)

# DirectX 8 spellings the shim kept -> the SDK's DirectX 9 ones. Header names
# first, then the type names; the D3DX math types are version-free.
HEADER_RENAMES = (
    ("d3d8.h", "d3d9.h"), ("d3d8types.h", "d3d9types.h"), ("d3d8caps.h", "d3d9caps.h"),
    ("d3dx8.h", "d3dx9.h"), ("d3dx8core.h", "d3dx9core.h"), ("d3dx8math.h", "d3dx9math.h"),
    ("d3dx8mesh.h", "d3dx9mesh.h"), ("d3dx8tex.h", "d3dx9tex.h"), ("D3DXMath.h", "d3dx9math.h"),
    ("dxerr8.h", "dxerr9.h"),
)
TYPE_RENAMES = (
    (re.compile(r"\b(I|LP|P)?(DIRECT3D|Direct3D)(\w*?)8\b"), r"\1\2\g<3>9"),
    (re.compile(r"\b(_?D3D(?:CAPS|LIGHT|MATERIAL|VIEWPORT|ADAPTER_IDENTIFIER|CLIPSTATUS))8\b"), r"\g<1>9"),
    (re.compile(r"\bDXGetError(String|Description)8([AW]?)\b"), r"DXGetError\g<1>9\2"),
)
SHIM_PATH_INCLUDE = re.compile(
    r'^([ \t]*#[ \t]*include[ \t]*)"[^"\n]*reference/shims/d3d8_shim_validated\.h"', re.M)
MANGLED_RENAMES = (
    (re.compile(r"(IDirect3D\w*?)8@@"), r"\g<1>9@@"),
    (re.compile(r"(_D3D(?:CAPS|LIGHT|MATERIAL|VIEWPORT|ADAPTER_IDENTIFIER|CLIPSTATUS))8@@"), r"\g<1>9@@"),
)


def build_module():
    import build
    return build


def sdk_include():
    """The verified SDK's Include/ (build.dxsdk_root exits when it is absent)."""
    return build_module().dxsdk_root() / "Include"


def standin_names():
    return {p.name.lower() for p in sdk_include().iterdir() if p.is_file()} | _EXTRA_STANDIN_NAMES


def sdk_headers(includes):
    """Basenames of the SDK headers a compile opened."""
    root = os.path.normcase(str(sdk_include().resolve()))
    return sorted({Path(p).name for p in includes
                   if os.path.normcase(str(Path(p).resolve())).startswith(root)})


def is_standin(path, names):
    """A header under reference/shims/ standing in for an SDK header."""
    try:
        Path(path).resolve().relative_to(SHIM_ROOT.resolve())
    except ValueError:
        return False
    return Path(path).name.lower() in names


# ---------------------------------------------------------------- discovery

def _scan_roots():
    """Where a ledger unit's headers can live: the tree's own sources and shims,
    and the Open-BFME-1 source trees its `// cl:` paths name (not that
    checkout's toolchains, targets and analysis, which no unit includes)."""
    yield ROOT / "Code"
    for top in sorted((ROOT / "reference").iterdir()):
        if top.name != "open-bfme-1" and top.is_dir():
            yield top
    bfme1 = ROOT / "reference" / "open-bfme-1"
    for part in ("game", "reference", "inputs/reference", "inputs/vendor", "Code"):
        if (bfme1 / part).is_dir():
            yield bfme1 / part


def include_graph():
    """{included basename (lower): {file including it}} over Code/ and reference/."""
    includers = defaultdict(set)
    for top in _scan_roots():
        for dirpath, dirnames, filenames in os.walk(top):
            dirnames[:] = [d for d in dirnames if d not in (".git", "toolchains", "gen_asm", "masm_dumps")]
            for filename in filenames:
                if not filename.lower().endswith(HEADER_SUFFIXES + SOURCE_SUFFIXES):
                    continue
                path = os.path.join(dirpath, filename)
                try:
                    with open(path, "r", encoding="latin-1") as handle:
                        text = handle.read()
                except OSError:
                    continue
                for _, literal in INCLUDE_LINE.findall(text):
                    includers[literal.replace("\\", "/").rsplit("/", 1)[-1].lower()].add(path)
    return includers


def reaching(names, includers):
    """Every scanned file that can reach one of `names` by #include name."""
    frontier, seen, reached = list(names), set(), set()
    while frontier:
        current = frontier.pop()
        if current in seen:
            continue
        seen.add(current)
        for path in includers.get(current, ()):
            if path not in reached:
                reached.add(path)
                frontier.append(os.path.basename(path).lower())
    return reached


def ledger_units(build):
    """{source path: [matched rows]} for compiled C/C++ units."""
    units = defaultdict(list)
    for row in build.load_function_rows():
        source = ROOT / row["source"]
        if source.suffix.lower() in SOURCE_SUFFIXES and row.get("status") == "matched":
            units[source].append(row)
    return units


def candidates(build, units):
    names = standin_names()
    reached = {os.path.normcase(os.path.abspath(p)) for p in reaching(names, include_graph())}
    return sorted(s for s in units if os.path.normcase(os.path.abspath(s)) in reached)


def sidecar_deps(build, output):
    try:
        meta = json.loads(build._deps_sidecar(output).read_text())
    except (OSError, ValueError):
        return None
    return [dep if os.path.isabs(dep) else str(ROOT / dep) for dep in meta.get("deps", {})]


# ---------------------------------------------------------------- compiling

def _run(command, env):
    result = subprocess.run(command + ["-showIncludes"], cwd=ROOT, env=env,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    return result.returncode, result.stdout or ""


def _includes(build, stdout):
    out = []
    for line in stdout.splitlines():
        if line.startswith("Note: including file:"):
            host = build._host_path(line[len("Note: including file:"):].strip())
            out.append(build._case_resolve(host) or host)
    return out


def _first_error(stdout):
    stdout = re.sub(re.escape(str(ROOT) + os.sep), "", stdout, flags=re.I)
    for line in stdout.splitlines():
        if re.search(r"\b(error|fatal error) [A-Z]\d+", line):
            return line.strip()[:200]
    lines = [l for l in stdout.splitlines() if l.strip() and not l.startswith("Note: including file:")]
    return (lines[0].strip() if lines else "compile failed")[:200]


def trial_compile(build, source, output, *, psdk=False, overlay=None, compile_source=None):
    """Compile `source` (or its rewritten copy) with the SDK include first.
    Returns (ok, includes, first error)."""
    command, env = build.compiler_command(source, output)
    env = dict(env)
    sdk_flag = "-I" + build.dxsdk_include_arg()
    psdk_flag = "-I" + build.wine_path(build.vc71_root() / "Vc7" / "PlatformSDK" / "Include")
    command = [part for part in command if part not in (sdk_flag, psdk_flag)]
    at = command.index("-EHsc-") + 1
    # what `// dxsdk` (and `// dxsdk` with `// platformsdk`) puts there
    front = [sdk_flag] + ([psdk_flag] if psdk else [])
    if overlay is not None:
        front = ["-I" + build.wine_path(overlay)] + front
    command[at:at] = front
    if compile_source is not None:
        command[-1] = compile_source.relative_to(ROOT).as_posix()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.unlink(missing_ok=True)
    code, stdout = _run(command, env)
    if code and "Cannot open include file" in stdout:
        sweep = [d for d in build._SWEEP_INCLUDE_DIRS if d.exists()]
        env["INCLUDE"] = env["INCLUDE"] + ";" + ";".join(build.wine_path(d) for d in sweep)
        command = command + [f"-I{build.wine_path(d)}" for d in sweep]
        code, stdout = _run(command, env)
    return code == 0, _includes(build, stdout), (None if code == 0 else _first_error(stdout))


def compare_rows(build, rows, output, symbol_map, rename=False):
    """(matching rows, first difference or None) for `rows` against `output`."""
    good, first = 0, None
    for row in rows:
        probe = dict(row)
        if rename:
            probe["name"] = mangled_rename(row["name"])
        try:
            patch = build.compile_function(probe, symbol_map, output)
        except (ValueError, SystemExit) as error:
            first = first or f"{row['name']}: {str(error)[:120]}"
            continue
        if patch["bytes"] == patch["target"] and not patch["unresolved"]:
            good += 1
            continue
        if first is None:
            at = next((i for i, (a, b) in enumerate(zip(patch["bytes"], patch["target"])) if a != b),
                      min(len(patch["bytes"]), len(patch["target"])))
            first = (f"{row['name']} +0x{at:x}: built {patch['bytes'][at:at + 6].hex()} "
                     f"retail {patch['target'][at:at + 6].hex()}")
            if patch["unresolved"]:
                first += f" unresolved {patch['unresolved'][:2]}"
    return good, first


# ---------------------------------------------------------------- rewriting

def rewrite_text(text):
    """(new text, [edit labels]) with the DirectX 8 spellings renamed."""
    edits = []
    new = SHIM_PATH_INCLUDE.sub(r"\1<d3d9.h>\n\1<d3dx9math.h>", text)
    if new != text:
        edits.append("shim-path->d3d9.h")
    for old, replacement in HEADER_RENAMES:
        pattern = re.compile(r'(#[ \t]*include[ \t]*[<"])' + re.escape(old) + r'([>"])', re.I)
        updated = pattern.sub(lambda m: m.group(1) + replacement + m.group(2), new)
        if updated != new:
            edits.append(f"{old}->{replacement}")
            new = updated
    for pattern, replacement in TYPE_RENAMES:
        for old in sorted({m.group(0) for m in pattern.finditer(new)}):
            edits.append(f"{old}->{pattern.sub(replacement, old)}")
        new = pattern.sub(replacement, new)
    return new, edits


def mangled_rename(name):
    for pattern, replacement in MANGLED_RENAMES:
        name = pattern.sub(replacement, name)
    return name


def prepare_rewrite(source, deps, names, overlay):
    """Rewrite the unit beside itself and its game headers into `overlay`.
    Returns (rewritten unit path or None, edit labels)."""
    if overlay.exists():
        shutil.rmtree(overlay)
    overlay.mkdir(parents=True)
    edits = set()
    for dep in deps or ():
        path = Path(dep)
        if not path.suffix.lower() in HEADER_SUFFIXES or is_standin(path, names):
            continue
        try:
            path.resolve().relative_to(sdk_include().resolve())
            continue
        except ValueError:
            pass
        try:
            text = path.read_text(encoding="latin-1")
        except OSError:
            continue
        new, labels = rewrite_text(text)
        if labels:
            (overlay / path.name).write_text(new, encoding="latin-1", newline="")
            edits.update(f"{path.name}:{label}" for label in labels)
    text = source.read_text(encoding="latin-1")
    new, labels = rewrite_text(text)
    if not labels and not edits:
        return None, []
    copy = source.with_name(source.stem + ".dxmig" + source.suffix)
    copy.write_text(new, encoding="latin-1", newline="")
    edits.update(f"{source.name}:{label}" for label in labels)
    return copy, sorted(edits)


# ---------------------------------------------------------------- classify

def classify(build, source, rows, symbol_map, names):
    rel = source.relative_to(ROOT).as_posix()
    baseline = build.obj_path(source)
    deps = sidecar_deps(build, baseline) or []
    shims = sorted({Path(d).name for d in deps if is_standin(d, names)})
    base_good = [row for row in rows
                 if compare_rows(build, [row], baseline, symbol_map)[0] == 1]
    record = {"source": rel, "rows": len(rows), "matched_rows": len(base_good),
              "shims": ",".join(shims), "edits": "", "detail": ""}
    stem = re.sub(r"[^A-Za-z0-9_]", "_", rel)
    output = SCRATCH / (stem + ".obj")
    failures = []
    dx8_match = None
    for label, psdk in (("as-is", False), ("as-is+psdk", True)):
        ok, includes, error = trial_compile(build, source, output, psdk=psdk)
        still = sorted({Path(p).name for p in includes if is_standin(p, names)})
        if not ok:
            failures.append(f"{label}: {error}")
            continue
        if still:
            failures.append(f"{label}: still opens {','.join(still)}")
            continue
        good, first = compare_rows(build, base_good, output, symbol_map)
        if good == len(base_good):
            opened = sdk_headers(includes)
            dx8 = sorted(DX8_SDK_HEADERS & {h.lower() for h in opened})
            if dx8:
                # A DX9 rewrite is still preferred when it also holds; if not,
                # the unit stays servable for per-body assessment.
                dx8_match = dx8_match or (label, opened)
                failures.append(f"{label}: byte-true through {','.join(dx8)}")
                continue
            record["class"] = label
            record["sdk"] = ",".join(opened)
            return record
        failures.append(f"{label}: {good}/{len(base_good)} {first}")
    overlay = SCRATCH / (stem + ".overlay")
    copy, edits = prepare_rewrite(source, deps, names, overlay)
    record["edits"] = ";".join(edits)
    try:
        if copy is not None or edits:
            for psdk in (False, True):
                ok, includes, error = trial_compile(build, source, output, psdk=psdk, overlay=overlay,
                                                    compile_source=copy)
                still = sorted({Path(p).name for p in includes if is_standin(p, names)})
                if not ok:
                    failures.append(f"rewrite{'+psdk' if psdk else ''}: {error}")
                    continue
                if still:
                    failures.append(f"rewrite: still opens {','.join(still)}")
                    continue
                good, first = compare_rows(build, base_good, output, symbol_map, rename=True)
                if good == len(base_good):
                    record["class"] = "mechanical"
                    record["sdk"] = ",".join(sdk_headers(includes))
                    if psdk:
                        record["edits"] = "+platformsdk;" + record["edits"]
                    return record
                failures.append(f"rewrite: {good}/{len(base_good)} {first}")
    finally:
        if copy is not None:
            copy.unlink(missing_ok=True)
        shutil.rmtree(overlay, ignore_errors=True)
    if dx8_match is not None:
        record["class"] = "dx8-observed"
        record["sdk"] = ",".join(dx8_match[1])
        record["edits"] = "+platformsdk" if dx8_match[0] == "as-is+psdk" else ""
        record["detail"] = (DX8_NOTE + " | " + " | ".join(failures))[:600]
        return record
    compiled = [f for f in failures if re.search(r": \d+/\d+ ", f)]
    record["class"] = "mismatch" if compiled else "blocked"
    record["detail"] = " | ".join(compiled[:1] + [f for f in failures if f not in compiled[:1]] or ["no trial"])[:600]
    return record


def write_queue(records):
    QUEUE.parent.mkdir(parents=True, exist_ok=True)
    order = {c: i for i, c in enumerate(CLASSES)}
    records = sorted(records, key=lambda r: (order.get(r["class"], 9), -int(r["matched_rows"]), r["source"]))
    with QUEUE.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, delimiter="\t", lineterminator="\n", extrasaction="ignore")
        writer.writeheader()
        for record in records:
            writer.writerow({k: str(record.get(k, "")).replace("\t", " ").replace("\n", " ") for k in FIELDS})


def read_queue():
    if not QUEUE.exists():
        return []
    with QUEUE.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle, delimiter="\t"))


def cmd_scan(args):
    build = build_module()
    units = ledger_units(build)
    if args.sources:
        wanted = [(ROOT / s).resolve() for s in args.sources]
        found = {s.resolve(): s for s in units}
        sources = [found[w] for w in wanted if w in found]
    else:
        sources = candidates(build, units)
    print(f"dx_migration: {len(sources)} candidate unit(s) reach an SDK-named header by name")
    rows = [row for source in sources for row in units[source]]
    build.compile_rows(rows, sources)
    names = standin_names()
    users = [s for s in sources
             if any(is_standin(d, names) for d in (sidecar_deps(build, build.obj_path(s)) or []))]
    print(f"dx_migration: {len(users)} unit(s) open a reference/shims stand-in")
    symbol_map = build.load_symbol_map()
    records = []
    workers = max(1, int(os.environ.get("BUILD_POOL", "1")))
    with concurrent.futures.ThreadPoolExecutor(workers) as pool:
        futures = {pool.submit(classify, build, s, units[s], symbol_map, names): s for s in users}
        for future in concurrent.futures.as_completed(futures):
            source = futures[future]
            try:
                record = future.result()
            except Exception as error:  # one unit's failure is a queue entry, not a dead scan
                record = {"source": source.relative_to(ROOT).as_posix(), "class": "blocked",
                          "rows": len(units[source]), "matched_rows": "", "shims": "",
                          "edits": "", "detail": f"scan error: {error}"[:200]}
            records.append(record)
            print(f"  {record['class']:<11} {record['source']}  {record['detail'][:100]}", flush=True)
    if args.sources:
        # a requested unit that no longer opens a stand-in leaves the queue
        keep = {s.relative_to(ROOT).as_posix() for s in sources}
        records += [r for r in read_queue() if r["source"] not in keep]
    write_queue(records)
    cmd_stats(args)


def cmd_stats(args):
    records = read_queue()
    totals = Counter(r["class"] for r in records)
    print(f"{QUEUE.relative_to(ROOT).as_posix()}: {len(records)} unit(s)")
    for name in CLASSES:
        print(f"  {name:<11} {totals.get(name, 0):>4}")


def servable(classes=SERVED):
    """Queue records to migrate, in queue order (tools/next_work.py --tier dx)."""
    return [record for record in read_queue() if record["class"] in classes]


def serve(classes=SERVED):
    """The queue's next unit to migrate."""
    return next(iter(servable(classes)), None)


def cmd_next(args):
    record = serve((args.cls,) if args.cls else SERVED)
    if record is None:
        print("dx_migration: nothing queued")
        return 1
    print(json.dumps(record, indent=1))
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="command", required=True)
    scan = sub.add_parser("scan")
    scan.add_argument("sources", nargs="*")
    nxt = sub.add_parser("next")
    nxt.add_argument("--class", dest="cls", choices=CLASSES)
    sub.add_parser("stats")
    args = ap.parse_args(argv)
    return {"scan": cmd_scan, "next": cmd_next, "stats": cmd_stats}[args.command](args) or 0


if __name__ == "__main__":
    sys.exit(main())
