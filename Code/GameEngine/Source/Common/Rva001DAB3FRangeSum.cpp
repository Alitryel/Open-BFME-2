// cl: /DNDEBUG /MD /EHsc /Oy- /Os
// ?Rva001DAB3F@@YAXPAHPAVRva001DA112@@1@Z @0x001DAB3F 50B: copies a (begin,end) pointer pair into a
// string-like target through the rowed 0x001DA112 range ctor and sums the second word of every 8-byte pair
// into *b. Codegen: the empty allocator argument is a const-ref temp (named) living in the dead
// first-param slot [ebp+0xb]; taking &range instead made it an escaped variable.
struct EmptyAlloc {};
class Rva001DA112
{
public:
	void rva001DA112(int lhs, int rhs, char *p);
};
void Rva001DAB3F(int *range, Rva001DA112 *lhs, Rva001DA112 *rhs)
{
	const EmptyAlloc &al = EmptyAlloc();
	lhs->rva001DA112(range[0], range[1], (char *)&al);
	*(int *)rhs = 0;
	for (int *p = (int *)range[0]; p != (int *)range[1]; p += 2)
		*(int *)rhs += p[1];
}
