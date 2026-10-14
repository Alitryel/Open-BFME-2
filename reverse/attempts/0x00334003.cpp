// ?rva00334003@Rva00334003@@QAEXPAUlua_State@@PBURva00333374IdOwner@@@Z
// partial score=0.976 date=2026-10-14
// ?rva00334003@Rva00334003@@QAEXPAUlua_State@@PBURva00333374IdOwner@@@Z
// partial score=0.95 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
//
// ?rva00334003@Rva00334003@@QAEXPAUlua_State@@PBURva00333374IdOwner@@@Z, retail 0x00334003, 165B.
// Thiscall Lua push-nil-or-global helper: null id-owner pushes nil through
// this+0xC lua_State; else AsciiString via rowed Rva00333374Get 0x00333374,
// str-or-empty-global 0xBBAC1C for lua_getglobal, top/type check plus rowed
// Rva00990030Lookup 0x00747190 id compare, then settop/pushnil. Callers
// 0x00334634/0x00334860 prove thiscall two-arg shape with ret 8.
#include "ascii_string.h"

struct lua_State;
extern "C" {
void lua_pushnil(lua_State *L);
void lua_getglobal(lua_State *L, const char *name);
int lua_gettop(lua_State *L);
int lua_type(lua_State *L, int idx);
void lua_settop(lua_State *L, int idx);
}

struct Rva00333374IdOwner
{
	unsigned char m_pad[0x74];
	int m_id;
};

AsciiString Rva00333374Get(const Rva00333374IdOwner *p);

struct Rva00990030Range;
unsigned int Rva00990030Lookup(Rva00990030Range *range, int index);

extern const char g_Rva0107301CEmptyString[];

class Rva00334003
{
public:
	unsigned char m_pad[0xC];
	lua_State *m_lua;
	void rva00334003(lua_State *L, const Rva00333374IdOwner *p);
};

// ?rva00334003@Rva00334003@@QAEXPAUlua_State@@PBURva00333374IdOwner@@@Z present-unmatched
void Rva00334003::rva00334003(lua_State *L, const Rva00333374IdOwner *p)
{
	if (!p) {
		lua_pushnil(m_lua);
		return;
	}
	AsciiString name = Rva00333374Get(p);
	int id = p->m_id;
	char *t = *(char **)&name;
	const char *s = t ? t + 8 : g_Rva0107301CEmptyString;
	lua_getglobal(m_lua, s);
	int top = lua_gettop(L);
	if (lua_type(m_lua, top) == 1 || id != (int)Rva00990030Lookup((Rva00990030Range *)m_lua, top)) {
		lua_settop(m_lua, top);
		lua_pushnil(m_lua);
	}
}
