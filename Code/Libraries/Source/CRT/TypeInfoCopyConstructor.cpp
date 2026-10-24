// Native CRT ti_inst.obj family: private copy constructor 0x0062903D (11B)
// and vector deleting destructor 0x00629048 (75B). The MSVC7.1 declaration
// retains every method, access level and field. _CRTIMP is empty in this
// native producer context: both native destructor references reach the real
// msvcr71.dll import thunk, not its IAT slot directly.
// The default argument and unreachable array-new are compiler-emission
// adapters, not claims about the original API or executed allocation.
// The copy constructor remains the independently established empty body.
// No array-delete declaration is visible: native frees both paths with the
// scalar operator delete. Evidence: typeinfo-vector-delete-20261024.md.
// cl: /O1 /G7 /MD /EHsc
// TU-scoped declaration adapted from the pinned MSVC7.1 typeinfo.h.
// The source-only default argument enables an unreachable array-new context;
// it adds no parameter and no new constructor overload to the native ABI.
#define _CRTIMP
class type_info {
public:
    _CRTIMP virtual ~type_info();
    _CRTIMP int operator==(const type_info& rhs) const;
    _CRTIMP int operator!=(const type_info& rhs) const;
    _CRTIMP int before(const type_info& rhs) const;
    _CRTIMP const char* name() const;
    _CRTIMP const char* raw_name() const;
private:
    void *_m_data;
    char _m_d_name[1];
    type_info(const type_info& rhs = typeid(int));
    type_info& operator=(const type_info& rhs);
};
// The compiler may emit an unreferenced ??_Ftype_info closure for the source
// default argument. It is not rowed and has no native counterpart.
type_info::type_info(const type_info&) {
    if (0) new type_info[2];
}
typedef char TypeInfoSizeCheck[sizeof(type_info)==12?1:-1];
