// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MT /EHsc /Ireference/shims/bfme2_aggdef /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/agg_def.cpp); this unit had no counterpart under Code/.
// The class is BFME 1's shape (reference/shims/bfme2_aggdef/agg_def.h): bool
// load/save family, 17 virtual slots.
// /MT preserves retail's direct free/strdup calls in the assignment operator.
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

// Retail treats array delete as nothrow: ~AggregateDefClass (0x001A3C90) has
// no EH state store between its body and the member vector's teardown, which
// the compiler drops only when delete[] cannot throw.
void __cdecl operator delete[](void *) throw();

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/agg_def.cpp          $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                
 *                                                                                             *
 *                     $Modtime:: 4/05/01 10:21a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "agg_def.h"
#include "htree.h"
#include "w3derr.h"
#include "chunkio.h"
#include "wwdebug.h"
#include "assetmgr.h"
#include "matinfo.h"
#include "texture.h"
#include "wwstring.h"

#include <windows.h>


///////////////////////////////////////////////////////////////////////////////////
//
//	Local constants
//
const char * const EMPTY_STRING			= "";

// Rowed global factory at 0x00136175: BFME2 calls it directly; its
// AggregateDefClass has no ZH Create_Render_Object/Load_Assets virtuals.
RenderObjClass * __cdecl Create_Render_Obj (const char *name);

// BFME2 reads the sub-object-LOD flag as a direct bit extract instead of the
// ZH virtual query (retail: ([param+0x10] >> 0x14) & 1 into Flags). TU-local
// reader so the shared RenderObjClass shim stays untouched.
class RenderObjFlagReader : public RenderObjClass
{
public:
	unsigned long Read_Subobj_Lod_Bit (void) const	{ return ((Bits >> 0x14) & 1); }
};


///////////////////////////////////////////////////////////////////////////////////
//
//	Global variable initialization
//
AggregateLoaderClass	_AggregateLoader;


///////////////////////////////////////////////////////////////////////////////////
//
//	AggregateDefClass
//
AggregateDefClass::AggregateDefClass (void)
	: m_Version (0),
	  m_pName (NULL)
{
	// Set our member data to default settings
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_MiscInfo, 0, sizeof (m_MiscInfo));
	m_MiscInfo.OriginalClassID = RenderObjClass::CLASSID_HLOD;
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	AggregateDefClass
//
AggregateDefClass::AggregateDefClass (const AggregateDefClass &src)
	: m_pName (NULL)
{
	// Set our member data to default settings
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_MiscInfo, 0, sizeof (m_MiscInfo));
	m_MiscInfo.OriginalClassID = RenderObjClass::CLASSID_HLOD;

	// Invoke the assignment operator
	(*this) = src;
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	AggregateDefClass
//
AggregateDefClass::AggregateDefClass (RenderObjClass &base_model)
	: m_pName (NULL)
{
	// Set our member data to default settings
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_MiscInfo, 0, sizeof (m_MiscInfo));
	m_MiscInfo.OriginalClassID = RenderObjClass::CLASSID_HLOD;

	Initialize (base_model);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	~AggregateDefClass
//
AggregateDefClass::~AggregateDefClass (void)
{
	// Free the name buffer if necessary
	if (m_pName != NULL) {
		
		// free() is used because the buffer was allocated with ::_strdup().
		::free (m_pName);
		m_pName = NULL;
	}	

	Free_Subobject_List ();
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	operator=
//
const AggregateDefClass &
AggregateDefClass::operator= (const AggregateDefClass &src)
{
	int index;

	// Free the name buffer if necessary
	if (m_pName != NULL) {		
		::free (m_pName);
		m_pName = NULL;
	}	

	// Start with a fresh set of data
	Free_Subobject_List ();

	// Copy the src object's name and info struct
	Set_Name (src.Get_Name ());
	::memcpy (&m_Info, &src.m_Info, sizeof (m_Info));
	::memcpy (&m_MiscInfo, &src.m_MiscInfo, sizeof (m_MiscInfo));	
	m_Version = src.m_Version;

	// Loop through all the entries in the src object's subobj list
	for (index = 0; index < src.m_SubobjectList.Count (); index ++) {
		W3dAggregateSubobjectStruct *pinfo = src.m_SubobjectList[index];
		if (pinfo != NULL) {

			// Copy the src object's info for this subobj
			W3dAggregateSubobjectStruct *new_info = W3DNEW W3dAggregateSubobjectStruct;
			::memcpy (new_info, pinfo, sizeof (W3dAggregateSubobjectStruct));

			// Add this subobj to our list
			m_SubobjectList.Add (new_info);
		}
	}

	// Return a reference to ourselves
	return *this;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Free_Subobject_List
//
void
AggregateDefClass::Free_Subobject_List (void)
{
	// Delete all the stucture pointers contained in the subobject list
	for (int index = 0; index < m_SubobjectList.Count (); index ++) {
		W3dAggregateSubobjectStruct *pinfo = m_SubobjectList[index];
		if (pinfo) {
			delete pinfo;
		}
	}

	// Reset the lists contents
	m_SubobjectList.Delete_All ();
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Create
//
RenderObjClass *
AggregateDefClass::Create (void)
{
	// BFME2 builds the base model through the global factory (0x00136175),
	// as Initialize does, not through a member wrapper.
	RenderObjClass *pmodel = ::Create_Render_Obj (m_Info.BaseModelName);
	if (pmodel != NULL) {
		
		// Perform the aggregation
		Attach_Subobjects (*pmodel);

		// Let the new object know what its new name and base name are.
		pmodel->Set_Name (m_pName);
		pmodel->Set_Base_Model_Name (m_Info.BaseModelName);
		pmodel->Set_Sub_Objects_Match_LOD ((m_MiscInfo.Flags & W3D_AGGREGATE_FORCE_SUB_OBJ_LOD) == W3D_AGGREGATE_FORCE_SUB_OBJ_LOD);

	} else {
		WWDEBUG_SAY (("Unable to load aggregate %s.\r\n", m_Info.BaseModelName));
	}

	// Return a pointer to the new aggregate
	return pmodel;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Find_Subobject
//


///////////////////////////////////////////////////////////////////////////////////
//
//	Attach_Subobjects
//


///////////////////////////////////////////////////////////////////////////////////
//
//	Initialize
//
void
AggregateDefClass::Initialize (RenderObjClass &base_model)
{
	// Start with fresh lists
	Free_Subobject_List ();

	// Determine what the render objects original name was.
	const char *orig_model_name = base_model.Get_Base_Model_Name ();
	orig_model_name = (orig_model_name == NULL) ? base_model.Get_Name () : orig_model_name;

	// Record information about this base model
	::lstrcpy (m_Info.BaseModelName, orig_model_name);
	m_Info.SubobjectCount = 0;
	m_MiscInfo.OriginalClassID = base_model.Class_ID ();
	m_MiscInfo.Flags = 0;
	m_MiscInfo.Flags = ((const RenderObjFlagReader &)base_model).Read_Subobj_Lod_Bit ();


	// Pass the aggregate name along
	Set_Name (base_model.Get_Name ());

	// Create a new instance of the model which we can use
	// to compare with the supplied model and determine
	// which 'bones-models' and textures are new.
	RenderObjClass *pvanilla_model = ::Create_Render_Obj (orig_model_name);

	// Build lists of changes from the delta between the original model and the provided one.
	Build_Subobject_List (*pvanilla_model, base_model);

	// Release the model if necessary
	REF_PTR_RELEASE (pvanilla_model);	
	return ;
}



///////////////////////////////////////////////////////////////////////////////////
//
//	Build_Subobject_List
//


///////////////////////////////////////////////////////////////////////////////////
//
//	Is_Object_In_List
//
bool
AggregateDefClass::Is_Object_In_List
(
	const char *passet_name,
	DynamicVectorClass <RenderObjClass *> &node_list
)
{
	// Assume failure
	bool retval = false;

	// Loop through the nodes in the list until we've found the one
	// were are looking for.
	for (int node_index = 0; (node_index < node_list.Count ()) && (retval == false); node_index ++) {
		RenderObjClass *prender_obj = node_list[node_index];
		
		// Is this the render object we were looking for?
		if (prender_obj != NULL &&
		    ::lstrcmpi (prender_obj->Get_Name (), passet_name) == 0) {
			retval = true;
		}
	}	

	// Return the true/false result code
	return retval;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Add_Subobject
//
void
AggregateDefClass::Add_Subobject (const W3dAggregateSubobjectStruct &subobj_info)
{
	// Create a new structure and copy the contents of the src
	W3dAggregateSubobjectStruct *pnew_entry = W3DNEW W3dAggregateSubobjectStruct;
	::lstrcpy (pnew_entry->SubobjectName, subobj_info.SubobjectName);
	::lstrcpy (pnew_entry->BoneName, subobj_info.BoneName);

	// Add this new entry to the list
	m_SubobjectList.Add (pnew_entry);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Read_Class_Info
//
bool
AggregateDefClass::Read_Class_Info (ChunkLoadClass &chunk_load)
{
	// Assume error
	bool ret_val = false;

	// Read the chunk straight into our header structure
	::memset (&m_MiscInfo, 0, sizeof (m_MiscInfo));
	if (chunk_load.Read (&m_MiscInfo, sizeof (m_MiscInfo)) == sizeof (m_MiscInfo)) {

		// Success!
		ret_val = true;
	}

	// Return the true/false result code
	return ret_val;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Save_Subobject
//
bool
AggregateDefClass::Save_Subobject
(
	ChunkSaveClass &chunk_save,
	W3dAggregateSubobjectStruct *psubobject
)
{
	// Assume error
	bool ret_val = false;

	// Write the subobj structure out to the chunk
	if (chunk_save.Write (psubobject, sizeof (W3dAggregateSubobjectStruct)) == sizeof (W3dAggregateSubobjectStruct)) {

		// Success!
		ret_val = true;
	}

	// Return the true/false result code
	return ret_val;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Load
//
PrototypeClass *
// ?AggregateLoaderClass::Load_W3D present-unmatched
AggregateLoaderClass::Load_W3D (ChunkLoadClass &chunk_load)
{
	// Assume failure
	AggregatePrototypeClass *pprototype = NULL;

	// Create a definition object
	AggregateDefClass *pdefinition = W3DNEW AggregateDefClass;
	if (pdefinition != NULL) {
		
		// Ask the definition object to load the aggregate data
		if (pdefinition->Load_W3D (chunk_load) != true) {
			
			// Error!  Free the definition
			delete pdefinition;
			pdefinition = NULL;
		} else {

			// Success!  Create a prototype from the definition
			pprototype = W3DNEW AggregatePrototypeClass (pdefinition);
		}
	}

    // Return a pointer to the prototype
	 return pprototype;
}
