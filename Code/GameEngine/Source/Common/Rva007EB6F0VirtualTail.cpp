// Native658680 is a16B tail forwarder. Thread552027 passes callback and context
// at55209A..5520AA; the virtual slot3 target consumes those same stack words.
// Correct the previously incomplete no-argument view; original API/type names remain unknown.
// Open-BFME: virtual tail-call chain reconstructed from retail RVA 0x007EB6F0.

class Rva007EB6F0Object
{
public:
    virtual Rva007EB6F0Object *unused0(void);
    virtual Rva007EB6F0Object *advance(void);
    virtual void unused2(void);
    virtual void tail(void *callback, int context);

    void invoke(void *callback, int context);

private:
    char m_pad0[0x6A4];
    Rva007EB6F0Object *m_next;
};

void Rva007EB6F0Object::invoke(void *callback, int context)
{
    Rva007EB6F0Object *result = advance();
    result->m_next->tail(callback, context);
}
