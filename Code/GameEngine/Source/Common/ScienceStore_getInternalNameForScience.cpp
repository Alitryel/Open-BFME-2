// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// Native callers306273 and37C0B7 load TheScienceStore intoECX; the donor
// ScienceStore::getInternalNameForScience supports the unused receiver.
// It is Zero Hour's and BFME1's ScienceStore::getInternalNameForScience (BFME1
// 0x000E71F0: the same invalid test, then NameKeyGenerator::keyToName).
// RET8 accounts for the hidden return pointer and key, not a free ABI.
enum NameKeyType
{
	NAMEKEY_INVALID = -1
};
enum ScienceType
{
	SCIENCE_INVALID = -1
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ScienceStore {public:AsciiString getInternalNameForScience(ScienceType science) const;};

AsciiString ScienceStore::getInternalNameForScience(ScienceType science) const
{
	if (science == SCIENCE_INVALID)
		return AsciiString::TheEmptyString;
	return TheNameKeyGenerator->keyToName((NameKeyType)science);
}
