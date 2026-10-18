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
    if directives != ["vc71-sp1"]:
        raise SystemExit(f"{source}: expected one '// compiler: vc71-sp1' directive")
    directory = ROOT / "vendor" / "vc71-sp1" / "bin"
    inputs = {}
    for name, expected in SP1_FILES.items():
        path = directory / name
        try:
            actual = hashlib.sha256(path.read_bytes()).hexdigest()
        except OSError as exc:
            raise SystemExit(f"vc71-sp1: cannot read {path}: {exc}") from exc
        if actual != expected:
            raise SystemExit(f"vc71-sp1: SHA256 mismatch for {path}")
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
