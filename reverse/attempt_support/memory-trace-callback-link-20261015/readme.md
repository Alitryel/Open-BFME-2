# Allocator trace callback owner repair

MemoryPoolInit stored its trace callback under the unresolved placeholder
Rva00031420Callback. GameMemoryBlockSlots already defines the rowed 12-byte
rva00031420 callback. Use that existing owner and remove the redundant pin.
No new function, symbol alias, address, layout, header or compiler flag is added.

## Target evidence and measured effect

Base commit: 8fa46beceaf66395c74f1c7b075e4d3778f7f242. The allocator constructor
at RVA 0x00033B90 has a DIR32 operand at RVA 0x00033D37 whose retail value is
VA 0x00431420. The existing provider row at RVA 0x00031420 forwards its const
char pointer argument to OutputDebugStringA and returns. Both declarations
use that same cdecl signature. The existing member offset/context evidence is
unchanged; this repair adds no class-identity or donor-layout claim.

Both consumer and provider were file-claimed before preparation. Published-index
fetch retained the equally current local snapshot. index-meta.json records
measurement a2839ea429 (2026-10-15 13:35), underlying census 5986a99448 and the
frozen index hash. The committed status snapshot at 4b7e7091c4 served only as
discovery evidence. No per-row data-back artifact or ranking was manufactured.

- Strict bounded preparation before and after, and the explicit ./build.sh
  pair gate, pass all 11 rows, three string literals and ten named imports,
  with no baseline or skipped references. Existing renamed funclets are
  verified through their parent EH graph. Both inputs have strict-current
  reusable receipts; these prove input currency, not a clean link closure.
- proof.py normalizes only the old callback spelling to the existing owner.
  All nondebug section bytes, flags, definitions, directives, symbolic
  relocations and external bindings then compare equal. It separately checks
  the constructor operand against retail, and proves the provider object is
  byte-for-byte unchanged. Data facts and findings are unchanged (zero).
- Paired in-memory previews refresh the same two explicit objects into separate
  copies of the frozen index. The consumer loses exactly one unresolved name
  (five findings become four); the provider retains its four existing findings.
  All other findings and existing variant findings are identical. The index
  hash remains unchanged. Ordinary link_check agrees with the remaining list.
- Legacy predicted LINKED bytes: 0 -> 0. Existing nonpadding bytes: consumer
  1,298, provider 49. New authored C++ bytes: 0. No closed-strict gain or
  executable-placement gain is claimed. No full link/census/nightly/boot runner
  was started, and census/status files were not changed.
- EH: one EXACT row, zero nonexact/missing/baseline use. Enforced data check:
  zero findings. Converged data check: eight addresses, zero second names or
  unjudged rows. Class gate, declared-definition check and pin consistency pass.
  No new variants are introduced; the old MemoryPool::_Init variant remains.
- Placement resweep: zero bodies and zero pins. Ledger consistency and diff
  whitespace checks pass. No verifier, baseline or whitelist edits.

Raw saved objects and parent source copies remain under ignored
build/memory-callback-link-20261015/before. Run proof.py from the repository root
with those snapshots, current strict receipts and the recorded index. To
recreate snapshots, prepare the base commit's two sources with the same verified
BFME 1 inputs, save the objects, then prepare the repair. JSON preserves the
measured results; the proof is session evidence rather than a portable gate.
The two ordinary link_check commands exit 1 because the units still have the
independent blockers below; all byte and scoped acceptance checks exit 0.

## Donor review and remaining blockers

BFME 1 verified checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d was
retained. The previous linking pass reviewed c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
for incidental-COMDAT suppression; that repair does not apply to this callback
identity. This pass inspected allocator-related paths and donor commit
a75be818dd863cb1ed8e9e9681b7e147f8dbc23b (unused stand-in pin removal): its
principle is applicable, but its allocator names, addresses and pins are not
transferred. The callback repair is established entirely by BFME 2's retail
operand and existing rowed provider. No matching named MemoryPoolInit or
GameMemoryBlockSlots donor unit was found in the current game/ tree.

The overdue BFME 1 freshness update is owned by the foreign live
file:reference/open-bfme-1 claim (codex-6bc6-20261008). No pointer or successful
freshness stamp was changed. This repair uses the last verified inputs.

MemoryPoolInit still lacks Rva000327D0Assertion and GeneralAllocator::rva000332D0;
its MemoryPool::_Init COMDAT and selected provider are proven wrong. The provider
still lacks the four globals g_00DE03E4, g_00DE03EC, g_00DE03F4 and g_00DE03F8.
These findings are unchanged and require independent evidence. Exact lists are
in link-after.txt. Broader closed-strict verification remains outstanding.

Model: gpt-6.1-sol.
