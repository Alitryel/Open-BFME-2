LeftHUDInput cursor getter link repair
=====================================

LeftHUDInput.cpp now passes its existing m_cursorName field directly to
Mouse::getCursorIndex. The callback already inlined this access, but its
private CommandButton view emitted a surplus four-byte getCursorName
COMDAT (8d4150c3, +0x50). The first same-name copy in InGameUI.cpp reads
+0x2C (8d412cc3). Neither standalone getter has a proven retail address.
Removing the surplus helper clears this consumer's sole link blocker.

Target evidence: the complete LeftHUDInput body at 0x004020CE..0x00402455
is 903 bytes. Native 0x004023A2 contains 83c650 (add esi,0x50) when preparing
the cursor-name address. The body has no relocation to getCursorName.
FunctionLexicon identity, original reference provenance and private layout
claims remain as recorded in the existing source and ledger. The cursor-name
field label is carried from that source/reference; native independently
establishes the +0x50 address computation. This repair does not establish
InGameUI's +0x2C view as retail truth or add a class contract.

Baseline source revision: a4e3c8064b. Discovery queue: committed
link_status.csv at 67e1365aa9, 2026-10-13 16:47 UTC. Actual local comparison:
index 147cfae2cb, 2026-10-14 07:27; SHA256
690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Index/status/history remain untouched. No matching per-row data-back artifact
was used, and no sole_bytes ranking or placement gain is claimed.

The saved before and current after consumer objects were each substituted
into that same index together with the current, byte-verified InGameUI
provider object. Consumer legacy preview changes from one losing COMDAT
to clean, LINKED 0 -> 903 existing authored retail bytes. Provider findings
are exactly unchanged: 22 unresolved, 21 duplicate, 123 COMDAT and 26
wrong-selected findings. The generic getter remains selected from that
provider; the removed copy was not selected. This changes no provider used
by another unit. Paired CLI verification likewise reports 1 of 2 units
clean and 0 -> 903 bytes. Its exit1 reflects the unchanged provider blockers.

Acceptance evidence:
- Bounded link_check --prepare-current consumer before/after 1/1 and provider
  7/7 establish strict reusable compiler receipts and normal byte gates.
- ./build.sh consumer: 1/1 exact; zero baselined or skipped reference checks.
- Full object proof: exactly one unused four-byte getter removed. All four
  retained COMDAT bodies, extents and relocation digests are identical. All
  ordinary nondebug sections, undefined/strong/weak names, and hatch counts
  remain unchanged. The 903-byte parent body is identical before/after.
- Frozen-file, class gate, new-variants admission, CSV, whitespace and
  converged-data checks pass (eight addresses, zero second names).
- EH verifier: no applicable rows or missing objects.
- Affected-unit place_bodies resweep: zero bodies, zero pins.
- Shadow data reports the pre-existing MessageStreamSubsystem wrong-name
  reference at VA0x00A00950. Undefined/strong names and retained relocation
  facts are identical; this repair neither introduces nor resolves it.

BFME1 review: committed verified pointer
23b143233b5a8664a3bdf8572df6d905c310a5a1, with today's successful freshness
stamp. Reviewed d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: removing surplus
private wrapper emitters is applicable as a linking repair principle. Its
aliases, pins, addresses and layouts are inapplicable and were not imported.
The unchanged broader linking review was reused. No donor inputs changed.

New authored bytes: zero. Strict compiler currency is proven, but this is
legacy local preview evidence only. Self-strict placement, closed-strict
closure and a fresh maintained census gain remain unmeasured. No full link
cycle, census build/measure/history, nightly or boot runner was started.
The provider's missing dependencies and class/definition conflicts require
separate repairs. Source and object backups and the reproducible comparison
script are preserved under build/lefthud-cursor-link-20261014.
