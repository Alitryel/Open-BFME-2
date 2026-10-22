// cl: /O1 /Ireference/shims/bfme2htree /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/htree.cpp); this unit had no counterpart under Code/.
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

/* $Header: /Commando/Code/ww3d2/htree.cpp 14    10/01/01 6:07p Patrick $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/htree.cpp                              $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 10/01/01 6:06p                                              $* 
 *                                                                                             * 
 *                    $Revision:: 14                                                          $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   HTreeClass::HTreeClass -- constructor                                                     *  
 *   HTreeClass::~HTreeClass -- destructor                                                     * 
 *   HTreeClass::Load -- loads a hierarchy tree from a file                                    * 
 *   HTreeClass::read_pivots -- reads the pivots out of a file                                 * 
 *   HTreeClass::Free -- de-allocate all memory in use                                         * 
 *   HTreeClass::Base_Update -- Computes the base pose transform for each pivot                * 
 *   HTreeClass::Anim_Update -- Computes the transform for each pivot with motion              * 
 *   HTreeClass::Blend_Update -- computes each pivot as a blend of two anims                   *
 *   HTreeClass::Combo_Update -- compute each pivot's transform using an anim combo            *
 *   HTreeClass::Get_Transform -- returns the transformation for the desired pivot             * 
 *   HTreeClass::Find_Bone -- Find a bone by name                                              *
 *   HTreeClass::Get_Bone_Name -- get the name of a bone from its index                        *
 *   HTreeClass::Update_Parent_Need_Bits -- all "needed" children force their parents to be nee*
 *   HTreeClass::HTreeClass -- copy constructor                                                *
 *   HTreeClass::Get_Parent_Index -- returns index of the parent of the given bone             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "htree.h"
#include "hanim.h"
#include "hcanim.h"
#include <string.h>
#include <assert.h>
#include "wwmath.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwmemlog.h"
#include "hrawanim.h"
// Bind channel reads to the byte-verified HRawAnim providers at 0x00160010
// and 0x001600A0, using their unpooled 0x20-byte channel layout.
#define BFME_MOTION_CHANNEL_OUT_OF_LINE
#include "../../../../../reference/shims/bfmehrawanim/motchan.h"
#undef BFME_MOTION_CHANNEL_OUT_OF_LINE

/*********************************************************************************************** 
 * HTreeClass::HTreeClass -- constructor                                                       * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
HTreeClass::HTreeClass(void) :
	NumPivots(0),
	Pivot(NULL),
	ScaleFactor(1.0f)
{
	// BFME's six extra members and an empty name.
	OwnedSequence1C[0] = 0;
	OwnedSequence1C[1] = 0;
	OwnedSequence1C[2] = 0;
	Unknown28 = 0;
	Unknown2C = 0;
	Unknown30 = 0;
	Name[0] = 0;
}

// HTreeClass::Init_Default: defined in HTreeClassInitDefault.cpp (its row's unit).

/*********************************************************************************************** 
 * HTreeClass::~HTreeClass -- destructor                                                       * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// HTreeClass::~HTreeClass: defined in HTreeClassDestructor.cpp (its row's unit).


/***********************************************************************************************
 * HTreeClass::HTreeClass -- copy constructor                                                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/4/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// HTreeClass::HTreeClass(const HTreeClass &): defined in HTreeClassCopyConstructor.cpp (its row's unit).

/*********************************************************************************************** 
 * HTreeClass::Load -- loads a hierarchy tree from a file                                      * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// Exact retail hierarchy loader with the BFME pivot ABI: HTreeClassLoadW3D.cpp.


/*********************************************************************************************** 
 * HTreeClass::read_pivots -- reads the pivots out of a file                                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// HTreeClass::read_pivots: defined in HTreeClassReadPivots.cpp (O2 retail region).


/*********************************************************************************************** 
 * HTreeClass::Free -- de-allocate all memory in use                                           * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/


// HTreeClass::Simple_Evaluate_Pivot(motion, pivot, frame, obj_tm, end_tm) is
// rowed at 0x00161700 with BFME2's body (HTreeClassReadPivots.cpp); the donor
// body that stood here was not retail's and would be the copy the link keeps.



// The compact-pivot overload is defined in HTreeClassBoneLookup.cpp.

// HTreeClass::Base_Update is defined in HTreeClassFirstCapturedBone.cpp.

/*********************************************************************************************** 
 * HTreeClass::Anim_Update -- Computes the transform for each pivot with motion                * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// HTreeClass::Anim_Update(const Matrix3D &, HAnimClass *, float) is defined in
// HTreeClassFirstCapturedBone.cpp.
								
// HTreeClass::Anim_Update(const Matrix3D &, HRawAnimClass *, float) is defined
// in HTreeClassFirstCapturedBone.cpp.


// HTreeClass::Blend_Update is defined in HTreeClassFirstCapturedBone.cpp.


// HTreeClass::Combo_Update is defined in HTreeClassFirstCapturedBone.cpp.


/***********************************************************************************************
 * HTreeClass::Find_Bone -- Find a bone by name                                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/4/97    GTH : Created.                                                                 *
 *=============================================================================================*/
// HTreeClass::Get_Bone_Index: defined in HTreeClassBoneLookup.cpp (its row's unit).


/***********************************************************************************************
 * HTreeClass::Get_Bone_Name -- get the name of a bone from its index                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/4/97    GTH : Created.                                                                 *
 *=============================================================================================*/
// HTreeClass::Get_Bone_Name: defined in HTreeClassBoneLookup.cpp (its row's unit).


/***********************************************************************************************
 * HTreeClass::Get_Parent_Index -- returns index of the parent of the given bone               *
 *                                                                                             *
 * INPUT:                                                                                      *
 * boneidx - the bone you are interested in                                                    *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 * the index of that bone's parent                                                             *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/12/2000  gth : Created.                                                                 *
 *=============================================================================================*/
// HTreeClass::Get_Parent_Index: defined in HTreeClassBoneLookup.cpp (its row's unit).


// Scale this HTree by a constant factor:
// HTreeClass::Scale: defined in HTreeClassScale.cpp (its row's unit).



// HTreeClass::Capture_Bone (0x00166980) is rowed in HTreeClassCaptureBone.cpp; a second definition here would not link.

// HTreeClass::Release_Bone: defined in HTreeClassReleaseBone.cpp (its row's unit).

// HTreeClass::Is_Bone_Captured: defined in HTreeClassIsBoneCaptured.cpp (its row's unit).

// HTreeClass::Control_Bone: defined in htree_control.cpp (its row's unit).

// HTreeClass::Get_Bone_Control (0x001620D0) is rowed in Get_Bone_ControlRva001620D0Farm.cpp; a second definition here would not link.

// ?Alter_Avatar_HTree@HTreeClass@@ present-unmatched
HTreeClass * HTreeClass::Alter_Avatar_HTree( const HTreeClass *tree, Vector3 &scale)
{
	// This is a specific list of pivot names used in the avatar meshes that we need to special case for scaling
	// The reason is due to the fact that we want to scale the avatar's bone structure with differing amount for
	// each axis, and with the T-pos of the avatar skeleton, undesirable results are caused due to the arms and hands
	// being stretched out on the Y-axis instead of the Z-axis like the rest of the bodies. Hence, the list of pivots
	// below are ones that I will special case and scale them based on the Z-axis scaling factor instead of the Y-axis
	// scaling factor.
	char * flip_list[] = { " RIGHTFOREARM", " RIGHTHAND", " LEFTFOREARM", " LEFTHAND", "RIGHTINDEX", "RIGHTFINGERS", "RIGHTTHUMB", "LEFTINDEX", "LEFTFINGERS", "LEFTTHUMB", 0 };
		
	// Clone the new tree with the tree that is passed in
	HTreeClass * new_tree = new HTreeClass( *tree );

	// Go through each of the pivots and calculate and transform the pivots to match the desired scaling factor
	for(int pi = 0; pi < new_tree->NumPivots; ++pi) {
		PivotClass piv = tree->Pivot[pi];
		Vector3 adjusted_scale = scale;
		
		// If there is no parent, skip
		if(!piv.Parent) continue;

		// If the pivot is on the flip list, use the Z scale to scale both the Z & Y axis 
		int index = 0;
		while(true) {
			if(!flip_list[index]) {
				break;
			} else if(strcmp(piv.Name, flip_list[index]) == 0) {
				adjusted_scale.Y = scale.Z;
				break;
			}
			++index;
		}

		// Get the positions of the pivot and the pivot's parent in worldspace & apply the altering scale to it
		Vector3 pivot_pos = piv.Transform.Get_Translation();
		Vector3 pivot_parent_pos = piv.Parent->Transform.Get_Translation();
		pivot_pos.Scale(adjusted_scale);
		pivot_parent_pos.Scale(adjusted_scale);

		// Get the pivot's parent's inverse transform
		Matrix3D parent_inverse_transform;
		piv.Parent->Transform.Get_Inverse(parent_inverse_transform);

		// Get the new desired vector in worldspace
		Vector3 new_relative_vector = pivot_pos - pivot_parent_pos;

		// Rotate the new vector by the pivot's parent's inverse transform to put it in local space 
		new_relative_vector = parent_inverse_transform.Rotate_Vector(new_relative_vector);

		// Store the final result in the new HTree
		new_tree->Pivot[pi].BaseTransform.Set_Translation( new_relative_vector );
	}

	return new_tree;
}

// Morph the bones on the HTree using weights from a number of other HTrees
// ?Create_Morphed@HTreeClass@@ present-unmatched
HTreeClass * HTreeClass::Create_Morphed(	int num_morph_sources,
														const float morph_weights[],
														const HTreeClass *tree_array[] )
{
	int i;
	assert(num_morph_sources>0);
	for(i=0;i<num_morph_sources;i++) {
		assert( tree_array[i] );
		assert( morph_weights[i]>=0.0f && morph_weights[i]<=1.0f );
	}
	for(i=0;i<num_morph_sources-1;i++) {
		assert( tree_array[i]->NumPivots == tree_array[i+1]->NumPivots );
	}

	// Clone the first one,
	HTreeClass * new_tree = W3DNEWARRAY HTreeClass( *tree_array[0] );

	// Then interpolate all the pivots translations
	for (int pi = 0; pi < new_tree->NumPivots; pi++) {

		Vector3 pos(0.0f,0.0f,0.0f);
		for(int nm = 0; nm < num_morph_sources; nm++) {
			pos.X += tree_array[nm]->Pivot[pi].BaseTransform.Get_Translation().X*morph_weights[nm];
			pos.Y += tree_array[nm]->Pivot[pi].BaseTransform.Get_Translation().Y*morph_weights[nm];
			pos.Z += tree_array[nm]->Pivot[pi].BaseTransform.Get_Translation().Z*morph_weights[nm];
		}

		new_tree->Pivot[pi].BaseTransform.Set_Translation( pos );
	}

	return new_tree;
}

// Create an HTree by Interpolating between others
// ?Create_Interpolated@HTreeClass@@ present-unmatched
HTreeClass * HTreeClass::Create_Interpolated(	const HTreeClass * tree_a0_b0, 
																const HTreeClass * tree_a0_b1, 
																const HTreeClass * tree_a1_b0, 
																const HTreeClass * tree_a1_b1, 
																float lerp_a, float lerp_b )
{
	assert( tree_a0_b0->NumPivots == tree_a0_b1->NumPivots );
	assert( tree_a0_b0->NumPivots == tree_a1_b0->NumPivots );
	assert( tree_a0_b0->NumPivots == tree_a1_b1->NumPivots );

	// Clone the first one,
	HTreeClass * new_tree = W3DNEW HTreeClass( *tree_a0_b0 );

	// Then interpolate all the pivots translations
	Vector3 pos_a0, pos_a1, pos;
	for (int pi = 0; pi < new_tree->NumPivots; pi++) {

// ?Lerp@Vector3@@ present-unmatched
		Vector3::Lerp( tree_a0_b0->Pivot[pi].BaseTransform.Get_Translation(),
							  		  tree_a0_b1->Pivot[pi].BaseTransform.Get_Translation(),
									  lerp_b, &pos_a0 );
// ?Lerp@Vector3@@ present-unmatched
		Vector3::Lerp( tree_a1_b0->Pivot[pi].BaseTransform.Get_Translation(),
									  tree_a1_b1->Pivot[pi].BaseTransform.Get_Translation(),
									  lerp_b, &pos_a1 );
		Vector3::Lerp( pos_a0, pos_a1, lerp_a, &pos );

		new_tree->Pivot[pi].BaseTransform.Set_Translation( pos );
	}

	return new_tree;
}

// Create an HTree by Interpolating between others
// ?Create_Interpolated@HTreeClass@@ present-unmatched
HTreeClass * HTreeClass::Create_Interpolated(const HTreeClass * tree_base, 
														   const HTreeClass * tree_a, 
														   const HTreeClass * tree_b, 
														   float a_scale, float b_scale )
{
	WWMEMLOG(MEM_ANIMATION);
	assert( tree_base->NumPivots == tree_a->NumPivots );
	assert( tree_base->NumPivots == tree_b->NumPivots );

	// Clone the first one,
	HTreeClass * new_tree = W3DNEW HTreeClass( *tree_base );

	float	a_scale_abs = WWMath::Fabs( a_scale );
	float	b_scale_abs = WWMath::Fabs( b_scale );

	if ( a_scale_abs + b_scale_abs > 0 ) {

		// Then interpolate all the pivots translations
		Vector3 pos_a, pos_b, pos;
		for (int pi = 0; pi < new_tree->NumPivots; pi++) {

// ?Lerp@Vector3@@ present-unmatched
			Vector3::Lerp( tree_base->Pivot[pi].BaseTransform.Get_Translation(),
							  			 tree_a->Pivot[pi].BaseTransform.Get_Translation(),
										 a_scale, &pos_a );
// ?Lerp@Vector3@@ present-unmatched
			Vector3::Lerp( tree_base->Pivot[pi].BaseTransform.Get_Translation(),
										 tree_b->Pivot[pi].BaseTransform.Get_Translation(),
										 b_scale, &pos_b );

			pos   = (pos_a * a_scale_abs + pos_b * b_scale_abs ) / ( a_scale_abs + b_scale_abs );

			new_tree->Pivot[pi].BaseTransform.Set_Translation( pos );
		}
	}

	return new_tree;
}


// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
