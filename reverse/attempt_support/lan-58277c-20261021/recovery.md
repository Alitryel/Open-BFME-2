# LANAPI::handleRequestJoin: constant sharing across admission scans

The complete 1844-byte body at RVA `0x0058277C..0x00582EB0` is exact,
including resolved calls. It ends in `ret 8`; the emitted COFF extent is also
1844 bytes, not a longer body whose prefix happens to match.
[verification.json](verification.json) records the compiler hashes, input
revisions, full-body hashes and relocation counts.

## Identity and source

`LANAPI::update` at `0x0044AAED` dispatches message type 3 through the jump
table at `0x0084B22F` to this boundary. The registry serial lookup, duplicate
serial/name checks, slot admission and reply flow support Zero Hour's
`LANAPI::handleRequestJoin` identity independently of the byte comparison.
The source outline comes from the official Zero Hour
`GeneralsMD/Code/GameEngine/Source/GameNetwork/LANAPIhandlers.cpp` in donor
`a80da2e3be84ebdb3b6bc280faca3f99a44788af`. BFME 2's native field accesses
establish the 16-byte executable CRC, packet fields and saved-slot copy.

The recovery extends the current BFME 2 home, preserving its renamed methods
and inline-only helper declarations. It does not replace that file with the
stale bank. The previous bank and its handoff at
`../0x0058277c-20261020-w1.md` supplied the near match and prior exclusions.

## Causal source change

The plain Zero Hour loop, `for(player=0; canJoin && player<MAX_SLOTS;
++player)`, preserves retail's top-tested serial scan. However, with one
straight-line serial-denial header, MSVC 7.1 carries constant 5 in EBX across
the following name scan. The slot pointer spills and other stack homes move:
1849 bytes instead of 1844. The older bank avoids that sharing by moving
`canJoin` outside the loop, but then rotates the loop and emits 1841 bytes.

Keep the Zero Hour loop and write both serial-header stores in each arm:

```cpp
if (player == 0) {
    reply.JoinDeny.reason = LANAPIInterface::RET_SERIAL_DUPE;
    reply.LANMessageType = 5;
} else {
    reply.JoinDeny.reason = LANAPIInterface::RET_SERIAL_DUPE;
    reply.LANMessageType = 5;
}
```

`player` is initialized by the loop before this condition is evaluated. Both
arms have identical, defined effects. This is a compiler-shaping reconstruction,
not a claim that retail used this exact source text. The compiler removes the
condition, emits retail's local `push 5; pop eax`, and stores type before reason.
It keeps the name-loop slot in EBX and restores every native stack home.
Tail merging after constant-web formation is the phase-order explanation;
the source/output controls establish the effect, not an internal compiler trace.

[controls.json](controls.json) retains these measured controls in the current
home, under the unchanged `/O1 /MD /EHsc /DNDEBUG` flags:

| Source form | Raw bytes | Result |
| --- | ---: | --- |
| Both arms: reason then type | 1844 | Exact, all 482 instructions |
| One straight-line header | 1849 | Constant 5 spans the name loop |
| Both arms: type then reason | 1844 | Only the two equal-valued stores swap |
| Duplicate only the reason store | 1849 | Same original register web |

The [regression patch](regression-control.patch) reproduces the straight-line
control on a diagnostic copy. Single-store equal arms and many equivalent
loop/type/store spellings were insufficient. Other excluded families included
callee visibility, compiler profiles, optimization switches, unused locals,
aggregate flag/index declarations and predicate-derived constants. The useful
new distinction was duplicating the **two-store group**, then measuring its
store order separately from its register allocation.

## Verification

`./build.sh Code/GameEngine/Source/GameNetwork/LANAPIhandlers.cpp` passes all
38 rows in the file, including existing EH ownership rows. It also verifies
the four string literals, six empty-string references and 14 named imports.
No compiler modification, optimization pragma, inline assembly, new pin or
alias is part of this recovery. `add_match.py` removed the old bank and recorded
the landing. This is one newly recovered function; no census gain is claimed.

The per-file `link_check.py` preview against the published October 20 22:09
index (`03035cf02c`) reports both `LANAPIhandlers.cpp` and its existing
`LANAPIUpdate.cpp` caller as `LINKS`. This is a preview against that index,
not a new census or a guarantee about an independently changed tree.
