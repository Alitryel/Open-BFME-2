# Tree-iterator comparison link repair, 2026-10-15

Four consumers now compare typed STLport tree iterators with a TU-local
operator!=, preserving the node-pointer comparison while suppressing an
unused external tree-base comparison that loses to the census provider.
No standalone target identity or ABI is inferred for that unaddressed helper.

## Controlled evidence

Base: 18e3ffec52f4dd1e9e30f0fccf77eae2a4023ec4.
The fetched index measures 825b86983f at 2026-10-15 12:37, derived from
census 5986a99448 at 04:52. Its SHA256 is
672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c.
Committed link_status.csv instead measures 28269d8e8d at 09:31 and serves
only discovery. Results below use the same fetched index before and after,
refreshed in memory with only the four owned, strictly prepared objects.

| Consumer | Retained identical COMDATs | Findings before -> after |
| --- | ---: | ---: |
| Rva00082EF5Ctor.cpp | 97 | 5 -> 4 |
| SkirmishAIManager.cpp | 80 | 21 -> 20 |
| ChatWindowsLan.cpp | 83 | 4 -> 3 |
| Rva00474483ConfigureSlots.cpp | 142 | 22 -> 21 |

All 402 retained COMDATs and all retained nondebug section bytes, flags,
extents, external definitions, symbolic relocations and data references are
unchanged. Each replacement is a private 12-byte node comparison with zero
relocations. Neither replaced helper has an incoming nondebug relocation.
The only external binding removed is
??9_Rb_tree_base_iterator@_STL@@QBE_NABU01@@Z. The selected provider stays
the same. No new-variant finding appears. Detailed before/after findings,
object hashes and currency evidence are in object-proof.json.

The consumers own 3,394 existing nonpadding bytes. Four conflicts disappear;
all other findings remain identical. Legacy local LINKED is 0 -> 0 bytes.
New authored C++ bytes: 0. Self-strict receipts establish object currency,
not a clean link closure. Closed-strict gains remain unmeasured. The census,
index, link status and history are not rewritten. No full link cycle,
nightly or boot runner was started.

## Acceptance

- Baseline strict preparation: 52/52 rows across the original five files.
- Final strict preparation and explicit ./build.sh: 42/42 rows across four
  files, three string literals, zero skipped literals or new named imports.
- EH verifier: 10/10 EXACT, no missing object or baseline use.
- Declared-definition and class gates pass. Data enforcement: zero findings.
  Converged data: eight addresses, zero second names or unjudged rows.
- Paired bounded link preview proves exactly four conflicts removed. The
  prescribed local link_check.py still returns 1 for independent blockers.
- Placement resweep: zero bodies, zero pins. check_csv and diff --check pass.

proof.py reproduces the object and paired-preview checks from repository root
using strict before-source/object/dependency snapshots in ignored
build/tree-comparison-link-20261015/before and the recorded index. Recreate
those snapshots by preparing the parent sources under identical inputs, then
prepare the changed sources. Raw objects and compiler receipts are local
scratch, not publication artifacts.

## Rejected sibling and handoff

Rva000A7E9E.cpp reproduced the same conflict, and the trial preserved all
95 retained COMDATs and its complete normalized nondebug bytes/relocations,
including the EH graph. Its gate nevertheless refused uw_00760bc6 (8 bytes
at 0x00760BC6), whose orphan object-symbol=$L7970 cannot follow compiler
label renumbering. This is recorded as false-reject byte-gate in re_attempts.
The entire source change was reverted and its claim released. Verifier code
was not edited. rejected-change.patch, rejected-object-proof.json and
rejected-gate.txt preserve the attempted repair and evidence. The rejected
trial's raw object/receipt snapshots remain in the ignored rejected folder.
A tooling seat can reproduce this at the recorded base and repair the check
with a regression test; do not work around it in the source repair.

Remaining blockers: Rva00082EF5Ctor has BfmeE16 allocator/vector competing
copies; ChatWindowsLan has less<int> and two unresolved methods; SkirmishAI
and Horde configuration have unresolved methods and additional map/vector
copy or selected-provider disagreements. link-after.txt enumerates them.
These are separate supported dependency repairs, not reasons to retry the
orphan-label rejection. No complete-link or retail runtime result is claimed.

## Reference review

Clean verified BFME1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
c3c5a59620585b5752df5861abfd7979010f485b. Another live worker owns
file:reference/open-bfme-1, so the pointer and missing freshness success stamp
were preserved. The pointer update still requires comparative full byte gates.

Reviewed donor c1315665a1b22beb7e6d9279548fe5b1c26ed1f9: suppressing unused
DamageInfo COMDAT emission is an applicable ownership principle. Its class,
layout and target bodies are inapplicable here and no donor code was imported.
The typed comparison follows the already verified BFME2 tree-iterator repair
and its canonical STLport node comparison. Target object and byte evidence,
not the donor's link result, establish preservation in these four consumers.
