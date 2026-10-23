# WeightInfoStruct provider rehome

Model gpt-6-astra, seat s5; input BFME2 7aae99cc67 and pinned BFME1
138757e9b74645fbcbb7724a7af2764e34931e11. No donor source was changed.

Move the existing 81-byte vector deleting destructor at RVA 0x0004554B
from W3DGhostObject.cpp to hanim.cpp. The destination already emits the
complete retail body and owns NamedPivotMapClass's destructor. The published
491a8b3d87 census reports both copies as retail with digest a68debbcea01.
No function, symbol, compiler option, header, or relocation was changed.

Validation:
- Initial focused hanim/colmathsphere gate: 26/26 rows.
- add_match --replace-existing for WeightInfoStruct: 25/25 hanim rows exact.
- prepare-current for hanim, colmathsphere, and W3DGhostObject: 29/29 exact;
  three strict reusable receipts. This does not establish link closure.
- Same-index link_check for hanim and W3DGhostObject: hanim LINKS,
  828 -> 908 linked bytes; old unit remains 0 -> 0 with its two unchanged
  unresolved GhostObject methods. Gain is 80 counted bytes (81-byte extent
  contains one 0xCC); zero newly recovered code. This is a scoped preview,
  not a fresh full census or a closed-strict link result.

Separate attempted rehome: existing Matrix3D constructor 0x000423C5/22B
into colmathsphere.cpp. add_match --replace-existing refused the unchanged
name/RVA/size because the pre-existing PristineBoneInfo folded row shares
that address. Matrix3D's row/source were preserved and the refusal recorded
as false-reject evidence. No gate workaround was attempted.

Correction and follow-up: the earlier Matrix3D refusal was caller error, not
a gate defect. add_match already supports --icf-owner. Supplying the existing
PristineBoneInfo owner with --replace-existing accepted the source-only
rehome and passed the normal 3/3 focused gate. The false-reject record is
retracted through re_log. No gate, source body or pin was modified.
