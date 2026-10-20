# 0x006C4730 GeneralAllocatorDebug::rva006C4730: backup trailer, copy-propagation round (claude3, 2026-10-20)

The bank `reverse/attempts/0x006c4730.cpp` is unchanged at fit 0.98688, with 3 instructions different, all in the backup trailer.

- Retail: `and; add ecx,4; jmp; and; lea ecx,[ecx+eax-0xa]; mov word ptr [ecx],bx`.
- Bank: a pointer phi gives `lea ecx,[ecx+eax+4]` and `add ecx,eax`, then `mov [ecx-0xa],bx`.
- The flag sweep and `permute.py 0x006C4730 --minutes 30` (936 trials, stop: no gain in 600) both stayed at 0.9869.

## New finding: the lea needs a named pointer that copy propagation cannot remove

| Variant | Trailer | Effect on the rest |
| --- | --- | --- |
| `unsigned int n = !(h&2) ? (h&M)+4 : (h&M); void *t = (char*)p+n-10; memset(t,0,2);` | retail's exact trailer bytes | data and backup swap esi and stack slot; frame 0x540 (fit 0.774, nd 118) |
| Same plus one extra zero use in the retry region | retail's exact trailer bytes | fit 0.806, nd 94 |
| `memset((char*)p+n-10,0,2)` (no local) | folds to `[ecx+eax-0xa]` | 784 B |
| memset inside an inline helper | folds to `[ecx+eax-0xa]` | 784 B |

So the materialization comes from a live user variable. An intrinsic argument blocks its propagation. memset's zero does not count toward the ebx zero-register weight, and the extra live variable flips the esi priority.

## Refuted this round

Every spelling below gives `mov word [ecx+eax-0xa],bx` (784 B, the size-phi family, fit 0.945) unless noted.

- **Inline helpers:**
  - a helper returning `unsigned short &`;
  - a helper returning `unsigned short *`, with and without a named `t`;
  - an inline size helper, with `?:`, if/return or if/else assignment;
  - a size helper using `(h&M) + (!(h&2)?4:0)` (worse, 0.878).
- **Pointer spellings:**
  - `(unsigned short*)(p+n) - 5`;
  - `p - 10 + n`;
  - `t -= 10`;
  - `t[0]`;
  - index form `((unsigned short*)p)[(n-10)/2]` (0.9755, shr form).
- **Integer arithmetic:**
  - `(unsigned int)p + n - 10`, inline or through a named `unsigned int t`;
  - the second trailer's `chunk = p-8; *(unsigned short*)(chunk+capacity-2) = 0`, as char* and as unsigned int.
- **Store and type variants:**
  - a static const zero source;
  - a 16-bit bitfield, and a 15+1 bitfield pair;
  - a volatile store;
  - a double store;
  - a store followed by a read-back test.
- **Hints:** `__assume(t != 0)` before or after the store, `if (!t) __assume(0)`, `__noop(t)`.
- **Pointer phi:** a pointer phi with -10 in each arm gives `mov [ecx],bx`, but the arms change to `lea ecx,[ecx+eax-6]`. This is fit 0.97589 with only 2 instructions different, but it is not retail's arm shape.

## Open lead

Find what keeps the address alive as a register without an intrinsic. Candidates:

- a live pointer reused by the devirtualised inline `Malloc` (WB 0x0070BE40 reaches the trailer through vtable +0x88);
- a pointer return value that the caller also uses.

Alternatively, pair the memset form with a source change that gives `data` back to esi. Retail keeps `backup` in slot `[esp+0x14]`, shared with the `localBackup` address.
