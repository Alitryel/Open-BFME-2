# OilSpill vector link repair, 2026-10-18

Base 70214d5c98; published census c2c5ac8c27, retail-truth-2.

Target evidence: xfer at 0x48C415 calls erase at 0x2A133B and reserve at
0x390729, whereas the Coord3D erase name now owns a different retail address.
Use the existing Gen_p12pod erase and neutral 12-byte reserve row names on the
breadcrumb vector. Declaring the rowed Coord3D push_back at 0x2CE7DC removes
this consumer's conflicting overflow/allocator copies without changing update.

The reserve grow call at 0x390763 targets the existing Rva000E016A method,
which allocates through the vector allocator at +8 and copies Coord3D ranges.
Its former generic allocate-copy instantiation emits a different body under
these flags. Preserve STLport reserve control flow, calling the actual owned
method directly. All 125 bytes and relocations still match. Neutral element
names are retained: these calls establish a shared three-word vector ABI and
12-byte stride, not a concrete element identity for every caller. No new pins,
aliases, private copies of canonical classes or escape hatches are introduced.

Paired legacy predictions use the same eight current providers, in the order
printed in before.txt and after.txt. Original 4/8 link, 434 bytes; final 6/8
link, 1,057 bytes: +623 (OilSpillUpdate 498, reserve 125). Rva00390911Xfer's
205 bytes already link with current providers and are excluded from the gain.
The unchanged ScriptListSubrecord ctor, allocate-copy and erase providers also
already link. LivingWorldManagerCtor remains blocked on other constructors,
destructors and subsystem virtuals; Rva000E0AE2Constructor remains blocked on
ShaderClass copy and void-pointer vector destruction. No unchanged unit is
claimed as a repair.

Self-strict receipts: 6/6 rows across the two touched and two helper-provider
units; string, float and import reference gates pass. Touched-source EH scan
has no EH rows. Frozen-definition and CSV checks pass. This is a legacy link
prediction with self-strict byte receipts, not closed-strict link measurement.
No full link cycle/census was run and no authored C++ byte growth is claimed.

STLport remains the semantic source for reserve. BFME1 linking repair review
and freshness blocker are recorded in the preceding GameSpy repair evidence;
no donor pointer or headers changed in this repair.
