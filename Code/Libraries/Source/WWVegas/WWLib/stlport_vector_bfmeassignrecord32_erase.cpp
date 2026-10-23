// cl: /O1
// stlport
//
// ?erase@?$vector@UBfmeAssignRecord32@@V?$allocator@UBfmeAssignRecord32@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord32@@PAU3@0@Z
// @ 0x00173FB6 (51B): range erase over vector<BfmeAssignRecord32>. Shifts
// the tail down with __copy_ptrs (29B wrapper emitted here as duplicate of
// the rowed 0x0017396F via the rowed __copy at 0x001737C0) then destroys
// the vacated tail with the rowed _Destroy at 0x00173AE0, stores the new
// finish and returns first. Follows VectorAsciiStringErase (0x002CCFC 51B)
// and FXBoneInfoVectorErase shape levers: prvalue __false_type tag forces
// the EBP frame with tag at [ebp+0xb].
struct BfmeAssignRecord32 {
	~BfmeAssignRecord32();
	unsigned char m_pad[32];
};

namespace _STL {

struct __false_type {
};

struct random_access_iterator_tag {
};

template <class Type>
class allocator {
};

template <class Type, class Allocator>
class vector {
public:
	typedef Type *iterator;
	iterator erase(iterator first, iterator last);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *extra);

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag)
{
	__false_type local;
	return __copy(first, last, result, reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);

}

inline _STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> >::iterator
_STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> >::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, m_finish, first, _STL::__false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}

// erase is a header inline in STLport: other units emit select-any copies of
// it, so a strong definition here was a duplicate symbol in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitstlport_vector_bfmeassignrecord32_erase@@YAXPAV?$vector@UBfmeAssignRecord32@@V?$allocator@UBfmeAssignRecord32@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitstlport_vector_bfmeassignrecord32_erase(_STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> > *p)
{
	p->erase(0, 0);
}
#pragma inline_depth()
