// ??0Rva00419C7F@@QAE@XZ
// partial score=1.0 date=2026-10-14
// cl: /O1 /MD /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
// Native419B94..419BA5 and factory419BCD allocate the same12B stringbuf
// object: vtableC3ABC4; bool+4; AsciiString+8. Its first slot is the owned
// Rva00419C7F scalar destructor419C63 and destructor419C7F frees that string.
// DebugIOInterface in the ZH reference supplies Read/Write/Flush/Execute/Delete
// semantics. BFME2 adds one zero-argument bool slot at+8; purpose unknown.
#include "ascii_string.h"
class Debug;
class Rva00419C7F {
public:
 Rva00419C7F();
 virtual ~Rva00419C7F();
 virtual int Read(char *,int) { return 0; }
 virtual bool rva0073B660() { return false; }
 virtual void Write(int,const char *,const char *);
 virtual void EmergencyFlush() {}
 virtual void Execute(Debug &,const char *,bool,unsigned int,const char *const *) {}
 virtual void Delete();
private:
 bool m_enabled;
 AsciiString m_text;
};
Rva00419C7F::Rva00419C7F() : m_enabled(false) {}
