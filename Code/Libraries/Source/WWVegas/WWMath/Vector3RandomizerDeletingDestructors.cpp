// cl: /DNDEBUG /MD /EHsc
//
// Base scalar-deleting destructor pair for Vector3Randomizer.
// Retail folds all four concrete randomizers' ??_G here (Solid 0xCEFD00,
// Hollow 0xCEFD1C, Cylinder 0xCEFD38, Box 0xCEFCE4 all carry 0x7235D0 in
// slot 0); the body calls the base complete dtor at 0x723620 (which
// installs the 6-slot abstract-base table at 0xBD5E38) then the matched
// scalar operator delete at 0x2FD60. BFME1 lands the four derived pairs
// in Vector3RandomizerDeletingDestructors.cpp; BFME2 folds the deleting
// wrappers, so the base pair is claimed here. Human-readable model:
// the abstract base carries Class_ID, Get_Vector, Get_Maximum_Extent,
// Scale and Clone as pure virtuals behind a virtual destructor.

class Vector3;
class Vector3Randomizer
{
public:
	virtual ~Vector3Randomizer();
	virtual unsigned Class_ID(void) const = 0;
	virtual void Get_Vector(Vector3 &vector) = 0;
	virtual float Get_Maximum_Extent(void) = 0;
	virtual void Scale(float scale) = 0;
	virtual Vector3Randomizer *Clone(void) const = 0;
};

inline __declspec(noinline) Vector3Randomizer::~Vector3Randomizer() {}

Vector3Randomizer *g_randomizerAnchor;

// Anchor: emits the ??_G scalar-deleting-destructor COMDAT.
void deleteVector3Randomizer(Vector3Randomizer *vector3Randomizer)
{
	delete vector3Randomizer;
}

// ??1Vector3Randomizer is a header inline elsewhere: another unit emits a
// select-any copy of it, so a strong definition here was a duplicate symbol
// in the linked build. This anchor only makes this unit emit its copy for the
// ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitVector3RandomizerDeletingDestructors@@YAXPAVVector3Randomizer@@@Z present-unmatched
void bfmeEmitVector3RandomizerDeletingDestructors(Vector3Randomizer *vector3Randomizer)
{
	vector3Randomizer->Vector3Randomizer::~Vector3Randomizer();
}
#pragma inline_depth()
