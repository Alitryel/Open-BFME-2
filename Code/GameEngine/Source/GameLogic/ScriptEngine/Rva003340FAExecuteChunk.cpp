// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /GX-
//
// Retail 0x003340FA/57, directly after the rowed
// LuaScriptEngine::ExecuteChunk 0x003340C1 and instruction-for-instruction
// its twin: lua_dobuffer 0x0074DD00 on the chunk's text (AsciiString data +8
// or ""), then lua_settop 0 0x00746F40, but on a lua_State held at +0x10
// rather than +0xC. The owning class is not established; names are
// address-derived.
#include "ascii_string.h"

__forceinline const char *GetStr003340FA(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

struct lua_State;

extern "C" int __cdecl lua_dobuffer(struct lua_State *L, const char *buff, unsigned int size, const char *name);
extern "C" void __cdecl lua_settop(struct lua_State *L, int idx);

class Rva003340FA
{
public:
	void executeChunk(char *buff, int size, const AsciiString &chunk);

private:
	unsigned char m_pad[0x10];
	struct lua_State *m_lua;
};

void Rva003340FA::executeChunk(char *buff, int size, const AsciiString &chunk)
{
	const char *name = GetStr003340FA(chunk);
	lua_dobuffer(m_lua, buff, size, name);
	lua_settop(m_lua, 0);
}
