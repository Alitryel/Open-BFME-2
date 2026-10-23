# SelectionTranslator::translateGameMessage, 2026-10-20, codex7

The bank improves from 4048 to 4050 bytes against retail's 4054. The contained-object
region now reproduces retail, including `mov esi,eax; mov ecx,esi`. Only the
case 62–71 group-reload region remains in the relocation-masked instruction
comparison. This is a partial, not a byte-gated match. No Code source, ledger
row, pin, verifier, or hatch was changed. The bank score increases from .90 to .95.

## Successful interaction

Both changes are needed: repeat `nativeContained43003C(obj)` in the condition
and assignment (as WorldBuilder repeats getContainedBy), and test bit 55 through
the unsigned 32-bit word at template +0x10C, mask `1u << 23`. The previous byte
test at +0x10E, mask 0x80 is semantically equivalent, but changes allocation.
Repeating the getter alone and widening the mask alone were inert. The successful
combination does not introduce padding, dummy locals, another class, or another
helper. It leaves the other kind-of tests untouched.

WorldBuilder's corresponding block calls getContainedBy repeatedly, and its
kind-of path passes bit 55 through a bitset test. Retail independently establishes
the +0x274 contained pointer and +0x10E bit test. The 32-bit source expression is
a code-generation choice, not a newly established target class declaration.
The bank retains the previous donor attribution and identity evidence. This
session's target boundary check and prior evidence agree on 0x43003C..0x431012,
with RET4 at 0x43100F. The constructor/vftable evidence is in the previous handoff.

## Remaining residue

Offsets below are relative to 0x43003C. These are **case 62–71**, correcting the
previous hans handoff's case 72–81 label.

* Retail: +C62 compares elapsed time; +C6A loads group into EAX; +C6D compares
  EAX with `[ebx+C]`; +C72 loads PlayerList into ECX; +C83 pushes EAX. In the
  normal-selection arm, +CF9 reloads group into ESI after the deselect calls.
* Bank: +C62 hoists group into ESI before the elapsed-time comparison; the
  equality and call use ESI. PlayerList is loaded through EAX. There is no
  reload at +CF9. Net size is four bytes short.

The isolated diagnostic reports 3 structural regions and 4 non-branch operand
differences after masking COFF relocation operands. Official align_diff confirms
the same 3 regions and -4 bytes; its 103 memory differences mostly count
unresolved global addresses, so they are not 103 layout defects. Full decoding
reaches the end of both extents. Branch destinations and callee bindings have
not passed the full byte gate.

An arithmetic equality, `!((UnsignedInt)group - (UnsignedInt)m_lastGroupSelGroup)`,
prevents the hoist and reproduces the later ESI reload. It emits SUB instead of
CMP, destroys the group in EAX, loads PlayerList through EAX and pushes group
from the stack. That diagnostic is 4055 bytes, 1 structural region, 3 operand
differences. Do not replace the bank with it: its lower mnemonic-diff count
does not make it an exact body. XOR has the same problem and one more operand
difference. The arithmetic result suggests a distinction between comparison
value flow and allocation, but no supported exact source was found for it.

## Trials already covered

The prior attempt history and linked handoffs were read before these trials.
Do not repeat them without new evidence. Scratch sources and logs are in
`build/selection43003c-oct20-seat/`; family names identify exact trial scripts.
Each compile wrote an isolated object using build.compiler_command, never a
manual build.compile_source call or the shared match object cache.

| Family | Choices and result |
| --- | --- |
| wave1, 16 | Direct failure-field invalidation instead of Bool valid; member contained/template accessors; normalized Boolean bit helper. All baseline. |
| wave2, 64 | Repeated contained getter; actual donor TEST_KINDOFMASK; WB selectedDraw/ID initialization and relationship arms; actual Drawable/Object getters; frame getter; loop-index declaration scope. No improvement. Actual bitset leaves a call and adds code. |
| wave3, 24 | /Ob2, inline_depth(255), auto_inline(on), explicit /Ob1, with and without real bitset/repeated getter. No improvement; /Ob1 worsens. |
| wave4, 16 | Real bitset const/nonconst operator[] proxy paths, 116/224 bits, wrapper forceinline, repeated getter. No improvement. |
| wave5, 128 | Byte/word storage, masked/shifted bit, Bool/Int/UnsignedInt/unsigned-char result, normalization, nested helper, repeated getter. **Word + integer result + repeated getter fixes A.** Some raw masked-word returns truncated to unsigned char are invalid diagnostics and were discarded. |
| wave6b, 64 | Diagnostic-only initialized inert locals, k=0..63 at function entry. Every successful compile is unchanged. None banked. Initial wave6 failed C4189 for k>0; wave6b disables that warning in scratch only. |
| wave7, 16; wave11, 8 | Minimized A through existing kind helper, separate helper, direct word test, Int/long and masked/shifted forms. Direct word test plus repeated getter is sufficient; retained wave11_00. |
| wave8, 64; wave8b, 64 | Real PlayerList::getLocalPlayer, Player::getHotkeySquad, reference-returning squad view, direct failure invalidation, double-tap helper, real GameLogic::getFrame. No group improvement. Donor local-player is +C versus target +10; frame is +3C versus target +40. Correcting those read views by +4 restores baseline, without fixing B. Do not silently use donor layouts. |
| wave9, 32 | Factorial /G6, /Oy-, /Oi, /Og-, /GF. No improvement; /Og- and /Oi strongly worsen. |
| wave10, 64 | Normal, goto join, early break, inverted arms; XOR equality helper; elapsed local/helper; separate final stores in each arm. XOR changes B as described above; early-break/store duplication worsens other allocations. |
| wave12, 64 | Subtraction in both orders, XOR, two relational comparisons; signed/unsigned, value/reference parameters; direct expression and Int/Bool helper forms. No exact compare; subtraction gives the useful diagnostic above. |
| wave13, 68 | Equality helpers with Bool/Int/UnsignedInt/unsigned-char returns, value/reference/pointer parameters, direct/ternary/early-return bodies. All unchanged. One-element equal/find/count and memcmp add code and worsen. |
| wave14, 72 | Register hints on group, now, count, loop index, player and draw; /Ow, /Ow-, /Oa, /Oa-, /Zc:forScope-, /Op, explicit /Og /Os /Ob2, /O1 /Ob2 /Gs0. See receipt for final results. |

Control flow, lifetime/scope, types/layout, callee visibility/inlining and compiler
settings each received concrete trials. Retain the actual WB declaration order:
group, now, validity player/squad/objects/count/i/draw; double-tap player/squad/
objects/count; normal-selection message/player/squad/objects/count/i. The current
validity Bool temporary differs from WB but removing it produces identical code,
including after A is fixed. Broad inert-local numbering did not move B.

Five unresolved callee bindings remain as recorded in the previous compact
handoff: deselectAll 0x42F9DA, integer-map ctor 0x43001D, operator[] 0x42FE40,
dtor 0x42FD1C and _M_find 0x2888D4. /EHs still preserves the 57-byte dtor shape.
No new pin is justified until whole-body/fold and name-owner checks succeed.

## Reproduction and session checks

From the repository root:

```
python3 reverse/attempt_support/0043003c-20261020-codex7/reproduce.py
```

This writes only under build/, freshly compiles baseline/best/subtraction with
the bank's source flags, and emits their masked diagnostic JSON. It deliberately
does not substitute for build.sh, branch-map verification or pin admission.
`before.json`, `best.json` and `subtraction.json` preserve the original diagnostic
diffs. `best.align.log` preserves the independent official alignment.

Session start: clean tree at 6f04adc45b07; pull --rebase was current; check_csv
passed. BFME 1 checkout and committed pointer were clean at
92f6bbe8e1dcdb46b5d27da0674313efc822b790. The shared freshness lock was held by
claudeb2 and was under six hours old, so this seat skipped the update as directed
and did not change or certify the pointer. No broad reference/dump queue was
used in this assigned lane. Primary 0x6EFBC0 was held by another contributor;
this seat claimed the first authorized fallback, 0x43003C. No maintainer-only
verification runner was started. Final results are in receipt.json.

Next work is the same group-comparison allocation problem. Start from the new
bank; do not reintroduce the contained-pointer local or Boolean-normalize the
word mask. Compare new hypotheses against both the retained equality source and
the arithmetic diagnostic. Completing the parent still requires callee identity,
full-byte, branch-table and link acceptance. The partial remains outside Code/.
