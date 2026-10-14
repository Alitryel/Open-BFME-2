// cl: /O1 /MD
// ?Rva0045D7E0Notify@@YAXPAXHH@Z @0x0045D7E0 121B. Notify pass over three
// arrays of four pointer vectors in the owner record (+0x88, +0x58, +0xB8,
// 12-byte vector records), skipping null entries. Callees are rowed:
// 0x001F0410, 0x001E11F8 and 0x002CAC6E. Binding host as a reference to the
// parameter keeps [ebp+8] live, so the counter gets its own [ebp-4] slot.
class ObjectCreationList
{
public:
	void rva001F0410(void *a1, void *a2);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

class Rva002CA9CA
{
public:
	void rva002CAC6E(int a, int b);
};

template <class T> struct Rva0045D7E0Vector
{
	T **m_begin;
	T **m_end;
	T **m_cap;
};

struct Rva0045D7E0Host
{
	char m_pad[0x58];
	Rva0045D7E0Vector<Rva001E11F8> m_a[4];        // +0x58
	Rva0045D7E0Vector<ObjectCreationList> m_b[4]; // +0x88
	Rva0045D7E0Vector<Rva002CA9CA> m_c[4];        // +0xB8
};

void Rva0045D7E0Notify(void *obj, int a, int b)
{
	Rva0045D7E0Host *&host = *(Rva0045D7E0Host **)&obj;
	for (int i = 0; i < 4; ++i) {
		for (ObjectCreationList **p1 = host->m_b[i].m_begin; p1 != host->m_b[i].m_end; ++p1) {
			if (*p1)
				(*p1)->rva001F0410((void *)a, (void *)b);
		}
		for (Rva001E11F8 **p2 = host->m_a[i].m_begin; p2 != host->m_a[i].m_end; ++p2) {
			if (*p2)
				(*p2)->rva001E11F8(a, b);
		}
		for (Rva002CA9CA **p3 = host->m_c[i].m_begin; p3 != host->m_c[i].m_end; ++p3) {
			if (*p3)
				(*p3)->rva002CAC6E(a, b);
		}	}
}
