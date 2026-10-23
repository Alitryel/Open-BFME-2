// cl: /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// These minimal declarations emit the wrappers, not complete class layouts.
// No bases, member layout, or destructor implementation are claimed here.
// The noinline empty destructor is an unmatched compilation scaffold; the
// verified wrapper call resolves to the retail destructor through its pin.

struct EmitVtableTag;

// ??_GCallHelpOnDamage@@UAEPAXI@Z @0x004BB4B5 28B: slot 0 of vtable 0x00C59FDC; calls ??1 at 0x004BB4D1.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x004BB470 uses class-name string "CallHelpOnDamage".
class CallHelpOnDamage { public: CallHelpOnDamage(EmitVtableTag *); virtual ~CallHelpOnDamage(); };
// ?<CallHelpOnDamage::CallHelpOnDamage> absent-from-retail
CallHelpOnDamage::CallHelpOnDamage(EmitVtableTag *) {}
