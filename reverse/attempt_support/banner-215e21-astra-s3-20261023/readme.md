# Banner record constructor boundary, 2026-10-23

Inputs: BFME2 b47a7a94c9, pinned BFME1 138757e9b74645fbcbb7724a7af2764e34931e11,
ordinary MSVC7.1, BannerUI.cpp's existing /O1 /G7 /arch:SSE /MD /EHsc flags.
The donor is not a source identity proof for this target.

## Retraction

The prior 21-byte clearBannerRecord claim begins at 0x00215E26 inside the
straight-line 26-byte initialization body at 0x00215E21..0x00215E3B.
The preceding verified INIVictorySystem callback ends at 215E21; the next
body starts at 215E3B. The complete native body is:

    8bc1 8308ff 33c9 894804 894808 89480c 894810 894814 884818 c3

It takes the receiver in ECX, returns that pointer in EAX, initializes word0
to -1, words4/8/C/10/14 to zero, and byte18 to zero. The claimed tail
instead relies on an already prepared EAX receiver. The old C++ static
helper happens to emit that private-register tail; byte equality alone
never established an independent retail entry there.

All-section raw E8/E9 relative-encoding and absolute-VA scans find no
candidate references to either start (entry-evidence.json). This is limited
negative evidence, not proof against dynamically computed references. The
complete stores and ordinary constructor ABI support the constructor
interpretation; no original class name or source inheritance is established.
Ghidra/WB tooling has no function containing the start, so no WB naming
claim is made.

Retire the interior row in its own commit, as add_match's replacement policy
requires. Remove the helper and put the same initialization statements
directly in CreateBanner. Its body remains 383 bytes; the baseline source
gate verifies28/28 rows and two data rows, and the legacy published-index
link preview reports1880 linked bytes. This retraction corrects coverage;
it claims no new recovered or linked bytes.

## Reconstruction probe

A distinct address-derived constructor with the complete native fields emits
all26 exact bytes with no relocations. Instantiating that constructor in
CreateBanner retains an extra four-byte slot=-1 store, so that caller form is
not adopted. The direct-initialization caller and independent constructor
preserve the existing normal named bodies. Compiler-local EH labels move;
normal parent-EH verification must decide their placement.

The shared BfmePod28 constructor is separately owned at583AE2 (35 bytes,
HordeMeleeSwarmXfer.cpp) and has different semantics. It must not acquire
another constructor address. A distinct record view is required; its precise
original class identity is still unknown.


Retraction validation: normal focused build27/27 functions and2/2 data rows
pass. The compiler-label fallback verifies all11 renumbered funclets through
their parent EH graphs. No source flags, pins, globals, or gate rules change.
A second private probe uses an independent 28-byte record layout (no base
class) and preserves both the exact26-byte constructor and the entire383-byte
CreateBanner body. This is preferred over the initial storage-inheritance
probe because original inheritance is not established.
