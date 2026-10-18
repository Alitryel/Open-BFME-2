// cl: /MD
// ??_GHordeMeleeAmoeba@@UAEPAXI@Z, retail 0x00587F4D 28B.
// Deleting dtor for HordeMeleeAmoeba whose ??1 is rowed at 0x00587F69; placeholder ~ is duplicate.
struct EmitVtableTag;

class HordeMeleeAmoeba { public: HordeMeleeAmoeba(EmitVtableTag *); virtual ~HordeMeleeAmoeba(); };
// ?<HordeMeleeAmoeba::HordeMeleeAmoeba> absent-from-retail
HordeMeleeAmoeba::HordeMeleeAmoeba(EmitVtableTag *) {}
