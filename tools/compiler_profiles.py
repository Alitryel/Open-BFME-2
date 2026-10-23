"""Explicit, hash-pinned compiler variants; the default remains MSVC 7.1 RTM."""
import hashlib
import json
import os
import tempfile
import zipfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SP1_FILES = {
    "c1.dll": "a47ff094f591ac85777f568c44f2d0c9e94295184faa1fb785bbc6f89d887f07",
    "c1xx.dll": "42fd57f25e0b536b0b7a817f4ab3ec0aa23fcc5f8e52104ad6f12de167ad2cfa",
    "c2.dll": "7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5",
    "cl.exe": "333254d73ee602f6ec14b00e9bf40f533a1b181429943e3634971642af00c9f7",
    "msobj71.dll": "0ab2538c9a2cb03e5642c0bc744c193d79bab2bf22f906a6ee5ba9e7a0fb525b",
    "mspdb71.dll": "e952861ef44831b5cfaf44cc33dcfadcb77b550a3d1e27337e4727c07d332051",
    "msvcp71.dll": "6c483cbe349863c7dcf6f8cb7334e7d28c299e7d5aa063297ea2f62352f6bdd9",
    "msvcr71.dll": "c4d4339df314a27ff75a38967b7569d9962337b8d4cd4b0db3aba5ff72b2bfbb",
}

DDK4035_FILES = {
    "c1.dll": "31aad0d8d776d882ce7036b9f97c98a1d10fc1b8c068ebb9a2bb22a74225b4aa",
    "c1xx.dll": "884727948209dfd638596bd7256c881ea8cc71bdc99f02bdf6e0a1274966f0eb",
    "c2.dll": "5fdc4d339dd4f9cfbcb00bd2bc79622a7363aea64204a93c4bf66485886242ae",
    "cl.exe": "c9d1dce113f9fcb2ebbc588efebfdc146098b503e4bcdbb146fe61e00ea7d025",
    "msobj71.dll": "fa140fa0a6be92a45db726def4651fa63042b76a47acd163ec513157c485a524",
    "mspdb71.dll": "f7ffe701485813a7f10861bc61ba533b09f1386c40c882e832f71881a705c75b",
    "msvcp71.dll": "1d5a627cb700400a7de751f0e7d3bf2f024e8d79f8c4a9f11a5a20a05c73ab9f",
    "msvcr71.dll": "91961cc52149826031f1b17b65a95a5c84c89d9a42f8621a43448c0fe897a94f",
}

CLANG23_ARCHIVE_SHA256 = "809f74c74c28983bcd23360f17cf0ed877946065a6e58430214bb035ccd2cd2d"
CLANG23_FILES = {
    "clang-cl.exe": "09688e25f2993365fe7f58348a0e0db7d0748699bc65ef1e9bb37536b9038c68",
    "libLLVM-23.dll": "f4f37b67d7a9d0d8f04e3cb7fbbb6debaa2abeaa0f50455127034be61298b0c9",
    "libclang-cpp.dll": "8b83793d028859a940a4150b72a3b450115cf93915e282c5f8fad0e87ba677e3",
    "libc++.dll": "06a2ed158f5a91e4d500c8b0764a25dfe57097991d137d8272c529eeb5c66048",
    "libunwind.dll": "aa282fa47bb2c4e210cea5e470cdbdca58568f0be0bc73e404d86ab9cd95ef6a",
}


def _checked_input(path, expected, profile):
    try:
        actual = hashlib.sha256(path.read_bytes()).hexdigest()
    except OSError as exc:
        raise SystemExit(f"{profile}: cannot read {path}: {exc}") from exc
    if actual != expected:
        raise SystemExit(f"{profile}: SHA256 mismatch for {path}")


def _clang23(environment):
    """Expand only the pinned package; never repair a changed existing cache.

    The archive and each executable enter receipts independently. This catches
    an extracted DLL changing during compilation as well as a changed package.
    A temporary directory and atomic rename make concurrent first use safe.
    """
    profile = "clang23-x86"
    archive = ROOT / "vendor" / profile / "compiler.zip"
    _checked_input(archive, CLANG23_ARCHIVE_SHA256, profile)
    directory = ROOT / "build" / "compiler_profiles" / profile / CLANG23_ARCHIVE_SHA256
    if not directory.resolve().is_relative_to(ROOT.resolve()):
        raise SystemExit(f"{profile}: compiler cache escapes the workspace")
    if not directory.exists():
        try:
            with zipfile.ZipFile(archive) as package:
                names = package.namelist()
                if len(names) != len(CLANG23_FILES) or set(names) != {
                        "bin/" + name for name in CLANG23_FILES}:
                    raise SystemExit(f"{profile}: unexpected archive members")
                directory.parent.mkdir(parents=True, exist_ok=True)
                with tempfile.TemporaryDirectory(prefix="extract-", dir=directory.parent) as scratch:
                    temporary = Path(scratch)
                    for name, expected in CLANG23_FILES.items():
                        path = temporary / name
                        path.write_bytes(package.read("bin/" + name))
                        _checked_input(path, expected, profile)
                        path.chmod(0o755)
                    try:
                        temporary.rename(directory)
                    except OSError:
                        # Another compiler may have published its complete cache.
                        if not directory.is_dir():
                            raise
        except (OSError, zipfile.BadZipFile) as exc:
            raise SystemExit(f"{profile}: cannot extract {archive}: {exc}") from exc
    inputs = {archive.relative_to(ROOT).as_posix(): CLANG23_ARCHIVE_SHA256}
    for name, expected in CLANG23_FILES.items():
        path = directory / name
        _checked_input(path, expected, profile)
        inputs[path.relative_to(ROOT).as_posix()] = expected
    env = environment.copy()
    if os.name == "nt":
        env["PATH"] = str(directory) + os.pathsep + env.get("PATH", "")
    else:
        import build
        env["WINEPATH"] = build.wine_path(directory) + ";" + env.get("WINEPATH", "")
    env["BFME_COMPILER_INPUTS"] = json.dumps(inputs, sort_keys=True)
    env["BFME_COMPILER_PROFILE"] = hashlib.sha256(
        env["BFME_COMPILER_INPUTS"].encode()).hexdigest()
    return directory / "clang-cl.exe", env


def command_options(compiler):
    """The optional Clang profile always targets the game's x86 MSVC ABI."""
    return ["--target=i686-pc-windows-msvc"] if compiler.name == "clang-cl.exe" else []


def source_options(compiler, flags):
    """Express the region's old MSVC CPU tuning in Clang's option syntax."""
    if compiler.name != "clang-cl.exe":
        return flags
    tuning = {"-G5": "/clang:-mtune=pentium", "-G6": "/clang:-mtune=pentiumpro",
              "-G7": "/clang:-mtune=pentium4"}
    return [tuning.get(flag, flag) for flag in flags]


def select(source, default_compiler, environment):
    """Select only a declared profile, preserving the verified RTM headers/libs.

    There is no fallback if a requested profile is missing, unknown or changed.
    Hashes enter both the command fingerprint and the ordinary dependency receipt.
    Verify the files on every selection, including a cache-currency check.
    """
    directives = [line[len("// compiler:"):].strip()
                  for line in source.read_text(encoding="utf-8-sig", errors="replace").splitlines()
                  if line.startswith("// compiler:")]
    if not directives:
        return default_compiler, environment
    if len(directives) != 1 or directives[0] not in ("vc71-sp1", "vc71-ddk-4035", "clang23-x86"):
        raise SystemExit(f"{source}: expected one known '// compiler:' directive")
    profile = directives[0]
    if profile == "clang23-x86":
        return _clang23(environment)
    files = SP1_FILES if profile == "vc71-sp1" else DDK4035_FILES
    directory = ROOT / "vendor" / profile / "bin"
    inputs = {}
    for name, expected in files.items():
        path = directory / name
        try:
            actual = hashlib.sha256(path.read_bytes()).hexdigest()
        except OSError as exc:
            raise SystemExit(f"{profile}: cannot read {path}: {exc}") from exc
        if actual != expected:
            raise SystemExit(f"{profile}: SHA256 mismatch for {path}")
        inputs[path.relative_to(ROOT).as_posix()] = expected
    env = environment.copy()
    # The executable and its DLLs stay together. INCLUDE and LIB deliberately
    # remain the ordinary submodule's, so selecting SP1 changes no headers.
    if os.name == "nt":
        env["PATH"] = str(directory) + os.pathsep + env.get("PATH", "")
    else:
        import build
        env["WINEPATH"] = build.wine_path(directory) + ";" + env.get("WINEPATH", "")
    env["BFME_COMPILER_INPUTS"] = json.dumps(inputs, sort_keys=True)
    env["BFME_COMPILER_PROFILE"] = hashlib.sha256(
        env["BFME_COMPILER_INPUTS"].encode()).hexdigest()
    return directory / "cl.exe", env
