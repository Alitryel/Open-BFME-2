# StructureTopple range-erase binding

At BFME2 29ac3dcc43, the current StructureToppleUpdateModuleDataCtor.cpp
object failed the legacy link preview only because the kept
vector<AngleFXInfo>::erase copy did not reproduce its pinned retail body.
The native constructor at 00257A5E calls range erase at 003FA4DB. That complete
38-byte body already has the rowed vector<BfmePod8>::erase owner in
stlport_pod_vector_malloc_bodies.cpp. The existing target-derived angle-FX
layout is eight bytes, and the constructor's +AC vector uses the same
three-pointer representation. The inline forwarding specialization binds
that call to the existing owner without emitting another erase body.
It makes no new claim about BfmePod8's application identity.

Same census index ae3b3e68e2, current objects before/after:

- Constructor: 0 -> 266 nonpadding existing matched bytes; LINKS.
- Existing erase-owner unit: 0 -> 0 of 1,239 bytes, still blocked by other
  record helpers. Paired total 0 -> 266, a legacy prediction only.
- ./build.sh for both units: 24/24 rows exact, including parent EH mapping
  for three renumbered funclets, one empty string and three float literals.
- link_check.py --prepare-current prepares strict reusable compile receipts
  for both units; no self-strict or closed-strict LINK closure is claimed.
- Frozen-source check, check_csv.py and git diff --check pass.

Cause sweep: refreshed ModuleFactory, Rva00181500Finish,
AngleFXInfoVectorInsertOverflow, StructureToppleUpdate, and the module-data
destructor. The destructor already links (119 B); the other units have
independent missing providers, duplicate allocation/copy or incorrect
allocation/overflow implementations. No zero-gain suppression edits retained.
The existing Pod8 owner remains unchanged. No pin, alias, shared header or
verification rule changed.

Additional triage: ControlBar destructor needs reconciliation with its two
other private vtable views; removing its vptr store is not supported.
The farm-library reader's old global blocker now has documented owners,
but another worker holds its unit and row. The narrow numeric scanner and
static-string units are also held by other workers and were left untouched.
The failed hash-provider trial is restored and recorded in re_attempts.log.
BFME1 pointer/freshness blocker remains as recorded in 20261022-pod900-link.md.
