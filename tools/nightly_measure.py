#!/usr/bin/env python3
"""Nightly measurement with separate Windows builder and publisher accounts.

The installed runner requires --role builder|publisher. Builder executes checkout,
gate, cycle, boot and ownership measurement without credentials. Publisher reads
an untrusted handoff, freezes a private copy, replaces all executable checker code
with its installed hash-pinned bundle, validates receipt/core, closure, bundle and
bound ownership artifacts, signs the ownership row and publishes. Publisher never
runs hooks, builds, links, boots, or imports code supplied by the builder.

See docs/nightly_setup.md for the mandatory account, ACL and scheduler setup.
Environment scrubbing is defense in depth; Windows account isolation is the
credential boundary. --approve is a maintainer-only install operation, never a
scheduled action. Existing Run helpers remain for component regression tests;
only BuilderRun and PublisherRun are reachable from the scheduled CLI.
Landing dependency: this runner lands after the north-star commit containing
tools/image_ownership.py (agent-a0b594d3646db42ad's committed branch).
"""
import argparse
import ast
import csv
import hashlib
import inspect
import io
import json
import os
import re
import shutil
import socket
import stat
import subprocess
import sys
import tempfile
import time
import zipfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
RUNNER = Path(__file__).resolve()
MARK = "NIGHTLY_MEASURE_CHECKOUT"            # in <checkout>/build/: this tool created the checkout
SNAPSHOT_MARK = "SNAPSHOT.json"               # link_cycle.SNAPSHOT_MARK
COOLDOWN = 300.0                              # AGENTS.md #7: five minutes between GitHub writes
LEASE = 12 * 3600.0                           # a crashed run's snapshot lease expires after this
SKIPPABLE = ("gate", "boot", "ownership")
EXIT_OK, EXIT_FAILED, EXIT_SETUP, EXIT_LOCKED, EXIT_DEGRADED, EXIT_UNAPPROVED = 0, 1, 2, 3, 4, 5
EMPTY_STORE = 3                               # cycle_artifacts EXIT["empty"]: no trusted bundle yet
NOT_VERIFIED, NOT_RECORDED = 3, 4             # the ownership child's refusals
SUBMODULE = "reference/open-bfme-1"
CODE_PATHS = ("tools", ".githooks", "vendor") # what runs with the credentials, with SUBMODULE (vendor: cl.exe, DLLs)
IDENT_KEYS = ("tools_tree", "githooks_tree", "vendor_tree", "submodule", "runner_sha256")
HISTORY_CSV = "reverse/image_ownership_history.csv"
BOOT_TAG = "relayout"                         # image_ownership.DEFAULT_REPORT is build/boot/relayout.json
PUSH_TRIES = 3
TRUSTED_COMMANDS = {}                         # populated from protected security.json by a split role
TRUSTED_CWD = None
DROP_ENV = ("LINK_CYCLE_ROOT", "BUILD_RECOMPILE_ONLY", "PYTHONPATH", "CCC_OVERRIDE_OPTIONS",   # compiler injection
            "CL", "_CL_", "ML", "_ML_", "LINK", "_LINK_",             # options cl/ml/link read from the environment
            "VC71_ROOT", "STLPORT_ROOT")                           # always use the approved toolchain/includes
CRED_ENV = ("GH_TOKEN", "GITHUB_TOKEN", "GH_ENTERPRISE_TOKEN", "GITHUB_ENTERPRISE_TOKEN", "GIT_ASKPASS",
            "SSH_ASKPASS", "SSH_AUTH_SOCK")
SECRETISH = re.compile(r"TOKEN|SECRET|PASSW|API_?KEY|CREDENTIAL|ASKPASS", re.I)
GIT_KEEP_WITH_CREDS = ("GIT_SSH", "GIT_SSH_COMMAND", "GIT_SSH_VARIANT")   # the publisher's own transport
GIT_SAFE = ("core.fsmonitor=", "commit.gpgSign=false", "protocol.ext.allow=never", "diff.external=",
            "diff.trustExitCode=false", "core.attributesFile=" + os.devnull)
GIT_NO_CREDS = ("credential.helper=", "core.askPass=")   # an empty helper empties every helper list
DRIVER_KEY = re.compile(r"^(filter|merge|diff)\.(.+)\.(clean|smudge|process|driver|required|textconv|command)$")

# ---- what a source may say to its compiler (build.source_extra_flags, compiler_profiles.select)
CL_MARK, COMPILER_MARK = "// cl:", "// compiler:"
SOURCE_SUFFIXES = (".c", ".cpp", ".cc", ".cxx", ".asm")
PINNED_COMPILERS = frozenset({"vc71-sp1", "vc71-ddk-4035", "clang23-x86"})   # hash-pinned under vendor/
# every `-` style `// cl:` token of the tree's sources on 2026-10-24 that takes no free operand
CL_FLAGS = frozenset("""
-EHa -EHc- -EHs -EHs- -EHs-c- -EHsc -EHsc- -G5 -G6 -G7 -GB -GF -GF- -GR -GR- -GS -GS- -GX -GX- -GZ -Gy
-MD -MT -O1 -O2 -Oa -Ob0 -Ob1 -Ob2 -Od -Og -Og- -Oi -Oi- -Op -Os -Ot -Ow -Ox -Oy -Oy- -RTCu -Z7 -Zc:wchar_t
-arch:IA32 -arch:SSE -arch:SSE2 -d2inlS100 -hotpatch -vd2 -vmg -vmm
""".split())
# prose that three Code/ sources carry on their `// cl:` line: cl reads these as file names or warns
CL_WORDS = frozenset(["(none", "--", "build.py", "base", "flags)", "(at", "defaults", "MSVC", "7.1", "folds",
                      "`x", "|=", "-1`", "into", "`mov", "[ecx],-1`;"])
CL_PAIRS = {"-clang:-mllvm": frozenset({"-clang:-branch-folder-reorder-blocks=false"})}   # -mllvm takes the next
CL_DEFINES = frozenset("""
-DBFME2_RETAIL_STRUCTURE_COLLAPSE_API -DBFME_ASCII_DTOR_DECL -DBFME_ASCII_KEEP_CHAR_SET_BODY
-DBFME_ASCII_KEEP_COPY_SET_BODY -DBFME_BUFFER_DTOR_OUT_OF_LINE -DBFME_COORD3D_INLINE_SCALE_LINK
-DBFME_HASHTABLE_NEW_NODE_NOFORCEINLINE -DBFME_MATRIX4_INCLASS_DEFAULT_CTOR -DBFME_MODULE_NO_MPO
-DBFME_RENDEROBJ_SIZE_LOD -DBFME_SB_CLEAR_DECL -DBFME_SNAPSHOT_CAPITALIZED_SLOTS -DBFME_SNAPSHOT_NAME_SLOT
-DBFME_SORTING_DWORD_DRAW -DBFME_STLP_NODE_ALLOC -DBFME_VOLUMETRIC_DELETE_LAYOUT
-DBFME_WEAPON_BARREL_INLINE_ONLY -DBFME_WWSTRING_CTOR_BUFFER_RELOAD -DBFME_WWSTRING_INLINE_CSTR_ASSIGN
-DBFME_WWSTRING_NATIVE_COPY_ASSIGN -DBFME_WWSTRING_NATIVE_COPY_CTOR -DBFME_WWSTRING_NATIVE_CSTR_ASSIGN
-DBFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR -DBFME_WWSTRING_NATIVE_LENGTH -DCRTIMP= -DEXTENDED_STATS
-DIN_ADDR=in_addr -DLZHLINTERNAL -DNDEBUG -DWIN32 -DWeightInfoStruct=WeightInfoStruct_HLod_RV
-DZH_EMIT_POOL_GLUE -D_BFME_RETAIL_TREE_INSERT_LAYOUT -D_CRTBLD -D_CRTIMP= -D_OPERATOR_NEW_DEFINED_
-D_STLP_NO_CSTD_FUNCTION_IMPORTS -D_STLP_NO_EXCEPTIONS -D_STLP_NO_EXCEPTIONS=1 -D_STLP_NO_MEMBER_TEMPLATES
-D_STLP_USE_MALLOC -D_STLP_USE_STATIC_LIB -D_WINDOWS -D__PLACEMENT_VEC_NEW_INLINE
-DsetScriptList=setScriptList_Scripts_RV -Dstricmp=_strcmpi
""".split())
CL_FORCED = frozenset({"-FIbfme_wwstring_teardown.h", "-FIshader.h", "-FIzh_ascii.h"})
CL_REFUSED = re.compile(r"^-B|xclang|plugin|-load|^@|clr|^-FU|^-AI|\.(exe|dll|com|bat|cmd|ps1|so)\b", re.I)
CL_IMPORT = re.compile(r"^[ \t]*#[ \t]*(import|using)\b", re.M)
SOURCE_ERRORS = 8


class Refused(Exception):
    """Setup refused: nothing was measured."""


class StepFailed(Exception):
    """A step failed; a blocking one stops the run."""


class Unapproved(StepFailed):
    """The checkout's code is not the approved code: nothing of it runs."""


def utc(t=None):
    return time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime(time.time() if t is None else t))


def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def write_json(path, value):
    """Atomically, so a reader never sees half a file."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix="." + path.name, dir=path.parent)
    with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(value, indent=1) + "\n")
    os.replace(tmp, path)


def read_json(path, default=None):
    try:
        return json.loads(Path(path).read_text(encoding="utf-8-sig"))
    except (OSError, ValueError):
        return default


def config_args(pairs):
    return [a for p in pairs for a in ("-c", p)]


# a query outside a Run: no hook (os.devnull holds none), no fsmonitor, no credential
QUERY_CONFIG = (*GIT_SAFE, *GIT_NO_CREDS, f"core.hooksPath={os.devnull}")


def git(cwd, *args, binary=False, config=QUERY_CONFIG, env=None):
    where = ["-C", str(cwd)] if TRUSTED_CWD else []
    return subprocess.run([TRUSTED_COMMANDS.get("git", "git"), *where, *config_args(config), *map(str, args)],
                          cwd=TRUSTED_CWD or cwd, capture_output=True,
                          text=not binary, env={**git_environment(), **(env or {})})


def git_environment():
    env = {k: v for k, v in os.environ.items() if not k.upper().startswith("GIT_")
           and not SECRETISH.search(k) and k not in DROP_ENV}
    env.update(GIT_CONFIG_GLOBAL=os.devnull, GIT_CONFIG_NOSYSTEM="1", GIT_TERMINAL_PROMPT="0",
               GH_CONFIG_DIR=str(HERE / "empty-gh"), PYTHONSAFEPATH="1")
    return env


def git_out(cwd, *args, config=QUERY_CONFIG):
    out = git(cwd, *args, config=config)
    if out.returncode:
        raise StepFailed(f"git {' '.join(map(str, args))}: {out.stderr.strip()[:300]}")
    return out.stdout.strip()


def driver_overrides(cwd):
    """Disable each configured filter, merge driver and alias, including names with spaces."""
    result = git(cwd, "config", "--null", "--get-regexp", r"^(filter|merge|alias|diff)\.", binary=True)
    if result.returncode not in (0, 1):
        raise Refused("cannot enumerate Git execution configuration")
    out = result.stdout or b""
    pairs = []
    for item in out.split(b"\0"):
        key = item.split(b"\n", 1)[0].decode("utf-8", errors="replace")
        if key.startswith("alias."):
            pairs.append(f"{key}=")
            continue
        m = DRIVER_KEY.match(key)
        if not m:
            continue
        kind, name = m.group(1), m.group(2)
        more = ([f"filter.{name}.{v}=" for v in ("clean", "smudge", "process")] + [f"filter.{name}.required=false"]
                if kind == "filter" else [f"merge.{name}.driver=false"] if kind == "merge"
                else [f"diff.{name}.textconv=", f"diff.{name}.command="])
        pairs += [p for p in more if p not in pairs]
    return pairs


def blob_id(data, oid):
    """Git's object id of a blob (SHA-1 or SHA-256 by the length of the id it is checked against)."""
    return (hashlib.sha1 if len(oid) == 40 else hashlib.sha256)(b"blob %d\0" % len(data) + data).hexdigest()


# ---------------------------------------------------------------- source directives

def cl_tokens(text):
    """build._source_flag_tokens: whitespace-split, a quoted /I path one operand."""
    tokens, cursor = [], 0
    while cursor < len(text):
        if text[cursor].isspace():
            cursor += 1
            continue
        token = re.match(r"\S+", text[cursor:]).group(0)
        if token.startswith(("/I", "-I")):
            operand = cursor + 2
            if token in ("/I", "-I"):
                while operand < len(text) and text[operand].isspace():
                    operand += 1
            if operand < len(text) and text[operand] == '"':
                close = text.find('"', operand + 1)
                if close < 0:
                    return tokens + [text[cursor:]]   # build.py refuses it; judged as one token here
                tokens.append(token[:2] + text[operand + 1:close])
                cursor = close + 1
                continue
        tokens.append(token)
        cursor += len(token)
    return tokens


def include_problem(path):
    p = path.replace("\\", "/")
    if not p or p.startswith(("/", "-")) or ":" in p or ".." in p.split("/") or any(ord(c) < 32 for c in p):
        return "not a relative directory inside the checkout"
    return ""


def cl_problems(line):
    """Why the tokens of one `// cl:` line are refused (empty when all are allowed)."""
    flags = [t.replace("/", "-", 1) if t.startswith("/") else t for t in cl_tokens(line[len(CL_MARK):])]
    # Check operands too: /I foo.dll must not bypass the executable-path ban.
    bad = [f"{f!r} (compiler, plugin, response file or executable)" for f in flags if CL_REFUSED.search(f)]
    i = 0
    while i < len(flags):
        f = flags[i]
        if f in CL_PAIRS:
            if i + 1 >= len(flags) or flags[i + 1] not in CL_PAIRS[f]:
                bad.append(f"{f!r} not followed by an allowed operand")
            i += 1
        elif f in ("-I",):
            why = include_problem(flags[i + 1]) if i + 1 < len(flags) else "no operand"
            if why:
                bad.append(f"-I {flags[i + 1] if i + 1 < len(flags) else ''!r}: {why}")
            i += 1
        elif f.startswith("-I"):
            why = include_problem(f[2:])
            if why:
                bad.append(f"{f!r}: {why}")
        elif not (f in CL_FLAGS or f in CL_WORDS or f in CL_DEFINES or f in CL_FORCED):
            bad.append(f"{f!r} (not in the allowlist)")
        i += 1
    return bad


def directive_problems(root, rels):
    """Why the sources `rels` (relative to `root`) could steer the compiler off the approved
    toolchain: every `// cl:` and `// compiler:` line, and `#import`."""
    problems = []
    for rel in rels:
        try:
            text = (Path(root) / rel).read_bytes().decode("utf-8-sig", errors="replace")
        except OSError as e:
            problems.append(f"{rel}: cannot inspect source: {e}")
            continue
        problems += directive_text_problems(rel, text)
    return problems


def directive_text_problems(rel, text):
    lines = text.splitlines()
    problems = []
    # Inspect all directives, including dormant duplicates, rather than letting a
    # later build.py change expose an unchecked directive.
    for line in lines:
        if line.startswith(CL_MARK):
            problems += [f"{rel}: // cl: {why}" for why in cl_problems(line)]
    compilers = [line[len(COMPILER_MARK):].strip() for line in lines if line.startswith(COMPILER_MARK)]
    if len(compilers) > 1 or any(c not in PINNED_COMPILERS for c in compilers):
        problems.append(f"{rel}: // compiler: {compilers} (allowed: one of {sorted(PINNED_COMPILERS)})")
    if CL_IMPORT.search(text):
        problems.append(f"{rel}: #import/#using loads a type library or assembly")
    return problems


def region_problems(root):
    """flag_defaults.region_tokens puts `-<opt>` of each region row on the command line."""
    path = Path(root) / "reverse" / "retail_inventory" / "flag_regions.csv"
    try:
        with path.open(newline="", encoding="utf-8") as handle:
            rows = list(csv.DictReader(handle))
    except (OSError, csv.Error, UnicodeDecodeError):
        return []
    return [f"{path.name}: opt {row.get('opt')!r} -> -{row.get('opt')} is not in the allowlist"
            for row in rows if "-" + str(row.get("opt")) not in CL_FLAGS]


def ledger_sources(root):
    path = Path(root) / "reverse" / "functions.csv"
    try:
        with path.open(newline="", encoding="utf-8") as handle:
            return {row.get("source") or "" for row in csv.DictReader(handle)} - {""}
    except (OSError, csv.Error, UnicodeDecodeError):
        return set()


def compiled_sources(root, listed):
    """Of the checkout's files `listed`, the ones a compile can read and that this tool does not
    trust by approval: everything under Code/, sources elsewhere, every ledger source."""
    approved = tuple(p + "/" for p in (*CODE_PATHS, SUBMODULE))
    picked = {rel for rel in listed if rel.startswith("Code/") or rel.lower().endswith(SOURCE_SUFFIXES)}
    picked |= {rel for rel in ledger_sources(root) if not rel.lower().endswith(".lib")}
    return sorted(rel for rel in picked if not rel.replace("\\", "/").startswith(approved))


def source_files(root):
    """Include tracked sources and local additions that the build can discover."""
    tracked = git(root, "ls-files", "-z", "--cached", "--others", "--exclude-standard", binary=True)
    if tracked.returncode:
        raise Unapproved("cannot enumerate tracked sources")
    names = {p.decode("utf-8", errors="surrogateescape") for p in tracked.stdout.split(b"\0") if p}
    return compiled_sources(root, names)


def main_root():
    """The clone's main tree (the parent of the common git directory), as daily_census.sh finds it."""
    out = git(HERE, "rev-parse", "--path-format=absolute", "--git-common-dir")
    if out.returncode:
        raise Refused(f"not in a git clone: {out.stderr.strip()}")
    return Path(out.stdout.strip()).parent


# ---------------------------------------------------------------- approval

def identity(cwd, commit):
    """The code identity of COMMIT: what runs with the publisher's credentials."""
    blob = git(cwd, "show", f"{commit}:tools/nightly_measure.py", binary=True)
    if blob.returncode:
        raise StepFailed(f"{commit} has no tools/nightly_measure.py")
    return {"tools_tree": git_out(cwd, "rev-parse", f"{commit}:tools"),
            "githooks_tree": git_out(cwd, "rev-parse", f"{commit}:.githooks"),
            "vendor_tree": git_out(cwd, "rev-parse", f"{commit}:vendor"),
            "submodule": git_out(cwd, "rev-parse", f"{commit}:{SUBMODULE}"),
            "runner_sha256": sha256_bytes(blob.stdout)}


def approval_diff(approved, ident):
    return [k for k in IDENT_KEYS if approved.get(k) != ident[k]]


def approve(root, rev, out=print, install_dir=None):
    """--approve REV: record REV's code identity as approved and install its runner."""
    work = Path(install_dir) if install_dir else Path(root) / "build" / "nightly_measure"
    commit = git_out(root, "rev-parse", "--verify", f"{rev}^{{commit}}")
    if git(root, "merge-base", "--is-ancestor", commit, "origin/master").returncode:
        raise Refused(f"{commit} is not on origin/master (git fetch origin master first); approve published code")
    ident = identity(root, commit)
    before = read_json(work / "approved.json")
    if before and before.get("commit"):
        out(git(root, "diff", "--stat", before["commit"], commit, "--", *CODE_PATHS, SUBMODULE).stdout.rstrip()
            or "no code change since the last approval")
    runner = work / "runner" / "nightly_measure.py"
    runner.parent.mkdir(parents=True, exist_ok=True)
    blob = git(root, "show", f"{commit}:tools/nightly_measure.py", binary=True).stdout
    tmp = runner.with_suffix(".tmp")
    tmp.write_bytes(blob)
    os.replace(tmp, runner)
    checker_files = install_checkers(root, commit, work / "checkers")
    write_json(work / "approved.json", {"commit": commit, **ident, "checker_files": checker_files, "approved_utc": utc(),
                                        "approved_by": f"{os.environ.get('USERNAME') or os.environ.get('USER')}"
                                                       f"@{socket.gethostname()}"})
    out(f"nightly_measure: approved {commit} (tools {ident['tools_tree'][:12]}, hooks {ident['githooks_tree'][:12]}, "
        f"{SUBMODULE} {ident['submodule'][:12]}); runner installed at {runner}; schedule that file")
    return EXIT_OK


# ---------------------------------------------------------------- lock and clock

def try_lock(path):
    """The open, locked handle of `path`, or None when another process holds it. An
    OS lock: it dies with the process, so a crashed run leaves nothing to clean."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    handle = open(path, "a+")
    try:
        if os.name == "nt":
            import msvcrt
            handle.seek(0)
            msvcrt.locking(handle.fileno(), msvcrt.LK_NBLCK, 1)
        else:
            import fcntl
            fcntl.flock(handle, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except OSError:
        handle.close()
        return None
    return handle


def unlock(handle):
    if os.name == "nt":
        import msvcrt
        handle.seek(0)
        msvcrt.locking(handle.fileno(), msvcrt.LK_UNLCK, 1)
    handle.close()


def last_write(clock):
    try:
        return float(read_json(clock)["last_write"])
    except (TypeError, KeyError, ValueError):
        return 0.0


def wait_cooldown(clock, say, now=None, sleep=None):
    """Sleep until COOLDOWN has passed since the clock's last GitHub write; the seconds waited."""
    wait = last_write(clock) + COOLDOWN - (now or time.time)()
    if wait > 0:
        say(f"nightly_measure: push cooldown: waiting {wait:.0f}s (last GitHub write {utc(last_write(clock))}, {clock})")
        (sleep or time.sleep)(wait)
        return round(wait)
    return 0


def stamp_clock(clock, what, now=None):
    t = (now or time.time)()
    write_json(clock, {"last_write": t, "last_write_utc": utc(t), "what": what,
                       "host": socket.gethostname(), "pid": os.getpid()})


# ---------------------------------------------------------------- ownership (runs in the child)

def measure_ownership(io_mod, report, image, out, record=True, measure_kw=None, record_kw=None):
    """image_ownership's measure() of the ORIGINAL boot report beside its image; the receipt
    to OUT; record() its history row when verified. 0 recorded (or measured, record False),
    NOT_VERIFIED, NOT_RECORDED. Runs in the child from its source (OWNERSHIP_PROBE)."""
    import json
    try:
        receipt = io_mod.measure(report, image=image, **(measure_kw or {}))
    except SystemExit as e:   # the module's own refusal (no image, no map, an unaccountable report)
        print(f"nightly_measure: ownership NOT VERIFIED: measure() refused: {e}")
        return 3
    with open(out, "w", encoding="utf-8") as f:
        f.write(json.dumps(receipt, indent=1, default=str))
    if not receipt.get("verified"):
        print("nightly_measure: ownership NOT VERIFIED:\n  " + "\n  ".join(receipt.get("refusals") or ["(no reason)"]))
        return 3
    print(f"nightly_measure: ownership verified: not ours {receipt.get('north_star')} of "
          f"{receipt.get('content_bytes')} content bytes")
    if record:
        try:
            io_mod.record(receipt, **(record_kw or {}))
        except SystemExit as e:
            print(f"nightly_measure: ownership not recorded: {e}")
            return 4
        print("nightly_measure: ownership recorded")
    return 0


# Every child Python runs isolated (-I: no cwd, script dir, user site or PYTHON* variable on
# its path), so a root-level csv.py or json.py of the measured commit never shadows the
# stdlib; the only import dir added is the approved tools/ (argv[1]), by absolute path.
OWNERSHIP_PROBE = ("import sys\nsys.path.insert(0, sys.argv[1])\nimport image_ownership\n"
                   + inspect.getsource(measure_ownership)
                   + "sys.exit(measure_ownership(image_ownership, sys.argv[2], sys.argv[3], sys.argv[4], "
                     "record=sys.argv[5] == 'record'))\n")
SCRIPT_BOOT = ("import runpy, sys\nsys.path.insert(0, sys.argv[1])\nsys.argv = sys.argv[2:]\n"
               "runpy.run_path(sys.argv[0], run_name='__main__')\n")


# ---------------------------------------------------------------- the run

class Run:
    def __init__(self, args, root, out=print):
        self.args, self.root, self.say = args, Path(root), out
        self.work = self.root / "build" / "nightly_measure"
        self.checkout = Path(args.checkout or self.root / "build" / "nightly_measure_wt").resolve()
        self.snapshots = Path(args.snapshot_dir or self.root / "build" / "nm").resolve()
        self.clock = Path(args.push_clock or os.environ.get("BFME_PUSH_CLOCK") or self.root / "build" / "push_clock.json")
        self.store = self.checkout / "build" / "cycle_bundles"
        self.approval_file = self.work / "approved.json"
        self.registry = self.work / "snapshots.json"
        self.py = sys.executable
        self.runner = RUNNER
        self.commit = self.dir = self.approved = None
        self.hooks = self.work / "empty-hooks"
        self.gh_dir = self.work / "empty-gh"
        self.bundle_out = False
        self.summary = {"tool": "nightly_measure", "host": socket.gethostname(), "started_utc": utc(),
                        "checkout": str(self.checkout), "snapshot_dir": str(self.snapshots),
                        "publish": not args.no_publish, "skipped_by_request": sorted(args.skip),
                        "commit": None, "status": "running", "steps": [], "failures_after_bundle": []}

    # -- bookkeeping
    def open_run_dir(self):
        stamp = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime())
        self.dir = self.work / "runs" / stamp
        n = 1
        while self.dir.exists():
            n += 1
            self.dir = self.work / "runs" / f"{stamp}-{n}"
        self.dir.mkdir(parents=True)
        self.summary["run_dir"] = str(self.dir)
        self.save()

    def save(self):
        if self.dir is not None:
            write_json(self.dir / "run.json", self.summary)
            write_json(self.work / "last_run.json", self.summary)

    def record(self, name, status, note="", **extra):
        self.summary["steps"].append({"step": name, "status": status, "note": note, **extra})
        self.save()
        self.say(f"nightly_measure: {name}: {status}" + (f" ({note})" if note else ""))

    def env(self, credentialed=False, git_config=()):
        env = {k: v for k, v in os.environ.items() if k not in DROP_ENV}
        if not credentialed:
            env = {k: v for k, v in env.items() if not SECRETISH.search(k) and not k.upper().startswith("GIT_")}
            env["GH_CONFIG_DIR"] = str(self.gh_dir)
        else:
            env = {k: v for k, v in env.items() if not k.upper().startswith("GIT_")
                   or k in GIT_KEEP_WITH_CREDS or k.startswith(("GIT_AUTHOR_", "GIT_COMMITTER_"))}
        env.update(PYTHONUNBUFFERED="1", PYTHONIOENCODING="utf-8", GIT_TERMINAL_PROMPT="0",
                   PYTHONPYCACHEPREFIX=str(self.work / "pycache"),   # never bytecode the checkout carries
                   PYTHONSAFEPATH="1")   # grandchildren and hooks (`python3 -c` at the root): no cwd on sys.path
        # Config discovery and execution must have exactly the same scope,
        # including authenticated history operations. gh supplies authentication.
        env["GIT_CONFIG_GLOBAL"] = os.devnull
        env["GIT_CONFIG_SYSTEM"] = os.devnull
        env["GIT_CONFIG_NOSYSTEM"] = "1"
        options = [*GIT_SAFE, *(() if credentialed else GIT_NO_CREDS),
                   f"core.hooksPath={self.hooks}", *git_config]
        for i, option in enumerate(options):
            env[f"GIT_CONFIG_KEY_{i}"], env[f"GIT_CONFIG_VALUE_{i}"] = option.split("=", 1)
        env["GIT_CONFIG_COUNT"] = str(len(options))
        return env

    def python(self, *args):
        """An isolated child Python (the argv before a script or -c): see OWNERSHIP_PROBE."""
        return [self.py, "-I", "-u", "-X", "utf8", "-X", f"pycache_prefix={self.work / 'pycache'}", *args]

    def tool(self, script, *args):
        """An approved tool run as __main__ with only the checkout's tools/ added to its path."""
        return self.python("-c", SCRIPT_BOOT, self.checkout / "tools", self.checkout / script, *args)

    def step(self, name, argv, cwd=None, accept=None, github_write=False, blocking=True):
        """Run one command, its output in <run>/<name>.log; the record. `accept(rc)` gives
        (status, note); by default 0 is ok, anything else failed. A failed step raises
        StepFailed after it is recorded (blocking) or returns its record."""
        cwd = Path(cwd or self.checkout)
        if name in ("gate", "cycle", "boot"):
            self.prove_sources()
        waited = 0
        if github_write:   # the wait first: the code is proven immediately before it runs
            waited = wait_cooldown(self.clock, self.say)
            self.prove_code("before " + name)
        if argv[0] == "git" and argv[1] in ("rebase", "commit", "push"):
            # A cooldown can last five minutes: verify the hook copy AND sources
            # after waiting, immediately before a hook can compile them.
            self.prove_code("before history hooks: " + name)
            self.prove_sources()
            if argv[1] == "rebase" and argv[-1] != "--abort":
                self.prove_rebase_sources(str(argv[-1]))
            self.approved_hooks()
        log = self.dir / f"{name}.log"
        start = time.time()
        self.say(f"nightly_measure: {name}: {' '.join(map(str, argv))}")
        credentialed = github_write or name in ("publish", "previous", "install") or name.startswith("history-")
        overrides = driver_overrides(cwd)
        env = self.env(credentialed, overrides)
        command = [str(a) for a in argv]
        if argv[0] == "git":
            command = ["git", *config_args((*GIT_SAFE, *(() if credentialed else GIT_NO_CREDS), f"core.hooksPath={self.hooks}",
                                            *overrides)), *map(str, argv[1:])]
        if command[0] in TRUSTED_COMMANDS:
            command[0] = TRUSTED_COMMANDS[command[0]]
        with open(log, "w", encoding="utf-8", errors="replace") as handle:
            try:
                rc = subprocess.run(command, cwd=cwd, stdout=handle, stderr=subprocess.STDOUT,
                                    stdin=subprocess.DEVNULL, env=env).returncode
                if github_write and name == "publish" and rc == 0:
                    # The write already happened: even a clock/summary I/O error
                    # from here must use the post-publication exit-4 contract.
                    self.bundle_out = True
            except OSError as e:
                handle.write(f"nightly_measure: could not start: {e}\n")
                rc = None
            finally:
                if github_write:   # an attempt may have written before it failed: the clock counts it
                    stamp_clock(self.clock, f"nightly_measure {name}")
        end = time.time()
        status, note = (accept or (lambda c: ("ok", "") if c == 0 else ("failed", f"exit {c}")))(rc)
        rec = {"step": name, "status": status, "note": note, "argv": [str(a) for a in argv], "cwd": str(cwd),
               "log": str(log), "exit": rc, "start_utc": utc(start), "end_utc": utc(end),
               "seconds": round(end - start, 1), **({"cooldown_waited": waited} if github_write else {})}
        self.summary["steps"].append(rec)
        self.save()
        self.say(f"nightly_measure: {name}: {status}" + (f" ({note})" if note else ""))
        if status == "failed" and blocking:
            raise StepFailed(name)
        return rec

    def fail(self, name, note, blocking=True):
        self.record(name, "failed", note)
        if blocking:
            raise StepFailed(name)

    def late_failure(self, name, note=""):
        """A failure after the bundle: never blocking it, loudly reported."""
        self.summary["failures_after_bundle"].append(name)
        self.save()
        self.say(f"nightly_measure: *** {name} FAILED{': ' + note if note else ''} -- the link-cycle bundle "
                 f"{'is published' if self.bundle_out else 'stands'}; see {self.dir / (name + '.log')} ***")

    # -- the checkout and its code
    def check_checkout(self):
        """Refuse any directory but a detached checkout this tool created."""
        if self.checkout == self.root.resolve():
            raise Refused(f"{self.checkout} is the clone's main tree; the runner needs its own checkout")
        probe = self.snapshots / ("0" * 10)
        if len(str(probe)) > len(str(self.checkout)):
            raise Refused(f"snapshot path {probe} is longer than the checkout {self.checkout}: link_cycle would "
                          "fail TUs near MAX_PATH there; pass a shorter --snapshot-dir")
        if not self.checkout.exists():
            return False
        if not (self.checkout / "build" / MARK).is_file():
            raise Refused(f"{self.checkout} exists and carries no build/{MARK}: not a checkout this tool "
                          "created; refusing to reset it")
        if git(self.checkout, "symbolic-ref", "-q", "HEAD").returncode == 0:
            raise Refused(f"{self.checkout} has a branch checked out; the runner's checkout is always detached")
        return True

    def load_approval(self):
        self.approved = read_json(self.approval_file)
        if not isinstance(self.approved, dict) or not self.approved.get("tools_tree"):
            self.unapproved(f"no approval at {self.work / 'approved.json'}")
        own = sha256_bytes(self.runner.read_bytes())
        if own != self.approved.get("runner_sha256"):
            self.unapproved(f"this runner ({self.runner}) is not the approved one (sha256 {own[:16]}); "
                            f"schedule {self.work / 'runner' / 'nightly_measure.py'}")

    def unapproved(self, why):
        commit = self.commit or "origin/master"
        base = (self.approved or {}).get("commit")
        review = (f"git diff {base} {commit} -- {' '.join(CODE_PATHS)} {SUBMODULE}" if base else
                  f"git show --stat {commit}")
        self.record("approval", "failed", f"{why}. A maintainer reviews: `{review}`, then approves: "
                                          f"`py -3 tools/nightly_measure.py --approve {commit}`")
        raise Unapproved("approval")

    def approved_hooks(self):
        """Materialize the approved tree from Git blobs, never from the checkout."""
        dest = self.work / "hooks" / self.approved["githooks_tree"]
        if dest.resolve().is_relative_to(self.checkout):
            self.unapproved("hook directory must be outside the measured checkout")
        tree = git(self.checkout, "ls-tree", "-rz", self.approved["githooks_tree"], binary=True)
        if tree.returncode:
            self.unapproved("cannot read the approved hook tree")
        entries = []
        for item in tree.stdout.split(b"\0"):
            if not item:
                continue
            head, name = item.split(b"\t", 1)
            mode, kind, oid = head.decode("ascii").split()
            rel = Path(name.decode("utf-8", errors="surrogateescape"))
            if kind != "blob" or rel.is_absolute() or ".." in rel.parts:
                self.unapproved("unsafe entry in approved hook tree")
            entries.append((mode, oid, rel))
        if not dest.exists():
            dest.mkdir(parents=True)
            for mode, oid, rel in entries:
                data = git(self.checkout, "cat-file", "blob", oid, binary=True)
                if data.returncode or blob_id(data.stdout, oid) != oid:
                    self.unapproved(f"invalid approved hook {rel}")
                path = dest / rel
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(data.stdout)
                path.chmod(0o555 if mode == "100755" else 0o444)
        actual = {p.relative_to(dest) for p in dest.rglob("*") if p.is_file()}
        if actual != {rel for _, _, rel in entries} or any(
                blob_id((dest / rel).read_bytes(), oid) != oid for _, oid, rel in entries):
            self.unapproved("runner-owned hook copy differs from the approved tree")
        self.hooks = dest

    def prove_sources(self):
        problems = directive_problems(self.checkout, source_files(self.checkout))
        problems += region_problems(self.checkout)
        if problems:
            self.unapproved("source compiler directive refused: " + "; ".join(problems[:SOURCE_ERRORS]))

    def prove_rebase_sources(self, target):
        """The current sources were just scanned. Inspect every changed source in the
        exact rebase target before post-checkout/post-rewrite hooks can compile it.
        The runner's only local commit changes HISTORY_CSV, so these are all the
        source changes the rebase can introduce."""
        diff = git(self.checkout, "diff", "--name-only", "--diff-filter=ACMRT", "-z", "HEAD", target, binary=True)
        if diff.returncode:
            self.unapproved("cannot inspect rebase source changes")
        changed = {p.decode("utf-8") for p in diff.stdout.split(b"\0") if p}
        paths = set(compiled_sources(self.checkout, changed)) & changed
        if "reverse/functions.csv" in changed:
            ledger = git_out(self.checkout, "show", f"{target}:reverse/functions.csv")
            paths |= {row.get("source", "") for row in csv.DictReader(io.StringIO(ledger))} - ledger_sources(self.checkout)
        problems = []
        for rel in sorted(paths - {""}):
            if rel.lower().endswith(".lib"):
                continue
            blob = git(self.checkout, "show", f"{target}:{rel}", binary=True)
            if blob.returncode:
                problems.append(f"{rel}: source unavailable in rebase target")
            else:
                problems += directive_text_problems(rel, blob.stdout.decode("utf-8-sig", errors="replace"))
        region = "reverse/retail_inventory/flag_regions.csv"
        if region in changed:
            data = git_out(self.checkout, "show", f"{target}:{region}")
            if any("-" + str(row.get("opt")) not in CL_FLAGS for row in csv.DictReader(io.StringIO(data))):
                problems.append("rebase target has an unapproved region opt")
        if problems:
            self.unapproved("source compiler directive refused in rebase target: " + "; ".join(problems[:SOURCE_ERRORS]))

    def prove_code(self, when):
        """The checkout's code is the approved code: HEAD's identity, and the files on disk are
        HEAD's (untracked and ignored ones under tools/ and .githooks/ removed first)."""
        git_out(self.checkout, "clean", "-q", "-f", "-d", "-x", "--", *CODE_PATHS)
        head = git_out(self.checkout, "rev-parse", "HEAD")
        diffs = approval_diff(self.approved, identity(self.checkout, head))
        if diffs:
            self.unapproved(f"{when}: {head} differs from the approved {self.approved.get('commit')} in "
                            f"{', '.join(diffs)}")
        dirty = git_out(self.checkout, "status", "--porcelain", "--untracked-files=all", "--", *CODE_PATHS, SUBMODULE)
        if dirty:
            self.unapproved(f"{when}: the checkout's code differs from {head}: {dirty[:300]}")

    def prepare(self):
        self.load_approval()
        self.hooks = Path(tempfile.mkdtemp(prefix="empty-hooks-", dir=self.work))
        self.gh_dir = Path(tempfile.mkdtemp(prefix="empty-gh-", dir=self.work))
        if not self.check_checkout():
            # --no-checkout: no file (and no hook) of an unapproved commit appears before the approval check
            self.step("worktree", ["git", "worktree", "add", "--no-checkout", "--detach", self.checkout,
                                   "origin/master"], cwd=self.root)
            (self.checkout / "build").mkdir(parents=True, exist_ok=True)
            (self.checkout / "build" / MARK).write_text(
                f"created by tools/nightly_measure.py at {utc()}; every run resets this checkout\n", encoding="utf-8")
        self.step("fetch", ["git", "fetch", "--quiet", "origin", "master"])
        self.commit = git_out(self.checkout, "rev-parse", "--verify", "origin/master^{commit}")
        self.summary["commit"] = self.commit
        self.save()
        diffs = approval_diff(self.approved, identity(self.checkout, self.commit))
        if diffs:   # before the checkout: no hook or tool of the new commit runs
            self.unapproved(f"origin/master {self.commit} differs from the approved {self.approved.get('commit')} "
                            f"in {', '.join(diffs)}")
        self.step("checkout", ["git", "checkout", "--quiet", "--force", "--detach", self.commit])
        self.step("submodule", ["git", "submodule", "update", "--quiet", "--init", "--force", SUBMODULE])
        self.prove_code("after the checkout")
        self.prove_sources()
        dirty = git_out(self.checkout, "status", "--porcelain", "--untracked-files=no")
        if dirty:
            self.fail("clean", f"the checkout is dirty after the reset: {dirty[:300]}")
        if git_out(self.checkout, "rev-parse", "HEAD") != self.commit:
            self.fail("clean", "HEAD is not the fetched commit")
        self.record("clean", "ok", f"at {self.commit}, code approved ({self.approved.get('commit', '')[:12]})")
        self.approved_hooks()

    # -- snapshots
    def snapshot(self):
        return self.snapshots / self.commit[:10]

    def cycle_dir(self):
        return self.snapshot() / "build" / "link_cycle"

    def claim_snapshot(self):
        """Before the export: link_cycle deletes an existing destination without SNAPSHOT_MARK,
        so an existing one must be registered here and marked; then lease it (or the path a
        new one takes) before link_cycle creates or reuses it."""
        dest = self.snapshot()
        existed = dest.exists()
        if existed:
            if str(dest) not in (read_json(self.registry, {}) or {}):
                raise Refused(f"{dest} exists and is not in {self.registry}: not a snapshot this runner leased; "
                              "link_cycle could delete it. Move it away or pass another --snapshot-dir")
            if not (dest / SNAPSHOT_MARK).is_file():
                raise Refused(f"{dest} has no {SNAPSHOT_MARK} (an unfinished export): link_cycle would delete it; "
                              "remove it by hand once nothing needs it")
        self.lease()

    def lease(self):
        """Lease this run's snapshot: an existing one keeps its registration (adopted ones are never
        pruned); a new one is registered as this run's creation (prunable later)."""
        reg = read_json(self.registry, {}) or {}
        key = str(self.snapshot())
        entry = reg[key] if key in reg else {"commit": self.commit, "created_by": str(self.dir),
                                             "registered": time.time()}
        entry.update(lease_until=time.time() + LEASE, released=False, run=str(self.dir))
        reg[key] = entry
        write_json(self.registry, reg)

    def release(self):
        reg = read_json(self.registry, {}) or {}
        if self.commit and str(self.snapshot()) in reg:
            reg[str(self.snapshot())]["released"] = True
            write_json(self.registry, reg)

    def prune_snapshots(self):
        """Keep the newest --keep-snapshots snapshots this runner created (this run's always);
        never one it adopted, one under a live lease or one without link_cycle's marker."""
        keep = self.args.keep_snapshots
        reg = read_json(self.registry, {}) or {}
        if not keep or not reg:
            return
        now, current = time.time(), str(self.snapshot()) if self.commit else None
        for key in [k for k in reg if not Path(k).exists()]:
            del reg[key]
        others = sorted((k for k, e in reg.items() if e.get("created_by") and k != current),
                        key=lambda k: reg[k]["registered"], reverse=True)
        gone = []
        for key in others[max(0, keep - (1 if current in reg else 0)):]:
            e = reg[key]
            if not (e.get("released") or e.get("lease_until", 0) < now):
                continue
            if not (Path(key) / SNAPSHOT_MARK).is_file() or Path(key).parent != self.snapshots:
                continue
            shutil.rmtree(key)
            del reg[key]
            gone.append(Path(key).name)
        write_json(self.registry, reg)
        if gone:
            self.record("prune", "ok", f"removed {len(gone)} older snapshot(s) this runner created: {', '.join(gone)}")

    # -- blocking steps
    def check_receipt(self, started):
        path = self.cycle_dir() / "receipt.json"
        try:
            receipt = json.loads(path.read_text(encoding="utf-8"))
            fresh = path.stat().st_mtime >= started - 1
        except (OSError, ValueError) as e:
            self.fail("receipt", f"no readable receipt at {path}: {e}")
        why = ("written before this run" if not fresh else
               f"measured {receipt.get('commit')}, not {self.commit}" if receipt.get("commit") != self.commit else
               "not authoritative" if receipt.get("authoritative") is not True else "")
        if why:
            self.fail("receipt", f"{path}: {why}")
        self.record("receipt", "ok", f"{path}: authoritative, core {str(receipt.get('core_sha256'))[:16]}")

    def cycle(self):
        self.claim_snapshot()
        started = time.time()
        self.step("cycle", self.tool("tools/link_cycle.py", "--snapshot", self.commit, "--snapshot-dir",
                                     self.snapshots, "--build", "--reuse-quarantine", "--reuse-stubs"))
        self.check_receipt(started)

    def previous_bundle(self, repo):
        """--previous DIR or --first for the bundle: the store's newest trusted measurement."""
        rec = self.step("previous", self.tool("tools/cycle_artifacts.py", "fetch", "--latest", "--store", self.store,
                                              *repo),
                        accept=lambda rc: ("ok", "") if rc == 0 else
                        ("ok", "no trusted bundle published yet: --first") if rc == EMPTY_STORE
                        else ("failed", f"exit {rc}"))
        if rec["exit"] == EMPTY_STORE:
            return ["--first"]
        latest = (read_json(self.store / "current.json") or {}).get("latest_measurement")
        if latest is None and not (self.store / "current.json").is_file():
            self.fail("previous-pointer", f"fetch succeeded but {self.store}/current.json is unusable")
        return ["--previous", self.store / latest / "bundle"] if latest else ["--first"]

    def publish(self):
        run = self.cycle_dir()
        repo = ["--repo", self.args.repo] if self.args.repo else []
        self.step("validate", self.tool("tools/publish_cycle.py", "validate", run))
        self.step("closure", self.tool("tools/closure_report.py", "graph", run, "--out", run))
        previous = self.previous_bundle(repo)
        bundle = self.dir / "bundle"
        self.step("bundle", self.tool("tools/publish_cycle.py", "bundle", run, "--out", bundle,
                                      "--producer", self.args.producer, *previous))
        if self.args.no_publish:
            self.step("publish", self.tool("tools/publish_cycle.py", "publish", bundle, *repo, "--dry-run"))
            return
        self.step("publish", self.tool("tools/publish_cycle.py", "publish", bundle, *repo), github_write=True)
        self.bundle_out = True

    # -- after the bundle: never blocking it
    def install(self):
        if self.args.no_publish:
            return self.record("install", "skipped", "--no-publish")
        repo = ["--repo", self.args.repo] if self.args.repo else []
        rec = self.step("install", self.tool("tools/cycle_artifacts.py", "fetch", "--latest", "--store", self.store,
                                             *repo), blocking=False)
        if rec["status"] == "failed":
            self.late_failure("install", rec["note"])

    def skip(self, name):
        if name in self.args.skip:
            self.record(name, "skipped", "--skip")
            return True
        return False

    def boot(self):
        """The boot report path when boot measured an image, else None."""
        if self.skip("boot"):
            return None
        out = self.checkout / "build" / "boot" / self.dir.name
        out.mkdir(parents=True, exist_ok=False)   # never adopt even a very recent leftover
        report = out / f"{BOOT_TAG}.json"
        started = time.time()

        def accept(rc):
            rep = read_json(report)
            fresh = report.is_file() and report.stat().st_mtime >= started
            if not fresh or not isinstance(rep, dict):
                return "failed", f"exit {rc}; no fresh report at {report}"
            if rc == 0:
                return "ok", ""
            if rc == 1 and rep.get("link_exit") == 0:
                return "measured", f"the image linked; its check found differences (see {report})"
            return "failed", f"exit {rc}"
        rec = self.step("boot", self.tool("tools/boot_image.py", "link", "--overlay", "Code/", "--relayout",
                                          "--own-data", "--out", out, "--tag", BOOT_TAG), accept=accept, blocking=False)
        if rec["status"] == "failed":
            self.late_failure("boot", rec["note"])
            return None
        shutil.copyfile(report, self.dir / report.name)          # a copy to read; measured is the original
        return report

    def ownership(self, report):
        """True when a history row was recorded in the checkout."""
        if self.skip("ownership"):
            return False
        if report is None:
            self.record("ownership", "skipped", "no boot report (the boot step was skipped or failed)")
            return False
        if not (self.checkout / "tools" / "image_ownership.py").is_file():
            self.record("ownership", "skipped", "tools/image_ownership.py is not in this commit")
            return False
        mode = "measure" if self.args.no_publish else "record"
        rec = self.step("ownership", self.python("-c", OWNERSHIP_PROBE, self.checkout / "tools", report,
                                                 report.with_suffix(".exe"), self.dir / "image_ownership.json", mode),
                        accept=lambda rc: ("ok", "measured, not recorded (--no-publish)" if mode == "measure" else "")
                        if rc == 0 else ("failed", "the receipt is NOT VERIFIED") if rc == NOT_VERIFIED
                        else ("failed", "image_ownership.record refused the row") if rc == NOT_RECORDED
                        else ("failed", f"exit {rc} (image_ownership did not import or measure() crashed)"),
                        blocking=False)
        if rec["status"] == "failed":
            self.late_failure("ownership", rec["note"])
            return False
        return mode == "record"

    def history(self):
        """Commit the history row and push it to master under the cooldown, through the hooks."""
        if not git_out(self.checkout, "status", "--porcelain", "--", HISTORY_CSV):
            self.record("history", "skipped", f"record() left {HISTORY_CSV} unchanged")
            return
        shutil.copyfile(self.checkout / HISTORY_CSV, self.dir / "image_ownership_history.csv")   # the row, kept
        self.approved_hooks()
        self.prove_code("before the history commit")   # its hooks run with the credentials in reach
        for name, argv in (("history-add", ["git", "add", "--", HISTORY_CSV]),
                           ("history-commit", ["git", "commit", "-q", "-m",
                                               f"image_ownership: nightly measurement at {self.commit[:12]}",
                                               "-m", f"Measured by tools/nightly_measure.py on {socket.gethostname()}; "
                                                     f"run {self.dir.name}."])):
            if self.step(name, argv, blocking=False)["status"] == "failed":
                return self.late_failure(name)
        for n in range(1, PUSH_TRIES + 1):
            if self.step(f"history-fetch-{n}", ["git", "fetch", "--quiet", "origin", "master"],
                         blocking=False)["status"] == "failed":
                continue
            # the rebase checks out the target's tree and runs its hooks: approved code only. The ref
            # is resolved once and that exact commit approved and rebased onto (a fetch elsewhere may
            # move origin/master between the check and the rebase)
            target = git_out(self.checkout, "rev-parse", "--verify", "origin/master^{commit}")
            diffs = approval_diff(self.approved, identity(self.checkout, target))
            if diffs:
                self.record("approval", "failed", f"origin/master {target} differs from the approved code in "
                                                  f"{', '.join(diffs)}")
                return self.late_failure("history", "origin/master's code changed since the approval; the row was "
                                                    "not rebased or pushed (kept in the run directory)")
            if self.step(f"history-rebase-{n}", ["git", "rebase", "--quiet", target],
                         blocking=False)["status"] == "failed":
                self.step("history-abort", ["git", "rebase", "--abort"], blocking=False)
                return self.late_failure(f"history-rebase-{n}", "the row did not rebase onto origin/master")
            try:   # the push runs the rebased tree's hooks with the credentials: they must be approved
                if self.step(f"history-push-{n}", ["git", "push", "--quiet", "origin", "HEAD:master"],
                             github_write=True, blocking=False)["status"] == "ok":
                    return
            except Unapproved:
                return self.late_failure("approval", "origin/master's code changed since the approval; the row "
                                                     "was not pushed (kept in the run directory)")
        self.late_failure("history", f"the push lost {PUSH_TRIES} races")

    def measure(self):
        self.prove_sources()
        if not self.skip("gate"):
            self.step("gate", self.tool("tools/build.py"))
        self.cycle()
        self.publish()
        stage = "install"   # from here a failure, raised or returned, degrades the run (exit 4), never 1
        try:
            self.install()
            stage = "boot"
            report = self.boot()
            stage = "ownership"
            if self.ownership(report):
                stage = "history"
                self.history()
        except (StepFailed, OSError) as e:
            self.late_failure(stage, f"{type(e).__name__}: {e}")

    def go(self):
        self.open_run_dir()
        code = EXIT_FAILED
        try:
            self.prepare()
            self.measure()
            late = self.summary["failures_after_bundle"]
            self.summary["status"], code = ("degraded", EXIT_DEGRADED) if late else ("ok", EXIT_OK)
        except Unapproved:
            if self.bundle_out:
                self.summary["status"], code = "degraded", EXIT_DEGRADED
                self.summary["failures_after_bundle"].append("approval")
            else:
                self.summary["status"], code = "unapproved", EXIT_UNAPPROVED
        except (StepFailed, OSError) as e:
            if self.bundle_out:
                self.summary["status"], code = "degraded", EXIT_DEGRADED
                self.summary["failures_after_bundle"].append("post-publish")
                self.say(f"nightly_measure: *** post-publish FAILED: {e} ***")
            else:
                self.summary.update(status="failed", failed_step=str(e))
        except Refused as e:
            self.summary.update(status="refused", refused=str(e))
            raise
        except BaseException:
            self.summary["status"] = "interrupted"
            raise
        finally:
            for stage, action in (("release", self.release), ("prune", self.prune_snapshots),
                                  ("save", self.save)):
                try:
                    if stage == "release" and not self.commit:
                        continue
                    if stage == "prune" and self.summary["status"] not in ("ok", "degraded", "failed"):
                        continue
                    if stage == "save":
                        self.summary["ended_utc"] = utc()
                    action()
                except (StepFailed, OSError) as e:
                    if self.bundle_out:
                        self.summary["status"], code = "degraded", EXIT_DEGRADED
                        self.summary["failures_after_bundle"].append(stage)
                        self.say(f"nightly_measure: {stage} failed after bundle: {e}")
                    else:
                        self.summary["status"], code = "failed", EXIT_FAILED
                        self.say(f"nightly_measure: {stage} failed: {e}")
            if self.summary["status"] == "degraded":
                code = EXIT_DEGRADED
        late = self.summary["failures_after_bundle"]
        self.say(f"nightly_measure: {self.summary['status'].upper()} at {self.commit}"
                 + (f"; FAILED after the bundle: {', '.join(late)}" if late else "") + f"; {self.dir / 'run.json'}")
        return code


def plain_path(path, *, allow_hardlinks=False):
    """Reject reparse points (including junctions), symlinks and hardlinked files."""
    p = Path(path)
    for part in (p, *p.parents):
        st = part.lstat()
        if stat.S_ISLNK(st.st_mode) or getattr(st, "st_file_attributes", 0) & 0x400:
            raise Refused(f"reparse/symlink path: {part}")
    if not allow_hardlinks and p.is_file() and p.stat().st_nlink != 1:
        raise Refused(f"hardlinked file: {p}")
    return p


def safe_relative(name):
    # Windows drive/ADS, device names, alternate separators and trailing dots
    # must be refused even when tests run on another platform.
    parts = str(name).split("/")
    if not parts or any(not p or p in (".", "..") or p[-1:] in (".", " ")
                        or re.search(r'[\\:\x00-\x1f<>"|?*]', p)
                        or re.fullmatch(r"(?i)(con|prn|aux|nul|com[1-9]|lpt[1-9])(\..*)?", p) for p in parts):
        raise Refused(f"unsafe handoff/bundle path: {name!r}")
    return Path(*parts)


def tree_hashes(root):
    hashes = {}
    plain_path(root)
    for p in sorted(Path(root).rglob("*")):
        plain_path(p)
        if p.is_file():
            hashes[p.relative_to(root).as_posix()] = sha256_bytes(p.read_bytes())
        elif not p.is_dir():
            raise Refused(f"non-regular artifact: {p}")
    return hashes


def copy_data_tree(source, dest, *, omit_tools=False, flatten_hardlinks=False):
    """Copy bytes, never links or Git metadata. The destination is publisher-private."""
    plain_path(source)
    Path(dest).mkdir(parents=True, exist_ok=False)
    for p in sorted(Path(source).rglob("*")):
        rel = p.relative_to(source)
        if any(part.lower() == ".git" for part in rel.parts) or (omit_tools and rel.parts[0].lower() == "tools"):
            continue
        plain_path(p, allow_hardlinks=flatten_hardlinks)
        q = Path(dest) / safe_relative(rel.as_posix())
        if p.is_dir():
            q.mkdir(exist_ok=True)
        elif p.is_file():
            q.parent.mkdir(parents=True, exist_ok=True)
            q.write_bytes(p.read_bytes())
        else:
            raise Refused(f"not a regular artifact: {p}")


def install_checkers(root, commit, dest):
    """Pin the complete approved tools tree, including every importable dependency.

    This is called only by the explicit maintainer approval/install operation.
    Never import the tree to discover its contents.
    """
    if Path(dest).exists():
        shutil.rmtree(dest)
    Path(dest).mkdir(parents=True)
    listing = git(root, "ls-tree", "-rz", f"{commit}:tools", binary=True)
    if listing.returncode:
        raise Refused("cannot read approved checker tree")
    for entry in listing.stdout.split(b"\0"):
        if not entry:
            continue
        head, name = entry.split(b"\t", 1)
        mode, kind, oid = head.decode("ascii").split()
        if kind != "blob" or mode not in ("100644", "100755"):
            raise Refused("checker bundle cannot contain links or submodules")
        rel = safe_relative(name.decode("utf-8"))
        data = git(root, "cat-file", "blob", oid, binary=True)
        if data.returncode or blob_id(data.stdout, oid) != oid:
            raise Refused(f"invalid approved checker blob: {rel}")
        q = Path(dest) / rel
        q.parent.mkdir(parents=True, exist_ok=True)
        q.write_bytes(data.stdout)
    return tree_hashes(dest)


def current_sid():
    """Use the OS token, never USERNAME or an environment-controlled profile."""
    if os.name != "nt":
        raise Refused("split-account roles require Windows")
    import ctypes
    from ctypes import wintypes
    token, size = wintypes.HANDLE(), wintypes.DWORD()
    adv = ctypes.WinDLL("advapi32", use_last_error=True)
    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    adv.OpenProcessToken.argtypes = [wintypes.HANDLE, wintypes.DWORD, ctypes.POINTER(wintypes.HANDLE)]
    kernel.GetCurrentProcess.restype = wintypes.HANDLE
    adv.GetTokenInformation.argtypes = [wintypes.HANDLE, ctypes.c_int, ctypes.c_void_p,
                                        wintypes.DWORD, ctypes.POINTER(wintypes.DWORD)]
    adv.ConvertSidToStringSidW.argtypes = [ctypes.c_void_p, ctypes.POINTER(wintypes.LPWSTR)]
    kernel.CloseHandle.argtypes = [wintypes.HANDLE]
    kernel.LocalFree.argtypes = [ctypes.c_void_p]
    if not adv.OpenProcessToken(kernel.GetCurrentProcess(), 8, ctypes.byref(token)):
        raise Refused("cannot query Windows account token")
    try:
        adv.GetTokenInformation(token, 1, None, 0, ctypes.byref(size))
        buf = ctypes.create_string_buffer(size.value)
        if not adv.GetTokenInformation(token, 1, buf, size, ctypes.byref(size)):
            raise Refused("cannot query Windows token user")
        sid = ctypes.cast(buf, ctypes.POINTER(ctypes.c_void_p))[0]
        text = wintypes.LPWSTR()
        if not adv.ConvertSidToStringSidW(sid, ctypes.byref(text)):
            raise Refused("cannot read Windows account SID")
        try:
            return text.value
        finally:
            kernel.LocalFree(ctypes.cast(text, ctypes.c_void_p))
    finally:
        kernel.CloseHandle(token)


def readable(path):
    """Probe access, not attributes. Absence is not evidence of an access denial."""
    try:
        p = Path(path)
        if p.is_dir():
            with os.scandir(p) as entries:
                next(entries, None)
        else:
            with p.open("rb"):
                pass
        return True
    except PermissionError:
        return False
    except OSError as e:
        raise Refused(f"credential isolation probe inconclusive at {path}: {e}") from e


def writable(path):
    try:
        with Path(path).open("r+b"):
            pass
        return True
    except PermissionError:
        return False


def directory_writable(path):
    try:
        fd, name = tempfile.mkstemp(prefix="isolation-probe-", dir=path)
    except PermissionError:
        return False
    os.close(fd)
    Path(name).unlink()
    return True


def reject_build_inputs(checkout, target=None):
    """Before the first compile: no committed, local or ignored build input.

    The marker alone is runner-owned. Reuse of an old build directory is refused;
    the maintainer removes a completed builder checkout before the next run.
    """
    if target:
        result = git(checkout, "ls-tree", "-r", "--name-only", target)
        if result.returncode or any(p.lower().startswith("build/") for p in result.stdout.splitlines()):
            raise Refused("tracked path under build/ in target checkout")
    build = Path(checkout) / "build"
    if build.exists():
        plain_path(build)
        for p in build.iterdir():
            if p.name != MARK:
                raise Refused(f"pre-existing tracked or untracked path under build/: {p}")
            plain_path(p)


def clang_cache(checkout):
    """Repair the profile cache from the approved, hash-pinned zip, without imports."""
    root = Path(checkout)
    constants = {}
    for node in ast.parse((root / "tools/compiler_profiles.py").read_text(encoding="utf-8")).body:
        if isinstance(node, ast.Assign):
            for target in node.targets:
                if isinstance(target, ast.Name) and target.id in ("CLANG23_FILES", "CLANG23_ARCHIVE_SHA256"):
                    constants[target.id] = ast.literal_eval(node.value)
    files, archive_sha = constants["CLANG23_FILES"], constants["CLANG23_ARCHIVE_SHA256"]
    archive = root / "vendor/clang23-x86/compiler.zip"
    if not archive.is_file():
        return   # a checkout not using this optional profile; select() will refuse it
    if sha256_bytes(plain_path(archive).read_bytes()) != archive_sha:
        raise Refused("clang archive hash mismatch")
    dest = root / "build/compiler_profiles/clang23-x86" / archive_sha
    dest.parent.mkdir(parents=True, exist_ok=True)
    plain_path(dest.parent)
    if dest.exists():
        plain_path(dest)
        actual = tree_hashes(dest)
        if actual == files and {p.name for p in dest.iterdir()} == set(files):
            return
        shutil.rmtree(dest)
    with zipfile.ZipFile(archive) as z:
        if len(z.namelist()) != len(files) or set(z.namelist()) != {"bin/" + name for name in files}:
            raise Refused("clang archive has unexpected members")
        dest.mkdir()
        for name, digest in files.items():
            data = z.read("bin/" + name)
            if sha256_bytes(data) != digest:
                raise Refused(f"clang archive member hash mismatch: {name}")
            (dest / safe_relative(name)).write_bytes(data)
    if tree_hashes(dest) != files:
        raise Refused("clang cache differs after extraction")


class SplitRun(Run):
    """Shared plumbing; all state and installation paths are explicit and disjoint."""
    def __init__(self, args, root, out=print):
        super().__init__(args, root, out)
        self.install_dir = Path(args.install_dir).absolute()
        self.work = Path(args.state_dir).absolute()
        self.handoff = Path(args.handoff_dir).absolute()
        self.approval_file = self.install_dir / "approved.json"
        self.registry = self.work / "snapshots.json"
        self.clock = Path(args.push_clock or self.work / "push_clock.json")
        self.hooks, self.gh_dir = self.work / "empty-hooks", self.work / "empty-gh"
        self.summary["role"] = args.role

    def preflight(self):
        global TRUSTED_CWD
        policy = read_json(self.install_dir / "security.json")
        if not isinstance(policy, dict):
            raise Refused("missing protected security.json; follow docs/nightly_setup.md")
        builder, publisher = policy.get("builder_sid"), policy.get("publisher_sid")
        if not builder or not publisher or builder == publisher or current_sid() != policy.get(self.args.role + "_sid"):
            raise Refused("role must run under its distinct configured Windows account")
        self.policy = policy
        if self.work.resolve() != Path(policy[self.args.role + "_state"]).resolve():
            raise Refused("role state directory is not the protected configured directory")
        for secret in (policy["signing_key"], policy["allowed_signers"]):
            if any(Path(secret).resolve().is_relative_to(p.resolve()) for p in (
                    self.root, self.handoff, Path(policy["builder_state"]))):
                raise Refused("publisher key and signer pin must be outside builder-writable trees")
        executables = policy.get("executables") or {}
        if set(executables) != {"git", "gh", "ssh-keygen"} or any(
                not Path(p).is_absolute() for p in executables.values()):
            raise Refused("security.json must pin absolute git, gh and ssh-keygen executable paths")
        if Path(policy.get("python", "")).resolve() != Path(sys.executable).resolve():
            raise Refused("use the configured publisher-protected Python installation")
        TRUSTED_COMMANDS.update(executables)
        roots = [self.install_dir, self.work, self.handoff, self.root.absolute()]
        if any(a.resolve().is_relative_to(b.resolve()) or b.resolve().is_relative_to(a.resolve())
               for i, a in enumerate(roots) for b in roots[i + 1:]):
            raise Refused("install, state, handoff and builder repository must be disjoint")
        for path in (self.install_dir, self.work, self.handoff):
            plain_path(path)
        if self.args.role == "builder":
            profile = Path(policy["publisher_profile"])
            # Directories are mandatory even on a publisher that does not use SSH/gh.
            locations = [profile / ".ssh", profile / "AppData/Roaming/GitHub CLI",
                         profile / "AppData/Local/Microsoft/Credentials",
                         profile / "AppData/Roaming/Microsoft/Credentials",
                         profile / ".git-credentials", Path(policy["signing_key"]),
                         Path(policy["publisher_state"]), *map(Path, policy.get("credential_locations", []))]
            if any(readable(p) for p in locations):
                raise Refused("builder can read publisher credential locations")
            protected = [self.approval_file, self.runner, self.install_dir / "security.json", Path(sys.executable),
                         *map(Path, executables.values())]
            protected += list((self.install_dir / "checkers").rglob("*"))
            if any(writable(p) for p in protected if p.is_file()) or any(
                    directory_writable(p) for p in [self.install_dir, self.install_dir.parent,
                                                  self.install_dir / "runner", self.install_dir / "checkers",
                                                  *[q for q in (self.install_dir / "checkers").rglob("*") if q.is_dir()]]):
                raise Refused("builder can rewrite the protected approval/runner/checker installation")
        self.load_approval()
        self.verify_bundle()
        if self.args.role == "publisher":
            TRUSTED_CWD = self.work / "native-cwd"
            TRUSTED_CWD.mkdir(exist_ok=True)

    def verify_bundle(self):
        expected = self.approved.get("checker_files")
        if not expected or "image_ownership.py" not in expected:
            raise Refused("missing tools/image_ownership.py: this runner must land after the north-star commit "
                          "from agent-a0b594d3646db42ad's committed branch; approve that commit or a descendant")
        required = {"image_ownership.py", "publish_cycle.py", "closure_report.py", "cycle_artifacts.py", "link_cycle.py",
                    "data_back_rank.py"}
        if not expected or not required.issubset(expected) or tree_hashes(self.install_dir / "checkers") != expected:
            raise Refused("installed checker bundle is missing or differs from its approval")
        if self.runner.absolute() != self.install_dir / "runner/nightly_measure.py":
            raise Refused("schedule the installed runner, never a checkout copy")


class BuilderRun(SplitRun):
    def env(self, credentialed=False, git_config=()):
        if credentialed:
            raise Refused("builder cannot request credentials")
        result = super().env(False, git_config)
        result.pop("BFME_OWNERSHIP_SIGNING_KEY", None)
        result["BUILD_POOL"] = "2"
        result["BFME_OBJSTORE"] = "off"
        return result

    def step(self, name, argv, **kw):
        if kw.get("github_write") or name.startswith("history-") or name in ("publish", "previous", "install"):
            raise Refused("builder cannot publish, sign or run credentialed history operations")
        if name in ("gate", "cycle", "boot"):
            clang_cache(self.checkout)
        if name == "cycle" and self.snapshot().exists():
            clang_cache(self.snapshot())
        return super().step(name, argv, **kw)

    def prepare(self):
        self.preflight()
        # Fresh dedicated checkout each run; never adopt planted ignored build inputs.
        reject_build_inputs(self.checkout)
        super().prepare()
        reject_build_inputs(self.checkout, self.commit)

    def ownership(self, report):
        # The builder measures but can never ask image_ownership.record() to sign.
        old = self.args.no_publish
        self.args.no_publish = True
        try:
            return super().ownership(report)
        finally:
            self.args.no_publish = old

    def measure(self):
        if self.args.skip:
            raise Refused("builder handoffs require gate, boot and ownership; --skip is diagnostic only")
        self.prove_sources()
        self.step("gate", self.tool("tools/build.py"))
        self.cycle()
        run = self.cycle_dir()
        self.step("validate", self.tool("tools/publish_cycle.py", "validate", run))
        self.step("closure", self.tool("tools/closure_report.py", "graph", run, "--out", run))
        self.step("bundle", self.tool("tools/publish_cycle.py", "bundle", run, "--out", self.dir / "bundle",
                                      "--producer", self.args.producer, "--first"))
        report = self.boot()
        self.ownership(report)
        if report is None or self.summary["failures_after_bundle"]:
            raise StepFailed("builder ownership did not verify; no handoff")
        self.export_handoff(report)
        # Only this dedicated, marked checkout's generated build state. Keep
        # failed runs for diagnosis; a leftover on the next run is refused.
        build_dir = plain_path(self.checkout / "build")
        for p in build_dir.rglob("*"):
            plain_path(p, allow_hardlinks=True)
        shutil.rmtree(build_dir)
        build_dir.mkdir()
        (build_dir / MARK).write_text("nightly builder checkout\n", encoding="utf-8")

    def export_handoff(self, report):
        dest = self.handoff / self.dir.name
        dest.mkdir()
        copy_data_tree(self.checkout, dest / "workspace", flatten_hardlinks=True)
        copy_data_tree(self.snapshot(), dest / "snapshot", flatten_hardlinks=True)
        copy_data_tree(self.dir / "bundle", dest / "bundle")
        meta = {"schema": 1, "commit": self.commit, "created": time.time(),
                "report": Path(report).relative_to(self.checkout).as_posix(),
                "files": tree_hashes(dest)}
        write_json(dest / "handoff.json", meta)
        # A partial run cannot replace the last complete handoff.
        write_json(self.handoff / "latest.json", {"id": dest.name,
                   "sha256": sha256_bytes((dest / "handoff.json").read_bytes())})
        self.record("handoff", "ok", str(dest))


PUBLISHER_CHECKS = """import sys, json
sys.path.insert(0, sys.argv[1])
import publish_cycle as pc, cycle_artifacts as ca, closure_report as cr
from pathlib import Path
workspace, snap, bundle = map(Path, sys.argv[2:5])
facts = pc.validate_run(snap / 'build/link_cycle', root=workspace)
if not facts['core_check'].startswith('recomputed with link_cycle '):
    raise SystemExit('receipt core could not be recomputed with the pinned bundle')
manifest = ca.validate(bundle, root=workspace)
if manifest['commit'] != sys.argv[5] or facts['commit'] != sys.argv[5]:
    raise SystemExit('handoff commit differs from artifacts')
if not (manifest.get('components', {}).get('closure_report') or {}).get('included'):
    raise SystemExit('bundle has no bound closure report')
fr = ca.freshness(facts['receipt'], root=workspace)
if ca.refusal(fr):
    raise SystemExit('receipt freshness/ancestry refused: ' + str(ca.refusal(fr)))
# Recompute graph-derived closure, never replay snapshot code.
cr.from_graph(snap / 'build/link_cycle')
"""


def publisher_process_guard():
    """Pinned checkers may spawn only trusted Git, gh and SSH signing commands.

    All native children start in a private empty cwd; Git gets explicit -C.
    Thus a planted git.exe or version.dll beside artifacts is never searched.
    No compile/link/game executable or secondary checkout Python is admitted.
    """
    import json, os, subprocess
    from pathlib import Path
    commands = json.loads(os.environ["NM_PUBLISHER_EXECUTABLES"])
    safe_cwd = os.environ["NM_PUBLISHER_SAFE_CWD"]
    original = subprocess.Popen

    def guarded(argv, *a, **kw):
        if a or isinstance(argv, (str, bytes)) or kw.get("shell") or kw.get("executable"):
            raise RuntimeError("publisher refused an indirect command")
        argv = list(map(str, argv))
        name = next((name for name, path in commands.items() if argv[0] in (name, path)), None)
        if name is None:
            raise RuntimeError("publisher refused executable: " + argv[0])
        cwd = kw.pop("cwd", None)
        argv[0] = commands[name]
        if name == "git":
            argv[1:1] = ["-C", str(Path(cwd or safe_cwd).absolute())]
        kw["cwd"] = safe_cwd
        return original(argv, **kw)

    subprocess.Popen = guarded


PUBLISHER_GUARD = inspect.getsource(publisher_process_guard) + "\npublisher_process_guard()\n"

BUILDER_ATTESTATION = ("Link, image and ownership figures are builder-attested. The publisher checks commit-bound "
                       "inputs, artifact integrity, receipt core and closure, and recomputes data_back_rank; "
                       "it does not independently re-link or reproduce these figures.")

# Keep the pinned publisher's normal immutable-release workflow, while qualifying
# its human-facing notes. No installed checker is edited or replaced.
PUBLISHER_PUBLISH = ("import sys\nsys.path.insert(0, sys.argv[1])\nimport publish_cycle as pc\n"
                     "notes = pc.release_notes\n"
                     "pc.release_notes = lambda manifest: " + repr(BUILDER_ATTESTATION + "\n\n") + " + notes(manifest)\n"
                     "sys.exit(pc.main(sys.argv[2:]))\n")


PUBLISHER_OWNERSHIP = """import sys, json
sys.path.insert(0, sys.argv[1])
import image_ownership as own
from pathlib import Path
report, out, history, key, signers, mode = sys.argv[2:]
# history_row's signed report_sha256 binds this publisher-authored statement.
# An additive report field preserves the existing history schema and signatures.
document = json.loads(Path(report).read_text(encoding='utf-8'))
document['measurement_attestation'] = {'schema': 1, 'basis': 'builder-attested',
    'statement': ATTESTATION}
Path(report).write_text(json.dumps(document, indent=1) + '\\n', encoding='utf-8')
receipt = own.measure(report, image=Path(report).with_suffix('.exe'))
if not receipt.get('verified') or not receipt['image']['bound'] or not receipt['map']['bound']:
    raise SystemExit('bound ownership measurement refused')
why = own.record_refusals(receipt)
if why:
    raise SystemExit('ownership record refused: ' + '; '.join(why))
receipt['measurement_attestation'] = document['measurement_attestation']
Path(out).write_text(json.dumps(receipt, indent=1), encoding='utf-8')
if mode == 'record':
    own.record(receipt, path=Path(history), key=key, signers=signers)
    if own.check_history(path=Path(history), signers=signers):
        raise SystemExit('ownership signature verification refused')
""".replace('ATTESTATION', repr(BUILDER_ATTESTATION))


class PublisherRun(SplitRun):
    """An allowlisted data validator/publisher. No checkout hooks or build tools."""
    def prove_code(self, when):
        self.verify_bundle()
        if hasattr(self, "staged_tools") and tree_hashes(self.staged_tools) != self.approved["checker_files"]:
            raise Refused("private checker copy changed")

    def tool(self, script, *args):
        if script not in ("tools/publish_cycle.py", "tools/cycle_artifacts.py", "tools/closure_report.py",
                          "tools/data_back_rank.py"):
            raise Refused(f"publisher cannot execute {script}")
        self.prove_code("before checker")
        if script == "tools/publish_cycle.py" and args[:1] == ("publish",):
            return self.python("-c", PUBLISHER_PUBLISH, self.staged_tools, *args)
        return self.python("-c", SCRIPT_BOOT, self.staged_tools, self.staged_tools / Path(script).name, *args)

    def env(self, credentialed=False, git_config=()):
        result = super().env(credentialed, git_config)
        result["NM_PUBLISHER_EXECUTABLES"] = json.dumps(self.policy["executables"])
        result["NM_PUBLISHER_SAFE_CWD"] = str(self.work / "native-cwd")
        return result

    def step(self, name, argv, **kw):
        # Inspect commands as well as labels. A renamed build/boot step is refused.
        if str(argv[0]) == "git":
            if argv[1] not in ("init", "fetch", "reset"):
                raise Refused("publisher Git is limited to private metadata initialization")
        else:
            allowed = (SCRIPT_BOOT, PUBLISHER_CHECKS, PUBLISHER_OWNERSHIP, PUBLISHER_PUBLISH)
            if str(argv[0]) != self.py or len(argv) < 2 or argv[1] != "-I" or "-c" not in argv or argv[argv.index("-c") + 1] not in allowed:
                raise Refused("publisher can execute only pinned data checkers")
            i = argv.index("-c")
            if Path(argv[i + 2]) != self.staged_tools:
                raise Refused("publisher cannot import checkout tools")
            if argv[i + 1] == SCRIPT_BOOT:
                script = Path(argv[i + 3])
                if script.parent != self.staged_tools or script.name not in (
                        "publish_cycle.py", "cycle_artifacts.py", "closure_report.py", "data_back_rank.py"):
                    raise Refused("publisher cannot build or boot or run a checkout tool")
        self.prove_code("before " + name)
        argv = list(argv)
        # Parent subprocesses are also launched from a clean native cwd. -C
        # preserves Git's data location; Python receives absolute checker paths.
        cwd = Path(kw.pop("cwd", self.checkout))
        if argv[0] == "git":
            argv = ["git", "-C", str(cwd), *argv[1:]]
        else:
            i = argv.index("-c") + 1
            # Python may read relative data paths. Native children still use the
            # guard's empty cwd, and -I keeps this data directory off sys.path.
            argv[i] = PUBLISHER_GUARD + "import os; os.chdir(" + repr(str(cwd)) + ")\n" + argv[i]
        return super().step(name, argv, cwd=self.work / "native-cwd", **kw)

    def bind_tree(self, repository, tree, commit, *, snapshot=False):
        """Compare tracked files to fetched Git objects, using a fresh private index.

        GIT_ATTR_SOURCE prevents builder attributes from controlling normalization.
        A separate index per comparison also defeats forged size/mtime cache hits.
        Submodules are checked separately against their own pinned commits.
        """
        index = self.dir / ("bind-snapshot.index" if snapshot else "bind-workspace.index")
        index.unlink(missing_ok=True)
        env = {"GIT_ATTR_SOURCE": commit, "GIT_INDEX_FILE": str(index)}
        args = ("--git-dir=" + str(repository / ".git"), "--work-tree=" + str(tree))
        try:
            listing = git(repository, "ls-tree", "-rz", commit, binary=True, env=env)
            if listing.returncode:
                raise Refused("cannot enumerate approved tracked paths")
            for entry in listing.stdout.split(b"\0"):
                if entry.startswith(b"160000 commit "):
                    header, name = entry.split(b"\t", 1)
                    if repository != self.checkout or name.decode() != SUBMODULE or \
                            header.split()[2].decode() != self.approved["submodule"]:
                        raise Refused("unvalidated submodule in approved tree; explicit binding support is required")
            loaded = git(repository, *args, "read-tree", commit, env=env)
            if loaded.returncode:
                raise Refused("cannot load approved tree for commit binding")
            result = git(repository, *args, "-c", "core.autocrlf=true", "status", "--porcelain=v1", "-z",
                         "--untracked-files=all", "--ignored=matching", "--ignore-submodules=all", binary=True, env=env)
            if result.returncode:
                raise Refused("cannot compare files against approved commit")
            for entry in result.stdout.split(b"\0"):
                if not entry:
                    continue
                code, name = entry[:2], entry[3:].decode("utf-8")
                if code not in (b"??", b"!!"):
                    raise Refused(f"tracked path differs from approved commit: {tree / name}")
                product = name if tree == self.snapshot_path else (tree.relative_to(self.snapshot_path) / name).as_posix() \
                    if snapshot else name
                if snapshot and not self.snapshot_product(product):
                    raise Refused(f"unexpected untracked snapshot path: {name}")
        finally:
            index.unlink(missing_ok=True)

    @staticmethod
    def snapshot_product(name):
        # --ignored=matching may name an entire ignored directory. Walk it below
        # as well, so an ignored build/ does not hide an arbitrary extra file.
        if name == SNAPSHOT_MARK or name == "build/":
            return True
        suffixes = {"match": (".obj", ".deps.json"),
                    "link_cycle": (".csv", ".json", ".gz", ".txt", ".obj", ".lib", ".def", ".rsp",
                                   ".exe", ".map", ".log", ".pdb", ".ilk", ".exp"),
                    "compiler_profiles": (".exe", ".dll"),
                    "patch": (".dat", ".exe", ".log", ".json", ".csv")}
        parts = name.split("/")
        return len(parts) >= 3 and parts[0] == "build" and parts[1] in suffixes and (
            name.endswith("/") or name.endswith(suffixes[parts[1]]))

    def bind_inputs(self):
        for tree in (self.checkout, self.snapshot_path):
            self.bind_tree(self.checkout, tree, self.commit, snapshot=tree == self.snapshot_path)
            self.bind_tree(self.checkout / SUBMODULE, tree / SUBMODULE, self.approved["submodule"],
                           snapshot=tree == self.snapshot_path)
        # Git reports ignored directories as a unit. Inventory every leaf too.
        for path in self.snapshot_path.rglob("*"):
            if path.is_file() and path.is_relative_to(self.snapshot_path / "build"):
                name = path.relative_to(self.snapshot_path).as_posix()
                if not self.snapshot_product(name):
                    raise Refused(f"unexpected untracked snapshot path: {name}")

    def private_git(self, path, url, commit, label):
        # No .git, config, hooks, attributes, templates or alternates from builder.
        empty = self.work / "empty-template"
        empty.mkdir(exist_ok=True)
        self.step(label + "-init", ["git", "init", "--quiet", "--template=" + str(empty), path], cwd=self.work)
        self.step("history-fetch-" + label, ["git", "fetch", "--quiet", "--no-recurse-submodules", url, commit], cwd=path)
        self.step(label + "-index", ["git", "reset", "--quiet", "--mixed", "FETCH_HEAD"], cwd=path)

    def prepare(self):
        self.preflight()
        (self.work / "native-cwd").mkdir(exist_ok=True)
        pointer = read_json(self.handoff / "latest.json") or {}
        ident = pointer.get("id", "")
        if not re.fullmatch(r"[0-9]{8}T[0-9]{6}Z(?:-[0-9]+)?", ident):
            raise Refused("no complete builder handoff")
        source = plain_path(self.handoff / ident)
        raw = plain_path(source / "handoff.json").read_bytes()
        if sha256_bytes(raw) != pointer.get("sha256"):
            raise Refused("handoff pointer does not bind its manifest")
        self.handoff_digest = sha256_bytes(raw)
        if self.handoff_digest in (read_json(self.work / "processed.json", []) or []):
            raise Refused("handoff has already been published")
        meta = json.loads(raw)
        self.commit = meta.get("commit", "")
        if meta.get("schema") != 1 or not re.fullmatch(r"[0-9a-f]{40}", self.commit):
            raise Refused("invalid handoff schema/commit")
        if not 0 <= time.time() - meta.get("created", 0) <= 24 * 3600:
            raise Refused("handoff is stale or future-dated")
        files = meta.get("files")
        if not isinstance(files, dict) or not files:
            raise Refused("handoff has no artifact inventory")
        stage = self.dir / "frozen"
        stage.mkdir()
        for name, digest in files.items():
            rel = safe_relative(name)
            if any(part.lower() == ".git" for part in rel.parts):
                raise Refused("handoff must not supply Git metadata")
            data = plain_path(source / rel).read_bytes()
            if sha256_bytes(data) != digest:
                raise Refused(f"handoff artifact changed: {name}")
            q = stage / rel
            q.parent.mkdir(parents=True, exist_ok=True)
            q.write_bytes(data)
        if tree_hashes(stage) != files:
            raise Refused("handoff contains colliding artifact paths")
        self.checkout, self.snapshots = stage / "workspace", stage
        self.snapshot_path = stage / "snapshot"
        self.staged_tools = self.dir / "checkers"
        shutil.copytree(self.install_dir / "checkers", self.staged_tools)
        self.prove_code("after freezing handoff")
        # The builder cannot choose the retail truth against which its image
        # is judged. Provision this baseline with the protected installation.
        retail = plain_path(self.install_dir / "retail.dat").read_bytes()
        if sha256_bytes(retail) != self.policy["retail_sha256"]:
            raise Refused("protected retail baseline differs from the maintainer pin")
        self.hooks.mkdir(exist_ok=True)
        self.gh_dir.mkdir(exist_ok=True)
        self.store = self.work / "cycle_bundles"
        # URLs are maintainer configuration, never supplied by the handoff.
        self.private_git(self.checkout, self.policy["repository_url"], self.commit, "workspace")
        self.step("history-fetch-ancestry", ["git", "fetch", "--quiet", "--no-recurse-submodules",
                  self.policy["repository_url"], "refs/heads/master:refs/remotes/origin/master"], cwd=self.checkout)
        if approval_diff(self.approved, identity(self.checkout, self.commit)):
            raise Refused("handoff commit does not have the approved code identity")
        self.private_git(self.checkout / SUBMODULE, self.policy["bfme1_url"], self.approved["submodule"], "bfme1")
        self.bind_inputs()
        target = self.checkout / "baselines/bfme2/workshop-vanilla-1.06/files/game.dat"
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(retail)
        # Validate the builder's original tracked tools first, then discard all
        # supplied executable code (including untracked files) before any import.
        if (self.checkout / "tools").exists():
            shutil.rmtree(self.checkout / "tools")
        shutil.copytree(self.staged_tools, self.checkout / "tools")
        shutil.rmtree(self.staged_tools)
        self.staged_tools = self.checkout / "tools"
        self.report = self.checkout / safe_relative(meta["report"])
        if not self.report.is_relative_to(self.checkout / "build/boot"):
            raise Refused("ownership report must be a builder boot artifact")
        # Scan source directives before strict dependency checking can select a compiler.
        self.prove_sources()
        self.check_artifact_paths()
        self.summary["commit"] = self.commit

    def check_artifact_paths(self):
        """Checker inputs may only refer to files in the private frozen workspace.

        Portable receipts have relative dependency keys. Never rewrite sidecars
        or provenance to make a non-portable build appear current.
        """
        report = read_json(self.report)
        if not isinstance(report, dict):
            raise Refused("missing ownership report")
        prov = report.get("provenance") or {}
        paths = list((prov.get("spec_files_sha256") or {}).keys())
        entries = (prov.get("objects") or {}).get("entries") or []
        for obj, _, source in entries:
            paths += [obj, source]
        for p in (self.checkout / "build").rglob("*.deps.json"):
            deps = read_json(p)
            if not isinstance(deps, dict):
                raise Refused("unreadable object dependency receipt")
            paths += list((deps.get("deps") or {}).keys())
            # /I. is a normal include root. It means this private workspace,
            # not an artifact file or a parent-directory escape.
            paths += [p for p in (deps.get("search_roots") or []) if p != "."]
            paths += list(deps.get("retry_dirs") or [])
        for name in paths:
            rel = safe_relative(str(name).replace("\\", "/"))
            if any(part.lower() == ".git" for part in rel.parts):
                raise Refused("artifact references Git metadata")
            # Missing search directories are meaningful inventory entries; the
            # checker revalidates those, but no path can escape the private copy.
            if not (self.checkout / rel).resolve().is_relative_to(self.checkout):
                raise Refused("artifact reference escapes private workspace")

    def snapshot(self):
        return self.snapshot_path

    def release(self):
        pass   # publisher never writes builder state/leases/handoff

    def prune_snapshots(self):
        pass

    def measure(self):
        snap = self.snapshot()
        bundle = self.dir / "frozen/bundle"
        self.step("handoff-validate", self.python("-c", PUBLISHER_CHECKS, self.staged_tools,
                                                 self.checkout, snap, bundle, self.commit))
        self.recompute_rank(bundle)
        # Bound artifacts are checked and the existing ownership signing path is
        # exercised entirely in publisher-private storage, with the pinned module.
        key = self.policy["signing_key"]
        signers = self.policy["allowed_signers"]
        history = self.checkout / HISTORY_CSV
        self.step("ownership-verify", self.python("-c", PUBLISHER_OWNERSHIP, self.staged_tools, self.report,
                  self.dir / "image_ownership.json", history, key, signers,
                  "measure" if self.args.no_publish else "record"))
        # Rebuild from the independently checked run and previous trusted bundle;
        # no code or cached Python from the transferred snapshot is executed.
        self.publish()
        self.install()
        if not self.args.no_publish:
            shutil.copyfile(history, self.dir / "image_ownership_history.csv")
            manifest = read_json(self.dir / "bundle/manifest.json") or {}
            tag = manifest.get("tag")
            if not isinstance(tag, str) or not re.fullmatch(r"[A-Za-z0-9_.-]+", tag):
                raise Refused("publisher bundle has no safe release tag")
            # Ownership evidence is published separately: cycle schema disallows
            # new members, and immutable cycle releases cannot accept more assets.
            self.publish_ownership(tag)
            processed = read_json(self.work / "processed.json", []) or []
            write_json(self.work / "processed.json", [*processed, self.handoff_digest])

    def publish(self):
        run = self.cycle_dir()
        repo = ["--repo", self.args.repo or self.policy["repository"]]
        self.step("validate", self.tool("tools/publish_cycle.py", "validate", run))
        self.step("closure", self.tool("tools/closure_report.py", "graph", run, "--out", run))
        previous = self.previous_bundle(repo)
        bundle = self.dir / "bundle"
        self.step("bundle", self.tool("tools/publish_cycle.py", "bundle", run, "--out", bundle,
                  "--rank", "run-dir", "--producer", self.args.producer, *previous))
        self.step("publish", self.tool("tools/publish_cycle.py", "publish", bundle, *repo,
                  *(["--dry-run"] if self.args.no_publish else [])), github_write=not self.args.no_publish)
        self.bundle_out = not self.args.no_publish

    def recompute_rank(self, bundle):
        """Run the pinned ranker in-process; never read a transferred pickle cache."""
        run, base = self.cycle_dir(), self.snapshot_path
        out = self.dir / "rank"
        out.mkdir()
        args = ["--status", "link_status.csv", "--folds", "data_fold_list.csv",
                "--ledger", base / "reverse/data_ledger.csv", "--functions", base / "reverse/functions.csv",
                "--exports", base / "reverse/exports.csv", "--json", out / "data_back_rank.json"]
        args += (["--objects", "../match", "--cache", self.dir / "rank_objects.pkl"]
                 if (base / "build/match").is_dir() else ["--no-objects"])
        self.step("rank", self.tool("tools/data_back_rank.py", *args), cwd=run)
        (out / "data_back_rank.txt").write_bytes((self.dir / "rank.log").read_bytes().replace(b"\r\n", b"\n"))
        for name in ("data_back_rank.txt", "data_back_rank.json"):
            recomputed = (out / name).read_bytes().replace(b"\r\n", b"\n")
            if recomputed != (bundle / name).read_bytes().replace(b"\r\n", b"\n"):
                raise Refused(f"publisher recomputed {name} differs from builder bundle")
        for name in ("data_back_rank.txt", "data_back_rank.json"):
            shutil.copyfile(out / name, run / name)

    def publish_ownership(self, cycle_tag):
        tag = "ownership-" + cycle_tag
        repo = self.args.repo or self.policy["repository"]
        # Native gh is installed by the maintainer, never read from the checkout.
        wait_cooldown(self.clock, self.say)
        self.prove_code("before ownership publication")
        argv = ["gh", "release", "create", tag, "--repo", repo, "--target", self.commit,
                "--prerelease", "--title", tag, "--notes", BUILDER_ATTESTATION + "\nSigned ownership evidence for " + cycle_tag,
                str(self.dir / "image_ownership.json"), str(self.dir / "image_ownership_history.csv"), str(self.report)]
        try:
            argv[0] = self.policy["executables"]["gh"]
            result = subprocess.run(argv, cwd=self.work / "native-cwd", env=self.env(True), stdin=subprocess.DEVNULL,
                                    capture_output=True, text=True)
            if result.returncode:
                raise StepFailed("ownership evidence publication: " + result.stderr[-300:])
        finally:
            stamp_clock(self.clock, "nightly ownership publication")


def parse(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--role", choices=("builder", "publisher"), help="required except for maintainer --approve")
    ap.add_argument("--install-dir", help="protected runner, approved.json, security.json and checker bundle")
    ap.add_argument("--state-dir", help="private writable state directory for this role")
    ap.add_argument("--handoff-dir", help="builder-writable directory; publisher only reads")
    ap.add_argument("--root", help="builder repository (explicit: installed runner lives outside the clone)")
    ap.add_argument("--approve", metavar="REV",
                    help="a maintainer's act: approve REV's code (tools/, .githooks/, the BFME 1 pin) and install its "
                         "runner in build/nightly_measure/runner/; review `git diff <approved> REV` first")
    ap.add_argument("--checkout", help="the runner's own checkout (default <repo>/build/nightly_measure_wt; created "
                                       "when missing)")
    ap.add_argument("--snapshot-dir", help="link_cycle --snapshot-dir (default <repo>/build/nm, runner-owned); "
                                           "<dir>/<commit 10> may be no longer than the checkout's path")
    ap.add_argument("--keep-snapshots", type=int, default=2,
                    help="after the run, keep this many snapshots this runner created (default 2; 0 keeps all)")
    ap.add_argument("--producer", default=f"{socket.gethostname()}/nightly_measure",
                    help="publish_cycle bundle --producer label")
    ap.add_argument("--repo", help="OWNER/REPO for the bundle publish and fetches (default: the tools' own)")
    ap.add_argument("--push-clock", help="the GitHub-write clock (default $BFME_PUSH_CLOCK, else "
                                         "<repo>/build/push_clock.json)")
    ap.add_argument("--no-publish", action="store_true",
                    help="no GitHub write: publish --dry-run, no install, ownership measured but not recorded")
    ap.add_argument("--skip", action="append", default=[], choices=SKIPPABLE, help="leave a step out (repeatable)")
    return ap.parse_args(argv)


def main(argv=None, *, root=None, out=print):
    args = parse(sys.argv[1:] if argv is None else argv)
    try:
        root = Path(root or args.root) if root or args.root else main_root()
        if args.approve:
            if args.role == "builder":
                raise Refused("builder cannot approve or install code")
            return approve(root, args.approve, out, install_dir=args.install_dir)
        if not args.role or not all((args.install_dir, args.state_dir, args.handoff_dir)):
            raise Refused("--role, --install-dir, --state-dir and --handoff-dir are required; see docs/nightly_setup.md")
        run = (BuilderRun if args.role == "builder" else PublisherRun)(args, root, out)
        if isinstance(run, SplitRun):
            run.preflight()
        lock = try_lock(run.work / "lock")
        if lock is None:
            holder = read_json(run.work / "holder.json")
            out(f"nightly_measure: another run holds {run.work / 'lock'}" + (f" ({holder})" if holder else "")
                + "; not started")
            return EXIT_LOCKED
        try:
            write_json(run.work / "holder.json", {"pid": os.getpid(), "host": socket.gethostname(), "since": utc()})
            return run.go()
        finally:
            unlock(lock)
    except (Refused, StepFailed) as e:
        out(f"nightly_measure: refused: {e}")
        return EXIT_SETUP


if __name__ == "__main__":
    sys.exit(main())
