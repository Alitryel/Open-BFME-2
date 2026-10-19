# Refresh: complete body, eight start-cursor operands remaining

The strongest bank remains real C++ for retail 0x006227E0..0x0062348C,
3244 bytes, frame 0xBC, full EH graph EXACT. It now uses the corrected
unsigned-key / pointer-payload record and the actual rowed insertion and
pair-copy bindings. Every call resolves through the real ledger; no diagnostic
address substitutions remain in remaining.json. The unnecessary const_cast
on the non-const second member was removed without changing compiled bytes.

The only differences are eight displacement bytes at parent offsets
BA3, BAE, BB9, BC1, C0D, C15, C20 and C2D. Both count branches add the
same deque contributions, but the compiler schedules their start-cursor
terms s2,s1,s0 while native schedules s2,s0,s1. The shared node terms and
deque1 finish term, both branch sizes, the complete preceding control flow
and every opcode/register selection are otherwise exact. 3236/3244 fixed
bytes agree. No matched parent row or new C++ byte coverage is claimed.

Target facts: existing pin and five matched callers identify the registry
member relationship; native unsigned pending-key comparisons, key/payload
stores and out-of-line destructor call establish the concrete prerequisite.
The original class/record names and donor-derived layout labels remain
inferences. See the separate asset-refresh-tree-20261019 and
asset-refresh-insert-20261019 evidence for the exact lifetime and insertion
providers. Those repairs are independently committed, not fabricated callee
bindings. BFME1's bank at 009EFF50 was reviewed and has its own unresolved
queue-sum scheduling problem; it is not an exact donor solution.

Fresh hypotheses tested in this pass:

- Canonical pending-record type and corrected lifetime/insertion identities:
  preserve the complete strongest body and remove the callee prerequisites.
- Authentic compiler profiles: default and DDK4035 emit identical3244B with
  eight operands; G7 emits3184B, SP1 emits3228B; caller EHs emits3255B.
- Natural declaration scopes: pass at function start, pass before the queue
  loop, and all loop variables at function start retain the eight operands.
  Reusing the queue variable emits3258B and changes EH.
- Actual pointer-element deques emit3258B and lose the shared finish-term
  schedule. A direct pointer pending payload preserves the eight operands
  but creates a different unresolved destructor instantiation; it is not used.
- Aggregate, direct-constructor and temporary pending-pair construction each
  emit3258B, changing only the tail schedule rather than improving it.
- Plain second-member assignment and const count view preserve exact parity.
- Iterator-distance counts emit3790B; an inline per-queue count accessor
  emits3268B; a combined active-count accessor changes inlining and emits2656B.

Earlier workers already exhausted 36 sum-order/grouping variants and 64
queue-reference combinations. Do not repeat those unchanged grids. No new
volatile barrier, pragma, assembly, dead local or synthetic evaluation order
was added. Fresh viable code-generation hypotheses are exhausted for this
pass; retain the strongest body and continue independent work.

remaining-tail.txt preserves the shared prefix and both final branches.
trials.json records the bounded profile/scope/type/construction/accessor
results. The scope trials overlapped an upstream rebase and temporarily lost
the destructor binding: their extra four bytes at C84..C87 are that transient
unresolved call, not a second source mismatch. remaining.json is the final
proof with actual bindings. source-trials.patch contains independent diffs
against the bank from its first #include onward; each section starts from
that same baseline. They use zero context (git apply --unidiff-zero). The bank preserves the complete best body; no failed
variant is placed under Code/.

Inputs: BFME2 dec23cfb78; pinned BFME1
cf0a80c228583af789772b794ab27abcab2debbf; unchanged STLport4.5.3 and native
MSVC /O2 /G6 /arch:SSE /EHsc, bfmealloc/sweep includes. The source/object
hashes in remaining.json refer to the diagnostic source before comment-only
bank header cleanup; bank_body_sha256 covers its identical #include/body
portion. No external decoder or unsupported reference source was read.
About twenty minutes of parent trials; model gpt-6.1-sol.
