# Joint segment-distance bank repair and improvement

Base e9bad594029953ca872149a8adeb2f4243dc9566; model gpt-6; lane R,
budget 30m, approximately 5 minutes for the joint helper/caller attempt.
BFME1 reference a18d9ed50607e9175de4d6568798d7d73119de09.

## Native evidence and semantic correction

Retail helper 0x004EACF5..0x004EADBA is 197 bytes, RET0, with
segment start a=EAX, segment end b=EDX, query p=ECX, result XMM0.
The retail 227-byte caller at 0x004EADBA..0x004EAE9D (RET4) passes
current point at ebp-C in EDX, previous point at ebp-18 in EAX,
and query point at ebp-24 in ECX. See the complete retail.txt.
The object layout and vslot 0x34 come from those bytes; Polyline and
PointSource are descriptive labels, not proven original class identities.
The ZH Line2D.cpp routine was reviewed as a geometry lead, but its ABI,
outputs and handling differ; this is reconstruction from target evidence.

The preceding caller bank declared helper parameters (b,a,p), but called
it (&p,&prev,&cur). This made the caller look exact by passing the query
as segment end and current segment end as query. It is not equivalent:
for a=(0,0), b=(10,0), p=(5,3), native distance squared is 9, while the
swapped calculation is 34. The old 0.998 caller bank is therefore not a
better correct candidate. Its historical source remains in git history.
The new joint banks use (a,p,b) with (&prev,&p,&cur), preserving meaning.
The remaining caller register mismatch is honest; do not fix it by swapping
argument meanings again. Also do not pin an unverified helper.

## New best

Reproduced old helper score 0.70826 (its older stored score was 0.6).
Coord2D constructor expressions in both squared-distance tails, with the
y-square term written first, restore the native projection tail without
merging it into the endpoint tail. A Coord2D constructor for the repeated
segment delta similarly restores the length-squared register schedule.
Parameter order (a,p,b) improves the initial XMM assignment further.

Helper score 0.90571, independently checked COFF extent 197, no unresolved
references. Caller score 0.98028, COFF extent 227, local helper unresolved
by the current ledger, as expected. Neither body is matched or link-credited.
The helper still assigns b=ECX/p=EDX instead of b=EDX/p=ECX and loads the
query Y component before X. Fix the helper ABI and entry schedule together;
then verify the actual joint caller, including its local call relocation.

## Trials and reproducibility

90 serialized measured candidates including baselines; exact transformations
are preserved in trials.py.txt and scores in results.json. Scratch compilation
uses MSVC7.1 /O1 /G7 /arch:SSE /MD /DNDEBUG, Wine11, BUILD_POOL=1,
FLAG_DEFAULTS=off. Variants cover inline coordinate subtraction/dot/distance,
by-value/reference wrappers, square helpers, constructor tails, shared/separate
endpoint returns, sum wrappers, six correctly paired parameter orders,
reference parameters, pointer/object shared tails and five compiler switches.
Separate returns still merge tails (176 bytes); pointer tail 167 and object
tail 193 do not retain native structure. Reference parameters and tested flags
do not fix the remaining ABI. Early harness path/replacement failures were
corrected; failed harness runs are not candidate measurements.

For reproduction, copy the pre-attempt caller bank from the base revision to
build/lane-r-poly/banked.cpp and run the sections of trials.py.txt in order.
Inspection of the final candidate is recorded in inspection.txt. Scorer lengths
in the trial table may be clipped; only the final 197/227 extents were separately
validated. No production source, pin, extent, or verifier was changed.
