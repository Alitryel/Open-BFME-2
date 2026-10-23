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

// TerrainResourceClientBehavior's verified deleting wrapper now comes from
// TerrainResourceClientBehaviorSlots.cpp, alongside its real destructor.
// Removing the empty scaffold also removes its conflicting vtable copy.
// InstantDeathBehaviorModuleData's wrapper likewise comes from its ctor unit,
// which emits the class's vtable.

struct EmitVtableTag;

// CastleBehavior and StancesBehavior wrappers now come from their real
// destructor units; the removed scaffolds emitted conflicting partial vtables.

// ??_GPropagandaTowerBehaviorModuleData@@UAEPAXI@Z @0x00481BB2 28B: slot 0 of vtable 0x00C49288; calls ??1 at 0x00481BCE.
// Owner evidence (audited 2026-09-26): retail registration PropagandaTowerBehavior -> data factory RVA 0x0024C21B -> ctor RVA 0x0048197C; primary vptr store RVA 0x00481988.
class PropagandaTowerBehaviorModuleData { public: PropagandaTowerBehaviorModuleData(EmitVtableTag *); virtual ~PropagandaTowerBehaviorModuleData(); };
// ?<PropagandaTowerBehaviorModuleData::PropagandaTowerBehaviorModuleData> absent-from-retail
PropagandaTowerBehaviorModuleData::PropagandaTowerBehaviorModuleData(EmitVtableTag *) {}

// ??_GSlaveWatcherBehaviorModuleData@@UAEPAXI@Z @0x004846DE 28B: slot 0 of vtable 0x00C4A298; calls ??1 at 0x004846FA.
// Owner evidence (audited 2026-09-26): retail registration SlaveWatcherBehavior -> data factory RVA 0x0024C660 -> ctor RVA 0x004846C7; primary vptr store RVA 0x004846CB.
class SlaveWatcherBehaviorModuleData { public: SlaveWatcherBehaviorModuleData(EmitVtableTag *); virtual ~SlaveWatcherBehaviorModuleData(); };
// ?<SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData> absent-from-retail
SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData(EmitVtableTag *) {}
