Ground-path optimizer accessor emission repair

At BFME2 base 005590d8f1bb7ebb1eed09ed163b4d5f60377b35,
PathRva00363FA4.cpp emits an unused three-byte PathNode::getNext COMDAT.
The consumer's field-at-zero view differs from the first indexed class view
in AIGroupMoveFormation.cpp. Mark the existing inline definition imported
forceinline, preserving its implementation while suppressing the competing
external copy. No import reference, new name, pin, layout, flags, header,
ledger row or baseline change is introduced.

Target evidence remains the existing complete 522-byte optimizer body at
00363FA4..003641AE, its caller 002EF908, the rowed layer-classification call,
and the independently established TheAI binding. BFME1/ZH supplies the donor
optimizer's semantics, not a recovered original target spelling or complete
PathNode layout. This repair makes no standalone retail identity claim for
either indexed accessor variant.

Before and after bounded prepare-current passes 1/1 and gives strict reusable
receipts. proof.py compares the original and current objects: all eight retained
nondebug sections preserve full bytes, flags, external definitions and symbolic
relocations. Only the unused 8b01c3 helper disappears. No retained relocation
targets that helper and no imported reference is added. The original source,
object and version-two receipt are preserved under ignored
build/path-next-link-20261015/before; recorded source/object/receipt hashes
identify both inputs.

The paired preview refreshes only this owned object into separate in-memory
copies of the identical index. The sole COMDAT finding disappears: legacy
predicted LINKED nonpadding bytes 0 -> 522. Ordinary link_check also reports
LINKS. The index measures ac77c85054, 2026-10-15 14:25, matching the committed
link-status queue's measurement. object-proof.json pins its SHA256. The other
indexed accessor provider and its unrelated blockers are untouched; its indexed
digest is recorded, but it has not been freshly prepared. The owned consumer
is self-strict; external provider currency is legacy. Closed-strict closure,
actual link placement and runtime behavior are unmeasured. Authored C++ growth
is zero. No census/index/status/history is rewritten.

Acceptance: independent normal byte gate 1/1, one float literal verified,
zero named imports, frozen-definition/class/new-variant checks pass, enforced
data has zero findings, converged data has zero second names at eight addresses,
EH has zero rowed graphs and zero missing objects, placement resweep has zero
bodies/pins, CSV and whitespace checks pass. checks.json records each command,
exit and output; accept.py repeats these bounded checks.

Shared-cause sweep: the frozen index contains exactly two getNext providers.
The formation consumer is the first copy and has no getNext blocker; its eleven
independent census findings require separate repairs. A bounded AI/Pathfinder
source search found that same private definition and the repaired optimizer.
No additional getNext repair is claimed. File and parent RVA were claimed
before editing. Discovery used repair_queue link, link_rank top/near/kind and
current-object checks; already repaired enemy-search and hunt getters were not
retried. No per-row data-back ranking was inferred from unavailable artifacts.

Donor review: retained verified BFME1 a7c38d3b2597121f178ab5190b3062478823257d;
reviewed 66b19a8e95a4add525ef808fcea088e306798e2b's imported-forceinline
emission repair and verification message. Its mechanism applies; Apt types,
layouts and linked-byte results do not transfer. Target object invariance is
the acceptance evidence here. Official BFME1 master was fetched read-only at
95eeb3bef370a7cd730b0ad5f228c317c8756e72. Another live file claim still holds
the reference update, including its comparative full-gate prerequisite. The
clean retained pointer was preserved and no freshness-success stamp written.
No full census, link cycle, nightly, boot or scheduler operation was run.

Reproduce at the recorded base/index: prepare-current the owned source, save
its source/object/receipt under the scratch before directory and its paired
findings/index hash as before.json; apply the patch and prepare-current again.
Run proof.py from the repository root. Committed JSON records this session's
exact measurements; binary objects remain local ignored evidence.
