# Narrow string destructor provider linkage repair

At BFME 2 base `45baf83306aabea4955ecf5ff879be47a7ca01e3`, change the public
`StringBase<char>` destructor provider from an explicit specialization to an
explicit instantiation of the template definition. The implementation and its
133-byte extent remain identical. MSVC changes its COMDAT selection from
NODUPLICATES (1) to ANY (2), allowing the verified definition to coexist with
callers' inline copies. No source headers, function rows, pins or hatches change.

## Target evidence and local acceptance

The existing fold-proof row identifies the public destructor with retail's
narrow release worker at RVA `0x00036410`. This repair retains that complete
body, rather than emitting a forwarding wrapper. `proof.json` records identical
133 raw bytes and relocation tuples before and after; the selection flag and
exclusive-definition classification change. The census truth helper reports
this folded name as unknown; the full byte gate and existing fold evidence,
not that helper verdict, establish its retail correspondence.

`./build.sh` passes 7/7 provider rows, six named imports and all string/float
checks. The explicit bounded cohort preparation passes 11/11 rows and creates
strict reusable self receipts for the provider and these unchanged consumers:

- `Code/GameEngine/Source/Common/FprintfAppendLine.cpp` (118 unique bytes).
- `Code/GameEngine/Source/GameLogic/Object/Upgrade/GeometryUpgradeDtor.cpp`
  (63 unique bytes).

Independent EH checks pass 5/5 rows before and after, with zero missing objects,
baselines or nonexact rows. The final provider preparation restores the changed
source and current object after reconstructing the original for comparison.
Frozen-source, case-collision, converged-data and pin-consistency checks pass.

The local index was measured at `cb660e4d97`, 2026-10-13 04:02. Its hash, checkout
base, exact source cohort and original/current object hashes are in `proof.json`.
Both comparisons refresh the same cohort together in an in-memory copy of that
index. Every compared object has a strict current receipt. The two consumers'
objects are unchanged and already link before this repair. The provider's sole
finding is the duplicate public destructor before; all three units have zero
findings after. Local legacy-linked coverage is **181 -> 1,121 bytes**, a gain
of **940 existing unique bytes**. The CLI's stale-index aggregate 940 -> 1,121
is not an attributable gain. New authored C++ bytes: **0**.

Strict self receipts certify byte-verified object freshness. These local
legacy link previews do not establish self-strict or closed-strict executable
placement gains. No census rebuild, full link cycle, nightly or boot test ran;
broader placement verification remains outstanding. The committed link status
and census index remain unchanged.

## Donor review and remaining reference work

Reuse the preceding narrow-cleanup donor review at verified BFME 1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. This seat also fetched and read
`5fa9bfd662c427a198176b0b727c4c11d0965733`, including
`game/GameEngine/Source/GameClient/System/Anim2DCollectionTemplates.cpp`:
canonical narrow-string cleanup binding is an applicable lead. The provider's
template linkage repair is a BFME 2 adaptation proven by its own compiled
bytes, relocations and local linkage, not an imported donor layout or ABI.
The preceding four consumer unwind failures remain deferred; this work does
not repeat their failed cleanup strategy.

Freshness fetch found official BFME 1 master at
`85106095550c4ceb39c5daaa707795a9ab4e5f40`, beyond the clean verified pointer.
The comparative full-gate dependency-cache verification remains outstanding,
as recorded by preceding seats. This bounded repair changes no donor inputs;
it retains the verified checkout and gitlink and does not create a successful
freshness timestamp or claim that the update was verified.
