# FileInfo placement-copy linkage

Inputs: BFME2 487c6371a3, verified BFME1 pointer 92f6bbe8e1dc,
unchanged retail-truth-2 census/index 5366c4f808 (2026-10-20 12:21).
BFME1 unique-owner linking repair 51b97cd79642 was reviewed as a technique;
the bindings and code identity here come from BFME2 bytes and existing rows.

Retail calls at 217858, 217883, 218B73 and 218DE4 target 21781D,
a 45-byte null-guarded placement-copy helper calling FileInfoStruct's
rowed constructor 217624. Its former ledger name dup_0021781D had no
object definition: an object-symbol alias borrowed the template name
already owned by the distinct native body 63CBC. Replace that owner with
Rva0021781DConstruct and direct typed calls; remove the obsolete alias pin.
The address-derived name preserves uncertainty about the original spelling.
No new pin, alias or class/layout claim is introduced.

The allocate_copy unit's explicit vector instantiation also emitted a
non-retail overflow. Declare the existing specialization instead; this is
a verified prerequisite for the larger 180-byte overflow unit to link.
The allocation unit itself remains blocked on other STL copies and assignment.
The push_back unit's typed-call change is required by the owner migration;
its own link blockers remain. MixFileCreatorParse was tested and fully restored:
its additional blockers need a separate repair, and its change was unnecessary
for this gain.

Same-index current-object LEGACY preview before/after:

| Unit | Bytes linked before | Bytes linked after |
| --- | ---: | ---: |
| construct_game_structs2 | 190 | 190 |
| uninit_copy_0021784A | 0 | 38 |
| uninit_fill_00217870 | 0 | 37 |
| vector_fileinfo_insert_overflow | 0 | 180 |
| vector_fileinfo_pushback | 0 | 0 |
| vector_fileinfo_allocate_copy | 0 | 0 |

Total 190 -> 445, **+255 existing retail bytes**. No closed-strict or
full-link gain is claimed. Byte gate and self-strict prepare-current receipts
verify all 16 rows in six touched units, including the provider's EH bodies.
Three compiler-local cleanup labels renumber, but the normal verifier proves
their bytes and parent EH placement. No EH verification was disabled.

Two careful push_back suppression trials failed and were reverted:
1. Declaration-only overflow introduces a false-type zero store, 55 -> 58 B.
2. Taking padding through &__x (a reference) addresses the referent rather than
   the argument slot and loses the native EBP frame. Retail uses [ebp+0Bh].
Do not retry those removals without a visible-body/argument-lifetime explanation.
The exact original push_back shape remains, with only the typed callee binding.

Two hatch-register entries shrink: the 21781D object-symbol row and pin.
