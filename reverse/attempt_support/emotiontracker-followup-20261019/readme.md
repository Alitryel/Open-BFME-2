# EmotionTracker parent and activation follow-up

The selector prerequisite at `0x004B13D8` is recovered separately in
`70626c5c0ee3ae2fd78392199a6516f35ea3330d`. Its tracked evidence is
`reverse/attempt_support/emotion-selector-20261019/readme.md`. This follow-up
preserves the remaining partial bodies and rules out unchanged retries. Neither
body described here is a production row or byte progress.

Inputs: parent tree `7a44bdd956`, then selector commit `70626c5c0e`; verified
reference checkout `b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`. Normal VC7.1 RTM,
`/O1 /G7 /arch:SSE /MD /EHsc`; the activation additionally retains its existing
ASCII/allocator shim flags. Authenticated `vc71-sp1` and `vc71-ddk-4035` trials
retained both bodies' mismatches. model=gpt-6.1-sol.

## Parent update, native 0x004B1633..0x004B1ECB

Read the two earlier parent handoffs before this one:
`0x004b1633-20261019-claude2.md` and
`0x004b1633-20261019-w6/readme.md`. Their boundary, WB `0x01230DD0`, real
multiple-interface receiver and corrected target flow remain valid. Native
ECX is module root+0x10; its data/object loads use ECX-0xC/-8. The retained
parent is still 2194 bytes / 659 instructions against 2200 / 661.

The only non-relocation difference is case 2's layer comparison, not the
earlier case-1 comparison. Native captures the owning object in EBX, calls the
other object's getter first, saves that result in the dead iterator home at
`[ebp-0x18]`, calls the owner's getter and reloads ECX before comparing:

```
mov ebx,[esi-8]; mov ecx,edi; call Object::rva0028B511
mov ecx,ebx; mov [ebp-0x18],eax; call Object::rva0028B511
mov ecx,[ebp-0x18]; cmp eax,ecx
```

The draft calls the owner first and saves its result in EBX, keeping the data
pointer there until then. Ordered helper variants get the call order but spill
the owner/result to new homes and widen the frame. `parent-alignment.txt`
records the complete retained mismatch; its other memory entries are absolute
relocations. No truncation, masking of unknown calls or assembly was used.

New trials covered the real WB status-bit predicate and its in/out-of-class
visibility; existing exact layer-getter visibility; actual getObject const and
nonconst overloads; case-local/direct data access; iterator scope and shared
cursor lifetime; direct/reversed pointer/reference receiver helpers and
reference-result helpers; actual nugget vector/type reconciliation; and both
authenticated compiler profiles. None closed this comparison. Already disproven
declaration-order and getter-spelling trials were read before selecting these
hypotheses. A complete selector definition in the same reconciled module also
leaves the parent unchanged. The selector's successful accessor/local-variable
repair does not transfer to this already accessor-based expression.

The bank now uses the actual nugget vector and the same root selector member
as the recovered source, replacing its former separate placeholder owner.
Already-rowed `EmotionNugget::OnDeactivation` replaces the old address-view
call. No new pin is needed for either. Activation `0x004DCC84` remains an
unrecovered provider, separately investigated below; the parent's six-byte
comparison discrepancy also still needs independent work. This is not a proven
compiler blocker.

## Activation, native 0x004DCC84..0x004DCE51

The whole prior attempt log was consulted, particularly entries 54404, 57821,
65007 and 65481. WB `0x010E9DF0` was reread, including its duration path at
`0x010EA085..0x010EA0FF`. It corroborates the positive forced-duration branch
and the zero-or-frame-plus-configured-duration ternary. The original BFME 1
donor is still the documented earlier revision; the same source at b3cc was
reviewed as a reference lead, not imported as a new target identity.

The old bank's measured full extent is **462**, not 461 bytes. Its remaining
non-relocation difference is:

```
native: mov eax,[eax+0xC]; cmp eax,edx; je zero; add eax,ecx
draft:  cmp [eax+0xC],edx; je zero; mov eax,[eax+0xC]; add eax,ecx
```

The obsolete `(object ? object : object)` condition artifact has been removed.
A raw member test after removal produced extra LEA/load/store instructions.
Using the existing deactivation sibling's real 19-word ModelConditionFlags
view at Object+0x10C, with masked-word `test(200)` / `set(200)`, restores the
native test/or instructions without that artifact. WB independently names
`BitFlags<591,ModelConditionFlagType>`; 19 words and bit 200 agree with the
native +0x124 / 0x100 accesses. Canonical ObjectID replaces the draft's int
getID result. The cleaned bank retains the old bank's alignment/score, with no
new field-name certainty claimed for the duration.

Const template return, owning-object accessors, frame placement, duration owner
value/reference accessors and frame-reference sum helpers did not close the
load. Staging configured duration in the real until member gives 460 bytes
(early store, missing native zero/jump tail); using that member in a subsequent
ternary gives 464 bytes with one extra early store. That diagnostic is retained
as `activation-member-conditional.cpp.txt` with its alignment; it is not the
bank and is not preferable production code. `/Ot` or `/O2` gives 518 bytes and
19 structural regions; `/Og-` gives 1118 bytes. SP1/DDK remain 462 bytes.

The bank's entire remainder matches apart from this duration region and the
resulting branch displacement shifts. No new Code file, pin, matched row,
extent change or compiler escape hatch is claimed for activation. The existing
4C-byte DelayedLuaEventList layout is retained; do not restore the duplicated
vptr from older banks. No fresh evidence justifies repeating the older named
duration/argument-reuse, volatile, equal-arm or arbitrary helper sweeps.
