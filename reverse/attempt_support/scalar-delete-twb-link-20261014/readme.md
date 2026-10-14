# Scalar delete dependency repair

Base checkout: `b123cb382c`. The available census index measures
`cb660e4d97`, 2026-10-13 04:02 UTC; its hash is recorded in both proof files.
The committed repair queue measures `67e1365aa9` and supplied discovery only.
No per-row data-back artifact, census rebuild, status edit, or full link cycle
was used.

The consumer `BfmeConv1325.cpp` called the invented `bfmeFreeTWB` name.
Target evidence: its existing 68-byte body at RVA `0x006634E0` has a REL32
operand reaching `0x0002FD60`, the complete 21-byte scalar operator delete
owned by `WWLib/mem_ops.cpp`. That provider's existing declaration proves the
one-pointer cdecl ABI. The consumer now calls `::operator delete` directly.
Remove the unused provider alternatename, the obsolete symbols.csv pin, and
exactly that alternatename's hatch-baseline key. No other consumer of the old
name exists in Code. Donor identity/layout uncertainty remains unchanged.

Donor review: official BFME 1 master fetched at
`85106095550c4ceb39c5daaa707795a9ab4e5f40`. Repair
`e0c623620c077cc216eb49c8e74c16e6349a9a7d` removes invented scalar-delete
stand-ins in three donor units with byte gates and local link previews.
Its direct-provider principle applies here; its names and address do not.
Repair `262d3e950` was also screened: BFME 2 already removed part_ldr's
duplicate Convert_To_Ver2 and its current local preview LINKS (5,216 bytes).
The last verified BFME 1 input pointer remains `cee35b7d8`; the previous
session's comparative full-gate update audit is still unfinished. Neither
the reference checkout/pointer nor its successful freshness stamp was advanced.

Acceptance before and after: bounded link_check --prepare-current verifies
all six rows in the two owned files with strict reusable receipts. The final
ordinary ./build.sh gate also passes 6/6, no skipped or baselined references.
All six emitted whole-body hashes are unchanged. Exactly one relocation name
changes, bfmeFreeTWB to global scalar operator delete; its native destination
is unchanged. Proofs retain all other bindings and index provenance.

Local link preview is legacy census closure with self-strict current objects,
not closed-strict or an actual link.exe placement. Before/after findings are
identical: provider LINKS (80 -> 80 bytes); consumer still has the unresolved
`?g_bfmeVftCTWA@@3PAPAXA` and contributes zero linked bytes. New authored C++
bytes and incremental linked bytes are zero. Verified improvement: one
obsolete alternatename removed, its keyed hatch debt lowered by one, and one
redundant pin removed. No newly invented alias, pin, class, layout or range.

Declared-definition, CSV, pin consistency and diff-whitespace checks pass.
Data check reports zero findings; enforced converged-data check reports zero
second names and zero unjudged rows across eight addresses. Broader closure
measurement and the remaining vtable provider are outstanding.

## Preparation recovery (2026-10-14)

The runner stopped replaying `45e415b091` onto `2f2baa4818`. Upstream already
landed this consumer's direct scalar-delete call and removed its stand-in
alias, pin and hatch key in `147cfae2cb`. The only source conflict was the
redundant operator-delete declaration. Retain upstream's declaration-free
code: no Code or function/symbol/hatch ledger delta remains from the
synchronized upstream. Rebase completed with `GIT_EDITOR=true git rebase
--continue`; the recovered commit preserves the historical evidence above.
No additional repair gain or authored C++ bytes is claimed.

Applied stash `2b901f89cdb9568e27ca393e04e245cfbf6420e8` with `--index`.
It has no staged or unstaged tracked delta. All 31 saved untracked files
(20 existing generated dumps and 11 ZH sweep artifacts) were restored
byte-for-byte and remain untracked. `recovery-inventory.json` accounts for
each path and digest. Stash and backup ref
`refs/runner/preparation/1791953168545404500` remain intact. The conflict
index is clear, and the recorded upstream is an ancestor of the recovered
HEAD. No new task, source reconstruction or claim was started.

Reconciliation checks at recovered HEAD:

- `link_check.py --prepare-current` for BfmeConv1325.cpp and mem_ops.cpp:
  six rows exact with strict reusable self receipts; no census/index/status
  update. Ordinary `./build.sh` repeats 6/6 with all reference gates clear
  (`byte-recovery.txt`).
- Local `link_check.py` repeats the historical census result exactly except
  elapsed time (`link-recovery.txt`): provider LINKS 80 bytes; consumer 0
  bytes with unresolved `?g_bfmeVftCTWA@@3PAPAXA`. Exit 1 is the same known
  consumer blocker, not a recovery regression. This is self-strict plus
  legacy census closure at `cb660e4d97`, not closed-strict or an actual link.
- CSV, declaration, pin-consistency and whitespace checks pass; data shadow
  has zero findings, and enforced converged-data has zero second names or
  unjudged rows across eight protected addresses.

BFME 1 official master was fetched again and is now `fea964f85433`. The
clean checkout still equals the last verified committed pointer `cee35b7d8`.
The prior comparative pointer-update audit remains unfinished; recovery
does not advance the pointer or its successful freshness stamp. The known
vtable provider and broader maintainer-only closure remain outstanding.
