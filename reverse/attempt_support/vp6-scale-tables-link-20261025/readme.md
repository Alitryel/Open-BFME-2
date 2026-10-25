# VP6 scaler coefficient ownership, 2026-10-25

model=gpt-6 lane=R budget=30m. Production base d0c913e6dde06ee8ff4e7cdfa655c4aa0a2889f5.
The six committed clean-room specifications and retail bytes are the only decoder
sources of evidence; no external decoder source or BFME1 decoder donor is read.

The completed authoritative a7637e3b221cc7af51ce45eb036048a8d46c3f57 snapshot
leaves all six MMX scalers self-failing on data-back mappings. Each horizontal
scaler has a private rounding array; both last-band files and both routines in
VerticalBandInterpMmx.cpp have private five-array copies. Retail's 64 named DIR32
references independently identify one address for each of the five coefficients:
RVA 7D9910/20/30/40/50, holding four unsigned 16-bit lanes of 51/102/154/205/128.
The full logical allocation is eight bytes each. The following eight zero bytes
are native alignment padding, excluded from the ownership rows and arrays.

The existing VerticalBandInterpMmx.cpp now owns five external C-linkage arrays,
using names already present in the ledger. Four other units declare and use
those owners; the second routine in the owner no longer has another private
copy. No instruction, calling convention, arithmetic, loop, function identity,
source path, header, pin, alias, hatch or verifier changes. The repair reconciles
native data identity rather than asserting the original C++ source spelling.

Before and after normal controls pass 6/6 bodies, 1,739 bytes in five sources.
The after control also verifies five eight-byte data rows. Native proof confirms
all 64 references keep the same instruction offsets, addends and retail targets;
private definition counts 4/4/4/4/6 become exactly one external definition each.
Control and repair process exits are both zero. This adds zero matched function
coverage. The source result is recorded once per body with add_match.

The completed controlled comparison below holds a7637e3b22 constant except for
these five sources and five data rows. No current census headline change is
claimed. All five original source blobs equal the baseline snapshot; all five
repaired blobs equal the production source commit.

The controlled input commit is 7124e772c53d154cc9131722a4fd4dba4998cf0a.
Its complete tree is independently reconstructed from the baseline plus the
retained binary patch; all five measured source blobs equal production commit
ad87df2168. Both measurement states retain BFME1 input 32774ab03393709a7f14331ba8d98d281a55ffd9,
while production keeps its separately verified 0bf534ea7ccde110c456edb9cd2dd5dae823c953.
No donor implementation is used by this repair. The separate measurement
worktree initially lacked its submodule checkout; its normal commit hook refused
that input. An isolated clone of the locally available committed baseline fixed
the missing checkout, and the unchanged commit then passed all normal hooks.
No hook, cache check or dependency gate was bypassed. The full runner uses
BUILD_POOL=1 and an immutable export, reusing 46,912 previous object/cache files.

The authoritative full link-cycle process exits zero after 3513 seconds.
Its unique placed closed-strict credit changes from 1,699,192 to 1,700,931 bytes,
a gain of 1,739 in 6 rows, with zero lost rows and zero new function coverage.
All six scalers are self-strict and closed-strict. All five native coefficient
data nodes pass with their complete eight-byte extents. Exactly five of 23,460
canonical objects change; all other 23,455 objects agree. Final link drift and
new unresolved references are zero, with no missing objects, failed compiles
or stale warm start. This gain belongs to the fixed comparison, not current
master. Independent closure reproduction and remaining witnesses follow.

The remaining-witness file is extracted from this completed measurement, not
from a prospective graph. InitPostProcessing remains closure-blocked through
GetProcessorFlags and CpuProbe_VendorSse2 to the selected __except_handler3
import twin (missing map/object definition). The independent Util configuration
path still reaches FilterBlock2dBil's g_bfmeTableC7E0 forward-map conflict. Neither
CPU behavior nor these unrelated data providers was changed or claimed repaired.
The final scaffold still reports five forced duplicate symbols (ten diagnostics);
this scoped credit is not the no-FORCE/no-stubs whole-game exit test.

Independent closure_report reconstruction reproduces all 98,202 status rows and
the exact 1,700,931-byte credit, with 25 ranked roots independently re-proved.
The retained graph/status hashes and receipt binding are in
independent-closure-verification.json. Source integration is t=2 minutes for the
shared six-body cohort; the full measurement process takes 3,513 seconds
(58.55 minutes). Claims were renewed before publication after the completed run
was collected. No source, ledger landing or attempt-log line was repeated.
