// cl: /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// AdaptiveDeltaMotionChannelClass::getframe<4>, retail 0x0018FCC0 (194 bytes),
// split out of hcanim.cpp with hcanim.cpp's flags and template. It is the only
// caller of decompress<4> (retail 0x0018F9C0, 222 bytes), whose instantiation
// lives here too; compiled in hcanim.cpp that COMDAT kept the whole unit from
// linking. hcanim.cpp declares the specialization and calls it here.
#include <string.h>

typedef unsigned long uint32;

extern float bfme2AdaptiveDeltaFilterTable[256];

template <int N> struct AdaptiveDeltaCacheStruct
{
	uint32	Frame;
	float		Value[2 * N];
};

// The 0x1C-byte channel of hcanim.cpp, only the members these bodies read.
class AdaptiveDeltaMotionChannelClass
{
private:

	enum { PACKET_SIZE = 9 };

	uint32	PivotIdx;
	uint32	Type;
	int		VectorLen;
	uint32	NumFrames;
	uint32	DataByteCount;
	float		Scale;
	uint32  *Data;

	template <int N> void getframe(uint32 frame_idx, AdaptiveDeltaCacheStruct<N> & cache);
	template <int N> void decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata);
};

// ??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z
// The packet cursor is taken from base only on the decoding path: declaring
// it at the top of the vector loop keeps base and the cursor in separate
// webs, and the register colouring of the whole head changes with it.
template <int N>
void AdaptiveDeltaMotionChannelClass::decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata)
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

	base += sizeof(float) * N;										// skip non-compressed header information
	base += (PACKET_SIZE * N) * (start >> 4);					// skip out to current packet

	for (int vi = 0; vi < N; vi++) {
		float last_value = src[vi];
		if (start < frame_idx) {
			unsigned char *pPacket = base;
			int fi = start & 0xF;
			uint32 frame = start;
			do {
			uint32 filter_index = *pPacket;
			pPacket++;
			float filter = bfme2AdaptiveDeltaFilterTable[filter_index] * Scale;	// decompression filter

			// data is grouped in sets of 16 nybbles
			do {
				int factor = pPacket[fi >> 1] << 24;
				if ((fi & 1) == 0) {
					factor <<= 4;
				}
				factor >>= 28;									// sign-extended nybble, -8 to +7

				last_value += factor * filter;

				frame++;
				if (frame >= frame_idx) break;
				fi++;
			} while (fi < 16);

			fi = 0;
			pPacket += (PACKET_SIZE * N) - 1;					// skip to next packet
			} while (frame < frame_idx);
		}

		outdata[vi] = last_value;
		base += PACKET_SIZE;
	}
}

// ??$getframe@$03@AdaptiveDeltaMotionChannelClass@@AAEXKAAU?$AdaptiveDeltaCacheStruct@$03@@@Z
template <int N>
void AdaptiveDeltaMotionChannelClass::getframe(uint32 frame_idx, AdaptiveDeltaCacheStruct<N> & cache)
{
	if (VectorLen != N) {
		memset(cache.Value, 0, sizeof(cache.Value));
		return;
	}

	if (frame_idx >= NumFrames) frame_idx = NumFrames - 1;

	if (cache.Frame + 1 == frame_idx) {
		// Sliding window
		cache.Frame++;
		memcpy(&cache.Value[0], &cache.Value[N], N * sizeof(float));
		decompress<N>(frame_idx, &cache.Value[0], frame_idx + 1, &cache.Value[N]);
		return;
	}

	if (frame_idx == cache.Frame) return;

	if (frame_idx < cache.Frame) {
		cache.Frame = frame_idx;
		decompress<N>(0, NULL, frame_idx, &cache.Value[0]);
	} else {
		decompress<N>(cache.Frame + 1, &cache.Value[N], frame_idx, &cache.Value[0]);
		cache.Frame = frame_idx;
	}

	decompress<N>(frame_idx, &cache.Value[0], frame_idx + 1, &cache.Value[N]);
}

template void AdaptiveDeltaMotionChannelClass::getframe<4>(uint32, AdaptiveDeltaCacheStruct<4> &);
