// ?rva000908F6@Rva007E3C20Vp6Stream@@QAEXXZ
// partial score=0.98 date=2026-10-14
// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva000908F6@Rva007E3C20Vp6Stream@@QAEXXZ, retail 0x000908F6 (193 B): the
// VP6 stream's two-pass tag scanner (video tags then audio tags). Layout is
// inferred from register use only.

class Rva007E3C20Vp6Stream;

class BfmeB996
{
public:
	char movePair(int *output, int *first, unsigned int *second, unsigned int limit);
};

void __cdecl Rva009A5800Forward(int s, int data, int size);
typedef void (__cdecl *ForwardFn)(int, int, int, int, int);

extern Rva007E3C20Vp6Stream *g_de44a0;
extern int g_de449c;

class Rva007E3C20Vp6Stream
{
public:
	void rva000908F6();

	char m_pad0[0x14];
	int m_handleB;
	int m_handleA;
	char m_pair[8];
	char m_pad1[0x30 - 0x24];
	int m_arg30;
	int m_arg34;
	char m_scanVideo;
	char m_pad2[3];
	int m_count;
	char m_pad3[8];
	int m_counter;
	char m_pad4[8];
	int m_buf;
	unsigned int m_limit;
};

void Rva007E3C20Vp6Stream::rva000908F6()
{
	int tag;
	int size;
	g_de44a0 = this;
	if (this->m_scanVideo)
	{
		do
		{
			if (!reinterpret_cast<BfmeB996 *>(m_pair)->movePair((int *)m_buf, &tag, (unsigned int *)&size, m_limit))
			{
				m_counter = m_count - 1;
				return;
			}
		} while (tag != 0x4b305641 && tag != 0x46305641);
		((ForwardFn)Rva009A5800Forward)(m_handleA, m_buf + 8, size, m_arg30, m_arg34);
	}
	char ok;
	do
	{
		ok = reinterpret_cast<BfmeB996 *>(m_pair)->movePair((int *)m_buf, &tag, (unsigned int *)&size, m_limit);
		++g_de449c;
		if (!ok)
		{
			m_counter = m_count - 1;
			return;
		}
	} while (tag != 0x4b30564d && tag != 0x4630564d);
	((ForwardFn)Rva009A5800Forward)(m_handleB, m_buf + 8, size, m_arg30, m_arg34);
	++m_counter;
}
