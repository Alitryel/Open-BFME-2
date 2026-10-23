// ?erase@?$vector@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@QAEPAVRva00297360Element@@PAV3@@Z
// cl: /Ireference/shims/bfme2_ascii /O1
// ?erase@?$vector@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@QAEPAVRva00297360Element@@PAV3@@Z @0x0040370D 55B single erase.
// Evidence: unlock lane; stride-0x10 Rva element with AsciiString at +4 via Rva00297360ElementCopy;
// rowed CopyRange 0x002915EB plus pinned element dtor at 0x0029D7C2 (ICF CameraMarker row);
// caller 0x004037A2 vector scan at +0x20/+0x24 key compare stride-0x10; shape-identical to
// BfmeStringRecord single erase 0x00357CA2 (55B ret 4) and ModuleInfo Nugget erase 0x0033C3BC.
#include "ascii_string.h"

class Rva00297360Element {
public:
  ~Rva00297360Element();

  int m_00;
  AsciiString m_04;
  int m_08;
  int m_0C;
};

Rva00297360Element *Rva002915EBCopyRange(Rva00297360Element *first, Rva00297360Element *last, Rva00297360Element *result, const int *tag);

namespace _STL {

struct __false_type
{
};

template <class Type>
class allocator {
};

template <class Type, class Allocator>
class vector {
public:
  typedef Type *iterator;

  iterator erase(iterator position);
  iterator end() { return m_finish; }

private:
  iterator m_start;
  iterator m_finish;
  iterator m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag);

struct random_access_iterator_tag
{
};

// STLport's random-access copy loop, rowed at 0x0028F869 (stlport_copy_rva00297360.cpp).
template <class RandomAccessIter, class OutputIter, class Distance>
OutputIter __copy(RandomAccessIter first, RandomAccessIter last, OutputIter result,
	const random_access_iterator_tag &, Distance *);

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag)
{
	random_access_iterator_tag category;
	return __copy(first, last, result, category, (int *)0);
}

}

inline _STL::vector<Rva00297360Element, _STL::allocator<Rva00297360Element> >::iterator
_STL::vector<Rva00297360Element, _STL::allocator<Rva00297360Element> >::erase(
  iterator position)
{
  if (position + 1 != end()) {
    __copy_ptrs(position + 1, m_finish, position, __false_type());
  }
  --m_finish;
  m_finish->~Rva00297360Element();
  return position;
}

// This erase is a header inline in retail: one other unit emits a select-any
// copy of it, so a strong definition here was a duplicate symbol in the linked
// build. Making it inline emits the same copy as select-any, and this anchor
// only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva00297360ElementErase@@YAXPAV?$vector@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitRva00297360ElementErase(_STL::vector<Rva00297360Element, _STL::allocator<Rva00297360Element> > *p)
{
  p->erase(0);
}
#pragma inline_depth()