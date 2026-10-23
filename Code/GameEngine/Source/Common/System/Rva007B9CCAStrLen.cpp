// cl: /O1 /G6 /MD
// Address-derived identity: isolated cdecl byte-string length helper.
// Complete retail body: RVA 0x007B9CCA..0x007B9CE2 (24 bytes).
// BFME 1 RVA 0x00C72A59 has the same complete bytes. Neither image supplies
// a known caller or original symbol; this is not a canonical strlen binding.
// No owner TU is established. Keep it separate from the adjacent atexit code.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

int rva007B9CCAStrLen(const char *text)
{
    const char *cursor = text;
    char current = *cursor++;

    // This compiler-only barrier retains LEA before the entry TEST. It emits
    // no instruction and does not assert an original-source synchronization.
    _ReadWriteBarrier();
    if (current)
        goto scan;
    goto finished;

scan:
    while (current)
        current = *cursor++;

finished:
    return (int)(cursor - text - 1);
}
