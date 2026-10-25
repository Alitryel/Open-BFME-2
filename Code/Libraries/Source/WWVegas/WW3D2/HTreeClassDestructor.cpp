// cl: /DNDEBUG /MD
//
// HTreeClass destructor, retail 0x001667E0, 26 bytes.
// Calls Free then the C allocator on the first owned-sequence word at +0x1C.
// Use the existing htree.h member spelling so the body composes with that TU;
// the retail field is a pointer, stored by the current header as a 32-bit word.

extern "C" void __cdecl free(void *);

class HTreeClass
{
	char pad[0x1C];
	unsigned int OwnedSequence1C[3];

public:
	void Free();
	~HTreeClass();
};

HTreeClass::~HTreeClass()
{
	Free();
	if (OwnedSequence1C[0])
		free(reinterpret_cast<void *>(OwnedSequence1C[0]));
}
