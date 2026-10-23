// cl: /MD
// ??0Rva0073EE21@@QAE@XZ @0x0073EE21 44B
// Ctor pattern twin of FXListRva001E28B8Ctor: base Rva0040F9D(1 0 0 0) plus member at +8.
// Evidence: call rowed 0x00040F64 with 1 0 0 0; and [0xC] 0 plus base member vtable 0x00BC6F20
// plus own vtable 0x008F1538 plus member vtable 0x008F1534; caller 0x0073F3DC.

struct Rva0040F9DBase
{
	Rva0040F9DBase() : m_handle(0) {}
	void *m_handle;
};

class Rva0040F9D : public Rva0040F9DBase
{
public:
	Rva0040F9D(int a1, int a2, char const *a3, void *a4);
	virtual ~Rva0040F9D();
};

extern "C" const unsigned char __identifier("??_7Secondary005E7ED7@@6B@")[];
// The retail table at RVA 0x008F1538: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?lock@Rva0040EDB@@UAE_NH@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("??_GRva0073EF24@@UAEPAXI@Z")();
}
extern const void *const g_00CF1538[3] = {
	(const void *)&__identifier("?lock@Rva0040EDB@@UAE_NH@Z"), // slot 0 0x00040EF8
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 1 0x0050B5C6
	(const void *)&__identifier("??_GRva0073EF24@@UAEPAXI@Z"), // slot 2 0x0073EF08
};
// The retail table at RVA 0x008F1534: 1 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_ERva0073EF24@@W7AEPAXI@Z")();
}
extern const void *const g_00CF1534[1] = {
	(const void *)&__identifier("??_ERva0073EF24@@W7AEPAXI@Z"), // slot 0 0x0073EE4D
};

struct Rva0073EE21Member
{
	Rva0073EE21Member() : m_vtable((void *)__identifier("??_7Secondary005E7ED7@@6B@")), m_04(0) {}
	void *m_vtable;
	int m_04;
};

class Rva0073EE21 : public Rva0040F9D
{
public:
	Rva0073EE21();
private:
	Rva0073EE21Member m_08;
};

Rva0073EE21::Rva0073EE21() : Rva0040F9D(1, 0, 0, 0)
{
	*(const void **)this = g_00CF1538;
	m_08.m_vtable = (void *)g_00CF1534;
}
