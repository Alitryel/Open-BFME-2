# GUI comparisons and tab arithmetic: pure C++ family repairs

BFME2 base2c7d0eefe5; pinned BFME1 reference32774ab03393709a7f14331ba8d98d281a55ffd9.
These replace existing inline assembly with real C++ without changing their
native bodies. The old enclosing .cpp files already count as C++ in progress.py;
these are assembly-debt repairs, not additional unique coverage bytes.

## Text-entry selection, RVA00444016,25 bytes

The original class, userdata layout and /Ob0 flag remain unchanged. The two
unsigned-word fields at+1C/+1E are compared after the same winGetUserData call.
The pure boolean identity `(user->at1E != user->at1C) && true` restores the
native DX comparison register and ECX boolean register under stock VC7.1.
Direct comparison chooses the opposite register web; merely introducing a
boolean/int temporary does not close it. No volatile, register constraint,
input bound, extra memory, ABI adapter or changed flag is used.

The complete inline-assembly block is removed. The whole25-byte function and
sole real relocation match with no masks or unresolved calls, independently
repeated using the production command and a separate scratch object. This is
instruction and ABI proof, not a claim that the original source used &&true.
Normal add_match and the full source's checks are required before committing.

Normal production add_match passes the sole row and all references, and the
whole-file declared-definition check passes. The published index a9f880ad06
does not include this source, so ordinary link_check cannot preview it; no
published linked-byte gain or final runtime result is claimed.

