# CRT long multiplication: correct ABI, unmatched instruction selection

Target `__allmul`, native RVA `00629580`, whole 52-byte `llmul.obj` body.
No prior attempt-log entry for this RVA existed. The 52-byte library row and
its established pin remain unchanged; no Code source or alias was added.

The retail helper consumes two consecutive little-endian 64-bit stack values,
returns their product modulo 2^64 in EDX:EAX, and returns with RET 16. It has a
zero-high-word fast path. Its slow path saves EBX only after that branch,
forms two cross products and the low-word full product with three unsigned
MUL instructions, adds the cross sum into EDX, restores EBX, and returns.
These are target instructions, not inferred application types.

The pinned unmodified clang23-x86 compiler can express the callable protocol
using stdcall plus its native external-name annotation. The annotation sets
the definition's one public COFF name to `__allmul`; it emits no alias,
alternate provider, instruction, pin or relocation. The first ordinary C++
candidate emits that exact name, RET 16 and a 55-byte relocation-free body.

The clean 64-bit-parameter candidate computes the mathematically equivalent
low product and cross terms. Moving the cross terms before the low product
reduces the body to 45 bytes. O1, Oz, and an explicit shrink-wrap control all
produce that same 45-byte shape. This is not a length-only near match.

A diagnostic four-stack-dword view uses volatile local parameter reads to
retain native's operand reloads. It reaches 53 bytes, but still saves ESI at
entry and merges the return; the native fast path saves no callee-saved
register. Both O1 and Oz produce the same shape. The arithmetic accesses only
the incoming local parameter words; it introduces no global or shared-memory
assumption. The clean two-qword source remains the preferred semantic guide.

Two independent controls do not close these differences:

* The compiler's genuine `__emulu` intrinsic still narrows the cross terms to
  two-operand IMUL when only their low halves contribute to the result.
* A likely-fast-path annotation, shrink-wrap enabled, and the previously
  useful branch-folder ordering switch still yield the 53-byte shape.

All candidates produce correct low-product arithmetic, but none reproduces
the three native unsigned MULs, native register allocation and split save /
return paths. No fake high-half use, input restriction, assembly instruction,
explicit frame manipulation or compiler modification was introduced to force
those machine choices. No partial byte score is claimed merely because one
candidate's length is 53 versus 52.

`clean.cpp.txt` preserves the 45-byte semantic guide; `stack-words.cpp.txt`
preserves the diagnostic 53-byte variant. Their complete disassemblies and
the original candidate/native comparison are adjacent. `inputs.json` records
compiler/source revisions and result hashes. Every object was emitted only
under ignored build/ using compiler_command; shared build/match was untouched.
This is a blocked handoff and scores zero recovered bytes.
