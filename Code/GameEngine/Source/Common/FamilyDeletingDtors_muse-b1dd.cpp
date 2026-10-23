// cl: /MD
// ??_GReplaceSelfUpgrade@@MAEPAXI@Z @0x004B70CF 28B
// Deleting dtor slot 0 of vtable 0x00858B10; calls rowed ??1ReplaceSelfUpgrade@@MAE@XZ at 0x004B70EB then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class ReplaceSelfUpgrade { public: ReplaceSelfUpgrade(EmitVtableTag *); protected: virtual ~ReplaceSelfUpgrade(); };
// ?<ReplaceSelfUpgrade::ReplaceSelfUpgrade> absent-from-retail
ReplaceSelfUpgrade::ReplaceSelfUpgrade(EmitVtableTag *) {}

