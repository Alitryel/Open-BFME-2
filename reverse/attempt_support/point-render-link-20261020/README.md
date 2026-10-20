Point renderer helper binding, 2026-10-20

At parent 4241adb2d4 the 3781-byte point renderer has two losing helper copies:
the SSE Vector4 four-float constructor and DX8Wrapper::Set_Transform(Matrix4).
Its existing target identity, layout and provenance remain unchanged. BFME1
verified revision reviewed in this session: 4483e88da1c2f3b9a273f779baac7458bd8bb891,
including emitter repair 51b97cd796. Neither helper has a retained call here.

Reuse the established scoped SSE Vector4 view and opt this renderer into an
imported forceinline declaration of the unchanged Matrix4 setter. The setter
shim keeps its original declarations for every other consumer. No IAT import
reference is emitted. The three removed COMDATs are the constructor, Vector4::Set
and the matrix setter. Every retained nondebug section, definition, flag and
relocation is identical, including EH metadata. No new identity or layout is
inferred from this linkage repair.

Normal byte/literal/float/import verification passes the whole 3781-byte row;
EH verification is exact, converged-data and declared-definition checks pass.
Strict provider preparation passes. The paired proof replaces old/new objects
in one frozen index: legacy prediction 0 -> 3766 linked nonpadding bytes.
Closed-strict gain is unmeasured; no census or full link cycle was run.
The other three banked_segline consumers retain their original preprocessing;
the complete byte gate also checks the shared shim change at commit time.

proof.json records the index and object hashes. To rerun proof.py, preserve the
old object at build/point-render-link/before.obj, or rebuild the parent source
and header in an isolated trial; prepare the current provider through the
normal byte gate first. The current index is not changed by this proof.
