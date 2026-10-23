// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Retail4149D..41589 initializes eighteen scalar fields of the 0x48-byte
// microphone record used by the AudioSettings constructor41589. Target stores
// establish offsets and constant; semantic purpose follows existing manager
// views and WorldBuilder microphoneSettings evidence. Original constructor
// class spelling remains uncertain, so preserve neutral name.
// Existing data-ledger global carries signaling-NaN bits0x7FA00000. Read
// its actual storage through volatile floats to preserve eighteen separate
// native loads and avoid any numeric conversion of the NaN payload.
// stlport
#define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION
#include <limits>
// Use the existing STLport special-value owner; native proves the4B7FA00000
// representation. The historical application spelling remains unproven.
class Rva0004149D {float values[18];public:Rva0004149D();};
Rva0004149D::Rva0004149D() {
 const volatile float &initial = _STL::_LimG<bool>::_F_qNaN.val;
 values[0]=initial;
 values[1]=initial;
 values[2]=initial;
 values[3]=initial;
 values[4]=initial;
 values[5]=initial;
 values[6]=initial;
 values[7]=initial;
 values[8]=initial;
 values[9]=initial;
 values[10]=initial;
 values[11]=initial;
 values[12]=initial;
 values[13]=initial;
 values[14]=initial;
 values[15]=initial;
 values[16]=initial;
 values[17]=initial;
}
