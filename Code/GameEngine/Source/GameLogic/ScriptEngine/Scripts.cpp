// cl: /DsetScriptList=setScriptList_Scripts_RV /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/scriptenginevtable /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Scripts.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   Generals
//
// File name: Scripts.cpp
//
// Created:   John Ahlquist, Nov 2001
//
// Desc:      Contains the information describing scripts.
//
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Lib/BaseType.h"

#define DEFINE_BUILDABLE_STATUS_NAMES
#define DEFINE_OBJECT_STATUS_NAMES
#define DEFINE_SCIENCE_AVAILABILITY_NAMES

#include "Common/BorderColors.h"
#include "Common/DataChunk.h"
#include "Common/GameState.h"
#include "Common/KindOf.h"
#include "Common/Radar.h"
#include "Common/ThingTemplate.h"
#include "Common/Player.h"
#include "Common/Xfer.h"

#include "GameClient/ShellHooks.h"

#include "GameLogic/Ai.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/Module/ContainModule.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


static Script *s_mtScript = NULL;
static ScriptGroup *s_mtGroup = NULL;

// The carved body at 0x001FC3D0 is a second copy of Script::getAction.
// Script::setAction stores at +0x28, setFalseAction stores at +0x2C, and
// setNextScript stores at +0x30, which proves the member layout.
class Rva001FC3D0ScriptAction
{
public:
	ScriptAction *getAction(void) const;

private:
	char m_prefix[0x28];
	ScriptAction *m_action;
};

// ?getAction@Rva001FC3D0ScriptAction@@QBEPAVScriptAction@@XZ
// ?getAction@Rva001FC3D0ScriptAction@@QBEPAVScriptAction@@XZ present-unmatched
ScriptAction *Rva001FC3D0ScriptAction::getAction(void) const
{
	return m_action;
}

//
// These strings must be in the same order as they are in their definitions 
// (See SHELL_SCRIPT_HOOK_* )
//
char *TheShellHookNames[]=
{
	"ShellMainMenuCampaignPushed", //SHELL_SCRIPT_HOOK_MAIN_MENU_CAMPAIGN_SELECTED,
	"ShellMainMenuCampaignHighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_CAMPAIGN_HIGHLIGHTED,
	"ShellMainMenuCampaignUnhighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_CAMPAIGN_UNHIGHLIGHTED,

	"ShellMainMenuSkirmishPushed", //SHELL_SCRIPT_HOOK_MAIN_MENU_SKIRMISH_SELECTED,
	"ShellMainMenuSkirmishHighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_SKIRMISH_HIGHLIGHTED,
	"ShellMainMenuSkirmishUnhighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_SKIRMISH_UNHIGHLIGHTED,

	"ShellMainMenuOptionsPushed", //SHELL_SCRIPT_HOOK_MAIN_MENU_OPTIONS_SELECTED,
	"ShellMainMenuOptionsHighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_OPTIONS_HIGHLIGHTED,
	"ShellMainMenuOptionsUnhighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_OPTIONS_UNHIGHLIGHTED,

	"ShellMainMenuOnlinePushed", //SHELL_SCRIPT_HOOK_MAIN_MENU_ONLINE_SELECTED,
	"ShellMainMenuOnlineHighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_ONLINE_HIGHLIGHTED,
	"ShellMainMenuOnlineUnhighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_ONLINE_UNHIGHLIGHTED,

	"ShellMainMenuNetworkPushed", //SHELL_SCRIPT_HOOK_MAIN_MENU_NETWORK_SELECTED,
	"ShellMainMenuNetworkHighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_NETWORK_HIGHLIGHTED,
	"ShellMainMenuNetworkUnhighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_NETWORK_UNHIGHLIGHTED,

	"ShellMainMenuExitPushed", //SHELL_SCRIPT_HOOK_MAIN_MENU_EXIT_SELECTED,
	"ShellMainMenuExitHighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_EXIT_HIGHLIGHTED,
	"ShellMainMenuExitUnhighlighted", //SHELL_SCRIPT_HOOK_MAIN_MENU_EXIT_UNHIGHLIGHTED,

	"ShellGeneralsOnlineLogin", //SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGIN,
	"ShellGeneralsOnlineLogout", //SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGOUT,
	"ShellGeneralsOnlineEnteredFromGame", //SHELL_SCRIPT_HOOK_GENERALS_ONLINE_ENTERED_FROM_GAME,

	"ShellOptionsOpened", //SHELL_SCRIPT_HOOK_OPTIONS_OPENED,
	"ShellOptionsClosed", //SHELL_SCRIPT_HOOK_OPTIONS_CLOSED,

	"ShellSkirmishOpened", //SHELL_SCRIPT_HOOK_SKIRMISH_OPENED,
	"ShellSkirmishClosed", //SHELL_SCRIPT_HOOK_SKIRMISH_CLOSED,
	"ShellSkirmishEnteredFromGame", //SHELL_SCRIPT_HOOK_SKIRMISH_ENTERED_FROM_GAME,

	"ShellLANOpened", //SHELL_SCRIPT_HOOK_LAN_OPENED,
	"ShellLANClosed", //SHELL_SCRIPT_HOOK_LAN_CLOSED,
	"ShellLANEnteredFromGame", //SHELL_SCRIPT_HOOK_LAN_ENTERED_FROM_GAME,
};
void SignalUIInteraction(Int interaction)
{
	if (TheScriptEngine)
		TheScriptEngine->signalUIInteract(TheShellHookNames[interaction]);
}


// Changing the order or meaning of either of these will require you to update the maps
// in a meaningful way. If there are new entries, add them to the end, rather than the middle.
const char *Surfaces[] = { "Ground", "Air", "Ground or Air", };
const char *ShakeIntensities[] = { "Subtle", "Normal", "Strong", "Severe", "Cine_Extreme", "Cine_Insane" };

enum { K_SCRIPT_LIST_DATA_VERSION_1 = 1,
			K_SCRIPT_GROUP_DATA_VERSION_1 = 1,
			K_SCRIPT_GROUP_DATA_VERSION_2 = 2,
			K_SCRIPT_DATA_VERSION_1 = 1,
			K_SCRIPT_DATA_VERSION_2 = 2,
			K_SCRIPT_OR_CONDITION_DATA_VERSION_1=1, 
			K_SCRIPT_ACTION_VERSION_1 = 1,
			K_SCRIPT_ACTION_VERSION_2 = 2,
			K_SCRIPT_CONDITION_VERSION_1 = 1,
			K_SCRIPT_CONDITION_VERSION_2 = 2,
			K_SCRIPT_CONDITION_VERSION_3 = 3,
			K_SCRIPT_CONDITION_VERSION_4 = 4,
			K_SCRIPTS_DATA_VERSION_1,
			end_of_the_enumeration
};

static Condition::ConditionType ParameterChangesVer2[] = 
{ 
	// Seven Changed from version 1.
	Condition::TEAM_INSIDE_AREA_PARTIALLY, 
	Condition::TEAM_INSIDE_AREA_ENTIRELY, 
	Condition::TEAM_OUTSIDE_AREA_ENTIRELY, 
	Condition::TEAM_ENTERED_AREA_PARTIALLY, 
	Condition::TEAM_ENTERED_AREA_ENTIRELY, 
	Condition::TEAM_EXITED_AREA_ENTIRELY, 
	Condition::TEAM_EXITED_AREA_PARTIALLY, 
	(Condition::ConditionType) -1,
};

enum { AT_END = 0x00FFFFFF };

//-------------------------------------------------------------------------------------------------
// ******************************** class  ScriptList *********************************************
//-------------------------------------------------------------------------------------------------
// Statics ///////////////////////////////////////////////////////////////////////////////////////
ScriptList *ScriptList::s_readLists[MAX_PLAYER_COUNT] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
Int					ScriptList::s_numInReadList = 0;

Int ScriptList::m_curId = 0;

/**
 ScriptList::updateDefaults -  checks for empty script lists, and adds some default stuff
 so you don't get a totally blank screen in the editor.
 Matched via MASM exact dump @ 0x0035C8A0 (183B); BFME inlines a 0x4c ScriptList ctor.
*/
// ?updateDefaults@ScriptList@@SAXXZ present-unmatched
void ScriptList::updateDefaults(void) 
{
	Int i;
	for (i=0; i<TheSidesList->getNumSides(); i++) 
	{
		ScriptList* pList = TheSidesList->getSideInfo(i)->getScriptList();
		if (pList == NULL) {
			pList = newInstance(ScriptList);	
			TheSidesList->getSideInfo(i)->setScriptList(pList);
		}
	}
}

/**
  Deletes any script lists attached to sides.  Used for editor cleanup.
*/
// ?reset@ScriptList@@SAXXZ present-unmatched
void ScriptList::reset(void) 
{
	Int i;
	if (TheSidesList == NULL) return; /// @todo - move this code into sides list.
	for (i=0; i<TheSidesList->getNumSides(); i++) 
	{
		ScriptList* pList = TheSidesList->getSideInfo(i)->getScriptList();
		TheSidesList->getSideInfo(i)->setScriptList(NULL);
		pList->deleteInstance();
	}
}



/**
  Ctor.
*/
// ScriptList::ScriptList: defined in ScriptListCtor.cpp (its row's unit).

/**
  Dtor.  Deletes any script lists or group lists.  Note that dtors for groups and script lists
	delete the whole list, so don't need to traverse here.
*/
// ??1ScriptList@@MAE@XZ present-unmatched
ScriptList::~ScriptList(void) 
{
	if (m_firstGroup) {
		m_firstGroup->deleteInstance();
		m_firstGroup = NULL;
	}
	if (m_firstScript) {
		m_firstScript->deleteInstance();
		m_firstScript = NULL;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@ScriptList@@MAEXPAVXfer@@@Z present-unmatched
void ScriptList::crc( Xfer *xfer )
{

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/ScriptList_xferMethodThunk.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ScriptList::loadPostProcess is owned by ScriptListDestructor.cpp; native
// C1FAAC slot1 points to the shared empty RET. Keep a single definition.

/**
  ScriptList::duplicate - Creates a full, "deep" copy of scriptlist. 
*/
// ScriptList::duplicate: defined in ScriptListDuplicate.cpp (its row's unit).

/**
  ScriptList::duplicateAndQualify - Creates a full, "deep" copy of scriptlist,
	adding the qualifier to names. 
*/
// ?duplicateAndQualify@ScriptList@@QBEPAV1@ABVAsciiString@@00@Z present-unmatched
ScriptList *ScriptList::duplicateAndQualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) const 
{
	ScriptList *pNew = newInstance(ScriptList);

	{
		const ScriptGroup *src = this->m_firstGroup;
		ScriptGroup *dst = NULL;
		while (src)
		{
			ScriptGroup *tmp = src->duplicateAndQualify( qualifier, playerTemplateName, newPlayerName);

			if (dst)
				dst->setNextGroup(tmp);
			else
				pNew->m_firstGroup = tmp;

			src = src->getNext();
			dst = tmp;
		}
	}

	{
		const Script *src = this->m_firstScript;
		Script *dst = NULL;
		while (src)
		{
			Script *tmp = src->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);

			if (dst)
				dst->setNextScript(tmp);
			else
				pNew->m_firstScript = tmp;

			src = src->getNext();
			dst = tmp;
		}
	}

	return pNew;
}

/**
  ScriptList::discard - Deletes a script list, but not any children. 
*/
// ?discard@ScriptList@@QAEXXZ present-unmatched
void ScriptList::discard(void)  
{
	m_firstGroup = NULL;
	m_firstScript = NULL;
	this->deleteInstance();
}

/**
  Add a script group to the current list of groups.  Offset to position ndx.
*/
// ?addGroup@ScriptList@@QAEXPAVScriptGroup@@H@Z present-unmatched
void ScriptList::addGroup(ScriptGroup *pGrp, Int ndx)
{
	ScriptGroup *pPrev = NULL;
	ScriptGroup *pCur = m_firstGroup;
	DEBUG_ASSERTCRASH(pGrp->getNext()==NULL, ("Adding already linked group."));
	while (ndx && pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
		ndx--;
	}
	if (pPrev) {
		// Weave into prev link.
		pGrp->setNextGroup(pPrev->getNext());
		pPrev->setNextGroup(pGrp);
	} else {
		// Goes at head of list.
		pGrp->setNextGroup(m_firstGroup);
		m_firstGroup = pGrp;
	}
}

/**
  Add a script to the current list of scripts.  Offset to position ndx.
*/
// ?addScript@ScriptList@@QAEXPAVScript@@H@Z present-unmatched
void ScriptList::addScript(Script *pScr, Int ndx)
{
	Script *pPrev = NULL;
	Script *pCur = m_firstScript;
	DEBUG_ASSERTCRASH(pScr->getNext()==NULL, ("Adding already linked group."));
	while (ndx && pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
		ndx--;
	}
	if (pPrev) {
		pScr->setNextScript(pPrev->getNext());
		pPrev->setNextScript(pScr);
	} else {
		pScr->setNextScript(m_firstScript);
		m_firstScript = pScr;
	}
}

/**
  Delete a script from the current list of scripts.
*/
// ?deleteScript@ScriptList@@QAEXPAVScript@@@Z present-unmatched
void ScriptList::deleteScript(Script *pScr)
{
	Script *pPrev = NULL;
	Script *pCur = m_firstScript;
	while (pCur != pScr) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	DEBUG_ASSERTCRASH(pCur, ("Couldn't find script."));
	if (pCur==NULL) return;

	if (pPrev) {
		// unlink from previous script.
		pPrev->setNextScript(pCur->getNext());
	} else {
		// Unlink from head of list.
		m_firstScript = pCur->getNext();
	}
	// Clear the link & delete.
	pCur->setNextScript(NULL);
	pCur->deleteInstance();
}

/**
  Delete a group from the current list of groups.
*/
// ?deleteGroup@ScriptList@@QAEXPAVScriptGroup@@@Z present-unmatched
void ScriptList::deleteGroup(ScriptGroup *pGrp)
{
	ScriptGroup *pPrev = NULL;
	ScriptGroup *pCur = m_firstGroup;
	while (pCur != pGrp) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	DEBUG_ASSERTCRASH(pCur, ("Couldn't find group."));
	if (pCur==NULL) return;
	if (pPrev) {
		// unlink from previous group.
		pPrev->setNextGroup(pCur->getNext());
	} else {
		// Unlink from head of list.
		m_firstGroup = pCur->getNext();
	}
	// Clear the link & delete.
	pCur->setNextGroup(NULL);
	pCur->deleteInstance();
}

/**
* ScriptList::ParseScriptsDataChunk - read a Scripts chunk.
* Format is the newer CHUNKY format.
*	See ScriptList::ScriptList for the writer.
*	Input: DataChunkInput 
*		
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptList_ParseScriptsDataChunk_Thunk.cpp
// ?ParseScriptsDataChunk@ScriptList@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z present-unmatched
Bool ScriptList::ParseScriptsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Int i;
	file.registerParser( AsciiString("ScriptList"), info->label, ScriptList::ParseScriptListDataChunk );
	DEBUG_ASSERTCRASH(s_numInReadList==0, ("Leftover scripts floating aroung."));
	for (i=0; i<s_numInReadList; i++) {
		if (s_readLists[i]) {
			s_readLists[i]->deleteInstance();
			s_readLists[i] = NULL;
		}
	}
	TScriptListReadInfo readInfo;
	for (i=0; i<MAX_PLAYER_COUNT; i++) {
		readInfo.readLists[i] = 0;
	}
	readInfo.numLists = 0;
	if (file.parse(&readInfo)) {
		DEBUG_ASSERTCRASH(readInfo.numLists<MAX_PLAYER_COUNT, ("Read too many, overrun buffer."));
		s_numInReadList = readInfo.numLists;
		for (i=0; i<s_numInReadList; i++) {
			s_readLists[i] = readInfo.readLists[i];
		}
		return true;
	}
	return false;
}

/**
* ScriptList::getReadScripts - Gets the scripts read in from a file by .
* ScriptList::ParseScriptsDataChunk.
*		
*/
// ?getReadScripts@ScriptList@@SAHQAPAV1@@Z present-unmatched
Int ScriptList::getReadScripts(ScriptList *scriptLists[MAX_PLAYER_COUNT])
{		 
	Int i;
	Int count = s_numInReadList;
	s_numInReadList = 0;
	for (i=0; i<count; i++) {
		scriptLists[i] = s_readLists[i];
		s_readLists[i] = NULL;
	}
	return count;
}								 

/**
* ScriptList::WriteScriptsDataChunk - Writes a Scripts chunk.
* Format is the newer CHUNKY format.
*	See ScriptEngine::ParseScriptsDataChunk for the reader.
*	Input: DataChunkInput 
*		
*/
// BFME's two writers are FREE functions taking the list itself as a second
// argument, not the static members the reference calls with two -- and it writes
// the GROUP chunk first. The reference copy writes the script chunk first, so
// the two produce different chunk orders in the saved map.
void WriteGroupDataChunk( DataChunkOutput &chunkWriter, ScriptList *scriptList, ScriptGroup *scriptGroup );
void WriteScriptDataChunk( DataChunkOutput &chunkWriter, ScriptList *scriptList, Script *script );

struct BfmeScriptListHeads
{
	UnsignedByte m_unreconstructed_00[4];
	Script *m_firstScript;						///< retail this+0x04
	ScriptGroup *m_firstGroup;					///< retail this+0x08
};

//
// Blocked on the row's own object-symbol note, which is a variant worth knowing.
// The row is NAMED ...QAPAV1@H@Z but carries
// object-symbol=?WriteScriptsDataChunk@ScriptList@@SAXAAVDataChunkOutput@@PBQAV1@H@Z,
// so the gate reads that second spelling out of the object. PBQAV1@ is what a
// parameter declared `ScriptList *const []' mangles to -- the donor's own
// declaration -- while this file's header declares `ScriptList *[]' and emits
// QAPAV1@. The two are different parameter TYPES, not a top-level const, so the
// destination cannot emit the donor's spelling without changing Scripts.h, and
// that is a wide header change for one body. It fails as "symbol not found in
// object", the same way an access-specifier mismatch does.
//
// The body itself is authored and the finding stands: BFME inlines the per-list
// writes here rather than calling WriteScriptListDataChunk, and writes the group
// chunk before the script chunk where the reference does the reverse.
// ScriptList::WriteScriptsDataChunk: defined in ScriptList_WriteScriptsDataChunk.cpp (its row's unit).



/**
* ScriptList::WriteScriptListDataChunk - Writes a Scripts chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/

// ?WriteScriptListDataChunk@ScriptList@@QAEXAAVDataChunkOutput@@@Z
// ScriptList::WriteScriptListDataChunk: defined in ScriptList_WriteScriptsDataChunk.cpp (its row's unit).


/**
* ScriptList::ParseScriptListDataChunk - read a Scripts chunk.
* Format is the newer CHUNKY format.
*	See ScriptList::WriteScriptListDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/ScriptList_ParseScriptListDataChunkThunk.cpp
// ?ParseScriptListDataChunk@ScriptList@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z present-unmatched
Bool ScriptList::ParseScriptListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	TScriptListReadInfo *pInfo = (TScriptListReadInfo*)userData;
	DEBUG_ASSERTCRASH(pInfo->numLists < MAX_PLAYER_COUNT, ("Too many."));
	if (pInfo->numLists >= MAX_PLAYER_COUNT) return false;
	pInfo->readLists[pInfo->numLists] = newInstance(ScriptList);
	Int cur = pInfo->numLists;
	pInfo->numLists++;
	file.registerParser( AsciiString("Script"), info->label, Script::ParseScriptFromListDataChunk );
	file.registerParser( AsciiString("ScriptGroup"), info->label, ScriptGroup::ParseGroupDataChunk );
	return file.parse(pInfo->readLists[cur]);
	
}


//-------------------------------------------------------------------------------------------------
// ******************************** class  ScriptGroup *********************************************
//-------------------------------------------------------------------------------------------------

/**
  Ctor - gives it a default name.
*/
// ??0ScriptGroup@@QAE@XZ present-unmatched
ScriptGroup::ScriptGroup(void) :
m_firstScript(NULL),
m_hasWarnings(false),
m_isGroupActive(true),
m_isGroupSubroutine(false),
//Added By Sadullah Nader
//Initializations inserted
m_nextGroup(NULL)
//
{
	m_groupName.format("Script Group %d", ScriptList::getNextID());
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@ScriptGroup@@MAEXPAVXfer@@@Z present-unmatched
void ScriptGroup::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version 
	* 2: m_isGroupActive, since it is twiddled by other scripts.  Only its initial state is determined by the map.
*/
// ------------------------------------------------------------------------------------------------
// Matched body: ScriptGroupXfer.cpp @ 0x350E90 (not this ZH list-walk; queue 0xAF9B24 was jmp-table).
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptGroupXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@ScriptGroup@@MAEXXZ present-unmatched
void ScriptGroup::loadPostProcess( void )
{

}  // end loadPostProcess

/**
  ScriptGroup::duplicate - Creates a full, "deep" copy of ScriptGroup.
	m_nextGroup is NULL on the copy.
*/
// ?duplicate@ScriptGroup@@QBEPAV1@XZ present-unmatched
ScriptGroup *ScriptGroup::duplicate(void) const 
{
	ScriptGroup *pNew = newInstance(ScriptGroup);	

	{
		Script *src = this->m_firstScript;
		Script *dst = NULL;
		while (src)
		{
			Script *tmp = src->duplicate();

			if (dst)
				dst->setNextScript(tmp);
			else
				pNew->m_firstScript = tmp;

			src = src->getNext();
			dst = tmp;
		}
	}

	pNew->m_groupName = this->m_groupName;
	pNew->m_isGroupActive = this->m_isGroupActive;
	pNew->m_isGroupSubroutine = this->m_isGroupSubroutine;
	pNew->m_nextGroup = NULL;

	return pNew;
}

/**
  ScriptGroup::duplicateAndQualify - Creates a full, "deep" copy of ScriptGroup, 
	adding qualifier to names.
	m_nextGroup is NULL on the copy.
*/
// ?duplicateAndQualify@ScriptGroup@@QBEPAV1@ABVAsciiString@@00@Z present-unmatched
ScriptGroup *ScriptGroup::duplicateAndQualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) const 
{
	ScriptGroup *pNew = newInstance(ScriptGroup);

	{
		Script *src = this->m_firstScript;
		Script *dst = NULL;
		while (src)
		{
			Script *tmp = src->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);

			if (dst)
				dst->setNextScript(tmp);
			else
				pNew->m_firstScript = tmp;

			src = src->getNext();
			dst = tmp;
		}
	}

	pNew->m_groupName = this->m_groupName;
	((StringBase<char> *)&pNew->m_groupName)->concat(*(const StringBase<char> *)&qualifier);
	pNew->m_isGroupActive = this->m_isGroupActive;
	pNew->m_isGroupSubroutine = this->m_isGroupSubroutine;
	pNew->m_nextGroup = NULL;

	return pNew;
}

/**
  Delete a script from the current list of scripts.
*/
// ?deleteScript@ScriptGroup@@QAEXPAVScript@@@Z present-unmatched
void ScriptGroup::deleteScript(Script *pScr)
{
	Script *pPrev = NULL;
	Script *pCur = m_firstScript;
	while (pScr != pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	DEBUG_ASSERTCRASH(pCur, ("Couldn't find script."));
	if (pCur==NULL) return;
	if (pPrev) {
		pPrev->setNextScript(pCur->getNext());
	} else {
		m_firstScript = pCur->getNext();
	}
	// Clear link & delete.
	pCur->setNextScript(NULL);
	pCur->deleteInstance();
}

/**
  Add a script to the current list of scripts.  Offset to position ndx.
*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/ScriptGroup_addScript_Thunk.cpp
// ?addScript@ScriptGroup@@QAEXPAVScript@@H@Z present-unmatched
void ScriptGroup::addScript(Script *pScr, Int ndx)
{
	Script *pPrev = NULL;
	Script *pCur = m_firstScript;
	DEBUG_ASSERTCRASH(pScr->getNext()==NULL, ("Adding already linked group."));
	while (ndx && pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
		ndx--;
	}
	if (pPrev) {
		// link to pPrev
		pScr->setNextScript(pPrev->getNext());
		pPrev->setNextScript(pScr);
	} else {
		// add to head of list.
		pScr->setNextScript(m_firstScript);
		m_firstScript = pScr;
	}
}

/**
* ScriptGroup::WriteGroupDataChunk - Writes a Scripts chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// ?WriteGroupDataChunk@ScriptGroup@@ present-unmatched
void ScriptGroup::WriteGroupDataChunk(DataChunkOutput &chunkWriter, ScriptGroup *pGroup)
{

	/**********SCRIPT GROUP DATA ***********************/
	while (pGroup) {
		chunkWriter.openDataChunk("ScriptGroup", K_SCRIPT_GROUP_DATA_VERSION_2);
			chunkWriter.writeAsciiString(pGroup->m_groupName);
			chunkWriter.writeByte(pGroup->m_isGroupActive);
			chunkWriter.writeByte(pGroup->m_isGroupSubroutine);
// ?WriteScriptDataChunk@Script@@SAXAAVDataChunkOutput@@PAV1@@Z present-unmatched
			if (pGroup->m_firstScript) Script::WriteScriptDataChunk(chunkWriter, pGroup->m_firstScript);
		chunkWriter.closeDataChunk();
		pGroup = pGroup->getNext();
	}
	
}

/**
* ScriptGroup::ParseGroupDataChunk - read a Group chunk.
* Format is the newer CHUNKY format.
*	See ScriptList::WriteScriptListDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// ?ParseGroupDataChunk@ScriptGroup@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z present-unmatched
Bool ScriptGroup::ParseGroupDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	ScriptList *pList = (ScriptList *)userData;
	ScriptGroup *pGroup = newInstance(ScriptGroup);

	pGroup->m_groupName = file.readAsciiString();
	pGroup->m_isGroupActive = file.readByte();
	if (info->version == K_SCRIPT_GROUP_DATA_VERSION_2) {
		pGroup->m_isGroupSubroutine= file.readByte();
	}
	pList->addGroup(pGroup, AT_END);
	file.registerParser( AsciiString("Script"), info->label, Script::ParseScriptFromGroupDataChunk );
	return file.parse(pGroup);
	
}

//-------------------------------------------------------------------------------------------------
// ******************************** class  Script *********************************************
//-------------------------------------------------------------------------------------------------
/**
  Ctor - initializes members.
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptCtor.cpp
// Script::Script (?) is rowed in ScriptWriteDataChunk.cpp; a second definition here would not link.

/**
  Dtor - The condition and action deletes the rest of the list, but we have to loop & delete
	all the scripts in out list.
*/

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@Script@@MAEXPAVXfer@@@Z present-unmatched
void Script::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// Matched body: ScriptXfer.cpp @ 0x3B2540 (BFME 2 layout). This ZH copy stays
// because its setActive call emits the 0x0006EDE3 alias row.
// Script::xfer is rowed in ScriptXfer.cpp; the Zero Hour copy here was a non-retail second
// definition. It was also what emitted the inline Script::setActive rowed here (as
// dup_0006ede3); this anchor keeps it emitted.
// ?bfmeAnchorScriptSetActive absent-from-retail
void bfmeAnchorScriptSetActive(Script *script, Bool active)
{
	script->setActive(active);
}

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@Script@@MAEXXZ present-unmatched
void Script::loadPostProcess( void )
{

}  // end loadPostProcess

/**
  Script::duplicate - Creates a full, "deep" copy of script. Condition list and action
  list is duplicated as well.  Note - just the script, doesn't
	duplicate a list of scripts.  m_nextScript is NULL on the copy.
*/
// ?duplicate@Script@@QBEPAV1@XZ is a row of ScriptDuplicate.cpp; this unit's copy was
// a second, non-retail definition of it.

/**
  Script::duplicate - Creates a full, "deep" copy of script, with qualifier 
  added to names. Condition list and action
  list is duplicated as well.  Note - just the script, doesn't
	duplicate a list of scripts.  m_nextScript is NULL on the copy.
*/
// ?duplicateAndQualify@Script@@QBEPAV1@ABVAsciiString@@00@Z present-unmatched
Script *Script::duplicateAndQualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) const 
{
	Script *pNew = newInstance(Script);
	if (pNew->m_condition) {
		pNew->m_condition->deleteInstance();
	}
	if (pNew->m_action) {
		pNew->m_action->deleteInstance();
	}
	pNew->m_scriptName = m_scriptName;
	((StringBase<char> *)&pNew->m_scriptName)->concat(*(const StringBase<char> *)&qualifier);
	pNew->m_comment = m_comment;
	pNew->m_conditionComment = m_conditionComment;
	pNew->m_actionComment = m_actionComment;
	pNew->m_isActive = m_isActive;
	pNew->m_isOneShot = m_isOneShot;
	pNew->m_isSubroutine = m_isSubroutine;
	pNew->m_easy = m_easy;
	pNew->m_normal = m_normal;
	pNew->m_hard = m_hard;
	pNew->m_delayEvaluationSeconds = m_delayEvaluationSeconds;
	if (m_condition) {
		pNew->m_condition = m_condition->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);
	}
	if (m_action) {
		pNew->m_action = m_action->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);
	}
	if (m_actionFalse) {
		pNew->m_actionFalse = m_actionFalse->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);
	}
	return pNew;
}

/**
  Script::updateFrom - Copies all the data from pSrc into this.  Any data in this 
	is deleted (conditions, actions).  Note that this guts pSrc, and removes it's conditions
	and actions.  Intended for use in an edit dialog, where pSrc is a copy edited, and if cancelled
	discarded, and if not cancelled, updated into the real script, then discarded.
*/
// Script::updateFrom: byte-exact reconstruction on BFME 2's Script layout in
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptDeleteClauses.cpp.

/**
  Script::deleteOrCondition - delete pCond from the or condition list.
*/
// Script::deleteOrCondition: byte-exact reconstruction on BFME 2's Script layout in
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptDeleteClauses.cpp.


/**
  Script::deleteAction - delete pAct from the action list.
*/
// ?deleteAction@Script@@QAEXPAVScriptAction@@@Z present-unmatched
void Script::deleteAction(ScriptAction *pAct)
{
	ScriptAction *pPrev = NULL;
	ScriptAction *pCur = m_action;
	while (pAct != pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	DEBUG_ASSERTCRASH(pCur, ("Couldn't find action."));
	if (pCur==NULL) return;
	if (pPrev) {
		pPrev->setNextAction(pCur->getNext());
	} else {
		m_action = pCur->getNext();
	}
	pCur->setNextAction(NULL);
	pCur->deleteInstance();
}


/**
  Script::deleteFalseAction - delete pAct from the false action list.
*/
// ?deleteFalseAction@Script@@QAEXPAVScriptAction@@@Z present-unmatched
void Script::deleteFalseAction(ScriptAction *pAct)
{
	ScriptAction *pPrev = NULL;
	ScriptAction *pCur = m_actionFalse;
	while (pAct != pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	DEBUG_ASSERTCRASH(pCur, ("Couldn't find action."));
	if (pCur==NULL) return;
	if (pPrev) {
		pPrev->setNextAction(pCur->getNext());
	} else {
		m_actionFalse = pCur->getNext();
	}
	pCur->setNextAction(NULL);
	pCur->deleteInstance();
}


/**
  Script::getUiText - Creates the string to display in the scripts dialog box.
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/Script_getUiText_Thunk.cpp
// Byte-exact BFME2 UI formatter lives in ScriptGetUiText.cpp.

/**
* Script::WriteScriptDataChunk - Writes a Scripts chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// ?WriteScriptDataChunk@Script@@SAXAAVDataChunkOutput@@PAV1@@Z present-unmatched
void Script::WriteScriptDataChunk(DataChunkOutput &chunkWriter, Script *pScript)
{
	/**********SCRIPT  DATA ***********************/
	while (pScript) {
		chunkWriter.openDataChunk("Script", K_SCRIPT_DATA_VERSION_2);
			chunkWriter.writeAsciiString(pScript->m_scriptName);
			chunkWriter.writeAsciiString(pScript->m_comment);
			chunkWriter.writeAsciiString(pScript->m_conditionComment);
			chunkWriter.writeAsciiString(pScript->m_actionComment);

			chunkWriter.writeByte(pScript->m_isActive);
			chunkWriter.writeByte(pScript->m_isOneShot);
			chunkWriter.writeByte(pScript->m_easy);
			chunkWriter.writeByte(pScript->m_normal);
			chunkWriter.writeByte(pScript->m_hard);	 
			chunkWriter.writeByte(pScript->m_isSubroutine);	
			chunkWriter.writeInt(pScript->m_delayEvaluationSeconds);	
			if (pScript->m_condition) OrCondition::WriteOrConditionDataChunk(chunkWriter, pScript->m_condition);
// ?WriteActionDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z present-unmatched
			if (pScript->m_action) ScriptAction::WriteActionDataChunk(chunkWriter, pScript->m_action);
// ?WriteActionFalseDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z present-unmatched
			if (pScript->m_actionFalse) ScriptAction::WriteActionFalseDataChunk(chunkWriter, pScript->m_actionFalse);
		chunkWriter.closeDataChunk();
		pScript = pScript->getNext();
	}	
}
/**
* Script::ParseScript - read a script chunk.
* Format is the newer CHUNKY format.
*	See ScriptList::WriteScriptDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/Script_ParseScript_Thunk.cpp
// ?ParseScript@Script@@SAPAV1@AAVDataChunkInput@@G@Z present-unmatched
Script *Script::ParseScript(DataChunkInput &file, unsigned short version)
{
	Script *pScript = newInstance(Script);

	pScript->m_scriptName = file.readAsciiString();
	pScript->m_comment = file.readAsciiString();
	pScript->m_conditionComment = file.readAsciiString();
	pScript->m_actionComment = file.readAsciiString();

	pScript->m_isActive = file.readByte();
	pScript->m_isOneShot = file.readByte();
	pScript->m_easy = file.readByte();
	pScript->m_normal = file.readByte();
	pScript->m_hard = file.readByte();
	pScript->m_isSubroutine = file.readByte();
	if (version>=K_SCRIPT_DATA_VERSION_2) {
		pScript->m_delayEvaluationSeconds = file.readInt();
	}
	file.registerParser( AsciiString("OrCondition"), AsciiString("Script"), OrCondition::ParseOrConditionDataChunk );
	file.registerParser( AsciiString("ScriptAction"),  AsciiString("Script"), ScriptAction::ParseActionDataChunk );
	file.registerParser( AsciiString("ScriptActionFalse"),  AsciiString("Script"), ScriptAction::ParseActionFalseDataChunk );
	if (! file.parse(pScript) ) 
	{
		return NULL;
	}
	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Unexpected data left over."));	
	return pScript;
}

/**
* Script::ParseScriptFromListDataChunk - read a script chunk in a script list.
* Format is the newer CHUNKY format.
*	See ScriptList::WriteScriptListDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// ?ParseScriptFromListDataChunk@Script@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z present-unmatched
Bool Script::ParseScriptFromListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	ScriptList *pList = (ScriptList *)userData;
	Script *pScript = ParseScript(file, info->version);
	pList->addScript(pScript, AT_END);
	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Unexpected data left over."));	
	return true;
}

/**
* Script::ParseScriptFromGroupDataChunk - read a script chunk in a script group.
* Format is the newer CHUNKY format.
*	See ScriptList::WriteScriptListDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// ?ParseScriptFromGroupDataChunk@Script@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z present-unmatched
Bool Script::ParseScriptFromGroupDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	ScriptGroup *pGroup = (ScriptGroup *)userData;
	Script *pScript = ParseScript(file, info->version);
	pGroup->addScript(pScript, AT_END);
	DEBUG_ASSERTCRASH(file.atEndOfChunk(), ("Unexpected data left over."));	
	return true;
}


/**
* Script::findPreviousOrCondition - find the OrCondition that immediately proceeds curOr.
*	Input: OrCondition 
*		
*/
// ?findPreviousOrCondition@Script@@QAEPAVOrCondition@@PAV2@@Z present-unmatched
OrCondition *Script::findPreviousOrCondition( OrCondition *curOr )
{
	OrCondition *myConditions = getOrCondition();
	if ( myConditions == curOr ) {
		return NULL;
	}
	
	while (myConditions) {
		if (myConditions->getNextOrCondition() == curOr) {
			return myConditions;
		}
		myConditions = myConditions->getNextOrCondition();
	}

	DEBUG_CRASH(("Tried to find an OrCondition that doesn't seem to exist (jkmcd)"));
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ******************************** class  OrCondition *********************************************
//-------------------------------------------------------------------------------------------------
// ??1OrCondition@@MAE@XZ present-unmatched
OrCondition::~OrCondition(void) 
{
	if (m_firstAnd) {
		m_firstAnd->deleteInstance();
		m_firstAnd = NULL;
	}
	if (m_nextOr) {
		OrCondition *cur = m_nextOr;
		OrCondition *next;
		while (cur) {
			next = cur->getNextOrCondition();
			cur->setNextOrCondition(NULL); // prevents recursion. 
			cur->deleteInstance();
			cur = next; 
		}
	}
}

OrCondition *OrCondition::duplicate(void) const 
{
	OrCondition *pNew = newInstance(OrCondition);	
	if (m_firstAnd) {
		pNew->m_firstAnd = m_firstAnd->duplicate();
	}
	OrCondition *pLink = m_nextOr;
	OrCondition *pCur = pNew;
	while (pLink) {
		pCur->m_nextOr = newInstance(OrCondition);
		pCur = pCur->m_nextOr;
		if (pLink->m_firstAnd) {
			pCur->m_firstAnd = pLink->m_firstAnd->duplicate();
		}
		pLink = pLink->m_nextOr;
	}
	return pNew;
}

// ?duplicateAndQualify@OrCondition@@QBEPAV1@ABVAsciiString@@00@Z present-unmatched
OrCondition *OrCondition::duplicateAndQualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) const 
{
	OrCondition *pNew = newInstance(OrCondition);
	if (m_firstAnd) {
		pNew->m_firstAnd = m_firstAnd->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);
	}
	OrCondition *pLink = m_nextOr;
	OrCondition *pCur = pNew;
	while (pLink) {
		pCur->m_nextOr = newInstance(OrCondition);
		pCur = pCur->m_nextOr;
		if (pLink->m_firstAnd) {
			pCur->m_firstAnd = pLink->m_firstAnd->duplicateAndQualify(qualifier, playerTemplateName, newPlayerName);
		}
		pLink = pLink->m_nextOr;
	}
	return pNew;
}

Condition *OrCondition::removeCondition(Condition *pCond)
{
	Condition *pPrev = NULL;
	Condition *pCur = m_firstAnd;
	while (pCond != pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}

	DEBUG_ASSERTCRASH(pCur, ("Couldn't find condition."));
	if (pCur==NULL) 
		return NULL;
	if (pPrev) {
		pPrev->setNextCondition(pCur->getNext());
	} else {
		m_firstAnd = pCur->getNext();
	}

	pCur->setNextCondition(NULL);
	return pCur;
}

void OrCondition::deleteCondition(Condition *pCond)
{
	// Retail 0x003B26A1: removeCondition, then a global-scope delete: the
	// virtual destructor through vtable[0] with flags 0, whose returned
	// complete-object pointer goes to ::operator delete. Condition's
	// destructor is protected; the PublicDtor cast reaches the same call.
	Condition *pCur = removeCondition(pCond);
	if (pCur == NULL)
		return;
	struct PublicDtor { virtual ~PublicDtor() {} };
	::delete (PublicDtor *)pCur;
}


/**
* OrCondition::WriteOrConditionDataChunk - Writes a Or condition chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// OrCondition::WriteOrConditionDataChunk: defined in OrConditionWriteOrConditionDataChunk.cpp (its row's unit).

/**
* OrCondition::ParseOrConditionDataChunk - read a Or condition chunk.
* Format is the newer CHUNKY format.
*	See OrCondition::WriteOrConditionDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* OrCondition::findPreviousCondition - find the condition that immediately proceeds curCond.
* Format is the newer CHUNKY format.
*	See OrCondition::WriteOrConditionDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
Condition *OrCondition::findPreviousCondition( Condition *curCond )
{
	Condition *myConditions = getFirstAndCondition();
	if (myConditions == curCond) {
		return NULL;
	}

	while (myConditions) {
		if (myConditions->getNext() == curCond) {
			return myConditions;
		}
		myConditions = myConditions->getNext();
	}

	DEBUG_CRASH(("Searched for non-existent And Condition. (jkmcd)"));
	return NULL;
}


//-------------------------------------------------------------------------------------------------
// ******************************** class  Condition *********************************************
//-------------------------------------------------------------------------------------------------
// Owned by ConditionCtor.cpp.

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/Condition_setConditionType_Thunk.cpp
// Condition::setConditionType: defined in Rva003b6d92Finish.cpp (its row's unit).

// Owned by ConditionDuplicate.cpp.

// ?duplicateAndQualify@Condition@@QBEPAV1@ABVAsciiString@@00@Z present-unmatched
Condition *Condition::duplicateAndQualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) const 
{
	Condition *pNew = newInstance(Condition)(m_conditionType);
	Int i;
	for (i=0; i<m_numParms && i<pNew->m_numParms; i++) {
		*pNew->m_parms[i] = *m_parms[i];
		pNew->m_parms[i]->qualify(qualifier, playerTemplateName, newPlayerName);
	}
	Condition *pLink = m_nextAndCondition;
	Condition *pCur = pNew;
	while (pLink) {
		pCur->m_nextAndCondition = newInstance(Condition)(pLink->getConditionType());
		pCur = pCur->m_nextAndCondition;
		for (i=0; i<pLink->m_numParms; i++) {
			*pCur->m_parms[i] = *pLink->m_parms[i];
			pCur->m_parms[i]->qualify(qualifier, playerTemplateName, newPlayerName);
		}
		pLink = pLink->m_nextAndCondition;
	}
	return pNew;
}

// Condition::~Condition (0x003B4230) is defined in ScriptConditionActionDtors.cpp.



// Condition::getUiStrings: defined in ConditionGetUiStrings.cpp (its row's unit).

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/Condition_getUiText_Thunk.cpp
AsciiString Condition::getUiText(void)
{
	AsciiString uiText;
	AsciiString strings[MAX_PARMS];
	Int numStrings = getUiStrings(strings);
	Int i;

	if (m_hasWarnings) {
		uiText = "[???]";
	}

	for (i=0; i<MAX_PARMS; i++) {
		if (i<numStrings) {
			((StringBase<char> *)&uiText)->concat(*(const StringBase<char> *)&strings[i]);
		}
		if (i<m_numParms) {
			uiText.concat(m_parms[i]->getUiText());
		}
	}

	return uiText;
}


/**
* Condition::WriteConditionDataChunk - Writes a condition chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// Condition::WriteConditionDataChunk: defined in ConditionWriteDataChunk.cpp (its row's unit).
// Condition::ParseConditionDataChunk: defined in Rva003b6d92Finish.cpp (its row's unit).


// The exact retail constructor is emitted by Template.cpp.

//-------------------------------------------------------------------------------------------------
// ******************************** class Parameter ***********************************************
//-------------------------------------------------------------------------------------------------
// Template::getParameterType: defined in Rva003b6d92Finish.cpp (its row's unit).

// Parameter::getCoord3D: defined in ParameterGetCoord3D.cpp (its row's unit).

// Parameter::setCoord3D: defined in ParameterSetCoord3D.cpp (its row's unit).

// ?qualify@Parameter@@QAEXABVAsciiString@@00@Z present-unmatched
void Parameter::qualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) 
{
	AsciiString tmpString;
	switch (m_paramType) {
		case SIDE:
			tmpString = m_string;
			((StringBase<char> *)&tmpString)->concat(*(const StringBase<char> *)&qualifier);
			if (tmpString==playerTemplateName) {
				m_string = newPlayerName;
			}
			break;
		case TEAM:	
			if (m_string == THIS_TEAM) {
				break;
			}
			/// otherwise drop down & qualify.
		case SCRIPT:
		case COUNTER:
		case FLAG:
		case SCRIPT_SUBROUTINE:
			((StringBase<char> *)&m_string)->concat(*(const StringBase<char> *)&qualifier);
			break;
		default: break;
	}
}

// Parameter::getUiText: defined in ParameterGetUiTextBody.cpp (its row's unit).

/**
* Parameter::WriteParameter - Writes an Parameter.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// Parameter::WriteParameter: defined in Parameter_WriteParameter.cpp (its row's unit).

/**
* Parameter::ReadParameter - read a parameter.
* Format is the newer CHUNKY format.
*	See Parameter::WriteParameter for the writer.
*	Input: DataChunkInput 
*		
*/
// ?ReadParameter@Parameter@@SAPAV1@AAVDataChunkInput@@@Z
// Body in Code/masm_dumps/_sa3__ReadParameter_Parameter__SAPAV1_AAVDataChunkInput_357FC0.asm (exact 748B retail @ 0x00357FC0).
//-------------------------------------------------------------------------------------------------
// ******************************** class ScriptAction ***********************************************
//-------------------------------------------------------------------------------------------------
// Owned by ScriptActionCtor.cpp.

// ScriptAction::setActionType: defined in Rva003b6d92Finish.cpp (its row's unit).

// Owned by ScriptActionDuplicate.cpp.

// ?duplicateAndQualify@ScriptAction@@QBEPAV1@ABVAsciiString@@00@Z present-unmatched
ScriptAction *ScriptAction::duplicateAndQualify(const AsciiString& qualifier, 
			const AsciiString& playerTemplateName, const AsciiString& newPlayerName) const 
{
	ScriptAction *pNew = newInstance(ScriptAction)(m_actionType);
	Int i;
	for (i=0; i<m_numParms; i++) {
		if (pNew->m_parms[i]) {
			*pNew->m_parms[i] = *m_parms[i];
			pNew->m_parms[i]->qualify(qualifier, playerTemplateName, newPlayerName);
		}
	}
	ScriptAction *pLink = m_nextAction;
	ScriptAction *pCur = pNew;
	while (pLink) {
		pCur->m_nextAction = newInstance(ScriptAction)(pLink->m_actionType);
		pCur = pCur->m_nextAction;
		for (i=0; i<pLink->m_numParms; i++) {
			if (pCur->m_parms[i] && pLink->m_parms[i]) {
				*pCur->m_parms[i] = *pLink->m_parms[i];
				pCur->m_parms[i]->qualify(qualifier, playerTemplateName, newPlayerName);
			}
		}
		pLink = pLink->m_nextAction;
	}
	return pNew;
}

// ScriptAction::~ScriptAction is owned by ScriptConditionActionDtors.cpp.

// ScriptAction::getUiStrings: defined in ScriptActionGetUiStrings.cpp (its row's unit).

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptAction_getUiText_Thunk.cpp
// ScriptAction::getUiText: defined in ScriptActionGetUiText.cpp (its row's unit).

/**
* ScriptAction::WriteActionDataChunk - Writes an Action chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// ?WriteActionDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z present-unmatched
void ScriptAction::WriteActionDataChunk(DataChunkOutput &chunkWriter, ScriptAction	*pScriptAction)
{
	/**********ACTION  DATA ***********************/
	while (pScriptAction) {
		chunkWriter.openDataChunk("ScriptAction", K_SCRIPT_ACTION_VERSION_2);
			chunkWriter.writeInt(pScriptAction->m_actionType);
			const ActionTemplate* at = TheScriptEngine->getActionTemplate(pScriptAction->m_actionType);
			if (at) {
				chunkWriter.writeNameKey(at->m_internalNameKey);
			}	else {
				DEBUG_CRASH(("Invalid action."));
				chunkWriter.writeNameKey(NAMEKEY("Bogus"));
			}
			chunkWriter.writeInt(pScriptAction->m_numParms);
			Int i;
			for (i=0; i<pScriptAction->m_numParms; i++) {
				pScriptAction->m_parms[i]->WriteParameter(chunkWriter);
			}
		chunkWriter.closeDataChunk();
		pScriptAction = pScriptAction->getNext();
	}	
}

// ScriptAction::ParseAction: BFME's reader is reconstructed in ScriptActionParseAction.cpp; ZH's
// version here was not retail's and emitted Parameter's constructor ahead of its retail copy.

/**
* ScriptAction::ParseActionDataChunk - read an action chunk in a script list.
* Format is the newer CHUNKY format.
*	See ScriptAction::WriteActionDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptsParseActionDataChunkThunk.cpp


/**
* ScriptAction::WriteActionFalseDataChunk - Writes a false Action chunk.
* Format is the newer CHUNKY format.
*	Input: DataChunkInput 
*		
*/
// ?WriteActionFalseDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z present-unmatched
void ScriptAction::WriteActionFalseDataChunk(DataChunkOutput &chunkWriter, ScriptAction	*pScriptAction)
{
	/**********ACTION  DATA ***********************/
	while (pScriptAction) {
		chunkWriter.openDataChunk("ScriptActionFalse", K_SCRIPT_ACTION_VERSION_2);
			chunkWriter.writeInt(pScriptAction->m_actionType);
			const ActionTemplate* at = TheScriptEngine->getActionTemplate(pScriptAction->m_actionType);
			if (at) {
				chunkWriter.writeNameKey(at->m_internalNameKey);
			}	else {
				DEBUG_CRASH(("Invalid action."));
				chunkWriter.writeNameKey(NAMEKEY("Bogus"));
			}
			chunkWriter.writeInt(pScriptAction->m_numParms);
			Int i;
			for (i=0; i<pScriptAction->m_numParms; i++) {
				pScriptAction->m_parms[i]->WriteParameter(chunkWriter);
			}
		chunkWriter.closeDataChunk();
		pScriptAction = pScriptAction->getNext();
	}	
}

/**
* ScriptAction::ParseActionFalseDataChunk - read a false action chunk in a script list.
* Format is the newer CHUNKY format.
*	See ScriptAction::WriteActionDataChunk for the writer.
*	Input: DataChunkInput 
*		
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptAction_ParseActionFalseDataChunk_Thunk.cpp

// NOTE: Changing these or adding ot TheOBjectFlagNames requires changes to 
// ScriptActions::changeObjectPanelFlagForSingleObject
// THEY SHOULD STAY IN SYNC.
const char* TheObjectFlagsNames[] = 
{ 
	"Enabled",
	"Powered",
	"Indestructible",
	"Unsellable",
	"Selectable",
	"AI Recruitable",
	"Player Targetable",
	NULL,
};
