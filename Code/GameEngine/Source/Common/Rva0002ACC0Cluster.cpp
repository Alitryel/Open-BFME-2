// cl: /Od
//
// Two length-computing forwarding wrappers that sit between the BfmeThingPI
// range caller (0x0002AC90) and the Rva0002ACF0Thing range caller (0x0002ACF0).
// Each is the pair-of-ends bridge built without optimisation: it takes the
// caller's start and second word, and passes the run's length through the
// pinned char_traits<char>::length at 0x00006F30. The classes are the rowed
// owners of the single callee each wrapper reaches; the method names are this
// image's addresses.

namespace _STL {

template<class _CharT> struct char_traits;

template<> struct char_traits<char>
{
	static unsigned int length(const char *text);
};

}

class BfmeS1155
{
public:
	unsigned int bfmeFind1155(const char *s, unsigned int pos, unsigned int n);

	unsigned int Rva0002ACC0(const char *s, unsigned int pos);
};

unsigned int BfmeS1155::Rva0002ACC0(const char *s, unsigned int pos)
{
	return bfmeFind1155(s, pos, _STL::char_traits<char>::length(s));
}

class Rva0002ACF0Thing
{
public:
	void bfmeDoPF(char *at, void *what, int many);

	void Rva0002AD20(char *s, void *what);
};

void Rva0002ACF0Thing::Rva0002AD20(char *s, void *what)
{
	bfmeDoPF(s, what, _STL::char_traits<char>::length(s));
}
