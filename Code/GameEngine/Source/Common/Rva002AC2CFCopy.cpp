// cl: /O1 /DNDEBUG /MD
// Native 0x002AC2CF..0x002AC340 (113 B; RET 12). The rowed virtual-slot
// forwarder 0x002AC2C7 and bounded-copy caller 0x0059B49E bind this existing
// address-derived member name and its three stack arguments. Original class
// and method names are unknown. Retail supplies the +0 buffer, +4 length,
// +8 second-segment handle and eight-byte text header; the two-segment-copy
// interpretation is structural. No ownership or original string type inferred.
// The first copy returns immediately when no bytes remain. The old bank
// incorrectly continued to the second memcpy on that path.

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);

struct Rva002AC2CFStringView
{
    char *data;
    const char *str() const { return data ? data + 8 : ""; }
};

class Rva002AC2CFTarget
{
public:
    void rva002AC2CF(int dst, int off, int count);

private:
    char *m_buf;
    int m_len;
    Rva002AC2CFStringView *m_second;
};

void Rva002AC2CFTarget::rva002AC2CF(int dst, int off, int count)
{
    int len = m_len;
    Rva002AC2CFTarget *self = this;
    if (off < len)
    {
        int chunk = count;
        if (off + chunk > len)
            chunk = len - off;
        memcpy((void *)dst, self->m_buf + off, (unsigned int)chunk);
        count -= chunk;
        if (count <= 0)
            return;
        dst += chunk;
        off += chunk;
    }
    Rva002AC2CFStringView *next = self->m_second;
    off -= len;
    const char *base = next->str();
    memcpy((void *)dst, base + off, (unsigned int)count);
}
