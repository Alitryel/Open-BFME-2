// Clean room: reverse/vp6_cleanroom/specs/001bd050.md 001bd550.md plus retail
// and code already in this repo only. No decoder source was consulted.
//
// LoadFrameHeader (retail 0x001BD050, 1279 bytes) reads a frame header into
// the decoder instance and VP6_LoadFrame (retail 0x001BD550, 28 bytes) is its
// cdecl entry point. LoadFrameHeader takes the instance in ESI, a private
// register convention MSVC gives a static function whose only caller shares
// its unit, so both bodies live here. Field offsets are the spec's.

struct Vp6HeaderReader;
struct PostProcInstance;

// Bool coder state (VP6_StartDecode/VP6_bitread/VP6_DecodeBool specs).
struct BoolCoder
{
	unsigned int m_lowValue;
	unsigned int m_range;
	unsigned int m_value;
	unsigned int m_count;
	unsigned int m_bytePosition;
	unsigned char *m_buffer;
	unsigned int m_measureCost;
	unsigned int m_bitCounter;
};

struct Quantizer
{
	unsigned int m_qIndex;									///< +0x00
	unsigned int m_qualityValue;							///< +0x04
	unsigned char m_unreconstructed08[0x3C - 0x08];
	unsigned int m_thresholdTable[64];						///< +0x3C
};

struct PbInstance
{
	unsigned char m_unreconstructed000[0x13C];
	Quantizer *m_quantizer;									///< +0x13C
	unsigned char m_unreconstructed140[0x150 - 0x140];
	BoolCoder m_primaryCoder;								///< +0x150
	unsigned char m_unreconstructed170[0x19C - 0x170];
	unsigned char m_version;								///< +0x19C
	unsigned char m_profile;								///< +0x19D
	unsigned char m_unreconstructed19E[0x1AC - 0x19E];
	unsigned char m_frameType;								///< +0x1AC
	unsigned char m_unreconstructed1AD[0x1B0 - 0x1AD];
	unsigned int m_frameWidth;								///< +0x1B0
	unsigned int m_frameHeight;								///< +0x1B4
	unsigned char m_unreconstructed1B8[0x1C8 - 0x1B8];
	unsigned int m_horizontalScale;							///< +0x1C8
	unsigned int m_horizontalRatio;							///< +0x1CC
	unsigned int m_verticalScale;							///< +0x1D0
	unsigned int m_verticalRatio;							///< +0x1D4
	unsigned int m_scalingMode;								///< +0x1D8
	unsigned int m_interlaced;								///< +0x1DC
	unsigned int m_expandedWidth;							///< +0x1E0
	unsigned int m_expandedHeight;							///< +0x1E4
	unsigned char m_unreconstructed1E8[0x1F4 - 0x1E8];
	unsigned int m_verticalFragments;						///< +0x1F4
	unsigned int m_horizontalFragments;						///< +0x1F8
	unsigned char m_unreconstructed1FC[0x234 - 0x1FC];
	unsigned int m_scaleWidth;								///< +0x234
	unsigned int m_scaleHeight;								///< +0x238
	unsigned int m_outputWidth;								///< +0x23C
	unsigned int m_outputHeight;							///< +0x240
	unsigned char m_unreconstructed244[0x264 - 0x244];
	unsigned char *m_scaleBuffer;							///< +0x264
	unsigned char m_unreconstructed268[0x298 - 0x268];
	PostProcInstance *m_postProc;							///< +0x298
	unsigned char m_unreconstructed29C[0x692 - 0x29C];
	unsigned char m_predictionFilterMode;					///< +0x692
	unsigned char m_mvSizeThreshold;						///< +0x693
	unsigned int m_varianceThreshold;						///< +0x694
	unsigned int m_refreshGolden;							///< +0x698
	unsigned char m_unreconstructed69C[0x944 - 0x69C];
	unsigned int m_multiStream;								///< +0x944
	unsigned char m_unreconstructed948[0x450C - 0x948];
	unsigned char *m_headerBuffer;							///< +0x450C, header reader's data
	unsigned char m_unreconstructed4510[0x451C - 0x4510];
	unsigned int m_secondPartitionOffset;					///< +0x451C
	unsigned int m_useHuffman;								///< +0x4520
	unsigned char m_unreconstructed4524[0x4534 - 0x4524];
	unsigned char m_loopFilterMode;							///< +0x4534
	unsigned char m_unreconstructed4535[0x4944 - 0x4535];
	unsigned int m_deInterlaceMode;							///< +0x4944
};

extern "C" unsigned int __cdecl ReadHeaderBits(Vp6HeaderReader *reader, unsigned int count);
// Both take a version byte; VP6_InitQTables ignores it.
extern "C" void __cdecl VP6_InitQTables(Quantizer *quantizer, unsigned char version);
extern "C" void __cdecl VP6_UpdateQ(Quantizer *quantizer, unsigned char version);
extern "C" void __cdecl VP6_StartDecode(BoolCoder *coder, unsigned char *source);
extern "C" void __cdecl SetPPInterlacedMode(PostProcInstance *postProc, int interlaced);
extern "C" void __cdecl SetDeInterlaceMode(PostProcInstance *postProc, int mode);
extern "C" int __cdecl VP6_bitread(BoolCoder *coder, int bits);
extern "C" int __cdecl VP6_InitFrameDetails(PbInstance *pbi);
extern "C" int __cdecl VP6_DecodeBool(BoolCoder *coder, int probability);
extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

// RVA 0x001BD050
static int LoadFrameHeader(PbInstance *pbi)
{
	Vp6HeaderReader *header = (Vp6HeaderReader *)&pbi->m_headerBuffer;
	pbi->m_frameType = (unsigned char)ReadHeaderBits(header, 1);
	unsigned char qIndex = (unsigned char)ReadHeaderBits(header, 6);
	pbi->m_multiStream = (unsigned char)ReadHeaderBits(header, 1);
	BoolCoder *coder;

	if (!pbi->m_frameType)
	{
		pbi->m_version = (unsigned char)ReadHeaderBits(header, 5);
		pbi->m_profile = (unsigned char)ReadHeaderBits(header, 2);
		if (pbi->m_version > 7)
			return 0;

		VP6_InitQTables(pbi->m_quantizer, pbi->m_version);
		pbi->m_interlaced = (unsigned char)ReadHeaderBits(header, 1);

		if (!pbi->m_multiStream && pbi->m_profile)
		{
			coder = &pbi->m_primaryCoder;
			VP6_StartDecode(coder, pbi->m_headerBuffer + 2);
		}
		else
		{
			coder = &pbi->m_primaryCoder;
			VP6_StartDecode(coder, pbi->m_headerBuffer + 4);
			pbi->m_secondPartitionOffset = ReadHeaderBits(header, 16);
		}

		SetPPInterlacedMode(pbi->m_postProc, pbi->m_interlaced);
		if (pbi->m_interlaced)
			SetDeInterlaceMode(pbi->m_postProc, pbi->m_deInterlaceMode);

		unsigned int verticalFragments = (unsigned char)VP6_bitread(coder, 8) * 2u;
		unsigned int horizontalFragments = (unsigned char)VP6_bitread(coder, 8) * 2u;
		unsigned int outputVertical = (unsigned char)VP6_bitread(coder, 8) * 2u;
		unsigned int outputHorizontal = (unsigned char)VP6_bitread(coder, 8) * 2u;

		if (!pbi->m_horizontalRatio)
			pbi->m_horizontalRatio = 1;
		if (!pbi->m_verticalRatio)
			pbi->m_verticalRatio = 1;

		unsigned int oldWidth = pbi->m_horizontalFragments * pbi->m_horizontalScale * 8 / pbi->m_horizontalRatio;
		unsigned int oldHeight = pbi->m_verticalScale * pbi->m_verticalFragments * 8 / pbi->m_verticalRatio;
		pbi->m_expandedWidth = outputHorizontal * 8;
		pbi->m_expandedHeight = outputVertical * 8;

		if (verticalFragments >= outputVertical) { pbi->m_verticalScale = 1; pbi->m_verticalRatio = 1; }
		else if (verticalFragments * 5 >= outputVertical * 4) { pbi->m_verticalScale = 5; pbi->m_verticalRatio = 4; }
		else if (verticalFragments * 5 >= outputVertical * 3) { pbi->m_verticalScale = 5; pbi->m_verticalRatio = 3; }
		else { pbi->m_verticalScale = 2; pbi->m_verticalRatio = 1; }

		if (horizontalFragments >= outputHorizontal) { pbi->m_horizontalScale = 1; pbi->m_horizontalRatio = 1; }
		else if (horizontalFragments * 5 >= outputHorizontal * 4) { pbi->m_horizontalScale = 5; pbi->m_horizontalRatio = 4; }
		else if (horizontalFragments * 5 >= outputHorizontal * 3) { pbi->m_horizontalScale = 5; pbi->m_horizontalRatio = 3; }
		else { pbi->m_horizontalScale = 2; pbi->m_horizontalRatio = 1; }

		unsigned int newWidth = pbi->m_horizontalScale * horizontalFragments * 8 / pbi->m_horizontalRatio;
		unsigned int newHeight = pbi->m_verticalScale * verticalFragments * 8 / pbi->m_verticalRatio;
		pbi->m_scaleWidth = newWidth;
		pbi->m_scaleHeight = newHeight;
		pbi->m_scalingMode = VP6_bitread(coder, 2);

		if (verticalFragments != pbi->m_verticalFragments || horizontalFragments != pbi->m_horizontalFragments)
		{
			pbi->m_frameWidth = horizontalFragments * 8;
			pbi->m_frameHeight = verticalFragments * 8;
			VP6_InitFrameDetails(pbi);
		}

		if (pbi->m_scaleBuffer && (oldWidth != newWidth || oldHeight != newHeight))
		{
			memset(pbi->m_scaleBuffer, 0, (pbi->m_outputHeight + 32) * (pbi->m_outputWidth + 32));
			unsigned int lumaBytes = (pbi->m_outputHeight + 32) * (pbi->m_outputWidth + 32);
			memset(pbi->m_scaleBuffer + lumaBytes, 0x80, lumaBytes / 2);
		}

		if (pbi->m_profile)
		{
			if (VP6_DecodeBool(coder, 128))
			{
				pbi->m_predictionFilterMode = 2;
				pbi->m_varianceThreshold = VP6_bitread(coder, 5) << 5;
				pbi->m_mvSizeThreshold = (unsigned char)VP6_bitread(coder, 3);
			}
			else
				pbi->m_predictionFilterMode = VP6_DecodeBool(coder, 128) != 0;
		}
	}
	else
	{
		if (!pbi->m_multiStream && pbi->m_profile)
		{
			coder = &pbi->m_primaryCoder;
			VP6_StartDecode(coder, pbi->m_headerBuffer + 1);
		}
		else
		{
			coder = &pbi->m_primaryCoder;
			VP6_StartDecode(coder, pbi->m_headerBuffer + 3);
			pbi->m_secondPartitionOffset = ReadHeaderBits(header, 16);
		}

		pbi->m_refreshGolden = VP6_DecodeBool(coder, 128);
		if (pbi->m_profile)
		{
			pbi->m_loopFilterMode = (unsigned char)VP6_DecodeBool(coder, 128);
			if (pbi->m_loopFilterMode)
				pbi->m_loopFilterMode = (unsigned char)VP6_DecodeBool(coder, 128) | (pbi->m_loopFilterMode << 1);
		}
	}

	pbi->m_useHuffman = VP6_DecodeBool(coder, 128);
	pbi->m_quantizer->m_qIndex = qIndex;
	Quantizer *quantizer = pbi->m_quantizer;
	quantizer->m_qualityValue = quantizer->m_thresholdTable[qIndex];
	VP6_UpdateQ(pbi->m_quantizer, pbi->m_version);
	return 1;
}

// RVA 0x001BD550: 1 when the header loaded, else 0 (retail keeps the 1 in EDI).
extern "C" int __cdecl VP6_LoadFrame(PbInstance *pbi)
{
	int result = 1;
	if (!LoadFrameHeader(pbi))
		result = 0;
	return result;
}
