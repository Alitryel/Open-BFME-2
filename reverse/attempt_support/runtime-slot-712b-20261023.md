# Unaligned runtime dispatch target cell at RVA 0x0000712B

The previous attempts correctly identified this range as data, not a function.
No dispatcher, resolver or import identity is invented by this change.

Target evidence: the seven-byte entry at 0x7ED9 pushes ECX and EAX, then
calls 0x7AF3, leaving return address 0x7EE0. The dispatcher loads -3509,
pops that return into ECX, adds them and reads exactly one four-byte word
at 0x712B, then jumps through that word. Retail holds four zero bytes there.
The fifth byte of the previously served gap is not read and is not claimed.

The source models only this four-byte mutable null target, with a packed
one-byte-aligned storage view because the retail address is unaligned.
RuntimeDispatchTarget_0000712B is an address-derived evidence label, not
an original symbol claim. No function-pointer signature is asserted.
The normal data gate proves sizeof=4 and the complete zero initializer.
There is no initialized address or relocation to guess. This is four bytes
of verified data ownership, not a functioning dispatcher reconstruction.
No linker placement or runtime behavior test is claimed.

The analogous cell at 0x735B holds 0x66825AB4, outside the target image.
Its dispatch path computes 0x8450 - 4341 = 0x735B. Its destination and runtime
writer are still unknown. We do not turn that unresolved address into an
invented import or treat its fifth surrounding byte as a proven object field.
The four related dispatch stubs remain on their existing blocked verdicts.
Future runtime work needs the binding/writer mechanism and entry register/
stack contract. Static data ownership of the null cell does not provide it.
