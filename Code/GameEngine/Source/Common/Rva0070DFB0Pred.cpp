// cl: /MD
// AptObject slot 7 in retail vtable 0x008EA264 returns the registerClass value.
// The name comparison at 0x006D3230 and the value global retain their rowed spellings.
extern "C" int __cdecl strcmp(const char *, const char *);
struct Rva008A4570Owner {
    void *m_data;
    bool nameEquals(const char *text);
};

extern int g_00E18064;
// g_00E18064: matched references place it at VA 0xe18064 (zero-filled .bss).
int g_00E18064;

class AptValue;
class EAStringC;
class AptObject {
public:
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
};

AptValue *AptObject::objectMemberLookup(AptValue *const, const EAStringC *const name) const
{
    return reinterpret_cast<AptValue *>(((Rva008A4570Owner *)name)->nameEquals("registerClass") ? g_00E18064 : 0);
}
