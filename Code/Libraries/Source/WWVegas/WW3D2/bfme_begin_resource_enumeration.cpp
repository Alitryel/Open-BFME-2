// cl: /DNDEBUG /MD
//
// bfmeBeginResourceEnumeration, retail 0x0061F110, 21 bytes.
// If the global registry at VA 0x00E09C0C is live, forward the type tag
// into Begin at 0x00621480.

class BfmeResourceEnumerator
{
public:
	void Begin(unsigned tag);
};

extern class Q1Receiver0134FAAC *TheQ1Receiver;

void bfmeBeginResourceEnumeration(unsigned tag)
{
	if ((*(BfmeResourceEnumerator **)&TheQ1Receiver))
		(*(BfmeResourceEnumerator **)&TheQ1Receiver)->Begin(tag);
}
