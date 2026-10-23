AerialPathfinder math linking attempt, 2026-10-20

At BFME 2 44d0196f61, verified BFME 1 a2c8039e61 and published index
b73720bed9, the native 2148-byte reconstruction passes byte verification
(2130 non-padding bytes). Only float sin/cos emitted COMDATs prevent legacy
linking: these 17-byte CRT wrappers differ from rowed fsin/fcos at RVAs
0x2FBB0/0x2FBC0. All eight parent calls to double _sin/_cos are already inline;
float atan2 deliberately remains an out-of-line call at RVA 0x422CD.

Two careful trials were rejected. Redeclaring just float sin/cos as
imported forceinline after math.h fails MSVC C2375, different linkage.
Replacing math.h with its needed double prototypes and imported forceinline
float sin/cos wrappers compiles but changes the parent bytes, including probe
arithmetic. The latter trial is retained as trial.patch;
original source restored. It is not a byte-exact alternative.

A whole-header forceinline wrapper, used by other units, risks inlining the
required out-of-line atan2 call. Further work needs selective declaration and
inline control that retains float roundings, Coord3D length visibility and
atan2's original call. Flags /O1 /arch:SSE /G7 /MD /EHsc; no pins, ABI changes,
compiler flag changes or verifier changes were attempted.
