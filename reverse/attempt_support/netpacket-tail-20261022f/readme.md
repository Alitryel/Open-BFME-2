# NetPacket::getCommandList: exact shared completion

2026-10-22, gpt-6-astra, codexb2. **Matched 0x00593F15..0x005944D8,
all 1475 bytes; EH EXACT; no unresolved relocations.** The normal home unit
now owns the body and `add_match.py` removed the partial bank. This assignment
is complete. The extent includes 1351 code bytes and the 124-byte switch table.

## Source finding

The previous bank differed in seven bytes: Z restored the cursor before
restoring `this`, preventing the backward jump into D's cursor-restoration
tail. The previous session's `bedge_0040` fixed that order but moved the loop
test to the top. Ordinary loop, declaration, throwing-callee, provider,
cursor-layout and compiler-profile experiments were already excluded by the
picker history; they were not repeated.

The new hypothesis was to enter **D's existing completion**, rather than the
loop header, through a conditional edge. A factorial tested eight predicates,
eight Z-edge forms and four D-label scopes. All 256 variants compiled; eight
were completely exact. A separate unchanged bank control reproduced the
seven-byte residue. The successful D scope contains two equivalent cursor
assignments, and Z can jump directly into the first:

```cpp
// D completion, after detach:
if (commandType == 1) {
finishCommand:
    i = offset;
} else {
    i = offset;
}
// Z completion, after detach:
if (commandType == 1) {
    goto finishCommand;
}
i = offset;
```

Every path still sets the same cursor and reaches the same loop condition.
D's `msg` and `ref` declarations have no initializers; their assignments remain
at the original sites. Thus the Z jump does not bypass initialization of a
local with an initializer or enter a destructor lifetime. It uses neither
of those D locals. No extra branch survives in the output.

The observed result is retail's Z `mov ebx,[ebp-2c]` followed by the backward
jump to D's `mov esi,[ebp-14]`. The likely allocator explanation is that the
cursor assignment now belongs to the shared successor while the `this`
restoration belongs to Z's incoming edge. Unlike the preceding session's
compiler trace, this explanation is an inference from source and emitted
bytes; no debugger or compiler modification was needed for this recovery.

The initial exact predicate was `commandType & 1`. A 48-case simplification
family established that `commandType == 1` is also exact and that removing the
duplicate D assignment loses the result. Two generated variants accidentally
removed the Z `msg` declaration and failed compilation; they are generator
errors, not verifier rejects. The formatted body in the complete current home
unit remained exact. Measurements preserve all counts and the resolved hash.

## Identity, layout and provenance

Inputs are BFME2 `3dfef660f908fa5854e627f6caaa9a26ff7e653e` and the committed
BFME1 reference `37c3022de1ab944c7ffe536440d637dc8199091c`. The inherited bank
and earlier handoffs preserve the longer reconstruction history. BFME1's
`game/GameEngine/Source/GameNetwork/NetPacket.cpp` and Zero Hour's
`GeneralsMD/Code/GameEngine/Source/GameNetwork/NetPacket.cpp` establish the
donor parser's purpose and D/Z acknowledgement behavior. They do not establish
BFME2 offsets or release allocation by themselves.

Independent target evidence is the caller at 0x0058BF11 in
`Connection::sendNetCommandMsg`, the packet's already matched reader and writer
family, and WorldBuilder twin 0x0154E140. The twin establishes the early
returns and local operations; the target instructions establish timestamp and
command-ID handling, message fields, constructor sizes and called identities.
The 0x10-byte list layout agrees with its matched constructor at 0x0058B06A.
The ACK payload words remain offset-named because their semantic names are
not proven here. This completion adds no pins, aliases, barriers or assembly.

The freshness receipt was less than 24 hours old at session start. The clean
reference checkout remained at the committed pointer. A read-only official
fetch found newer upstream c7678843663d6e48707b655224e4389e8f5890d1; this session
did not change the pointer or write a new successful-check timestamp.

## Acceptance checks

- `add_match.py` ran the normal `./build.sh` home gate: **163/163** functions;
  string, float, import, source-claim and existing funclet checks passed.
- `eh_verify.py`: **62/62 EXACT**, including this function.
- `find_declared_unmatched.py`: all definitions declared; `check_csv.py`: OK.
- `link_check.py NetPacket.cpp Connection_sendNetCommandMsg.cpp`: **2/2 LINKS**.
  The provider gains 1475 matched/linkable bytes; the 440-byte consumer now
  links too. This is the predictive check against the published census, not a
  maintainer-only link-cycle run. Exact output is in `link.txt`.
- `place_bodies.py NetPacket.cpp`: **0 additional bodies, 0 pins**.

## Reproduce the source search

Copy `search.py.txt` and `shared_tail.py.txt` to ignored
`build/netpacket-20261022f/`, removing `.txt`, then run the latter from the
repository root. The driver explicitly reads the starting bank from the
recorded BFME2 revision, since the landed bank is now deleted. It uses eight
isolated object paths and normal relocation resolution, never the shared
compile cache. `exact-tail.patch` is the small successful change to that bank,
already simplified to `commandType == 1`. Production uses the same body with
formatting, comments and the label renamed to `finishCommand`.
