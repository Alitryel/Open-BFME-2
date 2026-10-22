# addNewAIForPlayer: exact through per-path side-reference preparation

Recovered `?addNewAIForPlayer@Rva002A8F24@@QAEPAXPAVPlayer@@@Z`,
`0x002A9476..0x002A95B9`, **323 bytes**, including `ret 4`. Production source:
`Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAIManager.cpp`.
Unique recovered bytes: **323**. The accompanying 47-byte hash lookup row is an
already-covered ICF twin and contributes no additional unique bytes.

## Identity and input context

WorldBuilder `0x00E8E370` independently names `addNewAIForPlayer` and establishes
the team search, new-team fallback, side/dozer handling and collector creation.
Retail establishes the boundary, call targets, manager member offsets, Player
index at `+0x54`, side at `+0x58`, and AI flag at `+0x168`. See the
[earlier investigation](../002a9476-player-priority-20261020.md) and
[adapter investigation](../002a9476-inline-adapters-20261022/handoff.md).
Existing RVA-class and provider spellings are retained; this recovery does not
promote those private views into canonical class or donor-layout claims.
The bank's address-named army-manager global is replaced with the existing
`TheArmyDefinitionManager` declaration and a cast at the call site, preserving
the registered datum's actual name and pointer type.

Inputs: BFME 2 base `17aaebc9470f7b2e7656d59aedbf9dc4be143d7d`, BFME 1
`37c3022de1ab944c7ffe536440d637dc8199091c`, pinned MSVC 7.1 RTM,
`/O1 /arch:SSE /G7 /MD /EHsc`, with the home's existing STLport/shim flags.
The source flags and toolchain were not changed. Exact source, compiler and
object hashes, effective flags and every resolved relocation are preserved in
[full-verification.json](full-verification.json).

## The source change that closed it

The natural source prepared `&player->getSide()` once after team selection. It
emitted 332 bytes: `&teams914` won EBX instead of `player`. Two inline adapters
improved that to 325 bytes but left an extra `mov ecx,esi` before the found-team
AI lookup. Further adapter permutations did not close it.

The winning source uses direct calls and prepares the side **address** along
the existing paths:

```cpp
const AsciiString *side;
for (/* existing iterators */) {
    side = &player->getSide();
    if (/* existing team test */) {
        // Existing addPlayer and AI lookup; then break.
    }
}
if (!ai) {
    // Existing new-team construction, calls and push_back.
    side = &player->getSide();
}
// Existing army/dozer code consumes *side.
```

Every path that reaches the use assigns `side`: an empty/no-match loop takes
the new-team path; a found team with null AI also takes that path. The getter
only computes the address of a field. No string value is read early, so an
intervening call changing its contents does not make the later use stale.
The final object has one post-join `lea esi,[ebx+0x58]`, with no extra loop
instruction. Player is EBX, manager is EDI, iterator is ESI, and the end/team/key
temporaries share retail's stack slot. No adapters remain in production.

The inline-only `dllimport`/`__forceinline` getter view prevents this unit from
emitting a competing shared `Player::getSide` COMDAT; the final byte and linking
checks below include that declaration.

## Compiler observation and limits

A private Windows/WOW64 debugger traced the pinned C2 allocation records.
The natural baseline's player record had 8 references, cost 9 and priority 28;
the winning source had 9 references, cost 12 and priority 43. See
[allocator-summary.json](allocator-summary.json). These are decoded internal
record observations for this compiler, not a portable compiler contract.
The final disassembly proves that the changed source weighting survives long
enough to affect allocation even though repeated address preparation disappears.
The exact optimization pass responsible was not identified.

As a causal diagnostic on the older 325-byte candidate, changing just the
temporary receiver's selected register from ESI to ECX in a temporary compiler
process produced a 323-byte relocation-masked match. Its native preference
scores were ECX -1 and ESI -3. That diagnostic isolated the residue; its object
was never admitted, copied to the build cache or used as a verification receipt.
The recovered production object was compiled normally, without a debugger or
compiler intervention, and verified with all references resolved.

The reusable lesson is to test the placement of a real computation whose result
is consumed later, especially one suggested by register-use weighting. This is
not evidence that every allocation mismatch has this cause or that the original
retail source used this spelling. Prior failed adapter, lifetime, loop and
compiler-setting trials remain documented in the linked handoffs.

## Lookup ownership and verification

The real `hash_map<int,AsciiString>` emits a key-only `_M_find` whose complete
47-byte body at `0x002888D4` is identical to the already-rowed relationship-map
lookup in `PlayerGetRelationship.cpp`, with zero relocations.
[icf-proof.json](icf-proof.json) records the typed names, bytes and owner. Its
object hash identifies the private pre-admission proof object; the final normal
production object hash is in `full-verification.json`. `add_match.py --icf-owner`
admitted the twin; no symbol pin was added.

Final normal checks:

- `./build.sh Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAIManager.cpp`:
  **3/3 exact**, complete extents 135, 47 and 323 bytes; strings, floats and imports
  clean. Explicit strict resolution also reports no unresolved names.
- `tools/eh_verify.py` on the unit: **EXACT 1**, no baseline debt or missing object.
- `tools/find_declared_unmatched.py` on the unit: all definitions matched.
- `tools/link_check.py` on the unit: **LINKS**, row-byte sum 135 -> 505 against
  the published census index from `2026-10-21 21:42 UTC`, `e20daa4e78`. This is a
  scoped preview, not a new census or an executable/runtime test. The 370-byte
  row-sum increase includes the 47-byte ICF twin; unique recovery remains 323.

For isolated ordinary-compiler controls, copy [replay.py.txt](replay.py.txt) to
`build/` and run it from the repository root. It writes private trial objects
under `build/addnewai-side-replay/`, never the production cache. Historical
nonmatches are measurements, not recoveries; see [controls.json](controls.json).

The prior bank is removed by `add_match.py`; its source and earlier evidence
remain available at commit `3d5972685be231e777a80783689e4503cdc0ce45`.
