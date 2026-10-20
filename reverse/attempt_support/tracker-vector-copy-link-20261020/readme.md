# Tracker vector copy link investigation

Inputs: BFME2 `7e32ef28cefb71e864fe9b1cf2ee5b89b280d271`, BFME1
`4483e88da1c2f3b9a273f779baac7458bd8bb891`, published census
`3f413ed3ff` (2026-10-20 18:52). No source, ledger or pin changes retained.

The 125-byte copy constructor at 0x4147CF remains blocked by its
`vector<BfmePod44>` copy constructor at 0x414490. Earlier evidence (attempt-log
entry for 0x4147CF) identifies this member with the ScoredKillTracker family;
the POD view cannot represent both the native copy helper at 0x414359 and its
other POD helper bindings. The name and field interpretation remain structural
inferences rather than recovered original symbols.

`candidate.patch` replaces the member with the existing ScoredKillTracker view
and explicitly instantiates its vector copy constructor. With the unchanged
`/EHsc /MD` flags, explain_mismatch on 0x414490/96 reproduces the instruction
bytes with three unresolved callee bindings:

* allocator getter: 0x21983A;
* vector base constructor: 0x414420 (60 bytes);
* const-pointer uninitialized copy: 0x414359 (38 bytes).

Pin consistency found no existing bindings for these three typed names. Atomic
pin admission with this TU as fold proof accepted the base constructor proof
but refused the other two; `pin-refusal.txt` preserves the diagnostic. The
allocator getter has only seven non-relocation bytes, below the fold-proof
threshold. The const-pointer copy emits 96 bytes here, whereas the rowed
non-const-pointer helper has 38 bytes under the no-exception profile used by
ScoredKillEvaAnnouncer.cpp. Neither refusal is established as a verifier bug.

Resume only with an evidence-backed helper-profile/type reconciliation and an
admissible binding for the short getter. The patch is diagnostic, not a verified
replacement; retyping/repointing the old vector constructor and EH rows was not
attempted. Paired consumer/POD-provider link checks were 0 linked bytes before
the trial; no gain is claimed. Source was restored, `./build.sh` on the consumer
passed 1/1 matched rows and literal/import checks, and all seven claims were
released. No pin was written.
