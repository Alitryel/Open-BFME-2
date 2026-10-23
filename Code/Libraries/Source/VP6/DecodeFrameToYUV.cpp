// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001b60e0.md and 001b62c0.md plus
// retail only. No decoder source was consulted. Field names are descriptive
// labels from the spec text.
//
//   0x001B60E0 477 bytes  frame decode body; static here so MSVC passes the
//                         compressed buffer pointer in EAX. The spec gives it
//                         no identity of its own beyond "the optimised body of
//                         VP6_DecodeFrameToYUV", so it keeps an address name.
//   0x001B62C0  23 bytes  VP6_DecodeFrameToYUV, the public cdecl entry.
#include <stdio.h>

struct HeaderReader;
struct BOOL_CODER;
struct PostProcessor;
struct PB_INSTANCE;

extern "C" void __cdecl VP6_readTSC(unsigned int *result);						// 0x001B8E70
extern "C" void __cdecl InitHeaderBuffer(HeaderReader *reader, const unsigned char *data);	// 0x001BCF80
extern "C" int __cdecl VP6_LoadFrame(PB_INSTANCE *pbi);							// 0x001BD550
extern "C" void __cdecl VP6_StartDecode(BOOL_CODER *coder, unsigned char *source);	// 0x001BCEE0
extern "C" void VP6_DecodeFrameMbs(PB_INSTANCE *pbi);								// 0x001BC9C0
extern "C" void __cdecl UpdateUMVBorder(void);													// 0x001B96A0 UpdateUMVBorder
typedef void (__cdecl *UpdateUMVBorderFn)(PostProcessor *post, unsigned char *frame);
#define UpdateUMVBorder ((UpdateUMVBorderFn)&UpdateUMVBorder)

// The system-state clear routine pointer at VA 0x00E22D10.
extern void *g_bfmeSlotB48;
typedef void (__cdecl *ClearSysStateFn)();

// Global decoded-frame counter (VA 0x00DFDA50, zero-filled .bss).
int g_vp6FrameCounter;

extern "C" void *__cdecl memcpy(void *dest, const void *source, unsigned int count);
#pragma intrinsic(memcpy)

struct QUANTIZER
{
	unsigned int frameQIndex;			// +0x00
};

struct PB_INSTANCE
{
	unsigned char pad000[0x13C];
	QUANTIZER *quantizer;				// +0x13C
	unsigned char pad140[0x160 - 0x140];
	unsigned int boolBytePosition;		// +0x160 primary bool decoder position
	unsigned char pad164[0x170 - 0x164];
	unsigned char secondBoolCoder[0x190 - 0x170];	// +0x170
	unsigned int rawBitsInRemainder;	// +0x190
	unsigned int rawRemainder;			// +0x194
	unsigned char *rawPosition;			// +0x198
	unsigned char pad19C;
	unsigned char profile;				// +0x19D
	unsigned char pad19E[0x1A4 - 0x19E];
	unsigned int processorFrequency;	// +0x1A4
	unsigned char pad1A8[0x1AC - 0x1A8];
	unsigned char frameType;			// +0x1AC
	unsigned char pad1AD[0x1E8 - 0x1AD];
	unsigned int frameSize;				// +0x1E8
	unsigned char pad1EC[0x208 - 0x1EC];
	unsigned int reconYPlaneSize;		// +0x208
	unsigned int reconUVPlaneSize;		// +0x20C
	unsigned char pad210[0x244 - 0x210];
	unsigned char *thisFrameRecon;		// +0x244
	unsigned char pad248[0x24C - 0x248];
	unsigned char *goldenFrame;			// +0x24C
	unsigned char pad250[0x254 - 0x250];
	unsigned char *lastFrameRecon;		// +0x254
	unsigned char pad258[0x298 - 0x258];
	PostProcessor *postProcessor;		// +0x298
	unsigned char pad29C[0x698 - 0x29C];
	unsigned int refreshGoldenFrame;	// +0x698
	unsigned char pad69C[0x6A0 - 0x69C];
	unsigned int averageFrameQ;			// +0x6A0
	unsigned char pad6A4[0x910 - 0x6A4];
	unsigned int thisDecodeTime;		// +0x910
	unsigned int averageDecodeTime;		// +0x914
	unsigned char pad918[0x944 - 0x918];
	unsigned int multiStream;			// +0x944
	unsigned char pad948[0x450C - 0x948];
	unsigned char frameHeader[0x451C - 0x450C];	// +0x450C
	unsigned int secondPartitionOffset;	// +0x451C
	unsigned int useHuffman;			// +0x4520
};

// RVA 0x001B60E0
static int Rva001B60E0DecodeFrameToYUV(PB_INSTANCE *pbi, unsigned char *buffer, unsigned int byteCount)
{
	unsigned int startTime;
	unsigned int endTime;
	unsigned int duration;
	unsigned char *swap;

	VP6_readTSC(&startTime);
	pbi->frameSize = byteCount;
	InitHeaderBuffer((HeaderReader *)pbi->frameHeader, buffer);
	if (!VP6_LoadFrame(pbi))
		return -1;

	if (pbi->multiStream || pbi->profile == 0)
	{
		if (pbi->useHuffman)
		{
			pbi->rawBitsInRemainder = 0;
			pbi->rawRemainder = 0;
			pbi->rawPosition = buffer + pbi->secondPartitionOffset;
		}
		else
			VP6_StartDecode((BOOL_CODER *)pbi->secondBoolCoder, buffer + pbi->secondPartitionOffset);
	}

	VP6_DecodeFrameMbs(pbi);

	swap = pbi->lastFrameRecon;
	pbi->lastFrameRecon = pbi->thisFrameRecon;
	pbi->thisFrameRecon = swap;
	UpdateUMVBorder(pbi->postProcessor, pbi->lastFrameRecon);

	if (pbi->frameType == 0 || pbi->refreshGoldenFrame)
		memcpy(pbi->goldenFrame, pbi->lastFrameRecon, pbi->reconYPlaneSize + 2 * pbi->reconUVPlaneSize);

	((ClearSysStateFn)g_bfmeSlotB48)();

	if (pbi->frameType == 0)
		pbi->averageFrameQ = pbi->quantizer->frameQIndex;
	else
		pbi->averageFrameQ = (3 * pbi->averageFrameQ + pbi->quantizer->frameQIndex + 2) >> 2;

	VP6_readTSC(&endTime);
	duration = (endTime - startTime) / pbi->processorFrequency;
	pbi->thisDecodeTime = duration;
	if (pbi->averageDecodeTime == 0)
		pbi->averageDecodeTime = duration;
	else
		pbi->averageDecodeTime = (7 * pbi->averageDecodeTime + duration) >> 3;

	if (pbi->boolBytePosition > pbi->frameSize)
	{
		FILE *f = fopen("badframes.stt", "a");
		fprintf(f, "%8d %8d %8d \n", g_vp6FrameCounter, pbi->boolBytePosition, pbi->frameSize);
		fclose(f);
	}

	++g_vp6FrameCounter;
	return 0;
}

// RVA 0x001B62C0
extern "C" int __cdecl VP6_DecodeFrameToYUV(PB_INSTANCE *pbi, unsigned char *buffer, unsigned int byteCount)
{
	return Rva001B60E0DecodeFrameToYUV(pbi, buffer, byteCount);
}
