// cl: /Od /GZ /GS /MT /DNDEBUG
/* EA DirtySock diagnostic printer, ported verbatim from BFME1
 * Y4DirtySockDebug.c. Retail 0x0066AC50 (214B Ghidra, 242B BFME1).
 *
 * Separate TU from the socket wrappers for one reason: /GS. This body ends
 * with the cookie epilogue and the socket bodies do not; /GS is whole-file.
 */
#include <stdarg.h>
#include <stdio.h>

void (__stdcall *g_Rva01358EA8Print)(const char *text) = 0;

int Rva007FE780(const char *pFormat, ...)
{
	va_list pArgs;
	char strText[0x1000];
	const char *pText;

	pText = strText;
	va_start(pArgs, pFormat);

	if (pFormat[0] == '%' && pFormat[1] == 's' && pFormat[2] == 0)
	{
		pText = va_arg(pArgs, const char *);
	}
	else
	{
		vsprintf(strText, pFormat, pArgs);
	}
	va_end(pArgs);

	g_Rva01358EA8Print(pText);

	return 0;
}
