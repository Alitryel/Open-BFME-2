// cl: /DNDEBUG /MD /EHs-c- /Oy- /ICode/Libraries/Source/WWVegas/WWDebug
//
// DebugExceptionhandler::LogFPURegisters, retail 0x0003CD30 (635 bytes),
// converted from the Zero Hour debug_except.cpp body; ExceptionFilter
// (0x0003DCD0) calls it right after LogRegisters. The only BFME2 change is
// the Debug layout: width at +0x9F50 and fill character at +0x9F54, as in
// DebugExceptionhandler_LogRegisters.cpp.

#include "BfmeDebugExceptionView.h"

// ?LogFPURegisters@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
void DebugExceptionhandler::LogFPURegisters(Debug &dbg, struct _EXCEPTION_POINTERS *exptr)
{
	struct _CONTEXT &ctx = *exptr->ContextRecord;

	if (!(ctx.ContextFlags & 0x10008)) // CONTEXT_FLOATING_POINT
	{
		dbg << "FP registers not available\n";
		return;
	}

	FLOATING_SAVE_AREA &flt = ctx.FloatSave;
	dbg << Debug::Bin() << Debug::FillChar('0')
		<< "CW:" << Debug::Width(16) << (flt.ControlWord & 0xffff) << "\n"
		<< "SW:" << Debug::Width(16) << (flt.StatusWord & 0xffff) << "\n"
		<< "TW:" << Debug::Width(16) << (flt.TagWord & 0xffff) << "\n"
		<< Debug::Hex()
		<< "ErrOfs:      " << Debug::Width(8) << flt.ErrorOffset
		<< " ErrSel:  " << Debug::Width(8) << flt.ErrorSelector << "\n"
		<< "DataOfs:     " << Debug::Width(8) << flt.DataOffset
		<< " DataSel: " << Debug::Width(8) << flt.DataSelector << "\n"
		<< "Cr0NpxState: " << Debug::Width(8) << flt.Cr0NpxState << "\n";

	for (unsigned k = 0; k < 80 / 10; ++k)
	{
		dbg << Debug::Dec() << "ST(" << k << ") ";
		dbg.SetPrefixAndRadix("", 16);

		unsigned char *value = flt.RegisterArea + k * 10;
		for (unsigned i = 0; i < 10; i++)
			dbg << Debug::Width(2) << value[i];

		double fpVal;

		// convert from temporary real (10 byte) to double
		__asm
		{
			mov eax, value
			fld tbyte ptr [eax]
			fstp qword ptr [fpVal]
		}

		dbg << " " << fpVal << "\n";
	}
	dbg << Debug::FillChar() << Debug::Dec();
}
