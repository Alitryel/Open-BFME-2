// cl: /DNDEBUG /MD
//
// ?findBlockParse@@YAP6AXPAVINI@@@ZPBD@Z @0x0002BBFC (43B).
// Out-of-line copy of the block finder that INI::parseLine (0x0002C0F5,
// INIParseLineBFME2.cpp) inlines: walk theBlockParseList (VA 0x00DDF578) and
// return the parse callback of the node whose token strcmp-equals the key,
// else 0. Target facts: cdecl, one stack argument, plain RET; node layout
// { next +0, token +4, parse +8 } is the BlockParse registration record
// (Rva007ABBF6BlockParseInits.cpp). Name and semantics carried from Zero
// Hour's INI.cpp findBlockParse and the BFME1 donor's linked-list form; the
// named token local reproduces retail's MOV-load of the node token before
// the key push, as in the inlined parseLine copy.

// strcmp without dllimport, as in INIParseLineBFME2.cpp: E8 into the linker
// thunk at 0x006291C6 like retail.
extern "C" int __cdecl strcmp(const char *s1, const char *s2);

typedef void (*INIBlockParse)(class INI *ini);

struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;
};

extern BlockParse *theBlockParseList;

INIBlockParse findBlockParse(const char *token)
{
	for (BlockParse *parse = theBlockParseList; parse; parse = parse->next)
	{
		const char *name = parse->token;
		if (strcmp(name, token) == 0)
			return parse->parse;
	}
	return 0;
}
