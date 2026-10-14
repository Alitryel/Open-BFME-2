// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters7.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva0018123CGet@@YAHXZ @ 0x0018123c (6B): returns 0x00000001.
// Conditional-skip target (cmp / jne +6). Opaque address-derived name.
int Rva0018123CGet(void)
{
	return 0x00000001;
}
