// ?rva00336E1E@@YA_NXZ
// partial score=0.812 date=2026-10-17
// cl: /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// ?rva00336E1E@@YA_NXZ, retail 0x00336e1e, 84 bytes.
// Body of the debug-only error path of LuaScriptEngineParseScriptedEvent:
// the debug macro's guard call, then a chain of engine->something() calls.
#include <vector>
#include <string.h>
#pragma function(strcmp)

// Debug macro helpers (retail keeps the guard call and the record call).
extern bool bfmeRva000387C0();
extern void _bfme_debugRecordCallsite(int);

// The engine singleton pointer lives in a global slot at 0xde0880; the
// disassembly loads it, then walks virtual calls at +0x60/+0x6c/+0x38/+0x4c.
// We only need the two vtable slots the body actually reaches, as members of
// an opaque object whose vtable is laid out as the retail one.
struct DebugStream {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual DebugStream *method38(const char *);
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void method4c(int);
};

struct EngineVtbl {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual DebugStream *method60();
    virtual void pad25();
    virtual void pad26();
    virtual DebugStream *method6c();
};

struct Engine {
    EngineVtbl *vptr;
};

extern Engine *g_engine; // at 0xde0880

// The "Error during parsing XML data: " literal is at 0xc0e31c in retail; we
// reproduce it as a string constant used through the same call chain.

bool rva00336E1E() {
    static const char * const kPtr = (const char*)0xc0e31c;
    if (bfmeRva000387C0()) {
        _bfme_debugRecordCallsite(1);
        volatile Engine &eRef = *(volatile Engine *)&g_engine;
        DebugStream *s = eRef.vptr->method60();
        *(volatile EngineVtbl **)&eRef.vptr;
        s = eRef.vptr->method6c();
        s = s->method38(kPtr);
        const char *p0 = *(const char **)0;
        const char *p1 = *(const char * volatile *)p0;
        s = s->method38(p1);
        s->method4c(2);
    }
    return true;
}
