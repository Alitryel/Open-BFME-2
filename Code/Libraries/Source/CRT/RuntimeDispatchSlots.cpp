// cl: /DNDEBUG /MD
// Retail RVA 0x0000712B: a four-byte mutable pointer cell, not a function.
// Dispatcher 0x00007AF3 reads it using return address 0x00007EE0 - 0xDB5.
// The target file initializes it to null. Its runtime writer and eventual
// destination remain unknown; no callable prototype is asserted.
// The fifth byte of each gap is represented separately as zero fill, not as
// a pointer field or an additional byte consumed by the dispatcher.
// The retail cell is unaligned, so its storage view has one-byte alignment.
#pragma pack(push, 1)
struct RuntimeDispatchSlot
{
    void *target;
};
// The second dispatcher reads another complete 32-bit cell. Its initial
// bits are outside this image; no resolved import or callable type is known.
// Preserve the observed initial state as mutable raw bits, not a guessed
// address relocation. RuntimeDispatchSlot's null pointer view is unchanged.
struct RuntimeDispatchOpaqueSlot
{
    unsigned int target_bits;
};
#pragma pack(pop)
extern "C" {
    RuntimeDispatchSlot RuntimeDispatchTarget_0000712B = { 0 };
    // 0x00008450 - 4341 = 0x0000735B; native reads exactly four bytes.
    // The following zero byte is not part of the proven field.
    RuntimeDispatchOpaqueSlot RuntimeDispatchBits_0000735B = { 0x66825AB4u };
    // Separate zero fill before the next 16-byte-aligned function entries.
    // Neither byte belongs to a reconstructed runtime pointer object.
    unsigned char RuntimeDispatchFill_0000712F = 0;
    unsigned char RuntimeDispatchFill_0000735F = 0;
}
