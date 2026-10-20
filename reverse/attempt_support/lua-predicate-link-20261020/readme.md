Lua predicate ownership repair, 2026-10-20

The object-status event parser carried inline-noinline copies of two rowed
predicates whose owner units define strong symbols. Declaration-only calls
with __declspec(nothrow) preserve the complete parser and EH graph while
removing those duplicate copies. Both predicates compare existing memory;
the leaf calls C memcmp, and the record predicate short-circuits two leaf
calls. Their existing definitions substantiate the no-throw contract. No
new identity, layout, pin, ABI, data definition or helper anchor is introduced.

Paired link_check of the same three current providers, against unchanged
published index e7a7769fe5 (2026-10-20 18:36): before 0/609 nonpadding bytes,
after 609/609. Gains: parser 483, record owner 102, equality owner 24.
Only the parser source changes. All five rows pass before and after strict
provider preparation; parser scoped gate 2/2 and EH EXACT 1/1. Link preview,
new-variants, declared functions, class gate, converged data and check_csv
pass. This is self-strict object evidence and a legacy-index preview;
closed-strict closure and executable placement are unmeasured. Authored
C++ coverage +0. The unreferenced ConditionWords diagnostics are unchanged.

An initial inline-ownership trial in the standalone owners emitted neither
unused predicate. It was restored in full before the successful parser trial;
no anchors were added. The matched model-condition sibling already links;
no redundant edit was made there. Other Code definitions of these two names
are confined to the two owners and this parser, so this drains the cause.

Donor review: BFME1 4483e88da1c2, existing-provider repairs a411b334c and
3313189ad reviewed alongside prior session evidence. This target uses the
independently rowed BFME2 predicates and existing parser identity. The donor
supports the repair approach, not BFME2 addresses/layouts. Prior parser
70321 attempt and 0x00336c5d_20261020_nothrow_comparator handoff explain the
exception-analysis dependency; the latter also independently measured the
nothrow declaration alternative on the sibling. t=8 model=gpt-6.1-sol.
