# Resource-table cleanup prerequisite, 2026-10-19

Whole Rva004E013BOwnedResources.cpp and the owned Rva004DFED8 child
were reviewed and byte-verified. Both parent EH graphs are EXACT and
the resource file links, but native cleanup 0079182C adjusts this by4
and calls the complete131-byte vector<void*> destructor at00027370.
The source instead emits a14-byte Rva004DFC20Buckets destructor.
This is not an admissible fold, despite the parent and EH-shape checks.

This is the same unresolved allocator/vector cleanup dependency as
003EF22B (see table-3ef22b-cleanup-20261019.md). Its real-vector trial
already demonstrated parent-byte success but four conflicting COMDAT
copies. Those inputs have not changed; do not repeat that unchanged
trial independently. A shared fix must preserve normal-path inlining
and bind EH calls to the genuine131-byte destructor without competing
allocator/proxy/vector-base definitions.

The separate buffer cleanup0079184C correctly calls the14-byte7FAB3
owner, already rowed in this source, but this pass does not claim that
the whole file's lifetime dependencies are repaired. New handler791837
and both generated cleanup rows remain unchanged. No source edit.
