# Allocator growth 0x000334A0: ordered marker writes

Recovered the complete 604-byte body, `0x000334A0..0x000336FC`, ending in
RET4 at 336F9. Caller 34244 passes a size, consumes the returned chunk header
and adds eight for user data. The VirtualAlloc import and the existing 32B00
provider resolve through the normal byte/import gates. Field offsets and native
operations are target evidence; the inherited chunk/core semantic names remain
structural views, not recovered original declarations.

Inputs: BFME2 906b7f215326a0c732c80987d12500fbeab19975; pinned BFME1
a2c8039e61ad4dfb20c095d8eafe048248d31f25; stock MSVC 7.1 13.10.3077,
the existing allocator unit's region defaults. All same-RVA verdicts and both
linked earlier handoffs were read before the retry. The newer bank's inline
double-fencepost helper already fixed the previous initialization schedule.

## Exact mismatch and successful control

The unchanged bank emits 604 bytes with every call resolved. At native +126,
retail loads EDX=8, writes marker words +4 and +8, then writes immediate 9 at
+0C. The bank hoists that last write ahead of loading EDX. Every instruction
outside this four-line scheduling region is already exact.

Writing exactly the three existing marker lvalues through volatile unsigned
int lvalues gives the complete native body. Making only the final write, only
the first two writes, or either first write volatile leaves the same mismatch.
Making the preceding prior-size write volatile as well also matches, but is
unnecessary and was not retained. No reads, dummy uses or runtime operations
were added. The observed compiler response is established; it does not prove
that the original code declared these fields volatile or why its author chose
the original spelling.

Other controls do not close the mismatch: typed header setters, reference/value
helper arguments, aggregate header initialization, returning the initialized
chunk, and narrower temporary lifetimes. Aggregate copies can change the body
extent and register allocation. A full _ReadWriteBarrier at the tail restores
the marker sequence but moves unrelated core/header stores; barriers at earlier
initialization points introduce further differences. One exploratory pointer
advance variant omitted the prior-size store and was rejected as invalid;
it is not evidence about equivalent source forms.

## Integration and verification

Integrated into `Rva00031010Insert.cpp`, rather than adding another private
GeneralAllocator view. Existing node padding becomes the target-proven two
header words; the existing CoreBlock and allocator fields retain their offsets.
All three complete bodies independently match: 31010 (66 B), 332D0 (464 B),
334A0 (604 B). `add_match` verifies the complete unit, retires the bank, and
records landed. No pins, headers, compiler flags or gate baselines were changed.

The larger attempted allocator engine 33ED0 explicitly names this function as
a prerequisite. Its own source/register mismatches remain a separate recovery.

Local replay and detailed diagnostics: `build/fencepost-20261019/` contains
the unchanged baseline, baseline.log, trials.py, semantic_trials.py,
order_trials.py, lifetime_trials.py and their result tables. The compact
ordered-write results are committed beside this note. The focused recipe in
`docs/recipes.md` indexes this observation by assembly symptom.
