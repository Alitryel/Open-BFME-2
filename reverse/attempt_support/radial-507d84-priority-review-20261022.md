# Radial action: allocator ordering evidence and corrections

RVA `0x00507D84` remains a 924-byte bank with 36 differing non-relocation
bytes. This note records compiler evidence, not a recovered function.

Inputs:

- game.dat SHA256: `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`
- retail body SHA256: `15c4af7f237a773e53b4d7761ccbe6b5fd44b0298e34e6d0dfdf35c42410e0f5`
- bank source SHA256: `e35afd0cc770e7f19d6a80a38b0048b2cce52a227cb17777393bcfed2282d74f`
- unmodified bank object body SHA256: `28329e0f2a50ec79f29a84ecf29570c8353bf94cad5bd9e987d25ae9e9b396d5`
- MSVC 13.10.3077 c2.dll SHA256: `bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`

## Observed records

The successful native observer log is `t9b.log`, not the failed `t9.log`.
At named record visits 64 and 65, `_obj` has index 6, w9=13, w3=59,
cost=21; `_position` has index 9, w9=9, w3=59, cost=18. Object is visited
first. The report's attribution of a preceding 26-record traversal to a
constructor was wrong: the function marker identifies the radial function.
Several traversals occur; a global pass counter alone does not establish
the first coloring phase for a particular source symbol.

## Equal w3 does not imply stable insertion order

Independent disassembly of the unchanged compiler proves a second key.
Addresses below are c2.dll RVAs, not game.dat addresses.

```text
00082B3A 8B4F0C       mov ecx,[edi+0x0c]   ; existing primary key
00082B3E 8B700C       mov esi,[eax+0x0c]   ; new primary key
00082B41 3BF1         cmp esi,ecx
00082B43 7F11         jg  00082B56
00082B45 7407         je  00082B4E
00082B4E 8B4844       mov ecx,[eax+0x44]   ; new secondary key
00082B51 3B4F44       cmp ecx,[edi+0x44]   ; existing secondary key
00082B54 72F1         jb  00082B47
00082B56 897814       mov [eax+0x14],edi
00082B59 894718       mov [edi+0x18],eax
```

The continuation at `0x84BBA..0x84BD2` compares the same keys while walking
the list. Its tail at `0x8799A..0x8799A+12` compares `[ecx+0x44]` against
`[eax+0x44]` with unsigned `jbe` to insertion. Together these paths order by
descending signed w3 (`+0x0c`), then descending unsigned w17 (`+0x44`).
A new record can be inserted ahead when both keys are equal; this is not
stable FIFO insertion. The meaning and writer of w17 remain unproved.

The original record summary did not capture object and position w17 together.
Consequently it does not explain why object wins, and does not prove that
position's w3 must exceed 59. Capture both secondary keys, their writers and
the exact function/phase before deriving a source transformation.

## Diagnostic boundaries

An in-loop sink and a prologue sink changed the recorded priorities in
opposite directions. Two controls do not prove that only loop changes can
affect the decision. Alias/address spellings tested so far emitted the same
body; output equality alone does not prove pre-count folding or unchanged
priorities. This is a bounded negative, not a proof over all equivalent C++.

The implementation worker also forced a priority byte in a private compiler
process, outside the original observation-only instruction. That object is
quarantined: it is not a source candidate, shared-cache object, admission
receipt or recovered match. Its non-relocation equality is insufficient to
prove all relocation identities or exception data. No production change or
credit uses it. Further work must use the unmodified compiler; observation
must reproduce ordinary object bytes.

Local reproducible artifacts are retained under ignored
`build/rea-campaign-20261022/radial_trace_round2/` and
`build/rea-campaign-20261022/radial_priority_review/`. The latter independently
checks full body extents and disassembles the ordering routine. This note
supersedes the first report's insertion-order and necessary-priority claims.
