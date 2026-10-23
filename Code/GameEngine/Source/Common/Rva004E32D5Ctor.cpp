// cl: /MD
// ??0Rva004E32F2@@QAE@XZ @ 0x004E32D5 (29B). Default ctor: zero +4, bool +8=0,
// BfmeVNITree at +0x0C via pin 0x005011C1, vtable 0x00861F68. Same class as
// copy ctor 0x0052D477 (int+byte+tree) and dtor 0x004E32F2. Caller 0x004E331C.
// Tree spelled BfmeVNITree to call the pin; copy ctor proves map-tree layout.
class BfmeVNITree
{
public:
    BfmeVNITree();
private:
    int m_pad[3];
};

class Rva004E32F2
{
public:
    Rva004E32F2();
    virtual ~Rva004E32F2();
private:
    int m_04;
    bool m_08;
    BfmeVNITree m_0C;
};

Rva004E32F2::Rva004E32F2() : m_04(0), m_08(false)
{
}

// The retail call in this body reads 0x005011C1, an address the ledger already
// carries as ??0?$map@HUBfmePod24@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHUBfmePod24@@@_STL@@@3@@_STL@@QAE@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??0BfmeVNITree@@QAE@XZ=??0?$map@HUBfmePod24@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHUBfmePod24@@@_STL@@@3@@_STL@@QAE@XZ")
