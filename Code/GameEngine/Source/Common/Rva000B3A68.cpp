// cl: /O2 /G7 /DNDEBUG /MD
// ?rva000B3A68@Rva000B3A68@@QAEEXZ @0x000B3A68 24B
// Honest address-derived placeholder: method rva000B3A68 in new opaque class
// Rva000B3A68. Unlock lane: callers 0x000B3D42 0x000BF2CA 0x000C0270.
// Caller 0x000B3D39 is vslot 62 (0xF8) of W3D draw vtables and calls this with
// the same this; offsets +0x110 +0x12C are directly visible. Unsigned char
// return per mov-al-1 xor-al-al shape; /O2 /G7 removes xor-first compare.
class Rva000B3A68
{
public:
	unsigned char rva000B3A68();
private:
	char m_pad00[0x110];
	int m_val110; // +0x110
	char m_pad114[0x18];
	int m_val12C; // +0x12C
};

unsigned char Rva000B3A68::rva000B3A68()
{
	return m_val110 != 0 && m_val12C != 0;
}
