# O1 constructor-provider receipt diagnosis (read only)

Actual production object: build/match/^code_^game^engine^device_^source_^w3^d^device_^game^client_^drawable_^draw_^w3^d^model^draw^o1^inlines.obj
Sidecar is same stem with .deps.json (not .obj.deps.json).

Fresh independent read hashes object to MD5 2da4f38f6dbcec0b1196ecd0d0626d37. Version-2 receipt records object MD5 41a33f1c6366253a8facc9ccf004657f. Object is158424bytes, mtime2026-10-14 20:42:08.255834UTC; receipt mtime20:42:15.398602UTC. Saved initial weapon production-before O1 snapshot also hashes2da4, so current object equals the campaign baseline object.

Fresh process build._object_layout data MD5 and build._hash_file both hash2da4. This is not stale COFF-reader bytes. data_check stamp() reads uncached file bytes and correctly refuses the real receipt/object mismatch at its currency check.

compile_is_current(strict=True) and ordinary mode both returnTrue because their implementation verifies source, compile command, dependencies, and (strict) include inventory, but never compares meta[object] with object content. Therefore strict preparation can truthfully pass its present currency predicate while data_check correctly refuses the object binding. Root prepare-group logs show normal gates reused all26objects after strict preparation. These two outcomes are not logically contradictory under the actual code.

The exact command/source object-store key is D:/LAN/openbfme2/Open-BFME-2/.git/bfme-objstore/d2/d28ecb2a82cb214988770edf53645da14827c6dea9b36a4ea36da42a499a84da. Its version-2 entry8c58bd33a6a719a4.obj also hashes2da4 while its receipt records41a3. A separate legacy entryd32ee122fa398bf5 has both object and recorded hash2da4. Thus the mismatched pair is persisted in the object store, and ordinary restore can reproduce it because restore checks compile_is_current without object hash binding. The historical action that originally created this mismatched pair is not established by these observations; no unsupported attribution is made.

No source/object/receipt/store changes, cache deletion, recompile, gate edit, or false-reject claim performed. Root can preserve the bad pair as evidence, force one normal compile with object store disabled and fresh receipt, then independently hash the resulting pair before retrying data gate. Simply rerunning a cache-current normal gate or restore is insufficient to ensure new bytes/receipt. Any tooling integrity repair is a separate lane/commit with regression and Verifier-Change trailer; none attempted here.
