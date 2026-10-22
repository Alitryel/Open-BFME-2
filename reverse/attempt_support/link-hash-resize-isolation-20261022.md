# Isolate unresolved bucket-resize providers

Base25074ab48a, census e20daa4e78 (2026-10-21 21:42); BFME1 donor
37c3022de1ab. This follows the donor lane's separation of exact leaf
providers from unrelated template-instantiation debt. No BFME1 layout or
linking result is substituted for BFME2 evidence.

Before: stlport_hash_map_int_rva0029e067.cpp (194 nonpadding bytes) and
stlport_hashtable_asciistring.cpp (188 bytes) both legacy0B linked. Their
only live blocker is a wrong kept hashtable::resize copy. The int pin is
53F1EC (184-byte Armor owner); the two-word AsciiString pin is16DD70.
Neither instantiation reproduces its pinned resize body. Source identities
and layout evidence are retained from the existing verified rows.

Narrow the int unit to _M_new_node, which retains its rowed pair copy,
placement copy and compiler EH handler. An adjacent AsciiString lookup split was tested too. Move the integer insertion
row unchanged to its _deferred.cpp unit with original flags and dependency view.
Declare resize there rather than emit a second nonretail definition. The moved
insertion body still matches exactly. No insertion or resize recovery is
claimed: a current resize provider is still missing.

Accepted after: the integer unit legacy0->121B linked. Its deferred unit is
absent from this census and receives no link credit. Normal byte verification
and new-variant checks pass. Strict reusable preparation passes5rows across2units.

The AsciiString trial also passed2/2 bytes and previewed0->70B, but the commit
class gate correctly refused a new private AsciiString definition beside the
canonical header. This existing view is8bytes (see native facts in the original
source); isolating it requires real class reconciliation. That split is restored
and preserved only as link-ascii-map-isolation-20261022.patch.txt; zero credit.
The earlier trial log saying70B now links is superseded by this verdict. This is legacy
preview evidence, not a self-strict or closed-strict link/runtime claim.

Checks: ./build.sh stlport_hash_map_int_rva0029e067 (5/5), ./build.sh
stlport_hashtable_asciistring (2/2), link_check --new-variants on all4units,
find_declared_unmatched on all4trial units, check_csv, plus commit hooks.
Final accepted scope rechecked on the integer units only. Logs
build/link-helper-three-before.txt, link-hash-two-after.txt,
link-hash-two-variants.txt and link-hash-two-prepare-after.txt.

Next prerequisite is real bucket-resize provider reconciliation while keeping
callee visibility and exception cleanup shape, not repeated declaration
suppression. The science-vector sibling has a detailed existing EH/swap
bank at reverse/attempt_support/link-seat-20261020/science-hash-resize.md.
No new aliases, pins, baselines, or verifier changes.
