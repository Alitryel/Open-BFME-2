# Construction UI team accessor link repair, 2026-10-15

The private const Object::getTeam definition in
Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp
emitted an unused seven-byte COMDAT that differs from the first copy in link
order. Imported forceinline retains the established caller access and suppresses
that competing definition. No import reference is introduced. No layout, type,
name, boundary, compiler flag, header, global, pin or ledger extent changes.

## Paired measurement

Checkout before repair: 6cd7818d389188c49815fdc19fe1b4372b441c60.
Runner index receipt: a2839ea429, 2026-10-15 13:35; original census
5986a99448, 2026-10-15 04:52. Its unchanged SHA256 is
c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37.
The committed status report measures a different revision; no status was changed.

Both objects were prepared using link_check.py --prepare-current. The paired
proof refreshes each object separately into the same index in memory. It removes
exactly one COMDAT finding, leaving all other findings identical. Remaining
copies have identical keep/loss decisions and kept body facts. All 68 retained
COMDAT bodies and all other nondebug section bytes, flags, relocation targets,
external/weak bindings and data facts agree. No retained section references the
removed definition. Source/object/receipt hashes and complete findings are in
proof.json. Local strict-current receipts establish the object inputs; the
legacy link prediction remains 0 -> 0 bytes. No self-strict or closed-strict
executable gain is claimed; new authored C++ bytes are zero. No full link cycle
or census was run.

## Acceptance

- ./build.sh: 12/12 rows exact; six literals, floating constants and imports pass.
- Strict receipt preparation before and after: 12/12 exact each.
- EH before and after: three EXACT, no baseline or missing objects.
- Frozen-definition check, class gate, check_csv and new-variant check pass.
- Shadow data: three pre-existing findings, including two wrong names outside
  the baseline; paired data facts unchanged. Enforced converged data: eight
  addresses, zero second names and zero unjudged rows.
- place_bodies: zero bodies, zero pins. git diff --check passes.

## Provenance and handoff

Existing target-matched callers establish the retained field access. No new
standalone getter identity is asserted. BFME 1 commits
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 and
66b19a8e95a4add525ef808fcea088e306798e2b were reviewed for this established
emission mechanism; no donor types, layouts or identities were imported.

The unit still needs ControlBar::rva0031D230 and has ten allocator/vector COMDAT
conflicts plus two selected-provider findings (complete list in proof.json).
Those need separate repairs; suppressing this getter does not resolve them.
The BFME 1 pointer stays at verified a7c38d3b2597121f178ab5190b3062478823257d.
Official master fetched as 95eeb3bef370a7cd730b0ad5f228c317c8756e72; another seat
owns file:reference/open-bfme-1, so no pointer update or success stamp was made.
