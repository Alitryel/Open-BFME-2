TerrainResourceBehaviorModuleData destructor link repair, Astra s2, 2026-10-23

Input BFME2 7aef32dd08 (OpenContain-only change over 7aae99cc67), donor pointer
138757e9b74645fbcbb7724a7af2764e34931e11, unchanged MSVC 7.1 optimization flags.
Prior blocker: reverse/re_attempts.log entry for 482275: the private base deleting
destructor differs from the constructor TU under /Oy-. Do not retry flag-only
or Snapshot-body-only changes: the synthetic constructor emitted that table.

Retail table C49440 has the existing 31-slot ModuleData interface, with its own
scalar deleting destructor at 482259 and slot24=47A6A9 (return this). Native
482275 is 48 bytes: filter teardown at +18, then Snapshot-table restoration at
BBB554. Its handler is 78BB92, shared with the rowed constructor. The established
ctor/table prove the extra +4 field and tail fields at +1C/+20; their existing
names are retained rather than newly inferred.

Use canonical novtable ModuleData for this teardown view, preserve the +4 field,
and declare the proven slot24 override. Replace the synthetic constructor/delete
anchor with a qualified destructor call, as in CallHelpOnDamageModuleDataDtor.
The implicit destructor still emits all 48 native bytes. No competing private
base deleting destructor is emitted. Constructor source and all pins unchanged.

Validation: focused byte gate 1/1; parent EH EXACT 1/1; definition check passes;
link_check --prepare-current verifies the explicit source with a strict reusable
receipt. Paired legacy link preview against unchanged census 491a8b3d87:
constructor 101->101, destructor 0->48; both units now link (101->149 total).
This is +48 scoped legacy linked bytes, not new recovery or closed-strict/link.exe
coverage. Existing CallHelp repair is a source-pattern lead; target bytes/table
supply independent evidence here. No shared header, gate, or baseline changed.
