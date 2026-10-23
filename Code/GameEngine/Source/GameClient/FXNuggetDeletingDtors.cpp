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

// ??_GSoundFXNugget@@UAEPAXI@Z @0x001E0DEB 28B: slot 0 of vtable 0x00BDD768; calls ??1 at 0x001E0E07.
// Owner evidence (audited 2026-09-26): retail Sound FXList parse entry -> parser RVA 0x001E1329 -> ctor RVA 0x001E00A3; primary vptr store RVA 0x001E00AB; SoundFXNugget spelling from donor.
class SoundFXNugget { public: SoundFXNugget(EmitVtableTag *); virtual ~SoundFXNugget(); };
// ?<SoundFXNugget::SoundFXNugget> absent-from-retail
SoundFXNugget::SoundFXNugget(EmitVtableTag *) {}
