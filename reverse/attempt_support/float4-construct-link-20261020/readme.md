# Float-record constructor ownership: byte gate blocks the preview gain

Inputs: BFME2 `4ba5932b5f`, BFME1 donor `4483e88da1c2f3b9a273f779baac7458bd8bb891`,
published legacy census `3f413ed3ff` (2026-10-20 18:52, retail-truth-2).
No census, link-status, pin, baseline or retained game-source change.

The claim prerequisite recorded in attempt77380 had cleared. Current paired
`link_check.py` on ScriptEngineDoXfer, list_float4_469c61_insert,
vector_float4_469c61, list_create_nodes and Rva005472D3Alloc reproduced
0/5 clean and zero linked bytes. Both first consumers emit a non-retail
`_Construct<BfmeFloat4Record00469C61>`; the last three are held only by that
wrong selected definition. The existing native provider at469C61 is18 bytes.
Its owner and provenance were retained; no new payload identity was inferred.

The attached patch declares the specialization in both emitting consumers.
Paired legacy preview then reports three clean units,493+374+37=904 bytes.
This is a rejected trial, not a verified improvement or closed-strict credit.
The other two units still have independent blockers.

The plain declaration changes ScriptEngine::DoXfer's scheduling while retaining
its6131-byte extent. At parent offset0xFF4, native emits `8b 01 83 65 bc 00`
(load iterator node, zero the frame local), while the trial emits
`83 65 bc 00 8b 01`. All other parent bytes match. The EH verifier reports
four EXACT graphs, including this parent; compiler-local unwind labels move,
so the full byte gate also refuses stale `$L19707` ownership. An exact EH
graph alone does not authorize this parent mismatch or a ledger relabel.

Adding `throw()` to the specialization declaration does not resolve the full
gate's label refusal. Three gate invocations were made (whole unit, isolated
parent, nothrow whole unit), then the source was restored. The patch preserves
the last diagnostic trial. No unmatched reconstruction is left in Code.
Resume only with an evidence-backed way to retain the original compiler's
memory/alias and scheduling knowledge while binding the constructor to retail;
repeating the same declaration suppression is insufficient.

Session queue checks also found many stale census blockers already repaired in
current source. Paired current FX particle providers link296 bytes before any
edit; those bytes were not counted. The large string-base destructor family,
place-list helper, Apt key/vector constructors, native base vtables and EVA
clearer retain documented compiler/ABI prerequisites. EVA strict preparation
additionally lacks a reusable include inventory for parent-traversing includes;
the existing source explains why hiding its clearer changes parser stack homes.
The BfmeThing928FOne consumer is held by another worker. Read-only global
naming found zero supported edits; entry-constructor rehome remains a previously
rejected move into a nonlinking owner. No maintainer-only runner was started.

All trial file and RVA claims were released. The restored normal gate passes
79/79 rows, four complete constructor folds, four string literals, ten empty
string references and one float literal, with no skipped references. There is no
claimed authored-byte, legacy-link or closed-strict gain from this attempt.
