# 0x00758DE0: source-shape search, 2026-10-22

Continue the assigned body. The best bank remains
`reverse/attempts/0x00758de0.cpp`, **333 bytes, 41 positional differences,
zero relocations**, first difference +0x94. Its emitted code is unchanged.
The historical score 0.9069 is 302/333 bytes in operand-identical,
order-aligned instructions, not the positional match fraction.
No matching Code body or ledger row was added.

## Inputs and checks

- Start tree: `806076fdec`; committed BFME 1 pointer:
  `37c3022de1ab944c7ffe536440d637dc8199091c` (clean checkout).
- `check_csv.py` passed before work. The fresh BFME 1 update lock belonged to
  `claudec2`; this seat skipped the update under the runner's lock rule and
  did not mark freshness successful itself. `link_check.py --fetch-index`
  obtained the published cache. Broad queues were skipped for this assignment.
- Claimed 0x758DE0 before work. Prior history was read with
  `/opt/runner/pick-hard --rva 0x758DE0`, including the w1/w3 and virtual-call
  handoffs. Their flag/profile, sibling-context, ABI, and member-dispatch
  results remain applicable; the new searches test combinations and different
  source boundaries, not a claim that those old trials were unexplored.
- Re-ran `variant.py` on the retained bank: 333B versus 333B, 41 differing,
  first +0x94. The independently established extent remains 333B, ending at
  0x758F2C followed by three INT3 bytes. Do not use the ordinary four-INT3
  boundary finder for this body.

## What the new trials rule out

`trials.json` records compiled counts, distinct code hashes, and best scores.
Failed compiles are excluded. Initial malformed generator runs are excluded
entirely when a corrected family exists. These are isolated diagnostics using
`compiler_command`, private objects, and the ordinary compiler. They do not
write the shared match cache or substitute for landing gates.

- **Control flow and scope:** 1,024 combinations of node/index declaration
  scope, self aliases, test-result locals, vector references, loop and branch
  forms; then 4,096 loop/label/split-guard/state-branch combinations. All 4,096
  latter trials emitted the exact same code as the bank. The tested source
  graph spellings do not explain the virtual-call order.
- **Local symbol shifts:** 384 initialized-local scans at four anchors and
  512 nonvirtual-declaration padding trials were byte-identical. A targeted
  `permute.py` run tried 1,311 candidates without improving its own fitness.
  No padding or permute output was banked.
- **Argument and receiver boundaries:** inline source/data getters at each
  call site, reference-returning getters, inline argument identity helpers,
  scalar argument/result types, receiver/info temporaries with empty
  destructors, and virtual operator-call syntax. The 256 operator variants
  were byte-identical. No valid combination beat the bank.
- **Types/layout and aliasing:** volatile method/field combinations, source
  and data handles stored as pointers/integers with casts, class/reference
  parameter carriers, and narrowed/wide prepare returns. All 769 compiling
  storage/cast controls were byte-identical. Narrow returns that add MOVSX
  are not valid explanations for retail's full-EAX argument transfer.
- **Vector source and callee visibility:** 4,096 parenthesization controls
  were byte-identical; 4,096 copy/negation identity and statement-order
  combinations produced 160 distinct bodies, none better. Actual BFME 1
  WWMath `vector3.h` with its real copy constructor reproduced the bank;
  unary-minus variants were worse. The actual `coord3d.h` was also tested
  with visible recovered copy constructors, empty destructor and `Negate`,
  including Coord3DBase parameter/member models (192 compiling variants,
  eight distinct bodies). None improved the bank. These are donor type
  models, not evidence that the target's vectors have either donor identity.
- **Compiler settings:** no new supported flag hypothesis emerged. The
  earlier RTM/SP1/DDK and LTCG results were not repeated. Settings remain an
  independent explanation checked by the prior packet, not a proven cause.

The WorldBuilder twin at VA 0x01803740 was independently re-read. It has
retail's push/vtable/reload order in the affected calls. This twin is optimized;
it does not expose an unoptimized local-variable frame. Its extra statistics
work is not proof of an original retail local.

## Region winners and remaining question

Across the corrected families there were 597 distinct emitted bodies. A second
alignment on complete `(mnemonic, operands)` pairs confirms that the bank is
still best overall at 302/333. No trial improved the test-call region beyond
the bank. The apparent first-response winner uses a char return plus MOVSX;
it leaves the virtual-target load wrong and is an ABI diagnostic only. A
member-pointer first response makes the later reverse reload sequence exact,
but adds a thunk relocation and changes the earlier response and point
lifetime. Neither supplies a local edit that can be recombined into the bank.

The unresolved instructions are still the three virtual-call sequences from
the previous packet: inner vtable load versus argument-address pushes, and
prepare-result push versus outer receiver reload. Iterator, guards, reverse
copy/negation, extent, and the important saved registers already match.
No missing callee was identified, so there is no justified blocked-on RVA.

**Next concrete investigation:** trace creation/allocation of the transient
virtual-target and argument-address temporaries, then design a source change
that changes their relative allocation. A read-only Wine debugger setup was
validated against c2.dll 13.10.3077 at base 0x10700000. At c2+0x83ACD, EBX=0,
the target has 15 global allocation records; `allocator.json` preserves the
snapshot. This does not identify the scratch-register selection mechanism.
The names in that early snapshot are incompletely decoded; do not treat them
as a proven IR graph. The existing a9f98-c2keys packet's frozen-at-creation
HashVar tracing is a better starting point than re-reading mutable IR later.

The target's bank has index +0xC060 and cursor +0xC064. The neighboring
bfmeOneCGD provider's differently offset view must not silently replace it.
Production ownership still needs the existing CollisionManagerImpl identity;
the bank's BfmeThingCGD spelling is inherited diagnostic scaffolding.

## Reproduction

Copy the saved `.py.txt` files to an ignored directory two levels below the
repository root, dropping only `.txt`, and copy the bank as `base.cpp` there.
Run a generator, then `search.py FAMILY` (eight workers). For example:

```text
python3 build/cgd-resume/flow.py
python3 build/cgd-resume/search.py flow
python3 build/cgd-resume/regions.py
```

`search.py` records the original mnemonic-first diagnostic score; it is 292
for the bank and is distinct from the historical 302 score. `regions.py`
computes the full-instruction alignment and per-call comparisons. Hashes and
score definitions are in `trials.json`. Generator compile errors are expected
for incompatible reference cv-qualifiers and base/derived parameter models;
they are not compiler or verifier failures.

No nonmatching body was installed in Code, no pin or gate changed, and no
verification runner was started. The unchanged best body is re-banked with
its existing score. This packet preserves negative evidence and a concrete
continuation; it does not claim all possible C++ forms have been exhausted.
