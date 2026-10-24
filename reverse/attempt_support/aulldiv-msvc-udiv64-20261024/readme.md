# Unsigned CRT division: modern MSVC hardware-DIV bank

Target __aulldiv, retail0x006295C0, complete104B, native ulldiv.obj member.
No production, ledger, pin, verifier or compiler-profile change; no coverage gain.
The unchanged owning vendor/msvc71crt/msvcrt.lib passes the normal whole-file
gate:11/11 remaining bodies,10 extracted members, no skipped references.

The prior family-compiler-prerequisites-20261024/division.md bank demonstrated
the full algorithm but Clang23 and VC7.1 recursively called __aulldiv for its
64/32 operations. This bank removes that specific backend prerequisite using
the already installed x86 MSVC14.50.35717 and14.51.36231 compilers. Both
recognize Microsoft's genuine _udiv64 intrinsic and emit hardware DIV over
EDX:EAX, with no helper call. The installed immintrin.h declares the same
signature as Microsoft's documentation:
https://learn.microsoft.com/en-us/cpp/intrinsics/udiv64?view=msvc-170
The standalone20B capability probe is preserved separately.

The complete body retains all unsigned64 numerator/divisor inputs. In the
low-only-divisor branch, the first32/32 division yields remainder<divisor;
therefore the second64/32 quotient fits32 bits. For a nonzero high divisor,
normalization shifts by1..32 until the divisor fits32; its top bit is then set.
The normalized numerator high word is below2^31, so hardware DIV cannot overflow
its32-bit quotient. The product-correction logic includes native unsigned carry
and the original numerator comparisons. No external input assumption, recursive
runtime call, assembly, register constraint or fake return value is introduced.

## Controls and findings

Both complete nonrecursive bodies were tested with private compiler outputs:

| Source/control | MSVC14.50 | MSVC14.51 | Finding |
|---|---:|---:|---|
|Full original algorithm + _udiv64, O1|120B|121B|No recursion; redundant word assembly remains.|
|Same O2|125B|126B|No full-byte equality.|
|Union word representation + __emulu + carry temporary, O1|118B|118B|Unsigned MUL selected, but carry materializes SETB/TEST.|
|Cross product first + nested carry branch, O1|97B|97B|Two MUL and direct ADD/JB correction restored.|
|Same O2|104B|104B|Equal extent is not byte equality.|
|Direct original-argument views, O2|120B|108B|Hoisting/allocation changes; native entry remains absent.|
|Manual low/high shift expressions, O1/O2|129B|129B|SHR/SHL/OR; no RCR.|
|Equivalent genuine _rotr identities, O1/O2|137/139B|137/139B|ROR/mask/OR; no RCR.|
|/favor:ATOM, O1/O2|97/104B|97/104B|O1 identical; O2 moves TEST before saves, no RCR.|
|Explicit O1 /Oy|97B|97B|No frame-policy improvement.|
|Genuine __ull_rshift(value,1), O1/O2|97/104B|97/104B|Identical to ordinary wide shift.|

Moving the commutative second __emulu operand order to (divisor.low,q) produces
native MOV EAX,[divisor.low]; MUL ESI instead of MOV EAX,ESI; MUL [divisor.low].
This is genuine dataflow, and the improved form is retained in best104.cpp.txt.
Both compilers emit the same best97B/O1 and104B/O2 bodies. The104B body has
14 matching positional bytes and90 differing bytes; first difference is0.
The Atom104B control has11 matching bytes, not11 differences. There is no
exact prefix or relocation-mask credit. All complete candidates have zero
relocations, and no helper calls.

## Whole-body behavior verification

Unicorn2.1.4 emulates all instructions of retail and both improved97B/104B
bodies.98,152 deterministic full-width cases include cross-products of values
near every power of two, quotient/product boundaries, and60,000 seeded random
inputs, including32-bit-only divisors. All match Python n//d and retail,
preserve EBX/ESI/EDI/EBP, and clean16 argument bytes (entry ESP+20 after RET).
Each native/candidate independently raises the CPU exception on divisor zero.
The emulator creates fresh CPU states for those fault cases; reusing an
exception-pending instance is not a valid fault test. This is behavior evidence,
not exhaustive-input testing, byte proof, or compiler-profile admission.

## Remaining concrete prerequisites

1. Native unconditionally saves EBX/ESI and reloads stack words after the guard.
   O2 hoists originals into EBX/EBP/EDI with a later ESI save; O1 has an EBP frame.
2. Native normalizes with SHR/RCR pairs. Genuine wide shifts, __ull_rshift,
   manual halves, rotation identities and Atom tuning do not select those pairs.
3. Return/epilogue scheduling differs even after MUL/carry selection improves.
4. Actual generated stdcall symbol is __aulldiv@16, while native is __aulldiv.
   No alias, pin or false source signature has been admitted to bridge that.
5. These installed modern compilers are not supported repo compiler profiles.
   They remain diagnostic. A profile change cannot precede full exact-body proof.

The formal partial stash was withdrawn because the ordinary builder cannot
reproduce this unsupported profile and must not silently fall back to VC7.1.
The final attempt verdict is blocked, and tracked.cpp.txt sources preserve the
full genuine implementation. The earlier recursive banks remain intact.

## Reproduction and receipts

input-proof.json contains every actual command, source hash, compiler/c1xx/c2
hash, full extent and body hash; improved bodies include full disassemblies.
Source templates are separate.cpp.txt artifacts. Copy reproduce.py.txt to
build/aulldiv-modern/reproduce.py and invoke it with the worker launcher. It
reconstructs source bytes from those templates, checks their recorded hashes,
uses build.compiler_command for existing environment/settings, and substitutes
only the recorded installed compiler path for private diagnostic compilation.
It never calls build.compile_source or writes build/match.

For emulation, install unicorn==2.1.4 into build/aulldiv-modern/deps; copy
emulate.py.txt to build/aulldiv-modern/emulate.py and run with the launcher after
reproduction. No dependency or compiler is installed globally.
