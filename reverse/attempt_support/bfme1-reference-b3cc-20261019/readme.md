BFME1 b3cc6b15 reference refresh and existing funclet parent repair

At fixed BFME2 55ae0eb8cd932abab4d0e5515fa97e7a928b6dc1, compare verified
BFME1 cf0a80c228583af789772b794ab27abcab2debbf with official master
b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b. Both complete byte gates fail only
the same existing scoped-parent lookup for the 14-byte funclet76A02C; dependent
reference checks repeat that error and the no-op patch is consequently unavailable.
All989 data rows pass. Complete EH verification is identical:11702 exact,
36 bytes_differ and2 retail_only, all38 already baselined, no missing objects.
The first old EH command accidentally omitted --all and returned a usage error;
old-eh.log preserves it, and old-eh-all.log is the successful complete rerun.

The canonical pair<int,vector<unsigned>> Construct name now belongs to the
21C671 row in stlport_hero_integer_vector_tree.cpp. The independent45-byte
1E7243 body remains in stlport_construct_stl_types.cpp under its existing
dup_001E7243 alias. The funclet's parent= must name that logical same-source
row. A fresh isolated native compile verifies all45 parent bytes and its entire
EH graph, which places local label$L6038 at native76A02C. The next emitted
handler begins exactly14 bytes later. Every one of the14 funclet bytes,
including its REL32 to the empty placement-delete implementation69E440,
resolves exactly. This repairs metadata; it adds no alias, pin, body or bytes.
The normal scoped build passes all60 bodies after the repair.

The reference layout already uses game/ and inputs/. Every intended donor
include directory and the real compiler include roots were checked on disk;
no reference headers changed in this update. Sixteen changed clean donor trials
were attempted. Fourteen compiled directly, the nbench C++ wrapper compiled
after adding its actual inputs/vendor/nbench include directory, and the C
implementation is include-only. No new placements. Fifteen larger named WWVegas
units also compile with no new placements. An independent minimum8-byte pass
over335 earlier library trials atcf0 finds none; changed units are refreshed here.

The refreshed BFME1 retail scan has5522 unique placements, all already owned,
with5515 independent boundary controls. Its sole near lead is the previously
blocked25-byte Fade cleanup76962A. The lift lane has154 bodies,107 servable.
Forced ZH compilation builds919 units and refuses68, preserved in comparison.json;
its exact search finds only owned placements and its sole15-byte7A86AF packet
still lacks the supported clean C++ parent. No reference queue was treated as
exhausted merely because another one was empty.

comparison.json records input revisions, hashes, commands, include paths and
limitations. The normal commit hook must pass the final whole-tree gate before
this update can be published; the successful canonical result is recorded after
that hook completes. No verifier, baseline, compiler setting or source edits.
