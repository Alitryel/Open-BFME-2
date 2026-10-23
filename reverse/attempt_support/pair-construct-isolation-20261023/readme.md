# Pair construction isolation blocked by local-label migration

Base 4355bd21b3; published index 456ce161c5 (retail-truth-4).
StlportPairConstructFamily.cpp currently previews 0/168 B linked: the
selected Pod20 placement/copy providers are not retail's. Existing native
41922E has a string-aware neutral owner; do not alias it to the provisional
int-key pair. That identity issue remains unchanged.

The isolated trial moves placement4192A4 and its EH handler786729 to
StlportPairConstructPod20Deferred.cpp, preserving flags/declarations and
no new pin. Both ordinary moves verify. eh_verify on the deferred source
reports EXACT1 with no unavailable object. The original unit then previews
0->113 B linked, but this is NOT an accepted gain because the local cleanup
row78671B still cannot move. Candidate source and original-unit patch are
banked alongside this note; all production/ledger trial edits are restored.

add_match.py '$L3172' 0x0078671B 14 <deferred source> --replace-existing
with the original gen-funclet;parent notes refuses: found0 existing rows.
ledger_io.same_function_name scopes compiler locals to their source, so
add_match cannot locate the old source's label when its new identity names
the destination. Reusing --replace-rva would also be wrong: this is a real
parented funclet, not a generated unwind scaffold. Do not change the gate
or edit the ledger around it. A separate tooling repair needs an explicit
old-source migration path and regression coverage for label collisions,
while still proving the same parent EH graph and native action address.

This is a source-migration interface blocker, not an incorrect byte match
or permission to relabel/alias the compiler action. No C++ or linked-byte
gain is credited. Trial duration about8minutes; parent byte checks and
EXACT EH evidence establish the prerequisite for tooling investigation.
