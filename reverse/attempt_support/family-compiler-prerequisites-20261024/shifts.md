# Independent CRT shift-family review

Scope: __allshl0x00629780 and __aullshr0x006297A0,31B each. Root owns claims. Reviewed root's genuine regparm(3) U64/unsigned-char ABI plus full native bytes and word-funnel reconstructions. No production/ledger/gate/header edits.

Independent expression hypotheses: actual branch probability via __builtin_expect; minsize; unsigned-byte subtraction/borrow guards preserving every0..255 count; original word-funnel shape. Stock pinnedClang23 backend hypotheses: branch hoisting/sinking; early-if conversion; basic allocator; callee-save cost; PHI edge splitting; increased tail duplication; FastISel; GlobalISel with ordinary fallback; peephole disabled; unoptimized allocator; narrow-shift widening disabled; DAG combiner disabled.

Best new left-shift:36B from expect+tail duplication (expect_tail.cpp/results.json), preserving genuine ABI and all inputs. Still saves ESI, moves low word through ESI, usesCMPCL3F/JA, and omits nativeANDCL1F. It is not exact.

DAG combiner disabled is a useful diagnostic: it restoresCMPCL40/JAE, so the63-versus64 residue is compiler canonicalization rather than a source comparison error. It also emits SETB/TEST for the32 guard and does not restoreANDCL1F. Best such trial41B. Basic allocator changes the chosen registers; no-hoist/no-sink/cost/PHI controls are inert; alternate selectors do not close. All trial objects reside only in this directory.

The native large-count ANDCL1F is redundant before32-bit SHL/SHR (hardware already masks counts) and its CL output is unobservable in the actual caller-saved count-register protocol. The supported selectors erase that mask even with explicit n&31 in real C++. GenericDAG combine disabling does not disable target-specific shift-mask lowering. Forcing count as an additional returned/observable value would invent a different ABI and was not tried. No byte insertion, asm, restricted count bounds, artificial high halves or testing-only reserved-register flags were used.

No claim of exact impossibility across all compilers. Remaining concrete prerequisite is a supported target-specific codegen route that retains the redundant native mask while obtaining the real EAX/EDX/CL layout, or another pinned backend that naturally emits it. Repeating standardif/order/CPU tuning alone does not address the residual.

Artifacts: trials.py/results.txt/results.json (28 trials), isel_trials.py/isel_results.txt/isel_results.json (24), dag_trials.py/dag_results.txt/dag_results.json (16), backend_help.txt. Baseline root scripts are in short checkout build/shift_family_20261024 and build/shift_word_trials_20261024.*.
