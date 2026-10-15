Polygon parser / water-record reader link binding, 2026-10-15

At source base 06bb87b5b4683659a2b06cf2a8b8488bbfbd367a, the polygon parser
at 0x003294D6 called a pinned void-pointer spelling of the existing typed
reader at 0x00328E96. Declare and call the actual reader, casting the caller's
existing local record view, and remove the obsolete duplicate pin. No provider,
layout, shared header, baseline or authored function body is added.

Retail's E8 operand independently resolves to 0x00328E96. The existing reader
and caller sources establish matching fields: id +00, strings +04/+08, river
+0C, start +10, six strings +14..+28, color flag +2C, RGB +30, reals +3C/+40/+44,
polygon +48..+73 and water flag +74. These are existing target reconstructions;
the change does not promote the opaque record/class names to recovered names.
The existing reader cites BFME 1 as semantic guidance, with target offsets and
extended fields independently supplied by retail. No new donor code is used.

The paired proof uses the same frozen legacy index at ac77c85054, measured
2026-10-15 14:25; index-meta.json records its hash and source base. It refreshes
only the two strict-current objects in memory, leaving index/status untouched.
Consumer unresolved findings fall from two to one. The provider still links;
the consumer still has the separate standing-water constructor ABI blocker
??0Rva00308E63@@QAE@H_N@Z. Thus legacy linked bytes remain 663 across the pair,
new authored bytes are zero, and no self-strict/closed-strict placement gain is
claimed. A full link cycle/runtime test remains outstanding and was not run.

proof.py verifies the entire nondebug consumer object, including section flags,
data, definitions, symbolic relocations, linker directives and EH sections,
is identical modulo this one callee name. The provider object is byte-for-byte
unchanged. All 222 caller bytes are unchanged; exactly one zero-addend REL32
changes names, and its retail destination is independently checked. Findings
against the same index differ only by removal of the obsolete reader symbol.

Acceptance (logs adjacent):
- link_check.py --prepare-current for both sources: 17/17 functions, five
  string literals, five floats, zero imports; strict reusable receipts pass.
- ./build.sh consumer: 16/16 functions and literal/float/import checks pass.
- proof.py: complete object, relocation, paired legacy findings and unchanged
  data-binding assertions pass.
- eh_verify.py both sources: seven EXACT, none nonexact/baselined/missing.
- data_check.py --converged both: eight addresses, no second names/unjudged rows.
- data_check.py --enforce both: exit 1 for the PRE-EXISTING wrong-name binding
  ?g_Va00DBD0F0@@3HA at 0x009BD0F0. proof.py verifies every data fact and this
  single finding are identical before/after. The inventory prefers the unowned
  ?s_currentID@PolygonTrigger@@0HA spelling, while the existing neutral global
  has a real definition in ColdGlobalDwordGetters.cpp. This repair does not
  reconcile that separate global/class ownership debt.
- link_check.py --new-variants, class_gate.py and find_declared_unmatched.py
  consumer pass. place_bodies.py consumer finds zero new bodies/pins.
- check_csv.py and git diff --check pass.

Scope sweep: the obsolete reader spelling had only this source consumer and
its removed pin; no other source repair is implied. The remaining constructor
provider has a virtual-inheritance hidden-most-derived argument; the caller's
private view does not model it. Changing its spelling alone is unsupported.

BFME 1 linking review used clean committed donor
a7c38d3b2597121f178ab5190b3062478823257d. Current official master fetched as
3f09d565e01ed4ce9b40cf5ae9b80ec7c4f10420. Recent setFlip ILT, previous-frame,
FESL and vswprintf repairs were reviewed; the latter is already inherited and
the others do not establish this record's ABI. Existing provider/convergence
repair principles are applicable, without importing a layout. The submodule
is claimed by another worker; the recorded comparative-full-gate blocker
(thousands of stale objects) remains. Verified pointer/stamp unchanged.

Reproduce with the source base and index hash in index-meta.json: prepare both
sources before editing, save objects and receipts under
build/polygon-water-reader-link-20261015/before/, apply the source/pin change,
prepare the same pair, and run proof.py from the repo root. Saved proof.json
records this experiment's hashes; ignored compiled objects are not committed.
