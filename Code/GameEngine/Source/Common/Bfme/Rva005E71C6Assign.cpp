// cl: /DNDEBUG /MD /EHsc
// ?Rva005E71C6Assign@@YAXPAPAX0@Z, retail 0x005E71C6, 24 bytes.
// Free-function null-guarded assign with +0x28 refcount increment.
// Mirrors Rva00427A70::assign at 0x005E7184. Evidence: 6 callers at
// 0x005E71EC 0x005E7217 0x005E81E1 0x005E826E 0x005E82BD 0x005E82CF.

struct Rva005E71C6Object
{
	unsigned char m_unmodelled_000[0x28];
	unsigned m_references;
};

void Rva005E71C6Assign(void **dest, void **source)
{
	if (dest == 0)
		return;
	void *object = *source;
	*dest = object;
	if (object == 0)
		return;
	++static_cast<Rva005E71C6Object *>(object)->m_references;
}
