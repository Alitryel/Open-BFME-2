// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Vtable0xBE7258 and getter226309 identify SaveMapPreview. Its complete
// copy2262E7 has a Snapshot vptr, dword4 and three-dword aggregate at8.
// STLport4.5.3 range copying uses the retail configuration without catch blocks.
#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
class Xfer;
// SaveMapPreview's base is NOT canonical Snapshot: retail vtable 0xBE7258 holds
// crc/typeName/xfer while canonical Snapshot (Snapshot.cpp, shim) holds
// crc/xfer/loadPostProcess. Same mangled name different virtuals cannot share
// COMDATs, so the base keeps an honest Rva address name here.
class Rva002262E7SnapshotBase {
public:
    virtual ~Rva002262E7SnapshotBase();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class SaveMapPreview : public Rva002262E7SnapshotBase {
public:
    unsigned int word04;
    struct Words { unsigned int a,b,c; } words08;
    __declspec(nothrow) SaveMapPreview(const SaveMapPreview &o) : Rva002262E7SnapshotBase(o), word04(o.word04), words08(o.words08) {}
    virtual ~SaveMapPreview();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
typedef char SaveMapPreviewSizeCheck[sizeof(SaveMapPreview)==20 ? 1 : -1];
template _STL::vector<SaveMapPreview>::vector(const _STL::vector<SaveMapPreview>&);
template SaveMapPreview *_STL::vector<SaveMapPreview>::_M_allocate_and_copy<SaveMapPreview const *>(unsigned int, SaveMapPreview const *, SaveMapPreview const *);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmeVector0022C55B@@QAE@ABU0@@Z=??0?$vector@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@QAE@ABV01@@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?crc@SaveMapPreview@@UAEXPAVXfer@@@Z=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?typeName@SaveMapPreview@@UBEPBDXZ=?name@Rva00226309Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:?xfer@SaveMapPreview@@UAEXPAVXfer@@@Z=?rva002DBA3F@Rva002DBA3F@@QAEXPAVXfer@@@Z")
