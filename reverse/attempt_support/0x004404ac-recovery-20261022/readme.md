# AptMpGameSetup 0x004404AC: exact 526-byte recovery

The address-derived member now matches all 526 bytes and all 25 relocations
in its home unit, `Rva0043F483PopulatePlayerCombo.cpp`. Target evidence remains
the WB twin at 0x0149E9C0, the slot-refresh caller, field accesses and callees;
the name is not a recovered original identifier. This is a retail-guided C++
reconstruction, not a new reference transfer or layout claim.

The incoming bank from commit 95f76259b1 had the correct instruction sequence
and five EAX/ECX operand differences. The earlier duplicated team block had
already closed the persistent receiver/index ESI/EDI exchange. Read the
preceding `0x004404ac-mergeweb-20261022` handoff for exclusions; those searches
were not repeated.

## Closing hypothesis

A second, nested equivalent control merge raises the team-window value's
allocation priority relative to the short-lived locked flag. In each existing
`slot == 0` arm, name the initial team window. In the disabled path, branch on
`window == combo.m_window` with an identical HideList call in both arms. Keep
the post-call `*team` reload: HideList may mutate that storage. C2 removes both
the nested branch and the existing outer duplicate but retains allocation
costs which select retail's registers. The predicates are defined, side-effect
free and compare existing pointers. This graph does not claim original source
spelling. Collapsing the equivalent branches loses the match.

Read-only C2 traces measured priority 5 for both window and locked in the bank
and in a named-window control. In `localgraph-0108`, window rises to 8 while
locked stays 5 in both arms. Persistent receiver/index roles stay correct.
The compiler and its memory were never patched; tracing only set breakpoints
and read state using the existing mergeweb trace machinery.

## New searches

| Family | Successful compiles | Finding |
| --- | ---: | --- |
| Asymmetric flag and window forms | 1,024 | Independent polarity, type, output initialization, ternary shape and named-window choices do not close the residue. |
| Forceinline local preparation helpers | 256 | Pointer/reference outputs, aggregate returns, constructors and flag types do not close it; no unresolved helpers. |
| Multiway outer merge graphs | 240 | Flat, switch and balanced forms over 3/4/5/8/16 arms do not improve it. |
| Nested local merge boundaries | 504 | Eight predicates, seven boundaries, three control forms and either/both outer arms produce exact variants. Smallest selected variant is localgraph-0108. |

`results.json` records compact results and all exact variant names. The driver
is `search_new.py.txt`; copy it to ignored `build/4404ac-affinity/search_new.py`.
It imports the preceding mergeweb `search.py`, which uses isolated objects,
eight workers, `build.compiler_command` and whole-extent relocation-aware
comparison. Never use `build.compile_source` for scratch variants. Recover the
input as `build/4404ac-affinity/control.cpp` from the bank at 95f76259b1, and
prepare mergeweb's original `bank.cpp` as its handoff describes. Inputs and
hashes are in `inputs.json`. Flags remain the home's `/O1`, `/MD`, `/EHsc`,
`/DNDEBUG`, static STLport and BFME2 ASCII shim, MSVC 13.10.3077 under Wine.

## Linking and EH coverage

The new parent introduced unresolved wrapper copy-constructor/destructor
references. Their existing pins identify complete 13-byte one-pointer copy
and one-byte empty destruction bodies. Definitions now live beside the
wrapper's existing drop-down member in `GadgetImageComboBox.cpp`, away from
the parent's compilation context. Both are byte-verified folds onto existing
owners; no new pin or unique retail extent is claimed for them.

The parent's full EH data verifies EXACT. Its own object places cleanup
`$L6392` at 0x00788A56 and its 10-byte handler at 0x00788A5E, with no placement
conflicts (`eh-placement.json`). Both extents were already rowed from
`MpGameSetupSlots_Init_InitGadgets.cpp` under the 0x0043ECC1 parent's graph.
They are already covered, so this landing adds no duplicate EH rows.

Both affected units pass their normal byte gates (6/6 and 12/12 rows), source
claims, literals, floats and imports. EH verification passes all four parent
graphs across the two units. Frozen-file checks pass. With the two providers
present, `link_check.py` reports both units LINKS: the home grows from 1,080 to
1,606 linked bytes and the gadget unit from 1,802 to 1,816 against the published
2026-10-22 17:08 census. The latter 14 bytes are existing folds, not new unique
retail coverage.

The initial ledger check passed. BFME1 remained the clean committed verified
pointer 42bba2ddbd5cb895d99293583891d3b7315fa49e; another seat's fresh updater
lock, owner claudec2, required skipping a concurrent pointer update. No
freshness success was stamped and its lock was left alone. No maintained
verification runner was started.
