// cl: /DNDEBUG /MD /EHsc /Og-
// Sized free dispatcher twin of bfmeFreePM (BfmeTwoHundredSeventyThree.cpp):
// blocks over 0x80 bytes go through the one-argument big free, the rest
// through the two-argument small free. Retail 0x00028DC0 reaches the folded
// big free at 0x000237A0 and the lock-guarded small free at 0x00027B40
// (rowed as the node-alloc deallocate, pinned as bfmeSmallFreeVLX), where
// the PM sibling reaches its own PM pair. The true instance name is not
// proven by these bytes, so this row rides under an Rva owner.

void bfmeBigFreePM(void *at);
void Rva00028DC0FreeSized(void *at, unsigned int bytes);

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc;

template <>
class __node_alloc<true, 0>
{
private:
	static void _M_deallocate(void *p, unsigned int n);
	friend void ::Rva00028DC0FreeSized(void *at, unsigned int bytes);
};
}

// ?Rva00028DC0FreeSized@@YAXPAXI@Z
void Rva00028DC0FreeSized(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeBigFreePM(at);
	else
		_STL::__node_alloc<true, 0>::_M_deallocate(at, bytes);
}
