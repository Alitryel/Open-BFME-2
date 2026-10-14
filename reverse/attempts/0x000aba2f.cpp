// ?rva000ABA2F@@YAXXZ
// partial score=0.84 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva000ABA2F@@YAXXZ @0x000ABA2F 339B: dispatch/vtable table initializer.
// Retail writes 33 function pointers into the table at 0x00E17728 then calls
// the 0x006CD1F0 hook with 0. WB 0x8A5550 (345B) has the same stores in order.
void Rva006CD1F0Set(int);
void rva000ABA2F()
{
	*(void **)0x00E17728 = (void *)0x004A91D3;
	*(void **)0x00E1772C = (void *)0x004A91D8;
	*(void **)0x00E17734 = (void *)0x004B3FD0;
	*(void **)0x00E17738 = (void *)0x004A98DC;
	*(void **)0x00E1773C = (void *)0x004B3FD0;
	*(void **)0x00E17740 = (void *)0x004B3FD0;
	*(void **)0x00E17744 = (void *)0x004B3FD0;
	*(void **)0x00E17748 = (void *)0x004AB96D;
	*(void **)0x00E1774C = (void *)0x004AB450;
	*(void **)0x00E17750 = (void *)0x004A91D8;
	*(void **)0x00E17758 = (void *)0x004A91DD;
	*(void **)0x00E1775C = (void *)0x004A91F1;
	*(void **)0x00E17764 = (void *)0x004A91FD;
	*(void **)0x00E17768 = (void *)0x004A9211;
	*(void **)0x00E17770 = (void *)0x004AAD88;
	*(void **)0x00E17774 = (void *)0x004A923E;
	*(void **)0x00E17778 = (void *)0x004AA87E;
	*(void **)0x00E1777C = (void *)0x004D43D0;
	*(void **)0x00E17780 = (void *)0x004B3FD0;
	*(void **)0x00E17784 = (void *)0x004B3FD0;
	*(void **)0x00E17788 = (void *)0x004B3FD0;
	*(void **)0x00E1778C = (void *)0x004AA8AE;
	*(void **)0x00E17790 = (void *)0x004B3FD0;
	*(void **)0x00E17794 = (void *)0x004AB469;
	*(void **)0x00E17798 = (void *)0x004AA8C3;
	*(void **)0x00E1779C = (void *)0x004B3FD0;
	*(void **)0x00E177A0 = (void *)0x004A92B0;
	*(void **)0x00E177A4 = (void *)0x004A994C;
	*(void **)0x00E177A8 = (void *)0x004AA8D1;
	*(void **)0x00E177AC = (void *)0x004AA645;
	*(void **)0x00E177B4 = (void *)0x004910FB;
	*(void **)0x00E177C8 = (void *)0x004A92A2;
	*(void **)0x00E177CC = (void *)0x004A92A9;
	Rva006CD1F0Set(0);
}