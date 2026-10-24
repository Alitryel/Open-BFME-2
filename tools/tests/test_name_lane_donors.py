"""Reference searches need Git, without a separate GNU grep installation."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import rename


@pytest.fixture
def lane(tmp_path, monkeypatch):
    root = tmp_path / "donor tree with spaces ü"
    root.mkdir()
    subprocess.run(["git", "init", "-q", str(root)], check=True, capture_output=True)
    original = subprocess.run

    def without_grep(args, *pos, **kw):
        if Path(args[0]).stem.lower() == "grep":
            raise FileNotFoundError("No separate grep executable in this environment")
        return original(args, *pos, **kw)

    monkeypatch.setattr(name_lane.subprocess, "run", without_grep)
    return name_lane.Lane(root, rename.Context(root, object_scan=False))


def donor(lane, rel, text, *, zh=False):
    folder = rename.ZH_TREE if zh else "game"
    path = lane.path(rename.BFME1) / folder / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode())
    return path


def test_original_donor_names_survive_without_external_grep(lane):
    donor(lane, "Libraries/vector3.h",
          "inline float Dot_Product(const Vector3 &a, const Vector3 &b) { return 0; }\n"
          "x = Dot_Product(v, w);\n")
    assert lane.donor_params({"Dot_Product"}) == {"Dot_Product": {"a", "b"}}


@pytest.mark.parametrize("extension", ["h", "inl", "cpp"])
def test_each_supported_source_extension_is_read_recursively(lane, extension):
    donor(lane, f"nested/deeper/math.{extension}", "void Read(const Thing &original);\n")
    assert lane.donor_params({"Read"}) == {"Read": {"original"}}


def test_both_donor_roots_are_read_including_untracked_ignored_files(lane):
    lane.path(".gitignore").write_text("reference/\n")
    donor(lane, "native.h", "void Read(const Thing &native);\n")
    donor(lane, "nested/reference.h", "void Read(const Thing &reference);\n", zh=True)
    lane.path("other.cpp").write_text("void Read(const Thing &outside);\n")
    assert lane.donor_params({"Read"}) == {"Read": {"native", "reference"}}


def test_other_extensions_and_other_function_words_do_not_supply_names(lane):
    donor(lane, "notes.txt", "void Read(const Thing &textOnly);\n")
    donor(lane, "math.h", "void PrefixRead(const Thing &prefixOnly);\nRead(left, right);\n")
    assert lane.donor_params({"Read"}) == {"Read": set()}


def test_no_donor_roots_is_a_valid_empty_search(lane, monkeypatch):
    def unexpected(*a, **kw):
        raise AssertionError("No search process is needed when neither donor root exists")
    monkeypatch.setattr(name_lane.subprocess, "run", unexpected)
    assert lane.donor_params({"Read"}) == {"Read": set()}


def test_search_results_and_absent_words_are_cached(lane, monkeypatch):
    donor(lane, "math.h", "void Read(const Thing &value);\n")
    original = subprocess.run
    searches = []

    def counted(args, *a, **kw):
        if "grep" in args:
            searches.append(args)
        return original(args, *a, **kw)
    monkeypatch.setattr(name_lane.subprocess, "run", counted)
    assert lane.donor_params({"Read", "Absent"}) == {"Read": {"value"}, "Absent": set()}
    assert lane.donor_params({"Read", "Absent"}) == {"Read": {"value"}, "Absent": set()}
    assert len(searches) == 1


def test_function_batches_remain_bounded(lane, monkeypatch):
    donor(lane, "math.h", "void Read200(const Thing &last);\n")
    original = subprocess.run
    searches = []

    def counted(args, *a, **kw):
        if "grep" in args:
            searches.append(args)
        return original(args, *a, **kw)
    monkeypatch.setattr(name_lane.subprocess, "run", counted)
    results = lane.donor_params({f"Read{i}" for i in range(201)})
    assert results["Read200"] == {"last"} and results["Read0"] == set()
    assert len(searches) == 2


def test_git_display_configuration_does_not_change_parameter_evidence(lane):
    donor(lane, "math.h", "void Read(const Thing &original);\n")
    for setting, value in (("grep.lineNumber", "true"), ("grep.column", "true"),
                           ("color.grep", "always")):
        subprocess.run(["git", "-C", str(lane.root), "config", setting, value],
                       check=True, capture_output=True)
    assert lane.donor_params({"Read"}) == {"Read": {"original"}}


def test_later_batch_failure_keeps_all_new_cache_entries_unpublished(lane, monkeypatch):
    donor(lane, "math.h", "void Read0(const Thing &original);\n")
    original = subprocess.run
    searches = 0

    def fail_second(args, *a, **kw):
        nonlocal searches
        if "grep" in args:
            searches += 1
            if searches == 2:
                return subprocess.CompletedProcess(args, 2, "", "later reference search failed")
        return original(args, *a, **kw)
    monkeypatch.setattr(name_lane.subprocess, "run", fail_second)
    with pytest.raises(SystemExit, match="reference search"):
        lane.donor_params({f"Read{i}" for i in range(201)})
    assert searches == 2 and lane._donor == {}
    monkeypatch.setattr(name_lane.subprocess, "run", original)
    assert lane.donor_params({"Read0"}) == {"Read0": {"original"}}


@pytest.mark.parametrize("failure", ["exit", "missing"])
def test_search_error_is_reported_without_poisoning_parameter_cache(lane, monkeypatch, failure):
    donor(lane, "math.h", "void Read(const Thing &value);\n")
    original = subprocess.run

    def failed(args, *a, **kw):
        if "grep" in args or Path(args[0]).stem.lower() == "grep":
            if failure == "missing":
                raise FileNotFoundError("git unavailable")
            return subprocess.CompletedProcess(args, 2, "", "reference search failed")
        return original(args, *a, **kw)
    monkeypatch.setattr(name_lane.subprocess, "run", failed)
    with pytest.raises(SystemExit, match="reference search"):
        lane.donor_params({"Read"})
    assert "Read" not in lane._donor
    monkeypatch.setattr(name_lane.subprocess, "run", original)
    assert lane.donor_params({"Read"}) == {"Read": {"value"}}


def test_header_type_uses_only_zero_hour_headers(lane):
    donor(lane, "native.h", "class NativeOnly {};\n")
    donor(lane, "source.cpp", "class SourceOnly {};\n", zh=True)
    donor(lane, "nested/types.h", "class KnownType {};\nclass PrefixKnownType {};\n", zh=True)
    assert lane.header_type("KnownType")
    assert not lane.header_type("Known")
    assert not lane.header_type("SourceOnly")
    assert not lane.header_type("NativeOnly")


def test_header_spelling_is_found_without_external_grep(lane):
    donor(lane, "types.h", "class CameraShaker {};\n", zh=True)
    assert name_lane.lane_spelling(lane, "cameraShaker", "class") == "CameraShaker"


def test_ambiguous_header_spelling_is_not_chosen(lane):
    donor(lane, "types.h", "class Camera {};\nclass CAMERA {};\n", zh=True)
    assert name_lane.lane_spelling(lane, "camera", "class") == "camera"


@pytest.mark.parametrize("operation", ["header", "spelling"])
def test_other_reference_search_failures_are_not_silently_empty(lane, monkeypatch, operation):
    donor(lane, "types.h", "class CameraShaker {};\n", zh=True)
    original = subprocess.run

    def failed(args, *a, **kw):
        if "grep" in args or Path(args[0]).stem.lower() == "grep":
            return subprocess.CompletedProcess(args, 2, "", "reference search failed")
        return original(args, *a, **kw)
    monkeypatch.setattr(name_lane.subprocess, "run", failed)
    with pytest.raises(SystemExit, match="reference search"):
        if operation == "header":
            lane.header_type("CameraShaker")
        else:
            name_lane.lane_spelling(lane, "cameraShaker", "class")
