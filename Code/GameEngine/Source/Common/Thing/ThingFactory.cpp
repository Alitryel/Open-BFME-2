// cl: /Ireference/shims/bfme2_ascii_native_copy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: ThingFactory.cpp /////////////////////////////////////////////////////////////////////////
// Created:   Colin Day, April 2001
// Desc:		This is how we go and make our things, we make our things, we make our things!	
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/FileSystem.h"
#include "Common/GameAudio.h"
#include "Common/MapObject.h"
#include "Common/ModuleFactory.h"
#include "Common/RandomValue.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/CreateModule.h"
#include "Common/ProductionPrerequisite.h"
#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "Common/INI.h"

// Bottom-loop overload: this TU's flags compile the generic range-destroy to
// a non-retail form; the overload wins for (AsciiString*,AsciiString*) and
// offers the link no competing template copy (row 32 family2-LK3).
namespace _STL {
inline void _Destroy(AsciiString * __first, AsciiString * __last)
{ for (; __first != __last; ++__first) __first->~AsciiString(); }
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

enum { TEMPLATE_HASH_SIZE = 12288 };

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
ThingFactory *TheThingFactory = NULL;  ///< Thing manager singleton declaration

// STATIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Free all data loaded into this template database */
//-------------------------------------------------------------------------------------------------
// BFME2 freeDatabase is recovered in ThingFactoryReset.cpp.

//-------------------------------------------------------------------------------------------------
/** add the thing template passed in, into the databse */
//-------------------------------------------------------------------------------------------------
// BFME2 addTemplate, including its replacement path, is recovered in ThingFactoryReset.cpp.

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME2's complete85B constructor is recovered at002D0E14 in
// Rva002D0E14Ctor.cpp. The unmatched ZH constructor formerly left here
// also emitted a non-retail30B deleting destructor; keep that competing
// construction/vtable copy out of the link. ThingFactoryDtor.cpp emits
// the native28B deleting destructor with its verified71B out-of-line dtor.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1ThingFactory@@ present-unmatched
// BFME2's newTemplate and newOverride are recovered in ThingFactoryNewTemplate.cpp
// and ThingFactoryNewOverride.cpp. The unmatched ZH copies formerly left here
// emitted a non-retail 1216-byte ThingTemplate::operator= (Zero Hour layout)
// ahead of retail's 0x002D1101 in link order; keep them out of the link.

//-------------------------------------------------------------------------------------------------
/** Init */
//-------------------------------------------------------------------------------------------------
// ?init@ThingFactory@@ present-unmatched
void ThingFactory::init( void )
{

}  // end init

//-------------------------------------------------------------------------------------------------
/** Reset */
//-------------------------------------------------------------------------------------------------
// BFME2 reset is recovered in ThingFactoryReset.cpp.

//-------------------------------------------------------------------------------------------------
/** Update */
//-------------------------------------------------------------------------------------------------
// ?update@ThingFactory@@ present-unmatched
void ThingFactory::update( void )
{

}  // end update

//-------------------------------------------------------------------------------------------------
/** Return the template with the matching database name */
//-------------------------------------------------------------------------------------------------
// BFME ThingTemplate: m_nextTemplate @+0x38c, m_templateID @+0x478 (ZH headers differ).
// ?ThingFactory::findByTemplateID present-unmatched
const ThingTemplate *ThingFactory::findByTemplateID( UnsignedShort id )
{
	struct BFMEThingTemplateLinks {
		unsigned char padNext[0x38c];
		ThingTemplate *nextTemplate;
		unsigned char padId[0x478 - 0x38c - sizeof(ThingTemplate *)];
		UnsignedShort templateID;
	};
	for (ThingTemplate *tmpl = m_firstTemplate; tmpl; )
	{
		BFMEThingTemplateLinks *links = reinterpret_cast<BFMEThingTemplateLinks *>(tmpl);
		if (links->templateID == id)
			return tmpl;
		tmpl = links->nextTemplate;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
/** Return the template with the matching database name */
//-------------------------------------------------------------------------------------------------
// ?findTemplateInternal@ThingFactory@@ present-unmatched
ThingTemplate *ThingFactory::findTemplateInternal( const AsciiString& name, Bool check )
{
	ThingTemplateHashMapIt tIt = m_templateHashMap.find(name);

	if (tIt != m_templateHashMap.end()) {
		return tIt->second;
	}

#ifdef LOAD_TEST_ASSETS
	if (!strncmp(name.str(), TEST_STRING, strlen(TEST_STRING))) 
	{
		ThingTemplate *tmplate = newTemplate( AsciiString( "Un-namedTemplate" ) );

		// load the values
		tmplate->initForLTA( name );

		// Kinda lame, but necessary.
		m_templateHashMap.erase("Un-namedTemplate");
		m_templateHashMap[name] = tmplate;

		// add tmplate template to the database
		return findTemplateInternal( name );

	}
	
#endif
	
	if( check && name.isNotEmpty() )
	{
		DEBUG_CRASH( ("Failed to find thing template %s (case sensitive) This issue has a chance of crashing after you ignore it!", name.str() ) );
	}
	return NULL;

}  // end getTemplate

//=============================================================================
// ?newObject@ThingFactory@@ present-unmatched
Object *ThingFactory::newObject( const ThingTemplate *tmplate, Team *team, ObjectStatusMaskType statusBits )
{
	if (tmplate == NULL)
		throw ERROR_BAD_ARG;

	const std::vector<AsciiString>& asv = tmplate->getBuildVariations();
	if (!asv.empty())
	{
		Int which = GameLogicRandomValue(0, asv.size()-1);
		const ThingTemplate* tmp = findTemplate( asv[which] );
		if (tmp != NULL)
			tmplate = tmp;
	}

	DEBUG_ASSERTCRASH(!tmplate->isKindOf(KINDOF_DRAWABLE_ONLY), ("You may not create Objects with the template %s, only Drawables\n",tmplate->getName().str()));

	// have the game logic create an object of the correct type.
	// (this will throw an exception on failure.)
	//Added ability to pass in optional statusBits. This is needed to be set prior to
	//the onCreate() calls... in the case of constructing.
	Object *obj = TheGameLogic->friend_createObject( tmplate, statusBits, team );

	// run the create function for the thing
	for (BehaviorModule** m = obj->getBehaviorModules(); *m; ++m)
	{
		CreateModuleInterface* create = (*m)->getCreate();
		if (!create)
			continue;
	
		create->onCreate();
	}

	//
	// all objects are part of the partition manager system, add it to that 
	// system now
	//
	ThePartitionManager->registerObject( obj );

	obj->initObject();

	return obj;

} 

//=============================================================================

#if defined(_DEBUG) || defined(_INTERNAL)
AsciiString TheThingTemplateBeingParsedName;
#endif

//-------------------------------------------------------------------------------------------------
/** Parse Object entry */
//-------------------------------------------------------------------------------------------------
/*static*/ void ThingFactory::parseObjectDefinition( INI* ini, const AsciiString& name, const AsciiString& reskinFrom )
{
#if defined(_DEBUG) || defined(_INTERNAL)
	TheThingTemplateBeingParsedName = name;
#endif

	// find existing item if present
	ThingTemplate *thingTemplate = TheThingFactory->findTemplateInternal( name, FALSE );
	if( !thingTemplate )
	{
		// no item is present, create a new one
		thingTemplate = TheThingFactory->newTemplate( name );
		if ( ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES )
		{
			// This ThingTemplate is actually an override, so we will mark it as such so that it properly
			// gets deleted on ::reset().
			thingTemplate->markAsOverride();
		}
	}
	else if( ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES )
	{
		//Holy crap, this sucks to debug!!!
		//If you have two different objects, the previous code would simply 
		//allow you to define multiple objects with the same name, and just 
		//nuke the old one with the new one. So, I (KM) have added this 
		//assert to notify in case of two same-name objects.
		DEBUG_CRASH(( "[LINE: %d in '%s'] Duplicate factionunit %s found!", ini->getLineNum(), ini->getFilename().str(), name.str() ));
	}
	else
	{
		thingTemplate = TheThingFactory->newOverride( thingTemplate );
	}

	if (reskinFrom.isNotEmpty())
	{
		const ThingTemplate* reskinTmpl = TheThingFactory->findTemplate(reskinFrom);
		if (reskinTmpl)
		{
			thingTemplate->copyFrom(reskinTmpl);
			thingTemplate->setCopiedFromDefault();
			thingTemplate->setReskinnedFrom(reskinTmpl);
			ini->initFromINI( thingTemplate, thingTemplate->getReskinFieldParse() );
		}
		else
		{
			DEBUG_CRASH(("ObjectReskin must come after the original Object (%s, %s).\n",reskinFrom.str(),name.str()));
			throw INI_INVALID_DATA;
		}
	}
	else
	{
		ini->initFromINI( thingTemplate, thingTemplate->getFieldParse() );
	}

	thingTemplate->validate();
	
	if( ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES )
	{
		thingTemplate->resolveNames();
	}

#if defined(_DEBUG) || defined(_INTERNAL)
	TheThingTemplateBeingParsedName.clear();
#endif
}

//#define CHECK_THING_NAMES
#ifdef CHECK_THING_NAMES

#include "Common/STLTypedefs.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
}

const char *outFilenameINI				= "thing.txt";
const char *outFilenameStringFile	= "thingString.txt";

void resetReportFile( void )
{
	FILE *fp = fopen(outFilenameINI, "w");
	if (fp)
	{
		fprintf(fp, "-- ThingTemplate INI Report --\n\n");
		fclose(fp);
	}

	fp = fopen(outFilenameStringFile, "w");
	if (fp)
	{
		fprintf(fp, "-- ThingTemplate String File Report --\n\n");
		fclose(fp);
	}
}

AsciiStringList missingStrings;
void reportMissingNameInStringFile( AsciiString templateName )
{
	// see if we've seen it before
	AsciiStringListConstIterator cit = std::find(missingStrings.begin(), missingStrings.end(), templateName);
	if (cit != missingStrings.end())
		return;

	missingStrings.push_back(templateName);
}

void dumpMissingStringNames( void )
{
	missingStrings.sort();
	FILE *fp = fopen(outFilenameStringFile, "w");
	if (fp)
	{
		fprintf(fp, "-- ThingTemplate String File Report --\n\n");
		for (AsciiStringListConstIterator cit = missingStrings.begin(); cit!=missingStrings.end(); cit++)
		{
			fprintf(fp, "OBJECT:%s\n\"%s\"\nEND\n\n", cit->str(), cit->str());
		}
		fclose(fp);
	}
}

AsciiStringList missingNames;
void reportMissingNameInTemplate( AsciiString templateName )
{
	// see if we've seen it before
	AsciiStringListConstIterator cit = std::find(missingNames.begin(), missingNames.end(), templateName);
	if (cit != missingNames.end())
		return;

	missingNames.push_back(templateName);

	FILE *fp = fopen(outFilenameINI, "a+");
	if (fp)
	{
		fprintf(fp, "  DisplayName      = OBJECT:%s\n", templateName.str());
		fclose(fp);
	}

	//reportMissingNameInStringFile( templateName );
}

#endif

//-------------------------------------------------------------------------------------------------
/** Post process phase after loading the database files */
//-------------------------------------------------------------------------------------------------
// BFME2 postProcessLoad is recovered in ThingFactoryReset.cpp.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?dup_002ca82c@@YAXXZ=??$_Construct@VArmorTemplateSet@@V1@@_STL@@YAXPAVArmorTemplateSet@@ABV1@@Z")

// Retain this unit's existing header-inline row after the unfinished
// freeDatabase caller moves to its verified BFME2 unit. This pointer is
// a compile anchor, not a retail data claim.
extern ThingTemplate *(ThingTemplate::*const _bfmeInlineAnchorFriendNext)() const =
    &ThingTemplate::friend_getNextTemplate;

// The same for the header-inline rows that the ZH ThingTemplate::operator=
// used to pull in: compile anchors, not retail data claims.
extern ProductionPrerequisite &(ProductionPrerequisite::*const _bfmeInlineAnchorPrereqAssign)(const ProductionPrerequisite &) =
    &ProductionPrerequisite::operator=;
extern DynamicAudioEventRTS &(DynamicAudioEventRTS::*const _bfmeInlineAnchorDynAudioAssign)(const DynamicAudioEventRTS &) =
    &DynamicAudioEventRTS::operator=;
extern std::vector<ProductionPrerequisite>::size_type (std::vector<ProductionPrerequisite>::*const _bfmeInlineAnchorPrereqSize)() const =
    &std::vector<ProductionPrerequisite>::size;
