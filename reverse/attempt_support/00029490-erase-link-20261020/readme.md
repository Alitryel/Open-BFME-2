# String assign / erase link attempt

At 1add57af4b, frozen index 144ed0ccab, current caller 29490 remains 153B exact. Sole blocker is the visible erase copy; prior declaration-only suppression changes the native 0x14 frame to 0x0C. No declaration retry.

A pragma on the generic member definition leaves its /Od instantiation unoptimized. An inline explicit specialization under optimize(gsy), with /MD, preserves the 153B parent but leaves move out of line. Making move forceinline preserves the parent and produces the correct memmove import and zero-count branch, but erase is 54B against native 57B: first/last/this use EBX/EDI/ESI rather than EDI/ESI/EBX, and the tail folds the finish update into add [esi+4],eax. Both bodies have matching behavior; this is not byte proof. No source, pragma, pin or alias retained. Candidate and final diagnostic preserved here; scratch build/link-erase-oct20 contains all trials and original object. Source restored and normal gate rerun.

A next hypothesis, untested: instantiate the original dependent generic member explicitly under the helper optimization scope instead of specializing it; generic instantiation may preserve native arithmetic/register shape. Confirm caller's visible-analysis stack slots remain intact. Do not repeat specialization or declaration trials unchanged.
