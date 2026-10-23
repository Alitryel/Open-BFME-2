# Collision merge container abstractions, 2026-10-20

Target `?rva007586F0@CollisionManagerImpl@@QAEXXZ`, RVA 0x007586F0,
460 bytes. BFME2 413ecd9e74b1c122e930f26a1f9d3099f4ad6d20; pinned BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790; default MSVC 7.1,
`/O2 /G6 /DNDEBUG /MD`. Model Codex (runtime model not exposed).

The current joint bank `reverse/attempts/0x007586f0.cpp` remains unchanged.
The original method name is unknown. Native and WorldBuilder 0x01802EC0
are identical 460-byte optimized bodies, with no calls or relocations;
WorldBuilder supplies no original container/helper names.

Reproduced the 460-byte bank with the native 0x4C frame. First byte difference
is +0x1E: native `lea ebx,[ecx+0xc]`, candidate `add ecx,0xc`. The remaining
register-allocation problem is already described in the latest attempt log.

New bounded experiment: inline `SortChain::append` with the exact existing
head-before-tail/count-increment semantics, nested `append(chosen->pop())`,
and references for a, b, or both source chains, each tested with the direct,
append-member, and nested forms. All eleven variants compile to exactly the
baseline bytes; the abstraction changes do not affect allocation.

Independent support seat tested whole-run inline abstraction: a free helper
with a/b/d references and left/right values, and a destination member helper.
Both remain 460 bytes with the same register allocation; only two stores of
the same value to stack counter slots exchange order. An array/source/output/
run helper emits 456 bytes and worsens agreement. No hypothesis produced an
improvement, so retain the existing stronger bank and release the target.

No Code, ledger, pins, compiler settings, or verification gates were changed.
This is diagnostic evidence, not recovered coverage. Resume only with new
layout, compiler, or source evidence beyond these container abstractions.
