# Install_Materials canonical header and lifetime trials

Target: `?Install_Materials@BfmeB1137@@UBEXXZ`, native RVA `0x00095821`, extent 10,940 bytes. Inputs: BFME2 `413ecd9e`, pinned BFME1 `92f6bbe8`, MSVC 7.1 default 13.10.3077 under Wine; bank flags `/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc`, ASCII shim unchanged. Existing bank and production files remain unchanged.

The complete prior history in `bfmeb1137-install-00095821-20261019.md`, especially sessions 20p/20q, was read. This pass tested new source/API explanations, rather than repeating those scope sweeps.

The bank privately defines RGBColor although it is now canonical. Including `Code/Libraries/Include/Lib/RGBColor.h` instead is required before landing; its `getAsInt() const throw()` declaration is byte-inert here. The canonical-header patch reproduces the best existing result: 10,937 bytes, no unresolved calls, no structural differences, exactly one nonrelocation operand difference: at +0x2407, compiled `lea eax,[ebp-0x28]` versus retail `lea eax,[ebp-0xF8]`. The three-byte gap changes downstream relative branches and makes positional DIR32 patching noisy; compare raw COFF instruction streams with relocation operands normalized. The other 713 EBP-addressed instructions in this pass's broader metric agree.

New hypotheses and results:

- Binding mode-1 wind by const reference to a returned temporary, rather than aliasing a named local, tests a different C++ lifetime class. An inline wrapper retains the existing verified void/out getter contract. POD return: 10,929 bytes, three structural regions, 336 differing EBP operands. A user-written two-field copy constructor enables NRV: 10,928 bytes, zero structural regions, but frame 0x628 rather than 0x630 and 127 differing EBP operands. Both ordinary inline and forceinline give the same respective result. The patch preserves the most informative NRV trial.
- The BFME1 twin is the still-unmatched bank `targets/game/reverse/attempts/0x006e2ac0.cpp`, 13,048 retail bytes. It uses an eight-byte unsigned pair, read as float bits, in each mode. Repeating that representation in the BFME2 bank is byte-inert at function scope. Its branch-local form has 346 differing EBP operands. This is donor reconstruction evidence, not proof of an original field type.
- The rowed BFME2 getter 0x00094DD3 is an 18-byte leaf copying exactly two words. Declaring that call `throw()` is byte-inert, with either float or unsigned-pair fields and either scope. Returning the output pointer in EAX does not establish a hidden-return original signature.

There is no target or donor evidence for widening the wind object, forced alignment, explicit union storage, stack offsets, or a new class identity. None was introduced. Existing independent control-flow, lifetime, type, callee-visibility and compiler-setting investigations leave the same stack-coloring prerequisite; this pass adds no exact bytes. `trials.json` records the scoped results and `lifetime-reference.patch` permits resuming the distinct temporary-lifetime investigation. Full bytes, EH and linking remain mandatory if a future candidate closes the LEA.

Diagnostic patches use zero context; apply with `git apply --unidiff-zero` to copies of the stated inputs. Agent: Codex (runtime model not exposed).
