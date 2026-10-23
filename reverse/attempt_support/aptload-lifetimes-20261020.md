# AptLoad native lifetime recovery, 2026-10-20

Base: 9e42834dd0a7dcab4052951565b6687e02d65ab3. Source:
`Code/Libraries/Source/Apt/AptLoad.cpp`; flags `/O2 /arch:SSE /G6 /MD /EHsc`.
No source or compiler-flag change was required for the recovered actions.

## Identity and boundaries

The native parent `?Load@AptLinker@@QAEXABVEAStringC@@V2@@Z` is at
0x006D1F80, 1525 bytes. Its installed handler is 0x007A86DD and FuncInfo
0x00962198. The other native parent
`?update@Rva006D1D10@@QAEXVRva006D07E0Key@@0@Z` is at 0x006D1D10,
615 bytes, with handler 0x007A8666 and FuncInfo 0x00962124. Both complete
parent EH graphs verify EXACT. `verified_funclet_locations` establishes
ownership, not adjacency or the packet's old ZH local label. The packet at
0x007A86AF belongs to AptLinker::Load, not AptLoadCountedOwner.cpp.

The source's existing assertion paths and callers establish AptLinker identity;
WorldBuilder supplied the original semantic guide. This pass adds no new claim
that the address-based private class names are original target type names.
Each action's 8- or 15-byte extent is its complete native tail jump or return,
confirmed by the native boundary inventory. The object reader reports the
remainder of the shared EH section for local labels; that is not the extent.
Each handler has its complete 10-byte compiler body and installed metadata.

Recovered: five 15-byte failed-allocation actions at 0x007A8638, 0x007A8647,
0x007A86A0, 0x007A86AF, 0x007A86BE; two 10-byte handlers; and native
8-byte EAStringC cleanup actions 0x007A8670 and 0x007A8680 replacing generated
scaffolds. Their direct providers are independent verified ledger bodies.
The 16-byte record's sized delete at 0x006D8680 is admitted as an exact
22-byte ICF alias of `?Rva006D8680Free@@YAXPAXH@Z`, with zero unique-byte credit.
The independent 70-byte constructor at 0x006D0790 and the exact parents'
16-byte allocations establish class ownership; every owner relocation matches.
The 96-byte allocation uses the already admitted F4-pool delete at 0x006F12F0.

## Remaining 11 scaffold actions: concrete provider prerequisites

| Actions | Actual compiler callee | Required target | Current emitted body |
| --- | --- | --- | --- |
| 7A8620, 7A8628, 7A8688, 7A8690 | `??1Rva006D07E0Key@@QAE@XZ` | A9DF3, 5-byte jump to A9822 | 36 bytes, inline decrement/destroy/free |
| 7A8678 | `??1BfmeRefVGO@@QAE@XZ` | A9822, 30 bytes | 34 bytes, inline decrement/destroy/free |
| 7A8630, 7A8656, 7A865E, 7A8698, 7A86CD, 7A86D5 | `??1Rva006D0790Ref@@QAE@XZ` | 6CD530, 35 bytes | 68 bytes, two nested inline releases |

All eleven remain in their original generated scaffolds. The first five actions
can reproduce their bytes using existing pins/rows, but the compiled destructor
copies conflict with retail. The last six fail with an unresolved REL32 to
Rva006D0790Ref's destructor. Their native tail jump is to 0x006CD530, already
rowed as `?detach@Rva006CD530@@QAEXXZ` in
`Code/GameEngine/Source/Common/Thing/Rva006CD530Detach.cpp`. That whole native
body calls Rva006CFDF0DecRef and Rva006D1210Destroy; the current destructor does
not match it and cannot be admitted as an ICF alias. The byte verifier correctly
rejects treating the 68-byte body as 35 bytes: a relocation beginning at offset
33 runs beyond that extent. Do not raise the native row's extent to hide this.

Current raw emitted bodies, with relocation fields zeroed:

- Key (36): `8b0185c0741dff087519568b318bcee8000000008b0d000000006a1c56e8000000005ec3`
- VGO (34): `568b3185f67419ff0e75158bcee8000000008b0d000000006a1c56e8000000005ec3`
- Link ref (68): `568b3185f6743bff0e75378b460485c07422ff08751e578b7e0485ff74158bcfe8000000008b0d000000006a1c57e8000000005f8b0d000000006a1056e8000000005ec3`

Reassessment: ownership/lifetimes and frame offsets are established by the full
native EH graphs; changing them would contradict exact parents. The obstacle
is callee visibility and separate inline/out-of-line forms, not an untested
cleanup control-flow guess. Current compiler settings already reproduce both
substantive parents exactly. Prior log evidence for Key (entries beginning
`link-repair: retail 0xA9DF3` and `false-reject link_census keep_rule`) records
that dllimport/forceinline retains inline bytes but leaves unresolved
`__imp_??1Rva006D07E0Key`, and member-wrapper trials alter parent code. Those
failed trials were read and not repeated. Their false-reject description is a
prior agent's hypothesis, not a finding of this pass. A real canonical type /
callee-visibility repair must preserve both parent's inline behavior and the
native out-of-line providers before these eleven actions can be converted.
No pin, source alias, exception or verifier change was used to conceal this.

`place_bodies.py AptLoad.cpp` returns zero additional bodies or pins. Before
this pass, link_check already reported both VGO and Key non-retail COMDATs and
wrong_selected Key, so the unit's linked-byte gain remains zero. Byte recovery
and linking are distinct results; this batch does not claim a link repair.

## Reference prerequisites

BFME1 checkout is the verified master pointer 0dc8a26a9c6041c73dc564754cd059dc54faa72a.
Official upstream fetched at 92f6bbe8e1dcdb46b5d27da0674313efc822b790. Its update
was already claimed by codex-b66d-indefinite, so this pass preserved the verified
pointer and did not mark freshness successful. Ranked BFME1 exact donors: zero;
near lead: 25-byte ArmorStore cleanup still requiring its native parent. Clean
Bfme5SixtyEight donor compile/place search: zero. ZH: 919 cached objects,
68 existing dependency failures; the only packet served was the now recovered
0x007A86AF action. No VP6 decoder source was consulted.
