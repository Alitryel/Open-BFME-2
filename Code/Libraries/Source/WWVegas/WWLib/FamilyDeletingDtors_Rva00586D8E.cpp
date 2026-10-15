// cl: /MD
// ??_GHordeMeleeFormation@@UAEPAXI@Z, retail 0x00586E35 28B.
// Deleting dtor for HordeMeleeFormation whose ??1 is rowed at 0x00586E51; placeholder ~ is duplicate.
struct EmitVtableTag;

class HordeMeleeFormation { public: HordeMeleeFormation(EmitVtableTag *); virtual ~HordeMeleeFormation(); };
// ?<HordeMeleeFormation::HordeMeleeFormation> absent-from-retail
HordeMeleeFormation::HordeMeleeFormation(EmitVtableTag *) {}
