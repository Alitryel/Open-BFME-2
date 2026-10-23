// cl: /MD
//
// ??0Rva005CDB8F@@QAE@PBUPayload@0@@Z retail 0x005CDB8F 31B copy 20B plus refcount 0.
// Evidence: vtable 0x0087507C at +0; +4 zeroed (refcount inc at caller 0x005CDC43);
// 5-dword rep movsd from src arg to +8; new(0x1C) at caller 0x005CDC20; ret 4.
template <class T> class RvaCloneResult;

class Rva005CDB8F
{
public:
	struct Payload { int v[5]; };
	Rva005CDB8F(const Payload *src);
	// Same vftable view as RvaCloneValueReturns.cpp (slot 0 deleting dtor,
	// slot 1 clone, vftable 0x00C7507C); retail's deleting dtor 0x005FAA31 is
	// an ICF-shared vptr-reset-and-delete body, so the dtor is inline.
	virtual ~Rva005CDB8F() {}
	virtual RvaCloneResult<Rva005CDB8F> clone() const;
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005CDB8F::Rva005CDB8F(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}
