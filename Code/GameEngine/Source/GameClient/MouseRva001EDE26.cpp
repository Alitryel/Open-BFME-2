// cl: /MD
// ?rva001EDE26@Mouse@@QBE_NXZ @0x001EDE26 20B
// A tiny Mouse accessor (its 0x001EDE4C neighbour is Mouse::setPosition in Input/Mouse.cpp); cursor bytes at +0x4f9d/+0x4f9e and dwords at +0x4f0c/+0x4f10 per MouseSetEngineVisibility.cpp; callers at 0x41AA0 etc and 0x41AE3.
class Mouse {
	char _pad0[0x4f0c];
	int m_4f0c;
	int m_4f10;
	char _pad1[0x4f9d - (0x4f10 + 4)];
	unsigned char m_4f9d;
	unsigned char m_4f9e;
public:
	bool rva001EDE26() const;
};
bool Mouse::rva001EDE26() const
{
	return m_4f9d && m_4f9e;
}
