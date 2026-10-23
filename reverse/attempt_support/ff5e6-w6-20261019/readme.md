# Result

Semantic partial for `?rva000FF5E6@Rva0007E90ECallee@@QAEXH@Z`, RVA `0x000FF5E6`, size 788. Replace the previous bank under the assignment's semantic-correction exception. This is not a strict alignment improvement: the original and replacement both emit 788 bytes and have 18 differing bytes after relocation patching. `align_diff.py` reports structural/memory/register counts of 2/14/3 before and 2/13/4 after. The memory gain trades against one register-class difference. No source was added to `Code/`, no ledger row or pin was changed, and no exact match is claimed.

The previous bank sends midpoint then shifted midpoint to `rva000FE207`, but reverses those same values for `WaterTracksObj::init`. Retail sends midpoint then shifted midpoint to both. The replacement fixes that order and replaces the const hash-pair storage view with a mutable owner-pointer and integer-index cursor. The existing `_rva0007E394CursorEqual` provider supplies the independently verified two-dword comparison; no new symbol alias or pin is added. The two address-escaping endpoints share a local aggregate, which is a compiler-shaping choice rather than a claim about the original source. Every existing comment line is retained. Applicable Zero Hour comments beside duplicate detection and flip toggling are copied into the replacement.

# Identity and ABI evidence

The Ghidra inventory names a 788-byte start at `0xFF5E6`. Native bytes show the preceding body returning at `0xFF5E5`, this body's EH prologue at `0xFF5E6`, its `RET 4` at `0xFF8F7`, and the following body's prologue at `0xFF8FA`. ECX is the object pointer; the stack dword is used as an AsciiString reference and copied to object offset `0x28`. `Rva0007E90EBodies.cpp` and `W3DWaterTracksTestUpdate.cpp` are independent callers; the latter passes the water system's filename member. Keep the assigned address-derived symbol. The reviewed BFME 1 and Zero Hour loadTracks bodies support the water-loading behavior, but they do not establish a more specific target method name.

Retail reads the collection at map offset `0x124`, eight-byte records from `0x14..0x18`, record pointers at entry offset 4, and point vectors at record offsets `0x38..0x3C`. The cursor contains the collection pointer followed by its integer ordinal. The raw callee probe verifies equality `0x7E394`, reset `0xFE188`, find `0xFE207`, record getters `0x30C94A`, `0x30C91A`, `0x30C890`, `0x30C896`, filename-address getter `0xB28F2`, and the asset-merge forward `0x61F010`. The final relocation-patched comparison resolves every callee. The existing initializer row and retail argument pushes establish its two-float, two-vector-reference, filename, time-offset and optional-settings arguments. Field and cursor names beyond those facts remain structural views.

The endpoint-order assertions in `build/ff5e6-w6/identity.log` read the generated argument pushes directly: the original bank reverses its two endpoint addresses between calls; the replacement and retail each preserve their order. This is one static probe per body, not a runtime game test.

# Remaining mismatch

The owner store `mov [ebp-0x4c],edi` still executes at the start of the loop body instead of retail's preheader after the initial equality test. Endpoint aggregate homes are `midpoint=-0x6c`, `shifted=-0x64`, and midpoint-X spill `-0x5c`; retail uses `midpoint=-0x64`, `shifted=-0x5c`, and midpoint-X spill `-0x6c`. The perpendicular home is now retail's `-0x54`. These scheduling and stack-home differences account for the retained mismatch. `explain_mismatch.py` first differs at `+0x80`; its full raw output is `build/ff5e6-w6/explain-final.log`.

# Hypotheses tested

Before each trial, check `build/STOP_WORKER`; every probe used `BFME_OBJSTORE=off` and a fresh object. The preregistered hypotheses, evidence and refutations are in `build/ff5e6-w6/hypotheses.md`. All trial sources and raw outputs remain under that folder.

| Probe | Emitted bytes | Structural | Memory | Register | Patched differing bytes | Finding |
|---|---:|---:|---:|---:|---:|---|
| before | 788 | 2 | 14 | 3 | 18 | Original bank, reversed initializer endpoints. |
| correct-endpoints | 788 | 2 | 16 | 4 | 21 | Required endpoint correction; homes change. |
| geometry-aggregate | 785 | 8 | 47 | 27 | 513 | Three-vector aggregate changes frame and SSE dataflow. |
| endpoint-aggregate | 788 | 2 | 13 | 4 | 18 | Comparable alignment, endpoint order corrected. |
| mutable-cursor | 788 | 2 | 16 | 4 | 21 | Legal mutable pair storage alone does not move owner store. |
| condition-cursor | 788 | 2 | 17 | 4 | 544 | Named end assignment moves owner store into latch. |
| aggregate-midpoint-copy | 790 | 7 | 42 | 26 | 441 | Copy then += changes frame and SSE dataflow. |
| explicit-latch | 788 | 4 | 19 | 4 | 53 | Owner store reaches preheader; initialization and increment scheduling drift. |
| explicit-order | 788 | 2 | 20 | 4 | 28 | Reordering independent initialization/latch operations leaves scheduling drift. |
| typed-cursor / final | 788 | 2 | 13 | 4 | 18 | Plain pointer/index view preserves the best semantic repair. |

`align_diff.py` counts six unpatched absolute-address relocations in the memory column for these bodies. The table retains the tool's raw counts without subtracting them. Branch and relocation columns are not defects. Positional counts are diagnostic only and did not determine a strict closeness claim.

# Inputs and verification

BFME 2 input HEAD: `1d7d3716bc22594f17dca9ec14b3d2ccd4a337c9`. Reviewed BFME 1 checkout: `a18d9ed50607e9175de4d6568798d7d73119de09`. The bank retains its first `// cl:` settings: MSVC 7.1 with `/O1 /arch:SSE /G7 /MD /EHsc`, the BFME 2 ASCII shim, and the current donor WWMath/WWLib include directories. No compiler or shared-header change was made. Start clock: `2026-10-19 08:17:10 UTC`; record and completion receipts under `build/ff5e6-w6/` contain the measured elapsed time. Model: `gpt-6.1-sol`.

Raw measurements: `build/ff5e6-w6/before-align.log`, `before-disassembly.log`, `final-align.log`, and `final-disassembly.log`. Every other table row has matching `<probe>-align.log`, `<probe>-disassembly.log` and invocation receipts. `identity.log` contains the native boundary/callee disassembly and endpoint assertions. `record.log`, `check-csv.log`, `pin-consistency.log` and `post-record.log` contain the final bank/check outputs. `explain-final.log` confirms a mismatch, so `add_match.py` and the exact-landing build were not invoked.

Final checks pass: `check_csv.py`, `pin_consistency.py --check`, the static endpoint-order assertions, and preservation of every previous comment and the first compiler-flags line. The recorded bank contains the final candidate exactly after the tool-generated two-line header. The source remains unlanded, so `find_declared_unmatched.py` and `build.sh` are not applicable landing checks for this partial. No background process was started. All changes are uncommitted.
