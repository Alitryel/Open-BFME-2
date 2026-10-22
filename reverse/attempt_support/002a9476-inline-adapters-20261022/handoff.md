# addNewAIForPlayer: retail register layout recovered; one copy remains

**Resolved:** the [subsequent recovery](../002a9476-recovery-20261022/recovery.md)
closes all 323 bytes with ordinary C++, without these adapters. The text below
records the earlier partial result. Its bank was removed on recovery; for the
historical replay, restore `reverse/attempts/0x002a9476.cpp` from commit
`3d5972685be231e777a80783689e4503cdc0ce45` into an isolated checkout at that commit.

Partial, not a recovery. Target `0x002A9476..0x002A95B9`, 323 bytes through
`ret 4`. The replacement bank is `reverse/attempts/0x002a9476.cpp`.
It emits **325 bytes / 112 instructions**, against retail's 323 / 111.
No production source, ledger row, pin, compiler or verifier changed.

## Starting evidence

Read the complete RVA attempt history and these earlier handoffs first:

- [Player-priority investigation](../002a9476-player-priority-20261020.md),
  including its complete source attachment.
- [Earlier bank investigations](../bank-investigations-20261018/readme.md).

The October 14 bank had an equal-arm `end ? end : end`, stale `addPlayer`
spelling and an unsigned-key reference cast. The October 20 natural candidate
resolved those source problems but emitted 332 bytes: `&teams914` occupied EBX
instead of `player`, and the extra home prevented retail's stack-slot sharing.

## New causal observation

In the successful allocation variant, adapt **both** calls in the found-team
branch through ordinary inline functions:

```cpp
__forceinline void joinTeam0(AIGameTeam *t, Player *p)
{ t->addPlayer((const ModuleData *)p); }
__forceinline void *getTeamAI0(Rva004E9600 *t, Player *p)
{ return t->rva004E95D4(p); }
```

The branch calls `joinTeam0((AIGameTeam *)*it, player)` and then
`getTeamAI0((Rva004E9600 *)*it, player)`. The new-team branch can keep its direct
calls. These helpers perform the existing operations; they are not retail
identity claims. They add no logical operation, volatile access, barrier,
redundant condition, inline assembly or synthetic store.

| Found-branch adapters | Emitted bytes | Retail player/this/iterator allocation |
| --- | ---: | --- |
| Neither | 332 | No |
| Join only | 329 | No |
| Lookup only | 333 | No |
| Both | 325 | Yes |

With both, player is EBX, this is EDI, and the iterator is ESI. The end/team/map
key temporaries share `[ebp-0x10]`, and AI reuses the dead player argument home
`[ebp+8]`, as in retail. The effect also reproduces in the **current complete
home unit**, before its snapshot method or at the end; it is not dependent on
the historical attachment's old TU contents.

The saved candidate also replaces the earlier diagnostic one-byte `DozerElem`
with `hash_map<int, AsciiString>`, the value type supported by the returned
`AsciiString &` and WB evidence. That type repair leaves the instructions
unchanged. Other private class views remain those of the existing home; this
is not a canonical-header reconciliation.

## Exact residue

At retail offset `+0x44`, before the second found-team call:

```text
retail:  mov ecx,[esi]; push ebx; call rva004E95D4
ours:   mov esi,[esi]; push ebx; mov ecx,esi; call rva004E95D4
```

The extra `mov ecx,esi` is at object offset `+0x47`. All subsequent relative
branches shift consistently by two bytes. `align_diff.py` reports one
structural region, size delta +2. The other two memory differences are the
unresolved object DIR32 slots for the two globals; they are not layout deltas.

Strict verification still fails. Besides the real copy difference, the signed
`hash_map<int, AsciiString>` `_M_find` name has no admitted target. Native calls
`0x002888D4`; all 16 other call sites have the expected target among the
ledger's candidates after accounting for the two-byte insertion. Admission
still needs a complete fold/provider proof, not a guessed extra symbol pin.
The [proof](proof.json) preserves full raw disassembly, hashes, unresolved name
and call targets. No relocation-masked result is represented as exact.

## New controls ruled out

- Pointer copies/reference aliases of player; receiver reference aliases;
  iterator/receiver views, loop order/increment/while spellings.
- Adapter subsets, call sites, depths 1..4, member versus free functions,
  argument order, player/receiver reference parameters and return locals.
- Typed team vectors, actual map-lookup body visibility before/after the
  caller, actual current home context and placement.
- Meaningful duplicated completion paths and extracted scan/join helpers.
  These generally change the loop/AI lifetime or increase the extent.
- Member-function pointers, nested reference adapters, aggregate argument
  contexts, argument-only player views, inline/import/static/export modes.
- RTM, SP1 and DDK4035; CPU settings, optimization/inlining settings, the
  inline-only vector begin/end recipe and declaration-only push_back.
- Typed callee argument diagnostics, source parentheses, register qualifiers
  and the non-null contracts asserted by WB. No identity change was made.
- A bounded 150-unique-source permutation search on the improved current
  home produced no gain. Repeating it unchanged is not a new hypothesis.

The WB-only call at `0x00E8E76B` goes to the debugging helper at `0x00E8EA90`
which loads `AddPlayerForDebugging` with `GetProcAddress`. Retaining its
retail-empty inline stub did not change allocation; it is not the missing use.

The next investigation should explain why the found-team lookup receiver
becomes a global ESI-valued inline temporary instead of a direct ECX load,
while retaining the now-correct player web. The previous broad player-priority
problem is no longer the only available starting point. This does not prove
that ordinary C++ cannot express the final choice.

## Reproduction

Use [replay.py.txt](replay.py.txt) from the repository root, copied under
ignored `build/`, to reproduce the four causal controls with the ordinary
compiler. `align_diff.py` on the bank supplies the full-span instruction diff.
The trial fitness was 0.93762 using `variant_search.Scorer`; it is a blended
search metric, not a percentage of exact bytes. Normal full-extent, identity,
relocation, EH and linking checks are still required before landing.

Inputs: BFME 2 `17afe9c099a1c6ca313ff15a752b401c90b8c6bb`, BFME 1
`37c3022de1ab944c7ffe536440d637dc8199091c`, pinned MSVC 7.1 RTM;
`/O1 /arch:SSE /G7 /MD /EHsc`, STLport and the current home's shim flags.
Approximately 30 minutes of investigation; model Codex (GPT-6 family).
