// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Retail4149D..41589 initializes eighteen scalar fields of the 0x48-byte
// microphone record used by the AudioSettings constructor41589. Target stores
// establish offsets and constant; semantic purpose follows existing manager
// views and WorldBuilder microphoneSettings evidence. Original constructor
// class spelling remains uncertain, so preserve neutral name.
// Existing data-ledger global carries signaling-NaN bits0x7FA00000. Read
// its actual storage through volatile floats to preserve eighteen separate
// native loads and avoid any numeric conversion of the NaN payload.
// Descriptive bit-storage name; the original global spelling is unknown.
// Native readonly7BDA2C is the complete4B signaling-NaN payload7FA00000.
// Store the representation as integer bits so no initializer can quiet it.
extern const unsigned int AudioMicrophoneUnsetBits = 0x7fa00000u;
class Rva0004149D {float values[18];public:Rva0004149D();};
Rva0004149D::Rva0004149D() {
 const volatile float &initial = *reinterpret_cast<const volatile float *>(&AudioMicrophoneUnsetBits);
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
