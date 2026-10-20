# 0x006C4730 GeneralAllocatorDebug realloc: materialized trailer, 814 B attractor (2026-10-20)

Bank `reverse/attempts/0x006c4730.cpp` is unchanged (798 B, 3 instructions off, all
in the backup-allocation trailer). This round looked for a C++ spelling of the
trailer that is exact without memset. It found one, but that spelling moves the
function's register allocation to an 814 B layout. Earlier rounds:
`allocator-trailer-copyprop-20261020.md` and `allocator-header-lifetime-20261020.md`.

Retail trailer (inlined Malloc inside the retry loop):

    and ecx,0x7ffffff8 ; add ecx,4 ; jmp J ; and ecx,0x7ffffff8
    J: lea ecx,[ecx+eax-0xa] ; mov word [ecx],bx

## Exact trailer, wrong allocation

This gives retail's trailer instructions exactly, with a pointer phi of per-arm
pointers and a named size kept apart from the -10:

    unsigned short *t;
    if (!(h & 2)) {
        unsigned int n = (h & 0x7FFFFFF8) + 4;
        t = (unsigned short *)((char *)p + n - 10);
    } else {
        unsigned int n = h & 0x7FFFFFF8;
        t = (unsigned short *)((char *)p + n - 10);
    }
    *t = 0;

The two per-arm leas cross-jump into retail's single lea at the join. Every
variant of this form compiles to the same 814 B allocation:

- `extra + 2` is hoisted into ebx, so the loop has no `jmp`/align and no `lea eax,[edi+2]`;
- the zero register is esi, not ebx;
- data is not kept in esi;
- the frame is 0x540, not 0x544;
- the store becomes `mov word [ecx],0`.

Variants tried, all 814 B unless noted:

- **Trailer spellings.** Store in each arm (folds the store and keeps 814). A
  `char *` pointer. A function-scope `n`. Pointer arithmetic `- 5`. `n` written
  as `+=` in one arm. Reusing `h` or the `size` parameter as `n`. The arms in
  reverse order.
- **Loop and inline shape.** `for(;;)`. `while(!(...))`. Assigning `backup`
  separately. `mallocBackup(backupLength + 2)`. `+2` inside the inline. The
  inline in the shape of 0x6C1CC0 (`flags` parameter, `if (flags & 0x80000000)
  size += 2`).
- **Locals.** The declaration order permute found. `long`, `unsigned long` and
  `bool` types. `992 < extra`. `/Op`.
- **oldChunk.** A `?:` initializer (850 B). An initializer at function scope
  (812 B). The else-path assignment placed last (815 B). `char *` type.
  `GeneralAllocatorChunk *` type. Computing it inline at `bookBlock`. Assigning
  it after `rva006C2510` (812 B).
- **Temp counts.** The first trailer without `h`. The second trailer
  (`chunk + capacity - 2`) without `h`, as an if/else, or without `chunk`.

The per-arm constant form (`t = p + (h&M) + 4 - 10`, or `chunk + ... - 2`) keeps
the bank's allocation (798 B). It emits `lea ecx,[ecx+eax-6]` in the first arm
in place of `add ecx,4`, so it is no better than the bank.

## Permute

`build/permute/0x006c4730/flags_best.cpp` was seeded with the form above. After
1698 trials permute reached a best of 0.911. Its best text keeps the materialized
trailer *and* retail's ebx and loop allocation, but only by breaking semantics.

Bisecting that best text (each hunk reverted alone, then reverted in groups)
shows the allocation comes back only when all of these hold together:

- oldChunk is assigned after `rva006C2510`, where retail computes `lea eax,[esi-8]` before the call;
- `bookBlock(oldChunk,false)` runs after `rva000347A0`, where retail books the old block first;
- the else path leaves `total` unset.

Without the bookBlock move the result is 791 B, and the store becomes immediate.
Without the else-path change it is 812 B, and the store uses `si`.

So the live range of oldChunk in the data path is the lever that takes the
allocator off the 814 B layout. No semantically valid placement of oldChunk has
been found yet.

## Untried

- A source in which oldChunk does not live in a register across the backup loop
  in the data path: a different owner for the chunk pointer, for example a
  value carried in the debug-data call.
- Running permute again from the R1 form with semantic guards
  (its mutations change call order and leave variables unset).
