# Deferred narrow string cleanup provider repair

Eight available units (sources.txt) fail only on external narrow String_base
cleanup and alloc_proxy<char> deallocation copies in current-object legacy
previews against census 2967eab33e. All 22 rows pass strict-current preparation
before the trials; 9 string literals, 1 empty-string reference and 8 imports
are verified.

Trial 1 retains the vendor alloc_proxy::deallocate and String_base destructor
as TU-local dllimport/forceinline specializations. All eight units change
callers (12/22 rows fail): formerly inlined buffer frees become out-of-line
cleanup calls, with associated EH and funclet changes. Trial 2 also gives
_M_deallocate_block the same inline-only specialization, following the existing
Rva00079911Clear pattern; the same 12 rows still fail. This pattern is therefore
not portable to these units without additional compiler evidence. No false
reject is asserted: the emitted callers really differ.

All eight sources are restored to their original blobs. The post-restore
strict-current preparation verifies 22/22 rows again. No linking improvement
is claimed and no reconstruction is left in Code. The shared prerequisite is
preserving the existing partial inlining and EH shape while suppressing the
competing external definitions; do not repeat these two variants unchanged.
