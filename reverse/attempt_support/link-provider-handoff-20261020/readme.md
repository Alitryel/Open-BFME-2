# Remaining provider prerequisites after the +5,843 B batch

Base: 01dd767364, published census 5366c4f808 (2026-10-20 12:21).
These probes add no linked coverage. All experimental Code edits were restored;
the restored Path and subtitle-vector byte gates pass. No alias, pin, header,
ledger source or compiler flag change is retained. See re_attempts.log entries
for the named RVAs and trial timings.

* HLod: current preview holds 14,709 B. The strong fake ModelArrayClass complete
  destructor in HLodModelArrayDeletingDtor.cpp has a 12 B body; hlod.cpp emits
  the real 45 B complete destructor but no scalar wrapper. Moving the scalar
  row would lose its definition. The independent HLodDef scalar copy is 30 B
  against retail's 28 B. Repair both the true ModelArray view and scalar
  code generation before counting any gain; there was no source trial.
* Angle 0x363B4B: both providers are current and strictly byte-verified, but
  the inline-noinline copy in PathRva00365309.cpp conflicts with the strong
  VectorAngleRva00363B4B.cpp owner. Replacing the visible helper with a
  declaration changes the caller from a 0x78 stack frame to a biased frame
  allocating 0x9c and changes extensive scheduling. The 2,177 B caller needs
  visible callee analysis. Owner coverage remains zero (122 nonpadding B).
* Subtitle overflow 0x6887F0: the stock-header stlport_vector_int.cpp copy is
  not retail's and wins ahead of the verified alloc-only owner. Both current
  units pass all eight rows but preview 0/470 B. Declaration-only specialization
  and extern member instantiation each change the 50 B push_back caller:
  the empty iterator tag gains an initialized stack home. Only that row fails;
  the original seven-row source was restored and reverified. A compatible
  allocator/provider definition must preserve the caller's known tag effects.

The read-only rehome scan's exact 29 B Entry constructor is already deferred:
its split owner links, while AutoResolveBattle does not. Moving that row loses
coverage (recorded 2026-10-14 and again at adfdf28d0a). The narrow-string size
constructor also has an existing deliberately reverted repair; its required
full-gate vtable-identity prerequisite was not shown resolved, so it was not
retried. These are prerequisites, not new evidence that the lane is exhausted.
