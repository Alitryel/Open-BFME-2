"""Read-only reproduction against current normal-build objects and link index."""
import csv
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import allowed_symbols
import build
import link_census
import link_check
import link_debt

source = "Code/GameEngine/Source/GameClient/WeatherSettingCtor.cpp"
obj = allowed_symbols.Obj(build.obj_path(ROOT / source))
names = {symbol["name"] for symbol in obj.symbols.values()}
with (ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
    rows = [row for row in csv.DictReader(handle)
            if row["name"] in names or row["source"] == source]
truth = link_census.RetailTruth(rows)
index = link_check.load_index()
fact = link_census.object_facts(obj.path, truth)
selected = lambda name: link_check.scalar_callee_holder(name, obj.path, fact, index)
text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
callee = "?setFromInt@RGBColor@@QAEXH@Z"
result = {
    "source": source,
    "source_sha256": hashlib.sha256((ROOT / source).read_bytes()).hexdigest(),
    "object": obj.path.relative_to(ROOT).as_posix(),
    "object_sha256": hashlib.sha256(obj.data).hexdigest(),
    "text_only": link_debt.addresses(text),
    "with_compiled_proof": link_debt.addresses(
        text, source=source, obj=obj.path, truth=truth, selected=selected),
    "selected_callee_object": selected(callee),
    "whole_callee_proof": link_debt._ScalarCalls(truth, selected)._consumer(callee),
    "caller_rva": "0x201618",
    "caller_size": 503,
    "push_offset": "0x175",
    "call_offset": "0x185",
    "call_relocation_offset": "0x186",
    "callee_rva": "0x4edf",
    "callee_size": 76,
    "remaining_conservative": {},
}
for other in [
    "Code/GameEngine/Source/Common/Rva0059675ACtor.cpp",
    "Code/Libraries/Source/WWVegas/WW3D2/Rva0012CB67AssetReader.cpp",
]:
    result["remaining_conservative"][other] = link_debt.addresses(
        (ROOT / other).read_text(encoding="utf-8", errors="replace"))
print(json.dumps(result, indent=2))
assert result["text_only"] == ["0x886655"]
assert result["with_compiled_proof"] == []
assert result["whole_callee_proof"]
