"""Direct record typedefs in headers satisfy naming-lane type admission.

This proves a header name exists, never a target identity or layout.
"""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import rename

NAME = "ListboxData"


@pytest.fixture
def lane(tmp_path):
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True, capture_output=True)
    source = tmp_path / "Code/Game/Other.cpp"
    source.parent.mkdir(parents=True)
    source.write_text(f"struct {NAME} {{ int value; }};\n")
    subprocess.run(["git", "-C", str(tmp_path), "add", "--", "Code/Game/Other.cpp"],
                   check=True, capture_output=True)
    return name_lane.Lane(tmp_path, rename.Context(tmp_path, object_scan=False))


def header(lane, text, *, root="shim", suffix="h", tracked=True):
    folder = {"shim": "reference/shims/sweep/GameClient", "code": "Code/Game",
              "zh": f"{rename.BFME1}/{rename.ZH_TREE}/Code/Game"}[root]
    rel = f"{folder}/Types.{suffix}"
    path = lane.path(rel)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode())
    if tracked:
        subprocess.run(["git", "-C", str(lane.root), "add", "--", rel],
                       check=True, capture_output=True)
    return rel


@pytest.mark.parametrize("declaration", [
    "typedef struct _ListboxData { int value; } ListboxData;",
    "typedef struct { int value; } ListboxData;",
    "typedef class _ListboxData { public: int value; } ListboxData;",
    "typedef struct _ListboxData ListboxData;",
    "typedef class _ListboxData ListboxData;",
    "typedef struct _ListboxData { int value; } OtherAlias, ListboxData;",
    "typedef struct _ListboxData { struct Nested { int value; }; void f() { if (1) {} } } ListboxData;",
    "typedef\nstruct /* tag */ _ListboxData\n{ int value; }\n/* public alias */ ListboxData;",
])
def test_record_typedef_is_header_type_evidence(lane, declaration):
    header(lane, declaration)
    assert lane.header_type(NAME)
    assert lane.problem("class", "Rva00104DB0ListData", NAME, set()) is None


@pytest.mark.parametrize("root,suffix", [("code", "h"), ("code", "hpp"), ("shim", "h"), ("zh", "h")])
def test_supported_header_locations(lane, root, suffix):
    header(lane, "typedef struct { int value; } ListboxData;", root=root, suffix=suffix,
           tracked=root != "zh")
    assert lane.header_type(NAME)


@pytest.mark.parametrize("declaration", [
    "// typedef struct Tag { int value; } ListboxData;\n",
    "/* typedef struct Tag { int value; } ListboxData; */\n",
    'const char *text = "typedef struct Tag { int value; } ListboxData;";',
    "#define DECLARE_TYPE typedef struct Tag { int value; } ListboxData;\n",
    "#define DECLARE_TYPE " + "\\" + "\n  typedef struct Tag { int value; } ListboxData;\n",
    "#define DECLARE_TYPE " + "\\ " + "\n  typedef struct Tag { int value; } ListboxData;\n",
    "#define DECLARE_TYPE " + "\\ " + "\r\n  typedef struct Tag { int value; } ListboxData;\r\n",
    "typedef int ListboxData;",
    "typedef struct Tag *ListboxData;",
    "typedef struct Tag { int value; } *ListboxData;",
    "typedef struct Tag { int value; } &ListboxData;",
    "typedef struct Tag { int value; } ListboxData[2];",
    "typedef struct Tag { int value; } (*Callback)(int, ListboxData, int);",
    "typedef struct Tag { int value; } ListboxDataExtra;",
    "struct Tag { int value; } ListboxData;",
    "typedef struct Tag { int ListboxData; } OtherAlias;",
    "typedef struct Tag { struct { int value; } ListboxData; } OtherAlias;",
    "typedef struct Tag { int value; ListboxData;",
])
def test_nonrecord_or_noncode_spellings_do_not_admit_type(lane, declaration):
    header(lane, declaration)
    assert not lane.header_type(NAME)
    assert "another file's stand-in" in lane.problem("class", "Rva00104DB0ListData", NAME, set())


def test_untracked_local_header_does_not_admit_type(lane):
    header(lane, "typedef struct { int value; } ListboxData;", tracked=False)
    assert not lane.header_type(NAME)


def test_cpp_typedef_is_not_header_evidence(lane):
    header(lane, "typedef struct { int value; } ListboxData;", root="code", suffix="cpp")
    assert not lane.header_type(NAME)


def test_zero_hour_keeps_existing_h_only_scope(lane):
    header(lane, "typedef struct { int value; } ListboxData;", root="zh", suffix="hpp", tracked=False)
    assert not lane.header_type(NAME)


def test_header_filename_is_not_corrupted_by_git_quote_settings(lane):
    rel = header(lane, "typedef struct { int value; } ListboxData;")
    new_rel = "reference/shims/sweep/GameClient/Types with spaces ü.h"
    subprocess.run(["git", "-C", str(lane.root), "mv", "--", rel, new_rel],
                   check=True, capture_output=True)
    subprocess.run(["git", "-C", str(lane.root), "config", "core.quotePath", "true"],
                   check=True, capture_output=True)
    assert lane.header_type(NAME)


def test_header_search_failure_does_not_grant_type_admission(lane, monkeypatch):
    header(lane, "typedef struct { int value; } ListboxData;")
    original = subprocess.run

    def failed(args, *a, **kw):
        if "grep" in args:
            return subprocess.CompletedProcess(args, 2, "", "header discovery failed")
        return original(args, *a, **kw)
    monkeypatch.setattr(name_lane.subprocess, "run", failed)
    with pytest.raises(SystemExit, match="reference search"):
        lane.header_type(NAME)


def test_real_gadget_header_admits_listbox_alias():
    lane = name_lane.Lane(ctx=rename.Context(object_scan=False))
    assert "} ListboxData;" in lane.text("reference/shims/sweep/GameClient/Gadget.h")
    assert lane.header_type(NAME)
    assert lane.problem("class", "Rva00104DB0ListData", NAME, set()) is None
