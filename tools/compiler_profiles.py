"""Explicit, hash-pinned compiler variants; the default remains MSVC 7.1 RTM."""
import hashlib
import json
import os
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
    if len(directives) != 1 or directives[0] not in ("vc71-sp1", "vc71-ddk-4035"):
        raise SystemExit(f"{source}: expected one known '// compiler:' directive")
    profile = directives[0]
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
