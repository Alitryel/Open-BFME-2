// cl: /O2 /GB /arch:SSE /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// Native6889F0..688A9B,171B;4CC leading/5CC trailing; RET4.
// Same receiver reaches the owned reset6888D0 and the path string at+8.
// INI loader2DA4B takes the named parseVideoDefinition callback75A4DC.
// BF1 a7c38d3b VideoPlayerInit.cpp guides the INI lifetime and callback load;
// Bfme5HandOffClears.cpp guides the existing receiver reset. Name unresolved.
#include <string.h>
#include "string_base.h"
// Visible original StringBase C-string setter: receiver is computed before
// its inlined nullable strlen, as it is in the native calling sequence.
template <> __forceinline void StringBase<char>::set(const char *text) {
    set(text, text ? strlen(text) : 0);
}
#include "ascii_string.h"
// bfme link decl-only begin
template <> void StringBase<char>::set(char const *);
// bfme link decl-only end
class Xfer;
enum INILoadType {INI_LOAD_INVALID,INI_LOAD_OVERWRITE};
class INI {
public:
    INI();
    ~INI();
    void load(AsciiString,INILoadType,Xfer*,void(*)(INI*));
    static void parseVideoDefinition(INI*);
private:
    char storage[0x87C];
};
class Rva00688980 {
public:
    void rva006888D0();
    void rva006889F0(const char *path);
private:
    char prefix[8];
    AsciiString name;
};
void Rva00688980::rva006889F0(const char *path)
{
    rva006888D0();
    name = path;
    INI ini;
    ini.load(path,INI_LOAD_OVERWRITE,0,INI::parseVideoDefinition);
}
