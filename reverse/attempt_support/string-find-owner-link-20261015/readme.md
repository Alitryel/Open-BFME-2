# String-hashtable iterator provider repair

BFME2 base: `4af7765b504af85657faa07a65891fcb2b34d6d5`.

`stlport_string_find_0060CAEA.cpp` defines an exclusive iterator wrapper at
0x0060CB61, 27 bytes. `Rva0060D269.cpp` already emits a byte-and-relocation
identical inline noinline copy. Its caller needs that visible definition for
MSVC register-use analysis. Rehome the existing row to that emitter and remove
the standalone duplicate. No name, address, extent, pin or alias is added.
The established address-derived identities and layout claims are unchanged.

## Fixed-index before/after evidence

The frozen census measures `ac77c85054`, 2026-10-15 14:25, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
Both strict-current objects were independently refreshed into copies of this
same index for the paired comparison. No census files or index were modified.

Each object loses its one duplicate-wrapper finding. The find unit changes
from one finding to none and predicts **0 -> 65 existing linked bytes**.
The caller retains exactly its 24 independent COMDAT and four selected-provider
findings, predicting zero linked bytes. Check both units together to replace
the census's old provider, rather than inspecting one against stale objects.
The two-unit local link check therefore exits 1, with the repaired find unit
reported LINKS. This is a legacy local prediction: new authored unique C++
bytes are zero; self-strict and closed-strict placement gains are unmeasured.
No full census, link cycle, nightly or boot runner was started.

All four retained find-unit COMDATs and all 42 caller COMDATs have identical
whole bytes, relocation digests and sizes. All other normalized nondebug
sections, data facts, linker directives and symbol bindings are unchanged.
Removing the exclusive wrapper also drops its unused 18-byte iterator
constructor emission; neither removed section has a nondebug reference from
that object. The caller's inline emitter is unchanged. The wrapper twin's
whole 27-byte body and relocation digest are in proof.json.

## Acceptance and reproduction

The explicit byte gate and strict prepare-current gate pass all three rows
(65, 27 and 128 bytes), including each retained caller's relocations. EH is
EXACT 1. Enforced data, convergence, new variants, class, declared definitions,
CSV and whitespace checks pass. The placement rescan finds zero bodies/pins.
See acceptance.txt and the captured gate outputs.

proof.py uses ignored before/after snapshots in
`build/string-find-owner-link-20261015/`, strict receipts and the frozen index.
The snapshot sources came from the BFME2 base above; the current ledger owns
the wrapper in its caller unit. proof.json preserves the paired findings,
normalized-section assertions, object hashes, retail twin and data facts.
Both files and the rehomed RVA were claimed before editing.

## Donor review and remaining blockers

Reviewed BFME1 repair `d5043e1658bdf46d39281a2e975e9e0145221555`, which rehomes
eleven Coord3D rows from exclusive definitions to identical existing inline
emitters. Its provider-ownership pattern applies here; no donor code, ABI,
layout or identity was imported. BFME2 whole-object and retail evidence above
establish this repair independently.

The BFME1 checkout/gitlink remains the clean verified
`a7c38d3b2597121f178ab5190b3062478823257d`; fetched official master is
`3f09d565e`. The overdue pointer verification is foreign-claimed, so no
pointer change, repeated multi-hour verification or freshness success stamp
was made. The caller's remaining STLport allocation/string variants and
selected-provider conflicts require separate supported repairs.
