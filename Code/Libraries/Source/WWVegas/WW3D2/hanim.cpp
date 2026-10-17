// cl: /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#define Matrix4x4 Matrix4
// Retail treats array delete as nothrow: ~NamedPivotMapClass (0x001976F0) has
// no EH state store between its WeightInfo teardown and the PivotMapClass
// base's, which the compiler drops only when delete[] cannot throw.
void __cdecl operator delete[](void *) throw();

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
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

/* $Header: /Commando/Code/ww3d2/hanim.cpp 3     12/13/01 7:01p Patrick $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hanim.cpp                              $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 12/13/01 6:54p                                              $* 
 *                                                                                             * 
 *                    $Revision:: 3                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "hanim.h"
#include "assetmgr.h"
#include "htree.h"
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"



/*
**
**	HAnimComboClass
**
**
*/


NamedPivotMapClass::~NamedPivotMapClass(void)
{
}

NamedPivotMapClass::WeightInfoStruct & NamedPivotMapClass::WeightInfoStruct::operator = (WeightInfoStruct const &that)
{	
	if(Name) delete [] Name;
	assert(that.Name != 0);
	Name = nstrdup(that.Name); 
	Weight = that.Weight; 
	return *this; 
}

// add a name & weight to the arrays
void NamedPivotMapClass::Add(const char *Name, float Weight)
{
	WeightInfoStruct info;
	info.Name = (char *) Name;
	info.Weight = Weight;
	WeightInfo.Add(info);	
	info.Name = 0;
}

// configure the base pivot map using the specified tree
void NamedPivotMapClass::Update_Pivot_Map(const HTreeClass *Tree)
{
	// first, resize the base pivot map to fit the tree
	int numPivots = Tree->Num_Pivots();

	Resize(numPivots);
	ActiveCount = numPivots;

	// first, reset all weights to 1 (the default)
	while(numPivots--) {
		(*this)[numPivots] = 1.0f;
	}

	// for each named pivot, find the correct index and set the weight if the indicated bone is present
	// note: there is no check for redundant names
	int count = WeightInfo.Count();
	while(count--) {
		int actualPivot = Tree->Get_Bone_Index(WeightInfo[count].Name);
		if(actualPivot != -1) {
			(*this)[actualPivot] = WeightInfo[count].Weight;
		} 
	}
}

/*
**
*/
DEFINE_AUTO_POOL(HAnimComboDataClass,256);

// ??1HAnimClass@@UAE@XZ
HAnimClass::~HAnimClass(void)
{
}


// Definition moved to hanim_HAnimComboClass_ctor.cpp: the /G7 split TU needs
// the body visible to inline it into HAnimComboClass::HAnimComboClass(int).


// ?HAnimComboDataClass::HAnimComboDataClass present-unmatched
HAnimComboDataClass::HAnimComboDataClass(const HAnimComboDataClass &src)
:	PivotMap(src.Get_Pivot_Map()),
	HAnim(src.Get_HAnim())
{
	Shared = src.Is_Shared();
	Frame = src.Get_Frame();
	Weight = src.Get_Weight();
}


// ?HAnimComboDataClass::~HAnimComboDataClass present-unmatched
HAnimComboDataClass::~HAnimComboDataClass(void)
{
	if(HAnim) 
		HAnim->Release_Ref();
	if(PivotMap)
		PivotMap->Release_Ref();
}


__declspec(noinline) inline void HAnimComboDataClass::Set_HAnim(HAnimClass *motion)
{
	if ( motion != NULL ) {
		motion->Add_Ref();
	}
	if ( HAnim != NULL ) {
		HAnim->Release_Ref();
	}
	HAnim = motion;
}



/*
**	This function will replace the current pivot map (if any) with another pivot map that is
** set to 1 for only those pivot indices that actually have data.
*/
// ?HAnimComboDataClass::Build_Active_Pivot_Map present-unmatched
void HAnimComboDataClass::Build_Active_Pivot_Map(void) 
{
	if ( PivotMap != NULL ) {
		PivotMap->Release_Ref();
	}
	if(HAnim == NULL) {
		PivotMap = 0;
		return;
	}

	int numpivots = HAnim->Get_Num_Pivots();
	PivotMap = NEW_REF( PivotMapClass, ());
	PivotMap->Resize(numpivots);

	int count = 0;
	while(count < numpivots) {
		if(HAnim->Is_Node_Motion_Present(count)) {
			PivotMap->Add(1);

		} else {
			PivotMap->Add(0);
		}
		count++;
	}
}

/*	
**	HAnimComboClass
**
**
*/

HAnimComboClass::HAnimComboClass(void)
{}

// Body split to hanim_HAnimComboClass_ctor.cpp: retail built this ctor with
// /G7 (sub edi,1 loop decrement) while the rest of this TU only matches
// without it (Set_HAnim needs inc). See hanim_weight_vector_add.cpp.


// ?HAnimComboClass::~HAnimComboClass present-unmatched
HAnimComboClass::~HAnimComboClass(void)
{
	Reset();
}





void	HAnimComboClass::Set_Motion( int index, HAnimClass *motion )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_HAnim(motion);
}

// Get_Motion is defined in HAnimComboClassGetMotion.cpp: its /G7 build
// matches retail's ADD refcount increment; this unit needs INC for Set_HAnim.

// ?HAnimComboClass::Peek_Motion present-unmatched
HAnimClass *HAnimComboClass::Peek_Motion( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	HAnimClass *anim = data->Peek_HAnim();
	return anim;
}

// ?HAnimComboClass::Set_Frame present-unmatched
void	HAnimComboClass::Set_Frame( int index, float frame )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_Frame(frame);
}

// ?HAnimComboClass::Get_Frame present-unmatched
float	HAnimComboClass::Get_Frame( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Get_Frame();
}

// ?HAnimComboClass::Set_Weight present-unmatched
void	HAnimComboClass::Set_Weight( int index, float weight )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_Weight(weight);
}

// ?HAnimComboClass::Get_Weight present-unmatched
float	HAnimComboClass::Get_Weight( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Get_Weight();
}


// Get_Pivot_Weight_Map has the same /G7 provider as Get_Motion.

// ?HAnimComboClass::Peek_Pivot_Weight_Map present-unmatched
PivotMapClass	*HAnimComboClass::Peek_Pivot_Weight_Map( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Peek_Pivot_Map();
}

void HAnimComboClass::Append_Anim_Combo_Data(HAnimComboDataClass * Data)
{
	HAnimComboData.Add(Data);
}

void HAnimComboClass::Remove_Anim_Combo_Data(HAnimComboDataClass * Data)
{
	HAnimComboData.Delete(Data);
}

