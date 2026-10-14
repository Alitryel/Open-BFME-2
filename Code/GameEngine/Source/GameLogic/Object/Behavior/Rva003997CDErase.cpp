// cl: /MD /Oy-
// ?rva003997CD@Rva00399800@@QAEPAVRva0039597C@@PAV2@0@Z @0x003997CD 51B evidence: chain from rowed copy 0x00396260; erase-like shift over the owning range shared with rowed dtor TU Rva00395D77Destroy (same Destroy row 0x00399336 and layout); EBP frame under /O1 needs /Oy- (293 precedents); copy tag is last byte of first-arg slot per retail lea ebp+0xb; destroys [new_end m_end) per push order.
class Rva0039597C;
struct Rva00395D77;

Rva0039597C *Rva00396260Copy(Rva0039597C *first, Rva0039597C *last, Rva0039597C *dest, void *unused);

namespace _STL
{

template <class _Tp>
void _Destroy(_Tp first, _Tp last);

}

struct Rva00399800
{
	Rva00395D77 *m_begin;
	Rva00395D77 *m_end;
	Rva0039597C *rva003997CD(Rva0039597C *first, Rva0039597C *last);
	void rva00399EB3();
};

Rva0039597C *Rva00399800::rva003997CD(Rva0039597C *first, Rva0039597C *last)
{
	Rva0039597C *new_end = Rva00396260Copy(last, (Rva0039597C *)m_end, first, (void *)((char *)&first + 3));
	_STL::_Destroy((Rva00395D77 *)new_end, m_end);
	m_end = (Rva00395D77 *)new_end;
	return first;
}

// ?rva00399EB3@Rva00399800@@QAEXXZ, retail 0x00399EB3, 11 bytes: clear() -
// the erase above over [begin, end). Skeleton twin of STLport vector clear
// 0x000BCFB8.
void Rva00399800::rva00399EB3()
{
	rva003997CD((Rva0039597C *)m_begin, (Rva0039597C *)m_end);
}
