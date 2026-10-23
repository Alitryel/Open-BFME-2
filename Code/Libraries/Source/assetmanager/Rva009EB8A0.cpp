// cl: /MD
// Retail009EB8A0..009EB8C4: table VA01145744 slot11 (+2C),
// installed by the matched base constructor009EB7D0. Derived prototype
// tables also share this slot. The original method identity is unknown.
// Global pointer VA0134FAAC is the existing Q1 registry receiver.
// The one stacked argument is this object: the callee is the rowed
// AssetManagerImpl::LoadAsset at 0x00623600 (Rva00622290CollectKeys.cpp),
// which keeps incoming ECX as the registry.
class Rva009EF0D0Element;
class Q1Receiver0134FAAC;
class AssetManagerImpl {
public:
    void LoadAsset(Rva009EF0D0Element *);
};
extern class Q1Receiver0134FAAC *TheQ1Receiver;
class Rva009EB8A0 {
public:
    void method();
private:
    char prefix[4];
    unsigned int word0004;
};
void Rva009EB8A0::method()
{
    if ((word0004 & 0xff0000) != 0x30000 && TheQ1Receiver)
        ((AssetManagerImpl *)TheQ1Receiver)->LoadAsset(reinterpret_cast<Rva009EF0D0Element *>(this));
}
