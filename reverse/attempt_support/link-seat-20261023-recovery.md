# Preparation recovery, 2026-10-23

Recovered this checkout's four retained commits after the runner's completed
rebase. There is no remaining rebase, stash, resync stash, conflict index or
untracked saved edit. The original work remains reachable through
`refs/runner/preparation/1792742353544830944`; no backup was removed.

The recovery push-hook dry run passed all 98,111 function rows, 2,140 data rows,
literal/import checks and the no-op patch, then refused the already documented
FireWeaponWhenDeadBehavior DIR32 discrepancy. Its UpdateModule-qualified vtable
name still resolves to both 0x00C496E8 and 0x00C497B4. The affected destructor
and sibling RVAs are claimed by another worker. No class source was changed,
no verifier was weakened, and all temporary investigation claims were released.

Use the recovery instruction's withdrawal option for the reference update:
restore the upstream-pinned BFME 1 revision
138757e9b74645fbcbb7724a7af2764e34931e11. The proposed revision
74ea60ad41eff2841366bc177538571a31cc2781 and its earlier successful verification
remain in the retained history and backup. Its earlier freshness marker is
preserved locally as build/recovery-bfme1-last-check-74ea60ad.txt; it is no longer
the active freshness marker. The upstream class-view discrepancy must be
reconciled before retrying the reference update's full verification. Do not
infer that the update was freshly verified from the historical handoffs.

The independently retained wide-record list repair also verifies against the
restored reference inputs. Neither revision changes any donor header, and the
normal dependency cache confirms the list object's inputs remain current.

* `./build.sh Code/Libraries/Source/WWVegas/WWLib/stlport_list_002b8ff3_fill.cpp`:
  4/4 function rows and all scoped reference checks pass.
* `tools/check_csv.py` and the unit's `find_declared_unmatched.py`: pass.
* `tools/link_check.py --prepare-current` for the list unit: 1/1 provider
  byte-verified with strict reusable receipts; census/index/status unchanged.
* Paired `tools/link_check.py` with unicode_string.cpp and
  stlport_list_unicodestring_create_node.cpp: 3/3 link, 425 -> 541 B;
  the repaired list contributes 0 -> 116 B and both providers remain linked.

This is a legacy current-object link preview. Self-strict receipts and the
ordinary byte gate establish the unit's bytes; they do not establish
closed-strict or a fresh saved-census gain. The two ICF rows add zero unique
authored C++ bytes. Earlier MpCombo and Pod88 trials remain banked in the
existing handoffs; the redundant DieModule alternative remains superseded by
the upstream provider. Recovery does not reopen those tasks.
