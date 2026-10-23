# Three Miles import tail thunks, 2026-10-23

Recoveries: 0x629D92 (AIL_set_3D_orientation@28), 0x629EA0
(AIL_quick_startup@20), 0x629EF4 (AIL_stream_info@20), six bytes each.
Their whole FF25 boundaries and named mss32 IAT slots were established by the
previous attempts. Existing caller declarations supply ABI views; this does
not identify the original source prototypes beyond the proven import names.

The region /O1 controls reproduce the earlier blocker. With real float
parameters the orientation wrapper even copies arguments through x87; /Oy,
/Ob2 and /Og do not repair it. /O1 /Ot and /O2 each emit only FF25 plus one IAT
relocation. The source uses O2 in a dedicated three-function unit.

flag_defaults.py propose compiled the actual unit both ways, found all three
rows lost under region defaults, and wrote one tool-owned override. No default,
shared header, compiler executable or verifier rule was changed. Temporary
unverified ledger declarations were used only to supply the tool's scan inputs;
they were followed immediately by its comparison and the normal build gate.
Then all three rows were admitted again through normal verifying add_match
--replace-existing, recording the landings and keeping claims until publication.
Normal build reports 3/3 whole bodies exact and 3/3 named imports verified.
No inline assembly, speculative import alias, or generated stub was added.

The last EH stub remains dependent on the separately claimed queueSupplyTruck:
its handler RVA is 0x792E4C. No overlapping work on that parent was attempted.

The outside-attempt inventory is mostly existing source excluded by the
headline metric: MMX_idct and MMX_idct10_DX account for 5909 real bytes;
StackProbeBodyThunk, RTC_CheckEsp and EH_prolog account for another 127.
The 14-byte BitFlags<116>::clear row at 0x666E80 and an unowned two-byte
range at 0x579674 merit separate inspection. A 4094-real-byte DirectInput
keyboard-format data range is in the unbanked-attempt bucket, not a function.
These observations are classification, not recovered bytes. The scratch
inventory snapshots are in build/goal_{unbanked,outside}_inventory.json.
