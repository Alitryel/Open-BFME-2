"""Read-only reproduction of the MD5 private-helper identity false rejection.

Requires current objects from build.sh for md5c.c and WWLib/md5.cpp. This script
does not compile sources, edit ledgers or run a linker.
"""
import csv
import json
import struct
import sys
from pathlib import Path

root = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(root / "tools"))
import allowed_symbols as allowed

source = "Code/GameEngine/Source/GameNetwork/GameSpy/md5c.c"
owner = "Code/Libraries/Source/WWVegas/WWLib/md5.cpp"
with (root / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
    rows = [row for row in csv.DictReader(handle) if row["source"] in {source, owner}]
ident = allowed.Identity(rows=rows, objs=[], defs={})
path = str(allowed.row_object(next(row for row in rows if row["source"] == source)))
obj = ident.obj(path)
results = []
for name, target in (("_MD5Transform", 0x606360), ("_MD5Update", 0x606C40),
                     ("_MD5Final", 0x606D00), ("_MD5Digest", 0x606DB0)):
    raw, size, relocs = obj.body(obj.by_name[name])
    native = ident.read(target, size)
    references = []
    for offset, kind, ref in relocs:
        if kind == allowed.REL32:
            addend = struct.unpack_from("<i", raw, offset)[0]
            dest = target + offset + 4 + struct.unpack_from("<i", native, offset)[0] - addend
            references.append({"offset": hex(offset), "symbol": ref["name"],
                               "storage": ref["storage"], "target": hex(dest)})
    results.append({"symbol": name, "rva": hex(target), "size": size,
                    "verdict": ident.certify(path, name, target),
                    "references": references})
print(json.dumps(results, indent=2))
if "--expect-fixed" in sys.argv:
    assert {item["symbol"]: item["verdict"] for item in results} == {
        "_MD5Transform": "retail", "_MD5Update": "retail",
        "_MD5Final": "unknown", "_MD5Digest": "retail",
    }, results
