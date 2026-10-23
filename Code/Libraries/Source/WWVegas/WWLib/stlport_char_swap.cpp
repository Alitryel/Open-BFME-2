// cl: /Od /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// _STL::swap(char&, char&), retail 0x0024870 (34 B). Register-variant sibling
// of the int swap 0x0024750 in stlport_rb_tree_rebalance_erase.cpp: same /Od
// body and 0x18 frame, but a byte load/store with the temporary in the low
// frame byte at ebp-1 (mov cl / mov al) instead of the int's ebp-4 dword.
// STLport's char swap from the same <stl/_alloc.h> header. Derived from the
// rowed int-swap recipe, not copied: the operand widths are the difference.

namespace _STL
{

void swap(char &a, char &b)
{
	char t = a;
	a = b;
	b = t;
}

}
