# Exact collision axis-list sort

`?rva007586F0@CollisionManagerImpl@@QAEXXZ`, native
`0x007586F0..0x007588BC`, 460 bytes. Recovered from the existing bank under
`reverse/attempts/0x007586f0.cpp` at BFME2 input `806076fdec`; verified BFME1
pointer `37c3022de1ab944c7ffe536440d637dc8199091c`. MSVC 13.10.3077,
`/O2 /G6 /DNDEBUG /MD`, model gpt-6.1-sol, about 35 minutes.

The native UpdateSort caller (0x00759600), endpoint accesses and identical
optimized WorldBuilder body (0x01802EC0) support a bottom-up linked-list merge
sort over each collision axis. Endpoints are 20 bytes; the four temporary
list records contain head, tail and unsigned count at offsets 0, 4 and 8.
These are target structural findings. The original method and local type
names remain unknown, so the existing neutral method name is retained.
The prior bank and its provenance remain available at the input revision;
no new donor-source identity or original volatile declaration is asserted.

## Prior exclusions and new hypothesis

Read the 20261021 handoff, profiles and 20261022 alias handoff before editing.
They already covered declaration ordering, pass-loop forms, list accessors,
aggregate ownership, flags, authentic compiler versions, layout and lifetimes.
This leaf body has no missing callee. Its best bank emitted 460 bytes with
33 different positions: B used `lea ebx,[edi+0ch]`, whereas retail computed
`lea ebx,[esp+eax+38h]` next to A. Independent `B = &lists[src + 1]` got that
address but rotated registers and emitted 470 bytes. Full COFF extent was
checked separately from row-sized scoring throughout.

The new hypothesis was to change the costs of existing accesses, rather than
their index spelling or declaration order. An accessor/comparison factorial
tested 1,280 variants without improvement. A separate address-preparation and
branch-duplication family tested 456 valid variants without improvement.
`results.json` records compact counts and winners; the generators preserve
the choices without thousands of trial artifacts.

Read-only C2 traces showed a single reference contribution of 72 moving from
A to a synthesized address temporary when B became independently indexed.
At candidate-list insertion, return site `0x1078474f`, A (backend symbol 13,
candidate 13) changed priority 32 to -40 and refs 7 to 6; temporary symbol 279,
candidate 27, changed priority 240 to 312 and refs 6 to 7.

A **diagnostic-only** debugger edit restoring A's initial priority to 32
closed the body. Editing only the temporary's priority did not. Those objects
were isolated in ignored build scratch and were never admitted to the ledger,
normal cache or verification. `trace.py.txt` clearly marks these controls.
The debugger helper is adapted from the earlier a9f98 C2-key investigation.
`allocator.json` preserves compact initial insertion records.

## Source closure

A 576-variant family independently qualified existing count reads, indexed B
and endpoint value reads. Variant `qual-0321` matched exactly with unmodified
MSVC: B is `&lists[src + 1]`, and only the two A-count tests use an inline
volatile-qualified unsigned read. No memory access or artificial use was
added. A later member spelling is equally exact:

```cpp
unsigned int getCount() const volatile { return count; }
// ...
while (A->getCount() != 0)
// ...
if (a != 0 && A->getCount() != 0)
```

Nine equivalent accessor spellings integrated into the current home unit all
matched. The landing uses the member accessor, with the same two stack count
loads and merge logic as retail. A read-only trace of this unmodified winner
puts A at priority 24, refs 6 (instead of -40): it crosses the ordering threshold
without recreating every intermediate allocator statistic. Volatile here is a
source adaptation for compiler costs, not a target type-identity claim.

## Acceptance

- `add_match.py` ran the ordinary `./build.sh` gate: 2/2 bodies, 1,704 bytes,
  including the existing 1,244-byte UpdateSort. String, float and import checks
  passed. The 460-byte leaf has no relocations or exception handlers.
- `verification.json` records the ordinary shared-cache object's source/body
  hashes. Full COFF body extent is exactly 460, equal to all retail bytes.
- `find_declared_unmatched.py`: all defined functions already matched.
- `check_csv.py`: passed after staging the deleted bank (the tool enumerates
  tracked attempt paths). No baseline, whitelist, pin or gate change.
- `link_check.py --fetch-index` reused the published index; scoped link preview
  reports LINKS, 1,704 bytes. This is a preview, not a new link census.
- `place_bodies.py` rescanned the home unit: zero additional bodies or pins.

To reproduce the searches, copy the `.py.txt` files into ignored build scratch,
remove `.txt`, and adapt ROOT/OUT. `search.py` obtains the old bank from the
recorded git revision. `trace.py` expects the derived-control source generated
in that scratch directory; run only in a separate output directory. Ordinary
build.sh verification, not debugger controls, is the landing authority.
