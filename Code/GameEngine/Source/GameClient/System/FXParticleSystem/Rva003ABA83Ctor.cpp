// cl: /DNDEBUG /MD /EHsc
// ??0Rva003ABA83@@QAE@PAX0@Z @0x003ABA83 42B
// Unlock lane: ctor calling rowed T1Base 0x0055C903 with same (a,b) then
// vtable g_00C1C334 plus address of s_slot3E4first at +0x14 and g_ data at
// +0x18 as immediates. Evidence: three mov-dword immediates; base ctor rowed;
// s_slot3E4first extern C; neighbours /O1 /EHsc; ret 8 frameless.
extern "C" void *s_slot3E4first;
// The retail table at RVA 0x0081C334: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z")();
void __identifier("?doParticles@?$DefaultModule@$05@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
extern const void *const g_00C1C334[11] = {
	(const void *)&__identifier("??_GRva003AD273@@UAEPAXI@Z"), // slot 0 0x003AD257
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z"), // slot 3 0x00560AE1
	(const void *)&__identifier("?doParticles@?$DefaultModule@$05@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z"), // slot 4 0x0055C478
	(const void *)&__identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ"), // slot 5 0x00560ABA
	(const void *)&__identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ"), // slot 6 0x004BD9CB
	(const void *)&__identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ"), // slot 7 0x0055C44F
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 8 0x000910FB
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 9 0x000910FB
	(const void *)&__identifier("?Rva004647D1Get@@YAMXZ"), // slot 10 0x004647D1
};
extern "C" const void *const __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE43F@@6B@")[];
class T1Base_005F3750
{
public:
	T1Base_005F3750(void *a, void *b);
	virtual ~T1Base_005F3750();
private:
	char m_pad[0x14 - 4];
};
class Rva003ABA83 : public T1Base_005F3750
{
public:
	Rva003ABA83(void *a, void *b);
private:
	void *m_14;
	void *m_18;
};
Rva003ABA83::Rva003ABA83(void *a, void *b) : T1Base_005F3750(a, b)
{
	*(void **)this = (void *)g_00C1C334;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)__identifier("??_7Rva003AE43F@@6B@");
}
