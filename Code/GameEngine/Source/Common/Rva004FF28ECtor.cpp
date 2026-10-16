// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FF28E (50B): five-int init storing vtable 0xC63B34 plus +0x28,
// forwarding three ints to the rowed 0x4FBC4D ctor and one int to the
// 0x20E449 copy ctor.
// Returns this as int. Identities unproven.

extern "C" const void *const vtbl_00C63B34[];  // ??_7Rva004FF2C0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C63B34=??_7Rva004FF2C0@@6B@")

// 0x004FBC4D is the rowed Rva004FBCBE constructor and 0x0020E449 the rowed
// Rva0020E449 copy constructor; both are called in place on raw storage.
class UnicodeString;

class Rva004FBCBE
{
public:
	Rva004FBCBE(const UnicodeString &a, const UnicodeString &b, int c);
};

class Rva0020E449
{
public:
	Rva0020E449(const Rva0020E449 &other);
};

class Rva004FF28EOwner
{
public:
	int rva004FF28E(int a0, int a1, int a2, int a3, int a4);

private:
	int m_vptr;		// +0x00 = 0xC63B34
	char m_pad04[0x24];	// +0x04..0x27
	int m_28;		// +0x28 = a0
	char m_2C[16];		// +0x2C copy target for 0x20E449
};

int Rva004FF28EOwner::rva004FF28E(int a0, int a1, int a2, int a3, int a4)
{
	((Rva004FBCBE *)this)->Rva004FBCBE::Rva004FBCBE(
		*(const UnicodeString *)a2, *(const UnicodeString *)a3, a4);
	*(int *)this = ((unsigned int)vtbl_00C63B34);
	m_28 = a0;
	((Rva0020E449 *)m_2C)->Rva0020E449::Rva0020E449(*(const Rva0020E449 *)a1);
	return (int)this;
}
