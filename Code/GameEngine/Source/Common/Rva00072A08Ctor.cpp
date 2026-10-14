// cl: /DNDEBUG /MD
//
// Retail 0x000729F4, 20 bytes: default constructor of the reference-counted
// rendering-method forwarder whose vtable 0x00BC6540 holds the matched
// Rva00072A08 slot bodies (VslotSmallBodiesC.cpp; slots #2-#6 and #9 forward
// to the object at +8). Ghidra-unlisted, no caller (the body sits between
// W3DShroudMaterialPassClass::UnInstall_Materials 0x000729EB and slot #2).
//
// Shape: RefCountClass base (NumRefs = 1 at +4, vptr at +0), then the +8
// forwarding target built by its holder's inline constructor. Modelling the
// target as a member object -- as FXShaderSetup's +8 shader-asset handle is
// (fxshadersetup.cpp, 0x001525FB has the same three-store prologue) -- keeps
// retail's +4, vptr, +8 store order; a plain pointer initializer is hoisted.

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

	int NumRefs;
};

class Rva00072A08Inner;

class Rva00072A08Target
{
public:
	Rva00072A08Target() : m_target(0) {}

private:
	Rva00072A08Inner *m_target;
};

class Rva00072A08 : public RefCountClass
{
public:
	Rva00072A08();

	virtual bool rva00072A08(int a0, int a1);

protected:
	virtual ~Rva00072A08();

private:
	Rva00072A08Target m_08;
};

Rva00072A08::Rva00072A08()
{
}
