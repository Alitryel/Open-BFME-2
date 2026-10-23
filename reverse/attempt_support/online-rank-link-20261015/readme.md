# Online ladder-rank data ownership, 2026-10-15

Three units referenced two undefined address-named integers. Define each once in
PersistentStorageThread.cpp and share the descriptive names
BfmeOnlineLadderRank1v1 and BfmeOnlineLadderRank2v2. Own their complete four-byte
cells at retail RVAs A02548 and A0254C. No function row, pin, alias, class layout,
compiler flag, shared header or verifier baseline changes.

Base: 3940cf04819f30f6715a8430fea482b2bf96cbee. All three files were claimed
before editing. The two previously verified local commits were preserved.

## Identity and extent

Native HandlePersistentStorageResponses at 5BDAC1 writes the cells for mode 1
and mode 2. AptOnlineCustomMatch at 5A20A7 formats the values with literal keys
LadderRank1v1 and LadderRank2v2. AptOnlineQuickMatch at 5BBF15 selects them for
the same two modes. The byte-verified bodies prove the integer operands and
four-byte extent; retail initializes both cells to zero. The data gate checks
each complete cell against its compiled definition. proof.json records all six
native operand sites and full hashes of the three matched consumers.

These are descriptive identifiers; the original retail spelling is unknown.
No donor name, layout or address is asserted. Reviewed BFME1 linking repair
92a8d854746f059994f8ab370c133f3ba71eec24: reuse a single verified data owner
rather than introducing another undefined global. That ownership principle
applies; these cells had no existing definition. The retained BFME1 source had
no same-name ladder-rank lead to inherit.

## Paired local acceptance

The frozen index is the update at 19a2565407, 2026-10-15 09:33, based on census
5986a99448 at 04:52. SHA256 and strict source/object/receipt hashes are recorded
in proof.json. Both phases replace only the three explicitly prepared objects
in memory in copies of that same index. No index, status, census artifact or
measurement history was rewritten. The committed queue served discovery only.

- Strict preparation before and after and ./build.sh pass all 227 code rows.
  There are 88 verified literals, 21 empty-string references, 25 compiler float
  literals and 21 imports, with no skipped or baselined literal references.
- Both new data rows verify, and EH data is EXACT for all 51 applicable rows,
  with no absent objects, nonexact rows or baseline exceptions.
- Every pre-existing nondebug section, including code, local helpers, COMDATs,
  EH data, directives and normalized relocations, is identical. The only
  section change is extension of the provider's zero-initialized .bss from
  four to twelve bytes. Its existing queue global stays at offset zero; the
  rank globals occupy offsets four and eight. No existing definition moves.
  The two undefined globals become defined only in the provider. Consumer
  bindings differ solely by the recorded name substitution.
- Paired legacy findings fall 87 -> 81. PersistentStorageThread unresolved
  bindings fall 2 -> 0; custom-match 2 -> 0; quick-match 7 -> 5. All duplicate,
  COMDAT, address and selected-definition findings are exactly unchanged.
  Ordinary local link_check agrees: all three units still have independent
  blockers, and existing authored LINKED bytes remain 0 -> 0.
- Class, declared-definition, new-variant admission, whitespace and CSV checks
  pass. Converged data checks eight protected addresses with zero second names
  or unjudged rows. Shadow data retains the independent quick-match names
  TheLadderList at A05FB0 and g_00DB9198 at 9B9198.
- Placement resweep finds zero bodies and zero pins.

The generated scratch data ledger has 520 unrelated matched sources without
objects. Only its two exact A02548/A0254C rows were selected into the tracked
ledger. Each now has one definition and three references, matching the strict
objects prepared here. No whole-inventory refresh is claimed.

This repair adds eight owned data bytes and zero authored C++ code bytes.
Strict receipts prove compiler input currency, not executable placement or
closed-strict link closure. No self-strict or closed-strict gain, new census
result or runtime result is claimed. Full link cycles, census rebuilds,
nightlies and boot/scheduler checks were not run.

## Handoff

The retained blockers are STLport COMDAT/selected-provider differences and
Xfer's selected destructor; quick-match additionally has five unresolved
bindings. They need separate supported shared-dependency repairs. The unchanged
setDisabledUntil and string-lookup codegen blockers were not retried.

Official BFME1 master was fetched at 139ec64386d2a0a49d16ebfe0f14dddec3424c2c.
The clean verified checkout and gitlink remain
 a7c38d3b2597121f178ab5190b3062478823257d. Another worker owns
file:reference/open-bfme-1. Freshness remains due: the comparative update still
requires the old-input full baseline rebuild recorded in attempt 53899. No
pointer advancement or successful freshness stamp was made here.

proof.py replays the evidence using this session's ignored snapshots under
build/online-rank-link-20261015 and its frozen index. It is not an acceptance
gate or an independently portable test. Model: gpt-6.1-sol.
