# Shader Init: UTF16 allocator-family prerequisite

Continues the provider investigation for FXShaderGeometry::Init18C84E/2333B.
Root inputs:2d5d6b1294 after the completed word-vector repair; BFME1 verified
checkoutb3cc6b1588f2fdd4d31ab65199945a837f1f6e9b. The original shader bank
is preserved unchanged. No new byte recovery is claimed by this attempt.

## Established prerequisites

The separate completed repair (published50c7c24d95) corrected unsigned GameSpy
ports, false four-byte ushort constructors/fill, and the legacy proxy7410
owner. It does not establish the filename buffer's original element signedness.
Native filename caller513ED1 reaches count513DD0, base513D55, proxy7410 and
the29-byte word allocator17710. Shader remap's empty base211E58 instead calls
proxy14F3C4; its signed allocatorAD722 is27 bytes. Keep those distinct families.

The old short proxy and allocator pins still conflate these families. They
cannot simply be moved: that breaks the already-matched filename consumer.
Two honest reconstruction directions were tested, without inventing an
original allocator/container name or admitting unproven pins.

## New compiler and ABI results

- A POD two-byte record plus accurate STLport POD traits is87 bytes for the
  count constructor, versus native51. Aggregate zero fill is not scalar zero
  fill; width alone is insufficient.
- The nominal buffer view in `nominal-buffer-provider.cpp.txt` emits the exact
 58-byte base against513D55, using the canonical unsigned16 allocator and
 proxy. Calling `uninitialized_fill_n` in the count constructor preserves all
 51 native bytes except its not-yet-bound new base name. Direct `fill_n`
 instead emits50 bytes; a separate initialize method outlines and emits44.
- Porting that view, its real free lifetime and operator[] into the existing
 filename TU changes its native415-byte consumer, so it cannot land alone.
- A scoped allocator retaining the existing scalar short storage view can
 keep the normal vector count51 and base58 shapes. The original signedness
 remains unknown; this is a local ABI view, not a recovered application name.
- STLport here lacks member-template allocator rebinding. Merely inheriting
 allocator<short> strips the scoped allocation override through
 `__stl_alloc_rebind`: the base incorrectly callsAD722. Supplying the proper
 rebind overload selects the custom method but also changes consumer code.
- A local allocator implementation under this TU's native/O1 /arch:SSE /G7
 emits27 bytes. Native17710's/O2 implementation is29 bytes (separate returns
 and `add esp,8`, versus merged return and two pops). This is real compiler
 shape evidence, not proof of original signedness. Do not pin27 onto29.
- The final scoped proxy specialization calls the existing canonical29-byte
 allocator directly and leaves normal short-view deallocation intact. Its
 count/base otherwise reproduce native, but the filename consumer is412
 bytes rather than415. The sole unresolved proxy-constructor name was not
 pinned because the complete dependent repair still fails.

The new consumer discrepancy includes swapped stamp/temporary stack homes
at +0x47, register allocation and different loop/cleanup shapes. Pointer
signedness, begin versus operator[] API, memcpy through the cursor, deferred
cursor lifetime, explicit allocator destructor, implicit adapter lifetime,
and declaration-only count visibility were independently checked. API
variants remain412 bytes; deferring the cursor gives414, still wrong.
No dead statements, volatile levers, optimizer pragmas or emit/asm were used.

## Handoff

`scoped-allocator.patch.txt` is the final diagnostic candidate, not a match.
The JSON files and compact gate summary preserve the relevant failed trials.
Full logs remain in ignored `build/utf16-family-repair-oct20/` and
`build/word-family-repair-oct20/`. All production changes from this failed
prerequisite attempt were restored. No new pins, rows or claims of coverage
were retained; the existing shader bank remains the best reconstruction.

A future attempt needs a genuine caller/compiler explanation that preserves
the415-byte consumer while separating the allocator family. The shader's ten
remaining instruction-order mismatches also remain after that prerequisite.
Do not replay the unchanged adapter/API/lifetime variants above.

## Explicit allocator protocol follow-up

Inputs415e47e785/BFME1b3cc6b1588f2. A clean donor compile exposed a new,
independent feature difference: vendor4.5 disables member-template classes for
VC1310, whereas donor4.6 enables them. The alloc traits and proxy select their
direct rebound-allocator path through this feature. The intended header paths
were verified, and a preprocessor assertion checked that the trial enabled it.
No shared header was edited.

Full donor4.6 is inapplicable as a drop-in repair: the plain filename caller
emits410 rather than415 bytes, its base emits67 rather than58 and calls the
donor node allocator. Its allocator allocate method is also non-const, unlike
the target's established const provider ABI; the old const specialization is
therefore a genuine compile error under those headers.

Isolating MEMBER_TEMPLATE_CLASSES in the existing4.5/bfmealloc context keeps
the original plain caller415 exact. A correctly rebound scoped allocator needs
the standard optional hint argument: the first direct trial lacked its default
and failed compilation; specializing the proxy method fails because that method
is inherited in this protocol. The valid direct trial then gives these results:

| Scoped allocator context | Caller513ED1 | Count513DD0 | Base513D55 |
| --- | --- | --- | --- |
| Inline wrapper constructing a temporary canonical word allocator |415, only new count edge unresolved |51, only new base edge unresolved |58, proxy and custom allocation edges unresolved |
| Inline empty-subobject view calling canonical word allocation directly |412, first mismatch+47 |51, only base edge unresolved |58, only proxy edge unresolved |
| Declaration-only allocation method, real algorithm in separate O2 unit |412, first mismatch+47 |51, only base edge unresolved |58, proxy and allocation edges unresolved |

The new proxy emits all11 native bytes at7410. The separate O2 allocator emits
all29 native bytes at17710. Neither proves the whole repair: its declaration-only
caller still emits412. Conversely, the415-byte caller requires a wrapper that
is not the native allocation implementation. Never pin that wrapper to17710 or
interpret the415-byte caller's one unresolved edge as a complete match.

`member-protocol-415-diagnostic.patch.txt` preserves that useful but unlandable
415-byte diagnostic context; `member-protocol-allocation-o2.cpp.txt` preserves
the separately exact provider algorithm. The compact JSON includes normal
verifier results. Full sources/diffs remain build/utf16-stl46-oct20/. The scalar
storage signedness remains uncertain. No new pin or production change was made,
and the shader's better existing bank was preserved unchanged. This rules out
the newly supported allocator-protocol explanation without replaying the old
API/lifetime or shader instruction-numbering trials.
