// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00240000@@QAE@XZ, retail 0x00240000, 46 bytes.
// Ctor with vtable 0xBEDCB4 vector BfmeE12 at +4 second ptr 0xBEDAA8 at +0x10 zeros at +0x14..0x1C.
// Evidence: unlock lane, vtable store at +0, Vector_base ctor 0x7FAEA, caller fanout 7, prev/next neighbours.
// The retail table at RVA 0x007EDCB4: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva0024002E@Rva0024002EForwarder@@QAEXXZ")();
void __identifier("?rva00240035@Rva00240035Forwarder@@QAEXXZ")();
void __identifier("?rva0024003D@Rva0024003DForwarder@@QAEXXZ")();
void __identifier("?rva00240045@Rva00240045Forwarder@@QAEXXZ")();
}
extern const void *const g_00BEDCB4[4] = {
	(const void *)&__identifier("?rva0024002E@Rva0024002EForwarder@@QAEXXZ"), // slot 0 0x0024002E
	(const void *)&__identifier("?rva00240035@Rva00240035Forwarder@@QAEXXZ"), // slot 1 0x00240035
	(const void *)&__identifier("?rva0024003D@Rva0024003DForwarder@@QAEXXZ"), // slot 2 0x0024003D
	(const void *)&__identifier("?rva00240045@Rva00240045Forwarder@@QAEXXZ"), // slot 3 0x00240045
};
// The retail table at RVA 0x007EDAA8: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva00306C15@Rva00306C49@@QAEHPAXH@Z")();
void __identifier("?get@Rva00306C42BinarySubField@@QBEHXZ")();
void __identifier("?rva00306C49@Rva00306C49@@QAE_NH@Z")();
void __identifier("?rva00306C58@Rva00306C49@@QAE_NXZ")();
}
extern const void *const g_00BEDAA8[4] = {
	(const void *)&__identifier("?rva00306C15@Rva00306C49@@QAEHPAXH@Z"), // slot 0 0x00306C15
	(const void *)&__identifier("?get@Rva00306C42BinarySubField@@QBEHXZ"), // slot 1 0x00306C42
	(const void *)&__identifier("?rva00306C49@Rva00306C49@@QAE_NH@Z"), // slot 2 0x00306C49
	(const void *)&__identifier("?rva00306C58@Rva00306C49@@QAE_NXZ"), // slot 3 0x00306C58
};
namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator() {}
	};
	template <class T, class A> class _Vector_base
	{
	public:
		_Vector_base(const A &);
		void *_M_start;
		void *_M_finish;
		void *_M_end;
	};
}
struct BfmeE12
{
	float x;
	float y;
	float z;
};
class Rva00240000
{
public:
	Rva00240000();
private:
	const void *m_00;
	_STL::_Vector_base<BfmeE12, _STL::allocator<BfmeE12> > m_04;
	const void *m_10;
	int m_14;
	int m_18;
	int m_1C;
};
Rva00240000::Rva00240000()
	: m_00((const void *)g_00BEDCB4)
	, m_04(_STL::allocator<BfmeE12>())
{
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_10 = (const void *)g_00BEDAA8;
}
