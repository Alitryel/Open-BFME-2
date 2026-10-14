# Sort-record destructor emission repair

At base `0fcec3b4026c0e39cecb0ab7df6787cf6b732166`, the LAN lobby's
outgoing-slot view of Rva000795C1Record emitted an unused one-byte empty
destructor. Link order selected it ahead of the WWLib sort units' actual
15-byte buffer cleanup. Keep the lobby's existing empty nontrivial view
inline-only using dllimport forceinline; its full sort-record cleanup remains
owned by the unchanged WWLib units. No new identity, layout, alias, pin,
compiler flag, header or ledger claim is introduced.

The full provider object comparison removes only the unreferenced `ret`
destructor. All 19 retained external COMDAT bodies, extents and relocation
digests match. Every other nondebug section and normalized relocation matches,
including exception data. Strong, undefined and weak external sets are equal;
no imported reference appears. All four consumer object files are unchanged.
Object hashes and index SHA256 bind the assertions in object-proof.json;
proof.py reproduces them from snapshots under build/linear-insert-link-20261014.

The paired legacy preview replaces the same five objects on both sides of
runner index measurement `147cfae2cb`, 2026-10-14 07:27 UTC. The committed
reverse/link_status.csv is a different measurement and was used for discovery
only. Three existing consumers become LINKS: Rva00580776LinearInsert (471B),
Rva00580E10SiftHeap (194B), and Rva00580C0EPopHeap (96B), totaling **761B**.
The provider remains LINKS (1085B). Rva005810B6Sort loses its destructor conflict
but retains its independent wrong-selected vector<unsigned> copy constructor;
it is not credited. Paired aggregate linkable bytes are 1085 -> 1846.
The CLI exits 1 for that remaining blocked consumer. Census/index/status are
unchanged. These are legacy local predictions: new authored C++ bytes are zero;
no executable placement, self-strict or closed-strict gain is claimed.

Acceptance: bounded strict preparation passes 26/26 rows across all five
providers with reusable current receipts, three literals and one empty-string
reference (zero baselined/skipped), and zero unverified imports. Ordinary
./build.sh passes the edited provider's 2/2 rows. EH verification passes
21/21 EXACT, zero baseline or missing objects. Frozen-definition, class and
new-variant admission checks pass; enforced data checks have zero findings;
converged data checks judge eight addresses with zero second names or unjudged
rows. Placement resweep finds zero bodies/pins. check_csv and diff whitespace
checks pass; hooks run normally.

An initial trial suppressed the destructor in the linear-insert consumer
instead. Its five main rows remained exact, but all five exception graphs
changed to an imported destructor call at retail unwind sites 0x79C818 and
0x79C844, and the local link check reported an unresolved __imp_ destructor.
The whole consumer attempt was restored and all its rows reverified before
snapshotting the successful cohort. This failure motivated removal of the
unused early provider instead; no failed source remains. A --refresh command
was stopped during stale-source discovery after inspection showed it would
expand to unrelated ledger objects. The accepted checks prepare explicit
sources and refresh only those same objects in memory, never the whole tree.

BFME 1 linking review: verified clean pointer
`a7c38d3b2597121f178ab5190b3062478823257d`; reviewed donor
`de59a7e9f891b3ed2d4221d151ca881f4b75a583` and its byte/link evidence.
Its reconciliation of incidental private COMDATs is applicable; Apt layouts
and predicate code are inapplicable and no donor source is imported.
Official master fetch returned `46dddb7d562a0c4d66f2618c13f134f2710257ba`.
The prior comparative full-gate compiler/cache blocker remains documented in
terrain-small-link-20261014/readme.md; the verified pointer is retained and no
freshness-success stamp is written. No unchanged full-gate attempt is repeated.
No maintainer-only census build/measurement/history, link cycle, nightly or
boot runner was started. Broader current-ledger closure/placement verification
and the independent vector-copy provider repair remain outstanding.
