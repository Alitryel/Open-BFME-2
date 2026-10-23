Sequential-script constructor ownership, 2026-10-20

Four unchanged callers newly link in paired legacy previews against census
2026-10-20 18:36 at e7a7769fe5: ScriptEngine +1,338 B, TeamUpdateGenericScripts
+531 B, ScriptActions_sequentialScript +476 B, ExecuteSequentialScript +357 B;
total +2,702 B. This is a legacy prediction, not closed-strict closure, a
census update or a full executable link.

The standalone constructor and ScriptEngineDoXfer already emit the same 43-byte
body with the same vtable relocation (digest d023ca99e03b). Making the owner
noinline inline removes the exclusive-definition conflict. A placement-new
emission anchor, marked absent-from-retail, keeps the verified owner emitted.
It has no retail caller and claims no new identity or authored-body coverage.
No pin, alias, baseline, donor source or layout change is needed.

The constructor is an existing neutral target identity. Retail proves the
stores and the vtable relocation; the 16-byte subobject remains the established
compiler-shape inference. No new semantic identity or complete class contract
is asserted. Prior BFME1 linking fixes reviewed in this session contain no
same-name donor repair; the existing target copies establish this repair.

Owner plus DoXfer self-strict preparation: 78/78 rows; strings, floats and
imports pass; four EH graphs EXACT. The four unchanged callers are separately
byte-verified. Frozen-source, canonical-class, converged-data and diff checks
pass. All code bytes and relocation digests remain unchanged.

The owner still has a divergent vtable and selected destructor blocker.
DoXfer retains its unresolved virtual methods, destructor, and STL blockers.
These independent class-reconciliation prerequisites are not hidden or counted
as linked gains. The legacy preview uses the published index for untouched
providers, so it can retain blockers already repaired by other local commits.
