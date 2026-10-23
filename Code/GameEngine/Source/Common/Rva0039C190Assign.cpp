// cl: /Oy-
//
// ?rva0039C190@Rva0039C190@@QAEPAVRva0039B893@@PAV2@0@Z @0x0039C190 51B
// Vector-like reassign: copies [first, m_04) into result through the rowed
// 3-arg ?Rva0039BD9BCopy (callers push four args; the extra tag arg is
// ignored and the leaked inner-copy return is the new end), destroys
// [newEnd, m_04) via rowed ?Rva0022C8E3DestroyRange, stores the new end,
// returns result. Evidence: chain lane, callers at 0x0039C40F/0x0039C770/
// 0x0039D19E, twin of banked 0x0015068C. Owning class unproven.

class Rva0039B893;
struct Rva0052BF9BElem;

void __cdecl Rva0039BD9BCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result);
void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *first, Rva0052BF9BElem *last);

class Rva0039C190
{
public:
	Rva0039B893 *rva0039C190(Rva0039B893 *result, Rva0039B893 *first);
	void rva0039C40A();

private:
	int m_00;
	Rva0052BF9BElem *m_04;
};

typedef Rva0039B893 *(__cdecl *Copy4Fn)(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, void *tag);

Rva0039B893 *Rva0039C190::rva0039C190(Rva0039B893 *result, Rva0039B893 *first)
{
	Rva0052BF9BElem *newEnd = (Rva0052BF9BElem *)((Copy4Fn)Rva0039BD9BCopy)(first, (Rva0039B893 *)m_04, result, (void *)((char *)&result + 3));
	Rva0022C8E3DestroyRange(newEnd, m_04);
	m_04 = newEnd;
	return result;
}

// ?rva0039C40A@Rva0039C190@@QAEXXZ, retail 0x0039C40A, 11 bytes: clear() -
// the range erase above over [+0, +4) (its call at 0x0039C40F). Skeleton
// twin of STLport vector clear 0x000BCFB8.
void Rva0039C190::rva0039C40A()
{
	rva0039C190((Rva0039B893 *)m_00, (Rva0039B893 *)m_04);
}
