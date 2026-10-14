// cl: /DNDEBUG /MD
// ?Rva000A98BACleanup@@YAXXZ @0x000A98BA 34B
// Free singleton destroy: if g_00DE6170 non-null call virtual dtor at 0x0011018B then operator delete at 0x0002FD60 and clear with and [m],0.
// Evidence: frameless mov ecx test je; push esi mov esi ecx call the 0x0011018B destructor (rowed ??1Rva00785FD0Renderer@@QAE@XZ); push esi call ??3 mem_ops; and global 0 pop ecx pop esi ret; callers at 0x0006290B 0x000668FC.
class Rva0011018B
{
public:
	virtual ~Rva0011018B();
};
// g_00DE6170: matched references place it at VA 0xde6170 (retail .data initial value 0).
Rva0011018B * g_00DE6170 = 0;
void __cdecl operator delete(void *p);

// The destructor at 0x0011018B is rowed as the non-virtual
// ??1Rva00785FD0Renderer@@QAE@XZ (WW3D2/Rva0011018BDestructor.cpp).
class Rva00785FD0Renderer
{
public:
	~Rva00785FD0Renderer();
};

void __cdecl Rva000A98BACleanup(void)
{
	if (g_00DE6170 == 0)
		return;
	Rva0011018B *p = g_00DE6170;
	((Rva00785FD0Renderer *)g_00DE6170)->~Rva00785FD0Renderer();
	::operator delete(p);
	g_00DE6170 = 0;
}
