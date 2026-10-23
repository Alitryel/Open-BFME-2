INI macro allocator visibility, 2026-10-23
========================================

Inputs: BFME 2 b001415f9f plus the preceding three link repairs; BFME 1
f890413e75e671748215ba2ef3304aa7953993e9. Existing STLport reference source,
MSVC 7.1 flags in the TU; no new symbol pins, layouts, globals or aliases.

Legacy current-object link_check paired INIMacroTable.cpp with
StlSweepW5Rva0002D281.cpp: 64 -> 253 linked bytes. The macro unit contributes
0 -> 189; the existing 64-byte provider remains linked. Baseline is in
build/ini-macro-link-before.txt, after in build/ini-macro-trial2-link.txt.
The normal byte gate and --prepare-current both verify all four existing rows
(4/4), with no string, float or import references. This is a legacy preview
improvement with self-strict receipts, not a closed-strict measurement.

Target facts: the hash_map constructor at 0x2DC1D calls 0x2D281. That helper's
64 retail bytes call the 55-byte storage-base constructor at 0x25100 and the
bucket initializer at 0x148DDF. The existing real AsciiString hash-table pin
already names 0x2D281. The rowed provider at that address uses an inferred
int/Rva0002D281Element instantiation, with _STLP_NO_EXCEPTIONS and visible
allocator/vector constructors. Its inferred element identity is not promoted
by this repair.

The macro unit's previous declaration-only default vector constructor selected
a different 15-byte constructor, and its allocator-destructor declaration
prevented empty allocator lifetime elimination. The emitted helper was 77 bytes.
Removing just the vector declaration and forcing the allocator destructor inline
left a 69-byte helper and an undefined import in EH cleanup; discarded. Keeping
all three empty/default constructors visible and using the provider's existing
_STLP_NO_EXCEPTIONS setting emits the native 64-byte shape, with the call to
0x25100. All four claimed row bodies remain exact.

explain_mismatch still labels the AsciiString _M_initialize_buckets name
unresolved (it has no independent pin); its emitted 59-byte shape matches the
existing initializer at 0x148DDF apart from named relocations, including its
unpinned _M_next_size call. No pin was manufactured to close that chain. The
legacy linker nevertheless retains the existing retail-proven constructor
provider. This limitation is why the gain is not called closed-strict.

Cause sweep: the current rank artifact has no other unit blocked on this exact
AsciiString-pair hashtable constructor. Other hash-map sources have different
providers or independent blockers and were not changed.

Post-rebase audit: --prepare-current verifies both surviving repair units, 7/7
rows. The four-unit legacy cohort is 64 -> 356 bytes (+292), with the existing
constructor provider unchanged and the adjacent string-buffer overflow unit
still append-blocked. The two earlier +1558/+602 repairs were independently
landed upstream as a67b235991/e8d3a17a58; their duplicate local commits were
skipped during rebase rather than credited again.

The shadow identity check reports a divergent, newly emitted two-argument
_STLP_alloc_proxy<void**,...> constructor. The published index has no retail
address/selection for that name, and it is absent from the kept-reference set
(index references=False, selection=None). Thus retail-truth-2 drops its copies;
the legacy link check reports no blocker. Do not spend a suppression commit on
this unreferenced copy. This does not establish a closed-strict link closure.
