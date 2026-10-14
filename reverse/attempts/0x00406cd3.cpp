// ?rva00406CD3@Rva00406BB0@@UAE?AURva00406CD3Ptr@@XZ
// partial score=0.85 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// 0x00406CD3 (75B): Rva00406BB0's clone slot - new 12-byte copy through the
// rowed copy ctor 0x00406BB0, returned in a one-pointer holder through the
// hidden slot. Best form so far (71B): retail additionally zeroes a flag
// at [ebp-0x10], keeps the allocation at [ebp-0x14] and runs the new under
// EH state 1 (one more state-0 entry); this form gives state 0 with the
// allocation in [ebp-0x10]. NRVO/assign forms add the holder dtor call.
struct Rva00406CD3Ptr
{
	Rva00406CD3Ptr(void *p) : m_ptr(p) {}
	~Rva00406CD3Ptr();
	void *m_ptr;
};

class Rva00406BB0
{
public:
	Rva00406BB0(const Rva00406BB0 &other);
	virtual Rva00406CD3Ptr rva00406CD3();
private:
	void *m_04;
	int m_08;
};

Rva00406CD3Ptr Rva00406BB0::rva00406CD3()
{
	return Rva00406CD3Ptr(new Rva00406BB0(*this));
}
