"""Compiler selection must be explicit, reproducible and covered by receipts."""
import hashlib
import json
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import compiler_profiles


@pytest.fixture
def profile(tmp_path, monkeypatch):
    monkeypatch.setattr(compiler_profiles, "ROOT", tmp_path)
    directory = tmp_path / "vendor/vc71-sp1/bin"
    directory.mkdir(parents=True)
    hashes = {}
    for name in compiler_profiles.SP1_FILES:
        data = ("test compiler " + name).encode()
        (directory / name).write_bytes(data)
        hashes[name] = hashlib.sha256(data).hexdigest()
    monkeypatch.setattr(compiler_profiles, "SP1_FILES", hashes)
    source = tmp_path / "source.cpp"
    source.write_text("// compiler: vc71-sp1\nint f() { return 1; }\n")
    return tmp_path, directory, source


def test_no_profile_preserves_compiler_environment_and_fingerprint(tmp_path):
    source = tmp_path / "default.cpp"
    source.write_text("int f() { return 1; }\n")
    env = {"INCLUDE": "original", "PATH": "existing"}
    compiler = tmp_path / "original/cl.exe"
    assert compiler_profiles.select(source, compiler, env) == (compiler, env)
    expected = hashlib.md5(json.dumps([["cl", "-c"], "original"]).encode()).hexdigest()
    assert build._cmd_fingerprint(["cl", "-c"], env) == expected


def test_profile_preserves_headers_and_records_all_binaries(profile):
    root, directory, source = profile
    source.write_text("\ufeff" + "// long comment\n" * 400 + source.read_text(), encoding="utf-8")
    env = {"INCLUDE": "original headers", "LIB": "original libs", "PATH": "old"}
    compiler, selected = compiler_profiles.select(source, Path("old/cl.exe"), env)
    assert compiler == directory / "cl.exe"
    assert selected["INCLUDE"] == env["INCLUDE"]
    assert selected["LIB"] == env["LIB"]
    assert selected != env and "BFME_COMPILER_INPUTS" not in env
    assert set(json.loads(selected["BFME_COMPILER_INPUTS"])) == {
        f"vendor/vc71-sp1/bin/{name}" for name in compiler_profiles.SP1_FILES}
    assert build._cmd_fingerprint(["cl"], selected) != build._cmd_fingerprint(["cl"], env)


@pytest.mark.parametrize("directive", ["unknown", "", "vc71-sp1\n// compiler: vc71-sp1"])
def test_bad_or_duplicate_profile_refuses(profile, directive):
    _, _, source = profile
    source.write_text("// compiler: " + directive + "\n")
    with pytest.raises(SystemExit, match="expected one"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})


def test_changed_compiler_refuses_even_on_repeated_selection(profile):
    _, directory, source = profile
    compiler_profiles.select(source, Path("old/cl.exe"), {})
    (directory / "c2.dll").write_bytes(b"changed compiler")
    with pytest.raises(SystemExit, match="SHA256 mismatch"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})


def test_missing_compiler_refuses_without_fallback(profile):
    _, directory, source = profile
    (directory / "cl.exe").unlink()
    with pytest.raises(SystemExit, match="cannot read"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})


def test_receipt_tracks_binaries_and_does_not_hide_missing_includes(profile, monkeypatch):
    root, _, source = profile
    monkeypatch.setattr(build, "ROOT", root)
    _, env = compiler_profiles.select(source, Path("old/cl.exe"), {})
    output = root / "source.obj"
    output.write_bytes(b"object")
    build._write_deps_sidecar(source, output, "fingerprint", "", True, env=env)
    sidecar = output.with_suffix(".deps.json")
    meta = json.loads(sidecar.read_text())
    assert set(meta["deps"]) == set(json.loads(env["BFME_COMPILER_INPUTS"]))
    source.write_text('#include "missing.h"\n')
    build._write_deps_sidecar(source, output, "fingerprint", "", True, env=env)
    assert not sidecar.exists()


def test_compiler_changed_during_compile_cannot_receive_receipt(profile, monkeypatch):
    root, directory, source = profile
    monkeypatch.setattr(build, "ROOT", root)
    _, env = compiler_profiles.select(source, Path("old/cl.exe"), {})
    (directory / "c1xx.dll").write_bytes(b"changed during compile")
    output = root / "source.obj"
    output.write_bytes(b"object")
    build._write_deps_sidecar(source, output, "fingerprint", "", True, env=env)
    assert not output.with_suffix(".deps.json").exists()
