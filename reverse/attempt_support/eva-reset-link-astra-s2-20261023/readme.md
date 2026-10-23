# EVA reset and parser linkage

Starting revision a7e89da04e with the seat's separate packet repair queued. BFME1 remains the verified 138757e9b74645fbcbb7724a7af2764e34931e11 input. Existing BFME2 source and native bodies are the implementation evidence here; the BFME1 Eva files do not supply a replacement for this BFME2 status layout. Prior relevant attempts: re_attempts 52206/52238/52821/52830/52832/70781/72245/72246/80402 and eva-summary-s6-20261023.

## New result

Reset001DCD3C was exact only with receiver volatility/address-taking that prevented two INI parsers from reusing a dead temporary. Direct scalar writes preserved parser635/484 but hoisted XOR EAX,EAX over two negative-one stores. Use _mm_set_ss(-1.0f) and _mm_store_ss for exactly those two fields; leave every other member write direct. This is ordinary SSE intrinsic C++, matching the native float stores without assembly, synthetic code bytes, or a call target alias. All three complete bodies now match simultaneously.

Seven expression controls used only tools/explain_mismatch.py with explicit candidate RVAs and sizes; the driver restored the source in a finally block. Control, volatile constant, intrinsic-zero-only, known-float flag tests and known-float zero expressions retain the old reset mismatch. Intrinsic negative-one stores and intrinsic stores for every float both match80/635/484. Select the smaller two-store change. results.json and trials.py preserve the matrix; the reset log preserves the exact result.

Making that exact reset inline/noinline still loses parser ECX reuse (2/5 fail). Thus keep one strong real definition and reunite the parsers with Eva.cpp. Expand its existing opaque +28..+5C padding into the same parser field view, append the three unchanged parser implementations and their declarations, move their five ledger rows (three bodies/two EH stubs), and remove the split TU. This leaves one native reset and no new aliases, pins, anchors or runtime operations.

## Validation

The merged unit passes all21/21 rows, ten literals/five empty-string references, five compiler float literals and all other normal reference checks. All four EH records are EXACT. Frozen-definition and pin-consistency checks pass; place_bodies finds zero additional bodies/pins. The whole merge needs no shared header, gate, baseline or whitelist change.

Strict prepare-current remains unavailable because the existing reference/shims/eva_vector/EvaVectorABI.h:634 has a macro include _STLP_NATIVE_HEADER(vector) outside the recognized STLport roots. The refusal is an include-inventory limitation, not a byte mismatch. Source-local include paths were changed to explicit existing roots and resolve to the same files, but the macro still refuses a reusable receipt. No shared-shim or verifier workaround is made. Do not describe this as a strict-current or closed-strict proof.

A scoped legacy preview against456ce161c5 (2026-10-23 06:28) links3016 existing bytes. The split source is absent from both disk and the current ledger; preview.py uses the standard link_check.forget operation for exactly that retired object and refreshes only the merged current object, all in memory. It writes no census, status or index. The published index had both units unlinked on the duplicate reset. preview.json preserves those baseline blockers and the current clean result. This is existing-code linkage, not new unique coverage or a runtime/full-link claim.
