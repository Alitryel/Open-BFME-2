# CRT multiply: independent modern-MSVC intrinsic and frame evidence

## Inputs and scope

BFME2 43103255a8; published and clean BFME1 gitlink
0bf534ea7ccde110c456edb9cd2dd5dae823c953. Retail __allmul at RVA 00629580
owns its complete 52-byte llmul.obj body. Existing prebuilt library owner and
pin retained. No Code, ledger, gate, compiler profile, baseline or pin edit.

This is a new backend investigation beyond the old RTM/SP1/DDK and pinned
Clang controls in ../long-multiply-clang23-20261023/ and
../crt-and-sphere-prerequisites-20261024/. Installed Microsoft x86 compilers
14.50.35717 and 14.51.36231 were used only for isolated cached diagnostics.
They are NOT admitted compiler profiles and cannot verify production source.
The JSON compiler manifest records the actual driver/backend hashes.

The private script obtains build.compiler_command(source, private_output),
substitutes only its executable with the installed Hostx64/x86/cl.exe and
prepends that directory to the compiler environment PATH. The actual command,
executable/DLL hashes, sources, dependencies, ledgers and image enter the
ordinary recovery_experiments cache key. All46 runs report cacheable=true;
none touches build/match. Every source is a complete header-free translation
unit with one test body. Minimal controls below are not multiplication
implementations and are not proposed source recoveries.

## Actual new prerequisite progress

Unlike pinned Clang, modern MSVC's genuine __emulu intrinsic retains unsigned
MUL even when only the low half of a cross product contributes. Both modern
backends generate all three slow-path MULs without recursion. Unlike the old
Clang save-placement controls, the modern /O1 bodies save their cross-product
register only inside the slow branch. These are concrete selector improvements,
not exactness claims. No artificial high-half consumer was added.

The closest clean two-qword guide is best-plain.cpp.txt,14.51 /O1,51 bytes.
Its full disassembly is preserved. It still has an EBP entry frame and unused
stack slot, reverses the two cross products, saves ESI rather than native EBX,
merges the return, and uses zero ECX plus ADD EAX/ADC EDX rather than native's
single high-word ADD. These are substantial byte differences despite length.
14.50 /O1 emits66 bytes including dead stack-zero stores; /O2 emits85 bytes.
14.51 /O2 emits63 bytes without EBP but saves extra registers at entry.

## Independent explanations tested

- Twelve initial full-body controls: two compilers, /O1 and /O2, cross-first,
  low-first and full64-bit cross-sum expressions. The ordering forms converge
  per compiler/optimization setting; no helper calls or unresolved symbols.
- Eight14.51 /Oy controls explicitly form the result's unsigned high/low words
  or union view. They remove the generic carry addition but lengthen lifetimes,
  use extra saved registers and retain the size-optimized EBP frame (56-68B).
- Three minimal intrinsic controls isolate the frame: a sole __emulu return
  is frameless11B; two cross MULs truncated/summed to U32 are frameless25B;
  choosing the U64 product through a simple branch makes an EBP frame with an
  unused pushECX slot (25B). These controls are diagnostic, not native semantics.
- Seven callee/flow controls: truthful nothrow declaration of intrinsic, outer
  arithmetic function or both is inert; one intrinsic after selecting its
  operand and a single named U64 result also keep the conditional-body frame.
- Six policy/carry controls: /O1+Ot becomes the63B /O2 form; /O2+Os becomes the
  51B /O1 form. Thus the frame/register web follows documented size preference,
  not the broad O1/O2 label or an ignored /Oy. Genuine _addcarry_u32 with zero
  input carry supplies no improvement over ordinary high-word arithmetic.
- Four nonvolatile incoming-word projections (same16 physical input bytes,
  RET16, all128 input bits represented) remove wide-parameter extraction as an
  independent explanation. Their53-63B bodies still differ. No such projection
  was substituted for the cleaner two-U64 source.
- Six final private local-parameter reload controls preserve the native counts
  of incoming stack-word reads using volatile word parameters. These require
  semantic review before ANY landing and are explicitly not proposed production
  source. No volatile global, fabricated output or fixed register was used.
  The union form gives54B /O1 and59B /O2, correct cross-product MUL order and
  single high-word ADD. It still caches b_low in entry-saved EDI, uses ESI for
  cross sum, and /O1 keeps EBP. Read-contract projection is not exactness proof.

best-reload-diagnostic.cpp.txt and its complete disassembly preserve that
last differentiated result only to resume the prerequisite investigation.
All46 candidates/controls are listed in controls.tsv; full private reports
remain under build/crt-modern-multiply/. Baseline verification ran for each
cached experiment. No candidate is exact, no normal whole-Code-file landing
gate was claimed, and C++ exact progress is ZERO bytes.

## Remaining prerequisites

1. Native52B instruction/frame/register selection under the full input domain:
   native saves only EBX after its initial branch, keeps b_low in ECX, preserves
   a_high through the initial condition, executes the two cross products before
   the low product, adds only to EDX, and has distinct RET16 exits. The controls
   above isolate real remaining causes; they do not establish impossibility.
2. A supported public-symbol/ABI route if modern MSVC ever reproduces the body.
   Ordinary MSVC stdcall emits __allmul@16; the native helper is __allmul.
   Diagnostic comparison used the natural name __allmul@16 against native RVA.
   No alias, second provider, name pin, linker workaround or renamed byte owner
   was introduced. No modern compiler profile should be added for these results.

Microsoft documents __emulu as a32x32->64 unsigned multiplication and /Os,
/Ot as code-size versus speed preferences:
https://learn.microsoft.com/en-us/cpp/intrinsics/emulu?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/os-ot-favor-small-code-favor-fast-code?view=msvc-170
