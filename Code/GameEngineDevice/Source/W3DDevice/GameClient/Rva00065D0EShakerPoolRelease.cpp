// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Complete 22B cdecl body 65D0E..65D24: if the pointer is nonnull, call
// rowed pooled FreeObject 65964 on the existing CameraShaker allocator.
// The current donor-backed camera-shaker TU defines that real static member
// with DEFINE_AUTO_POOL(CameraShakeSystemClass::CameraShakerClass,256).
// Native DIR32 names its owned VA DE1E98. This uses declarations only;
// original wrapper identity and an operator-delete role are unasserted.
// Allocator keeps the provider's private-static linkage; friendship only
// grants this TU's borrowed helpers access to that existing definition.
// Its allocating partner 65D04..65D0E (10B) sits right before it: ecx =
// the same allocator, tail jump to rowed pooled allocate 658DB, which
// Add_Camera_Shake (65DD2) also calls inline; no direct callers. Address
// name, as for the release; an operator-new role is likewise unasserted.
class CameraShakeSystemClass { public: class CameraShakerClass; };
template<class T,int N> class ObjectPoolClass;
void __cdecl rva00065D0EReleaseShakerMemory(void *);
void *__cdecl rva00065D04AllocateShakerMemory();
template<class T,int N> class AutoPoolClass {
    friend void __cdecl rva00065D0EReleaseShakerMemory(void *);
    friend void *__cdecl rva00065D04AllocateShakerMemory();
private:
    static ObjectPoolClass<T,N> Allocator;
};
struct Rva00065964ObjectPool { void *rva000658DB(); void FreeObject(void *); };
void *__cdecl rva00065D04AllocateShakerMemory() {
    return ((Rva00065964ObjectPool *)&AutoPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::Allocator)->rva000658DB();
}
void __cdecl rva00065D0EReleaseShakerMemory(void *memory) {
    if (memory)
        ((Rva00065964ObjectPool *)&AutoPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::Allocator)->FreeObject(memory);
}
