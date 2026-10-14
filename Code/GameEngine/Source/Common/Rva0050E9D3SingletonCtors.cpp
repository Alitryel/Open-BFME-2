// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Out-of-line constructors of the two guarded singletons whose getters live
// in Rva0050E9D3Enable.cpp. Each getter builds its static in place by
// writing the vtable and setting the flag byte at +4; retail also keeps the
// standalone constructor that does the same (no direct caller):
//  - ??0Rva004E3FFA@@QAE@XZ 0x004E3FFA (13B): vtable VA 0x00C621F0, the
//    static at 0x00E0445C behind Rva004E4179Get.
//  - ??0Rva0043C705@@QAE@XZ 0x0043C705 (13B): vtable VA 0x00C3D690, the
//    static at 0x00E03318 behind Rva0043C9B3Get.
// The classes are unknown; the vptr is modelled as an explicit word, as the
// getters do, so this unit emits no vtable. Skeleton twins of
// FloatUpdateModuleData's ctor 0x0048D7A6.

extern const void *const g_00C621F0[];
extern const void *const g_00C3D690[];

class Rva004E3FFA
{
public:
	Rva004E3FFA();

private:
	const void *m_vtable;	// +0
	unsigned char m_flag;	// +4
};

Rva004E3FFA::Rva004E3FFA()
{
	m_vtable = g_00C621F0;
	m_flag = 1;
}

class Rva0043C705
{
public:
	Rva0043C705();

private:
	const void *m_vtable;	// +0
	unsigned char m_flag;	// +4
};

Rva0043C705::Rva0043C705()
{
	m_vtable = g_00C3D690;
	m_flag = 1;
}
