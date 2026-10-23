// cl: /O2
// Return nested +0x101 text, falling back to virtual slot 7 on its optional source.
struct Rva007EA970Source
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6();
    virtual char *fallback();
};

struct Rva007EA970Inner
{
    char m_pad0[12];
    Rva007EA970Source *m_source;
    char m_pad10[0xF1];
    char m_text[1];
};

struct Rva007EA970Owner
{
    int m_reserved;
    Rva007EA970Inner *m_inner;
    char *getText();
};

char *Rva007EA970Owner::getText()
{
    Rva007EA970Inner *inner = m_inner;
    char *local = inner->m_text;
    if (*local)
        return local;
    return inner->m_source ? inner->m_source->fallback() : 0;
}

// Retail 0x00657940 (30B), right after getText: the nested +0x228 word,
// falling back to virtual slot 8 on the same optional source.
struct Rva00657940Source
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual int fallback();
};

struct Rva00657940Inner
{
    char m_pad0[12];
    Rva00657940Source *m_source;
    char m_pad10[0x228 - 0x10];
    int m_value;
};

struct Rva00657940Owner
{
    int m_reserved;
    Rva00657940Inner *m_inner;
    int getValue();
};

int Rva00657940Owner::getValue()
{
    Rva00657940Inner *inner = m_inner;
    int value = inner->m_value;
    if (value)
        return value;
    return inner->m_source ? inner->m_source->fallback() : 0;
}
