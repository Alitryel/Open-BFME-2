// cl: /Od
// A run named by its start and length passed on as a pair of ends, built
// without optimisation. The frame holds something this body never names.

namespace _STL
{
template <class T> class char_traits;
template <class T> class allocator;

template <class T, class Traits, class Allocator>
class basic_string
{
public:
	basic_string &assign(const char *first, const char *last);
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > OTString;

class BfmeThingOT
{
public:
	void bfmeSetOT(char *at, int many);
};

void BfmeThingOT::bfmeSetOT(char *at, int many)
{
	unsigned char spare[0x68];

	((OTString *)this)->assign(at, at + many);
}
