# Volumetric-shadow constructor square-root conversion attempt

Date: 2026-10-23. Seat3, isolated worktree `t3-b3925755`.
Base: `d6bee6a5d7f218f1f59af4da66d7cd3cdfe69fa2`; the source is also
unchanged at inspected origin `188285d0f739c3e4e330f4aa9934cc5e5c3e1d80`.
Verified donor/toolchain input remains `138757e9b74645fbcbb7724a7af2764e34931e11`.
No donor update or newer-input verification is claimed.

## Scope and target facts

Whole file: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowV2Constructor.cpp`.
Claimed the file and all five row starts before edits: constructor
`0x0010811E/609B`, folded vector-base constructor `0x00211E58/29B`, folded
vertex constructor `0x0047A6A9/3B`, unwind `0x007644F3/10B`, and EH handler
`0x007644FD/10B`. Claims protect existing bodies, not new coverage.

The existing target/WB identity and layout evidence is unchanged. Native
bounding-box arithmetic reaches a float input store at `0x00108325`, discards
the extra x87 value, reloads the float at `0x0010832A`, executes FSQRT at
`0x0010832D`, and stores a float result at `0x0010832F`. The radius is then
loaded by MOVSS and stored at object offset `0x80`; height arithmetic follows.
These are real input/result precision boundaries, not arbitrary padding.
The existing WWMath donor implementation explains the inline assembly, but
does not prove that a CRT intrinsic has the same rounding or scheduling.

## Trials

All six trials used normal `./build.sh` on this one TU. Source flags remained
`/I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc`
with the existing STLport marker. Own isolated OrbStack environment, one
compiler, and `BFME_OBJSTORE=off`; no command/include expansion, shared header,
wrapper, runtime, class layout, symbol pin, alias, or ledger edit.

Including the pinned CRT `<math.h>` introduces float overloads, so existing
fabs operands were explicitly converted to double to preserve the original
double-call selection. Only the approved TU-local `#pragma intrinsic(sqrt)`
was used; no optimization pragma, volatile, dummy storage, or artificial
side-effect was added.

| Trial | Constructor size | Result |
| --- | ---: | --- |
| Existing by-value helper returns `(float)sqrt((double)val)`, pragma after header | 593B | FSQRT emitted, float input/result temporary stores eliminated |
| Helper uses float `sqrt(val)` overload | 599B | Header forwarding chain retains an external sqrt call |
| Float overload with pragma before header | 599B | Same external-call result; no benefit from visibility ordering |
| Direct caller expression with named float squared-radius/radius and parentheses, pragma before header | 599B | External call remains; x87 discard topology changes |
| Same named float expression, pragma after header | 593B | FSQRT emitted, required float input spill still absent |
| Existing helper takes const float reference, named float caller values | 593B | Same intrinsic tail as preceding trial; address binding does not retain storage |

Every trial failed only the 609B constructor; the other four rows and existing
fold checks remained byte-exact. The first direct-intrinsic trial preserves
the first `0x1F6` bytes (502B), then differs at retail `0x00108314` by moving
the vector-empty comparison ahead of floating-point work. Its 593B size is
not a near-exact semantic proof: the missing input rounding can change values.

The retained candidate patch is the final const-reference trial. Its raw
object tail includes:

```text
00108314 cmp dword ptr [ebp - 0x20], 0
00108318 fadd dword ptr [ebp - 0x28]
0010831b movss xmm0, dword ptr [ebp - 0x24]
00108320 addss xmm0, dword ptr [ebp - 0x30]
00108325 fld st(0)
0010832f fmul st(1)
00108332 fld dword ptr [ebp + 8]
00108336 fmul dword ptr [ebp + 8]
00108339 movss dword ptr [esi + 0x84], xmm0
00108345 faddp st(1)
00108347 fstp st(1)
00108349 fsqrt
0010834b fstp dword ptr [esi + 0x80]
```

Addresses above are offsets into the unrelocated constructor object displayed
at its target base; they do not assert placement of the failed candidate.
The omitted ADDSS constant has an ordinary unresolved object relocation.
Read-only COFF inspection and Capstone supplied this diagnostic. The normal
explain-mismatch hexdump confirmed the size/first difference; its disassembly
display hit the host Apple objdump unsupported `-b` option. No tooling was
changed or verification bypassed.

## Verdict and restoration

Blocked within the approved constraints. New useful evidence is that explicit
float casts, genuine named float lifetimes/parentheses, direct versus inline
helper topology, float-overload visibility, and const-reference binding do not
retain the native precision barriers with this compiler configuration. This
does not establish that all possible genuine C++ forms are exhausted. A new
attempt needs evidence for a different precision-preserving language/intrinsic
mechanism or another independent codegen explanation, not another cosmetic
float temporary or register-only trial. No semantic equivalence is claimed for
the failed intrinsic bodies.

`candidate.patch` applies to the unchanged original source and is evidence
only. No existing better bank was overwritten. The source was restored exactly
and normal verification rerun: 5/5 bodies, one string reference, one float
literal, one named import, complete STLport fold check, EH EXACT 1/1, and all
defined functions declared/matched. No source, ledger, coverage, assembly-removal,
or linking gain is claimed. No census, link cycle, boot, publication, or external
decoder-source operation was performed.
