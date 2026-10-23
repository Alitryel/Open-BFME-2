# Narrow vector instantiations

The camera-track record growth unit and string-record copy unit instantiated
the entire vector class. This emitted unused default-insert members referring
to undefined element default constructors. Instantiate only the existing rowed
growth/copy helpers. No element ABI, retail identity, pin or ledger row changes.
All eight existing bodies remain byte-exact (281B and 197B respectively).

Paired current-object legacy link prediction improves 0 -> 478 linked bytes,
with both units link clean. Strict self preparation verifies 8/8 bodies and all
literal/import checks. Frozen definitions, canonical class gate, data shadow
and new-variant checks pass. This is a legacy prediction with self-strict byte
evidence; no closed-strict or full-census gain is claimed.

BFME1 donor revision reviewed this session:
92f6bbe8e1dcdb46b5d27da0674313efc822b790. This repair uses the existing target
rows and template emission evidence, without importing donor source.
