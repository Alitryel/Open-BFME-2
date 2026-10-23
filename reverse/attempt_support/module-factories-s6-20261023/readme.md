# Module factory link closure

2026-10-23, astra-s6, gpt-6-astra. Light SureForge follow-up: two sources,
a bounded return-ABI correction, two single-entry tables, existing native
oracles and validation path. Research/plan: all tree callers of hasEntries
use the bool signature and native25-byte code returns0/1; no int consumer.
Native table contents and matched callback addresses inspected directly.

RVA004DF49C retained its exact25-byte implementation and identifier, correcting
only the return ABI from int to bool. A scratch bool compile first established
exactness. ledger_io removed exactly the old row; add_match byte-verified the
new row; deleted_rows prevents the retired signature returning via union merge.
This is a signature repair, not an identifier rename or an ICF alias. All three inline-assembly fragments were subsequently removed. Fresh-context
Devin GLM5.3 tried15 isolated variants under the original flags; unsigned
count > 0 emits the exact25 bytes, whereas count != 0 emits24 bytes with
test/setne. Owner scoped build independently confirms the landed ordinary
C++ implementation (build-clean.txt). No assembly or intrinsics remain.

VA00BF247C and VA00BF2534 each contain exactly32 bytes: one16-byte FieldParse
entry plus a fully null terminator. The entries are DelayTime / existing
INI::parseDurationUnsignedInt RVA00338B30 / null userdata / offset0x118 and
KillLocomotorUpgrade / existing INI::parseBool RVA0002E850 / null /0x118.
These arrays now have real definitions in the owning factory TU and data rows.

Execute checks: scoped owner1/1 and factory6/6 body rows match; both32-byte data
rows pass sizeof/bytes/literal and callback relocation checks. Enforced
data_check on both sources reports0 findings. Structural sweep found no other
int-returning declarations or duplicate table definitions. Source hashes and
native table bytes are retained. No tool, baseline, pin, whitelist or header edit.

Delivery preview: both units link against the published03:12 index491a8b3d87 and
again after refresh to06:28 index456ce161c5 (link-refreshed.txt);
owner25->25, factory0->212 bytes. This is an in-memory preview, not a new census
or linked executable. Normal commit/push hooks still apply. Keep this small
closure with other verified work for publication per batching policy.
