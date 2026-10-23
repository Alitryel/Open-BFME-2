# AimWeaponBehavior update: historical near-match evidence

Superseded by the verified recovery in commit `f3eade866d` at
`Code/GameEngine/Source/GameLogic/Object/Behavior/updateRva0045B297Farm.cpp`.
The stale banked candidate has been removed; the notes below preserve the earlier
trial evidence and do not describe pending recovery work.

Target RVA `0x0045B297`, 516 bytes, RET at `0x0045B49A`; next entry `0x0045B49B` is a separate float helper. Native constructor `0x0045B226` installs VA `0x00C418C0` at module+0x10; slot0 points to this entry. Interface receiver reads Object at -8, ModuleData at -0xC and aiming byte at +0x10. Named factory, pool and constructor support the owner independently of the donor.

Semantic donor: Open-BFME-1 `fcbee55c91adafaddd080cf086fe393cda8dea5c`, `game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorUpdate.cpp`; source recovery commit `40d4eacdf7`. Donor570B is a semantic guide; BFME2 offsets, virtual predicate, condition indices and consolidated drawable notification differ. The bank is a substantial target-specific reconstruction, not a byte claim. Estimated score0.9 describes believed semantics, not verified retail coverage.

Parent compiled the complete const-getter candidate through `tools/explain_mismatch.py` with RVA/size/source, under Wine11 and `/O1 /arch:SSE /G7 /DNDEBUG /MD /GX`. It emits516B; first byte difference+0xAF (RVA45B346). x87 multiplication/SSE spill/outgoing argument scheduling differs. Denominator liveness causes low-threshold XMM2 versus native XMM1 and conditional post-notify reload versus native common reload. No exact match is asserted, no row was added and no provider integration was measured. The bank has only comment/include-path changes from that tested candidate; verify again before adoption.

## Corrected target contracts

- Pitch masks in Object word5 at+0x120 are0x40000/0x80000/0x100000: condition178/179/180. Near/far181/182 are distinct. All five are cleared together. The worker erroneously conflated these sets and indexed a19-word array by mask>>5; the bank fixes that error.
- Native near branch calls clear182,set181; far branch clear181,set182. Constructor temporaries are evaluated right-to-left. Earlier worker evidence reversed clear/set.
- Clamp picks10.0 when10.0>horizontal, elsehorizontal. Native float bits at VA0x00BC2428 support10.0.
- Existing current-weapon provider0x0028AEBD is const Object, returns const Weapon*, and takes an optional OUT-slot pointer. Null suppresses OUT write; it does not select PRIMARY. A const_cast only permits calling the already-owned nonconst Weapon predicate.
- Native sqrt products/sum are x87 fld/fmul/faddp then fstpQWORD argument; there is no witnessed float rounding store of each product or sum. Double return narrows to float at the subsequent fstpDWORD.
- AI virtual call is slot111/+0x1BC, bool const contract already in AIUpdateInterface provider views. It does not prove all dynamic instances call RVA0x00262D8F.
- Single-bit constructor0x0028F59A and five-bit method0x000B6253 use76-byte/19-word buffers. Other existing providers: Thing folded getter0x005508E2, Weapon predicate0x002C9586, sqrt import0x0062921C, Object notify0x0028AE6D, two-mask method0x0028CFB2, clear-mask0x001E42F2, Drawable apply0x00274176. No new pin is needed.
- Partial class views and differing base spellings do not prove vtable/COMDAT linkage. The old claim that the constructor emits no vtable is unsupported. Reconcile with the constructor unit and check provider integration before landing.

## Measured trials: avoid unchanged repetitions

| Shape | Emitted extent | Result |
|---|---:|---|
| Combined predicate expression, before snapshot repair |501| Different bool spill/register shape |
| Separate bool OR, coordinate snapshots and correct masks |516| First difference+0xAF |
| Correct real const getter declaration |516| Same+0xAF |
| /G6 or/G5 |516| Same+0xAF |
| No explicit sqrt double cast |516| Same+0xAF |
| Original donor three separate pitch branches |516| Same+0xAF |
| Ten initialized before coordinate loads |513| Size mismatch |
| Denominator copied after divide through chosen pointer |516| FrameB8 instead of nativeB4, first difference+5 |
| Scalar deltas retaining separate snapshots/subtractions |498| FrameAC, first difference+5 |

Original OpenCode SpaceBunny handoffs were uncompiled proposals; parent rejected semantic mistakes and ran the public compiler tool. Its follow-up scalar direct-subtraction proposal was not tested separately; the measured498B row is the parent snapshot variant. Parent did not use asm, volatile, new aliases or verifier exceptions. Neither proposal nor bank earns recovered-byte credit.
