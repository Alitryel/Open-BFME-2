// cl: /O1 /arch:SSE /G7 /EHsc /MD
// Retail 0x003F42BD (58 B, ret 4): visit every element of a pointer vector
// (begin at +4, end at +8) through slot 0 of the callback, stopping at the
// first element the callback rejects. The owner and callback names are
// address-derived; identity rests on the bytes (ecx = owner, one stack
// argument, virtual call [edx] with the element as its argument).
// Shape: a guarded do-loop (the entry test is the pointer difference through
// `sar`: `(unsigned)(end - begin) > 0u` keeps it, a signed `!= 0` folds to a
// test of 0xfffffffc) whose begin pointer is re-read at the loop top through a
// volatile alias, which is what makes the entry `sub eax,[esi+4]` a memory
// operand and the loop reload `mov eax,[esi+4]` as in retail.
template<class T> inline volatile T &__vref(T &x) { return *(volatile T *)&x; }

class Rva003F42BDCallback
{
public:
	virtual bool visit(void *item);
};

class Rva003F42BD
{
public:
	void rva003F42BD(Rva003F42BDCallback *callback);

private:
	int m_00;
	void **m_begin;
	void **m_end;
};

void Rva003F42BD::rva003F42BD(Rva003F42BDCallback *callback)
{
	unsigned int i = 0;
	if ((unsigned int)(m_end - m_begin) > 0u) {
		do {
			void **b = __vref(m_begin);
			if (!callback->visit(b[i]))
				break;
			++i;
		} while (i < (unsigned int)(m_end - m_begin));
	}
}
