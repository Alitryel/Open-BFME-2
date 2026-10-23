// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
// ?rva0033B217@Rva002CF1E2Node@@QAEXXZ @0x0033B217 315B: six GameText fetches into wide members, called per node by the
// rowed list walk 0x002CF1E2. fetch returns the UnicodeString by value (sret), so the EH state store lands after the call
// and the assignment takes the returned temporary: retail evidence is the call order and state stores. Member layout from
// retail offsets only; address-derived names.
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
    virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
    virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
    virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
    virtual void pad12(); virtual void pad13();
    virtual UnicodeString fetch(AsciiString *key, int unk);
};

extern GameTextInterface *TheGameText;

struct Rva002CF1E2Node
{
    char m_pad00[0x2c];
    AsciiString m_key2c;
    UnicodeString m_val30;
    AsciiString m_key34;
    UnicodeString m_val38;
    AsciiString m_key3c;
    UnicodeString m_val40;
    AsciiString m_key44;
    UnicodeString m_val48;
    AsciiString m_key4c;
    UnicodeString m_val50;
    AsciiString m_key54;
    UnicodeString m_val58;
    void rva0033B217();
};

void Rva002CF1E2Node::rva0033B217()
{
    {
        m_val30 = TheGameText->fetch(&m_key2c, 0);
    }
    {
        m_val38 = TheGameText->fetch(&m_key34, 0);
    }
    {
        m_val50 = TheGameText->fetch(&m_key4c, 0);
    }
    {
        m_val48 = TheGameText->fetch(&m_key44, 0);
    }
    {
        m_val58 = TheGameText->fetch(&m_key54, 0);
    }
    {
        m_val40 = TheGameText->fetch(&m_key3c, 0);
    }
}
