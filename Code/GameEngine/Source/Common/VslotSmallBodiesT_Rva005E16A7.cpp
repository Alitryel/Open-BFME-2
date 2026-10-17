// cl: /DNDEBUG /MD
// Split from VslotSmallBodiesT.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch T. As in VslotSmallBodiesA-S, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// 0x0057BC25: tail call of the rowed 0x0057BAC4 on this object.
// Slot 8 of StrategicHUD::SelectionDetailsUIImpl's vftable 0x00C6F26C (its
// rowed ctor and dtor install it): virtual.
namespace StrategicHUD { class SelectionDetailsUIImpl; }
class StrategicHUD::SelectionDetailsUIImpl
{
public:
	void Close();
	virtual void rva0057BC25();
};


// 0x0058AD81 and 0x005EE2CF: the pinned Object command-button entry points
// for the argument, with the +0x08 button (and the +0x1C position).
class CommandButton;
struct Coord3D;
class Object
{
public:
	void doCommandButton(const CommandButton *button, Int a, bool b);
	void doCommandButtonAtPosition(const CommandButton *button, const Coord3D *pos, Int a, Int b);
};
struct Rva005EE2CFPos
{
	Real x;
	Real y;
	Real z;
};
class AISpecialPower
{
public:
	void activate(Object *obj);
private:
	Int m_00;
	Int m_04;
	const CommandButton *m_08;
};

class Rva005EE2CF
{
public:
	void rva005EE2CF(Object *obj);
private:
	Int m_00;
	Int m_04;
	const CommandButton *m_08;
	char m_pad0C[0x10];
	Rva005EE2CFPos m_1C;
};


// 0x00596BA2: the unsigned +0x38 count as a Real (the argument is unused).
class Rva00596BA2
{
public:
	Real rva00596BA2(Int unused) const;
private:
	char m_pad00[0x38];
	UnsignedInt m_38;
};


// 0x005C4212 and 0x005C4221: hand this object to virtual slot 3 (resp. 2)
// of the argument.
class Rva005C4212;
class Rva005C4212Visitor
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02(Rva005C4212 *o);
	virtual void v03(Rva005C4212 *o);
};
class Rva005C4212
{
public:
	void rva005C4212(Rva005C4212Visitor *v);
	void rva005C4221(Rva005C4212Visitor *v);
};



// 0x005DAA9E and 0x005DAC6D: copy the three words at +0x30 (resp. +0x2C)
// out, the first as a Real.
struct Rva005DAA9ETriple
{
	Real x;
	Int y;
	Int z;
};
class Rva005DAA9E
{
public:
	void rva005DAA9E(Rva005DAA9ETriple *out) const;
private:
	char m_pad00[0x30];
	Rva005DAA9ETriple m_30;
};

class Rva005DAC6D
{
public:
	void rva005DAC6D(Rva005DAA9ETriple *out) const;
private:
	char m_pad00[0x2C];
	Rva005DAA9ETriple m_2C;
};


// 0x005E16A7 and 0x005E2126: the pinned INI::initFromINI on this object with
// the field table at VA 0x00C779F0 (resp. 0x00C77A98).
struct FieldParse;
class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};
extern const FieldParse g_rva005E16A7FieldParse[];
extern const FieldParse g_rva005E2126FieldParse[];
class Rva005E16A7
{
public:
	void rva005E16A7(INI *ini);
	void rva005E2126(INI *ini);
};
void Rva005E16A7::rva005E16A7(INI *ini)
{
	ini->initFromINI(this, g_rva005E16A7FieldParse);
}
void Rva005E16A7::rva005E2126(INI *ini)
{
	ini->initFromINI(this, g_rva005E2126FieldParse);
}

// 0x005F84F7: clears entry i (8 bytes each) of the +0x20 vector through the
// rowed 0x002BED91 when i is in range.
class Rva002BED91
{
public:
	void clear();
private:
	Int m_00;
	Int m_04;
};
class Rva002BED91Vector
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	Rva002BED91 &operator[](UnsignedInt i) { return m_start[i]; }
private:
	Rva002BED91 *m_start;
	Rva002BED91 *m_finish;
};
class Rva005F84F7
{
public:
	void rva005F84F7(Int i);
private:
	char m_pad00[0x20];
	Rva002BED91Vector m_20;
};


// 0x00604A1E: creates the named directory (kernel32 CreateDirectoryW, no
// security attributes) unless the name is NULL or empty.
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryW(const unsigned short *path, void *security);
class Rva00604A1E
{
public:
	bool rva00604A1E(const unsigned short *path);
};


// 0x00740A96: the rowed 0x007401A3 setter on the +0x20 member with the first
// argument and the rowed 0x00740A60 lookup of the second.
template <class T> class StringBase;
Int Rva00740A60Get(const StringBase<char> &name);
class Rva007401A3
{
public:
	void rva007401A3(Int a, Int b);
};
class Rva00740A96
{
public:
	void rva00740A96(Int a, const StringBase<char> &name);
private:
	char m_pad00[0x20];
	Rva007401A3 m_20;
};

