// cl: /DNDEBUG /MD
//
// ?rva004AC135@RainOfFireUpdate@@UAEXM@Z, retail 0x004AC135, 19 bytes: slot 1
// of the vtable 0x00C54BA0 that RainOfFireUpdate's ctors (0x004AC0E3,
// 0x004AC272) install at +0x20, beside the rowed slot 0 setter of the same
// float; adds the argument to the float at +0x2C. Compiled with the +0x20
// subobject this. Names by address.
#include "RainOfFireUpdateView.h"

void RainOfFireUpdate::rva004AC135(float delta)
{
	scale += delta;
}
