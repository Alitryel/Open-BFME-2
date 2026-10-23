# Signature-check callee-expression ordering controls

Target: `?Rva00237D3DCheck@@YAHXZ`, RVA `0x00237D3D`, 226 bytes.
Model gpt-6; compiler MSVC7.1 RTM, `/O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc`.
The existing exact ASM owner and its approved patch representation are unchanged.
This bounded attempt addresses the narrower C++/assembly alternative documented
in `../trust237-patched-target-20261023/readme.md`; rounds17/18 and the latest
blocker recheck were reviewed before work. The remote claim was pushed before
compilation under owner `codex-01a1071d-trust237-expression`.

## Hypothesis and result

The mixed candidate uses C++ for the API setup/calls, retaining only the dead
status-save and proven NOP16/return island in inline assembly. It emits226B,
but `MOV EBX,EAX; PUSH ESI` is reversed from target's `PUSH ESI; MOV EBX,EAX`
at +C2..C4. Hypothesis: moving the status save into the *callee expression*
of `LocalFree(argv)` might prepare the argument before evaluating that callee.

Six forms were tested with both external and internal helper linkage:
comma-expression with LocalFree or &LocalFree; force-inline helper returning
a function pointer, function reference, or nothrow function pointer; and a
template identity helper returning LocalFree after the status-save assembly.
All12 successful trials emit exactly the baseline's full226-byte body and
identical relocation records. All retain the same three differing bytes at
+C2..C4. There is no main-body call to a saveStatus helper. Some external
helpers emit unused out-of-line copies; these are diagnostic only and were
never admitted as retail functions. Internal linkage does not change the target.

The audit checks raw extent, raw bytes, all relocations, the three actual PE
imports (GetCommandLineW, CommandLineToArgvW, LocalFree), and the normal
compile_function resolver's resulting differences. WinVerifyTrust's existing
import thunk is rowed as `?ji_00655652@@YAXXZ`, so the source spelling
`_WinVerifyTrust@12` is unresolved by the unchanged global map. For diagnostic
comparison only, it is resolved to the independently established0x655652.
No pin/alias was added. A normal explain_mismatch run reports that unresolved
callee as well as the ordering mismatch; no exact byte-gate pass is claimed.

## Reproduce and remaining work

Copy `trials.py.txt` to ignored build/ and run it from the repository root with
the normal toolchain and verified BFME1 inputs. It uses tools/variant.py with
isolated scratch outputs, not build.compile_source. `evidence.json` records the
original trial objects and source hashes; the generator also re-audits fresh
outputs. No production Code, functions.csv, symbols.csv, baseline or verifier
was changed, no full build was duplicated, and no master push was attempted.
The main operator owns publication and the shared account cooldown.

The callee-expression hypothesis is exhausted for these forms. The existing
mixed candidate remains available at the linked handoff; no worse official
bank replaces it. Further recovery needs a genuinely new way to retain the
argument/status instruction order, or an independently justified minimal
ordering island. This result makes no claim of new C++ coverage or linkage.
