# Campaign copy cleanup ownership

BFME2 parent 6b9c77161e; published index a9f880ad06, retail-truth-4.
Verified BFME1 input 32774ab03393 remains fresh. This repair follows the
target's already verified copy-parent and cleanup relationships, rather than
assuming a donor or generic BfmeE16 identity. Earlier BfmeE16 visibility
experiments are not repeated.

Rva0056616BCopy.cpp formerly held the 333-byte copy constructor, its EH
rows, and nine independent 63-byte cleanup owners. The parent references
three undefined member destructors and a non-retail selected Pod32 vector
copy. Keep its source and flags unchanged in Rva0056616BCopyDeferred.cpp;
leave the cleanup owners in their existing fold-proof source. Remove their
inline specifier in the standalone owner so they continue to emit without
the parent. Their noinline attribute, semantics, bytes and relocations stay
unchanged. The deferred parent declares these verified cleanup specializations
externally, avoiding duplicate strong definitions while preserving every
parent/EH byte and resolved call.
No pins, aliases, layouts or callee declarations change.

Paired scoped `link_check.py Rva0056616BCopy.cpp` preview with current objects
and the same frozen index: 0 -> 567 linked authored bytes (nine cleanups).
This is a legacy preview, not closed-strict or a new census result. The new
deferred unit has no index position and earns no gain. It still needs
~Rva0052C867, ~Rva0052C8AB, ~Rva0052CD81 and the proven native Pod32 copy.

Acceptance: 23/23 byte matches across the two units, 10/10 exact EH graphs,
no undeclared definitions, and strict reusable receipt preparation using
the normal byte gate. The 14 parent/EH rows move together; the nine cleanup
rows and their fold-proof source remain unchanged. Label renumbering is
resolved against the complete exact parent EH graph.
