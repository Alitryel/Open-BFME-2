// ??0StreakLineClass@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// readable body of ??0StreakLineClass@@QAE@XZ: Code/Libraries/Source/WWVegas/WW3D2/streak.cpp
//
// Retail 0x0091A730, 207 bytes. Named by the S4 ctor-then-publish caller as
// S4Made0091A730 (416-byte allocation). Identity is StreakLineClass: base
// RenderObjClass ctor at 0x009204B0, then SegLineRendererClass at +0x104 and
// StreakRendererClass at +0x154 -- the same offsets streak.cpp already uses.
//
// Retail EH map has null states 1 and 3 for Vector3/Vector4 array
// construction within the inlined vector constructors. Their real empty
// default constructors retain these states; treating either type as POD
// removes a state even though the zero-length vector emits no allocation.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// Array deallocation is nonthrowing; preserve the retail unwind lifetimes.
void operator delete[](void *) throw();

class RefCountClass
{
public:
	RefCountClass();
	virtual void Delete_This();
	virtual ~RefCountClass();
	int NumRefs;
};

class MultiListObjectClass
{
public:
	MultiListObjectClass();
	virtual ~MultiListObjectClass();
	void *ListNode;
};

// upstream layout: reference/shims/sweep/rendobj.h (BFME RenderObjClass is 0xC8)
class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RenderObjClass();
	virtual int Class_ID() const;
	virtual ~RenderObjClass();

protected:
	char m_tail[0xB8];
};

#include "simplevec.h"
// bfme link decl-only begin
template <> SimpleDynVecClass<float>::~SimpleDynVecClass();
template <> SimpleVecClass<float>::~SimpleVecClass();
template <> bool SimpleVecClass<float>::Resize(int);
// bfme link decl-only end

class Vector3
{
public:
 Vector3() {}
	float X, Y, Z;
};

class Vector4
{
public:
 Vector4() {}
	float X, Y, Z, W;
};

// upstream layout: Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h
class SegLineRendererClass
{
public:
	SegLineRendererClass();
	SegLineRendererClass(const SegLineRendererClass &);
	~SegLineRendererClass();

private:
	char m_storage[0x50];
};

// upstream layout: Code/Libraries/Source/WWVegas/WW3D2/StreakRendererCtor.cpp
class StreakRendererClass
{
public:
	StreakRendererClass();
	StreakRendererClass(const StreakRendererClass &);
	~StreakRendererClass();

private:
	char m_storage[0x4C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streak.h
// offsets: StreakLineClass_Get_Obj_Space_Bounding_Box.cpp
class StreakLineClass : public RenderObjClass
{
public:
	StreakLineClass();
	StreakLineClass(const StreakLineClass &);
	virtual RenderObjClass *Clone() const;

private:
	unsigned int MaxSubdivisionLevels;
	unsigned int *Personalities;
	float NormalizedScreenArea;
	SimpleDynVecClass<Vector3> PointLocations;
	SimpleDynVecClass<Vector4> PointColors;
	SimpleDynVecClass<float> PointWidths;
	SegLineRendererClass LineRenderer;
	StreakRendererClass StreakRenderer;
};

// ??0StreakLineClass@@QAE@XZ etc. are owned by streak.cpp; declared only here.

// Anchor keeps this unit's select-any ctor copies (and the vector bodies they
// reference) emitted; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeStreakLineCtorAnchor@@YAXXZ absent-from-retail
void _bfmeStreakLineCtorAnchor()
{
	StreakLineClass a;
	StreakLineClass b(a);
}
#pragma inline_depth()
