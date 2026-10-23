// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// ?rva001FD19E@Rva001FD19E@@QAEPBDH@Z @0x001FD19E 25B bounds-checked slot getter stride 4 offset 0x48 OOB empty string caller 0x00241ECC
// The ten 4-byte slots are AsciiStrings: out of range retail returns the
// exported AsciiString::TheEmptyString (VA 0x00DE0878, zero-filled .data),
// not a string literal. The callers' spelling returns the slot as const char *.
#include "ascii_string.h"

class Rva001FD19E
{
public:
	const char *rva001FD19E(int index);
private:
	char m_pad[0x48];
	AsciiString m_slots[10];
};

const char *Rva001FD19E::rva001FD19E(int index)
{
	if (index < 0 || index >= 10)
		return (const char *)&AsciiString::TheEmptyString;
	return (const char *)&m_slots[index];
}
