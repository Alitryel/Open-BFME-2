#!/usr/bin/env python3
"""One verified rename per invocation, with its provenance in the ledger.

Renaming by hand is already a busy practice here (hundreds of Name/Rename
commits a week), and the byte gate cannot see most of what a hand rename
forgets. Names never reach the byte compare: build.py reads each body out of
the object by the row's MANGLED name and resolves every REL32 call through a
name -> address map built from functions.csv rows and symbols.csv pins. So a
rename that misses a caller's private declaration, a funclet's `parent=`
token, an `__ehhandler$<parent>` row, a pin, an `/alternatename` pragma or a
`present-unmatched` marker either fails some later gate far from the cause, or
-- worse -- passes every gate and breaks only the link (a stale pin keeps the
old name resolving; name_dependents then sees nothing "lost"). And
functions.csv union-merges, so a renamed-away (name, rva) without a
reverse/deleted_rows.csv tombstone can come back beside its successor, where
check_csv reads the pair as an ICF alias group. Only 9 of 240 recent rename
commits wrote that tombstone.

This tool makes the whole edit, verifies it, and records why:

  plan     every file, row, pin, note, marker and pragma the rename touches,
           computed in memory; `--dry-run` prints it and writes nothing;
  refuse   canonical names (retail exports, vendored= rows, .lib members,
           retail module class names, the retail RTTI exception classes,
           converged globals, evidence-tier names, anything spelled inside a
           string literal, anything name_basis.csv already records as
           canonical), a new name that collides or is itself a placeholder,
           an `inferred` basis replacing a real name, a generated source, a
           name a shrink-only baseline is keyed on, and a mangled-name change
           beyond the identifier;
  claim    every affected RVA, a `file:` scope for every Code/ or shim file
           written and `class:` for a class or member (tools/claims.py); claims
           this run newly took are KEPT for the lander, who releases them
           after the push (the command is printed), and released on failure;
  apply    under the ledger lock, after journalling the before-state to
           build/rename-journal/, then one ./build.sh over every touched
           ledger source (owner, callers, includers of a touched header) and
           the commit hooks' ledger checks (check_csv, find_declared_unmatched);
           the rename stands only when all pass;
  restore  every touched file byte for byte on any failure, exception or
           SIGTERM; a run killed outright leaves its journal, and
           `rename.py recover` restores it (every run refuses to start while
           one is pending);
  record   a tombstone 'Renamed to <new> by tools/rename.py (<basis>)' for each
           renamed (name, rva) row, and one reverse/name_basis.csv row
           (kind,old,new,basis,evidence,source,rva).

Provenance is the owner's rule: a descriptive name that is not proven
canonical still gets a clean readable identifier, and the ledger -- not the
identifier -- says it is `inferred`. An inferred name may replace only a
placeholder or weak name (tools/name_metric.py's definition, shared rather
than copied); a canonical name may replace a placeholder or an inferred name;
nothing replaces a canonical name. Both bases are checked, never asserted:

  inferred   --evidence agree:<id> names a row of reverse/name_agreed.csv
             for this very rename, and the agreement is recomputed from the
             hashed votes in reverse/name_votes.csv (tools/name_agreement.py):
             two or more distinct workers -- identities taken from the
             environment, not from a session label -- voted the spelling, no
             rival spelling has as many, nothing disputed it. The record is an
             index, never the authority. A file may instead take mechanical:<rows>, a stem
             derived from a real-named row it owns. Refused, too, over a
             real-named pin, a WorldBuilder lead or an evidence-tier name at
             the address, and for a word only shaped like a placeholder that a
             Zero Hour, BFME 1 or vendored/SDK view declares.
  canonical  export, module, rtti, vendored/lib, file (an approved TU or a
             retail __FILE__ path); wb, zh and bfme1 re-graded by
             tools/name_evidence.py's proof() -- the very rules that grade
             its candidates, so a hint never lands as a permanent name --
             with zh/bfme1 also citing a <path>:<line> that spells the name
             (never BFME 1's own ledgers, whose names agents chose; its
             ea_evidence.csv is EA's); string/assert citing the renamed
             function's own address in string_xrefs.tsv, whose string spells
             the word on word boundaries. Each verified.

When a rename respells a name another name_basis.csv record spells (a
method of a renamed class), a `carry` row moves that record with it.

After every `git pull --rebase` and before the push, the lane and the lander
run `rename.py check --range origin/master..HEAD`: a rename landed while
another seat added a pin, a caller or an extern with the old spelling passes
every gate (the byte gate masks DIR32, a stale pin keeps the old name
resolving) and breaks only the link; `check` refuses it.

Two kinds need more than a word rewrite. A `global` (one reverse/data_rows.csv
row) is invisible to the byte gate, which masks DIR32 operands: a consumer
left on the old extern still matches and only the link breaks, so consumers
are found by text and by object symbol table, and the rename refuses one it
cannot rewrite. Converged addresses (reverse/data_converged.csv) are never
renamed; reverse/data_ledger.csv, tool-written and protected, is reported
stale rather than edited. A `file` is a `git mv` within its directory (a move
across directories changes the region's default flags and the TU placement,
which are judgements) plus its path-keyed columns: functions.csv and
data_rows.csv `source`, tu_map.csv `source` and the docs/doxygen/sources.cfg
INPUT line. A unit keyed in a protected path-keyed register
(flag_overrides.csv, hatch_baseline.tsv, data_check_baseline.txt,
code_identity_baseline.tsv, data_ledger.csv) is refused as needing a
Verifier-Change commit, as is one that expands __FILE__ (the path reaches its
bytes), one another file #includes, and an approved retail TU path.

A `class` (one class/struct/union/enum token) is respelled as a whole token:
in every mangled name it scopes or types -- functions.csv names and notes
(`parent=`, `object-symbol=`), pins, data rows (`??_7X@@6B@`), funclet rows,
ctor/dtor/`??_G` rows, template arguments -- and in every source, header and
shim view that spells it, code and comments, plus the units whose objects
reference a renamed symbol. It refuses a word that is also a function or
datum identifier, a class registered in reverse/canonical_classes.csv (its
contract and class_gate key move in a class-reconciliation commit), and any
class that scopes an export, a vendored= or .lib row, an evidence-tier name or
a converged datum. Retail is /GR-, so no RTTI string carries a game class name.
A `member` (one non-static data member of one class) never reaches bytes:
every view declaring it and every file using it through a header view is
rewritten, a file that also declares the word for another class is refused.
A `param` or `local` is respelled inside one function body in one file; a
local is refused in a file that compiles /Od (the `// cl:` line,
flag_overrides.csv and the region default, last /O winning), where a name can
reorder the frame, and either is refused when the word could mean an outer
entity there (a global, a member, a spelling in an included header, a use
before the declaration) or the new word is already spelled in the file.
Their name_basis.csv rows are qualified (`Class::member`,
`Scope::function::param`), so a canonical record for one never protects an
unrelated name of the same spelling.

The tool never commits. It prints the files to stage and a suggested subject
('Rename <old> to <new> (<basis>)').

  python3 tools/rename.py function --rva 0x00658D50 --new readQuotedToken \\
      --basis inferred --evidence 'agree:<record>' --dry-run

  python3 tools/rename.py global --name '?g_00DFE9E0@@3UDisplayCriticalSection@@A' \\
      --new g_displayCriticalSection --basis inferred --evidence 'agree:<record>' --dry-run
  python3 tools/rename.py file --source Code/.../DrawableRva00278644.cpp \\
      --new Drawable_setAudible --basis inferred --evidence 'mechanical:<rows>' --dry-run

  python3 tools/rename.py class --name Rva0040ADDD --new AwardRecordView \\
      --basis inferred --evidence 'agree:<record>' --dry-run
  python3 tools/rename.py member --class Rva00362EC7 --member m_0C --new m_markerHandle \\
      --basis inferred --evidence 'agree:<record>' --dry-run
  python3 tools/rename.py local --source Code/.../BfmeCombine1236.cpp --function bfmeCombine1236 \\
      --name a4 --new rowScale --basis inferred --evidence 'agree:<record>' --dry-run

A landed inferred name that turns out wrong goes back through `revert`
(`rename.py revert --record <agreement id> --reason TEXT`, or the library's
revert()): basis `restored`, accepted only as the exact inverse of a
recorded inferred landing -- same kind and address, from the name's current
spelling (carry rows followed) to the placeholder it replaced. It is the one
rename whose new name may be a placeholder. The landing's tombstones leave
deleted_rows.csv (check_csv, a protected verifier, honours no other record;
teaching it to read `restored` rows is a Verifier-Change follow-up), the
landed name is tombstoned in turn, and the name_basis.csv row is append-only:
rename.py honours it if a union merge brings a lifted tombstone back, and
`check` reports that line.

Kinds in this build: function, global, file, class, member, param, local;
plus `check`, `recover` and `revert`. Vendored and SDK sources (vendored= or .lib
rows, library directories, gamespy and Platform SDK shims) are refused for
every kind. The library API (plan_rename, apply_rename, is_placeholder,
is_protected, check_renames, recover) is what the lane tools call.
"""
import argparse
import base64
import csv
import io
import json
import os
import posixpath
import re
import signal
import socket
import subprocess
import sys
import threading
import time
import uuid
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import ledger_io  # noqa: E402
import name_agreement  # noqa: E402
import name_metric  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = "reverse/functions.csv"
SYMBOLS = "reverse/symbols.csv"
DATA_ROWS = "reverse/data_rows.csv"
DELETED = "reverse/deleted_rows.csv"
NAME_BASIS = "reverse/name_basis.csv"
EXPORTS = "reverse/exports.csv"
NAME_TIERS = "reverse/name_tiers.csv"
CONVERGED = "reverse/data_converged.csv"
MODULES = "reverse/module_factory_registrations.csv"
DATA_LEDGER = "reverse/data_ledger.csv"
TU_MAP = "reverse/tu_map.csv"
LINK_STATUS = "reverse/link_status.csv"
SOURCES_CFG = "docs/doxygen/sources.cfg"
LOCK = "reverse/.add_match.lock"
NAME_BASIS_HEADER = "kind,old,new,basis,evidence,source,rva"
GENERATED = name_metric.GENERATED
SEARCH_ROOTS = ("Code", "reference/shims")
HEADER_SUFFIXES = (".h", ".hpp", ".hh", ".hxx", ".inl", ".inc")
SOURCE_SUFFIXES = (".cpp", ".c")
# Files keyed by name that the verifier freeze forbids editing: a renamed debt
# row cannot be re-keyed there, so the excuse would silently stop applying.
FROZEN_KEYED = ("reverse/*baseline*", "reverse/*whitelist*", "reverse/data_ledger.csv")
# The retail RTTI names of game.dat's thrown exception classes (-GR- leaves
# no other game class RTTI): the type-name strings are retail bytes.
RTTI_CLASSES = frozenset({"INIException", "XferException", "FunctorNotSet", "DllHandle", "Exception",
                          "LoadFailure", "CAtlException", "_com_error", "exception", "type_info"})
# Machine-checked canonical evidence kinds (check_canonical). A harvested
# pin, a caller's guess, a table or a vtable shape is an inference, not
# proof: those go through the inferred (agreement) path.
CANONICAL_KINDS = frozenset({"export", "vendored", "lib", "rtti", "module", "string", "assert", "file",
                             "zh", "bfme1", "wb"})
AGREED = name_agreement.AGREED
AGREED_HEADER = ",".join(name_agreement.AGREED_COLUMNS)
BODY_OWNERS = "reverse/body_owners.csv"
WB_LEADS = "reverse/wb_name_leads.csv"
STRING_XREFS = "reverse/string_xrefs.tsv"
BFME1 = "reference/open-bfme-1"
ZH_TREE = "inputs/reference/CnC_Generals_Zero_Hour"
# Third-party sources stay pristine: their names are upstream's (vendored=).
VENDORED_DIRS = ("Code/Libraries/Source/Lua/", "Code/Libraries/Source/Compression/ZLib/",
                 "Code/Libraries/Source/ATL/", "Code/Libraries/Source/GdiPlus/", "Code/Libraries/Source/DirectX/",
                 "Code/Libraries/Source/CRT/", "Code/GameEngine/Source/GameNetwork/GameSpy/gp/",
                 "Code/GameEngine/Source/GameNetwork/GameSpy/gstats/",
                 "Code/GameEngine/Source/GameNetwork/GameSpy/ghttp/",
                 "Code/GameEngine/Source/GameNetwork/GameSpy/serverbrowsing/", "vendor/",
                 "reference/shims/gamespy/")
# Platform SDK, DirectX, CRT and middleware views among the shims.
SDK_HEADER = re.compile(r"(?i)(?:win\w*|windowsx?|d3d\w*|ddraw|dinput\w*|dsound|dxerr\w*|mmsystem|mmreg|objbase"
                        r"|ocidl|ole\w*|shellapi|shlguid|shlobj|commctrl|comdef|comutil|atl\w*|dbghelp|imagehlp"
                        r"|lmcons|mapicode|netdb|process|direct|vfw|snmp|wmsdk|fstream|bink|mss|unknwn|wtypes"
                        r"|guiddef|basetsd|tchar|io|malloc|stdio|stdlib|string|math|time|limits|float|ctype"
                        r"|errno|assert|new|xstddef|excpt|stdarg|memory)\.h")
BASIS_RE = re.compile(r"inferred|restored|canonical:([a-z0-9-]+)")
# The one basis that may put a placeholder back: the exact inverse of a
# recorded inferred rename (revert()), evidence `revert:<agreement id> <reason>`.
RESTORED = "restored"
REVERT_RE = re.compile(r"revert:([A-Za-z0-9_.:-]+)(?:\s+(\S.*))?")
LANDED_TOMBSTONE = re.compile(r"Renamed to (\S+) by tools/rename\.py \(inferred\)")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
# A source split into the parts a rename treats differently. Literals end at a
# newline as the compiler's do, so a stray quote cannot swallow the file.
SEGMENT = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
PRAGMA_LINKER = re.compile(r"[ \t]*#[ \t]*pragma[ \t]+comment[ \t]*\([ \t]*linker\b")
MARKER_WORDS = ("present-unmatched", "absent-from-retail")
# `__identifier("?mangled")` names a symbol, not text: it is a code reference
# (thousands of Code/ call sites take a function's address this way).
IDENTIFIER_CALL = re.compile(r"__identifier\s*\(\s*$")


def identifier_string(text, start):
    """True when the string literal at `start` is an __identifier(...) argument."""
    return IDENTIFIER_CALL.search(text, max(0, start - 64), start) is not None
# Path-keyed ledger columns a file rename repoints.
PATH_COLUMNS = (("reverse/functions.csv", "source"), ("reverse/data_rows.csv", "source"),
                ("reverse/tu_map.csv", "source"), ("reverse/body_owners.csv", "source"))
# Path-keyed files a phase-1 file rename may not re-key: tool-owned or
# shrink-only (tools/protected_paths.py), so re-keying is a Verifier-Change commit.
PROTECTED_PATH_KEYED = ("reverse/flag_overrides.csv", "reverse/hatch_baseline.tsv",
                        "reverse/data_check_baseline.txt", "reverse/code_identity_baseline.tsv",
                        "reverse/data_ledger.csv")
IMAGE_BASE = 0x400000
# Characters that continue a mangled or C symbol on either side.
SYMBOL_CHAR = r"A-Za-z0-9_?@"


class Refusal(Exception):
    """The rename is refused; the message says why. Nothing was written."""


class VerifyFailed(Exception):
    """./build.sh did not report every touched source OK; everything was restored."""


# ---------------------------------------------------------------- shared rules

def is_placeholder(name, kind="function"):
    """True for a placeholder or weak identifier (tools/name_metric.py's
    definition: address/bfme/hex-run/offset/decompiler names, and for params
    and locals weak single letters and tmp/arg names). A mangled function name
    is judged by its identifier."""
    if kind == "function" and (name.startswith("?") or "@" in name):
        try:
            name = split_function_name(name)[1]
        except Refusal:
            return False
    return bool(name_metric.weak(kind, name))


def basis_kind(basis):
    """'inferred', 'canonical' or 'restored'; raises Refusal on anything else."""
    match = BASIS_RE.fullmatch(basis or "")
    if not match:
        raise Refusal(f"--basis must be 'inferred' or 'canonical:<evidence-kind>', got {basis!r}")
    if basis == RESTORED:
        return RESTORED
    if match.group(1) is not None:
        if match.group(1) not in CANONICAL_KINDS:
            raise Refusal(f"unknown canonical evidence kind {match.group(1)!r}; "
                          f"one of {', '.join(sorted(CANONICAL_KINDS))}")
        return "canonical"
    return "inferred"


def mangled_re(name):
    """`name` as a whole symbol: not part of a longer mangled or C name. `$`
    is a boundary, so `__ehhandler$<name>` and `__unwindfunclet$<name>$0` match;
    so is a local static's nested scope (`?s@?1??<name>@4HA`)."""
    return re.compile(r"(?<![%s])%s(?![%s])|(?<=\?[0-9]\?)%s(?=@)" % (
        SYMBOL_CHAR, re.escape(name), SYMBOL_CHAR, re.escape(name)))


def word_re(word):
    return re.compile(r"\b%s\b" % re.escape(word))


def split_function_name(mangled):
    """(prefix, identifier, suffix) of a function symbol whose identifier a
    rename may respell: `?ident@...` or a C name (`_ident`, `_ident@8`,
    `@ident@8`, `ident`). Special members, operators, templates and compiler
    labels are refused: their identifier is a class, or not text at all."""
    match = re.fullmatch(r"(\?)([A-Za-z_][A-Za-z0-9_]*)(@.+)", mangled)
    if match:
        return match.groups()
    if mangled.startswith("?"):
        raise Refusal(f"{mangled} is a special member, operator or template function; "
                      "its identifier is not a plain name (rename its class instead)")
    match = re.fullmatch(r"([_@]?)([A-Za-z_][A-Za-z0-9_]*?)((?:@\d+)?)", mangled)
    if match and not mangled.startswith(("__ehhandler$", "__unwindfunclet$")):
        return match.groups()
    raise Refusal(f"{mangled} is not a function name this tool can respell")


def rename_function_symbol(mangled, new_ident):
    """`mangled` with only its identifier respelled; refuses when MSVC's
    name back-references would make the compiler spell the result differently
    (the identifier is name fragment 0: a later `V0@`/`U0@`/`W40@`/`@0@`
    refers to it, and a later fragment spelled like the new identifier would
    become such a reference)."""
    prefix, old_ident, suffix = split_function_name(mangled)
    if prefix == "?":
        if re.search(r"(?:[VUT]|W4|@)0@", suffix):
            raise Refusal(f"{mangled}: a back-reference to the identifier (fragment 0) follows it; "
                          "respelling it would change the rest of the signature")
        if re.search(r"(?<![A-Za-z0-9_])%s@" % re.escape(new_ident), suffix) or \
                re.search(r"[VUT]%s@" % re.escape(new_ident), suffix):
            raise Refusal(f"{mangled}: {new_ident} already names a fragment of the signature; "
                          "the compiler would encode it as a back-reference")
        if re.search(r"[VUT@]%s@" % re.escape(old_ident), suffix):
            raise Refusal(f"{mangled}: {old_ident} also names a scope or type in the signature")
    return prefix + new_ident + suffix


class Unparsed(ValueError):
    """A mangled name outside the subset `fragments` reads."""


FUNCLET_PREFIXES = ("__ehhandler$", "__unwindfunclet$")


def fragments(symbol):
    """(start, end) of every name fragment of `symbol` -- each identifier of
    a qualified name, template name and C name -- in order. A class token is
    only ever one whole fragment, so `TBar` (a struct named TBar: `PAUTBar@@`)
    and the method `UBar` (`?UBar@Zed@@`) never contain the class Bar, which a
    lookbehind on V/U/T cannot tell apart. Raises Unparsed outside the MSVC
    7.1 subset the ledger uses; callers refuse rather than guess."""
    offset = 0
    for prefix in FUNCLET_PREFIXES:
        if symbol.startswith(prefix):
            offset = len(prefix)
    text = symbol[offset:]
    if not text.startswith("?"):
        match = re.fullmatch(r"[_@]?([A-Za-z_][A-Za-z0-9_]*?)(?:[@$][A-Za-z0-9_]+)?", text)
        if not match:
            raise Unparsed(symbol)
        return [(offset + match.start(1), offset + match.end(1))]
    out = []
    try:
        end = _parse_symbol(text, 0, out)
    except (IndexError, ValueError) as error:
        raise Unparsed(f"{symbol}: {error}") from None
    if text[end:] and not (offset and re.fullmatch(r"\$\d+", text[end:])):
        raise Unparsed(f"{symbol}: trailing {text[end:]!r}")
    return [(offset + a, offset + b) for a, b in out]


def _parse_symbol(s, i, out):
    if s[i] != "?":
        raise ValueError(f"symbol expected at {i}")
    i += 1
    if s[i] == "?" and s[i + 1] != "$":
        i += 1
        if s.startswith("__", i):
            i += 3
            if s[i] == "?":                              # ??__E?data@..@@YAXXZ: a nested symbol
                i = _parse_symbol(s, i, out)
                if s[i] != "@":
                    raise ValueError("dynamic initializer")
                return _parse_header(s, _parse_qualified(s, i + 1, out), out)
        elif s.startswith("_R0", i):
            i = _parse_type(s, i + 3, out)
            if not s.startswith("@8", i):
                raise ValueError("RTTI type descriptor")
            return i + 2
        elif s[i] == "_":
            if s.startswith("_R", i):
                raise ValueError("RTTI name")
            i += 2
        else:
            i += 1
    i = _parse_qualified(s, i, out)
    return _parse_header(s, i, out)


def _parse_qualified(s, i, out):
    """Fragments up to the terminating `@`; returns the index after it."""
    while True:
        c = s[i]
        if c == "@":
            return i + 1
        if c.isdigit():
            i += 1
        elif s.startswith("?$?", i):                    # template operator / special member
            k = i + 3
            k += 2 if s[k] == "_" else 1
            i = _parse_template_args(s, k, out)
        elif s.startswith("?$", i):
            j = s.index("@", i + 2)
            out.append((i + 2, j))
            i = _parse_template_args(s, j + 1, out)
        elif c == "?":
            if s[i + 1] == "A":                  # anonymous namespace ?A0x...@
                i = s.index("@", i) + 1
            elif s[i + 1].isdigit() and s[i + 2] == "?":   # ?1? + a nested function symbol
                i = _parse_symbol(s, i + 3, out)
            else:
                raise ValueError(f"scope at {i}")
        elif c.isalpha() or c == "_":
            j = s.index("@", i)
            if not IDENT.fullmatch(s[i:j]):
                raise ValueError(f"fragment {s[i:j]!r}")
            out.append((i, j))
            i = j + 1
        else:
            raise ValueError(f"name at {i}")


def _parse_template_args(s, i, out):
    while s[i] != "@":
        i = _parse_type(s, i, out)
    return i + 1


def _number_value(s, i):
    """(value, next index) of an encoded number."""
    sign = 1
    if s[i] == "?":
        sign, i = -1, i + 1
    if s[i].isdigit():
        return sign * (int(s[i]) + 1), i + 1
    j, value = i, 0
    while s[j] in "ABCDEFGHIJKLMNOP":
        value = value * 16 + "ABCDEFGHIJKLMNOP".index(s[j])
        j += 1
    if s[j] != "@":
        raise ValueError(f"number at {i}")
    return sign * value, j + 1


def _parse_number(s, i):
    if s[i] == "?":
        i += 1
    if s[i].isdigit():
        return i + 1
    j = i
    while s[j] in "ABCDEFGHIJKLMNOP":
        j += 1
    if s[j] != "@":
        raise ValueError(f"number at {i}")
    return j + 1


def _parse_function(s, i, out):
    """Return type, arguments and throw spec, after the calling convention."""
    i = i + 1 if s[i] == "@" else _parse_type(s, i, out)
    if s[i] == "X":
        i += 1
    else:
        while s[i] not in "@Z":
            i = _parse_type(s, i, out)
        i += 1
    if s[i] != "Z":
        raise ValueError(f"throw spec at {i}")
    return i + 1


def _parse_type(s, i, out):
    c = s[i]
    if c in "PQRSAB" and s[i + 1] == "6":                   # function pointer
        return _parse_function(s, i + 3, out)
    if c in "PQRSAB" and s[i + 1] == "8":                   # member function pointer
        i = _parse_qualified(s, i + 2, out)
        return _parse_function(s, i + 2, out)
    if c in "PQRSAB":
        i += 1
        if s[i] == "E":
            i += 1
        if s[i] not in "ABCD":
            raise ValueError(f"pointer cv at {i}")
        return _parse_type(s, i + 1, out)
    if c in "VUT":
        return _parse_qualified(s, i + 1, out)
    if c == "W" and s[i + 1].isdigit():
        return _parse_qualified(s, i + 2, out)
    if c == "?" and s[i + 1] in "AB":
        return _parse_type(s, i + 2, out)
    if c == "_" and s[i + 1].isalpha():
        return i + 2
    if s.startswith("$$C", i) and s[i + 3] in "ABCD":
        return _parse_type(s, i + 4, out)
    if s.startswith("$0", i):
        return _parse_number(s, i + 2)
    if s.startswith(("$1", "$E"), i):
        return _parse_symbol(s, i + 2, out)
    if c == "Y":                                            # array: dimension count, dimensions
        count, i = _number_value(s, i + 1)
        for _ in range(count):
            i = _parse_number(s, i)
        return _parse_type(s, i, out)
    if c.isdigit() or c in "CDEFGHIJKMNOXZ":
        return i + 1
    raise ValueError(f"type {c!r} at {i}")


def _parse_header(s, i, out):
    if i == len(s):
        return i
    c = s[i]
    if c in "01234":                                         # data: type, cv
        i = _parse_type(s, i + 1, out)
        if s[i] == "E":
            i += 1
        if s[i] not in "ABCD":
            raise ValueError(f"data cv at {i}")
        return i + 1
    if c in "67":                                            # vftable / vbtable
        i += 2
        while s[i] != "@":
            i = _parse_qualified(s, i, out)
        return i + 1
    if c == "8":
        return i + 1
    if c in "YZ":
        return _parse_function(s, i + 2, out)
    if c in "CDKLST":
        return _parse_function(s, i + 2, out)
    if c in "ABEFIJMNQRUV":
        i += 1
        if s[i] == "E":
            i += 1
        return _parse_function(s, i + 2, out)
    if c in "GHOPWX":
        i = _parse_number(s, i + 1)
        return _parse_function(s, i + 2, out)
    if c == "$" and s[i + 1] in "012345":                    # vtordisp thunk: two numbers
        i = _parse_number(s, _parse_number(s, i + 2))
        return _parse_function(s, i + 2, out)
    raise ValueError(f"header {c!r} at {i}")


def leading_fragment(symbol):
    """The identifier fragment of `?ident@...` or a C name, else None: the
    first fragment of a special member (`??0X`, `??1X`, `??_GX`, `??RX`) is
    its class, not an identifier."""
    text = symbol
    for prefix in FUNCLET_PREFIXES:
        if text.startswith(prefix):
            text = text[len(prefix):]
    if text.startswith("??"):
        return None
    try:
        spans = fragments(text)
    except Unparsed:
        return None
    return text[spans[0][0]:spans[0][1]] if spans else None


SYMBOL_TOKEN = re.compile(r"(?:__ehhandler\$|__unwindfunclet\$)?\?[A-Za-z0-9_?@$]+")


def class_spans(symbol, word):
    """Spans of `symbol`'s fragments spelling the type `word` (not its
    leading identifier). Raises Unparsed when `symbol` spells `word@` and
    cannot be read."""
    if f"{word}@" not in symbol:
        return []
    spans = fragments(symbol)
    lead = 0
    body = symbol
    for prefix in FUNCLET_PREFIXES:
        if body.startswith(prefix):
            body = body[len(prefix):]
    if body.startswith("?") and not body.startswith("??"):
        lead = 1
    return [(a, b) for a, b in spans[lead:] if symbol[a:b] == word]


def class_sub(text, word, new):
    """`text` with every mangled symbol in it respelling the type fragment
    `word` as `new`; returns (text, count). Raises Unparsed for a symbol that
    spells `word@` and cannot be tokenized."""
    out, last, count = [], 0, 0
    for match in SYMBOL_TOKEN.finditer(text):
        symbol = match.group(0)
        spans = class_spans(symbol, word)
        if not spans:
            continue
        pieces, prev = [], 0
        for a, b in spans:
            pieces += [symbol[prev:a], new]
            prev = b
        pieces.append(symbol[prev:])
        out += [text[last:match.start()], "".join(pieces)]
        last = match.end()
        count += len(spans)
    out.append(text[last:])
    return "".join(out), count


class ClassToken:
    """`class_sub` with the interface of a compiled regex (`search`, `sub`,
    `subn`), for the ledger and pragma rewrites."""

    def __init__(self, word):
        self.word = word

    def subn(self, new, text):
        try:
            return class_sub(text, self.word, new if isinstance(new, str) else new(None))
        except Unparsed as error:
            raise Refusal(f"cannot tokenize a mangled name spelling {self.word}: {error}") from None

    def sub(self, new, text):
        return self.subn(new, text)[0]

    def search(self, text):
        return self.subn(self.word + "\0", text)[1] > 0


def check_new_identifier(new, kind, basis=None):
    """A new name is an identifier, not a keyword, and not a placeholder --
    except under basis `restored`, which puts back the exact placeholder a
    recorded inferred rename replaced (check_restore proves it is that one)."""
    if not IDENT.fullmatch(new or ""):
        raise Refusal(f"new name {new!r} is not a C++ identifier")
    if new in name_metric.KEYWORDS:
        raise Refusal(f"new name {new!r} is a keyword")
    if basis != RESTORED and is_placeholder(new, kind):
        raise Refusal(f"new name {new} is itself a placeholder or weak name")


# ---------------------------------------------------------------- the tree

class Context:
    """The tree a rename reads and writes. Everything is relative to `root`;
    tests point it at a temporary git repository with miniature ledgers."""

    def __init__(self, root=ROOT, object_scan=True, sweep_dirs=("build",)):
        self.root = Path(root).resolve()
        self.object_scan = object_scan and self.root == ROOT.resolve()
        # where tools/name_evidence.py finds the zh/bfme1 sweep caches
        self.sweep_dirs = tuple(sweep_dirs)
        self._cache = {}

    def path(self, rel):
        return self.root / rel

    def read(self, rel):
        path = self.path(rel)
        return path.read_bytes() if path.exists() else None

    def dicts(self, rel):
        if rel not in self._cache:
            raw = self.read(rel)
            self._cache[rel] = list(csv.DictReader(io.StringIO(raw.decode("utf-8")))) if raw else []
        return self._cache[rel]

    def rows(self):
        return self.dicts(FUNCTIONS)

    def pins(self):
        return self.dicts(SYMBOLS)

    def git(self, *args):
        result = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True)
        if result.returncode not in (0, 1):
            raise Refusal(f"git {' '.join(args[:2])} failed: {result.stderr.strip()[:200]}")
        return result.stdout

    def grep_files(self, needle, *, word=False, roots=SEARCH_ROOTS):
        """Tracked files under `roots` containing `needle` (fixed string)."""
        args = ["grep", "-l", "-F", "-I"] + (["-w"] if word else []) + ["-e", needle, "--", *roots]
        return sorted(p for p in self.git(*args).splitlines() if p)

    def ledger_sources(self):
        if "_sources" not in self._cache:
            self._cache["_sources"] = {r["source"] for r in self.rows() if r.get("status") == "matched"}
        return self._cache["_sources"]


def is_generated(rel):
    return rel.replace("\\", "/").startswith(GENERATED)


def name_basis_rows(ctx):
    return ctx.dicts(NAME_BASIS)


def recorded_basis(ctx, name):
    """The basis name_basis.csv last recorded for `name` as a NEW name, or None."""
    found = None
    for row in name_basis_rows(ctx):
        if row.get("new") == name:
            found = row.get("basis")
    return found


def current_records(ctx):
    """{spelling: last name_basis.csv row recording it as a new name}."""
    out = {}
    for row in name_basis_rows(ctx):
        if row.get("new"):
            out[row["new"]] = row
    return out


def carry_records(ctx, plan, transform):
    """Append a `carry` row for every name_basis.csv record whose spelling
    this rename changes (a method of a renamed class, a param of a renamed
    function): protection and provenance are looked up by spelling, so a
    record left on the old spelling would silently lapse."""
    lines = []
    for spelling, row in current_records(ctx).items():
        if spelling in (plan.old, plan.new):
            continue
        moved = transform(spelling)
        if moved and moved != spelling:
            plan.carried.append((spelling, moved, row.get("basis", "")))
            lines.append(csv_line(["carry", spelling, moved, row.get("basis", ""),
                                   f"scope renamed by {plan.subject()}", row.get("source", ""), row.get("rva", "")]))
    if lines:
        plan.edit(ctx, NAME_BASIS, appended(plan.after.get(NAME_BASIS, ctx.read(NAME_BASIS)), lines,
                                            header=NAME_BASIS_HEADER))


def is_protected(ctx, kind, name, *, rva=None, identifier=None):
    """Why `name` (mangled for a function) is canonical and may not be renamed,
    or None. `identifier` is the bare word the rename respells. A class is
    judged by every mangled name it scopes (class_protected); a member, param
    or local (qualified `Scope::name`) only by name_basis.csv."""
    if kind == "class":
        return class_protected(ctx, name)
    if kind in ("member", "param", "local"):
        basis = recorded_basis(ctx, name)
        if basis and basis.startswith("canonical"):
            return f"{name} is recorded canonical ({basis}) in reverse/name_basis.csv"
        return None
    ident = identifier or name
    if any(row.get("name") == name for row in ctx.dicts(EXPORTS)):
        return f"{name} is a retail export (reverse/exports.csv)"
    for row in ctx.rows():
        if row.get("name") != name:
            continue
        notes = row.get("notes", "")
        if "vendored=" in notes:
            return f"{name} is a vendored= row (upstream's real identity)"
        if row.get("source", "").lower().endswith(".lib"):
            return f"{name} is a .lib member"
    for row in ctx.dicts(NAME_TIERS):
        if row.get("name") == name and row.get("name_tier") == "evidence":
            return f"{name} is evidence-tier in reverse/name_tiers.csv ({row.get('evidence')})"
    if ident in RTTI_CLASSES:
        return f"{ident} is a retail RTTI exception class name"
    if any(row.get("name") == ident for row in ctx.dicts(MODULES)):
        return f"{ident} is a retail module class name (reverse/module_factory_registrations.csv)"
    if any(row.get("name") == name for row in ctx.dicts(CONVERGED)):
        return f"{name} is a converged global (reverse/data_converged.csv)"
    for candidate in {name, ident}:
        basis = recorded_basis(ctx, candidate)
        if basis and basis.startswith("canonical"):
            return f"{candidate} is recorded canonical ({basis}) in reverse/name_basis.csv"
    return None


# ---------------------------------------------------------------- text rewrite

def rewrite_source(text, word, new_word, old_symbol, new_symbol):
    """Respell `word` in code, `old_symbol` in comments and linker pragmas, and
    `word` in present-unmatched/absent-from-retail markers. Returns
    (text, counts, string_hits): a string literal that still spells `word`
    afterwards is retail-locked text the rename must not touch."""
    words, symbol = word_re(word), mangled_re(old_symbol)
    out, last, string_hits = [], 0, []
    counts = {"code": 0, "comment": 0, "pragma": 0}

    def code(part):
        new, n = words.subn(new_word, part)
        counts["code"] += n
        return new

    for match in SEGMENT.finditer(text):
        out.append(code(text[last:match.start()]))
        seg = match.group(0)
        if seg.startswith(("//", "/*")):
            new, n = symbol.subn(new_symbol, seg)
            if any(w in seg for w in MARKER_WORDS):
                new, m = words.subn(new_word, new)
                n += m
            counts["comment"] += n
        else:
            line_start = text.rfind("\n", 0, match.start()) + 1
            new = seg
            if PRAGMA_LINKER.match(text, line_start):
                new, n = symbol.subn(new_symbol, seg)
                counts["pragma"] += n
            elif identifier_string(text, match.start()):
                new, n = symbol.subn(new_symbol, seg)
                if n:
                    counts["identifier"] = counts.get("identifier", 0) + n
            if words.search(new):
                string_hits.append(seg)
        out.append(new)
        last = match.end()
    out.append(code(text[last:]))
    return "".join(out), counts, string_hits


def code_mentions(text, word):
    """Occurrences of `word` in code (comments and literals blanked)."""
    return len(word_re(word).findall(name_metric.strip(text)))


# ---------------------------------------------------------------- ledger rewrite

def rewrite_records(raw, label, symbol_re, new_symbol):
    """Replace a whole symbol in every record of an LF ledger. Returns
    (new_raw, [(old_fields, new_fields)]) for the records that changed;
    every other record keeps its exact bytes."""
    ledger_io.lf_terminator(raw, label)
    out, changed = [], []
    for payload, term in ledger_io.split_records(raw):
        text = payload.decode("utf-8")
        new = symbol_re.sub(lambda _m: new_symbol, text)
        if new != text:
            changed.append((ledger_io.fields(payload), ledger_io.fields(new.encode("utf-8"))))
            payload = new.encode("utf-8")
        out.append(payload + term)
    return b"".join(out), changed


def csv_line(values):
    buffer = io.StringIO()
    csv.writer(buffer, lineterminator="\n").writerow(values)
    return buffer.getvalue().encode("utf-8")


def tombstone_line(name, rva, reason):
    """deleted_rows.csv's own spelling: bare name and RVA, quoted reason."""
    return f'{name},0x{rva:08X},"{reason.replace(chr(34), chr(34) * 2)}"\n'.encode("utf-8")


def appended(raw, lines, header=None):
    """`raw` plus `lines`; a missing file starts with `header`."""
    if raw is None:
        raw = (header + "\n").encode("utf-8") if header else b""
    elif raw and not raw.endswith(b"\n"):
        raise Refusal("ledger does not end with a newline (truncated last row?)")
    return raw + b"".join(lines)


# ---------------------------------------------------------------- the plan

@dataclass
class Plan:
    kind: str
    old: str
    new: str
    basis: str
    evidence: str
    source: str
    rva: int
    old_word: str = ""
    new_word: str = ""
    before: dict = field(default_factory=dict)    # rel -> bytes or None (absent)
    after: dict = field(default_factory=dict)     # rel -> bytes
    verify: list = field(default_factory=list)    # ledger sources ./build.sh must pass
    renamed_rows: list = field(default_factory=list)   # (old name, new name, rva)
    renamed_pins: list = field(default_factory=list)
    notes_rows: list = field(default_factory=list)
    source_counts: dict = field(default_factory=dict)
    claims: list = field(default_factory=list)
    warnings: list = field(default_factory=list)
    mentions: list = field(default_factory=list)  # files outside the rename that name the old name
    moves: list = field(default_factory=list)     # (old path, new path): git mv, undone by git mv
    moved_bytes: dict = field(default_factory=dict)  # old path -> its bytes when planned
    renamed_data: list = field(default_factory=list)  # data_rows.csv (old name, new name, rva)
    path_rows: dict = field(default_factory=dict)     # ledger -> records whose path column moved
    owner_rows: list = field(default_factory=list)    # body_owners.csv (name, rva) renamed with their row
    carried: list = field(default_factory=list)       # name_basis.csv records carried to a new spelling

    def edit(self, ctx, rel, data):
        if rel not in self.before:
            self.before[rel] = ctx.read(rel)
        self.after[rel] = data

    def subject(self):
        if self.kind in ("member", "param", "local"):
            return f"Rename {self.old} to {self.new_word} ({self.basis})"
        return f"Rename {self.old_word or self.old} to {self.new_word or self.new} ({self.basis})"

    def report(self):
        where = f" at 0x{self.rva:08X}" if self.rva is not None else ""
        lines = [f"rename: {self.kind} {self.old} -> {self.new}{where} ({self.basis})",
                 f"  owner source: {self.source}"]
        for old, new in self.moves:
            lines.append(f"  git mv {old} {new}")
        for rel, count in sorted(self.path_rows.items()):
            lines.append(f"  {rel}: {count} path field(s) repointed")
        if self.renamed_data:
            lines.append(f"  data_rows.csv rows renamed ({len(self.renamed_data)}), each tombstoned:")
            lines += [f"    0x{rva:08X} {old} -> {new}" for old, new, rva in self.renamed_data]
        if self.renamed_rows:
            lines.append(f"  functions.csv rows renamed ({len(self.renamed_rows)}), each tombstoned:")
            lines += [f"    0x{rva:08X} {old} -> {new}" for old, new, rva in self.renamed_rows]
        if self.notes_rows:
            lines.append(f"  functions.csv notes rewritten ({len(self.notes_rows)}):")
            lines += [f"    0x{rva:08X} {name}" for name, rva in self.notes_rows[:20]]
        if self.owner_rows:
            lines.append(f"  body_owners.csv owners renamed with their rows ({len(self.owner_rows)}):")
            lines += [f"    0x{rva:08X} {name}" for name, rva in self.owner_rows]
        if self.carried:
            lines.append(f"  name_basis.csv records carried ({len(self.carried)}):")
            lines += [f"    {old} -> {new} ({basis})" for old, new, basis in self.carried]
        if self.renamed_pins:
            lines.append(f"  symbols.csv pins renamed in place ({len(self.renamed_pins)}):")
            lines += [f"    {address} {old} -> {new}" for old, new, address in self.renamed_pins]
        if self.source_counts:
            lines.append(f"  sources rewritten ({len(self.source_counts)}):")
            for rel, counts in sorted(self.source_counts.items()):
                detail = ", ".join(f"{k} {v}" for k, v in counts.items() if v)
                lines.append(f"    {rel} ({detail})")
        lines.append(f"  verify ({len(self.verify)}): ./build.sh " + " ".join(self.verify))
        if self.claims:
            lines.append("  claims: " + " ".join(str(c) if isinstance(c, str) else f"0x{c:08X}"
                                                for c in self.claims))
        lines.append(f"  ledger files: {', '.join(sorted(r for r in self.after if r.startswith('reverse/')))}")
        for rel in self.mentions:
            lines.append(f"  mention (not rewritten): {rel}")
        for warning in self.warnings:
            lines.append(f"  warning: {warning}")
        lines.append(f"  suggested subject: {self.subject()}")
        return "\n".join(lines)


def is_vendored_path(ctx, rel):
    """True for a third-party or SDK source whose names are upstream's: a
    file any vendored= or .lib row lists as its source, a vendored library
    directory, the gamespy shims, or a Platform SDK/DirectX/CRT shim header."""
    rel = (rel or "").replace("\\", "/")
    if rel.lower().endswith(".lib") or rel.startswith(VENDORED_DIRS):
        return True
    if rel.startswith("reference/shims/") and SDK_HEADER.fullmatch(posixpath.basename(rel)):
        return True
    if "_vendored_sources" not in ctx._cache:
        ctx._cache["_vendored_sources"] = {r.get("source", "") for r in ctx.rows()
                                           if "vendored=" in r.get("notes", "")
                                           or r.get("source", "").lower().endswith(".lib")}
    return rel in ctx._cache["_vendored_sources"]


def refuse_vendored(ctx, paths, what):
    vendored = sorted(p for p in paths if p and is_vendored_path(ctx, p))
    if vendored:
        raise Refusal(f"{what} touches vendored or SDK source {vendored[0]}: its names are upstream's "
                      "(canonical) and the file stays pristine")


def heuristic_placeholder(word, kind):
    """True when `word` is a placeholder only by name_metric's shape rules
    (an offset-like tail, a weak local) -- the ones that can misread a real
    name -- rather than by an address token, a bfme token, a hex run, a
    decompiler local or an unambiguous field-style offset (m_0C, unk14)."""
    if not is_placeholder(word, kind):
        return False
    if name_metric.ADDRESSED.fullmatch(word) or re.search(r"(?i)(^|_)bfme", word) or \
            re.search(r"[0-9A-F]{6,8}", word) or name_metric.HEXRUN.search(word) or \
            name_metric.OPAQUE.fullmatch(word) or name_metric.OFFSET_FIELD.fullmatch(word):
        return False
    return True


def reference_declarers(ctx, word, limit=40):
    """Files that declare `word` (name_metric.declared) in the Zero Hour
    tree, the BFME 1 game tree or this repo's vendored/SDK views."""
    found = []
    sub = ctx.path(BFME1)
    if (sub / ".git").exists():
        hits = subprocess.run(["git", "-C", str(sub), "grep", "-l", "-w", "-F", "-I", "-e", word, "--",
                               ZH_TREE, "game"], capture_output=True, text=True).stdout.splitlines()
        for hit in hits[:limit]:
            text = (sub / hit).read_text(encoding="utf-8", errors="replace")
            if any(name == word for kind, name in name_metric.declared(hit, text) if kind != "file"):
                found.append(f"{BFME1}/{hit}")
    for rel in ctx.grep_files(word, word=True):
        if is_vendored_path(ctx, rel):
            text = (ctx.read(rel) or b"").decode("utf-8", errors="replace")
            if any(name == word for kind, name in name_metric.declared(rel, text) if kind != "file"):
                found.append(rel)
    return found


def wb_rows(ctx, rva):
    return [r for r in ctx.dicts(WB_LEADS) if _rva(r.get("target_rva")) == rva and r.get("wb_name")]


def wb_identifiers(ctx):
    if "_wb_ids" not in ctx._cache:
        ids = set()
        for row in ctx.dicts(WB_LEADS):
            ids.update(p for p in re.split(r"::|[^A-Za-z0-9_]", row.get("wb_name", "")) if p)
        ctx._cache["_wb_ids"] = ids
    return ctx._cache["_wb_ids"]


def inferred_guards(ctx, kind, old_name, old_word, rva):
    """Refuse an inferred name over evidence already on record: a real-named
    pin, a WorldBuilder lead or an evidence-tier name at the address, an old
    word that WorldBuilder or the evidence tier spells, or (for a word that is
    a placeholder only by shape) one declared in a reference tree or a
    vendored/SDK view."""
    if rva is not None and kind in ("function", "global"):
        own = mangled_re(old_name)
        for pin in ctx.pins():
            name = pin.get("name", "")
            if _rva(pin.get("address")) != rva or not name or own.search(name):
                continue
            ident = leading_fragment(name) or (fragments_text(name) or [name])[0]
            if not is_placeholder(ident, "function"):
                raise Refusal(f"symbols.csv pin {name} already names 0x{rva:08X}; an inferred name may not "
                              "replace a body with a real name on record -- resolve it first "
                              "(tools/pin_consistency.py, or land it as canonical:<kind>)")
        if kind == "function":
            leads = wb_rows(ctx, rva)
            if leads:
                raise Refusal(f"WorldBuilder lead {leads[0]['wb_name']} (score {leads[0].get('score')}) names "
                              f"0x{rva:08X}; land it as canonical:wb if it fits, never an inferred name over it")
        for row in ctx.dicts(NAME_TIERS):
            if _rva(row.get("target_rva")) == rva and row.get("name_tier") == "evidence" \
                    and row.get("name") != old_name:
                raise Refusal(f"evidence-tier name {row.get('name')} ({row.get('evidence')}) is on record at "
                              f"0x{rva:08X}; an inferred name may not replace it")
    if old_word in wb_identifiers(ctx):
        raise Refusal(f"{old_word} is spelled by a WorldBuilder name in {WB_LEADS}: it may be EA's own")
    for row in ctx.dicts(NAME_TIERS):
        if row.get("name_tier") == "evidence" and old_word in (fragments_text(row.get("name", "")) or []):
            raise Refusal(f"{old_word} is part of the evidence-tier name {row.get('name')}")
    if kind in ("function", "class", "global", "member") and heuristic_placeholder(old_word, kind):
        declarers = reference_declarers(ctx, old_word)
        if declarers:
            raise Refusal(f"{old_word} is declared in {declarers[0]}: a reference or vendored name, "
                          "not a placeholder, whatever its shape")


def fragments_text(symbol):
    """The fragment texts of `symbol`, or None when it cannot be read."""
    try:
        return [symbol[a:b] for a, b in fragments(symbol)]
    except Unparsed:
        return None


def check_agreement(ctx, kind, evidence, old_names, new_names, rva):
    """An inferred name's two-agent agreement: `agree:<id>` names a row of
    reverse/name_agreed.csv for this very rename, and the votes it indexes
    carry it. The row is only an index (kind, old, new, rva and the lane key
    source|kind|scope|placeholder); its `agents` column is not trusted. The
    agreement is recomputed from reverse/name_votes.csv by
    tools/name_agreement.py: two or more distinct workers voted the landed
    spelling, no rival spelling has as many, and neither the record nor the
    spelling has been disputed."""
    match = re.fullmatch(r"agree:([A-Za-z0-9_.:-]+)", evidence.strip())
    if not match:
        raise Refusal("an inferred name lands only on a two-agent agreement: --evidence agree:<record-id> "
                      f"naming a row of {AGREED} (or mechanical:<rows> for a file named from its own rows)")
    rid = match.group(1)
    rows = [r for r in ctx.dicts(AGREED) if r.get("id") == rid]
    if not rows:
        raise Refusal(f"agreement record {rid} is not in {AGREED}")
    row = rows[-1]
    problems = []
    if row.get("kind") != kind:
        problems.append(f"kind {row.get('kind')!r}")
    if row.get("old") not in old_names:
        problems.append(f"old {row.get('old')!r}")
    if row.get("new") not in new_names:
        problems.append(f"new {row.get('new')!r}")
    if rva is not None and _rva(row.get("rva")) != rva:
        problems.append(f"rva {row.get('rva')!r}")
    key = row.get("key") or ""
    parts = key.split("|")
    if len(parts) != 4 or parts[1] != kind or parts[3] != row.get("old"):
        problems.append(f"lane key {key!r} (source|kind|scope|placeholder of this rename)")
    if any(r.get("status") == "disputed" for r in rows):
        problems.append("the record was disputed")
    if not problems:
        problems = name_agreement.verify(ctx.dicts(name_agreement.VOTES), ctx.dicts(AGREED), key,
                                         row.get("new", ""))
    if problems:
        raise Refusal(f"agreement record {rid} does not agree to this rename: {'; '.join(problems)}")


def mechanical_stems(ctx, source):
    """File stems derivable from the real-named rows `source` owns: a row's
    identifier, its class, Class_method and ClassMethod."""
    stems = set()
    for row in ctx.rows():
        if row.get("source") != source or row.get("status") != "matched":
            continue
        scope = scope_of(row.get("name", "")) or ""
        parts = [p for p in scope.split("::") if p]
        if not parts or any(is_placeholder(p, "function") for p in parts):
            continue
        ident = parts[-1].lstrip("~")
        cls = parts[-2] if len(parts) > 1 else None
        stems.add(ident)
        if cls:
            stems.update({cls, f"{cls}_{ident}", cls + ident[:1].upper() + ident[1:]})
    return {s.lower() for s in stems}


def check_canonical(ctx, kind, evidence_kind, evidence, new_name, new_word, rva, *, old_word=None):
    """Verify a canonical basis against the record it cites; raises Refusal.
    A canonical name is permanent (nothing replaces it), so it is never
    self-asserted, and never weaker than tools/name_evidence.py's proof:
    wb, zh and bfme1 are re-graded by name_evidence.proof() (the same rules
    that grade the lane's candidates: a WB pairing that scores, asserts the
    name and is unique; a specific Zero Hour same-body placement at this
    address; a BFME 1 same-body placement with EA or Zero Hour same-body
    support) and the citation must still check out; string and assert need
    a retail string referenced by this very function (or, for a class, by a
    function it scopes) that spells the word on word boundaries."""
    def cite():
        match = re.search(r"((?:reference|Code|vendor)/[^\s:]+):(\d+)", evidence)
        if not match:
            raise Refusal(f"canonical:{evidence_kind} needs --evidence citing <path>:<line>")
        path, line = match.group(1), int(match.group(2))
        data = ctx.read(path)
        if data is None:
            raise Refusal(f"cited file {path} does not exist")
        lines = data.decode("utf-8", errors="replace").splitlines()
        if not 0 < line <= len(lines) or not word_re(new_word).search(lines[line - 1]):
            raise Refusal(f"{path}:{line} does not spell {new_word}")
        return path

    def graded(which):
        import name_evidence
        why = name_evidence.proof(ctx.root, which, kind, old_word, new_word, rva, sweep_dirs=ctx.sweep_dirs)
        if why:
            raise Refusal(f"canonical:{which}: tools/name_evidence.py does not grade {old_word} -> {new_word} "
                          f"as proof: {'; '.join(why)[:400]}")

    def cited_rva():
        match = re.search(r"0x([0-9A-Fa-f]{1,8})", evidence)
        return int(match.group(1), 16) if match else None

    if evidence_kind == "export":
        names = {r.get("name", "") for r in ctx.dicts(EXPORTS)}
        ok = new_name in names if kind in ("function", "global") else \
            any(new_word in (fragments_text(n) or []) for n in names)
        if not ok:
            raise Refusal(f"canonical:export: no retail export in {EXPORTS} spells {new_name}")
    elif evidence_kind == "module":
        if not any(r.get("name") == new_word for r in ctx.dicts(MODULES)):
            raise Refusal(f"canonical:module: {new_word} is not a retail module class name in {MODULES}")
    elif evidence_kind == "rtti":
        if new_word not in RTTI_CLASSES:
            raise Refusal(f"canonical:rtti: {new_word} is not a retail RTTI class name")
    elif evidence_kind in ("vendored", "lib"):
        upstream = any(new_word in (fragments_text(r.get("name", "")) or [])
                       for r in ctx.rows() if "vendored=" in r.get("notes", "")
                       or r.get("source", "").lower().endswith(".lib"))
        if not upstream:
            cite()
    elif evidence_kind in ("zh", "bfme1"):
        path = cite()
        if evidence_kind == "zh" and "CnC_Generals_Zero_Hour" not in path:
            raise Refusal(f"canonical:zh must cite a file in the Zero Hour tree ({BFME1}/{ZH_TREE})")
        if evidence_kind == "bfme1":
            if not path.startswith(BFME1 + "/"):
                raise Refusal(f"canonical:bfme1 must cite a file under {BFME1}/")
            if re.match(rf"{re.escape(BFME1)}/targets/[^/]+/reverse/", path) and \
                    posixpath.basename(path) != "ea_evidence.csv":
                raise Refusal(f"canonical:bfme1 may not cite {path}: BFME 1's ledgers hold names agents "
                              "chose; cite its ea_evidence.csv or a Zero Hour line")
        graded(evidence_kind)
    elif evidence_kind in ("string", "assert"):
        at = cited_rva()
        if at is None:
            raise Refusal(f"canonical:{evidence_kind} needs --evidence citing 0x<rva> of the renamed "
                          f"function's retail string in {STRING_XREFS}")
        if kind in ("function", "global"):
            if rva is None or at != rva:
                raise Refusal(f"canonical:{evidence_kind} must cite the renamed row's own address"
                              + (f" 0x{rva:08X}" if rva is not None else "") + f", not 0x{at:08X}")
        elif kind == "class":
            scoped = [r for r in ctx.rows() if _rva(r.get("target_rva")) == at
                      and (scope_of(r.get("name", "")) or "").split("::")[:-1][-1:] == [old_word]]
            if not old_word or not scoped:
                raise Refusal(f"canonical:{evidence_kind}: no function of {old_word} is at 0x{at:08X}")
        else:
            raise Refusal(f"canonical:{evidence_kind} names functions, globals and classes, not a {kind}")
        spelled = word_re(new_word)
        found = False
        for line in (ctx.read(STRING_XREFS) or b"").decode("utf-8", errors="replace").splitlines():
            if "\t" not in line:
                continue
            text, refs = line.rsplit("\t", 1)
            if at in {_rva(x.strip()) for x in refs.split(",")} and spelled.search(text):
                found = True
                break
        if not found:
            raise Refusal(f"canonical:{evidence_kind}: no retail string in {STRING_XREFS} referenced by "
                          f"0x{at:08X} spells {new_word} as a word")
    elif evidence_kind == "file":
        base = posixpath.basename(new_name).lower()
        approved = any(r.get("tu") == new_name and r.get("confidence") == "approved" for r in ctx.dicts(TU_MAP))
        retail = any(line.split("\t")[0].replace("\\", "/").lower().endswith("/" + base)
                     for line in (ctx.read(STRING_XREFS) or b"").decode("utf-8", errors="replace").splitlines())
        if kind != "file" or not (approved or retail):
            raise Refusal(f"canonical:file needs an approved {TU_MAP} TU or a retail __FILE__ path ending in "
                          f"{base}")
    elif evidence_kind == "wb":
        at = rva if rva is not None else cited_rva()
        leads = wb_rows(ctx, at) if at is not None else []
        def fits(wb):
            parts = wb.split("::")
            return parts[-1] == new_word if kind == "function" else new_word in parts[:-1]
        if kind not in ("function", "class") or not any(fits(r["wb_name"]) for r in leads):
            raise Refusal(f"canonical:wb needs a {WB_LEADS} row at the address naming {new_word}")
        graded("wb")
    else:
        raise Refusal(f"canonical:{evidence_kind} is not machine-checkable")


def check_basis(ctx, kind, basis, evidence, old_name, old_word, rva, *, new_name=None, new_word=None,
                source=None):
    """Refuse a basis that may not replace `old_name`: an inferred name needs
    the two-agent agreement record (or, for a file, a stem derived from its
    own real-named rows) and may replace only a placeholder with no evidence
    on record; a canonical basis is verified against the record it cites."""
    which = basis_kind(basis)
    ctx._cache.pop("_restoring", None)
    if not (evidence or "").strip():
        raise Refusal("--evidence is required (canonical: the evidence; inferred: the agreement record)")
    if any(c in evidence for c in "\r\n"):
        raise Refusal("--evidence must be one line")
    if which == RESTORED:
        check_restore(ctx, kind, evidence, old_name, new_name or new_word, rva)
        return which
    new_name = new_name or new_word
    new_word = new_word or new_name
    placeholder = is_placeholder(old_word, kind)
    recorded = recorded_basis(ctx, old_name) or recorded_basis(ctx, old_word)
    if which == "inferred" and not placeholder:
        raise Refusal(f"{old_word} is a real name, not a placeholder; an inferred name may replace "
                      "only a placeholder or weak name")
    if which == "canonical" and not placeholder and not (recorded or "").startswith("inferred"):
        raise Refusal(f"{old_word} is a real name that name_basis.csv does not record as inferred; "
                      "a canonical name may replace only a placeholder or an inferred name")
    if which == "inferred":
        inferred_guards(ctx, kind, old_name, old_word, rva)
        if evidence.strip().startswith("mechanical:"):
            if kind != "file":
                raise Refusal("mechanical: evidence names a file from its own rows; other kinds need agree:<id>")
            stem = posixpath.splitext(posixpath.basename(new_name or ""))[0]
            if stem.lower() not in mechanical_stems(ctx, source or old_name):
                raise Refusal(f"{stem} is not derived from a real-named row {source or old_name} owns "
                              "(identifier, Class, Class_method or ClassMethod)")
        else:
            check_agreement(ctx, kind, evidence, {old_name, old_word}, {new_name, new_word}, rva)
    else:
        check_canonical(ctx, kind, BASIS_RE.fullmatch(basis).group(1), evidence, new_name, new_word, rva,
                        old_word=old_word)
    return which


# ---------------------------------------------------------------- reverting an inferred name
#
# A disputed inferred name goes back to the placeholder it replaced. That one
# rename needs what every other is refused -- a placeholder as the new name,
# a non-placeholder old name, and the old (name, rva) back although its
# tombstone says it was renamed away -- so it is its own basis, `restored`,
# checked here as the exact inverse of a recorded `inferred` landing, never
# a lane-side override of the engine's checks.

def revert_id(evidence):
    match = REVERT_RE.fullmatch((evidence or "").strip())
    return match.group(1) if match else None


def word_of(kind, spelling):
    """The identifier a name_basis.csv spelling of `kind` respells."""
    if kind in ("function", "global"):
        try:
            return split_function_name(spelling)[1]
        except Refusal:
            return _identifier(spelling) or spelling
    if kind in ("member", "param", "local"):
        return spelling.rsplit("::", 1)[-1]
    return spelling


def respell(kind, spelling, word):
    """`spelling` (as name_basis.csv records it) with its identifier `word`."""
    if kind in ("function", "global"):
        return rename_function_symbol(spelling, word)
    if kind in ("member", "param", "local"):
        return f"{spelling.rsplit('::', 1)[0]}::{word}" if "::" in spelling else word
    return word


@dataclass
class Landing:
    """A recorded inferred rename and where its name stands now."""
    record: str
    kind: str
    placeholder: str      # the old word the landing replaced
    landed: str           # the word it landed
    current: str          # the landed spelling now (after carry rows)
    target: str           # that spelling with the placeholder back
    rva: object
    source: str


def landing(ctx, record):
    """The inferred rename `agree:<record>` landed, not yet restored. Carry
    rows (a renamed class or function respelling this record's scope) are
    followed to its current spelling."""
    rows = name_basis_rows(ctx)
    found = [i for i, r in enumerate(rows) if r.get("basis") == "inferred"
             and (r.get("evidence") or "").strip() == f"agree:{record}"]
    if not found:
        raise Refusal(f"no inferred rename with evidence agree:{record} is recorded in {NAME_BASIS}")
    at = found[-1]
    row = rows[at]
    kind = row.get("kind", "")
    if kind not in ("function", "global", "class", "member", "param", "local"):
        raise Refusal(f"agree:{record} renamed a {kind}; only lane kinds are reverted")
    if any(r.get("basis") == RESTORED and revert_id(r.get("evidence")) == record for r in rows[at + 1:]):
        raise Refusal(f"agree:{record} was already reverted")
    current = row.get("new", "")
    for r in rows[at + 1:]:
        if r.get("kind") == "carry" and r.get("old") == current:
            current = r.get("new", "")
    placeholder, landed = word_of(kind, row.get("old", "")), word_of(kind, row.get("new", ""))
    if word_of(kind, current) != landed:
        raise Refusal(f"agree:{record}'s name {landed} has since been respelled ({current}); revert that first")
    return Landing(record, kind, placeholder, landed, current, respell(kind, current, placeholder),
                   _rva(row.get("rva")), row.get("source", ""))


def check_restore(ctx, kind, evidence, old_name, new_name, rva):
    """Basis `restored`: --evidence `revert:<id> <reason>` names an inferred
    landing that this rename exactly inverts (same kind, its current spelling
    to the placeholder it replaced, same address)."""
    match = REVERT_RE.fullmatch(evidence.strip())
    if not match or not match.group(2):
        raise Refusal("basis restored needs --evidence 'revert:<agreement id> <reason>' "
                      "(python3 tools/rename.py revert --record <id> --reason ...)")
    land = landing(ctx, match.group(1))
    problems = []
    if land.kind != kind:
        problems.append(f"it renamed a {land.kind}, not a {kind}")
    if old_name != land.current:
        problems.append(f"its name is now {land.current}, not {old_name}")
    if new_name != land.target:
        problems.append(f"it replaced {land.target}, not {new_name}")
    if rva is not None and land.rva is not None and rva != land.rva:
        problems.append(f"it is at 0x{land.rva:08X}")
    if problems:
        raise Refusal(f"revert:{land.record} is not the exact inverse of that rename: {'; '.join(problems)}")
    ctx._cache["_restoring"] = (land.kind, land.landed, land.placeholder, land.rva)


def restore_lifts(ctx, kind, landed, placeholder, rva):
    """{(name, rva): line} of the deleted_rows.csv tombstones the landing of
    `landed` over `placeholder` wrote ('Renamed to <T> by tools/rename.py
    (inferred)' where <T> respelled back is the tombstoned name)."""
    out = {}
    if kind not in ("function", "global", "class"):
        return out
    raw = ctx.read(DELETED)
    if raw is None:
        return out
    pattern = re.compile(rf"(?<![A-Za-z0-9_]){re.escape(landed)}(?=@)")
    for line in raw.decode("utf-8", errors="surrogateescape").splitlines():
        if not line.strip() or line.startswith(("#", "name,")):
            continue
        row = next(csv.reader(io.StringIO(line)), [])
        if len(row) < 3 or _rva(row[1]) is None:
            continue
        target = LANDED_TOMBSTONE.match(row[2])
        if not target:
            continue
        if kind == "class":
            try:
                back = class_sub(target.group(1), landed, placeholder)[0]
            except Unparsed:
                continue
        else:
            back = pattern.sub(placeholder, target.group(1), count=1)
            if rva is not None and _rva(row[1]) != rva and not row[0].startswith(FUNCLET_PREFIXES):
                continue
        if back == row[0] and back != target.group(1):
            out[(row[0], _rva(row[1]))] = line
    return out


def lifted_tombstones(ctx):
    """{(name, rva): line} that recorded restores (and one being planned)
    took back out of deleted_rows.csv: rename.py honours them even if a union
    merge brings a line back (check_csv does not; `rename.py check` reports it)."""
    out = {}
    specs = [(r.get("kind"), word_of(r.get("kind"), r.get("old", "")), word_of(r.get("kind"), r.get("new", "")),
              _rva(r.get("rva"))) for r in name_basis_rows(ctx) if r.get("basis") == RESTORED]
    if ctx._cache.get("_restoring"):
        specs.append(ctx._cache["_restoring"])
    for spec in specs:
        out.update(restore_lifts(ctx, *spec))
    return out


def revert(ctx, record, reason, *, function=None, **run_kwargs):
    """Put the placeholder back over the inferred name `agree:<record>`
    landed: the exact inverse, through run() like any rename (claims,
    byte verification, restore on failure), recorded append-only in
    name_basis.csv as basis `restored`, with the landing's tombstones lifted
    and the landed name tombstoned in turn. `function` (Class::method#2)
    supplies the overload index of a param's or local's function; the scope
    itself comes from the record, carry rows followed."""
    reason = " ".join((reason or "").split())
    if not reason:
        raise Refusal("a revert needs --reason: what the code shows against the landed name")
    land = landing(ctx, record)
    evidence = f"revert:{record} {reason}"
    common = dict(basis=RESTORED, evidence=evidence)
    if land.kind == "function":
        if land.rva is None:
            raise Refusal(f"agree:{record} recorded no address")
        kwargs = dict(rva=land.rva, new=land.placeholder, old=land.current)
    elif land.kind in ("global", "class"):
        kwargs = dict(name=land.current, new=land.placeholder)
    elif land.kind == "member":
        kwargs = dict(cls=land.current.rsplit("::", 1)[0], member=land.landed, new=land.placeholder)
    else:
        scope = land.current.rsplit("::", 1)[0]
        # an overload index (#N) from the caller survives a respelled scope
        overload = function.rsplit("#", 1)[1] if function and "#" in function else None
        kwargs = dict(source=land.source, name=land.landed, new=land.placeholder,
                      function=f"{scope}#{overload}" if overload else scope)
    return run(land.kind, ctx, **common, **kwargs, **run_kwargs)


def includers(ctx, paths, limit):
    """Ledger sources that #include any of `paths` by file name, transitively.
    Names match case-insensitively on the basename, so doubt widens the set."""
    seen, frontier, found = set(paths), set(paths), set()
    while frontier:
        names = sorted({Path(p).name for p in frontier})
        frontier = set()
        pattern = r"#[[:space:]]*include[[:space:]]*[<\"]([^>\"]*/)?(%s)[>\"]" % "|".join(
            re.escape(n) for n in names)
        hits = ctx.git("grep", "-l", "-i", "-E", "-e", pattern, "--", *SEARCH_ROOTS).splitlines()
        for hit in hits:
            if hit in seen:
                continue
            seen.add(hit)
            if hit in ctx.ledger_sources():
                found.add(hit)
            if not hit.endswith(SOURCE_SUFFIXES) or hit not in ctx.ledger_sources():
                frontier.add(hit)
        if len(found) > limit:
            raise Refusal(f"touched headers reach more than {limit} ledger sources; "
                          "this tool has no batch mode: pass a larger --max-files (every unit is still verified) or leave the name")
    return found


def object_referencers(ctx, symbol):
    """Sources whose cached objects reference `symbol` (name_dependents' scan,
    which falls back to the source text where no current object exists)."""
    if not ctx.object_scan:
        return set()
    import name_dependents
    return name_dependents.dependents({symbol}, name_dependents._row_objects(ctx.rows()), ctx.root)


def alias_pins(ctx, old_name, rva):
    """symbols.csv pins at `rva` that spell the same qualified function as
    `old_name` under another mangled signature (a caller unit's private view
    of the class mangles back-references in its own order)."""
    scope = scope_of(old_name)
    out = set()
    for pin in ctx.pins():
        name = pin.get("name", "")
        if name == old_name or _rva(pin.get("address")) != rva or not name.startswith("?"):
            continue
        try:
            split_function_name(name)
        except Refusal:
            continue
        if scope and scope_of(name) == scope:
            out.add(name)
    return sorted(out)


def shared_identifier(ctx, word, own_re):
    """Another ledger, pin or data symbol whose spelling contains `word` as a
    name fragment (an identifier, scope or type), or None. Symbols `own_re`
    matches -- the renamed name and funclets embedding it -- are ours."""
    names = [r["name"] for r in ctx.rows()] + [p.get("name", "") for p in ctx.pins()] + \
        [d.get("name", "") for d in ctx.dicts(DATA_ROWS)]
    for other in names:
        if not other or word not in other or own_re.search(other):
            continue
        try:
            spans = fragments(other)
        except Unparsed:
            if re.search(r"(?<![A-Za-z0-9_])%s(?![A-Za-z0-9_])" % re.escape(word), other):
                return other      # unreadable, and it may spell the word: refuse
            continue
        if any(other[a:b] == word for a, b in spans):
            return other
    return None


def frozen_mentions(ctx, symbol):
    return ctx.grep_files(symbol, roots=FROZEN_KEYED)


def enclosing_types(code):
    """{body start: innermost enclosing type name or None} for every
    class/struct/union body in stripped `code`, with the body names."""
    bodies = type_bodies(code)
    out = []
    for name, start, end in bodies:
        outer = [(s, n) for n, s, e in bodies if s < start and end <= e and (s, e) != (start, end)]
        out.append((name, start, end, max(outer)[1] if outer else None))
    return out


def foreign_declarations(code, word, cls, kind="function"):
    """How stripped `code` declares `word` as something other than the
    renamed entity: a type, typedef or enumerator, a data member, a method of
    another class, a function of another scope, a global (for a function), a
    parameter or a local. `cls` is the renamed function's class (None for a
    free function or a global)."""
    found = []
    pattern = re.escape(word)
    if declares_type(code, word) or re.search(r"\b(?:class|struct|union|enum)\s+%s\s*;" % pattern, code):
        found.append("a type")
    if re.search(r"\btypedef\b[^;{}]*\b%s\s*(?:\[[^\]]*\]\s*)*;" % pattern, code) or \
            re.search(r"\(\s*\*\s*%s\s*\)" % pattern, code):
        found.append("a typedef or function pointer")
    for body in re.finditer(r"\benum\b[^;{()]*\{([^{}]*)\}", code):
        if re.search(r"(?:^|,)\s*%s\s*(?:=|,|$)" % pattern, body.group(1).strip()):
            found.append("an enumerator")
    bodies = enclosing_types(code)
    for name, start, end, _outer in bodies:
        flat = flatten(code[start:end])
        if member_statements(code[start:end], word):
            found.append(f"a data member of {name}")
        elif name != cls and re.search(r"(?<![\w:.>~])%s\s*\(" % pattern, flat):
            found.append(f"a method of {name}")
    for scope, start, _end, _params in name_metric.functions_in(code):
        base = scope.split("#")[0]
        if base.split("::")[-1] != word:
            continue
        inside = [n for n, s, e, _o in bodies if s <= start < e]
        owner = "::".join(base.split("::")[:-1]) or (inside[-1] if inside else None)
        if kind == "global" or (owner or None) != (cls or None) and \
                (owner or "").split("::")[-1] != (cls or ""):
            found.append(f"a function of {owner or 'the global scope'}")
    if kind != "global" and word in set(name_metric.global_names(code)):
        found.append("a global")
    for scope, start, end, params in name_metric.functions_in(code):
        if word in set(parameters(params)):
            found.append(f"a parameter of {scope}")
        if word in set(name_metric.local_names(code[code.find("{", start):end])):
            found.append(f"a local of {scope}")
    return found


def rewrite_units(ctx, plan, old_word, new_word, old_name, new_name, owner_source, max_files, *,
                  cls=None, kind="function", aliases=None):
    """Rewrite `old_word` in the owner, every file that spells it and every
    unit whose object references `old_name`; returns the ledger sources the
    build must verify (rewritten units, the owner, includers of a rewritten
    header). A word rewrite is whole-word, so a file that also declares the
    word as anything else (foreign_declarations) is refused."""
    touched = set(ctx.grep_files(old_word, word=True)) | {owner_source}
    by_object = object_referencers(ctx, old_name)
    for alias in aliases or ():
        by_object |= object_referencers(ctx, alias)
    touched |= by_object
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) name {old_word}: {', '.join(generated[:5])}; "
                      "the rename would leave them stale and they are never edited")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files name {old_word} (over --max-files {max_files})")
    headers = []
    for rel in sorted(touched):
        data = ctx.read(rel)
        if data is None:
            raise Refusal(f"{rel} is listed but missing")
        text = data.decode("utf-8", errors="surrogateescape")
        if code_mentions(text, new_word):
            raise Refusal(f"{new_word} is already a name in {rel}")
        foreign = foreign_declarations(name_metric.strip(text), old_word, cls, kind)
        if foreign:
            raise Refusal(f"{rel} also declares {old_word} as {foreign[0]}; a word rewrite would rename "
                          "it too")
        new_text, counts, strings = rewrite_source(text, old_word, new_word, old_name, new_name)
        for alias, renamed in (aliases or {}).items():
            # a whole alias spelling in a comment or pragma (the word rewrite
            # leaves comments alone)
            new_text, n = mangled_re(alias).subn(lambda _m, r=renamed: r, new_text)
            counts["comment"] += n
        if strings:
            raise Refusal(f"{old_word} is spelled inside a string literal in {rel}: {strings[0][:80]} "
                          "(retail-locked text)")
        if new_text == text:
            if rel in by_object:
                raise Refusal(f"{rel}'s object references {old_name} but its text never spells "
                              f"{old_word} (a macro or generated name): cannot rewrite it")
            continue
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    verify.add(owner_source)
    if headers:
        verify |= includers(ctx, headers, max_files)
    return verify


def plan_function(ctx, rva, new, basis, evidence, *, old=None, max_files=25):
    """Plan respelling one RVA's function identifier everywhere it is named."""
    rows = [r for r in ctx.rows() if _rva(r.get("target_rva")) == rva]
    if not rows:
        raise Refusal(f"no functions.csv row at 0x{rva:08X}")
    owners = [r for r in rows if not r["name"].startswith(("__ehhandler$", "__unwindfunclet$", "$L"))
              and "parent=" not in r.get("notes", "")]
    if old:
        owners = [r for r in owners if r["name"] == old]
        if not owners:
            raise Refusal(f"{old} has no row at 0x{rva:08X}")
    names = sorted({r["name"] for r in owners})
    if len(names) != 1:
        raise Refusal(f"0x{rva:08X} carries {len(names)} function names ({', '.join(names) or 'none'}); "
                      "pass --old to choose one")
    old_name = names[0]
    owner = owners[0]
    if is_generated(owner["source"]):
        raise Refusal(f"{old_name} lives in generated source {owner['source']}; "
                      "recover it as real C++ first (never edit Code/gen_*)")
    prefix, old_word, _ = split_function_name(old_name)
    new = new or ""
    if new.startswith("?"):
        # a full mangled spelling: it must equal the identifier-only rewrite
        new_word = split_function_name(new)[1]
        if new_word == old_word:
            raise Refusal("the new name is the old name")
        if rename_function_symbol(old_name, new_word) != new:
            raise Refusal(f"{new} changes the mangled signature beyond the identifier "
                          f"(identifier-only rewrite is {rename_function_symbol(old_name, new_word)})")
    else:
        new_word = new
    check_new_identifier(new_word, "function", basis)
    if new_word == old_word:
        raise Refusal("the new name is the old name")
    new_name = rename_function_symbol(old_name, new_word)

    reason = is_protected(ctx, "function", old_name, rva=rva, identifier=old_word)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    refuse_vendored(ctx, [owner["source"]], f"renaming {old_name}")
    which = check_basis(ctx, "function", basis, evidence, old_name, old_word, rva, new_name=new_name,
                        new_word=new_word)

    # Collisions: one name, one identity.
    if any(r["name"] == new_name for r in ctx.rows()) or any(p.get("name") == new_name for p in ctx.pins()):
        raise Refusal(f"{new_name} already names a row or pin")
    tombstoned = _tombstones(ctx)
    if (new_name, rva) in tombstoned:
        raise Refusal(f"({new_name}, 0x{rva:08X}) is tombstoned in deleted_rows.csv: "
                      f"{tombstoned[(new_name, rva)][:120]}")
    # The identifier must denote only this function, or a word rewrite renames
    # something else too.
    old_re = mangled_re(old_name)
    statics = sorted(d.get("name", "") for d in ctx.dicts(DATA_ROWS) if old_re.search(d.get("name", "")))
    if statics:
        raise Refusal(f"data row {statics[0]} (a local static) embeds {old_name}; the function kind does not "
                      "rename data rows -- rename the static with the global kind's review first")
    # A caller unit that declares the function in its own view of the class
    # can mangle it differently (another back-reference order) and binds
    # through a pin at this same address: the same identity, so the same
    # rename. Only a pin at the address with the same qualified identifier
    # qualifies; anything else spelling the word is still refused below.
    aliases = alias_pins(ctx, old_name, rva)
    for alias in aliases:
        renamed = rename_function_symbol(alias, new_word)
        if any(r["name"] == renamed for r in ctx.rows()) or any(p.get("name") == renamed for p in ctx.pins()):
            raise Refusal(f"{renamed} (the alias pin {alias} renamed) already names a row or pin")
    own_re = re.compile("|".join(mangled_re(n).pattern for n in [old_name] + aliases))
    other = shared_identifier(ctx, old_word, own_re)
    if other:
        raise Refusal(f"{old_word} also spells {other}; a word rewrite would rename it too")
    frozen = frozen_mentions(ctx, old_name)
    if frozen:
        raise Refusal(f"{old_name} is a key in {', '.join(frozen)} (frozen, shrink-only); "
                      "renaming it needs a Verifier-Change commit")

    plan = Plan("function", old_name, new_name, basis, evidence.strip(), owner["source"], rva,
                old_word=old_word, new_word=new_word)

    # Ledgers.
    raw = ctx.read(FUNCTIONS)
    new_raw, changed = rewrite_records(raw, "functions.csv", old_re, new_name)
    for before, after in changed:
        at = _rva(before[2])
        if before[0] != after[0]:
            plan.renamed_rows.append((before[0], after[0], at))
        else:
            plan.notes_rows.append((before[0], at))
    for alias in aliases:
        new_raw, changed = rewrite_records(new_raw, "functions.csv", mangled_re(alias),
                                           rename_function_symbol(alias, new_word))
        for before, after in changed:
            if before[0] != after[0]:
                raise Refusal(f"functions.csv row {before[0]} embeds the alias pin {alias} in its name")
            plan.notes_rows.append((before[0], _rva(before[2])))
    plan.edit(ctx, FUNCTIONS, new_raw)
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        new_raw, changed = rewrite_records(raw, "symbols.csv", old_re, new_name)
        for before, after in changed:
            plan.renamed_pins.append((before[0], after[0], before[1]))
        for alias in aliases:
            new_raw, changed_alias = rewrite_records(new_raw, "symbols.csv", mangled_re(alias),
                                                     rename_function_symbol(alias, new_word))
            for before, after in changed_alias:
                plan.renamed_pins.append((before[0], after[0], before[1]))
            changed = changed + changed_alias
        if changed:
            plan.edit(ctx, SYMBOLS, new_raw)
        others = sorted({p["name"] for p in ctx.pins() if _rva(p.get("address")) == rva
                         and p.get("name") != old_name and not own_re.search(p.get("name", ""))})
        for name in others:
            plan.warnings.append(f"pin {name} also names 0x{rva:08X} (not renamed; one address, one name)")
    # check_csv.check_body_owners: an audited owner's name must equal its row's.
    for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", old_re, new_name):
        plan.owner_rows.append((before[1], _rva(before[0])))
    reason_text = f"Renamed to {{new}} by tools/rename.py ({basis})"
    for old_row, new_row, at in plan.renamed_rows:
        if (old_row, at) in tombstoned:
            continue
        plan.edit(ctx, DELETED, appended(plan.after.get(DELETED, ctx.read(DELETED)),
                                         [tombstone_line(old_row, at, reason_text.format(new=new_row))],
                                         header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["function", old_name, new_name, basis, plan.evidence, owner["source"], f"0x{rva:08X}"])],
        header=NAME_BASIS_HEADER))

    old_scope, new_scope = scope_of(old_name), scope_of(new_name)

    def carried(spelling):
        if old_re.search(spelling):
            return old_re.sub(lambda _m: new_name, spelling)
        if old_scope and new_scope and spelling.startswith(old_scope + "::"):
            return new_scope + spelling[len(old_scope):]
        return None
    carry_records(ctx, plan, carried)
    scope = scope_of(old_name) or ""
    verify = rewrite_units(ctx, plan, old_word, new_word, old_name, new_name, owner["source"], max_files,
                           cls=scope.rsplit("::", 1)[0].split("::")[-1] if "::" in scope else None,
                           aliases={a: rename_function_symbol(a, new_word) for a in aliases})
    verify |= {r["source"] for r in ctx.rows() if r["name"] in {o for o, _, _ in plan.renamed_rows}}
    verify |= {r["source"] for r in ctx.rows()
               if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")

    plan.claims = sorted({at for _, _, at in plan.renamed_rows} | {at for _, at in plan.notes_rows}) + \
        [f"file:{owner['source']}"]
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted(set(ctx.grep_files(old_name, roots=("docs", "reverse"))) - edited) + \
        sorted(set(ctx.grep_files(old_word, word=True, roots=("docs",))) - edited
               - set(ctx.grep_files(old_name, roots=("docs",))))
    return plan


# ---------------------------------------------------------------- globals

def data_rva(row):
    """A data_rows.csv row's RVA (its address read the way address_kind says)."""
    address = _rva(row.get("address"))
    if address is None:
        return None
    return address - IMAGE_BASE if row.get("address_kind") == "va" else address


def _identifier(symbol):
    try:
        return split_function_name(symbol)[1]
    except Refusal:
        return None


def plan_global(ctx, name, new, basis, evidence, *, max_files=25):
    """Plan respelling one reverse/data_rows.csv global everywhere it is named.

    The byte gate masks DIR32 operands, so a consumer left on the old name
    still byte-matches and only the link breaks: the plan has to find every
    consumer itself, by text and by object symbol table, and refuses when it
    cannot rewrite one."""
    rows = ctx.dicts(DATA_ROWS)
    if name.startswith("?") or "@" in name:
        owners = [r for r in rows if r.get("name") == name]
    else:
        owners = [r for r in rows if r.get("name") == name or _identifier(r.get("name", "")) == name]
    if not owners:
        raise Refusal(f"no reverse/data_rows.csv row names {name}")
    names = sorted({r["name"] for r in owners})
    if len(names) != 1:
        raise Refusal(f"{name} matches {len(names)} data rows ({', '.join(names[:4])}); "
                      "pass the mangled name")
    old_name = names[0]
    if len(owners) != 1:
        raise Refusal(f"{old_name} has {len(owners)} data_rows.csv rows; rename needs one global, one row")
    owner = owners[0]
    rva = data_rva(owner)
    if rva is None:
        raise Refusal(f"{old_name}'s data row has no readable address")
    source = owner.get("source", "")
    if is_generated(source):
        raise Refusal(f"{old_name} lives in generated source {source} (never edit Code/gen_*)")
    if source not in ctx.ledger_sources():
        raise Refusal(f"{source} owns no matched function row; ./build.sh could not verify the rename")
    if old_name.startswith("??"):
        raise Refusal(f"{old_name} is a compiler-named datum (vftable, RTTI, local static); "
                      "rename its class or function instead")
    _prefix, old_word, _ = split_function_name(old_name)
    new = new or ""
    if new.startswith("?") or "@" in new:
        new_word = _identifier(new)
        if not new_word or rename_function_symbol(old_name, new_word) != new:
            raise Refusal(f"{new} changes the mangled data symbol beyond the identifier")
    else:
        new_word = new
    check_new_identifier(new_word, "global", basis)
    if new_word == old_word:
        raise Refusal("the new name is the old name")
    new_name = rename_function_symbol(old_name, new_word)

    reason = is_protected(ctx, "global", old_name, rva=rva, identifier=old_word)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    for row in ctx.dicts(CONVERGED):
        if _rva(row.get("address")) == rva:
            raise Refusal(f"0x{rva:08X} is a converged address (reverse/data_converged.csv binds "
                          f"{row.get('name')}); data_check --converged refuses renaming it")
    refuse_vendored(ctx, [source], f"renaming {old_name}")
    which = check_basis(ctx, "global", basis, evidence, old_name, old_word, rva, new_name=new_name,
                        new_word=new_word)

    if any(r.get("name") == new_name for r in rows) or any(r["name"] == new_name for r in ctx.rows()) \
            or any(p.get("name") == new_name for p in ctx.pins()):
        raise Refusal(f"{new_name} already names a data row, function or pin")
    clash = shared_identifier(ctx, new_word, re.compile(r"(?!)"))
    if clash:
        raise Refusal(f"{new_word} already spells {clash}")
    old_re = mangled_re(old_name)
    other = shared_identifier(ctx, old_word, old_re)
    if other:
        raise Refusal(f"{old_word} also spells {other}; a word rewrite would rename it too")
    frozen = [rel for rel in frozen_mentions(ctx, old_name) if rel != DATA_LEDGER]
    if frozen:
        raise Refusal(f"{old_name} is a key in {', '.join(frozen)} (frozen, shrink-only); "
                      "renaming it needs a Verifier-Change commit")

    plan = Plan("global", old_name, new_name, basis, evidence.strip(), source, rva,
                old_word=old_word, new_word=new_word)
    raw = ctx.read(DATA_ROWS)
    new_raw, changed = rewrite_records(raw, "data_rows.csv", old_re, new_name)
    for before, after in changed:
        if before[0] != after[0]:
            plan.renamed_data.append((before[0], after[0], rva))
    plan.edit(ctx, DATA_ROWS, new_raw)
    raw = ctx.read(FUNCTIONS)
    new_raw, changed = rewrite_records(raw, "functions.csv", old_re, new_name)
    for before, after in changed:
        if before[0] != after[0]:
            raise Refusal(f"functions.csv row {before[0]} embeds {old_name} in its name")
        plan.notes_rows.append((before[0], _rva(before[2])))
    if changed:
        plan.edit(ctx, FUNCTIONS, new_raw)
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        new_raw, changed = rewrite_records(raw, "symbols.csv", old_re, new_name)
        for before, after in changed:
            plan.renamed_pins.append((before[0], after[0], before[1]))
        if changed:
            plan.edit(ctx, SYMBOLS, new_raw)
    tombstoned = _tombstones(ctx)
    reason_text = f"Renamed to {new_name} by tools/rename.py ({basis})"
    if (old_name, rva) not in tombstoned:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), [tombstone_line(old_name, rva, reason_text)],
                                         header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["global", old_name, new_name, basis, plan.evidence, source, f"0x{rva:08X}"])],
        header=NAME_BASIS_HEADER))

    verify = rewrite_units(ctx, plan, old_word, new_word, old_name, new_name, source, max_files,
                           kind="global")
    verify |= {r["source"] for r in ctx.rows()
               if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.claims = sorted({rva} | {at for _, at in plan.notes_rows if at is not None}) + [f"file:{source}"]
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    if ctx.read(DATA_LEDGER) is not None and old_name.encode() in ctx.read(DATA_LEDGER):
        plan.warnings.append(f"{DATA_LEDGER} (tool-written, protected) still spells {old_name}; "
                             "data_check reads it in shadow mode until tools/data_ledger.py regenerates "
                             "it in a Verifier-Change commit")
    plan.mentions = sorted(set(ctx.grep_files(old_name, roots=("docs", "reverse"))) - edited) + \
        sorted(set(ctx.grep_files(old_word, word=True, roots=("docs",))) - edited
               - set(ctx.grep_files(old_name, roots=("docs",))))
    plan.warnings.append("the byte gate masks DIR32: a consumer the plan missed would still match; "
                         "the link census is the backstop")
    return plan


# ---------------------------------------------------------------- files

def field_spans(text):
    """(start, end) of each field of one CSV record, quotes included."""
    spans, i, n = [], 0, len(text)
    while True:
        start = i
        if i < n and text[i] == '"':
            i += 1
            while i < n:
                if text[i] == '"':
                    if i + 1 < n and text[i + 1] == '"':
                        i += 2
                        continue
                    i += 1
                    break
                i += 1
        while i < n and text[i] != ",":
            i += 1
        spans.append((start, i))
        if i >= n:
            return spans
        i += 1


def repoint_column(raw, label, column, old, new):
    """`raw` with every record whose `column` field is exactly `old` changed
    to `new`; returns (new_raw, count). Every other byte is kept."""
    ledger_io.lf_terminator(raw, label)
    if old.encode("utf-8") not in raw:
        return raw, 0
    records = ledger_io.split_records(raw)
    header = ledger_io.fields(records[0][0]) if records else []
    if column not in header:
        raise Refusal(f"{label} has no {column!r} column")
    index = header.index(column)
    out, count, needle = [records[0][0] + records[0][1]], 0, old.encode("utf-8")
    for payload, term in records[1:]:
        if needle in payload:
            text = payload.decode("utf-8")
            spans = field_spans(text)
            if len(spans) > index:
                start, end = spans[index]
                value = text[start:end]
                if value in (old, f'"{old}"'):
                    payload = (text[:start] + value.replace(old, new) + text[end:]).encode("utf-8")
                    count += 1
        out.append(payload + term)
    return b"".join(out), count


def path_keyed_lines(ctx, rel, path):
    """1-based lines of `rel` with a tab- or comma-separated field equal to `path`."""
    raw = ctx.read(rel)
    if raw is None or path.encode("utf-8") not in raw:
        return []
    return [number for number, line in enumerate(raw.decode("utf-8", errors="replace").splitlines(), 1)
            if path in re.split(r"[\t,]", line)]


def plan_file(ctx, source, new, basis, evidence, *, max_files=25):
    """Plan `git mv` of one Code/ unit within its directory, with every
    path-keyed ledger column that names it.

    Phase 1 keeps the directory: a move across directories changes the flag
    region's default flags and the TU placement, which are judgements, not
    renames. It refuses a unit any protected, path-keyed register lists
    (flag_overrides.csv is tool-owned, the baselines are shrink-only and
    data_ledger.csv is tool-written): re-keying those is a Verifier-Change
    commit, and a stale key there would silently stop excusing or configuring
    the unit."""
    old = (source or "").replace("\\", "/")
    if not old.startswith("Code/"):
        raise Refusal(f"{old} is not under Code/")
    if is_generated(old):
        raise Refusal(f"{old} is a generated source (never renamed or edited)")
    suffix = posixpath.splitext(old)[1]
    if suffix not in SOURCE_SUFFIXES:
        raise Refusal(f"{old}: phase 1 renames .cpp/.c units only (a header rename rewrites its includers)")
    data = ctx.read(old)
    if data is None:
        raise Refusal(f"{old} does not exist")
    if ctx.git("ls-files", "--", old).strip() != old:
        raise Refusal(f"{old} is not tracked")
    new = (new or "").replace("\\", "/")
    if "/" not in new:
        new = posixpath.join(posixpath.dirname(old), new)
    if not posixpath.splitext(new)[1]:
        new += suffix
    if posixpath.splitext(new)[1] != suffix:
        raise Refusal(f"{new} changes the file type ({suffix})")
    if posixpath.dirname(new) != posixpath.dirname(old):
        raise Refusal("phase 1 renames within one directory: a move changes the region's default "
                      "flags and the TU placement")
    old_stem, new_stem = posixpath.splitext(posixpath.basename(old))[0], \
        posixpath.splitext(posixpath.basename(new))[0]
    if new == old:
        raise Refusal("the new name is the old name")
    check_new_identifier(new_stem, "file", basis)
    taken = [p for p in ctx.git("ls-files", "--", posixpath.dirname(old) + "/").splitlines()
             if p.lower() == new.lower() and p != old]
    if taken or ctx.path(new).exists():
        raise Refusal(f"{new} already exists ({(taken or [new])[0]}); paths are compared case-insensitively")
    rows = [r for r in ctx.rows() if r.get("source") == old]
    if not any(r.get("status") == "matched" for r in rows):
        raise Refusal(f"{old} owns no matched functions.csv row; ./build.sh could not verify the rename")

    for candidate in (old, old_stem):
        recorded = recorded_basis(ctx, candidate)
        if recorded and recorded.startswith("canonical"):
            raise Refusal(f"canonical name: {candidate} is recorded canonical ({recorded}) in {NAME_BASIS}")
    if any(r.get("tu") == old and r.get("confidence") == "approved" for r in ctx.dicts(TU_MAP)):
        raise Refusal(f"canonical name: {old} is an approved retail TU in {TU_MAP}")
    refuse_vendored(ctx, [old], f"renaming {old}")
    which = check_basis(ctx, "file", basis, evidence, old, old_stem, None, new_name=new, new_word=new_stem,
                        source=old)
    keyed = {rel: lines for rel in PROTECTED_PATH_KEYED if (lines := path_keyed_lines(ctx, rel, old))}
    if keyed:
        detail = "; ".join(f"{rel} line {', '.join(map(str, lines[:3]))}" for rel, lines in keyed.items())
        raise Refusal(f"{old} is keyed in protected path-keyed files ({detail}); "
                      "renaming it needs a Verifier-Change commit")
    text = data.decode("utf-8", errors="surrogateescape")
    if "__FILE__" in name_metric.strip(text):
        raise Refusal(f"{old} expands __FILE__, which spells the path the build passes to cl: "
                      "a rename would change its bytes")
    name = posixpath.basename(old)
    pattern = r"#[[:space:]]*include[[:space:]]*[<\"]([^>\"]*/)?%s[>\"]" % re.escape(name)
    including = [p for p in ctx.git("grep", "-l", "-i", "-E", "-e", pattern, "--", *SEARCH_ROOTS).splitlines()
                 if p]
    if including:
        raise Refusal(f"{old} is #included by {', '.join(including[:3])}; phase 1 does not rewrite includes")

    plan = Plan("file", old, new, basis, evidence.strip(), new, None, old_word=old_stem, new_word=new_stem)
    plan.moves = [(old, new)]
    plan.moved_bytes[old] = data
    for rel, column in PATH_COLUMNS:
        raw = ctx.read(rel)
        if raw is None:
            continue
        new_raw, count = repoint_column(raw, rel, column, old, new)
        if count:
            plan.edit(ctx, rel, new_raw)
            plan.path_rows[rel] = count
    raw = ctx.read(SOURCES_CFG)
    if raw is not None:
        lines = raw.decode("utf-8").splitlines(keepends=True)
        hits = [i for i, line in enumerate(lines) if re.fullmatch(r"INPUT\s*\+=\s*%s\s*" % re.escape(old), line)]
        for i in hits:
            lines[i] = lines[i].replace(old, new)
        if hits:
            plan.edit(ctx, SOURCES_CFG, "".join(lines).encode("utf-8"))
            plan.path_rows[SOURCES_CFG] = len(hits)
    plan.edit(ctx, NAME_BASIS, appended(plan.after.get(NAME_BASIS, ctx.read(NAME_BASIS)), [csv_line(
        ["file", old, new, basis, plan.evidence, new, ""])], header=NAME_BASIS_HEADER))
    plan.verify = [new]
    data_rvas = {data_rva(r) for r in ctx.dicts(DATA_ROWS) if r.get("source") == old}
    plan.claims = sorted({_rva(r.get("target_rva")) for r in rows} | data_rvas - {None}) + \
        [f"file:{old}", f"file:{new}"]
    edited = set(plan.after) | {old}
    plan.mentions = sorted(set(ctx.grep_files(old, roots=("docs", "reverse", "Code", "reference/shims")))
                           - edited)
    plan.mentions += sorted(set(ctx.grep_files(name, roots=("Code", "reference/shims", "docs")))
                            - edited - set(plan.mentions))
    if LINK_STATUS in plan.mentions:
        plan.warnings.append(f"{LINK_STATUS} is census output; the next census re-keys {old}")
    return plan


# ---------------------------------------------------------------- classes

CANONICAL_CLASSES = "reverse/canonical_classes.csv"
CLASS_CONTRACTS = "reverse/class_contracts"
FLAG_OVERRIDES = "reverse/flag_overrides.csv"
# A source split for a token rewrite: whole #include lines first (their paths
# are the file kind's business), then comments and literals as SEGMENT has them.
TOKEN_SEGMENT = re.compile(r"(?m:^[ \t]*#[ \t]*include\b[^\n]*)|" + SEGMENT.pattern, re.S)
INCLUDE_LINE = re.compile(r"[ \t]*#[ \t]*include\b")
ACCESS = re.compile(r"\b(?:public|private|protected)\s*:")
OPTIMIZE = re.compile(r"[-/]O([dx12gs])$")


def type_fragment_re(word):
    """`word` as a type or scope fragment of a mangled symbol (a scope, a
    V/U/T class or W4 enum type, a template name, the class of a special
    member), read by the `fragments` tokenizer: a regex-like object."""
    return ClassToken(word)


class ClassText:
    """`word` as a C++ token in text, and as a type fragment inside every
    mangled name quoted there (comments, markers, linker pragmas,
    __identifier strings); never inside a longer identifier or as a mangled
    name's leading identifier."""

    def __init__(self, word):
        self.word = word
        self.plain = re.compile(r"(?<![A-Za-z0-9_?@$])%s(?![A-Za-z0-9_])" % re.escape(word))

    def subn(self, new, text):
        out, last, count = [], 0, 0
        for match in SYMBOL_TOKEN.finditer(text):
            plain, n = self.plain.subn(new, text[last:match.start()])
            try:
                symbol, m = class_sub(match.group(0), self.word, new)
            except Unparsed as error:
                raise Refusal(f"cannot tokenize a mangled name spelling {self.word}: {error}") from None
            out += [plain, symbol]
            count += n + m
            last = match.end()
        plain, n = self.plain.subn(new, text[last:])
        out.append(plain)
        return "".join(out), count + n

    def sub(self, new, text):
        return self.subn(new, text)[0]

    def search(self, text):
        return self.subn(self.word + "\0", text)[1] > 0


def class_token_re(word):
    return ClassText(word)


def rewrite_tokens(text, token, new_word, *, comments=True, span=None, identifiers=False):
    """Respell every `token` match in code, in comments (when `comments`) and
    in linker-pragma strings, within `span` (start, end) of `text`; with
    `identifiers` (a type token) also inside __identifier("?mangled")
    arguments, which are code references. #include lines are left alone, and
    without `identifiers` so are __identifier arguments (a member, param or
    local is never spelled in a mangled name). Returns (text, counts,
    string_hits, include_hits): any other string literal that spells the
    token is retail-locked text."""
    start, end = span or (0, len(text))
    region = text[start:end]
    out, last = [], 0
    counts = {"code": 0, "comment": 0, "pragma": 0}
    string_hits, include_hits = [], []

    def sub(part, key):
        new, n = token.subn(new_word, part)
        if n or key in counts:
            counts[key] = counts.get(key, 0) + n
        return new

    for match in TOKEN_SEGMENT.finditer(region):
        out.append(sub(region[last:match.start()], "code"))
        seg = match.group(0)
        line_start = region.rfind("\n", 0, match.start()) + 1
        if INCLUDE_LINE.match(seg):
            if token.search(seg):
                include_hits.append(seg.strip())
            out.append(seg)
        elif seg.startswith(("//", "/*")):
            out.append(sub(seg, "comment") if comments else seg)
        elif PRAGMA_LINKER.match(region, line_start):
            out.append(sub(seg, "pragma"))
        elif identifier_string(region, match.start()):
            out.append(sub(seg, "identifier") if identifiers else seg)
        else:
            if token.search(seg):
                string_hits.append(seg)
            out.append(seg)
        last = match.end()
    out.append(sub(region[last:], "code"))
    return text[:start] + "".join(out) + text[end:], counts, string_hits, include_hits


def class_protected(ctx, word):
    """Why the class/struct/enum `word` is canonical, or None: a retail RTTI or
    module class name, recorded canonical, or the scope or type of a retail
    export, a vendored= or .lib row, an evidence-tier name or a converged datum."""
    frag = type_fragment_re(word)
    if word in RTTI_CLASSES:
        return f"{word} is a retail RTTI exception class name"
    if any(row.get("name") == word for row in ctx.dicts(MODULES)):
        return f"{word} is a retail module class name (reverse/module_factory_registrations.csv)"
    basis = recorded_basis(ctx, word)
    if basis and basis.startswith("canonical"):
        return f"{word} is recorded canonical ({basis}) in reverse/name_basis.csv"
    for spelling, row in current_records(ctx).items():
        if not row.get("basis", "").startswith("canonical") or spelling == word:
            continue
        if word in spelling.split("::")[:-1] or ("@" in spelling and frag.search(spelling)):
            return f"{word} scopes {spelling}, recorded canonical ({row.get('basis')}) in reverse/name_basis.csv"
    for row in ctx.dicts(EXPORTS):
        if frag.search(row.get("name", "")):
            return f"{word} names the retail export {row['name']} (reverse/exports.csv)"
    for row in ctx.rows():
        if not frag.search(row.get("name", "")):
            continue
        if "vendored=" in row.get("notes", ""):
            return f"{word} is in the vendored= row {row['name']} (upstream's real identity)"
        if row.get("source", "").lower().endswith(".lib"):
            return f"{word} is in the .lib member {row['name']}"
    for row in ctx.dicts(NAME_TIERS):
        if row.get("name_tier") == "evidence" and frag.search(row.get("name", "")):
            return f"{word} is in the evidence-tier name {row['name']} ({row.get('evidence')})"
    for row in ctx.dicts(CONVERGED):
        if frag.search(row.get("name", "")):
            return f"{word} is in the converged global {row['name']} (reverse/data_converged.csv)"
    return None


def declares_type(code, word):
    """True when stripped `code` defines a class/struct/union/enum body named `word`."""
    return re.search(r"\b(?:class|struct|union|enum)\s+%s\b[^;{()]*\{" % re.escape(word), code) is not None


def leading_identifier(name, word):
    """True when `word` is the identifier (not a scope or type) of symbol `name`."""
    return leading_fragment(name) == word


def include_walk(ctx, paths, limit=2000):
    """Every tracked file under SEARCH_ROOTS that #includes any of `paths`,
    transitively (basename match, case-insensitive: doubt widens the set)."""
    seen, frontier = set(paths), set(paths)
    while frontier:
        names = sorted({Path(p).name for p in frontier})
        frontier = set()
        pattern = r"#[[:space:]]*include[[:space:]]*[<\"]([^>\"]*/)?(%s)[>\"]" % "|".join(
            re.escape(n) for n in names)
        for hit in ctx.git("grep", "-l", "-i", "-E", "-e", pattern, "--", *SEARCH_ROOTS).splitlines():
            if hit and hit not in seen:
                seen.add(hit)
                if not (hit.endswith(SOURCE_SUFFIXES) and hit in ctx.ledger_sources()):
                    frontier.add(hit)
        if len(seen) > limit:
            raise Refusal(f"the touched headers are included by more than {limit} files; "
                          "this tool has no batch mode: pass a larger --max-files (every unit is still verified) or leave the name")
    return seen - set(paths)


def rewrite_ledger(ctx, plan, rel, label, regex, replacement):
    """rewrite_records over one ledger; records the edit when anything changed."""
    raw = ctx.read(rel)
    if raw is None:
        return []
    new_raw, changed = rewrite_records(raw, label, regex, replacement)
    if changed:
        plan.edit(ctx, rel, new_raw)
    return changed


def plan_class(ctx, name, new, basis, evidence, *, max_files=25):
    """Plan respelling one class/struct/union/enum type token everywhere: every
    mangled name it scopes or types (functions.csv names and notes, pins, data
    rows), every source, header and shim view that spells it, and the units
    whose objects reference a renamed symbol. The rewrite is the whole token,
    so it refuses when the word also names a function or datum."""
    old = name or ""
    if not IDENT.fullmatch(old):
        raise Refusal(f"{old!r} is not a type identifier")
    check_new_identifier(new or "", "class", basis)
    if new == old:
        raise Refusal("the new name is the old name")
    reason = class_protected(ctx, old)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    if any(row.get("class") == old for row in ctx.dicts(CANONICAL_CLASSES)) or \
            ctx.path(f"{CLASS_CONTRACTS}/{old}.json").exists():
        raise Refusal(f"{old} is registered in {CANONICAL_CLASSES} / {CLASS_CONTRACTS}; its key, contract "
                      "and class_gate allowances move in a class-reconciliation commit, not here")
    which = check_basis(ctx, "class", basis, evidence, old, old, None, new_name=new, new_word=new)

    frag = type_fragment_re(old)
    token = class_token_re(old)
    names = [r["name"] for r in ctx.rows()] + [p.get("name", "") for p in ctx.pins()] + \
        [d.get("name", "") for d in ctx.dicts(DATA_ROWS)]
    scoped = sorted({n for n in names if n and frag.search(n)})
    # One token, one type: `X::Node` and `Y::Node` would both be respelled.
    enclosing = set()
    for symbol in scoped:
        spans = fragments(symbol)
        starts = {a: symbol[a:b] for a, b in spans}
        for _a, b in class_spans(symbol, old):
            enclosing.add(None if symbol[b + 1:b + 2] == "@" else starts.get(b + 1))
    for other in names:
        if other and leading_identifier(other, old):
            raise Refusal(f"{old} is also the identifier of {other}; a token rewrite would rename it too")
    # Collisions: the new token must be free everywhere a mangled name or a
    # source could spell it.
    taken = ctx.grep_files(new, word=True)
    if taken:
        raise Refusal(f"{new} already appears in {', '.join(taken[:3])}")
    new_frag = type_fragment_re(new)
    clash = next((n for n in names if n and (new_frag.search(n) or leading_identifier(n, new))), None) or \
        shared_identifier(ctx, new, re.compile(r"(?!)"))
    if clash:
        raise Refusal(f"{new} already spells {clash}")
    for rel in ctx.grep_files(old, roots=FROZEN_KEYED):
        if rel == DATA_LEDGER:
            continue
        if frag.search((ctx.read(rel) or b"").decode("utf-8", errors="replace")):
            raise Refusal(f"{old} scopes a key in {rel} (frozen, shrink-only); "
                          "renaming it needs a Verifier-Change commit")

    texts = {}
    for rel in ctx.grep_files(old):
        data = ctx.read(rel)
        if data is None:
            continue
        text = data.decode("utf-8", errors="surrogateescape")
        if token.search(text):
            texts[rel] = text
    declarers = sorted(rel for rel, text in texts.items() if declares_type(name_metric.strip(text), old))
    for text in texts.values():
        enclosing |= {outer for name, _s, _e, outer in enclosing_types(name_metric.strip(text)) if name == old}
    if len(enclosing) > 1:
        raise Refusal(f"{old} names types in {len(enclosing)} different scopes "
                      f"({', '.join(sorted(e or '<global>' for e in enclosing))}); a token rewrite would rename "
                      "them all -- phase 1 renames one type only when its spelling is unique")
    if not scoped and not declarers:
        raise Refusal(f"no class, struct, union or enum named {old} (no definition, no ledger name)")
    by_object = set()
    if ctx.object_scan and scoped:
        import name_dependents
        by_object = name_dependents.dependents(set(scoped), name_dependents._row_objects(ctx.rows()), ctx.root)
    touched = set(texts) | by_object
    refuse_vendored(ctx, touched | set(declarers), f"renaming the type {old}")
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) spell {old}: {', '.join(generated[:5])}; "
                      "the rename would leave them stale and they are never edited")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files spell {old} (over --max-files {max_files})")

    owner = next((d for d in declarers if d in ctx.ledger_sources()), declarers[0] if declarers else "")
    plan = Plan("class", old, new, basis, evidence.strip(), owner, None, old_word=old, new_word=new)

    for before, after in rewrite_ledger(ctx, plan, FUNCTIONS, "functions.csv", frag, new):
        at = _rva(before[2])
        if before[0] != after[0]:
            plan.renamed_rows.append((before[0], after[0], at))
        else:
            plan.notes_rows.append((before[0], at))
    for before, after in rewrite_ledger(ctx, plan, SYMBOLS, "symbols.csv", frag, new):
        plan.renamed_pins.append((before[0], after[0], before[1]))
    for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", frag, new):
        plan.owner_rows.append((before[1], _rva(before[0])))
    data_index = {d.get("name"): data_rva(d) for d in ctx.dicts(DATA_ROWS)}
    for before, after in rewrite_ledger(ctx, plan, DATA_ROWS, "data_rows.csv", frag, new):
        if before[0] != after[0]:
            plan.renamed_data.append((before[0], after[0], data_index.get(before[0])))
    tombstoned = _tombstones(ctx)
    lines = [tombstone_line(o, at, f"Renamed to {n} by tools/rename.py ({basis})")
             for o, n, at in plan.renamed_rows + plan.renamed_data
             if at is not None and (o, at) not in tombstoned]
    if lines:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), lines, header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["class", old, new, basis, plan.evidence, owner, ""])], header=NAME_BASIS_HEADER))

    def carried(spelling):
        if "@" in spelling or spelling.startswith("?"):
            return frag.sub(new, spelling)
        parts = spelling.split("::")
        return "::".join(new if i < len(parts) - 1 and p == old else p for i, p in enumerate(parts))
    carry_records(ctx, plan, carried)
    # A class rename that reverts an earlier one would recreate tombstoned pairs.
    for _o, n, at in plan.renamed_rows:
        if (n, at) in tombstoned:
            raise Refusal(f"({n}, 0x{at:08X}) is tombstoned in deleted_rows.csv: {tombstoned[(n, at)][:120]}")

    headers = []
    for rel in sorted(touched):
        text = texts.get(rel)
        if text is None:
            data = ctx.read(rel)
            text = data.decode("utf-8", errors="surrogateescape") if data is not None else ""
        new_text, counts, strings, includes = rewrite_tokens(text, token, new, identifiers=True)
        if strings:
            raise Refusal(f"{old} is spelled inside a string literal in {rel}: {strings[0][:80]} "
                          "(retail-locked text)")
        for line in includes:
            plan.warnings.append(f"{rel}: {line} names {old} in a path (not renamed; use the file kind)")
        if new_text == text:
            if rel in by_object:
                raise Refusal(f"{rel}'s object references a {old} symbol but its text never spells "
                              f"{old} (a macro or generated name): cannot rewrite it")
            continue
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    renamed = {o for o, _, _ in plan.renamed_rows}
    verify |= {r["source"] for r in ctx.rows() if r["name"] in renamed}
    verify |= {r["source"] for r in ctx.rows() if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    renamed_data = {o for o, _, _ in plan.renamed_data}
    verify |= {d.get("source", "") for d in ctx.dicts(DATA_ROWS) if d.get("name") in renamed_data}
    if headers:
        verify |= includers(ctx, headers, max_files)
    plan.verify = sorted(v for v in verify if v and not is_generated(v) and v in ctx.ledger_sources())
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    if not plan.verify:
        raise Refusal(f"no ledger source compiles {old}; ./build.sh could not verify the rename")

    prose = len(word_re(old).findall(plan.after.get(FUNCTIONS, b"").decode("utf-8", errors="replace")))
    if prose:
        plan.warnings.append(f"functions.csv notes still spell {old} {prose} time(s) in prose (left as written)")
    plan.claims = sorted({at for _, _, at in plan.renamed_rows if at is not None} |
                         {at for _, at in plan.notes_rows if at is not None}) + [f"class:{old}"]
    if ctx.read(DATA_LEDGER) is not None and \
            frag.search(ctx.read(DATA_LEDGER).decode("utf-8", errors="replace")):
        plan.warnings.append(f"{DATA_LEDGER} (tool-written, protected) still spells {old} symbols; "
                             "tools/data_ledger.py regenerates it in a Verifier-Change commit")
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted(set(ctx.grep_files(old, word=True, roots=("docs", "reverse"))) - edited)
    stems = sorted(rel for rel in plan.source_counts if old in Path(rel).stem)
    for rel in stems:
        plan.warnings.append(f"{rel}: its file name spells {old} (not renamed; use the file kind)")
    return plan


# ---------------------------------------------------------------- members

def flatten(body):
    """`body` with nested brace blocks collapsed to `;` (name_metric.members' view)."""
    while True:
        flat = re.sub(r"\{[^{}]*\}", ";", body)
        if flat == body:
            return body
        body = flat


def comment_mentions(data, word):
    """True when a comment in `data` (bytes) spells `word`."""
    text = (data or b"").decode("utf-8", errors="replace")
    return any(word_re(word).search(m.group(0)) for m in SEGMENT.finditer(text)
               if m.group(0).startswith(("//", "/*")))


def class_bodies(code, cls):
    """(start, end) of every class/struct/union body named `cls` in stripped `code`."""
    pattern = re.compile(r"\b(?:class|struct|union)\s+%s\b[^;{()]*\{" % re.escape(cls))
    return [(m.end(), name_metric.close(code, m.end() - 1)) for m in pattern.finditer(code)]


def type_bodies(code):
    """(name, start, end) of every class/struct/union body in stripped `code`."""
    pattern = re.compile(r"\b(?:class|struct|union)\s+([A-Za-z_]\w*)\b[^;{()]*\{")
    return [(m.group(1), m.end(), name_metric.close(code, m.end() - 1)) for m in pattern.finditer(code)]


def member_statements(body, word):
    """The declaration statements in one class body that declare data member `word`."""
    flat = ACCESS.sub(";", flatten(body))
    return [stmt for stmt in flat.split(";") if word in name_metric.members(stmt)]


def parameters(params):
    """The names a parameter list declares (`int count` counts, unlike
    name_metric.param_names, which wants two non-keyword words)."""
    for part in params.split(","):
        words = name_metric.WORD.findall(part.split("=")[0])
        if len(words) >= 2 and words[-1] not in name_metric.KEYWORDS:
            yield words[-1]


def prototype_param_spans(code, scope, params, name, skip):
    """Spans of the parameter `name` in this file's in-class declarations of
    `scope` (Class::method): a declaration with the definition's arity whose
    parameter at the same position is spelled `name`. A parameter list with
    nested parentheses or template commas is left alone (positions would be
    guesses); `skip` (start, end) is the definition itself."""
    parts = scope.split("#")[0].split("::")
    if len(parts) < 2 or "(" in params or "<" in params:
        return []
    cls, method = parts[-2], parts[-1]
    mine = [part.split("=")[0] for part in params.split(",")]
    index = [i for i, part in enumerate(mine) if name_metric.WORD.findall(part)[-1:] == [name]]
    if len(index) != 1:
        return []
    spans = []
    for tname, body_start, body_end in type_bodies(code):
        if tname != cls:
            continue
        for match in re.finditer(r"(?<![\w~])%s\s*\(" % re.escape(method), code[body_start:body_end]):
            open_ = body_start + match.end()
            close = code.find(")", open_)
            if close < 0 or close > body_end or skip[0] <= open_ < skip[1]:
                continue
            decl = code[open_:close]
            if "(" in decl or "<" in decl:
                continue
            theirs = decl.split(",")
            if len(theirs) != len(mine):
                continue
            words = name_metric.WORD.findall(theirs[index[0]].split("=")[0])
            if len(words) >= 2 and words[-1] == name:
                at = open_ + sum(len(t) + 1 for t in theirs[:index[0]])
                spans.append((at, at + len(theirs[index[0]])))
    return spans


def other_declarations(code, word, cls=None):
    """Where stripped `code` declares `word` other than as a member of `cls`."""
    found = []
    for name, start, end in type_bodies(code):
        if name != cls and member_statements(code[start:end], word):
            found.append(f"a member of {name}")
    if word in set(name_metric.global_names(code)):
        found.append("a global")
    for scope, start, end, params in name_metric.functions_in(code):
        if word in set(parameters(params)):
            found.append(f"a parameter of {scope}")
        if word in set(name_metric.local_names(code[code.find("{", start):end])):
            found.append(f"a local of {scope}")
    return found


def plan_member(ctx, cls, member, new, basis, evidence, *, max_files=25):
    """Plan respelling one non-static data member of `cls` in every view that
    declares it and every file that uses it through those views. Member names
    never reach bytes (offsets do), so no ledger row changes; the build still
    verifies every unit that compiles a touched file."""
    for word in (cls, member):
        if not IDENT.fullmatch(word or ""):
            raise Refusal(f"{word!r} is not an identifier")
    check_new_identifier(new or "", "member", basis)
    if new == member:
        raise Refusal("the new name is the old name")
    old_q, new_q = f"{cls}::{member}", f"{cls}::{new}"
    reason = is_protected(ctx, "member", old_q, identifier=member)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    which = check_basis(ctx, "member", basis, evidence, old_q, member, None, new_name=new_q, new_word=new)

    views, texts = [], {}
    for rel in sorted(set(ctx.grep_files(cls, word=True)) & set(ctx.grep_files(member, word=True))):
        text = ctx.read(rel).decode("utf-8", errors="surrogateescape")
        code = name_metric.strip(text)
        statements = [s for start, end in class_bodies(code, cls)
                      for s in member_statements(code[start:end], member)]
        if not statements:
            continue
        if any(re.search(r"\bstatic\b", s) for s in statements):
            raise Refusal(f"{old_q} is a static data member in {rel}; rename it with the global kind")
        views.append(rel)
        texts[rel] = text
    if not views:
        raise Refusal(f"no view of {cls} declares a data member {member}")
    headers = [v for v in views if not (v.endswith(SOURCE_SUFFIXES) and v in ctx.ledger_sources())]
    users = include_walk(ctx, headers) if headers else set()
    users = {rel for rel in users
             if code_mentions(ctx.read(rel).decode("utf-8", errors="surrogateescape"), member)}
    touched = set(views) | users
    refuse_vendored(ctx, touched, f"renaming {old_q}")
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) use {old_q}: {', '.join(generated[:5])} (never edited)")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files use {old_q} (over --max-files {max_files})")

    plan = Plan("member", old_q, new_q, basis, evidence.strip(), views[0], None, old_word=member, new_word=new)
    token = word_re(member)
    edited_headers = []
    for rel in sorted(touched):
        text = texts.get(rel) or ctx.read(rel).decode("utf-8", errors="surrogateescape")
        code = name_metric.strip(text)
        elsewhere = other_declarations(code, member, cls)
        if elsewhere:
            raise Refusal(f"{rel} also declares {member} as {elsewhere[0]}; a word rewrite there is ambiguous")
        if code_mentions(text, new):
            raise Refusal(f"{new} is already a name in {rel}")
        new_text, counts, strings, _includes = rewrite_tokens(text, token, new, comments=False)
        if strings:
            raise Refusal(f"{member} is spelled inside a string literal in {rel}: {strings[0][:80]}")
        if new_text == text:
            continue
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not (rel.endswith(SOURCE_SUFFIXES) and rel in ctx.ledger_sources()):
            edited_headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    if edited_headers:
        verify |= includers(ctx, edited_headers, max_files)
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if not plan.verify:
        raise Refusal(f"no ledger source compiles a view of {cls}; ./build.sh could not verify the rename")
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    for rel in sorted(rel for rel in plan.source_counts if comment_mentions(ctx.read(rel), member)):
        plan.warnings.append(f"{rel}: comments still mention {member} (left as written)")
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["member", old_q, new_q, basis, plan.evidence, views[0], ""])], header=NAME_BASIS_HEADER))
    plan.claims = [f"class:{cls}"]
    plan.mentions = sorted(set(ctx.grep_files(old_q, roots=("docs", "reverse"))) - set(plan.after))
    return plan


# ---------------------------------------------------------------- params and locals

def scope_of(mangled):
    """`Class::method` for a plain mangled function name, `Class::Class` /
    `Class::~Class` for a constructor/destructor, the bare name for a C
    symbol; None for anything else (operators, templates, labels)."""
    match = re.match(r"\?\?([01])((?:[A-Za-z_]\w*@)+)@", mangled)
    if match:
        parts = match.group(2).rstrip("@").split("@")
        cls = parts[0]
        return "::".join(reversed(parts)) + "::" + ("~" if match.group(1) == "1" else "") + cls
    match = re.match(r"\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)*)@", mangled)
    if match:
        parts = [match.group(1)] + [p for p in match.group(2).split("@") if p]
        return "::".join(reversed(parts))
    match = re.fullmatch(r"[_@]?([A-Za-z_]\w*?)(?:@\d+)?", mangled)
    return match.group(1) if match else None


def compile_flags(ctx, rel):
    """The flags build.py compiles `rel` with ('-' style), last one winning:
    build.compiler_command's base `-O2`, then on the real tree
    build.source_extra_flags (the `// cl:` line, flag_overrides.csv and the
    region default); elsewhere the `// cl:` line then any flag_overrides.csv row."""
    if ctx.root == ROOT.resolve():
        import build
        return ["-O2"] + [f.replace("/", "-", 1) if f.startswith("/") else f
                          for f in build.source_extra_flags(ROOT / rel)]
    flags = ["-O2"]
    data = ctx.read(rel) or b""
    for line in data.decode("utf-8-sig", errors="replace").splitlines():
        if line.startswith("// cl:"):
            flags += line[len("// cl:"):].split()
            break
    for row in ctx.dicts(FLAG_OVERRIDES):
        if row.get("source") == rel:
            flags += (row.get("flags") or "").split()
    return [f.replace("/", "-", 1) if f.startswith("/") else f for f in flags]


def optimized(flags):
    """False when the effective (last) optimisation level is /Od, or none is given
    (cl's own default)."""
    levels = [m.group(1) for m in (OPTIMIZE.match(f) for f in flags) if m]
    return bool(levels) and levels[-1] != "d"


def header_closure(ctx, rel, limit=400):
    """Tracked headers under SEARCH_ROOTS that `rel` #includes, transitively,
    resolved by basename (case-insensitive; doubt widens the set)."""
    if "_by_base" not in ctx._cache:
        index = {}
        for path in ctx.git("ls-files", "--", *SEARCH_ROOTS).splitlines():
            index.setdefault(Path(path).name.lower(), []).append(path)
        ctx._cache["_by_base"] = index
    index = ctx._cache["_by_base"]
    seen, frontier = set(), [rel]
    while frontier and len(seen) < limit:
        data = ctx.read(frontier.pop()) or b""
        text = data.decode("utf-8", "replace")
        for name in re.findall(r'^[ \t]*#[ \t]*include[ \t]*[<"]([^>"]+)[>"]', text, re.M):
            for path in index.get(Path(name).name.lower(), []):
                if path not in seen and path != rel:
                    seen.add(path)
                    frontier.append(path)
    return seen


def pick_function(code, function):
    """The name_metric.functions_in entry `function` names: its exact scope
    (`Class::method`, `Class::method#2` for the second overload in the file),
    or a bare method name when one function in the file has it."""
    found = name_metric.functions_in(code)
    exact = [f for f in found if f[0] == function]
    same = [f for f in found if f[0].split("#")[0] == function.split("#")[0]]
    if exact and ("#" in function or len(same) == 1):
        return exact[0]
    loose = [f for f in found if f[0].split("#")[0] == function
             or f[0].split("#")[0].split("::")[-1] == function]
    if len(loose) == 1:
        return loose[0]
    if not loose:
        raise Refusal(f"no function {function} defined in the file")
    raise Refusal(f"{function} is ambiguous here: {', '.join(f[0] for f in loose)}")


def plan_scoped(kind, ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25):
    """Plan respelling one parameter or local inside one function body. Names
    of params and locals never reach bytes under optimisation; a local under
    /Od can (frame order), so /Od files are refused for locals. The rename is
    confined to the function's text, so it refuses whenever the old word
    could mean something else there or the new word could capture a use."""
    rel = (source or "").replace("\\", "/")
    if is_generated(rel):
        raise Refusal(f"{rel} is a generated source (never edit Code/gen_*)")
    if rel not in ctx.ledger_sources():
        raise Refusal(f"{rel} owns no matched function row; ./build.sh could not verify the rename")
    for word in (name, new):
        if not IDENT.fullmatch(word or ""):
            raise Refusal(f"{word!r} is not an identifier")
    check_new_identifier(new, kind, basis)
    if new == name:
        raise Refusal("the new name is the old name")
    if function is None and rva is not None:
        scopes = {scope_of(r["name"]) for r in ctx.rows()
                  if r.get("source") == rel and _rva(r.get("target_rva")) == rva}
        scopes.discard(None)
        if len(scopes) != 1:
            raise Refusal(f"0x{rva:08X} does not name exactly one plain function in {rel}; pass --function")
        function = scopes.pop()
        overloads = [f[0] for f in name_metric.functions_in(name_metric.strip(
            ctx.read(rel).decode("utf-8", errors="surrogateescape"))) if f[0].split("#")[0] == function]
        if len(overloads) > 1:
            raise Refusal(f"{rel} defines {len(overloads)} overloads of {function} ({', '.join(overloads)}); "
                          f"0x{rva:08X} is one of them -- pass --function {function}#N for the right one "
                          "(a parameter name never reaches the bytes, so the build cannot catch a wrong pick)")
    if not function:
        raise Refusal("--function (or --rva) is required")
    text = ctx.read(rel).decode("utf-8", errors="surrogateescape")
    code = name_metric.strip(text)
    scope, start, end, params = pick_function(code, function)
    brace = code.find("{", start)
    body = code[brace:end]
    if kind == "param":
        if name not in set(parameters(params)):
            raise Refusal(f"{name} is not a parameter of {scope}")
    else:
        if name in set(parameters(params)):
            raise Refusal(f"{name} is a parameter of {scope}, not a local")
        if name not in set(name_metric.local_names(body)):
            raise Refusal(f"{name} is not a local of {scope}")
        flags = compile_flags(ctx, rel)
        if re.search(r'^[ \t]*#[ \t]*pragma[ \t]+optimize[ \t]*\([^)]*\boff\b', text, re.M):
            raise Refusal(f"{rel} turns optimisation off with #pragma optimize; a local's name can reorder "
                          "that /Od frame")
        if not optimized(flags):
            raise Refusal(f"{rel} compiles without optimisation ({' '.join(flags) or 'no /O flag'}); "
                          "renaming a local can reorder the /Od frame")
        first_use = word_re(name).search(body)
        first_decl = min((m.start(2) for m in name_metric.LOCAL.finditer(body) if m.group(2) == name),
                         default=None)
        if first_use and first_decl is not None and first_use.start() < first_decl:
            raise Refusal(f"{name} is used in {scope} before its declaration (it names something outer there)")
    old_q, new_q = f"{scope.split('#')[0]}::{name}", f"{scope.split('#')[0]}::{new}"
    reason = is_protected(ctx, kind, old_q, identifier=name)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    refuse_vendored(ctx, [rel], f"renaming {old_q}")
    which = check_basis(ctx, kind, basis, evidence, old_q, name, rva, new_name=new_q, new_word=new)
    region = code[start:end]
    if re.search(r"(?:->|\.|::)\s*%s\b" % re.escape(name), region):
        raise Refusal(f"{scope} spells {name} after ->, . or ::; it also names a member there")
    if code_mentions(text, new):
        raise Refusal(f"{new} is already a name in {rel}")
    outside = code[:start] + " " * (end - start) + code[end:]
    elsewhere = [d for d in other_declarations(outside, name) if not d.startswith(("a parameter", "a local"))]
    if elsewhere:
        raise Refusal(f"{name} is also {elsewhere[0]} in {rel}; the function may mean it")
    for header in sorted(header_closure(ctx, rel)):
        data = ctx.read(header)
        if data is not None and code_mentions(data.decode("utf-8", errors="replace"), name):
            raise Refusal(f"{name} is also spelled in included header {header}; the function may mean it")

    new_text, counts, strings, _ = rewrite_tokens(text, word_re(name), new, span=(start, end))
    if strings:
        raise Refusal(f"{name} is spelled inside a string literal in {scope}: {strings[0][:80]}")
    if new_text == text:
        raise Refusal(f"{name} does not occur in {scope}'s text")
    if kind == "param":
        # the in-class prototype names the parameter too; leaving it on the
        # old word makes the declaration and the definition disagree
        protos = prototype_param_spans(code, scope, params, name, (start, end))
        new_text = text
        for span in sorted(protos + [(start, end)], reverse=True):
            new_text, part, _strings, _ = rewrite_tokens(new_text, word_re(name), new, span=span)
            if span != (start, end):
                counts = {k: counts.get(k, 0) + part.get(k, 0) for k in set(counts) | set(part)}
    if rva is None:
        rvas = {_rva(r.get("target_rva")) for r in ctx.rows()
                if r.get("source") == rel and scope_of(r["name"]) == scope.split("#")[0]}
        rva = rvas.pop() if len(rvas) == 1 and "#" not in scope else None
    plan = Plan(kind, old_q, new_q, basis, evidence.strip(), rel, rva, old_word=name, new_word=new)
    plan.source_counts[rel] = counts
    plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        [kind, old_q, new_q, basis, plan.evidence, rel, f"0x{rva:08X}" if rva is not None else ""])],
        header=NAME_BASIS_HEADER))
    plan.verify = [rel]
    plan.claims = ([rva] if rva is not None else []) + [f"file:{rel}"]
    return plan


def plan_param(ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25):
    return plan_scoped("param", ctx, source, name, new, basis, evidence,
                       function=function, rva=rva, max_files=max_files)


def plan_local(ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25):
    return plan_scoped("local", ctx, source, name, new, basis, evidence,
                       function=function, rva=rva, max_files=max_files)


def _rva(text):
    try:
        return int(text, 16)
    except (TypeError, ValueError):
        return None


def _tombstones(ctx, honour_restores=True):
    """(name, rva) -> reason of deleted_rows.csv; a tombstone a `restored`
    rename lifted does not count (honour_restores) even if it came back."""
    out = {}
    raw = ctx.read(DELETED)
    if raw is None:
        return out
    for line in raw.decode("utf-8", errors="replace").splitlines():
        if not line.strip() or line.startswith(("#", "name,")):
            continue
        row = next(csv.reader(io.StringIO(line)))
        if len(row) >= 2 and _rva(row[1]) is not None:
            out[(row[0], _rva(row[1]))] = row[2] if len(row) > 2 else ""
    if honour_restores:
        for pair in lifted_tombstones(ctx):
            out.pop(pair, None)
    return out


PLANNERS = {"function": plan_function, "global": plan_global, "file": plan_file, "class": plan_class,
            "member": plan_member, "param": plan_param, "local": plan_local}


def plan_rename(kind, *, ctx=None, **kwargs):
    """Plan one rename of `kind`; raises Refusal. Writes nothing."""
    if kind not in PLANNERS:
        raise Refusal(f"kind {kind!r} is not implemented in this build ({', '.join(PLANNERS)})")
    ctx = ctx or Context()
    plan = PLANNERS[kind](ctx, **kwargs)
    restoring = ctx._cache.pop("_restoring", None)
    if plan.basis == RESTORED and restoring:
        # check_csv keeps no record of a restore, so the landing's tombstones
        # must leave deleted_rows.csv; the restored name_basis.csv row is what
        # rename.py (and `check`) still knows them by
        lifted = set(restore_lifts(ctx, *restoring).values())
        if lifted:
            raw = plan.after.get(DELETED, ctx.read(DELETED)).decode("utf-8", errors="surrogateescape")
            kept = [l for l in raw.splitlines(keepends=True) if l.rstrip("\r\n") not in lifted]
            plan.edit(ctx, DELETED, "".join(kept).encode("utf-8", errors="surrogateescape"))
            plan.warnings.append(f"lifted {len(lifted)} tombstone(s) the landing wrote")
    return plan


# ---------------------------------------------------------------- apply

def build_verify(ctx, sources):
    """One ./build.sh over `sources`; True only on exit 0 with `Functions: OK`."""
    command = ([sys.executable, str(ctx.path("tools/build.py"))] if sys.platform == "win32"
               else [str(ctx.path("build.sh"))]) + list(sources)
    print(f"rename: verifying {len(sources)} source(s): ./build.sh {' '.join(sources)}", flush=True)
    result = subprocess.run(command, cwd=ctx.root, capture_output=True, text=True)
    output = result.stdout + result.stderr
    tail = "\n".join(output.rstrip().splitlines()[-25:])
    print(tail)
    return result.returncode == 0 and re.search(r"^Functions: OK \d+/\d+", output, re.M) is not None


def restore(ctx, before):
    """Put every file back exactly as it was; remove files that did not exist."""
    for rel, data in before.items():
        path = ctx.path(rel)
        if data is None:
            if path.exists():
                path.unlink()
        else:
            path.write_bytes(data)


# ---------------------------------------------------------------- journal
#
# The container is killed every 20-40 minutes and a class or caller-heavy
# ./build.sh takes minutes, so the in-process rollback is not enough: before
# the first write the plan's before-state is journalled, and a run that dies
# (SIGKILL, power) leaves the journal for `rename.py recover`. Every new run
# refuses to start while one exists.

JOURNAL_DIR = "build/rename-journal"


def _boot_id():
    try:
        return Path("/proc/sys/kernel/random/boot_id").read_text().strip()
    except OSError:
        return ""


def _b64(data):
    return None if data is None else base64.b64encode(data).decode("ascii")


def _unb64(text):
    return None if text is None else base64.b64decode(text)


def journals(ctx):
    """[(path, record)] of every rename journal in this tree."""
    out = []
    for path in sorted(ctx.path(JOURNAL_DIR).glob("*.json")) if ctx.path(JOURNAL_DIR).is_dir() else []:
        try:
            out.append((path, json.loads(path.read_text(encoding="utf-8"))))
        except (OSError, ValueError):
            out.append((path, None))
    return out


def journal_alive(record):
    """True while the process that wrote `record` may still be running."""
    if not record or record.get("host") != socket.gethostname() or record.get("boot") != _boot_id():
        return False
    try:
        os.kill(int(record.get("pid", 0)), 0)
    except (OSError, ValueError):
        return False
    return int(record.get("pid", 0)) != os.getpid()


def write_journal(ctx, plan, claimed=None):
    """Persist everything a restore needs before the first write."""
    record = {"id": uuid.uuid4().hex, "pid": os.getpid(), "host": socket.gethostname(), "boot": _boot_id(),
              "started": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), "subject": plan.subject(),
              "before": {rel: _b64(data) for rel, data in plan.before.items()},
              "moves": [list(m) for m in plan.moves],
              "moved_bytes": {old: _b64(data) for old, data in plan.moved_bytes.items()},
              "claims": [str(k) if not isinstance(k, int) else f"0x{k:08X}" for k in (claimed.new if claimed else [])],
              "tokens": {str(k): v for k, v in (claimed.tokens if claimed else {}).items()}}
    folder = ctx.path(JOURNAL_DIR)
    folder.mkdir(parents=True, exist_ok=True)
    path = folder / f"{record['id']}.json"
    tmp = path.with_suffix(".tmp")
    tmp.write_text(json.dumps(record), encoding="utf-8")
    with tmp.open("rb") as handle:
        os.fsync(handle.fileno())
    os.replace(tmp, path)
    return path


def restore_journal(ctx, record):
    """Undo one journalled rename: moves back, every file's bytes back."""
    for old, new in reversed(record.get("moves", [])):
        if ctx.path(new).exists() and not ctx.path(old).exists():
            moved = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", new, old], capture_output=True)
            if moved.returncode == 0:
                continue
        data = _unb64(record.get("moved_bytes", {}).get(old))
        if data is not None:
            ctx.path(old).parent.mkdir(parents=True, exist_ok=True)
            ctx.path(old).write_bytes(data)
        if ctx.path(new).exists():
            ctx.path(new).unlink()
        subprocess.run(["git", "-C", str(ctx.root), "reset", "-q", "--", old, new], capture_output=True)
        subprocess.run(["git", "-C", str(ctx.root), "add", "--", old], capture_output=True)
    restore(ctx, {rel: _unb64(data) for rel, data in record.get("before", {}).items()})


def recover(ctx, *, release_claims=True):
    """Restore every journal whose process is gone; returns (restored, busy)."""
    restored, busy = [], []
    for path, record in journals(ctx):
        if record is None:
            raise Refusal(f"{path} is unreadable; inspect it by hand (the before-state is in it)")
        if journal_alive(record):
            busy.append(record.get("subject", path.name))
            continue
        restore_journal(ctx, record)
        if release_claims and record.get("claims") and os.environ.get("BFME_CLAIMS", "on") != "off":
            import claims
            claims.release(record["claims"], root=ctx.root,
                           tokens={claims.key_of(k): v for k, v in record.get("tokens", {}).items()})
        path.unlink()
        restored.append(record.get("subject", path.name))
    return restored, busy


def refuse_pending_journal(ctx):
    pending = journals(ctx)
    if pending:
        path, record = pending[0]
        state = "is still running" if journal_alive(record) else "did not finish"
        raise Refusal(f"a rename {state} ({(record or {}).get('subject', path.name)}; journal {path}): "
                      "run `python3 tools/rename.py recover` first")


# ---------------------------------------------------------------- apply

def ledger_checks(ctx, plan):
    """What the commit hooks will say about the result: check_csv over the
    ledgers and find_declared_unmatched over the touched units. [] when both
    pass (or when the tree has no such tools, as in a fixture)."""
    problems = []
    if ctx.path("tools/check_csv.py").exists():
        result = subprocess.run([sys.executable, "tools/check_csv.py"], cwd=ctx.root, capture_output=True,
                                text=True)
        if result.returncode:
            problems.append("check_csv: " + " | ".join((result.stdout + result.stderr).strip().splitlines()[-5:]))
    units = sorted({rel for rel in plan.after if rel.startswith("Code/") and rel.endswith(SOURCE_SUFFIXES)} |
                   {new for _old, new in plan.moves})
    if units and ctx.path("tools/find_declared_unmatched.py").exists():
        result = subprocess.run([sys.executable, "tools/find_declared_unmatched.py", "--fail", *units],
                                cwd=ctx.root, capture_output=True, text=True)
        if result.returncode:
            problems.append("find_declared_unmatched: " +
                            " | ".join((result.stdout + result.stderr).strip().splitlines()[-5:]))
    return problems


def apply_rename(plan, *, ctx=None, verify=build_verify, checks=ledger_checks, claimed=None):
    """Write the plan, verify it (./build.sh, then the hooks' ledger checks),
    restore everything on any failure. A journal written before the first
    write makes a killed run recoverable (`rename.py recover`). Raises
    Refusal when the tree moved since planning or a journal is pending,
    VerifyFailed when the build or the ledger checks refuse the result."""
    ctx = ctx or Context()
    refuse_pending_journal(ctx)
    for rel, data in plan.before.items():
        if ctx.read(rel) != data:
            raise Refusal(f"{rel} changed since the rename was planned; plan again")
    for old, new in plan.moves:
        if ctx.read(old) != plan.moved_bytes.get(old) or ctx.path(new).exists():
            raise Refusal(f"{old} or {new} changed since the rename was planned; plan again")
    if checks:
        already = checks(ctx, Plan(plan.kind, plan.old, plan.new, plan.basis, plan.evidence, plan.source,
                                   plan.rva))
        if already:
            raise Refusal(f"the ledger checks already fail before the rename: {already[0][:300]}; "
                          "repair the ledger first (AGENTS.md step 2)")
    journal = write_journal(ctx, plan, claimed)
    moved = []
    try:
        for old, new in plan.moves:
            ctx.path(new).parent.mkdir(parents=True, exist_ok=True)
            result = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", old, new],
                                    capture_output=True, text=True)
            if result.returncode:
                raise Refusal(f"git mv {old} {new} failed: {result.stderr.strip()[:200]}")
            moved.append((old, new))
        for rel, data in plan.after.items():
            ctx.path(rel).parent.mkdir(parents=True, exist_ok=True)
            ctx.path(rel).write_bytes(data)
        if not verify(ctx, plan.verify):
            raise VerifyFailed(f"verification failed for {plan.old} -> {plan.new}; every file restored")
        problems = checks(ctx, plan) if checks else []
        if problems:
            raise VerifyFailed(f"the commit hooks would refuse {plan.old} -> {plan.new} ({problems[0][:300]}); "
                               "every file restored")
    except BaseException:
        unmove(ctx, plan, moved)
        restore(ctx, plan.before)
        journal.unlink()
        raise
    journal.unlink()
    return plan


def unmove(ctx, plan, moved):
    """Undo `git mv`s newest first; the bytes go back even when git cannot."""
    for old, new in reversed(moved):
        result = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", new, old],
                                capture_output=True, text=True)
        if result.returncode:
            ctx.path(old).write_bytes(plan.moved_bytes[old])
            if ctx.path(new).exists():
                ctx.path(new).unlink()
            subprocess.run(["git", "-C", str(ctx.root), "reset", "-q", "--", old, new],
                           capture_output=True)
            print(f"rename: warning: git mv {new} {old} failed; bytes restored, index reset "
                  f"for both paths ({result.stderr.strip()[:120]})", file=sys.stderr)


# ---------------------------------------------------------------- claims

def claim_keys(plan):
    """Every RVA the plan names, a file: scope for every Code/ or shim file it
    writes or moves, and class: for a class or member rename."""
    keys = [k for k in plan.claims if isinstance(k, int)]
    scopes = {k for k in plan.claims if isinstance(k, str)}
    for rel in list(plan.after) + [p for move in plan.moves for p in move]:
        if rel.startswith(("Code/", "reference/shims/")):
            scopes.add(f"file:{rel}")
    if plan.kind == "class":
        scopes.add(f"class:{plan.old_word}")
    if plan.kind == "member":
        scopes.add(f"class:{plan.old.split('::')[0]}")
    return sorted(set(keys)) + sorted(scopes)


def claim_label(key):
    return f"0x{key:08X}" if isinstance(key, int) else str(key)


@dataclass
class Claimed:
    new: list = field(default_factory=list)       # keys this run took (not ones it already held)
    tokens: dict = field(default_factory=dict)    # key -> fencing token, for a safe release
    unconfirmed: list = field(default_factory=list)

    def release(self, root=None):
        if not self.new:
            return []
        import claims
        tokens = {claims.key_of(k): v for k, v in self.tokens.items()}
        released = claims.release(self.new, root=root, tokens=tokens)
        self.new = []
        return released


def take_claims(keys, enabled, root=None):
    """Claim `keys`. Returns a Claimed holding only the keys this run newly
    took, so releasing it never drops a claim the caller already held.
    Refuses when another worker holds any key; keys origin could not confirm
    (network trouble, nobody else holding them) are reported, not refused."""
    if not enabled or os.environ.get("BFME_CLAIMS", "on") == "off" or not keys:
        return Claimed()
    import claims
    try:
        names = set(claims._names(claims.owner(root), root))
        held = {claims.key_of(k) for k, info in claims.active(root).items() if info.get("owner") in names}
        result = claims.claim(keys, note="tools/rename.py", root=root)
    except claims.ClaimsUnavailable as error:
        if error.refused:
            claims.release([k for k in error.claimed], root=root)
            raise Refusal(f"claimed by another worker: {', '.join(map(claim_label, error.refused))}")
        print(f"rename: warning: claims unavailable ({error}); working unclaimed", file=sys.stderr)
        return Claimed(new=list(error.claimed))
    claimed, refused = result
    unconfirmed = set(getattr(result, "unconfirmed", []))
    taken = Claimed(new=[k for k in claimed if claims.key_of(k) not in held],
                    tokens={k: v for k, v in result.tokens.items() if claims.key_of(k) not in held},
                    unconfirmed=sorted(unconfirmed, key=str))
    others = [k for k in refused if k not in unconfirmed]
    if others:
        taken.release(root)
        raise Refusal(f"claimed by another worker: {', '.join(map(claim_label, others))}")
    if unconfirmed:
        print("rename: warning: origin could not confirm claims on "
              f"{', '.join(map(claim_label, unconfirmed))} (network; nobody else holds them): working unclaimed "
              "there", file=sys.stderr)
    return taken


# ---------------------------------------------------------------- run

class _Terminated(KeyboardInterrupt):
    """SIGTERM, raised so the rollback in apply_rename runs."""


def _on_sigterm(signum, frame):
    raise _Terminated(f"signal {signum}")


def run(kind, ctx, *, dry_run=False, claim=True, keep_claims=None, verify=build_verify, checks=ledger_checks,
        **kwargs):
    """Plan under the ledger lock, then (unless dry-run) claim, apply and
    keep the claims for the lander (released after the push), or release
    them when the rename fails."""
    from portable_lock import lock, unlock
    keep_claims = (not dry_run) if keep_claims is None else keep_claims
    if not dry_run:
        refuse_pending_journal(ctx)
    handle = None
    previous = None
    if not dry_run and threading.current_thread() is threading.main_thread():
        previous = signal.signal(signal.SIGTERM, _on_sigterm)
    try:
        if not dry_run:
            handle = ctx.path(LOCK).open("a")
            lock(handle, exclusive=True, wait_notice="rename: waiting for the ledger lock...")
        plan = plan_rename(kind, ctx=ctx, **kwargs)
        plan.claims = claim_keys(plan)
        print(plan.report())
        if dry_run:
            print("rename: --dry-run: nothing written")
            return plan
        claimed = take_claims(plan.claims, claim, ctx.root)
        try:
            apply_rename(plan, ctx=ctx, verify=verify, checks=checks, claimed=claimed)
        except BaseException:
            claimed.release(ctx.root)
            raise
        if not keep_claims:
            claimed.release(ctx.root)
        elif claimed.new:
            print("rename: claims kept until the rename is pushed; then run: python3 tools/claims.py release "
                  + " ".join(map(claim_label, claimed.new)))
        staged = " (git mv already staged " + ", ".join(n for _, n in plan.moves) + ")" if plan.moves else ""
        print(f"rename: verified OK. Stage: git add {' '.join(sorted(plan.after))}{staged}")
        print("rename: after every pull --rebase, before the push: python3 tools/rename.py check "
              "--range origin/master..HEAD")
        print(f"rename: suggested subject: {plan.subject()}")
        return plan
    finally:
        if handle is not None:
            unlock(handle)
            handle.close()
        if previous is not None:
            signal.signal(signal.SIGTERM, previous)


# ---------------------------------------------------------------- post-rebase check
#
# A rename is verified against the tree it was planned on. While it was in
# flight another seat may have landed a pin with the old name (symbols.csv
# union-merges), a caller declaring or calling it, or a data consumer extern:
# the byte gate masks DIR32 and a stale pin keeps the old name resolving, so
# all of that passes every gate and breaks only the link. `check` re-reads
# the merged tree for every rename the range landed.

CHECK_LEDGERS = (FUNCTIONS, SYMBOLS, DATA_ROWS, BODY_OWNERS)


def basis_rows_in_range(ctx, spec):
    """name_basis.csv rows the commits in `spec` (A..B) added."""
    diff = ctx.git("diff", "--unified=0", spec, "--", NAME_BASIS)
    added = [line[1:] for line in diff.splitlines() if line.startswith("+") and not line.startswith("+++")]
    rows = list(csv.DictReader(io.StringIO(NAME_BASIS_HEADER + "\n" + "\n".join(added))))
    return [r for r in rows if r.get("kind") != "kind"]


def code_spellers(ctx, word):
    """Non-generated Code/ and shim files that spell `word` as a code token."""
    out = []
    for rel in ctx.grep_files(word, word=True):
        if is_generated(rel):
            continue
        text = (ctx.read(rel) or b"").decode("utf-8", errors="replace")
        if code_mentions(text, word) or any(w in text for w in MARKER_WORDS) and word_re(word).search(text):
            out.append(rel)
    return out


def check_row(ctx, row, texts):
    """Problems with one landed rename: its old spelling still in use."""
    kind, old = row.get("kind"), row.get("old", "")
    problems = []
    if kind in ("function", "global"):
        old_re = mangled_re(old)
        for rel in CHECK_LEDGERS:
            if old_re.search(texts[rel]):
                problems.append(f"{rel} still spells {old}")
        word = _identifier(old) or old
        for rel in code_spellers(ctx, word):
            problems.append(f"{rel} still spells {word}")
    elif kind == "class":
        token = ClassToken(old)
        for rel in CHECK_LEDGERS:
            if token.search(texts[rel]):
                problems.append(f"{rel} still has a mangled name scoped or typed by {old}")
        for rel in code_spellers(ctx, old):
            problems.append(f"{rel} still spells {old}")
    elif kind == "file":
        if ctx.path(old).exists():
            problems.append(f"{old} exists again")
        for rel, _column in PATH_COLUMNS:
            if path_keyed_lines(ctx, rel, old):
                problems.append(f"{rel} still keys {old}")
    elif kind == "member" and "::" in old:
        cls, member = old.rsplit("::", 1)
        for rel in sorted(set(ctx.grep_files(cls, word=True)) & set(ctx.grep_files(member, word=True))):
            code = name_metric.strip((ctx.read(rel) or b"").decode("utf-8", errors="replace"))
            if any(member_statements(code[a:b], member) for a, b in class_bodies(code, cls)):
                problems.append(f"{rel} still declares {old}")
    elif kind in ("param", "local") and old.count("::") >= 1:
        scope, name = old.rsplit("::", 1)
        source = row.get("source", "")
        data = ctx.read(source) if source else None
        if data is not None:
            code = name_metric.strip(data.decode("utf-8", errors="replace"))
            for found, start, end, params in name_metric.functions_in(code):
                if found.split("#")[0] != scope:
                    continue
                body = code[code.find("{", start):end]
                if name in set(parameters(params)) | set(name_metric.local_names(body)):
                    problems.append(f"{source}: {found} still declares {kind} {name}")
    return problems


def check_renames(ctx, rows):
    """Problems with landed renames `rows` (name_basis.csv records): an old
    spelling back in a ledger, a pin, a source, a marker or a pragma, and any
    tombstoned (name, address) data row (functions.csv's tombstones are
    check_csv's). A row a later rename deliberately reverted is skipped."""
    texts = {rel: (ctx.read(rel) or b"").decode("utf-8", errors="replace") for rel in CHECK_LEDGERS}
    every = name_basis_rows(ctx)
    problems = []
    for row in rows:
        if row.get("kind") == "carry":
            continue
        position = next((i for i, r in enumerate(every) if r == row), -1)
        if any(r.get("new") == row.get("old") for r in every[position + 1:]):
            continue
        problems += [f"{row.get('kind')} {row.get('old')} -> {row.get('new')}: {p}"
                     for p in check_row(ctx, row, texts)]
    tombstoned = _tombstones(ctx)
    for (name, at), line in sorted(lifted_tombstones(ctx).items(), key=lambda kv: (kv[0][0], kv[0][1] or 0)):
        if (name, at) in _tombstones(ctx, honour_restores=False):
            problems.append(f"{DELETED} has the tombstone of restored {name} at 0x{at:08X} again (a union "
                            "merge brought it back); delete that line again -- check_csv refuses the row")
    for data in ctx.dicts(DATA_ROWS):
        if (data.get("name"), data_rva(data)) in tombstoned:
            problems.append(f"{DATA_ROWS} row {data.get('name')} at 0x{data_rva(data):08X} is tombstoned "
                            f"({tombstoned[(data.get('name'), data_rva(data))][:80]})")
    return problems


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     epilog=__doc__.split("\n\n", 1)[1])
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--basis", required=True, help="'inferred' or 'canonical:<evidence-kind>' "
                        f"({', '.join(sorted(CANONICAL_KINDS))})")
    common.add_argument("--evidence", required=True,
                        help="canonical: the evidence; inferred: the two-agent agreement record")
    common.add_argument("--dry-run", action="store_true", help="print the full plan, write nothing")
    common.add_argument("--no-claim", action="store_true", help="skip tools/claims.py (tests)")
    common.add_argument("--no-object-scan", action="store_true",
                        help="find referencing units by text only, not cached object symbol tables")
    common.add_argument("--max-files", type=int, default=25, help="refuse a larger blast radius (default 25)")
    common.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    common.add_argument("--sweep-dir", action="append", default=None,
                        help="canonical:zh/bfme1: directory holding zh_sweep/ and bfme1_sweep/ caches "
                             "(default build/; repeatable), as tools/name_evidence.py takes it")
    common.add_argument("--release-claims", action="store_true",
                        help="release this run's claims when it ends (default: keep them for the lander, "
                             "who releases them after the push)")
    kinds = parser.add_subparsers(dest="kind", required=True)
    checker = kinds.add_parser("check", help="after a pull --rebase: refuse when a landed rename's old "
                                             "spelling is back (pins, callers, externs, markers)")
    span = checker.add_mutually_exclusive_group(required=True)
    span.add_argument("--range", dest="span", help="the commits to check, e.g. origin/master..HEAD")
    span.add_argument("--all", action="store_true", help="every name_basis.csv record")
    checker.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    recovery = kinds.add_parser("recover", help="restore every rename a killed run left half-applied")
    recovery.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    back = kinds.add_parser("revert", help="put the placeholder back over a landed inferred name "
                                           "(the exact inverse, recorded as basis restored)")
    back.add_argument("--record", required=True, help="the agreement id the landing cited (agree:<id>)")
    back.add_argument("--reason", required=True, help="what the code shows against the landed name")
    back.add_argument("--function", help="param/local only: Class::method#N when the function is overloaded")
    for flag, text in (("--dry-run", "print the full plan, write nothing"), ("--no-claim", "skip tools/claims.py"),
                       ("--no-object-scan", "find referencing units by text only"),
                       ("--release-claims", "release this run's claims when it ends")):
        back.add_argument(flag, action="store_true", help=text)
    back.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    function = kinds.add_parser("function", parents=[common],
                                help="respell one RVA's function identifier")
    function.add_argument("--rva", required=True, help="the function's target RVA (hex)")
    function.add_argument("--new", required=True,
                          help="new identifier, or the full mangled name (identifier change only)")
    function.add_argument("--old", help="the current mangled name, when several share the RVA")
    data = kinds.add_parser("global", parents=[common],
                            help="respell one reverse/data_rows.csv global and every consumer")
    data.add_argument("--name", required=True, help="the global's mangled name, or its bare identifier")
    data.add_argument("--new", required=True,
                      help="new identifier, or the full mangled name (identifier change only)")
    unit = kinds.add_parser("file", parents=[common],
                            help="git mv one Code/ unit within its directory, with its path-keyed rows")
    unit.add_argument("--source", required=True, help="the unit's repo-relative path")
    unit.add_argument("--new", required=True, help="new file name or stem (same directory), or full path")
    klass = kinds.add_parser("class", parents=[common],
                             help="respell one class/struct/union/enum token in every name and view")
    klass.add_argument("--name", required=True, help="the type's current identifier")
    klass.add_argument("--new", required=True, help="the new identifier")
    member = kinds.add_parser("member", parents=[common],
                              help="respell one non-static data member in every view and use")
    member.add_argument("--class", dest="cls", required=True, help="the class whose member it is")
    member.add_argument("--member", required=True, help="the member's current identifier")
    member.add_argument("--new", required=True, help="the new identifier")
    for kind in ("param", "local"):
        scoped = kinds.add_parser(kind, parents=[common],
                                  help=f"respell one {kind} inside one function body in one file")
        scoped.add_argument("--source", required=True, help="the ledger source defining the function")
        scoped.add_argument("--function", help="Class::method (Class::method#2 for a later overload)")
        scoped.add_argument("--rva", help="or the function's target RVA (hex)")
        scoped.add_argument("--name", required=True, help=f"the {kind}'s current identifier")
        scoped.add_argument("--new", required=True, help="the new identifier")
    args = parser.parse_args(argv)
    if args.kind == "recover":
        ctx = Context(args.root, object_scan=False)
        try:
            restored, busy = recover(ctx)
        except Refusal as why:
            print(f"rename: refused: {why}", file=sys.stderr)
            return 2
        for subject in restored:
            print(f"rename: restored: {subject}")
        for subject in busy:
            print(f"rename: still running (left alone): {subject}")
        if not restored and not busy:
            print("rename: no rename journal; nothing to recover")
        return 1 if busy else 0
    if args.kind == "revert":
        ctx = Context(args.root, object_scan=not args.no_object_scan)
        try:
            revert(ctx, args.record.removeprefix("agree:"), args.reason, function=args.function,
                   dry_run=args.dry_run, claim=not args.no_claim,
                   keep_claims=False if args.release_claims else None)
        except Refusal as why:
            print(f"rename: refused: {why}", file=sys.stderr)
            return 2
        except VerifyFailed as why:
            print(f"rename: {why}", file=sys.stderr)
            return 1
        return 0
    if args.kind == "check":
        ctx = Context(args.root, object_scan=False)
        rows = name_basis_rows(ctx) if args.all else basis_rows_in_range(ctx, args.span)
        problems = check_renames(ctx, rows)
        for problem in problems:
            print(f"rename: check: {problem}", file=sys.stderr)
        print(f"rename: check: {len(rows)} rename(s), {len(problems)} problem(s)")
        return 1 if problems else 0
    ctx = Context(args.root, object_scan=not args.no_object_scan, sweep_dirs=args.sweep_dir or ("build",))
    kwargs = dict(new=args.new, basis=args.basis, evidence=args.evidence, max_files=args.max_files)
    if args.kind == "function":
        try:
            kwargs.update(rva=int(args.rva, 16), old=args.old)
        except ValueError:
            parser.error(f"--rva {args.rva!r} is not hex")
    elif args.kind in ("global", "class"):
        kwargs.update(name=args.name)
    elif args.kind == "member":
        kwargs.update(cls=args.cls, member=args.member)
    elif args.kind in ("param", "local"):
        try:
            rva = int(args.rva, 16) if args.rva else None
        except ValueError:
            parser.error(f"--rva {args.rva!r} is not hex")
        kwargs.update(source=args.source, name=args.name, function=args.function, rva=rva)
    else:
        kwargs.update(source=args.source)
    try:
        run(args.kind, ctx, dry_run=args.dry_run, claim=not args.no_claim,
            keep_claims=False if args.release_claims else None, **kwargs)
    except Refusal as why:
        print(f"rename: refused: {why}", file=sys.stderr)
        return 2
    except VerifyFailed as why:
        print(f"rename: {why}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
