// Native658690 is a16B tail forwarder. Thread552027 passes the callback
// at5521E3..5521ED; the virtual slot4 target consumes those same stack words.
// Correct the previously incomplete no-argument view; original API/type names remain unknown.
// Open-BFME: virtual tail-call chain reconstructed from retail RVA 0x007EB700.

class Rva007EB700Object
{
public:
    virtual Rva007EB700Object *unused0(void);
    virtual Rva007EB700Object *advance(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void tail(void *callback);

    void invoke(void *callback);

private:
    char m_pad0[0x6A4];
    Rva007EB700Object *m_next;
};

void Rva007EB700Object::invoke(void *callback)
{
    Rva007EB700Object *result = advance();
    result->m_next->tail(callback);
}
