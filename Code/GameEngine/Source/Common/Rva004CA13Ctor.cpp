// cl: /MD
// ??0W3DThingFactory@@QAE@XZ @0x0004CA01 18B: chain ctor calls base 0x002D0E14 then stores vtable 0x00BC4858. Evidence: caller 0x00041DB8 Win32GameEngine factory after new 0x28; dtor 0x0004CA13 same vtable tail-jmps to 0x002D0588; base row Rva002D0E14.
class Rva002D0E14
{
public:
	Rva002D0E14();
	virtual ~Rva002D0E14();
};

class W3DThingFactory : public Rva002D0E14
{
public:
	W3DThingFactory();
	virtual ~W3DThingFactory();
};

W3DThingFactory::W3DThingFactory()
{
}
