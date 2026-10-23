// cl: /DNDEBUG /MD
// Retail RVA 0x0000712B: a four-byte mutable pointer cell, not a function.
// Dispatcher 0x00007AF3 reads it using return address 0x00007EE0 - 0xDB5.
// The target file initializes it to null. Its runtime writer and eventual
// destination remain unknown; no callable prototype is asserted.
// The fifth byte of the previously served five-byte gap is not owned here.
// The retail cell is unaligned, so its storage view has one-byte alignment.
#pragma pack(push, 1)
struct RuntimeDispatchSlot
{
    void *target;
};
#pragma pack(pop)
extern "C" {
    RuntimeDispatchSlot RuntimeDispatchTarget_0000712B = { 0 };
}
