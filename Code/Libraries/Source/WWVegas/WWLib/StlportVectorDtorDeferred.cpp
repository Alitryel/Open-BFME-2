// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Byte-matched vector destructors with independently rowed range-worker owners.
// The two remaining competing-copy dependencies live in DeferredOwners.cpp.
#include <vector>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

// ??1?$vector@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@_STL@@@_STL@@QAE@XZ @0x57994 (_Destroy at 0x54f94)
// Element view matches StlportOwnedDeque.cpp (kept ??_G at 0x51B1E): 4-byte owning ref.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref();
private:
    long refs;
};
struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<OpaqueRefElement4 *>(OpaqueRefElement4 *, OpaqueRefElement4 *); }
template _STL::vector<OpaqueRefElement4>::~vector();

// ??1?$vector@UBfmeAssignRecord172@@V?$allocator@UBfmeAssignRecord172@@@_STL@@@_STL@@QAE@XZ @0x1eb945 (_Destroy at 0x1eb1b3)
struct BfmeAssignRecord172 { public: ~BfmeAssignRecord172(); };
namespace _STL { template <> void _Destroy<BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *); }
template _STL::vector<BfmeAssignRecord172>::~vector();


// ??1?$vector@UBfmeAssignRecord44@@V?$allocator@UBfmeAssignRecord44@@@_STL@@@_STL@@QAE@XZ @0x4146e2 (_Destroy at 0x4144f0)
struct BfmeAssignRecord44 { public: ~BfmeAssignRecord44(); };
namespace _STL { template <> void _Destroy<BfmeAssignRecord44 *>(BfmeAssignRecord44 *, BfmeAssignRecord44 *); }
template _STL::vector<BfmeAssignRecord44>::~vector();

// ??1?$vector@URvaPair00257544@@V?$allocator@URvaPair00257544@@@_STL@@@_STL@@QAE@XZ @0x00257544 63B.
// StructureCollapseUpdateModuleData +0xA0 member vector: retail destroys the range through the rowed 8-byte AsciiString-keyed DestroyPairs at 0x32C0CA then frees storage via 0x30830 (EH states 0/-1); called by the StructureCollapse dtor at 0x00257B7A plus Unwind funclets at 0xB720EF/0xB7213E. ICF-twin of rowed 0x004C3D4C and 0x0049E274 (same 63B Destroy+free shape). True element name unproven so honest RvaPair address name stands in for the 8-byte AsciiString-plus-int layout the retail destroy proves.
struct RvaPair00257544 { AsciiString m_key; int m_value; public: ~RvaPair00257544(); };
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<RvaPair00257544 *>(RvaPair00257544 *, RvaPair00257544 *); }
template _STL::vector<RvaPair00257544>::~vector();

// ??1?$vector@URva002BBB96Element@@V?$allocator@URva002BBB96Element@@@_STL@@@_STL@@QAE@XZ @0x002BBB18 (_Destroy at 0x002BB6A5)
struct Rva002BBB96Element { public: ~Rva002BBB96Element(); };
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<Rva002BBB96Element *>(Rva002BBB96Element *, Rva002BBB96Element *); }
template _STL::vector<Rva002BBB96Element>::~vector();


// ??1?$vector@URva005F8620Element@@V?$allocator@URva005F8620Element@@@_STL@@@_STL@@QAE@XZ @0x005F85E1 (_Destroy at 0x005F85C8)
struct Rva005F8620Element { public: ~Rva005F8620Element(); };
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<Rva005F8620Element *>(Rva005F8620Element *, Rva005F8620Element *); }
template _STL::vector<Rva005F8620Element>::~vector();

// ??1?$vector@URva001DEF38Element@@V?$allocator@URva001DEF38Element@@@_STL@@@_STL@@QAE@XZ @0x001DEEF9 (_Destroy at 0x001DEEE0)
struct Rva001DEF38Element { public: ~Rva001DEF38Element(); };
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<Rva001DEF38Element *>(Rva001DEF38Element *, Rva001DEF38Element *); }
template _STL::vector<Rva001DEF38Element>::~vector();

// Native callers use first/last cdecl arguments and target these rowed workers.
// Bind operations without equating the application element class views.
// The complete 25B worker at 2BB6A5 reads only these two arguments, and native
// caller 2BBB18 pushes and pops exactly two; the provider's unused tag is absent.
#pragma comment(linker, "/alternatename:??$_Destroy@PAURvaPair00257544@@@_STL@@YAXPAURvaPair00257544@@0@Z=?Rva0032C0CADestroyPairs@@YAXPAURvaPair0032C0CA@@0@Z")
#pragma comment(linker, "/alternatename:??$_Destroy@PAURva005F8620Element@@@_STL@@YAXPAURva005F8620Element@@0@Z=?Rva005F85C8Destroy@@YAXPAURva005F8447@@0@Z")
#pragma comment(linker, "/alternatename:??$_Destroy@PAURva002BBB96Element@@@_STL@@YAXPAURva002BBB96Element@@0@Z=??$__destroy_aux@PAUBfmeAssignRecord52@@@_STL@@YAXPAUBfmeAssignRecord52@@0ABU__false_type@0@@Z")
