# Allocation engine 0x00033ED0: complete C++ recovery

Native extent 0x00033ED0..0x00034496, 1478 bytes, includes the live footer
store after the old 1466-byte boundary and RET8 at 0x00034493. The existing
address-derived name is retained. Calls from the 204-byte calloc body at
34A60 independently establish the size/flags/result relationship. Retail
establishes each field offset, list orientation, branch and call destination;
semantic chunk/bin names remain structural interpretations. The earlier
bank attributes its control-flow guide to dlmalloc 2.7 mALLOc. No original
EA source identity is claimed from that similarity or from equal bytes.

Inputs: BFME2 9e42834dd0a, verified committed BFME1
0dc8a26a9c6041c73dc564754cd059dc54faa72a, stock MSVC 7.1 13.10.3077.
The entire calloc unit and all prior same-RVA log entries were read. The
October19 audit records the earlier semantic corrections; the newer r44
bank incorporated them and reduced the body to eleven differing instruction
lines. No applicable EA allocator donor was found by the prior reference
pass. BFME1's MemoryPool implementation has a different allocator design.

## Independent remaining causes

The bank's ordinary int lock counter disagreed with the existing contract
in MemoryPoolInit.cpp and System/memory_pool.cpp: a 0x18-byte critical section
followed by a volatile int usage count. Applying that same declaration
removes all ten register differences in unlock/callback/relock, retaining
every native memory access and call. This is the established sibling view;
bytes alone do not establish the original source's volatile spelling.

Only the displacement at 34204 then differed: native JE34268 versus
compiled JE34274. Native34268 reads/tests the saved result;34274 checks the
growth callback. Flattening the nested fallback guards into
`if (m_46d && nb >= mmap_threshold && n_mmaps < n_mmaps_max)` followed by
`if (m_46d)` reproduces the whole native body. The second check still
observes the option after a failed mapped-allocation call. It also permits
the compiler's common result-check path. No added calls, dummy accesses,
assembly, flag changes or pins are required.

Controls: equivalent for/while/do/goto forms, separate break predicates,
struct/array result storage, typed/integer results, mapped-result assignment
forms, a forced-inline fallback helper and G6/Ob1 settings leave the last
jump unchanged. A shared success exit and a separate inline allocation
operation alter the frame/body. Volatile result storage and full compiler
barriers also disturb code generation; they are not retained. One helper
trial initially returned a value from void and was corrected before use.
The final change keeps ordinary result storage and the existing lock contract.

## Integration

The malloc body and complete offset view are integrated into the existing
Rva00034A60Calloc.cpp unit, preserving its empty GeneralAllocator base and
calloc body. No shared header or competing new translation unit is added.
Normal add_match verifies both rows, 1478+204 bytes, and both named imports;
the old partial bank is retired. find_declared_unmatched reports no undeclared
bodies. The published-index link preview reports this complete unit LINKS,
0 ->1682 bytes, at census ca836f7270 (2026-10-20 08:25). This is a preview,
not a new census or runtime claim. All allocator calls now resolve to rowed
32DF0,334A0,33930 providers. The whole-unit placement scan is retained in the
local replay directory.

Replay: build/next-batch-oct20a contains the unchanged bank, each isolated
source and explain_mismatch result, trial generators, integrated proof and
link/placement output. The final source is the resumable exact artifact.
Model: gpt-6.1-sol.
