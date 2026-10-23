# Shader copy ownership repair

At BFME 2 revision `ad83498efc76a6d2a501d3e45ff0de2608dcf439`, the
`DX8WrapperGetShader.cpp` consumer emits an unused external
`ShaderClass::operator=` COMDAT that differs from the first copy in link order.
`Get_Shader` copies one unsigned shader word. Copying that member directly
removes the competing helper without changing the operation or class layout.
No pin, alias, header or compiler setting changes.

## Evidence and acceptance

`context.json` records the measurement revision, index SHA-256 and metadata:
index commit `19a2565407`, census commit `5986a99448`. `proof.json` pairs genuine
before/after objects against that same index, refreshing only this consumer in
memory. The legacy preview falls from one COMDAT finding to zero, and existing
authored linked bytes rise from 0 to 13. No closed-strict gain or new authored
C++ bytes are claimed. The census and link status were not rewritten.

The complete matched 13-byte `Get_Shader` body and its relocation digest remain
identical. All other normalized nondebug sections, data, linker directives and
external bindings remain identical; only the unused 13-byte assignment helper
and its binding disappear. Neither object has a nondebug relocation to that
helper. `proof.py` reproduces these assertions with the scratch before object
in `build/shader-copy-link-20261015/` and the current object.

- `./build.sh Code/Libraries/Source/WWVegas/WW3D2/DX8WrapperGetShader.cpp`:
  1/1 row exact; string, float and import checks pass.
- `link_check.py --prepare-current` passes before and after, with strict reusable
  receipts; the after receipt hash is recorded in `proof.json`.
- Prescribed `link_check.py` reports LINKS, 0 -> 13 legacy linked bytes.
- `find_declared_unmatched.py`, `class_gate.py`, `link_check.py --new-variants`,
  `data_check.py --enforce` and `data_check.py --converged` pass.
- `eh.json`: no EH-bearing rows, no missing objects. A `place_bodies.py` resweep
  finds zero additional bodies or pins.

The existing target source and original Zero Hour `dx8wrapper.h` provenance
establish the word-copy operation. The target object comparison establishes
this repair independently. BFME 1 donor repair
`de59a7e9f891b3ed2d4221d151ca881f4b75a583` was reviewed for the related principle
of reconciling incidental inline COMDAT ownership; its Apt-specific helper is
inapplicable and no donor layout or code was imported.

Broader closed-strict placement remains unmeasured; no full link cycle or census
was run. BFME 1 freshness remains blocked on the reference scope held by another
worker and the existing baseline/dependency verification problem. The verified
pointer `a7c38d3b2597121f178ab5190b3062478823257d` was retained; official master
was fetched read-only at `9f6997d13`, with no success stamp or pointer advance.
The separate audio-cache false reject is recorded beside this evidence.
