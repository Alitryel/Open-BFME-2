// cl: /Od
//
// Byte-search predicate over a two-word char range, sitting between
// bfmeFindFirstOfVMD (0x00026E40) and the basic_string constructors. The range
// layout matches the rowed BfmeS1155 (0x0002A3A0) and BfmeRangePI spellings:
// begin at +0, end at +4. The body is /Od (frame pointer, unoptimised), calls
// the pinned bfmeFindByteInRange at 0x00026C60, and reports whether the search
// reached the end. Class and method names are this image's addresses.

char *bfmeFindByteInRange(char *rangeFirst, char *rangeLast, char wanted);

class Rva00027080Thing
{
public:
	int Rva00027080(const char *p);

	char *m_begin;		// +0x00
	char *m_end;		// +0x04
};

// ?Rva00027080@Rva00027080Thing@@QAEHPBD@Z @ 0x00027080 (65B)
int Rva00027080Thing::Rva00027080(const char *p)
{
	char wanted = *p;
	char value = wanted;	// the extra /Od copy is what retail's frame shows

	return bfmeFindByteInRange(m_begin, m_end, value) == m_end;
}
