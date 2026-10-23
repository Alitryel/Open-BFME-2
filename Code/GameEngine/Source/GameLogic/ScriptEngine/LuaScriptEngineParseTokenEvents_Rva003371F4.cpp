// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
//
// ?ProcessEventsElement@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// retail 0x003371F4, 195 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseTokenEvents.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// RVA 0x002EA5D0 (donor): Events dispatch reached from matched LuaScriptEngineParseToken.cpp.
// Retail string/call pairs establish InternalEvent -> 00332C7A, ScriptedEvent
// -> 00336BE4, ModelConditionEvent -> 00336C5D, ObjectStatusEvent -> 00336EB0.
// All receive the unchanged engine ECX and parser stack argument; each returns ret 4.
// BFME2 names from WorldBuilder's LuaScriptEngine.cpp: ProcessEventsElement
// (:904-932, same Events / InternalEvent / ScriptedEvent / ModelConditionEvent /
// ObjectStatusEvent dispatch) and ProcessInternalEvent for 0x00332C7A.
typedef int Int;

extern "C" int strcmp(const char *, const char *);

class XmlNameSlotList
{
public:
	Int finish();
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
};

// InternalEvent dispatch uses the established event-flag host ABI at the same this.
class __declspec(novtable) LuaScriptEngine
{
public:
	void ProcessEventsElement(BfmeLexEAN *parser);
	void ProcessInternalEvent(XmlNameSlotList *xml);
	void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
	void ProcessScriptedEvent(XmlNameSlotList *xml);
	void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);

};


void LuaScriptEngine::ProcessEventsElement(BfmeLexEAN *parser)
{
	char *tail = parser->getTailEAN();
	int cmpEvents = strcmp(tail, "Events");
	if (cmpEvents != 0)
		return;

	Int status = ((XmlNameSlotList *)parser)->finish();
	while (status != 0)
	{
		if (--status != 0)
			return;

		const char *tag = parser->getTailEAN();
		int cmp;

		cmp = strcmp(tag, "InternalEvent");
		if (cmp == 0)
		{
			ProcessInternalEvent((XmlNameSlotList *)parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ScriptedEvent");
		if (cmp == 0)
		{
			// The recovered provider uses the same parser view as finish/InternalEvent.
			ProcessScriptedEvent((XmlNameSlotList *)parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ModelConditionEvent");
		if (cmp == 0)
		{
			rva002E9680ParseModelConditionEvent(parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ObjectStatusEvent");
		if (cmp != 0)
			return;

		rva002E9AA0ParseObjectStatusEvent(parser);

	checkFinish:
		status = ((XmlNameSlotList *)parser)->finish();
	}
}
