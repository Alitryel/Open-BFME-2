# 0x237D3D: finite empty loops and sibling-image leads

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, extent 226.
Previous handoff: `../trust237-20261022-round7/readme.md`. Inputs:
BFME2 `2791384223`, committed and checked-out BFME1 `42bba2ddbd`.
Model: GPT-6.1-sol. No Code, ledger, pin, gate or compiler binary changed.

## Hypothesis and results

Read the per-RVA history and relevant prior evidence before editing.
Ordinary predicates, single-iteration counting loops, lifetimes, layouts,
callee visibility, EH, compiler profiles, alignment, copy coalescing and
managed-mode controls already had concrete trials. Do not rerun those matrices.

The new control-flow hypothesis was that repeated finite loops with no
observable effect could disappear late enough to leave separate padding
nodes, or retain the status save with a closer return tail. `empty_loops.py.txt`
crosses eight families, one/sixteen repetitions, an outer repeat loop versus
separate scopes, before/after LocalFree, two return tails, O1/O2 and G6/G7.
All loops terminate for every unsigned 32-bit input, including wraparound.
The accumulation forms use even unsigned consecutive products or sixteen
XORs, so their accumulated value is zero.

All **512** compiles succeed, producing **136** distinct raw bodies.
None improves the 219-byte bank or contains sixteen consecutive NOPs.
Six variants (five distinct bodies) contain one literal NOP each. These
retain actual loop instructions: e0290/e0291 pad at +0x10F before a loop
at +0x110; e0402/e0403/e0422/e0423 pad at +0xEF before +0xF0.
These are ordinary 16-byte loop alignment, not the retail tail. All six
use O2 and first differ at +0. Thus the specific empty-loop family supplies
no evidence for a padding-only remnant after the body disappears.

`emulate_loops.py.txt` relocates each distinct object by its symbol records
into private Unicorn memory. All **21,488 executions**, 136 code/relocation
groups times 158 status values, pass return=1, observable API counts/order,
GUID and file/data layout, balanced stack, and callee-saved-register checks.
External stubs clobber caller-saved registers and flags. Samples include
unsigned boundaries, 128 seeded random values, and six trust HRESULTs.
The first harness assumed two out-of-line memset calls; O2 inlines them.
The final harness permits this and verifies all fields at WinVerifyTrust.
This was a harness correction, not a failing candidate behavior.

## Read-only lead checks

`inspect_leads.py.txt` checks the same RTM c2 hash as round7. A broader
raw-immediate scan finds 45 A9 patterns and fourteen possible instruction
decodings. Bounded contexts reject an apparent `mov ebx,A9` inside the
displacement of `mov edi,[ebx+A9]` at 0x10736E5D. The extra `push A9` at
0x107DB0E9 is a diagnostic line number passed with the embedded source path
`p2pragma.c`, not an instruction-node constructor. The ECX=A9 sites at
0x10801CD6 and 0x1084D8E4 compare/skip nodes, not create them. This scan
finds no new direct constructor beyond round7's four; it is not an
exhaustive reachability proof or proof of a post-link patch.

A target-specific image check covers both available BFME1 game images,
workshop-vanilla-1.03 and retail-1.03-unpacked. Neither imports WinVerifyTrust,
CommandLineToArgvW or GetCommandLineW; neither executable section contains
the first GUID word 00AAC56B. The BFME2 game has the expected imports and
one such word at 0x237D86 within this body. Hashes and compact results are
in summary.json. No dynamic counterpart is ruled out, and no broad queue
or reference sweep was repeated.

## Retained bank and reproduction

Keep `reverse/attempts/0x00237d3d.cpp`, score **69/86 = 0.802326**.
Independent `variant.py` reproduces 219 bytes, raw SHA256
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`,
diagnostic masked prefix 205 and 21 positional differences. Still unresolved:
sixteen 90 bytes at +0xCD..DC and return-tail ordering. No missing game
callee was identified. No exact byte-admission or new linking result is claimed.

Copy the three saved scripts into build/trust237-round8 without `.txt`.
Restore round5's search.py/base.cpp as its handoff describes. Run empty_loops.py
from the repository root; it uses eight compiler threads and private objects.
Run inspect_leads.py for the bounded compiler/image probes. Independently run
variant.py on the retained bank with the name above, RVA/extent above,
_memset=0x6291AE and _WinVerifyTrust@12=0x655652, then emulate_loops.py.
The emulator uses round4's scratch Unicorn installation and constructs its
own deterministic samples. It does not need round6's JSON or repeat its trials.
All three scripts pass py_compile. summary.json keeps compact receipts;
full objects and diagnostic JSON remain disposable scratch under build/.

Ledger integrity passes. The shared BFME1 freshness lock is live under
claudec2; this seat skipped the update and wrote no success timestamp.
Release this claim after banking. Preserve unrelated reverse/zh_sweep/.
Continue only this assignment; these finite negative trials do not establish
that a clean C++ match is impossible.
