// ?rva00050DBD@Rva00050DBD@@QAE_NXZ @0x00050DBD 19B virtual-forward via +0x44; callers 0x53633 0x5ED07 0x5ED79 0x5EE5F 0x5EEBA
// ?rva00050DD0@Rva00050DD0@@QAE_NXZ @0x00050DD0 19B virtual-forward via +0x4C; callers 0x536A0 0x53787 0x537AB 0x5EDAB 0x5EE1E
struct Probe44
{
	virtual bool check(int v);
};
struct Outer44
{
	char m_pad[0x44];
	Probe44 m_iface;
};
class Rva00050DBD
{
public:
	Outer44 *m_outer;
	bool rva00050DBD();
};
bool Rva00050DBD::rva00050DBD()
{
	if (m_outer != 0)
		return m_outer->m_iface.check(0);
	return false;
}
struct Probe4C
{
	virtual bool check(int v);
};
struct Outer4C
{
	char m_pad[0x4C];
	Probe4C m_iface;
};
class Rva00050DD0
{
public:
	Outer4C *m_outer;
	bool rva00050DD0();
};
bool Rva00050DD0::rva00050DD0()
{
	if (m_outer != 0)
		return m_outer->m_iface.check(0);
	return false;
}
