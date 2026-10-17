// cl: /MD
// ??_GRva00414B40@@UAEPAXI@Z @0x00414B24 28B: scalar deleting dtor calling ??1Rva00414B40 at 0x00414B40.
// Same-shape sibling of ??_GRva00414932 at 0x00414AEE; needs ??1 row to exist.
struct EmitVtableTag;

// Secondary base at +0xC: slot 0 of its table 0x00C3A0AC, just ahead of the
// primary 0x00C3A0BC, is the this-adjusting (sub ecx, 0xC) deleting-destructor
// thunk 0x004149AC, target evidence for it. Both bases are novtable, so only
// this class's own tables are emitted.
struct __declspec(novtable) Rva00414B40Base0 { virtual ~Rva00414B40Base0(); char m_unmodelled04[0x0C - 0x04]; };
struct __declspec(novtable) Rva00414B40BaseC { virtual ~Rva00414B40BaseC(); };
class Rva00414B40 : public Rva00414B40Base0, public Rva00414B40BaseC { public: Rva00414B40(EmitVtableTag *); virtual ~Rva00414B40(); };
// ?<Rva00414B40::Rva00414B40> absent-from-retail
Rva00414B40::Rva00414B40(EmitVtableTag *) {}
