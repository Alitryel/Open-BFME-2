// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAUTreeKey00242F5E@@PAU1@@_STL@@YAPAUTreeKey00242F5E@@PAU1@00ABU__false_type@0@@Z @0x00523E01 38B:
// Existing eight-byte vector view; direct genuine mutable-pair Construct523DD4.
// Native Apt adder524845 supplies std::make_pair and erase writes its first
// dword. The int spelling follows that producer's source view; signedness
// is not inferred from copy bytes. Callers52451A/524565 are in5244DC.
// Dedicated TU so the call stays external.
struct TreeKey00242F5E
{
	char _m[8];
public:
	TreeKey00242F5E(const TreeKey00242F5E &that);
};
class AsciiString;
namespace _STL {
template <class First, class Second> struct pair;
template <class T, class U> void _Construct(T *, const U &);
}
namespace _STL
{
struct __false_type {};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_STL::_Construct((_STL::pair<int, AsciiString> *)cur, *(const _STL::pair<int, AsciiString> *)first);
	return cur;
}
}
template TreeKey00242F5E *_STL::__uninitialized_copy(TreeKey00242F5E *, TreeKey00242F5E *, TreeKey00242F5E *, const _STL::__false_type &);
