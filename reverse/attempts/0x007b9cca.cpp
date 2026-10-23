// rva007B9CCAStrLen
// partial score=0.7916666667 date=2026-10-23
// cl: /O1 /G6 /MD
// Best new candidate (astra-s3 helper seat, 2026-10-23): 24 bytes, 5 differing
// byte positions vs retail 0x7B9CCA (parent's best was 6).
// Emits: 8b4c2404 8a11 84d2 8d4101 7407 8a10 40 84d2 75f9 2bc1 48c3
// Retail: 8b4c2404 8a11 8d4101 84d2 7407 8a10 40 84d2 75f9 2bc1 48c3
// The only delta: guard block order (test/lea swapped). The je+7 and jne-latch
// bytes are exact without volatile, ja/jbe or unsigned casts.
int rva007B9CCAStrLen(const char *s) {
    const char *p = s;
    char c;
    if ((c = *p++)) goto loop;
    goto out;
loop:
    while (c) { c = *p++; }
out:
    return (int)(p - s - 1);
}
