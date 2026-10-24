// cl: /GX-

// Alpha default-module copy through its middle base, followed by four vptr stores.

class Rva003AEA42
{
public:
	Rva003AEA42(const Rva003AEA42 &other);
};

// Rva003AEA15_v0: matched references place it at VA 0xc1cdcc (retail .rdata value -9).
extern "C" char Rva003AEA15_v0 = -9;
// Rva003AEA15_v14: matched references place it at VA 0xc1c504 (retail .rdata value -41).
extern "C" char Rva003AEA15_v14 = -41;
// Rva003AEA15_v18: matched references place it at VA 0xc1c900 (retail .rdata value 45).
extern "C" char Rva003AEA15_v18 = 45;
// Rva003AEA15_v1c: matched references place it at VA 0xc1cdbc (retail .rdata value -83).
extern "C" char Rva003AEA15_v1c = -83;

namespace FXParticleSystem
{
template <int CATEGORY>
class __declspec(novtable) DefaultModule
{
public:
    __declspec(noinline) DefaultModule(const DefaultModule &that);
    virtual DefaultModule *clone() const;

private:
    char m_storage[0x9C];
};

// ??0?$DefaultModule@$00@FXParticleSystem@@QAE@ABV01@@Z
template <>
DefaultModule<1>::DefaultModule(const DefaultModule<1> &that)
{
	const void *src = &that;
	((Rva003AEA42 *)this)->Rva003AEA42::Rva003AEA42(*(const Rva003AEA42 *)src);
	*(void **)this = &Rva003AEA15_v0;
	*(void **)((char *)this + 0x14) = &Rva003AEA15_v14;
	*(void **)((char *)this + 0x18) = &Rva003AEA15_v18;
	*(void **)((char *)this + 0x1C) = &Rva003AEA15_v1c;
}
}
