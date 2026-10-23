// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?rva00330E4C@@YAMM@Z, retail 0x00330E4C (17B).
// Target evidence: a raw float helper returning through ST0 the product of
// the one-frame-in-seconds global (VA 0x00DBA508, 1/30, the ledger's
// opacityLogicStepSeconds), the degrees-to-radians literal (0.017453292f)
// and the stack argument, in that order -- the shape of Zero Hour's
// ConvertAngularVelocityInDegreesPerSecToRadsPerFrame (GameCommon.h) over
// BFME2's 1/30-second global. Twin skeleton of 0x003389BD
// (INI_parseAngularVelocityReal.cpp), which uses the 0.2 global. The
// original helper name is unknown; the RadiusDecal update (0x00330F98)
// nearby reads the same two values.
typedef float Real;

#define PI 3.14159265359f

extern float opacityLogicStepSeconds;

Real rva00330E4C(Real value)
{
	const Real RADS_PER_DEGREE = PI / 180.0f;
	return value * (opacityLogicStepSeconds * RADS_PER_DEGREE);
}
