# VP6 shared filter scratch, 2026-10-25

model=gpt-6 lane=R budget=30m. Source base 684d224e847addd2e91c10be4a202e405f95fbae.
Only committed clean-room specs, retail and this repo's independently recovered
code are consulted; no external decoder source or BFME1 decoder body is read.

Native FilterBlock2d at 001B8280 passes height11 and width8 to the rowed dword
first pass. Its second pass starts at DFDA78, exactly32 bytes into scratch
DFDA58. Both bilinear callers perform nine rows of eight dword writes into
that same scratch buffer. The complete maximum footprint is 11*8*4=352 bytes,
ending at DFDBB8 where an independently rowed debug frame counter begins.
The whole 352-byte retail span is initially zero. These target facts establish
the allocation and row-one relationship; they do not recover the original
C++ variable name or whether retail spelled a flat or row-major array.

The prior source defined two separate four-byte integers for the base and row
one. One int[88] now owns the whole proven span; row one is owner+8 elements.
The bilinear consumer uses the same complete array declaration. No algorithm,
call ABI, source path, header, pin, linker alias, hatch or verifier changes.
Native references and all five rowed bodies (821 bytes) pass the normal before
and final control; the final control also verifies the complete352-byte owner.
All six scratch DIR32 references retain their instruction sites and original
targets. The two83-byte MMX/SSE2 sibling bodies are unchanged controls; only
three affected generic/bilinear bodies (655 bytes) are recorded with add_match.

A direct scalar-to-array change exposed VC7.1's pointer-induction choice: the
array's biased -2..5 loop uses a pointer four bytes earlier with compensated
store displacements. It is semantically equal but does not reproduce retail.
Taking the array's address, an unknown-bound compatible declaration and
origins3/1/4 do not fix that shape. Origin0 does: the plain for column0..7
loop over the array base compiles to the exact native pointer bias and stores.
The redundant +=0 and a diagnostic local reference were removed; the clean
final source still passes5/5. No pragma, inline asm or volatile workaround.

The 7124e772c5 measured graph has a forward-map conflict at this scratch in
FilterBlock2dBil_8 and a closure witness from UtilMachineSpecificConfig through
FilterBlock_C. Full new linking credit is pending the next authoritative batch
comparison; no prospective gain, new function coverage or census update is
claimed by the source repair. Useful diagnostics remain under the ignored
build/vp6-filter-scratch-link-20261025 directory.
