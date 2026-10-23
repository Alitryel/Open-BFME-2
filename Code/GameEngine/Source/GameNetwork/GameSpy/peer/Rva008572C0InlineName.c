// cl: /DNDEBUG /MD

// _Rva008572C0InlineName @ 0x00698880 (17B)
// BFME1 peer reconstruction at 0x008572C0; function/type names remain
// address-derived. Retail starts after int3 padding and exactly matches the
// donor: it tests the byte at record+0x60 and returns that pointer only when
// nonempty. The offset semantics are target bytes; the record type is donor-
// carried.

char *Rva008572C0InlineName(void *record)
{
    char *name = (char *)record + 0x60;
    return *name ? name : 0;
}
