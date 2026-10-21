// cl: /MD
// ??_GIngameNoticeDisplay@@UAEPAXI@Z @0x004E6231 28B: scalar deleting dtor calling ??1IngameNoticeDisplay at 0x004E61C8.
// Same-shape sibling of ??_GRva001E3624; needs ??1 row to exist.
struct EmitVtableTag;

class IngameNoticeDisplay { public: IngameNoticeDisplay(EmitVtableTag *); virtual ~IngameNoticeDisplay(); };
// ?<IngameNoticeDisplay::IngameNoticeDisplay> absent-from-retail
IngameNoticeDisplay::IngameNoticeDisplay(EmitVtableTag *) {}
