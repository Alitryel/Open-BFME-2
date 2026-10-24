# BFME1 reference freshness, 2026-10-24

BFME2 comparison revision: 6958a56410. Previous clean, committed and verified
reference: f5140c1cff6a58e16276fd6de6788186286953d4. Fetched official
Open-BFME/Open-BFME-1 master: 32774ab03393709a7f14331ba8d98d281a55ffd9.
The checkout had no private or dirty work. No layout migration was needed:
BFME2 already resolves game/ and inputs/reference/, and the intended engine,
ZH include and toolchain directories were checked on disk. lift_lane.py exists
at both revisions. No changed donor C++ is directly included by a BFME2 unit;
the update changes no headers, toolchain inputs or tools.

Old-pointer ./build.sh: FULL GATE OK, 98200 function rows, 2179 data rows,
6419 named imports, source claims and every other full gate check passed.
The new-pointer build starts from the identical BFME2 source and ledgers.
New-pointer ./build.sh also passed FULL GATE OK: 98200/98200 function rows,
2179 data rows, 6419 imports and all remaining checks. Both gates exited zero;
there were no pre-existing failures or update regressions. Source and ledgers
remained identical throughout the paired comparison. The success stamp was
updated only after the second full gate completed.

Reviewed donor linking changes through 32774ab03. GeometryInfo's shared record
declaration is already inherited; prerequisite record splits need a BFME2
identity correction before transfer; PeerDefs' Unicode placement suppression
is not its remaining integer/AsciiString insertion blocker; inline compare and
topple emptiness repairs are local donor leads. No unsupported implementation
was imported.

Refreshed bfme1_sweep.py scan/ranked/near and lift_lane.py --limit 1000.
The scan independently reproduced 5516 established boundaries. ranked serves
zero byte-identical unclaimed donor files. This does not exhaust reusable
reference source and does not replace the dedicated link-repair queues.
