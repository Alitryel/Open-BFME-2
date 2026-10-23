# Voice-record helper provider repair

BFME2 base: `908f235353a09667e93c3d2707fb4efc2d7130fd`.

Rehome the existing 51-byte `Rva004D977D::rva004D977D` row at
0x004D977D from its split source to the inline emitter already used by
PickAndPlayUnitVoiceResponse.cpp. Delete the split source. Its only external
code definition is this helper; both copies have identical complete bodies
and relocation digest `31b0cc5051d9`. The helper conditionally assigns the two
existing eight-byte records. Its address-derived identity and layout claims
are retained, without inferring new names or types from equality.

Both sources, the RVA and the separate Rva004D97B0Record.cpp consumer were
claimed before editing. The retained home and consumer sources and complete
objects are byte-identical before and after, including data and directives.
No C++ implementation, pin, alias, extent or compiler option was added.

## Paired measurement

The frozen index measures commit `ac77c85054`, 2026-10-15 14:25 UTC, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
Each phase refreshes strict-current snapshots into an independent copy of
that index. The after phase uses link_check.forget, the index-update path's
normal operation, to remove facts for the deleted object. The saved index,
committed link_status.csv and census history are unchanged.

| Unit | Local findings before | After | Legacy predicted linked bytes |
| --- | ---: | ---: | ---: |
| Rva004D977D.cpp | 1 duplicate | removed | 0 -> removed |
| PickAndPlayUnitVoiceResponse.cpp | 8 | 7 | 0 -> 0 |
| Rva004D97B0Record.cpp | 0 | 0 | 580 -> 580 |

The only finding removed is the helper duplicate. New authored bytes and
legacy predicted linked-byte gain are both **zero**. Receipts prove individual
object currency; no self-strict or closed-strict placement gain is claimed.

Ordinary two-file link_check exits 1: it still sees the deleted split object
in its unchanged census. The paired proof removes that obsolete object
explicitly and demonstrates the seven remaining home findings. Its separate
consumer remains LINKS. No full census, link cycle, nightly or boot runner ran.

## Acceptance

Before explicit strict preparation verifies 25/25 rows across three units;
after verifies 25/25 across the two retained units. The ordinary byte gate
inside add_match verifies all 20 home rows, including the rehomed row's entire
retail extent and relocations. It also verifies 31 strings and two compiler
floats, with zero skipped or baselined references. Nine existing funclet pins
are verified through their parent EH graphs after compiler label renumbering.

EH: six EXACT, zero debt or missing objects. Enforced data: zero findings.
Converged data: eight addresses, no second names or unjudged rows. New variants,
class admission, frozen definitions, CSV integrity and whitespace checks pass.
Placement rescan is recorded in acceptance.txt. proof.py asserts strict receipts,
identical retained objects, the exact retail twin and paired finding changes.
Its ignored snapshots live in build/voice-record-link-20261015/{0,1,2}.

## Donor review and handoff

Reviewed BFME1 repairs `d5043e1658bdf46d39281a2e975e9e0145221555`
(rehome exclusive Coord3D definitions to exact inline emitters) and
`d003077f0b7ce97622adb7a53f1fe76653433c5c` (use the existing stream provider).
Their ownership principle applies; no donor code, address or layout is imported.
Official master fetched as `9f335a9e`; clean verified checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. The overdue freshness update
retains the previously recorded old-input full baseline blocker: 2806 of 2982
stale TUs remained after 21 minutes. The preserved verified inputs are used;
no unchanged multi-hour retry, pointer advancement or success stamp is claimed.

Remaining home findings: three NameKeyGenerator::KeyToBucketMap duplicate
methods; the Rva00395561 destructor COMDAT/selected-body pair; and unresolved
BfmeTmpCF constructor/destructor. These need independent repairs. High-ranked
AmbientLight, setDisabledUntil, string-record lookup and LoadPCAFile bodies
retain documented compiler-shape blockers and were not retried. name_globals
--dry-run found zero rewrites. No per-row data-back artifact was assumed.
