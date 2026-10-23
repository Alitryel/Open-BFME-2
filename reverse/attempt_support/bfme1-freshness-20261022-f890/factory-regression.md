# Publication integration prerequisite

The first publication attempt rebased the verified donor update onto BFME 2
`b5e4cb7fa80726a4d394f0750d53c30621b9247e`; the outgoing freshness commit became
`42803eed77`. Its ordinary full push gate refused one of 98,069 function rows:
`?rva00042036@Rva00042036@@QAEPAVRva000647B5@@XZ`, RVA `0x00042036`, 50 B.
Retail has `push 0x10` before operator new, but the compiled body had
`push 0x14`. All other function rows, string/float/import references, DIR32,
pins, module registry, source claims and all 2,131 data rows passed. The no-op
patch could not run because the function gate was red.

This was introduced by upstream `d0823bd581` after the fixed production
revision used for the passing donor pair. That commit replaced the factory's
8 B private SubsystemInterface with the canonical 12 B header, leaving the
4 B derived padding that compensated for the old undersized base. The donor
update changes no header involved here. The correct size is established by
the retail factory allocation: 4 B snapshot base + 12 B canonical subsystem
base = 16 B. Removing that redundant derived padding restores `push 0x10`
without changing the shared header or any field access.

Claimed the factory file and row before editing. Scoped byte verification and
`find_declared_unmatched.py` pass. `link_check.py --prepare-current` verifies the
explicit provider with a strict reusable compile receipt and ordinary byte
checks. The legacy published-index preview changes from 0 linked bytes before
the repair to 50 after it; the census's original 50-byte total is restored.
Logs are adjacent. This is a self-strict provider check plus legacy link preview,
not a closed-strict closure or census measurement. No new authored C++ bytes
are claimed. This repair is required to publish the already verified freshness
update after its integration rebase.
