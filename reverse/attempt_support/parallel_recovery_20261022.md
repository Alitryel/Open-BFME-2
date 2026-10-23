# Ten independent recovery investigations, 2026-10-22

Starting BFME2 revision: `3896cd69952cd7f195c4c2433487625179b01d29`.
BFME1 input: `37c3022de1ab944c7ffe536440d637dc8199091c`.
Trials used the repository's MSVC 7.1 command and isolated scratch objects;
no direct production-cache compilation, gate changes or assembly lifts.
Three workers ran concurrently. Production integration remained serialized.
All original banks were preserved: none of the failed probes was better.

## 1. Allocator, 0x00032050, 140 bytes

After reading the complete source packet and prior arithmetic/visibility trials,
tested memory-fence kinds in the existing bank. `_WriteBarrier` and the bank's
`_ReadWriteBarrier` give identical 140-byte bodies, 42 differing bytes, first
difference +0x46. `_ReadBarrier` is not an intrinsic in this compiler: it emits
an unresolved call and a 151-byte body. This is not a viable scheduling lever.
The already-exact first 70 bytes remain intact; native's later expression
association/register allocation is the outstanding prerequisite.

## 2. AIBuildableWallSegment::canMake, 0x00596E15, 218 bytes

Read the whole home TU, bank, all prior verdicts and four linked handoffs.
The additional hypothesis was that making only the existing cache store
observable would stop destructor-tail merging. A volatile cache member and a
volatile lvalue store both produce the same 204-byte baseline, with all
relocations resolved and 76 differing bytes. Native keeps a separate success
destructor and failure values in ESI; the compiler merges cleanup and uses EBX.
No improved candidate was established.

## 3. Small-gap inventory

No new credible tiny body beyond already-known entries. Useful ranges:

- 0x00564B0A: add ECX,12 then jump to shared empty constructor 0x0047A6A9;
  original containing owner remains unsupported.
- 0x0030C4C6: vtordisp adjustor with an unresolved hidden non-POD return ABI.
- 0x003ABCAD, 0x003ABCFC, 0x003ABD5B, 0x003ABDC0, 0x003AC243:
  deleting-destructor adjustors requiring folded-class reconciliation.
- 0x0001DA40: XOR AX,AX; RET, no established callable-owner/argument evidence.
- 0x00579674: INC EAX; RET, no proven register-input callable ABI.

Apparent other gaps were compiler/EH stubs or interior fragments, not bodies.

## 4. strlen, 0x007B9CCA, 24 bytes

Reviewed the previous 72-form search. Explicit intrinsic expansion with /O1 /Oi
is 17 bytes. Unsigned byte and inline nonvolatile load helpers keep /O1's
23-byte memory-compare pretest. A volatile inline helper gives a 22-byte rotated
loop; a reference helper gives a 17-byte loop. /O2 /Ot /G5 or /G6 produces
27 bytes with different registers and padding; disabling /Og produces 54-67
bytes. Native loads DL before LEA, tests DL and keeps an unaligned explicit
pretest. Neither signedness nor inline helper visibility resolves that policy.

## 5. Particle xfer adjustor, 0x003ABAB3, 8 bytes

The following is a **code-generation demonstration**, not a proven native
ObjectModule layout. It reproduces the native negative adjustment exactly:

```cpp
// cl: /O1 /G7 /EHsc /MD
class Xfer { public: void Version1(); };
class TrialPrimary {
public: virtual void gap(); virtual void xfer(Xfer *); char padding[20];
};
class TrialSecondary { public: virtual void xfer(Xfer *) = 0; };
class ObjectModule : public TrialPrimary, public TrialSecondary {
public: ObjectModule();
protected: virtual void xfer(Xfer *);
};
ObjectModule::ObjectModule() {}
```

`tools/variant.py <scratch.cpp> xfer 0x003ABAB3 8
'?xfer@ObjectModule@@MAEXPAVXfer@@@Z=0x00560AE1'` reports EXACT 8B for
`?xfer@ObjectModule@@OBI@AEXPAVXfer@@@Z`. Both bases must declare virtual xfer;
declaring it only on the secondary base does not emit the adjustor.

Integration requires more than relabeling the shared 21-byte callee. Native
references are particle secondary-interface references. Current 0x00560AE1 is
rowed with public nonvirtual QA spelling; the thunk needs protected virtual MAE.
Common/Thing/Module.cpp already defines a different unrowed MAE donor body.
Seven qualified callers and four particle constructor/vtable units also depend
on the current declaration/literal spelling. Neither this-independent shared
callee nor scratch names prove the original containing class.

## 6. MissileUpdate predicate adjustor, 0x004A7691, 8 bytes

Native constructor/vtable evidence establishes a stronger partial relationship:
MissileUpdate object+0x20 points to C53548, whose slot4 is false callback
0x005CB9FF; object+0x24 points to C53530, whose slot1 is adjustor 0x004A7691.
The complete adjustor is SUB ECX,4; JMP 0x005CB9FF. The callee is five bytes,
XOR AL,AL; RET4. Original callback and argument meanings remain unknown.

Under /O1 /MD /G7, a primary interface with four gap slots then virtual
bool predicate(int), secondary interface with one gap slot then the same
callback, and an overriding derived class returning false reproduce both
EXACT 8B adjustor and EXACT 5B callback. A class export/global instance retains
the adjustor; method-only export, novtable and member-pointer anchors omit it.
Pure gap declarations remove unresolved gap methods but do not avoid extra
constructor/vtable emission. Private special-member declarations suppress the
adjustor again. This scratch proof alone is not production-ready.

Follow-up compound-layout proof: the tracked diagnostic patch
`reverse/attempt_support/missile_adjacent_layout_20261022.patch` groups the
existing Base3 and Base4 views under an adjacent partial base. Its false
callback and adjustor are exact without exports, globals or new constructors.
Using the production source's actual /O1 /arch:SSE /G7 override, the existing
84-byte destructor, 28-byte deleting destructor and 53-byte projectile-fire
body also remain exact under resolved existing call bindings. Existing
MissileUpdate vtable symbol names remain unchanged.

This patch is **diagnostic only, not suitable for production**: the three pure
gap slots introduce __purecall entries where native C5354C/C53550/C53554 hold
real methods at 0x004A768A, 0x0049CB8A and 0x004A78B8. Those three providers
are already rowed under other partial views. Reconcile that runtime vtable
prefix before landing; exact function bodies alone do not prove vtable data.
Whole EH verification also remains. The original containing interface and
argument meanings are still unknown; no unrelated false alias is reused.

## 7. BFME1 clean-source compilation

Read and compiled clean WWMath color.cpp, icoord.cpp and
Matrix3D_Rotate_Vector.cpp, with Common/debug.h ahead of the different WWLib
debug interface. /O1 /G6: color emitted 10 symbols, nine matching shapes over
22 covered hits; icoord emitted 15 symbols, 14 shapes over 20 covered hits;
rotation emitted two symbols with no match. /O2 /G7 /arch:SSE: color three
shapes/three covered hits; icoord eight shapes/14 covered hits; rotation two
shapes/two covered hits. No unique unclaimed whole-body placements in either
profile. No lifted machine-code bodies were treated as recovered C++.

## 8. Zero Hour compilation expansion

Expanded bounded compile sampling from seven to 103 cached objects. Refreshed
match/packets: 2,839 functions; 146 exact unique placements (6,806 bytes) already
claimed; 122 ambiguous multi-hit placements (5,756 bytes); 517 near results
(38,808 bytes); zero conversion packets. Forty-one near addresses were already
covered. Multi-hit helpers do not establish a new carrier identity.
Remaining compile prerequisites include DirectSound, generated shader headers,
Miles AIL declarations and SDK synchronization declarations. No header or gate
substitution was made to conceal these failures.

## 9. Erase forwarder, 0x004643C9, 5 bytes

Independent native entry after RET at 0x004643C8 and before the next prologue
at 0x004643CE. It preserves ECX and forwards the key reference to already-rowed
0x00463D9B, whose ABI returns a count in EAX and RET4. Original set/multiset
wrapper identity remains unknown. An address-derived wrapper using the existing
opaque key/tree view is exact, without pins or aliases. Production whole-file
verification and link preview passed; the file's exact bytes grow from 73 to 78.

## 10. Packed color expansion, 0x000ABC43, 46 bytes

Complete native extent is PUSH EBX through RET. Arguments are destination
pointer and a 16-bit value on the cdecl stack. Native's partial-register
SHL BH,3 / MOV AX,BX sequence is not reproduced by the new clean-C++ probes.
Five union byte/word variants under /O1 or /O2, /G6 or /G7 and /Ob0 produce
59-74 bytes: the byte shift and word splice spill through stack unions.
Three scalar narrowing/mask variants produce 53-63 bytes. All differ from
the first byte; none is a better candidate.
Native also preserves input bit15 into output bit24, so describing it as an
ordinary RGB555 conversion requires an additional input-domain assumption.
