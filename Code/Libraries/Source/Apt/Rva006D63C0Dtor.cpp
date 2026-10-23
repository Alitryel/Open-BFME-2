// cl: /DNDEBUG /MD /EHsc
// AptValueWithHash owns the native hash at +8 and the GC base at +0.
// Retail slot 14 at 0x008EA228 calls this complete destructor at 0x006D63C0.
class Rva0070A840
{
public:
    ~Rva0070A840();
};
class __declspec(novtable) Rva006DE350
{
public:
    virtual ~Rva006DE350();
    unsigned int m_flags;
};
class __declspec(novtable) AptValueWithHash : public Rva006DE350
{
    Rva0070A840 m_hash;
protected:
    virtual ~AptValueWithHash();
};
AptValueWithHash::~AptValueWithHash()
{
}
