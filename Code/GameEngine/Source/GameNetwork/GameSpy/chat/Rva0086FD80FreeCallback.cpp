// cl: /DNDEBUG /MD

// ?Rva0086FD80FreeCallback@@YAXPAURva0086FD80Callback@@@Z @ 0x006AF5F0 (17B)
// BFME1 donor at 0x0086FD80; function and callback type names remain
// address-derived. Target loads the pointer at +0x14 and tail-jumps through
// the CRT free import. The target starts after int3 padding. The struct
// layout is donor-carried; the imported free call is target evidence.
extern "C" __declspec(dllimport) void __cdecl free(void *);

struct Rva0086FD80Callback
{
    unsigned char pad[0x14];
    void *data;
};

void Rva0086FD80FreeCallback(Rva0086FD80Callback *callback)
{
    free(callback->data);
}
