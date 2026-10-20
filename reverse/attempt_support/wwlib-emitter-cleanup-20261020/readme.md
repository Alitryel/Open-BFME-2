# WWLib emitter cleanup

BFME2 base `54a521e4`, retained BFME1 pin `92f6bbe8`; original compiler/header inputs and source flags retained.

`MixFileCreatorFileInfoStructAssign.cpp` already has real Swap/Insert callers that require its assignment operator. Remove the redundant unrowed artificial caller and its two inline-depth pragmas. `stlport_vector_e12_o1.cpp` uses ordinary explicit template instantiations for precisely the ten library helpers formerly forced by artificial calls, some using null pointers or receivers. Keep its established placeholder element identity, static max, and existing linker alias unchanged. No new target identity is asserted.

Normal whole-unit builds pass 8/8 and 10/10 rows, 675 claimed bytes total. Paired original/current objects retain exactly identical relocated bytes at all 18 owned rows. Both exception checks have 3 EXACT graphs, zero failures. The original E12 scratch compile explicitly carries the native source path-derived `/O1 /arch:SSE /G7` flags; omitting those flags initially failed and was not used as a baseline.

The same published census index was used for both sides, refreshing only current `mixfile.cpp`, whose stale conflicting assignment copy had already been removed upstream. Both original and repaired units link cleanly in that paired preview. This is 0 new unique bytes and 0 new linked bytes. Removed object definitions are the eleven artificial emitters and two unused incidental E12 helpers; no definition was added. No owned retail definition disappeared.

Focused placement scan found 0 bodies and 0 pins. Undeclared-function checks are clean. No header, pin, gate, baseline or verifier changes. `paired.json` records object SHA256 hashes, each retained relocated row hash, definitions and complete link predictions; `before-eh.json` and `after-eh.json` record the exception checks. Objects and reproduction script remain in ignored `build/mixfile-anchor/` in the writer checkout.

Agent: Codex (runtime model not exposed).
