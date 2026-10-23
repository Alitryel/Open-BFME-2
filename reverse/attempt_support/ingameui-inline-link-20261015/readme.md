InGameUI unused inline helper repair, 2026-10-15

Source base: 3d7e8ac2fb377b5b2ae99b312eb5ffdfa316780e. Measurement: runner
legacy census ac77c85054, 2026-10-15 14:25, index hash in context.json.
The current InGameUIMessages.cpp object had three COMDAT findings. Two unused
public definitions are removed from contention: fast_float_floor becomes
file-static, and eight localized-font isNotEmpty calls spell the existing
StringBase<char> base method directly. The included BFME 1 ascii_string.h
already defines AsciiString as public StringBase<char>, and its isNotEmpty
wrapper simply forwards to that exact method. No layout or behavior is inferred
from the spelling change. No pin, alias, flag, shared-header or baseline change.

Paired acceptance refreshes ONLY the four explicitly listed, strict-current
objects into two copies of the SAME in-memory census. Consumer findings fall
from three to one; the remaining finding is wide StringBase::getCharAt. All
three provider objects and their findings are unchanged. The consumer's 5,080
existing authored bytes remain unlinked (0 -> 0), and authored C++ growth is zero.
This is verified removal of two link findings, not a linked-byte, closed-strict
or full-game link gain. Strict receipts cover the explicit four sources; the
rest of the census remains legacy evidence.

COFF proof: all 61 retained COMDAT bodies and symbolic relocations are identical.
The unused 11-byte AsciiString wrapper section disappears. The 18-byte floor
body stays byte-identical as a static symbol; only its public binding disappears.
Neither original helper has incoming nondebug relocations, including section
references. All other nondebug sections, external bindings and directives are
unchanged, except the two public names. SafeSEH handler membership is identical;
its list order and symbol indices are normalized in the comparison. Provider
objects are identical in their entirety. Object hashes, helper bytes and
symbolic relocations are recorded in proof.json.

The floor and AsciiString::isNotEmpty witnesses in PartitionManager and
DumbProjectileBehavior have no established retail RVA; these are first-copy
comparisons, not newly established retail identities. The remaining getCharAt
provider in string_base_inline.cpp is byte-verified at 0x00035760. Target
identities/layouts of the consumer's matched rows remain backed by the existing
ledger evidence; no donor address or layout is transferred.

Acceptance (logs adjacent):
- ./build.sh InGameUIMessages.cpp: 48/48 matched, string/float/import gates pass.
- link_check.py --prepare-current --paths-from sources.txt before and after:
  110/110 matched across the four explicit sources, strict receipts; string,
  float and named-import checks pass. Renumbered funclets are verified by the
  normal parent-EH resolver, without changing ledger object-symbol notes.
- proof.py: paired findings 3 -> 1, providers and all retained code/EH unchanged.
- link_check.py --paths-from sources.txt: exit 1, 1/4 sources link cleanly;
  consumer has only getCharAt left. The three providers retain prior results.
- eh_verify.py --sources-from sources.txt: 12/12 EH rows EXACT.
- data_check.py --enforce with four explicit source arguments: exit 1 for two
  pre-existing consumer wrong-name data findings, at 0x009FEEA8 and 0x009FEE20.
  Paired proof confirms both are identical before/after. No baseline change.
- data_check.py --converged with the same four source arguments: exit 0,
  eight addresses, zero second names, zero unjudged rows.
- link_check.py --new-variants on the four sources: exit 0.
- class_gate.py and find_declared_unmatched.py on the consumer: pass.
- place_bodies.py consumer: zero new bodies and pins.
- check_csv.py and git diff --check: pass.

Remaining blocker trial: removing the local generic getCharAt definition
suppresses its wrong COMDAT, but changes register allocation/argument convention
in getLineWidth, updateMilitarySubtitle and militarySubtitle(UnicodeString).
The failed byte gate is preserved in build-first.txt. The definition was restored;
all final rows pass. Its 22-byte local tail-merged body differs from the canonical
23-byte retail body. Three incoming nondebug relocations (getLineWidth +0x2f,
updateMilitarySubtitle +0x10f and +0x19b) forbid treating it as unused. Reconcile
that codegen dependency before suppressing it; no more blind suppression trials.
The two wrong-name subtitle static data findings are separate existing debt.

Dependency sweep: family-near.json records the only other census unit with at
most four findings involving these public helpers: PathfindLayerAllocateCells.
It also needs fast_float_ceil and an unresolved PathfindCell destructor. No
linked-byte improvement there is inferred from this bounded consumer repair.

BFME 1 review: 6ffd3f498c98872efbb0ad242c3afea4640e4ef5 routes AsciiString
compare through the existing StringBase spelling to avoid a public wrapper;
that emission technique is applicable, not its functions/layout. Also reviewed
66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocation) and c1315665a1
(DamageInfo suppression). No donor source imported. The clean BFME 1 checkout
remains the committed a7c38d3b2597121f178ab5190b3062478823257d. Pull fetched
upstream master 7afa50f4cfe2205fab66de58312bc722dccf8cbe, but another worker
owns file:reference/open-bfme-1 for the comparative full verification. No pointer
or freshness stamp changed here; freshness verification remains that owner's
blocker. No census, full link cycle or runtime verification started.

Reproduction: use the source base and exact index in context.json. Before the
edit, prepare the four sources and save their strict objects under ignored
build/ingameui-inline-link-20261015/before/. Prepare the same sources after the
edit; put context.json in that scratch directory, then run proof.py from this
checkout. It writes proof.json there. Compiled caches and source backups stay
ignored; tracked proof.json records the original bounded experiment.
