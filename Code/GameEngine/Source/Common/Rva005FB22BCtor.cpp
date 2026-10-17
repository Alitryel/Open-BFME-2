// cl: /MD
// ??0Rva005FB22B@@QAE@PBX@Z @ 0x005FB22B 24B
// Honest address-name ctor beside Rva005FA393Dtor. Target evidence: 24B
// retail stores vtable VA 0x879F04 at [this], zeroes +4, copies *arg to +8,
// 1 caller 0x5FB2B3, ret 4. Prev dtor shares /O1 /MD shape.
// The retail table at RVA 0x00879F04: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva004E84A4@@QAEPAXI@Z")();
void __identifier("?clone@Rva005FB22B@@QBE?AV?$RvaCloneResult@VRva005FB22B@@@@XZ")();
void __identifier("?rva005FB243@Rva005FB243@@QAE?AURvaF1Handle@@HH@Z")();
}
extern const void *const g_00879F04[3] = {
	(const void *)&__identifier("??_GRva004E84A4@@QAEPAXI@Z"), // slot 0 0x005FAA31
	(const void *)&__identifier("?clone@Rva005FB22B@@QBE?AV?$RvaCloneResult@VRva005FB22B@@@@XZ"), // slot 1 0x005FB2CC
	(const void *)&__identifier("?rva005FB243@Rva005FB243@@QAE?AURvaF1Handle@@HH@Z"), // slot 2 0x005FB243
};
template <class T> class RvaCloneResult {
public: RvaCloneResult(T *p):pointer(p){if(p)++p->m_ref;} ~RvaCloneResult();
private: T *pointer;
};
class __declspec(novtable) Rva005FB22B
{
public:
    Rva005FB22B(const void *arg);
    virtual ~Rva005FB22B();
    RvaCloneResult<Rva005FB22B> clone() const;
    __forceinline Rva005FB22B(const Rva005FB22B &src):m_ref(0) {
      *(const void **)this=g_00879F04;m_08=src.m_08;
    }
private:
    template<class T> friend class RvaCloneResult;
    int m_ref;
    void *m_08;
};
Rva005FB22B::Rva005FB22B(const void *arg)
{
    m_ref = 0;
    *(const void **)this = g_00879F04;
    m_08 = *(void *const *)arg;
}

// Native 005FB2CC: copy payload+8 into fresh12-byte counted object.
RvaCloneResult<Rva005FB22B> Rva005FB22B::clone() const {
 return RvaCloneResult<Rva005FB22B>(new Rva005FB22B(*this));
}
