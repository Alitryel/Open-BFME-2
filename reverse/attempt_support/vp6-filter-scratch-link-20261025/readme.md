# VP6 shared filter scratch, 2026-10-25

model=gpt-6 lane=R budget=30m. Source base 684d224e847addd2e91c10be4a202e405f95fbae.
Only committed clean-room specs, retail and this repo's independently recovered
code are consulted; no external decoder source or BFME1 decoder body is read.

Native FilterBlock2d at 001B8280 passes height 11 and width 8 to the rowed dword
first pass. Its second pass starts at DFDA78, exactly 32 bytes into scratch
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
and final control; the final control also verifies the complete 352-byte owner.
All six scratch DIR32 references retain their instruction sites and original
targets. The two 83-byte MMX/SSE2 sibling bodies are unchanged controls; only
three affected generic/bilinear bodies (655 bytes) are recorded with add_match.

A direct scalar-to-array change exposed VC7.1's pointer-induction choice: the
array's biased -2..5 loop uses a pointer four bytes earlier with compensated
store displacements. It is semantically equal but does not reproduce retail.
Taking the array's address, an unknown-bound compatible declaration and
origins 3/1/4 do not fix that shape. Origin 0 does: the plain for columns 0 through 7
loop over the array base compiles to the exact native pointer bias and stores.
The redundant +=0 and a diagnostic local reference were removed; the clean
final source still passes 5/5. No pragma, inline asm or volatile workaround.

The 7124e772c5 measured graph has a forward-map conflict at this scratch in
FilterBlock2dBil_8 and a closure witness from UtilMachineSpecificConfig through
FilterBlock_C. The source commit made no prospective credit claim; the completed
fixed comparison is recorded below. No new function coverage or current-master
census update is claimed. Useful diagnostics remain under the ignored
build/vp6-filter-scratch-link-20261025 directory.

The authoritative full link-cycle process exits zero after 2992 seconds.
Its unique placed closed-strict credit changes from 1,700,931 to 1,703,678 bytes,
a gain of 2,747 in 5 rows with zero losses.
All three affected functions are placed and closed-strict. The full 352-byte
scratch datum passes. Exactly two of 23,460 canonical objects change;
all 23,458 others agree. Zero final drift and zero new unresolved
references are recorded, with no missing objects, failed compile or stale warm
start. This is a fixed-comparison result, not a new current-master census.
Independent closure reproduction and the actual remaining witnesses are retained
separately. Source work is t=14 minutes for the shared three-body repair; full
measurement time is recorded independently in actual-process-exit.json.

The five gaining rows are FilterBlock2dBil (295 bytes), FilterBlock_C (993),
FilterBlock2dBil_8 (295), FilterBlockBil_8_C (766) and VP6_printmodes (398).
beneficiary-closure.json preserves every previously failing reachable node and
checks that none remains in each gaining row's closure. The debug body and its
object are unchanged; its old frame-counter forward-map conflict disappears.
FilterBlock2d's existing 65-byte credit is retained, not counted as a new gain.

The independent graph report reproduces the full 1,703,678-byte credit and all
98,202 status rows, with 25 roots additionally checked by forced closure.
Its receipt, graph and tool digests are retained in
independent-closure-verification.json. Both comparison snapshots keep the same
32774ab03393709a7f14331ba8d98d281a55ffd9 reference; the normal publication gate
also passes 5/5 bodies and the data owner at the rebased production reference
listed in publication-gate-exit.json. Source blobs agree with the measured input.

The earlier process has no fabricated exit code: interrupted-process.json records
its old boot identity and the confirmed new boot before restarting the same
immutable input. Completed cache objects were reused. The process timing above
belongs only to the completed resumed run; source work remains t=14 minutes.

The three configuration roots now reach the unresolved selected import twin
__except_handler3 through GetProcessorFlags and CpuProbe_VendorSse2, as retained
in remaining-witnesses.json. Their former scratch witness is cleared. The whole
game's no-FORCE/no-stubs/runtime exit test remains open; final_link still records
five forced duplicate symbols (ten diagnostics). No runtime pass is claimed.
