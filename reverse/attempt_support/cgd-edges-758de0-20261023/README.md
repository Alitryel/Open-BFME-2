# 0x758DE0: branch copies survive allocation, but do not make the point local

Continue the assigned 333-byte body. The bank's code is unchanged:
**333 bytes, zero relocations, 31 positional byte differences, first +0x94**,
SHA256 `01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
Full-instruction alignment remains 308/333 (0.924924924924925). No production
source, row, pin, header, setting or gate changed. The reverse-only fastcall
interface remains a diagnostic ABI model, not an established original type.
Keep the ordinary, uniform thiscall control in `control.cpp.txt`.

## Hypothesis and prior negatives

The preceding packet, `cgd-global-homes-758de0-20261022/README.md`, establishes
that the first response's point gets a global EAX home before local allocation,
shared into the reverse response. Changing the reverse point offset in a
deliberately non-equivalent diagnostic removed that home and fixed the first
return sequence, but left the inner vtable early in EDX. Ordinary getters,
address identities, pointer-bit copies, scope/loop/declaration changes, callback
and return ABI models, real headers, sibling context and the recorded compiler
settings had already failed. Those results were not grounds to retry them alone.

The new hypothesis came from the NetPacket recipe: identical assignments on
different branch paths can survive global allocation and merge later. Could
this split the two responses' point-address lifetimes without adding final
instructions? Six factorial families test that mechanism, its placement and
interactions. The accessor and argument-class families include controls for
older single-entry/POD experiments; their new axes are branch paths and two
separately constructed, potentially nontrivial four-byte class arguments.

## New finding

`edge-bridge.cpp.txt` (edges/v0787) produces 333B, zero relocations, 39 positional
differences, 303 fully aligned bytes, hash
`08e15c89afc78d973e7c0e72a8ead3fbc06ebbc9fd930ea7a93bc4766c520c60`.
It assigns the same point pointer on two paths that join before the state-2
filter. Its reverse call reads the node's point directly. Relative to the bank:

- The first inner vtable uses EAX, and the first return sequence at +0xd8 is
  exactly retail's `mov ecx,[esi]; mov ecx,[ecx+4]; push eax; call [ebp+24h]`.
- The point LEA instead uses EDX at +0xb8, before the state-filter branch.
  Retail needs a short EAX lifetime at +0xce, followed by the pushes and then
  its vtable load at +0xd3. The new candidate still loads that vtable early,
  at +0xce. Its data-load order also differs. It is worse than the bank.
- The uniform-interface control, `edge-uniform.cpp.txt` (v0786), emits the
  **same first-response instructions from +0xb4 through +0xe0**. Thus this
  particular allocation/return-sequence finding does not require the reverse
  ABI cast. Its whole body is 335B and worse: 84 positional differences when
  the two extra bytes are counted (variant.py reports 82 overlapping-byte
  differences and the separate 335B/333B extent mismatch).
- `edge-direct.cpp.txt` (v0785), which removes only the data bridge from v0787,
  instead homes the point in EAX, the inner vtable in EDX, and loses that exact
  return sequence. The helper parameter boundary interacts with this CFG.
  This observation does not establish an original helper or interface.

Two completed, read-only c2 traces independently reproduce the corresponding
untraced objects, including sizes, hashes and zero relocations. See
`trace-checks.json`. The RTM compiler is still c2.dll 13.10.3077, base
0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.

In the v0787 trace, after +0x7c367 and on entry to global allocation +0x821a7,
the point has **two LEA definitions in different blocks**, both with raw
destination-symbol word 7 equal to 29. After allocation (+0xb0037), both
destinations are physical EDX (register ID 3); the first response's normal is
EDI (8), and a separate reverse point LEA is EAX (1). The branch copies really
survive through allocation, and the reverse point no longer shares their
home. However, the joined point is still a global value with two definitions,
not retail's short local. Block numbers and symbol addresses are snapshot
identifiers, not source-local names. The compact address stages and selected
IR preserve the observations for both diagnostic and uniform controls.

## Searches

All **29,696** family inputs compiled successfully with eight workers and
private objects through `compiler_command`, never `build.compile_source` or
the shared match cache. `trials-summary.json` records full `(mnemonic, operands)`
alignment; search.py's mnemonic-first metric differs. A region winner that
loses the solved prefix, register roles or reverse block is not an improvement.

| Family | Compiled | Distinct bodies | Best full alignment / positional differences |
| --- | ---: | ---: | ---: |
| edges | 3,072 | 502 | 305 / 44 |
| edgepoint | 4,096 | 226 | 308 / 31 |
| once | 2,048 | 23 | 308 / 31 |
| callpaths | 2,048 | 330 | 308 / 31 |
| pathget | 16,384 | 69 | 308 / 31 |
| duo | 2,048 | 48 | 273 / 51 |

- **edges:** eight state/label transfer forms, eight predicates, point/normal
  aliases, declaration scope, reverse alias reuse, data bridge and ABI control.
  Each branch assigns identical addresses; unused null aliases are never read.
  This is the new allocation finding above, not a closer candidate.
- **edgepoint:** move duplicate address assignments before/after state work,
  before/after its filter, or into the reverse region; combine predicates,
  shared labels, scope and the two interface controls. No usable improvement.
- **once:** one-iteration state, first-response and reverse-response loops and
  wrappers, crossed with the bridge and interface controls. The state loop
  always exits after assigning 1 or 2. Nothing beats the bank.
- **callpaths:** duplicate complete calls, conditional expressions, labels and
  branch-selected one-iteration paths at independent call sites. The predicates
  have no effects; the selected branch executes the original call exactly once.
  Nominal region improvements lose solved bytes elsewhere.
- **pathget:** eight inline accessor CFGs with direct/bit-copied point or node
  pointers, parameter order/convention, predicates, independently selected call
  sites and the controls. Most variants collapse to previously seen code.
  These branch-path accessors do not create the required lifetime.
- **duo:** consistent virtual prepare with two four-byte argument classes,
  pointer/reference members, constructors, copy forms, empty destructors,
  ordinary/fastcall convention, direct construction versus inline wrapper,
  separate/shared class types and data bridge. Unlike the old two-POD family,
  this includes nontrivial construction/copy/destruction. All are worse;
  several introduce EH relocations. No new argument type or ABI was proven.

The old independent negatives for types/layout, callee visibility, real
BFME 1/ZH headers, optimized WorldBuilder twin and compiler settings remain
applicable. This session found no new compatible compiler-setting hypothesis.
The local toolchain inventory has only the known 13.10 compiler, and no
collisionmanager library/PDB/map with source information was found. Neither
fact establishes a prerequisite blocker or justifies a blocked-on RVA.

## Validation and continuation

Started from rebased input HEAD `14ff8ff5fe` over origin/master `e78b7455a7`,
preserving three unpublished evidence commits. The workspace was clean,
the assigned body was claimed, its history read with pick-hard, and check_csv
passed: 98,069 function rows, 15,856 symbol rows, 2,135 data rows. AGENTS.md
was unchanged and within 24 hours of its preceding read. BFME 1's committed,
clean checkout remains `42bba2ddbd5cb895d99293583891d3b7315fa49e`;
claudec2 owned the fresh update lock, so this seat skipped that update and did
not mark freshness success. The assigned lane overrides broad queues, and no
maintainer-only runner was started.

Independent variant.py runs reproduce the bank (333B/31, first +0x94), v0787
(333B/39, first +0x94) and v0786 (335B/333B, first +0x3e). The trace compiles
also completed and matched their ordinary objects. These are expected
diagnostic mismatches, not false gate rejections or matched-body acceptance.
Ledger, script syntax, whitespace and path-case checks accompany the commit.

Continue **making the first-response point local without a joined global
home, while explaining virtual-target lowering under a consistent interface**.
The new two-definition CFG is now a concrete negative: it breaks sharing with
the reverse call but still cannot free EAX for a target load after the point
push. More duplicate branch/accessor variants from these families are not an
untried explanation. The test call's load/push ordering is also still wrong.
No external prerequisite or missing function was identified. The claim is
released with this handoff; the standing assignment remains in progress.

For reproduction, copy the .py.txt/.cpp.txt files into an ignored directory
two levels below the repo root and remove .txt. Run a generator, search.py
FAMILY, then regions.py with the family names. `edges.py` recreates the selected
sources. `global.py early-edge edges/v0787.cpp` and `global.py early-uniform
edges/v0786.cpp` produce the eight checkpoints; analyse.py verifies their
completed objects and writes the compact trace/disassembly records. The full
debugger snapshots and bulk variants remain ignored; only reproducible inputs
and selected evidence are banked.
