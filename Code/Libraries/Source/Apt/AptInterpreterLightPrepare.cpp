// cl: /O2 /MD /EHsc /I.
// Native 006FD300..006FD331 is the light PrepareForExecution sibling.
// It asserts the same thrown-value state as the named700090 sibling,
// using AptActionInterpreter.cpp:0x857, and returns PushStaticData().
// The unused setup pointer is retained because native RET4 proves its ABI.
#include "Code/Libraries/Source/Apt/AptObject/AptScriptFunction.h"
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct AptActionSetup;
class AptActionInterpreter {
    char prefix[0x60];
    AptValue *mpThrownValue;
public:
    void *rva006FD300(AptActionSetup *);
};
void *AptActionInterpreter::rva006FD300(AptActionSetup *) {
    if (mpThrownValue) {
        g_bfmeAptAssertAtE17734("!hasThrownValue()",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x857);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return AptScriptFunctionBase::PushStaticData();
}
