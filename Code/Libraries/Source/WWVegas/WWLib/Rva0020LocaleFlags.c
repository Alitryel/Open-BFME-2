// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

// These four 49-byte BFME 2 bodies have confirmed retail boundaries and
// distinct locale-info type values. Their BFME 1 donor names are ICF-ambiguous,
// so keep the target definitions address-named until target callers establish
// stronger identities. Donor code supplies the equivalent locale flag logic;
// the imported call, field offset, and each immediate are verified in retail.
__declspec(dllimport) int __stdcall GetLocaleInfoA(unsigned long, unsigned long, char *, int);

typedef struct Rva0020LocaleFlagInput
{
	unsigned long lcid;
} Rva0020LocaleFlagInput;

#define BFME_LOCALE_FLAG(RVA, FLAG)                                      \
int Rva##RVA##LocaleFlag(Rva0020LocaleFlagInput *locale)                 \
{                                                                        \
	char value[2];                                                        \
	GetLocaleInfoA(locale->lcid, FLAG, value, 2);                         \
	if (value[0] == '0')                                                  \
		return 0;                                                           \
	return value[0] == '1' ? 1 : -1;                                      \
}

BFME_LOCALE_FLAG(0020F20, 0x54)
BFME_LOCALE_FLAG(0020F60, 0x55)
BFME_LOCALE_FLAG(0020FD0, 0x56)
BFME_LOCALE_FLAG(0021010, 0x57)
