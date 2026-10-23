# canMake: remove the unreachable zero-copy preference

Recovered `AIBuildableWallSegment::canMake`, retail 0x596E15, all 218 bytes,
with its exact EH graph, 10-byte handler at 0x79D381 and 8-byte unwind cleanup
at 0x79D379. The cleanup comes from the parent's own object, replacing the
anonymous `gen_uw` row without changing its generated source.

## Identity and inputs

WorldBuilder's named twin 0x15386C0 and retail vtable slot 16 establish the
parent's identity. Retail establishes the start ID at +0x4C, money access at
+0x94, cached cost at +0x54, Object position at +0x38, and the quote call at
virtual byte offset 0x50. The already matched quote-record constructor and
destructor establish that record's layout and lifetime. The opaque declarations
do not establish complete target classes or original source spelling.

BFME 2 started at 663a013fb8. BFME 1 inputs remained at the committed, clean
f890413e75e671748215ba2ef3304aa7953993e9. The freshness update was skipped
because the runner's live update lock belonged to codex4; no freshness-success
stamp was written. Production flags are `/O1 /G7 /arch:SSE /MD /EHsc`, stock
MSVC 7.1 RTM. Read-only compiler traces use c2.dll image base 0x10700000 and SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.

## Minimal closing change

The previous bank (blob c6d8c81f8f95c7131c3d592d2d62dbdf44594825) was already
218 bytes, but used EBX instead of ESI in two return instructions. Preserve
its empty return-holder lifetime and the separate nested return blocks. Change
only the return value in the existing unreachable funds arm from zero to two:

```cpp
unsigned int money = player->m_money;
if (money < result.m_pad04) {
    do {
        if (!(player->m_money < (unsigned int)result.m_pad04))
            break;
        { selected.code = 2; return selected.code; }
    } while (0);
    { selected.code = 2; return selected.code; } // previously zero
}
```

Both comparisons use the same unsigned conversion and unchanged operands.
There is no intervening call or store. Thus the changed arm is unreachable
under defined sequential C++ behavior. This is a code-generation adaptation,
not a claim that EA used the return-holder or unreachable arm. Removing the
nested return blocks produces a different, 204-byte body. The production
quote declaration must retain all intervening virtual slots: offset 0x50,
not 0x4C. Normal byte verification independently checks the actual callees.

The commit hook's shadow identity check caught an additional EH binding issue
before any commit was made: the native cleanup jumps to the five-byte wrapper
at 0x29A21F, not directly to the 26-byte destructor at 0x39205C. The old byte
resolver's broad jump scan and masked EH comparison had accepted that direct
destructor reference. The implicit derived `WallQuoteResult` destructor emits the
required five-byte wrapper while normal paths still call 0x39205C directly.
Eight wrapper-form controls preserved the parent's instruction bytes; six
also preserved its direct normal-path callees. Two visible-anchor controls
preserved the exact parent and emitted the existing 26-byte destructor.

The final unit keeps that destructor visible as an inline, noinline COMDAT
copy of the matched provider. `pin_admission.py --add` proved the new wrapper
name against the existing sole owner at 0x29A21F, including its whole body,
all owner relocations and the same-object 26-byte callee. Its pin carries
`fold-proof=`; the helper has no other address. The tool's checked hatch
grant is retained without its unrelated register tightening. The wrapper's
original class/name remain unknown. Its implicitly generated helper needs no
authored destructor or unmatched marker; a private implicit-destructor control
preserved the exact parent and subsequent normal gates check its fold.
Compiler-local cleanup labels are resolved from
the parent's verified EH graph, independently of ordinal renumbering.

The existing cleanup provider's out-of-line definition also becomes `inline`
while retaining `noinline`: both copies are then selectable identical COMDATs.
Leaving the provider strong caused a real duplicate-definition conflict.
The provider's 26-byte destructor and five-byte wrapper both remain exact.
Checking provider and parent together passes link prediction and reports zero
new shadow code-identity findings across all seven rows. No provider identity,
ABI, layout or instructions change.

## Why it works

Read-only traces of the old bank show five COPY (0x10D) definitions of the
return record: literal two, the fixed-zero record, two, nine and nine, plus
one outbound copy. Adding further dead joins leaves that body unchanged.
Changing the existing zero producer removes this particular copy preference.

The old return record has priority 8, six references, round 2, chosen register
4 (EBX). The winner has priority 7, six references, still round 2, and chooses
register 7 (ESI); neither has interference neighbours at that selection. The
fixed-zero record changes from priority 36 / 11 references to 40 / 10. This
closes the role swap without raising the return record's allocation priority.
An earlier 223-byte ESI control instead raised its return record's priority to
36 and allocated in round 1; that is a different mechanism.

`compiler-observations.json` preserves the relevant raw phase, operand and
color records. The trace driver only reads compiler state; it never writes
compiler memory. `validation.json` independently checks all seven traced or
production objects, including every EH graph. The exact body's masked SHA256
is `069fe273b7d7374f21578acb50b5ad3d6654bd0b1dfe3914d840f4a60e12fc5e`;
the old bank's is
`f54565adda9cdd992a36d7f917d0dcfb7f5fcf84313d6d1c01fd8549b91c4695`.

## Search and reproduction

The 13 preserved family drivers tested 9,728 compilable variants, with no final
compile errors or unresolved diagnostic relocations. `receipt.json` records
counts and best results. Only `dead-producer` closed the body: 384 of its 720
variants were exact. The minimal winner is `dead-01000`, literal two, assigning
the existing return field, with unchanged declaration scopes. Reproduce one
private compile from the repository root:

```sh
CANMAKE_CASE=dead-01000 python3 reverse/attempt_support/canmake-joins-20261023/dead-producer.py.txt
```

The drivers reuse the tracked frozen context and private-object scorer from
earlier handoffs, never the shared match object cache. Diagnostic relocation
maps are not landed pins. Most drivers also accept `CANMAKE_CASE`; omit it to
run that family with eight compiler workers.

`fold-replay.py.txt` compiles three final private controls: the complete unit,
an opaque destructor anchor, and direct cleanup without the wrapper. Each
retains the exact parent and masked EH graph; their emitted cleanup references
show why the complete fold proof and identity check are also required.
`fold-controls.json` records those controls. Their private objects never enter
the shared match cache.

The other families tested duplicate guards; single-field receiver reuse;
receiver/code pairs; return boundary types; compiler profiles; discriminator
expressions; read/write barriers; packed receiver/code values; direct named
receiver locals; selectors moved before their guards; quote/return owners;
and additional unreachable joins. None improved the old two-byte residue.
These are distinct from changing the already present dead producer. See the
previous handoffs for earlier scope, loop, header and allocation scans.

## Normal acceptance checks

- `./build.sh Code/GameEngine/Source/GameLogic/SkirmishAI/AIWallBuilder/AIBuildableWallSegment.cpp`:
  all five rows exact, including the two existing siblings and both EH rows.
- `tools/eh_verify.py`: exact parent EH graph; both EH rows are independently
  byte-verified from this same object.
- `./build.sh Code/GameEngine/Source/Common/Rva0039205CDtor.cpp`: both provider
  rows exact after selecting the existing noinline definition as a COMDAT.
- `tools/link_check.py` for provider and parent together: both link successfully,
  172 to 398 LINKED bytes against the published census.
- `tools/place_bodies.py` for that unit: no additional bodies or pins.
- `tools/find_declared_unmatched.py`: all definitions declared.
- `tools/pin_consistency.py --check`, checked fold-pin admission and the
  shadow code-identity scan: no new incorrect code binding after the repair.

The parent and EH rows were entered through `add_match.py`; no handwritten
asm, tool changes or gate exceptions were added. The one new pin is the
verified wrapper fold described above. The bank is retired. The first
uncommitted funclet record in the attempt log is superseded by its corrected
`add_match --replace-existing` record; no invalid prototype was published.
