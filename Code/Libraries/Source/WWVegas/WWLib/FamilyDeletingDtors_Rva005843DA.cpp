// cl: /O1 /MD
// ??_GHordeMeleeSwarm@@UAEPAXI@Z retail 0x005844E6 28B.
// Deleting dtor slot0 of vtable 0x0086FC80 for HordeMeleeSwarm whose ??1 is at
// 0x00584502 rowed as dup alias; placeholder ~ is duplicate.
struct EmitVtableTag;

class HordeMeleeSwarm { public: HordeMeleeSwarm(EmitVtableTag *); virtual ~HordeMeleeSwarm(); };
// ?<HordeMeleeSwarm::HordeMeleeSwarm> absent-from-retail
HordeMeleeSwarm::HordeMeleeSwarm(EmitVtableTag *) {}
