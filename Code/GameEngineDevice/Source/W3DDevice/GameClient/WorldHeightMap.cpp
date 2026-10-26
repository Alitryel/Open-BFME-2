// cl: /Ireference/shims/bfmeheightmap /Ireference/shims/zh_overridable_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// Matched operations inline; keep CRT math wrappers local to this unit.
#pragma push_macro("inline")
#define inline static inline
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include <math.h>
#pragma pop_macro("inline")

// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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

// WorldHeightMap.cpp
// Class to encapsulate height map.
// Author: John Ahlquist, April 2001

#define INSTANTIATE_WELL_KNOWN_KEYS

#include "windows.h"
#include "stdlib.h"
#include <string.h>
#include "Common/STLTypedefs.h"

#include "Common/DataChunk.h"
//#include "Common/GameFileSystem.h"
#include "Common/FileSystem.h" // for LOAD_TEST_ASSETS
#include "Common/GlobalData.h"
#include "Common/MapReaderWriterInfo.h"
#include "Common/TerrainTypes.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/WellKnownKeys.h"

// BFME2-only caches used by 30DA25/30D773. Retail .data contains a zero
// key plus each exact name pointer at DBDC84, DBDD84 and DBDD8C. Keep
// them beside the existing StaticNameKey owners instead of address aliases.
extern const StaticNameKey TheKey_GenericAIObjectType("GenericAIObjectType");
extern const StaticNameKey TheKey_objectBasePriority("objectBasePriority");
extern const StaticNameKey TheKey_objectBasePhase("objectBasePhase");
// Waypoint keys TerrainLogic's map load reads: zero cache plus the name
// pointer at 0x009BDCB4/0x009BDCBC (names at VA 0x00C091A8/0x00C091B8).
extern const StaticNameKey TheKey_waypointType("waypointType");
extern const StaticNameKey TheKey_waypointTypeOption("waypointTypeOption");
// BFME2 player keys between the WellKnownKeys player block entries: zero
// cache plus the name pointer at 0x009BDE74 (after playerNightColor),
// 0x009BDEA4 and 0x009BDEAC (after playerAIType; names at VA 0x00C09600,
// 0x00C09674, 0x00C09688). Player::initFromDict and GameLogic read them.
extern const StaticNameKey TheKey_playerHandicap("playerHandicap");
extern const StaticNameKey TheKey_playerFactionIcon("playerFactionIcon");
extern const StaticNameKey TheKey_livingWorldPlayerID("livingWorldPlayerID");


#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/SidesList.h"

#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/TileData.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/W3DShadow.h"

#include "Common/file.h"
// Preserve STLport operations inline without unused external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline ICoord2D *
__copy_backward_ptrs<ICoord2D *, ICoord2D *>(ICoord2D *__first, ICoord2D *__last, ICoord2D *__result, const __false_type &)
{
    return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (ptrdiff_t *)0);
}
template <> __declspec(dllimport) __forceinline ICoord2D *
vector<ICoord2D, allocator<ICoord2D> >::erase(ICoord2D *__first, ICoord2D *__last)
{
    pointer __i = __copy_ptrs(__last, this->_M_finish, __first, _TrivialAss());
    _Destroy(__i, this->_M_finish);
    this->_M_finish = __i;
    return __first;
}
}
// bfme link decl-only begin
namespace _STL { template <> void vector<ICoord2D, allocator<ICoord2D> >::_M_insert_overflow(ICoord2D *, ICoord2D const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> ICoord2D * allocator<ICoord2D>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define K_OBSOLETE_HEIGHT_MAP_VERSION 8

#define PATHFIND_CLIFF_SLOPE_LIMIT_F	9.8f	

// -----------------------------------------------------------
static AsciiString validateName(AsciiString n, Int flags)
{

	return n;

}

/* ********* GDIFileStream class ****************************/
class GDIFileStream : public InputStream
{
protected:
	File* m_file;
public:
	GDIFileStream(File* pFile):m_file(pFile) {};
	virtual Int read(void *pData, Int numBytes) {
			return(m_file->read(pData, numBytes));
	};
};


/* ********* MapObject class ****************************/
/*static*/ MapObject *MapObject::TheMapObjectListPtr = NULL;
/*static*/ Dict MapObject::TheWorldDict;





void MapObject::setRenderObj(RenderObjClass *pObj)
{
	REF_PTR_SET(m_renderObj, pObj);
}

#pragma optimize("s", on)
void MapObject::setBridgeRenderObject( BridgeTowerType type, RenderObjClass* renderObj )
{

	if( type >= 0 && type < BRIDGE_MAX_TOWERS )
		REF_PTR_SET( m_bridgeTowers[ type ], renderObj );

}
#pragma optimize("", on)

#pragma optimize("s", on)
RenderObjClass* MapObject::getBridgeRenderObject( BridgeTowerType type )
{

	if( type >= 0 && type < BRIDGE_MAX_TOWERS )
		return m_bridgeTowers[ type ];
	return NULL;

}
#pragma optimize("", on)

void MapObject::validate(void)
{
	verifyValidTeam();
	verifyValidUniqueID();
}

// MapObject::verifyValidTeam is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/MapObject_verifyValidTeamMethodThunk_Rva0030D6C7.cpp (0x0030D6C7).

// MapObject::verifyValidUniqueID is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/MapObject_verifyValidUniqueIDMethodThunk_Rva0030E0AA.cpp (0x0030E0AA).

// MapObject::fastAssignAllUniqueIDs is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/MapObject_fastAssignAllUniqueIDs_Rva0030E390.cpp (0x0030E390).
// Its std::stack<MapObject*> draft used to instantiate the deque node allocator
// rowed from this unit (0x0030E390's retail body uses a folded 4-byte deque); the
// member is kept emitted here explicitly.
template void std::_Deque_base<MapObject *, std::allocator<MapObject *> >::_M_create_nodes(MapObject ***, MapObject ***);







// MapObject::countMapObjectsWithOwner is recovered in WorldHeightMap_Rva0030e26f.cpp.

/* ********* WorldHeightMap class ****************************/

TileData *WorldHeightMap::m_alphaTiles[NUM_ALPHA_TILES]={0,0,0,0,0,0,0,0,0,0,0,0};

// BFME 2's WorldHeightMap constructors and destructor are rowed in
// WorldHeightMapCtors.cpp and Rva00B0028Dtor.cpp. The Zero Hour copies
// that stood here emitted a six-slot WorldHeightMap vtable where retail's
// (0x007C967C) has two, and kept those units from linking.



#ifdef EVAL_TILING_MODES
static Bool ParseFunkyTilingDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	WorldHeightMap *pThis = (WorldHeightMap *)userData;
	*((Int *)&pThis->m_tileMode) = file.readInt();
	return true;
}
#endif

/** Optimized version of method to get triangle flip state of a terrain cell.  Use this
*	instead of getAlphaUVData() whenever possible.
*/
// ?getFlipState@WorldHeightMap@@ present-unmatched
Bool WorldHeightMap::getFlipState(Int xIndex, Int yIndex) const
{
	if (xIndex<0 || yIndex<0) return false;
	if (yIndex>=m_height) return false;
	if (xIndex>=m_width) return false;
	if (!m_cellFlipState) return false;
	return m_cellFlipState[yIndex*m_flipStateWidth + (xIndex >> 3)] & (1<<(xIndex&0x7));
}

/** Sets the value of the flip state bit.
*/
// ?setFlipState@WorldHeightMap@@ present-unmatched
void WorldHeightMap::setFlipState(Int xIndex, Int yIndex, Bool value) 
{
	if (xIndex<0 || yIndex<0) return ;
	if (yIndex>=m_height) return ;
	if (xIndex>=m_width) return ;
	if (!m_cellFlipState) return ;
	UnsignedByte *curVal = &m_cellFlipState[yIndex*m_flipStateWidth + (xIndex >> 3)];
	if (value) {
		*curVal |= (1<<(xIndex&0x7));
	}	else {
		*curVal &= ~(1<<(xIndex&0x7));
	}
}

/** Clears all flip state bits.
*/




//////////////////////////////////////////////////////////////////////////////m_SeismicUpdateFlag

///////////////////////////////////////////////m_SeismicZVelocities

















/** Get whether the cell is a cliff cell (impassable to ground vehicles).
*/

//=============================================================================
// setCliffState
//=============================================================================
/** Sets the cliff state for a given cell. */
//=============================================================================


/**
* WorldHeightMap::ParseLightingDataChunk - read a global lights chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseObjectsDataChunk - read a height map chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseHeightMapData - read a height map chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseHeightMapData - read a height map chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseHeightMapData - read a height map chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseHeightMapData - read a height map chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseBlendTileDataChunk - read a blend tile info chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/
// WorldHeightMap::ParseBlendTileDataChunk has no located retail body: BFME 2 registers
// "BlendTileData" through a parser object (0x000AEFC8). The 19-byte forwarder at
// 0x002811CA once credited to it is TerrainLogic::parseWaypointDataChunk.

/** Function to read in the tiles for a texture class. */
// WorldHeightMap::readTexClass is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva000AF917Finish.cpp (0x000AF917).

/**
* WorldHeightMap::ParseBlendTileData - read a blend tile info chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/


/**
* WorldHeightMap::ParseObjectData - read a object info chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/

/**
* WorldHeightMap::ParseObjectData - read a object info chunk.
* Format is the newer CHUNKY format.
*	See WHeightMapEdit.cpp for the writer.
*	Input: DataChunkInput 
*		
*/



// Targa format:  Header

typedef struct {
	UnsignedByte	idLength;
	UnsignedByte	colorMapType; // 0 = rgb, 1 = indexed.
	UnsignedByte	imageType; //0x1 = indexed, 0x2 = rgb, 0x8 = rle.
	UnsignedByte	colorMapInfo[5]; // we ignore, only do rgb.
	Short			xOrigin;
	Short			yOrigin;
	Short			imageWidth;
	Short			imageHeight;
	UnsignedByte	pixelDepth;
	UnsignedByte	flags; //  &0x0F = alpha channel bits, &0x10 is right to left flag,
						   // 0x20 is top to bottom flag.  (0x0? is left to right, bottom to top)
						   // 0x3? is top to bottom, right to left.
} TTargaHeader;

// followed by idLength bytes of ascii data

// followed by pixel data

// followed by optional data.



/*Break down a .tga file into a collection of tiles.  numRows * numRows total tiles.*/



/** updateTileTexturePositions - assigns each tile a location in the texture.
*/

/** getUVData - Gets the texture coordinates to use.  See getTerrainTexture.
*/

/** getUVData - Gets the texture coordinates to use.  See getTerrainTexture.
*/

/// Get whether something is cliff indexed with the offset that HeightMapRenderObjClass uses built in.

/** getUVData - Gets the texture coordinates to use.  See getTerrainTexture.
		xIndex and yIndex are the integer coorddinates into the height map.
		U and V are the texture coordiantes for the 4 corners of a height map cell.
		fullTile is true if we are doing 1/2 resolution height map, and require a full
		tile to texture  a cell.  Otherwise, we use quarter tiles per cell.
*/

/** getUVForTileIndex - Gets the texture coordinates to use.  See getTerrainTexture.
		ndx is the index into the linear height array.
		tileNdx is the index into the texture tiles array.
		U and V are the texture coordiantes for the 4 corners of a height map cell.
		fullTile is true if we are doing 1/2 resolution height map, and require a full
		tile to texture  a cell.  Otherwise, we use quarter tiles per cell.
*/


///@todo: Are the different "if" cases mutually exclusive?  If so, should add else statements.

/** getUVData - Gets the texture coordinates to use with the alpha texture.  
		xIndex and yIndex are the integer coorddinates into the height map.
		U and V are the texture coordiantes for the 4 corners of a height map cell.
		fullTile is true if we are doing 1/2 resolution height map, and require a full
		tile to texture  a cell.  Otherwise, we use quarter tiles per cell.
		flip is set if we need to flip the diagonal across the cell to make the 
		alpha coordinates blend properly.  Filling a square with 2 triangles is not symmetrical :)
*/



	



// setDrawOrg (retail 0x000AC40D) is recovered against the BFME 2 layout in
// WorldHeightMapSetDrawOrg.cpp.

/** Gets global texture class. */


/** Sets all the cliff flags in map based on height. */

/** Sets the cliff flag for a cell based on height. */

/** Gets global texture class. */



// WorldHeightMap::getTerrainNameAt (0x000AEC4E) is rowed in WorldHeightMapGetTerrainNameAt.cpp; a second definition here would not link.	


// The ledger names this buffer _s_buffer (0x009E81C8); the six-argument
// getPointerToTileData in WorldHeightMapRva000AED2E.cpp shares it.
extern "C" { UnsignedByte s_buffer[DATA_LEN_BYTES]; }
static UnsignedByte s_blendBuffer[DATA_LEN_BYTES];


#define K_HORIZ 0
#define K_VERT 1
#define K_LDIAG 2
#define K_RDIAG 3
#define K_LLDIAG 4
#define K_LRDIAG 5
#define K_DIR_MOD 0x05
#define K_INV 6

#pragma optimize("s", on)
UnsignedByte *WorldHeightMap::getRGBAlphaDataForWidth(Int width, TBlendTileInfo *pBlend)
{
	Int alphaTileNdx = 0;
	if (pBlend->horiz) {
		alphaTileNdx = K_HORIZ;
	} else if (pBlend->vert) {
		alphaTileNdx = K_VERT;
	} else if (pBlend->rightDiagonal) {
		alphaTileNdx = K_RDIAG;
		if (pBlend->longDiagonal) alphaTileNdx=K_LRDIAG;
	} else if (pBlend->leftDiagonal) {
		alphaTileNdx = K_LDIAG; 
		if (pBlend->longDiagonal) alphaTileNdx=K_LLDIAG;
	}
	if (pBlend->inverted) {
		alphaTileNdx += K_INV;
	}
	return m_alphaTiles[alphaTileNdx]->getRGBDataForWidth(width);
}
// Native000ADDCE..000ADE29 RET12. BFME1 ba7ddda7e8
// WorldHeightMap.cpp supplies the blendTileData semantic lead; target adds
// the raw-tile mode argument. Existing TU buffers and alpha getter are reused.
// External helper declarations below are native call ABI views; original
// linkage spelling remains unknown. Raw loaderAC88E reads signed word arg8,
// four further words and ECX, RET20/AL. SetupAC6F9 RET0 ignores ECX. MMX
// blendAC63F reads four cdecl words, RET0, source/destination/alpha/count.
class Rva000ADDCEWorldHeightMapView
{
public:
 bool rawTile(Short tile,Int width,UnsignedByte *buffer,Int bytes,Int mode);
 void blendTile(TBlendTileInfo *blend,Int width,Int mode);
};
void __cdecl Rva000AC6F9SetupAlphaTiles();
void __cdecl Rva000AC63FBlendPixels(UnsignedByte *source,UnsignedByte *destination,UnsignedByte *alpha,Int pixels);
void Rva000ADDCEWorldHeightMapView::blendTile(TBlendTileInfo *blend,Int width,Int mode)
{
 if(rawTile(blend->blendNdx,width,s_blendBuffer,0x2000,mode)) {
  Rva000AC6F9SetupAlphaTiles();
  UnsignedByte *alpha=reinterpret_cast<WorldHeightMap *>(this)->getRGBAlphaDataForWidth(width,blend);
  if(alpha)Rva000AC63FBlendPixels(s_blendBuffer,s_buffer,alpha,width*width);
 }
}

#pragma optimize("", on)




