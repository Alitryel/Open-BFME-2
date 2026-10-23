LinearCampaign beginCampaign reserve provider repair

The existing229-byte body at1ECDB3 calls vector<BfmeAssignRecord172>::reserve
at1EBE2D. Its old private POD definition emitted trivial copy/destruction helpers
that conflict with the verified nontrivial record provider. The ordinary preview
reported six COMDAT conflicts and two wrong-selected helpers. It also needed the
current GetThingTemplate16-byte provider at37DC52, renamed after the published
13:17 census; provider and consumer were checked together rather than treating
that stale index name as a missing implementation.

The history record is never accessed by this file. Forward-declare it and declare
the existing reserve specialization, keeping record copy/lifetime behavior in its
verified provider. This removes the guessed private POD layout and its spurious
helper implementations. No source behavior or call target changes: the complete
beginCampaign body remains229 bytes exact, reserve126 bytes and the lookup16 bytes
also verify through their current providers. No pin, alias, baseline, flag or
shared-header change, and no new C++ coverage.

Validation: normal scoped build1/1, find_declared_unmatched passes, place_bodies
minimum8 finds no incidental bodies. Ordinary link_check over Begin and the
current lookup provider reports2/2 LINKS: Begin0->228 unique bytes, lookup146->146.
The new-variants check over those same two files exits0. These are bounded
predictions against published index8eecc93d07, not a new census or link cycle.

The provider stlport_asciistring_record_bodies.cpp already supplies the exact
reserve implementation; no broader record layout reconciliation is claimed.
proof.json preserves native rows, source/object hashes, relocations and complete
resolved bytes. The before source is recoverable from the parent commit.
