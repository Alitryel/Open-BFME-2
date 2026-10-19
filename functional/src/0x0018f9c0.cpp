// ??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z
// partial score=0.733 date=2026-10-17
// ??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z
// partial score=0.8378 date=2026-10-14
// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmehcanim /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
// Native Hashable ctor EF9C2 is the 13B size copy; the /O2 default emits
// a conflicting 16B provider. Use this existing scope for the base header.
#include "hash.h"
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4
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

/* $Header: /Commando/Code/ww3d2/hcanim.cpp 3     6/29/01 6:41p Jani_p $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hcanim.cpp                             $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 6/27/01 7:50p                                               $* 
 *                                                                                             * 
 *                    $Revision:: 3                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   NodeMotionStruct::NodeMotionStruct -- constructor                                         *
 *   NodeMotionStruct::~NodeMotionStruct -- destructor                                         *
 *   HCompressedAnimClass::HCompressedAnimClass -- constructor                                 * 
 *   HCompressedAnimClass::~HCompressedAnimClass -- Destructor                                 * 
 *   HCompressedAnimClass::Free -- De-allocates all memory in use                              * 
 *   HCompressedAnimClass::Load -- Loads hierarchy animation from a file                       * 
 *   HCompressedAnimClass::read_channel -- Reads in a single channel of motion                 * 
 *   HCompressedAnimClass::add_channel -- Adds a motion channel to the animation               * 
 *   HCompressedAnimClass::Get_Translation -- returns the translation vector for the given fram* 
 *   HCompressedAnimClass::Get_Orientation -- returns a quaternion for the orientation of the p* 
 *   HCompressedAnimClass::read_bit_channel -- read a bit channel from the file                *
 *   HCompressedAnimClass::add_bit_channel -- install a bit channel into the animation         *
 *   HCompressedAnimClass::Get_Visibility -- return visibility state for given pivot/frame     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "hcanim.h"
#include "assetmgr.h"

// BFME reaches the hierarchy through a free function, as HRawAnimClass::Load_W3D
// does -- cdecl, one argument, caller cleans -- rather than through the asset
// manager singleton. The body lives in another translation unit.
HTreeClass *Get_HTree(const char *name);

// The compressed-animation constructor and loader both ask the retail name
// key singleton to assign a key to the fully-qualified animation name.  The
// complete NameKeyGenerator header is intentionally not pulled into this
// WW3D2 unit: this small declaration preserves the proven ABI and keeps the
// animation include boundary local.
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// BFME2's loader uppercases the qualified name with the imported toupper
// (0x00BBA5B4) before keying it, as HRawAnimClass::Load_W3D does.
extern "C" __declspec(dllimport) int __cdecl toupper(int);

// The Debug manager (theDebug, 0x00DE0880) that BFME2's missing-bone report
// streams through. The reference Debug class is not virtual, so this view
// carries the retail slots; only the slots called here are named.
class HCompressedAnimDebug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual HCompressedAnimDebug &operator<<(const char *text);
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void CrashDone(int mode);
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void SkipNext();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual HCompressedAnimDebug &CrashBegin(const char *file, int line, const char *group);
};
extern Debug *theDebug;
#define TheHCompressedAnimDebug (*(HCompressedAnimDebug **)&theDebug)

// 0x000387C0: reads the Debug singleton's report-enabled flag; 0x00038790
// records the report's call site (Debug::SkipNext(true)).
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

#include "htree.h"
// BFME2's TimeCodedMotionChannelClass is stateless: the search cache moved out
// to the caller, which passes it by reference (retail 0x0018EC60 reads and
// writes it through its second argument), and +0x14 is the last packet index
// that the binary search falls back to. motchan.h still describes BFME1's
// cached class, so it is renamed out of the way and redeclared below. The
// adaptive-delta channel lost its cache the same way.
#define TimeCodedMotionChannelClass BfmeOneTimeCodedMotionChannelClass
#define AdaptiveDeltaMotionChannelClass BfmeOneAdaptiveDeltaMotionChannelClass
#include "motchan.h"
#undef AdaptiveDeltaMotionChannelClass
#undef TimeCodedMotionChannelClass
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"


// The normalized quaternion lerp at 0x00717550 (ledger
// ?BFME2_Nlerp@@YAXAAVQuaternion@@ABV1@1M@Z) that BFME2 blends with where Zero
// Hour calls Fast_Slerp.
void BFME2_Nlerp(Quaternion &result, const Quaternion &p, const Quaternion &q, float alpha);

class TimeCodedMotionChannelClass : public W3DMPO
{
public:

	TimeCodedMotionChannelClass(void);
	~TimeCodedMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);
	Quaternion Get_QuatVector(float32 frame);
	void	Get_Vector(float32 frame, float * setvec, uint32 & cachedIdx);
	void	Get_QuatVector(float32 frame, Quaternion & q, uint32 & cachedIdx);

	int		Get_Channel_Memory_Usage(void);

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	uint32	PacketSize;			// size of each packet
	uint32	NumTimeCodes;		// Number of packets
	uint32	LastTimeCodeIdx;	// absolute index to last time code
	uint32 *	Data;					// pointer to packet data

	void 		Free(void);
	uint32	get_index(uint32 timecode, uint32 & cachedIdx);

	friend class HCompressedAnimClass;
};

/***********************************************************************************************
 * TimeCodedMotionChannelClass::get_index -- returns packet index                             *
 *                                                                                             *
 * BFME2 (retail 0x0018EC60): the caller owns the cache. The look-ahead only runs while two   *
 * more packets fit before the last one, and the binary search is folded in.                  *
 *=============================================================================================*/
WWINLINE uint32 TimeCodedMotionChannelClass::get_index(uint32 timecode, uint32 & cachedIdx)
{
	uint32 idx = cachedIdx;

	if (idx + PacketSize * 2 <= LastTimeCodeIdx) {
		uint32 * packet = &Data[idx];
		if (timecode >= (packet[0] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
			if (timecode < (packet[PacketSize] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
				return idx;
			}
			if (timecode < (packet[PacketSize * 2] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
				cachedIdx = idx + PacketSize;
				return cachedIdx;
			}
		}
	}

	// special case last packet
	if (timecode >= (Data[LastTimeCodeIdx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
		cachedIdx = LastTimeCodeIdx;
		return LastTimeCodeIdx;
	}

	int leftIdx = 0;
	int rightIdx = NumTimeCodes - 2;

	for (;;) {
		int dx = (leftIdx + rightIdx) / 2;
		uint32 * packet = &Data[dx * PacketSize];

		if (timecode < (packet[0] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
			rightIdx = dx;
			continue;
		}

		if (timecode < (packet[PacketSize] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
			cachedIdx = packet - Data;
			return cachedIdx;
		}

		if (leftIdx ^ dx) {
			leftIdx = dx;
			continue;
		}

		leftIdx++;
	}
}

/***********************************************************************************************
 * TimeCodedMotionChannelClass::Get_Vector -- returns the value for the specified frame #     *
 *                                                                                             *
 * BFME2 (retail 0x0018ED50): one float per packet, and the search cache comes from the      *
 * caller. Retail inlines it into every caller (nothing calls the copy at 0x0018ED50).         *
 *=============================================================================================*/
WWINLINE void	TimeCodedMotionChannelClass::Get_Vector(float32 frame, float * setvec, uint32 & cachedIdx)
{
	uint32 tc0 = frame;

	uint32 pidx = get_index(tc0, cachedIdx);
	uint32 p2idx;

	if (pidx == ((NumTimeCodes - 1) * PacketSize)) {
		*setvec = *(float32 *)&Data[pidx+1];
		return;
	} else {
		p2idx = pidx + PacketSize;
	}

	uint32 time = Data[p2idx];

	if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG) {
		*setvec = *(float32 *)&Data[pidx+1];
		return;
	}

	float32 time1 = (Data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 time2 = (time & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);

	float32 ratio = (frame - time1) / (time2 - time1);

	float32 *frame1 = (float32 *) &Data[pidx+1];
	float32 *frame2 = (float32 *) &Data[p2idx+1];

	*setvec = WWMath::Lerp(frame1[0],frame2[0],ratio);
}

/***********************************************************************************************
 * TimeCodedMotionChannelClass::Get_QuatVector -- returns the orientation for the frame #     *
 *                                                                                             *
 * BFME2 (retail 0x0018EEF0): writes through the caller's quaternion and blends with the      *
 * normalized lerp at 0x00717550 instead of returning a Fast_Slerp result.                    *
 *=============================================================================================*/
WWINLINE void TimeCodedMotionChannelClass::Get_QuatVector(float32 frame, Quaternion & q, uint32 & cachedIdx)
{
	float32 * packets = (float32 *) Data;
	uint32 tc0 = frame;

	uint32 pidx = get_index(tc0, cachedIdx);
	uint32 p2idx;

	if (pidx == LastTimeCodeIdx) {
		float32 *vec = &packets[pidx+1];
		q.Set(vec[0], vec[1], vec[2], vec[3]);
		return;
	} else {
		p2idx = pidx + PacketSize;
	}

	uint32 time = Data[p2idx];

	if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG) {
		// its a binary movement!
		float32 *vec = &packets[pidx+1];
		q.Set(vec[0], vec[1], vec[2], vec[3]);
		return;
	}

	// The next timecode never carries the flag here, so retail converts it unmasked.
	float32 time1 = (Data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 ratio = (frame - time1) / ((float32)time - time1);

	BFME2_Nlerp(q, *(Quaternion *)&packets[pidx+1], *(Quaternion *)&packets[p2idx+1], ratio);
}

// The adaptive-delta filter table, owned by AdaptiveDeltaMotionChannelFinish.cpp
// (retail 0x00DB67D8).
extern float bfme2AdaptiveDeltaFilterTable[256];

// Decoded values for two consecutive frames of an N-float adaptive-delta
// channel. The caller owns it and starts Frame at 0x0FFFFFFF, an index no
// channel reaches. Descriptive name: retail only shows the 4 + 2*N*4 byte layout.
template <int N> struct AdaptiveDeltaCacheStruct
{
	uint32	Frame;
	float		Value[2 * N];
};

/*
** BFME2's AdaptiveDeltaMotionChannelClass (0x1C bytes, see the matched
** constructor at 0x00195F60). Retail compiles each sampler once per vector
** length: the scalar copies have no vector loop and 9-byte packet strides, the
** quaternion copies count four vectors over 36-byte strides. That is a
** compile-time length, so the bodies below are templates on it.
*/
class AdaptiveDeltaMotionChannelClass : public W3DMPO
{
public:

	AdaptiveDeltaMotionChannelClass(void);
	~AdaptiveDeltaMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);
	Quaternion Get_QuatVector(float32 frame);
	void	Get_Vector(float32 frame, float * setvec, AdaptiveDeltaCacheStruct<1> & cache);
	void	Get_QuatVector(float32 frame, Quaternion & q, AdaptiveDeltaCacheStruct<4> & cache);

	int		Get_Channel_Memory_Usage(void);

private:

	enum { PACKET_SIZE = 9 };

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	uint32	NumFrames;			// Number of frames
	uint32	DataByteCount;
	float		Scale;				// Scale Filter, this much
	uint32  *Data;				 	// pointer to packet data

	void 		Free(void);

	template <int N> void getframe(uint32 frame_idx, AdaptiveDeltaCacheStruct<N> & cache);
	template <int N> void decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata);

	friend class HCompressedAnimClass;
};

/***********************************************************************************************
 * AdaptiveDeltaMotionChannelClass::decompress -- decode N floats up to frame_idx             *
 *                                                                                             *
 * BFME2 (retail 0x0018F910 for one float, 0x0018F9C0 for four): continues from src_idx and   *
 * srcdata, or from the uncompressed header when srcdata is NULL. Nothing is decoded for a     *
 * frame past the end, so the source values are passed through.                               *
 *=============================================================================================*/
// ??$decompress@$00@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z

extern float filtertable[256];

template <>
void AdaptiveDeltaMotionChannelClass::decompress<4>(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata)
{
	unsigned char *base = (unsigned char *) Data;
	float *src = srcdata;
	uint32 start;

	if (srcdata == NULL) {
		start = 0;
		src = (float *) Data;
		base = (unsigned char *) Data;
	} else {
		start = src_idx;
	}

	if (frame_idx >= NumFrames) {
		start = frame_idx;
	}

	base += sizeof(float) * 4;
	base += (PACKET_SIZE * 4) * (start >> 4);

	for (int vi = 0; vi < 4; vi++) {
		unsigned char *pPacket = base + PACKET_SIZE * vi;
		float last_value = src[vi];
		if (start < frame_idx) {
			int fi = start & 0xF;
			uint32 frame = start;
			do {
			float filter = filtertable[*pPacket] * Scale;
			pPacket++;
			do {
				int factor = pPacket[fi >> 1] << 24;
				if ((fi & 1) == 0) {
					factor <<= 4;
				}
				factor >>= 28;
				last_value += factor * filter;
				frame++;
				if (frame >= frame_idx) break;
				fi++;
			} while (fi < 16);
			fi = 0;
			pPacket += (PACKET_SIZE * 4) - 1;
			} while (frame < frame_idx);
		}
		outdata[vi] = last_value;
	}
}
