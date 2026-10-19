# FXShaderGeometry::Init: provider identity and wrapper visibility

Native target: `0x0018C84E..0x0018D16B`, 2,333 bytes, RET 4.
BFME2 revision: `95f0f83963d7246d0dbb84f066914581fa07f7db`.
Reference checkout: the published `a18d9ed50607e9175de4d6568798d7d73119de09`.
The complete home `fxshadergeometry.cpp`, saved bank
`reverse/attempts/0x0018c84e.cpp`, and previous attempt evidence were read.
The existing bank is retained unchanged; no production source or pin changed.

## New target evidence

The possible signed/unsigned mismatch recorded by the previous attempt is not
established by allocator addresses alone. Native proxy bodies at `0x00007410`
and `0x0014F3C4` are identical over their complete 11-byte boundaries:
`8bc18b4c24088908c20800`. They are distinct addresses, not an ILT jump.
The current short proxy name is pinned to the former; the empty base needed by
Init calls the latter. Ordinary recursive fold admission must still resolve
that identity conflict; adding a second address is not a repair.

A direct E8/E9 byte scan, followed by verification of the sites in the existing
byte-verified caller bodies, finds the following chain:

- `0x00513FCB`, within `Rva00513ED1` (415 B), calls count constructor `0x00513DD0`.
- `0x00513DDE`, within that 51-byte constructor, calls base constructor `0x00513D55`.
- `0x00513D78`, within that 58-byte base, calls allocator `0x00017710`.

The complete caller is in `AptCreateAHeroDrawMapComponent.cpp`. It copies a
Unicode string into a two-byte buffer, filters filename characters through an
unsigned-short pointer, and sets the resulting Unicode string. This proves
the buffer width and usage. Its existing source spells `vector<short>` and
casts the data; the native operations do not distinguish that spelling from
an unsigned-short buffer. Thus they do not independently justify relabeling
the provider as `vector<unsigned short>`.

Allocator `0x00017710` has the rowed unsigned-short name, plus an existing
signed-short pin. The signed-short ledger owner at `0x000AD722` has a different
27-byte emitted body; `0x00017710` is 29 bytes. This is an existing candidate
identity problem, not evidence that a new fold alias may ignore other addresses.

## Controlled compiler and source trials

The official `explain_mismatch.py` reproduces the saved bank at exactly 2,333 B.
It reports the unresolved short empty-base constructor at offset `+0x473`.
The displayed disassembly has eleven differing instruction rows, including
that unresolved call; these counts are diagnostic, not verified-byte progress.

Six isolated trials are recorded in `results.json`:

- Authenticated `vc71-sp1` and `vc71-ddk-4035`: both 2,333 B and eleven differing rows.
- ZH `dx8fvf.h` location/normal/diffuse/stride accessor semantics: unchanged.
- Additional simple descriptor-view getters: unchanged.
- Replacing all direct mesh count reads with its existing count accessors,
  with either descriptor variant: 2,339 B and worse instruction layout.

No dead statements, volatile operations, extra pins or invented allocator
bindings were added by these trials. The saved bank's existing dead EH scope
was not promoted to production or represented as newly verified EH evidence.
The trial generator is preserved as `trials.py.txt`; diagnostic logs and
isolated sources remain in `build/resume-eh-local/turn47-fx-*`.

## Remaining work

Reconcile the genuine short empty-base/proxy ownership with independent
type/provider evidence before trying to admit its fold. The known normal-X
load ordering, two-bone read ordering and SIB operand differences also remain.
The tested compiler profiles and wrapper families provide no new improvement;
do not replay them unchanged. No exact match, new name, or new byte gain is
claimed by this handoff.
