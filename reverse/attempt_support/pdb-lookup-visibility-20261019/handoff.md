# PDB lookup: visibility, lifetime and ordering follow-up

BFME2 5dc0a19ac8; BFME1 a18d9ed50607e9175de4d6568798d7d73119de09;
MSVC 13.10.3077, original bank flags O1/G6/Oi/Ob1/MD/GX-/GS-.
Native boundaries and CodeView facts remain those recorded in
../0x0075b177-pdb-source-lookup/. No implementation source was read.

The existing whole-member bank is unchanged: helpers 75ACEE/849B and
75B03F/312B are exact; public caller 75B177/847B commutes two argument loads
at +16 and +19, differing at +17/+18/+1A/+1B. Do not mistake exact private
helpers for a completed replacement of the retained native archive member.

New visibility hypothesis: export the two helpers, declare one or both opaque
in the caller's TU, or move definitions later. All preserve the same 847B
and four differences. Thus interprocedural visibility is not the missing lever.

Typed argument bundles, natural inline lookup adapters (including output
initialization/name assignment), narrower declaration scopes, early public
prototypes, chained zero initializers and positive/loop-shaped outer control
flow do not close the residue. Bundles containing address can shrink the frame
34 to 30 without improving load order. Moving the 1024B alloca through the
initialization changes the prefix and register saves instead of matching it.

Compiler-ordering probes were diagnostic only. Empty asm is inert;
extern-C _ReadWriteBarrier moves the alloca result store too early or changes
other prefix scheduling. _ReadBarrier is not recognized by this compiler.
The initial C++-linkage barrier declaration emits a call, so those results are
not intrinsic tests. Volatile pointer parameters change the decorated name
and cannot claim the public ABI; volatile snapshots worsen size/frame.
None of these probes was promoted to production.

trials.json records the measured sizes and first differences. It includes
failed diagnostic forms so they are not repeated as plausible successes.
No better bank, Code source, pin or ledger recovery resulted. Further work
needs a new supported backend/source context for the two independent loads.
