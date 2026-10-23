// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Time_Info destructor, the body every time facet's destructor
// calls on its _M_timeinfo. The five scalar strings come first in reverse
// declaration order at 0x210, 0x204, 0x1F8, 0x1EC and 0x1E0 - each one the
// inlined `if (_M_start) free(_M_start)` - and the three arrays follow through
// the compiler's vector destructor iterator, which is what the 12-byte string
// stride and the 14/24/2 element counts identify.
//
// Two things this body needs that are easy to get wrong. The string destructor
// has to be a PLAIN inline: as __forceinline MSVC 7.1 folds it in without
// tracking it, and the four `mov byte ptr [esp+0x10], N` unwind-state updates
// between the scalar strings - twenty bytes - never appear. And free has to be
// declared with C++ linkage: as extern "C" the compiler treats it as nothrow
// and drops the same states again.

extern "C" void __cdecl free(void *block) throw(...);

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class _Time_Info
{
public:
	~_Time_Info();

	string _M_dayname[14];
	string _M_monthname[24];
	string _M_am_pm[2];
	string _M_time_format;
	string _M_date_format;
	string _M_date_time_format;
	string _M_long_date_format;
	string _M_long_date_time_format;
};

inline _Time_Info::~_Time_Info()
{
}

}

// _Time_Info::~_Time_Info is a header inline in STLport: another unit emits a
// select-any copy of it, so a strong definition here was a duplicate symbol
// in the linked build. This anchor only makes this unit emit its copy for the
// ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitTimeInfoDtor@@YAXPAV_Time_Info@_STL@@@Z present-unmatched
void bfmeEmitTimeInfoDtor(_STL::_Time_Info *p)
{
	p->_Time_Info::~_Time_Info();
}
#pragma inline_depth()
