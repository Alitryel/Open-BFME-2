// cl: /MD
// ??0Rva0053DAD0@@QAE@H@Z @0x0053DAD0 22B
// __thiscall ctor storing vtable g_00C69310 plus 0 at +4 plus int arg at +8.
// Evidence: mov eax ecx plus mov ecx esp+4 plus and eax+4 0 plus mov eax vtable
// plus mov eax+8 ecx plus ret 4; caller at 0x0031B812; vtable no name yet.
// The retail table at RVA 0x00869310: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00567A69@@UAEPAXI@Z")();
void __identifier("?rva0053DA53@SelectGameWindowHotKeyAction@@UAEII@Z")();
void __identifier("?rva0053DA64@SelectGameWindowHotKeyAction@@UAEII@Z")();
void __identifier("?doInvoke@SelectGameWindowHotKeyAction@@UAE_N_N@Z")();
}
extern const void *const g_00C69310[4] = {
	(const void *)&__identifier("??_GRva00567A69@@UAEPAXI@Z"), // slot 0 0x0053DAE6
	(const void *)&__identifier("?rva0053DA53@SelectGameWindowHotKeyAction@@UAEII@Z"), // slot 1 0x0053DA53
	(const void *)&__identifier("?rva0053DA64@SelectGameWindowHotKeyAction@@UAEII@Z"), // slot 2 0x0053DA64
	(const void *)&__identifier("?doInvoke@SelectGameWindowHotKeyAction@@UAE_N_N@Z"), // slot 3 0x0053DA75
};

class Rva0053DAD0
{
public:
	Rva0053DAD0(int value);
private:
	char m_pad[12];
};

Rva0053DAD0::Rva0053DAD0(int value)
{
	*(const void **)this = g_00C69310;
	*(int *)((char *)this + 4) = 0;
	*(int *)((char *)this + 8) = value;
}
