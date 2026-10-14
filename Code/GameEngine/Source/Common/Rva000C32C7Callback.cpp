// ?Rva000C32C7@@YAXPAVRva000C19C3@@PAXPB_N@Z, retail 0x000C32C7 (18B).
// A cdecl three-argument callback that forwards to a member of its first
// argument, passing the other two through: the shape of the rowed GameState
// post-process callbacks 0x002DC66F / 0x002DD908 with the owner first. The callee
// 0x000C19C3 is a thiscall taking (object, flag pointer): it reads the byte
// behind its second argument to pick one of two 0x14-byte slots at +0x160.
// No direct caller reaches 0x000C32C7 in retail; the names stay
// address-derived.
class Rva000C19C3
{
public:
	void rva000C19C3(void *object, const bool *flag);
};

void Rva000C32C7(Rva000C19C3 *owner, void *object, const bool *flag)
{
	owner->rva000C19C3(object, flag);
}
