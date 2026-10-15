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
// The destructor is only declared; the verified wrapper call resolves to the
// retail destructor through its row or pin.

struct EmitVtableTag;

// ??_GAttackNugget@@UAEPAXI@Z @0x001F0606 28B: slot 0 of vtable 0x00BE0FF4; calls ??1 at 0x001F0622.
// Owner evidence (audited 2026-09-26): retail Attack OCL parse entry -> parser RVA 0x001F0D96 -> ctor RVA 0x001F05C1; primary vptr store RVA 0x001F05D9; AttackNugget spelling from donor.
class AttackNugget { public: AttackNugget(EmitVtableTag *); virtual ~AttackNugget(); };
// ?<AttackNugget::AttackNugget> absent-from-retail
AttackNugget::AttackNugget(EmitVtableTag *) {}

// ??1AttackNugget@@UAE@XZ is owned by Code/GameEngine/Source/GameLogic/Object/AttackNuggetDtor.cpp (row at 0x001F0622);
// this unit only declares it, and the tag constructor emits the vtable and its deleting wrapper.
