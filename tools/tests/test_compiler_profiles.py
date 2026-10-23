"""Compiler selection must be explicit, reproducible and covered by receipts."""
import hashlib
import json
import sys
import zipfile
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import compiler_profiles


@pytest.fixture
def clang_profile(tmp_path, monkeypatch):
    monkeypatch.setattr(compiler_profiles, "ROOT", tmp_path)
    monkeypatch.setattr(build, "wine_path", lambda path: str(path))
    files = {"clang-cl.exe": b"test clang", "libLLVM-23.dll": b"test LLVM"}
    archive = tmp_path / "vendor/clang23-x86/compiler.zip"
    archive.parent.mkdir(parents=True)
    with zipfile.ZipFile(archive, "w") as out:
        for name, data in files.items():
            out.writestr("bin/" + name, data)
    monkeypatch.setattr(compiler_profiles, "CLANG23_FILES", {
        name: hashlib.sha256(data).hexdigest() for name, data in files.items()}, raising=False)
    monkeypatch.setattr(compiler_profiles, "CLANG23_ARCHIVE_SHA256",
                        hashlib.sha256(archive.read_bytes()).hexdigest(), raising=False)
    source = tmp_path / "leaf.cpp"
    source.write_text("// compiler: clang23-x86\nvoid leaf() {}\n")
    return tmp_path, archive, source, files


def test_clang_archive_is_explicit_and_tracks_archive_and_executables(clang_profile):
    root, archive, source, files = clang_profile
    original = {"INCLUDE": "original headers", "LIB": "original libs", "PATH": "old"}
    compiler, env = compiler_profiles.select(source, Path("old/cl.exe"), original)
    assert compiler.name == "clang-cl.exe"
    assert compiler_profiles.command_options(compiler) == ["--target=i686-pc-windows-msvc"]
    assert compiler_profiles.command_options(Path("old/cl.exe")) == []
    assert env["INCLUDE"] == original["INCLUDE"]
    assert env["LIB"] == original["LIB"]
    inputs = json.loads(env["BFME_COMPILER_INPUTS"])
    assert inputs[archive.relative_to(root).as_posix()] == hashlib.sha256(archive.read_bytes()).hexdigest()
    for name, data in files.items():
        path = compiler.parent / name
        assert path.read_bytes() == data
        assert inputs[path.relative_to(root).as_posix()] == hashlib.sha256(data).hexdigest()
    assert build._cmd_fingerprint([str(compiler)], env) != build._cmd_fingerprint(["cl"], original)


def test_clang_translates_only_legacy_cpu_tuning_flags():
    flags = ["-O1", "-G5", "-G6", "-G7", "-arch:SSE", "-GS-", "-Gr"]
    assert compiler_profiles.source_options(Path("clang-cl.exe"), flags) == [
        "-O1", "/clang:-mtune=pentium", "/clang:-mtune=pentiumpro",
        "/clang:-mtune=pentium4", "-arch:SSE", "-GS-", "-Gr"]
    assert flags[1:4] == ["-G5", "-G6", "-G7"]


def test_msvc_source_flags_remain_identical():
    flags = ["-O1", "-G7", "-arch:SSE", "-GS-"]
    assert compiler_profiles.source_options(Path("cl.exe"), flags) == flags


def test_changed_clang_archive_refuses_before_extracting(clang_profile):
    root, archive, source, _ = clang_profile
    archive.write_bytes(archive.read_bytes() + b"changed")
    with pytest.raises(SystemExit, match="SHA256 mismatch"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})
    assert not (root / "build/compiler_profiles").exists()


def test_missing_clang_archive_refuses_without_fallback(clang_profile):
    _, archive, source, _ = clang_profile
    archive.unlink()
    with pytest.raises(SystemExit, match="cannot read"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})


def test_parallel_clang_first_use_observes_only_a_complete_cache(clang_profile):
    from concurrent.futures import ThreadPoolExecutor
    _, _, source, _ = clang_profile
    with ThreadPoolExecutor(max_workers=2) as pool:
        results = list(pool.map(lambda _: compiler_profiles.select(source, Path("old/cl.exe"), {}), range(2)))
    assert results[0] == results[1]


@pytest.mark.parametrize("change", ["changed", "missing"])
def test_changed_or_missing_extracted_clang_refuses_without_repair(clang_profile, change):
    _, _, source, _ = clang_profile
    compiler, _ = compiler_profiles.select(source, Path("old/cl.exe"), {})
    if change == "changed":
        compiler.write_bytes(b"modified executable")
    else:
        compiler.unlink()
    with pytest.raises(SystemExit, match="SHA256 mismatch|cannot read"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})


def test_clang_archive_cannot_smuggle_an_unlisted_file(clang_profile, monkeypatch):
    _, archive, source, _ = clang_profile
    with zipfile.ZipFile(archive, "a") as out:
        out.writestr("../outside.dll", b"not an admitted compiler input")
    monkeypatch.setattr(compiler_profiles, "CLANG23_ARCHIVE_SHA256",
                        hashlib.sha256(archive.read_bytes()).hexdigest())
    with pytest.raises(SystemExit, match="archive members"):
        compiler_profiles.select(source, Path("old/cl.exe"), {})


def test_changed_extracted_clang_during_compile_cannot_receive_receipt(clang_profile, monkeypatch):
    root, _, source, _ = clang_profile
    monkeypatch.setattr(build, "ROOT", root)
    compiler, env = compiler_profiles.select(source, Path("old/cl.exe"), {})
    (compiler.parent / "libLLVM-23.dll").write_bytes(b"changed during compile")
    output = root / "leaf.obj"
    output.write_bytes(b"object")
    build._write_deps_sidecar(source, output, "fingerprint", "", True, env=env)
    assert not output.with_suffix(".deps.json").exists()


@pytest.fixture
def profile(tmp_path, monkeypatch):
    monkeypatch.setattr(compiler_profiles, "ROOT", tmp_path)
    monkeypatch.setattr(build, "wine_path", lambda path: str(path))
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


def test_no_profile_preserves_compiler_environment_and_fingerprint(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "wine_path", lambda path: str(path))
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


def test_ddk_uses_its_own_files_and_cannot_reuse_an_sp1_receipt(profile, monkeypatch):
    root, directory, source = profile
    _, sp1 = compiler_profiles.select(source, Path("old/cl.exe"), {})
    ddk = root / "vendor/vc71-ddk-4035/bin"
    ddk.mkdir(parents=True)
    hashes = {}
    for name in compiler_profiles.SP1_FILES:
        data = ("DDK compiler " + name).encode()
        (ddk / name).write_bytes(data)
        hashes[name] = hashlib.sha256(data).hexdigest()
    monkeypatch.setattr(compiler_profiles, "DDK4035_FILES", hashes)
    source.write_text("// compiler: vc71-ddk-4035\n")
    compiler, env = compiler_profiles.select(source, Path("old/cl.exe"), {})
    assert compiler == ddk / "cl.exe"
    assert build._cmd_fingerprint(["cl"], env) != build._cmd_fingerprint(["cl"], sp1)
    (ddk / "c2.dll").write_bytes((directory / "c2.dll").read_bytes())
    with pytest.raises(SystemExit, match="SHA256 mismatch"):
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
