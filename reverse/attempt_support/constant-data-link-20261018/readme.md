# Constant data link repairs, 2026-10-18

Three current consumers each lacked one data definition. Define their existing
external names in their home units; no new alias, pin, function row or private
class view is introduced.

Target evidence is independent of donor names: INI callback 0x0033940F uses the
32 bytes at VA 0x00C0EA88, including the entire diagnostic and zero padding.
Constructor 0x005380A8 reads four bytes at VA 0x00C691E8, 0x3D75C290 (one ULP
above 0.06f). The explicit decimal retains those exact bits. Decal method
0x000B9CE8 indexes the seven pointers at VA 0x00DB4E8C. Each complete pointed-to
string is verified, including entry 6 repeating entry 4. ZH's corresponding
entry is EXHordeC_UP, so that donor value is not inherited. Source comments
retain neutral identity/layout qualifications from the original recoveries.
The verified BFME 1 pointer 64d369b901 was reviewed; no source update was needed.

`data-proof.json` compares both scalar objects directly with retail, and every
table relocation and complete target string. The scripts and original objects
are retained locally under build/constdata-link-20261018. `object-proof.json`
compares paired before/after objects against one unchanged published index
(c2c5ac8c27). Retained COMDAT digests and weak bindings stay unchanged except the decal
method's relocation spelling: its raw bytes and all other relocations remain
identical, while the former shadow-manager alias now names the real global
directly. The redundant /alternatename is removed. Each missing data reference
becomes a real definition.

Acceptance: self-strict reusable byte receipts, 5/5 function rows, string,
float and import reference gates pass. Paired bounded legacy link preview:
0/3 -> 3/3 clean, 0 -> 622 nonpadding authored bytes (236 + 149 + 237).
Unreferenced diagnostic copies remain diagnostic only. No added authored C++
coverage, closed-strict measurement, census or full-link/runtime claim.
