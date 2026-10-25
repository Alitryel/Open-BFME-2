// cl: /DNDEBUG /MD /EHs-c- /Oy- /ICode/Libraries/Source/WWVegas/WWDebug
// Open-BFME: DebugExceptionhandler::LogRegisters, converted from the
// verified GeneralsMD debug exception implementation.

#include "BfmeDebugExceptionView.h"

// ?LogRegisters@DebugExceptionhandler@@CAXAAVDebug@@PAU_EXCEPTION_POINTERS@@@Z
void DebugExceptionhandler::LogRegisters(Debug &dbg, struct _EXCEPTION_POINTERS *exptr)
{
    struct _CONTEXT &ctx = *exptr->ContextRecord;

    dbg << Debug::FillChar('0')
        << Debug::Hex()
        << "EAX:" << Debug::Width(8) << ctx.Eax
        << " EBX:" << Debug::Width(8) << ctx.Ebx
        << " ECX:" << Debug::Width(8) << ctx.Ecx
        << "\n"
        << "EDX:" << Debug::Width(8) << ctx.Edx
        << " ESI:" << Debug::Width(8) << ctx.Esi
        << " EDI:" << Debug::Width(8) << ctx.Edi
        << "\n"
        << "EIP:" << Debug::Width(8) << ctx.Eip
        << " ESP:" << Debug::Width(8) << ctx.Esp
        << " EBP:" << Debug::Width(8) << ctx.Ebp
        << "\n"
        << "Flags:" << Debug::Bin() << Debug::Width(32) << ctx.EFlags
        << Debug::Hex() << "\n"
        << "CS:" << Debug::Width(4) << ctx.SegCs
        << " DS:" << Debug::Width(4) << ctx.SegDs
        << " SS:" << Debug::Width(4) << ctx.SegSs
        << "\nES:" << Debug::Width(4) << ctx.SegEs
        << " FS:" << Debug::Width(4) << ctx.SegFs
        << " GS:" << Debug::Width(4) << ctx.SegGs
        << "\n" << Debug::FillChar() << Debug::Dec();
}
