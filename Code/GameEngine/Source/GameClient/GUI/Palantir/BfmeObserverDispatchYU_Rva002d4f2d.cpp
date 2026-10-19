// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/Palantir
//
// BFME2 literal fix: retail's two statics name "NonCommand_MultiplayerOptions"
// (VA 0x00C02D90, the observer-active arm) and "NonCommand_Options" (VA
// 0x00C02D7C, the inactive arm); the donor carried BFME1's "NonCommand_Objectives"
// and "NonCommand_PlayerStatus". Only the literals differ; the body is byte-equal.
//
// Open-BFME5: the observer-dependent command dispatch at retail 0x0058EDB0,
// 228 bytes.  Same two-static shape as 0x0058ECA0, but the selector is a live
// observer plus a predicate call rather than a flag bit.

class AsciiStringYU
{
public:
	AsciiStringYU(const char *text);

	~AsciiStringYU(void);
};

#include "../../../Common/GameLogicObjectLookupView.h"

// The global at 0x012F33F8 is the ControlBar singleton; only the accessor
// spellings the method pins carry are declared here.
class GameWindow;
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void rva004C1B60(GameWindow *window, void *entry);
};
extern GameLogic *TheGameLogic;				// retail 0x012F0898
extern ControlBar *TheControlBar;			// retail 0x012F33F8

// ?bfmeApplyYU@@YGXH@Z
void __stdcall bfmeApplyYU(int unused)
{
	AsciiStringYU *name;

	if (TheGameLogic != 0 && TheGameLogic->isInMultiplayerGame())
	{
		static AsciiStringYU s_bfmeObjectivesYU("NonCommand_MultiplayerOptions");

		name = &s_bfmeObjectivesYU;
	}
	else
	{
		static AsciiStringYU s_bfmeOtherYU("NonCommand_Options");

		name = &s_bfmeOtherYU;
	}

	const CommandButton *entry = TheControlBar->findCommandButton(*(const AsciiString *)name);

	if (entry != 0)
		TheControlBar->rva004C1B60(0, (void *)entry);
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??0AsciiStringYU@@QAE@PBD@Z=??0?$StringBase@D@@AAE@PBD@Z")
#pragma comment(linker, "/alternatename:??1AsciiStringYU@@QAE@XZ=??1?$list@URva0036ADF9Element@@V?$allocator@URva0036ADF9Element@@@_STL@@@_STL@@QAE@XZ")
