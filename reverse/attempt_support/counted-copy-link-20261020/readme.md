Counted-handle placement copy repair, 2026-10-20

Parent cdbb820b24; published legacy census 5366c4f808, 2026-10-20 12:21.
Four consumers emitted nonretail _Construct COMDATs for opaque element views.
The 4F6A52 native helper calls the two-handle copy constructor at 44BD00;
the 2393AA helper calls the one-handle copy constructor at 0A8C7C. Both
helpers null-check the destination. Existing rowed owners independently
establish these calls and layouts; the constructors increment the owned
reference counts. Raw-byte or list copy from the consumers' structural views
is incorrect. Specialized construction calls the rowed constructor, with
throw() justified by each complete native constructor body. Keep COMDAT
identity and the out-of-line boundary with inline plus noinline. Reserve
reuses the allocate/copy unit's definition rather than emitting a competing
raw copy.

The generic STLport construction operation is the reference semantic guide;
BFME1 revision reviewed remains 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
The opaque source element names and their unused fields remain structural
inferences, not newly established application identities. No new pins,
ledger rows, aliases, shared headers or verifier changes.

Before: four consumers link 0 B. After: 223 + 104 + 177 + 178 = 682 B newly
link in current-object legacy preview. All seven consumer/provider units link
337 -> 1,019 B. Existing providers do not lose bytes. This is not a
closed-strict or full-link measurement. Self-strict preparation verifies
19/19 rows across the six consumer/helper units and 1/1 constructor row,
including literal/import checks. All original consumer rows pass the byte
gate. pin_admission.fold_proof_problems independently proves each of the
three existing _Construct bindings against its whole owner body and every
relocation (temporary proof notes only for the two older blank-note pins).
Declared-definition, canonical-class, ledger and diff checks pass.

Initial direct specialization emitted a 45-byte EH wrapper. Inline plus
throw() produced the exact 18-byte helper, but inlined it into the overflow
row; noinline preserved the required call boundary. No failed candidate
remains. A census-name sweep found these four indexed consumers for the
three pinned Construct names; all are repaired together.

Residual shadow identity findings: once the Construct callees are repaired,
the checker reaches _M_clear<Rva00058BBDElement> and
_M_clear<Rva0023A076Element>, both pinned to 57DE4. Their list-shaped view
still emits cleanup differing from that address's owned opaque-reference
cleanup. These are independent inherited template-view debt; the ordinary
link preview does not enforce it. No closed-strict improvement is claimed.
A further repair must reconcile destruction with StlportOwnedDeque.cpp and
stlport_vector_opaque_mclear.cpp, and measure an additional linking consumer
or be included as a verified prerequisite. Do not treat the opaque list view
as an established element identity.
