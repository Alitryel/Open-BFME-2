// ?rva00602810@Rva00602810@@QAEHXZ @0x00602810 19B: honest-address thiscall near Rva006026E0 cluster.
// Evidence: retail reads ecx+0xc as pointer, returns 0 when [p]==0 else [p]-[p+8]; callers at 0x00428075 0x00428099 unclaimed.
class Rva00602810
{
public:
	char m_pad00[0xc];
	int *m_p0c;
	int rva00602810();
};

int Rva00602810::rva00602810()
{
	if (m_p0c[0] != 0)
		return m_p0c[0] - m_p0c[2];
	return 0;
}

// ?rva006026C0@Rva006026C0@@QAEHXZ @0x006026C0 19B: same skeleton as 0x00602810 on receiver+0x8.
// Evidence: retail reads ecx+0x8 as pointer, returns 0 when [p]==0 else [p]-[p+8].
class Rva006026C0
{
public:
	char m_pad00[0x8];
	int *m_p08;
	int rva006026C0();
};

int Rva006026C0::rva006026C0()
{
	if (m_p08[0] != 0)
		return m_p08[0] - m_p08[2];
	return 0;
}

// ?rva00602850@Rva00602850@@QAEHXZ @0x00602850 19B: same skeleton as 0x00602810 on receiver+0x14.
// Evidence: retail reads ecx+0x14 as pointer, returns 0 when [p]==0 else [p]-[p+8].
class Rva00602850
{
public:
	char m_pad00[0x14];
	int *m_p14;
	int rva00602850();
};

int Rva00602850::rva00602850()
{
	if (m_p14[0] != 0)
		return m_p14[0] - m_p14[2];
	return 0;
}
