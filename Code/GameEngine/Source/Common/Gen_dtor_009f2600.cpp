// cl: /DNDEBUG /MD /EHsc

// Retail 0x009F5970 is the complete destructor for the generated class
// Gen_dtor_009f2600. It first calls the object's cleanup operation, then
// destroys the twelve-byte elements at +0x18 through the MSVC EH vector
// destructor iterator (seventeen in BFME1, twenty-one here). The cleanup
// body is the retail routine at 0x00627600 (pin); its internal layout is
// independent of this destructor's trailing array. B1 0x009F5970 84B ->
// B2 0x00627DE0 84B, immediate-only drift at +0x30 (push 0x11 vs 0x15).

// The element destructor retail hands the EH vector iterator is 0x00142D70,
// the rowed STLport narrow basic_string destructor: each twelve-byte
// element is a string.
namespace _STL {
template <class _Tp> class allocator;
template <class _CharT> class char_traits;
template <class _CharT, class _Traits, class _Alloc> class basic_string
{
public:
	~basic_string();
};
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva00142D70String;

struct Gen_uw_009f5690
{
	~Gen_uw_009f5690() { ((Rva00142D70String *)this)->Rva00142D70String::~Rva00142D70String(); }
	int m_head;
	char m_body[0xC - sizeof(int)];
};

class __declspec(novtable) Gen_dtor_009f2600
{
public:
	virtual ~Gen_dtor_009f2600();
	void cleanup();

private:
	char m_pad[0x14];
	Gen_uw_009f5690 m_items[21];
};

Gen_dtor_009f2600::~Gen_dtor_009f2600()
{
	cleanup();
}
