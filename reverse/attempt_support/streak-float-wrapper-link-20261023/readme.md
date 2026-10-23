# Streak float-wrapper link handoff

Base BFME2 fc1e27b6f4; BFME1 donor 96c88c73a5cd1a58fc2f8db691beea50acd996db.
Published legacy census b711de3634, 2026-10-23 14:28; current four-object
preview: streak.cpp 4940 B, StreakLineDestructor.cpp 357 B,
simplevec_float_cleanup.cpp 175 B, StreakVectorConstructorsBFME2.cpp 216 B.
Before and all byte-exact trials after: zero of four link, zero gained bytes.
No self-strict or closed-strict gain claimed. Production edits restored.

Target table CF1688 and the existing matched destructor row establish that
StreakLineClass::~StreakLineClass is the native 327-byte body at 742590.
The ZH streak.h has that declaration commented out; streak.cpp therefore
emits a wrong implicit destructor ahead of StreakLineDestructor.cpp.
Copying the donor streak.h into a TU-local header, uncommenting only
`virtual ~StreakLineClass(void);`, and using it from streak.cpp passes all
65/65 byte rows, string/float/import gates, and declared-unmatched check.
This removes the destructor COMDAT/selected blockers, but gains no whole
unit. Reproduce this minimal useful trial by copying the committed donor
header, uncommenting its destructor declaration, and replacing the one
`#include "streak.h"` in streak.cpp with that copy. No other header edits.

The remaining blockers are selected float scalar deleting destructors.
Retail SimpleDynVec<float> at168067 and SimpleVec<float> at168083 are28 B:
push esi; mov esi,ecx; call native dtor; test byte[esp+8],1; je;
push esi; call delete; pop ecx; mov eax,esi; pop esi; ret4.
Current streak.cpp copies are30 B, differing only in je distance and
`add esp,4` in place of `pop ecx`. Canonical cleanup provider has the exact
28-byte wrappers. Native normal destructors are167FF7/167F67.

Ruled out: optimize(s) around destructor specialization declarations;
optimize(s) around simplevec.h; an unemitted static SimpleDynVec<float>
automatic-object anchor under optimize(s); explicit noinline inline float
destructor definitions with donor cleanup under optimize(s). Each retained
65/65 byte rows but left both wrong selected wrappers unchanged. Revert all
these no-gain variants. `extern template class` for the two float vectors
suppresses required inlining/emission: Set_Widths calls unresolved Delete_All,
and StreakLine default constructor no longer inlines float construction
(two failed byte rows). Ending the TU with optimize(s) also fails Set_Colors
and changes SimpleVec<Vector4>::Resize; do not repeat.

Further prerequisites visible in the paired preview: StreakLineDestructor
emits a non-retail normal SimpleDynVec<float> destructor; float cleanup Add
needs an undefined Grow<float>; constructor provider differs on both float
constructor COMDATs. Repair providers and callers together. Declaration-only
Streak destructor alone is a prerequisite, not a linked-byte repair.

Target semantic identity/ABI comes from existing matched target rows and
native tables; ZH supplies the source declaration and vector cleanup guide.
No new identity, pin, alias, table or byte claim was introduced. t=27 minutes.

Follow-up at 0647f94c99: the missing Grow<float> provider can be compiled
from the same verified donor's simplevec.h. Complete 59B at1001D5 equals
BfmePod4's existing owner including every relocation (none); add_match
with --icf-owner admits the float fold and all6 rows pass. The attached
grow-provider.patch preserves this small prerequisite trial. However the
current-object preview still links0/175 B: once Grow resolves, both
selected float deleting destructors are exposed as wrong. The existing
wrapper investigation above therefore remains necessary. All source and
ledger trial edits were restored; no alias row or extra pin was retained.
No gain credited, no additional wrapper-suppression variants attempted.
