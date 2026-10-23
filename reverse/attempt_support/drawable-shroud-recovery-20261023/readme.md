# Exact Drawable shroud notification

`?onComingOutOfShroud@Drawable@@AAEXXZ`, retail
`0x0027893E..0x00278C29`, 747 bytes, is now exact. The compiler's 10-byte
EH handler at `0x007735D3` is rowed from the same object. Its static-guard
unwind funclet is already matched at `0x007735C6` (13 bytes), under
`Rva007735C6ClearFlag` in GlobalFlagClearers_DFECxx.cpp. The exact parent EH
graph binds the current compiler label `$L13619` to that address; there is no
uncovered cleanup body and no second row was added. The two existing
callbacks remain exact.

Input BFME2: `060ad76780dced93c6d7c28bc7a3fda246b98464`; committed, clean
BFME1: `f890413e75e671748215ba2ef3304aa7953993e9`. The runner's active BFME1
freshness lock belonged to codex4; this seat followed the lock rule and did
not advance that pointer. Compiler flags remain those of the bank: O1, Ob1,
d2inlS100, G7, SSE, MD, EHsc, NDEBUG and static STLport. Model gpt-6.1-sol.

## Evidence and closure

The complete picker history and the bitset, tail and join-review handoffs
were read first. They had already excluded ordinary declaration/carrier,
helper visibility, layout and compiler-flag explanations. The starting
748-byte bank has one nonrelocation difference: at +2BA, it reloads Object
from `[ebp-10]` instead of moving the already live EDX into ECX. Its shared
notification source repairs the earlier holder/template allocation, while
separate sources recover EDX but regress the earlier allocation.

Two new finite families used isolated objects and eight compiler workers:

* Qualification of eight existing reads: 256 generated/compiled sources,
  four distinct bodies, no improvement.
* Equivalent-path reference costs: shared/separate final notification
  sources crossed with 13 existing operations and six defined predicates,
  plus two controls: 158 generated/compiled sources, 30 distinct bodies.
  Nine variants emit the same exact 747-byte body.

The retained source uses the separate revealed and shrouded event sources
shown by WB, and duplicates the existing CastleMemberBehavior `findModule`
assignment under the existing alt-event flag. Both arms perform the same
call with the same arguments. C2 merges the condition and duplicate call
away, retaining different allocation costs: holder/template allocation now
agrees with retail, while the late receiver remains `mov ecx,edx`.
Duplicating the castle lookup or castle Drawable lookup at the same region
under any of three predicates also closes it. This is a source adaptation,
not evidence that the original source contained the duplicate branch.

WB CA3700's method/file identity, the retail caller and target field accesses
retain the provenance detailed in `drawable-shroud-bitset-20261020.md`.
The target establishes the event/status offsets and 218-bit KindOf storage;
ZH BitFlags remains only a semantic guide. No stronger identity is claimed
for the inherited holder/module/nearest placeholder names or views.

## Integration and acceptance

The method shares the existing `DrawableShroud.cpp` callback unit. Its views
were reconciled with the bank instead of introducing another private-view
unit or replacing the incompatible ZH-shaped Drawable.cpp headers. Both
original callbacks still reproduce all 107 and 28 bytes. No pin, alias,
baseline, whitelist, shared header or verifier change was needed.

* Both `add_match.py` invocations ran the ordinary build gate; final result
  4/4 matched, with string/float/import checks passing.
* Full COFF extents and resolved relative calls independently equal retail
  for all four rows; `verification.json` records sizes and hashes. The handler
  address is the retail parent's initial push immediate, minus image base.
* `eh_verify.py`: one EH graph, EXACT; `verified_funclet_locations` confirms
  `$L13619` at the already covered 0x7735C6. No missing unwind rows.
* `find_declared_unmatched.py`: all definitions matched.
* `link_check.py`: LINKS, existing 135 to 891 bytes in the stored-index preview.
  This is not a new link census.
* `place_bodies.py`: zero additional bodies or pins.

`search.py.txt` replays the search from the recorded input bank. Copy it to
`build/shroud-27893e-20261023/search.py` before running; all its objects are
private scratch. The normal gate, not the search's instruction score, is
the admission authority. `search-summary.json` preserves compact counts and
winner names. Scratch logs and objects remain under that build directory.
