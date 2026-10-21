// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) void* __cdecl memmove( void*, const void*, unsigned int );

struct Element {
	int val0;
	void* val4;
	void* val8;
};

// The retail REL32 decodes to 0x0003E4B0, already matched as
// ?DebugReAllocMemory@@YAPAXPAXI@Z (same realloc-like shape); declare the
// true spelling instead of the donor's placeholder, so no new pin is needed.
extern void *DebugReAllocMemory(void *, unsigned);

class Rva00889C90Class
{
public:
	int m_val0;
	Element* m_data; // +4
	unsigned int m_size;      // +8

	void d_00889c90( void* arg1, void* arg2 );
};

void Rva00889C90Class::d_00889c90( void* arg1, void* arg2 )
{
	if ( !arg1 ) return;

	for ( unsigned int i = 0; i < m_size; ++i )
	{
		Element* element = &m_data[i];
		if ( element->val4 == arg1 && element->val8 == arg2 )
		{
			memmove( element, element + 1, (m_size - i - 1) * sizeof(m_data) );
			m_data = m_data - 1;
			m_data = (Element*)DebugReAllocMemory( m_data, m_size * sizeof(Element) );
		}
	}
}
