# Isolate the unresolved 4192A4 placement-copy view

2026-10-23, gpt-6.1-sol; parent 64372a5697. Compiler flags stay
`/Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB`; no donor/header changes.
Published census 456ce161c5, retail-truth-4, 2026-10-23 06:28.

StlportPairConstructFamily.cpp was held at 0/168 linked bytes by the old
BfmePod20 placement helper and its copy-callee binding. The native copy at
41922E now has a separate string-aware Rva0041922ECopy.cpp provider; its
AsciiString plus 28-byte record layout does not justify equating the old
pair<const int,BfmePod20> spelling with it. No alias or rename is introduced.
stlport_pod_hash_bodies.cpp also retains a non-retail trivial copy under the
old spelling, plus several independent conflicts.

Move the unchanged 45-byte placement helper, 10-byte compiler EH handler and
14-byte cleanup action to StlportPairConstructPod20.cpp. Preserve every ledger
identity, extent, note, compiler flag and external callee. This follows the
link lane's supported isolation repair: the unresolved helper remains present
and byte verified, while unrelated placement families can link.

Paired legacy current-object preview, with stlport_pod_hash_bodies.cpp and
Rva0041922ECopy.cpp supplied as the same peer/provider cohort:

- Family before 0/168 B; after 113/113 B, LINKS.
- Existing copy provider stays 61/61 B, LINKS.
- POD hash provider stays 0/616 B with the same independent blockers.
- Aggregate existing indexed units: 61 -> 174 B, **+113 B linked**.

The new split source has no entry in the published index. Ordinary link_check
explicitly reports it unpreviewable; no linked-byte gain is claimed for its
55 authored bytes or its cleanup funclet. Its old unresolved binding is not
claimed repaired. This is a legacy scoped preview, not a self-strict or
closed-strict measurement, and neither census nor link_status.csv is changed.

Acceptance: `./build.sh StlportPairConstruct` passes 8/8 rows across both units,
including automatically resolved EH-label renumbering. Both sources pass
find_declared_unmatched. `link_check.py --prepare-current` passes the same
8/8 rows with strict reusable compiler receipts. `link_check.py --new-variants
--staged-peers` reports no new conflicting unanimous COMDAT variants.

Local diagnostics: build/link-seat-pod20-cohort-before.log and
build/link-seat-pair-split-{existing-after,gate,strict,variants}.log.
The next repair needs an evidence-backed type/name reconciliation for the
41922E/4192A4 family and all its callers, not another trivial-copy suppression.
