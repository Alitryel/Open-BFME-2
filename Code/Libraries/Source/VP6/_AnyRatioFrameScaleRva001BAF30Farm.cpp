// _AnyRatioFrameScale
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001baca0.md plus retail only.
// No decoder source was consulted.
//
// AnyRatio_2D_Scale (retail 0x001BACA0, 644 bytes): cdecl 2-D scaler for the
// 4/5 and 3/5 and 2/1 ratios selected from the context scale and ratio
// fields (returns zero for any other pair). Horizontal and vertical pass
// callbacks come from the codec scale slots (defined here; the direct copy
// callback is HorizontalLine_Copy and the empty vertical callback is the
// plain ret at VA 0x009A91C0). The body is carried from the byte-identical
// Open-BFME-1 project donor.

struct Rva009AA260Context
{
	unsigned char m_pad00[0x58];
	int m_hscale;
	int m_hratio;
	int m_vscale;
	int m_vratio;
};

typedef void (__cdecl *Rva009AA260HorizontalScale)(
	const unsigned char *, unsigned int, unsigned char *, unsigned int);
typedef void (__cdecl *Rva009AA260VerticalScale)(
	unsigned char *, unsigned int, unsigned int);

extern "C" void __cdecl HorizontalLine_Copy(const void *, unsigned int, void *, unsigned int);

// BFME2 image-scale callback slots (.data). DIR32-masked so the gate does not
// read their addresses. Names describe ratio family and pass direction.
extern Rva009AA260HorizontalScale g_horizontalScale45Slot;
extern Rva009AA260HorizontalScale g_horizontalScale35Slot;
extern Rva009AA260HorizontalScale g_horizontalScale21Slot;
extern Rva009AA260VerticalScale g_verticalScale45Slot;
extern Rva009AA260VerticalScale g_verticalScale35Slot;
extern Rva009AA260VerticalScale g_verticalScale21Slot;
extern Rva009AA260VerticalScale g_lastVerticalScale45Slot;
extern Rva009AA260VerticalScale g_lastVerticalScale35Slot;
extern Rva009AA260VerticalScale g_lastVerticalScale21Slot;

// Matched DIR32 references place these mutable callback slots in .data's
// zero-filled tail; preserve their null retail initial values.
// g_horizontalScale45Slot: VA 0x00E22F78.
Rva009AA260HorizontalScale g_horizontalScale45Slot;
// g_verticalScale21Slot: VA 0x00E22F8C.
Rva009AA260VerticalScale g_verticalScale21Slot;
// g_lastVerticalScale45Slot: VA 0x00E22F94.
Rva009AA260VerticalScale g_lastVerticalScale45Slot;
// g_verticalScale45Slot: VA 0x00E22F98.
Rva009AA260VerticalScale g_verticalScale45Slot;
// g_horizontalScale21Slot: VA 0x00E22F9C.
Rva009AA260HorizontalScale g_horizontalScale21Slot;
// g_lastVerticalScale35Slot: VA 0x00E22FAC.
Rva009AA260VerticalScale g_lastVerticalScale35Slot;
// g_lastVerticalScale21Slot: VA 0x00E22FC0.
Rva009AA260VerticalScale g_lastVerticalScale21Slot;
// g_verticalScale35Slot: VA 0x00E22FC4.
Rva009AA260VerticalScale g_verticalScale35Slot;
// g_horizontalScale35Slot: VA 0x00E22FCC.
Rva009AA260HorizontalScale g_horizontalScale35Slot;

static void __cdecl Rva009A91C0NullScale(
	unsigned char *, unsigned int, unsigned int)
{
}

static Rva009AA260HorizontalScale rva009AA260Horizontal45(void)
{
	return g_horizontalScale45Slot;
}

static Rva009AA260HorizontalScale rva009AA260Horizontal35(void)
{
	return g_horizontalScale35Slot;
}

static Rva009AA260HorizontalScale rva009AA260Horizontal21(void)
{
	return g_horizontalScale21Slot;
}

static Rva009AA260VerticalScale rva009AA260Vertical45(void)
{
	return g_verticalScale45Slot;
}

static Rva009AA260VerticalScale rva009AA260Vertical35(void)
{
	return g_verticalScale35Slot;
}

static Rva009AA260VerticalScale rva009AA260Vertical21(void)
{
	return g_verticalScale21Slot;
}

static Rva009AA260VerticalScale rva009AA260LastVertical45(void)
{
	return g_lastVerticalScale45Slot;
}

static Rva009AA260VerticalScale rva009AA260LastVertical35(void)
{
	return g_lastVerticalScale35Slot;
}

static Rva009AA260VerticalScale rva009AA260LastVertical21(void)
{
	return g_lastVerticalScale21Slot;
}

extern "C" int __cdecl AnyRatio_2D_Scale(
	Rva009AA260Context *context,
	const unsigned char *source,
	int source_pitch,
	unsigned int source_width,
	unsigned int source_height,
	unsigned char *dest,
	unsigned int dest_pitch,
	unsigned int dest_width,
	unsigned int dest_height)
{
	unsigned int i;
	unsigned int k;
	unsigned int source_band_height = 0;
	unsigned int dest_band_height = 0;

	int hscale = context->m_hscale;
	int hratio = context->m_hratio;
	int vscale = context->m_vscale;
	int vratio = context->m_vratio;
	int ratio_scalable = 1;

	Rva009AA260HorizontalScale horizontal_scale = 0;
	Rva009AA260VerticalScale vertical_scale = 0;
	Rva009AA260VerticalScale last_vertical_scale = 0;

	(void)source_height;

	switch (hratio * 10 / hscale)
	{
	case 8:
		horizontal_scale = rva009AA260Horizontal45();
		break;
	case 6:
		horizontal_scale = rva009AA260Horizontal35();
		break;
	case 5:
		horizontal_scale = rva009AA260Horizontal21();
		break;
	case 10:
		horizontal_scale = (Rva009AA260HorizontalScale)HorizontalLine_Copy;
		break;
	default:
		ratio_scalable = 0;
		break;
	}

	switch (vratio * 10 / vscale)
	{
	case 8:
		vertical_scale = rva009AA260Vertical45();
		last_vertical_scale = rva009AA260LastVertical45();
		source_band_height = 4;
		dest_band_height = 5;
		break;
	case 6:
		vertical_scale = rva009AA260Vertical35();
		last_vertical_scale = rva009AA260LastVertical35();
		source_band_height = 3;
		dest_band_height = 5;
		break;
	case 5:
		vertical_scale = rva009AA260Vertical21();
		last_vertical_scale = rva009AA260LastVertical21();
		source_band_height = 1;
		dest_band_height = 2;
		break;
	case 10:
		vertical_scale = Rva009A91C0NullScale;
		last_vertical_scale = Rva009A91C0NullScale;
		source_band_height = 4;
		dest_band_height = 4;
		break;
	default:
		ratio_scalable = 0;
		break;
	}

	if (ratio_scalable == 0)
		return ratio_scalable;

	horizontal_scale(source, source_width, dest, dest_width);

	for (k = 0;
		k < (dest_height + dest_band_height - 1) / dest_band_height - 1;
		++k)
	{
		for (i = 1; i < source_band_height; ++i)
		{
			horizontal_scale(
				source + i * source_pitch, source_width,
				dest + i * dest_pitch, dest_width);
		}

		horizontal_scale(
			source + source_band_height * source_pitch, source_width,
			dest + dest_band_height * dest_pitch, dest_width);

		vertical_scale(dest, dest_pitch, dest_width);

		source += source_band_height * source_pitch;
		dest += dest_band_height * dest_pitch;
	}

	for (i = 1; i < source_band_height; ++i)
	{
		horizontal_scale(
			source + i * source_pitch, source_width,
			dest + i * dest_pitch, dest_width);
	}

	last_vertical_scale(dest, dest_pitch, dest_width);
	return ratio_scalable;
}

#include <string.h>
struct Rva009AA260Context;
extern "C" int __cdecl AnyRatio_2D_Scale(Rva009AA260Context *, const unsigned char *, int, unsigned, unsigned, unsigned char *, unsigned, unsigned, unsigned);

struct Vp6AnyRatioPostProc
{
	unsigned char pad00[0x40];
	unsigned int frameWidth;
	unsigned char pad44[0x58 - 0x44];
	int hScale;
	int hRatio;
	int vScale;
	int vRatio;
	unsigned char pad68[0x70 - 0x68];
	unsigned int expandedWidth;
	unsigned int expandedHeight;
	int reconY;
	int reconU;
	int reconV;
	unsigned char pad84[0xB4 - 0x84];
	int border;
};

struct Vp6AnyRatioYUVConfig
{
	int yWidth, yHeight, yStride, uvWidth, uvHeight, uvStride;
	unsigned char *y, *u, *v;
};

extern "C" int AnyRatioFrameScale(Vp6AnyRatioPostProc *pp, unsigned char *frame, Vp6AnyRatioYUVConfig *config, int yOffset, int uvOffset)
{
	int destWidth = pp->expandedWidth;
	int hRatio = pp->hRatio;
	int vRatio = pp->vRatio;
	int vScale = pp->vScale;
	int hScale = pp->hScale;
	int sourceWidth = (pp->expandedWidth * hRatio + (hScale - 1)) / hScale;
	int destHeight = pp->expandedHeight;
	int sourceHeight = (pp->expandedHeight * vRatio + (vScale - 1)) / vScale;
	int paddedWidth;
	int paddedHeight;
	int result;
	int i;
	if (hRatio == 3)
		paddedWidth = (sourceWidth + 2) / 3 * 3 * pp->hScale / hRatio;
	else
		paddedWidth = (sourceWidth + 7) / 8 * 8 * pp->hScale / hRatio;
	if (vRatio == 3)
		paddedHeight = (sourceHeight + 2) / 3 * 3 * pp->vScale / vRatio;
	else
		paddedHeight = (sourceHeight + 7) / 8 * 8 * pp->vScale / vRatio;
	result = AnyRatio_2D_Scale((Rva009AA260Context *)pp, frame + pp->reconY, pp->frameWidth + pp->border * 2, sourceWidth, sourceHeight,
		config->y + yOffset, config->yStride, destWidth, destHeight);
	for (i = 0; i < paddedHeight; i++)
		memset(config->y + i * config->yStride + destWidth + yOffset, 0, paddedWidth - destWidth);
	for (i = destHeight; i < paddedHeight; i++)
		memset(config->y + i * config->yStride + yOffset, 0, paddedWidth);
	if (result == 0)
		return 0;
	sourceWidth = (sourceWidth + 1) >> 1;
	sourceHeight = (sourceHeight + 1) >> 1;
	destWidth = (destWidth + 1) >> 1;
	destHeight = (destHeight + 1) >> 1;
	AnyRatio_2D_Scale((Rva009AA260Context *)pp, frame + pp->reconU, (pp->frameWidth >> 1) + pp->border, sourceWidth, sourceHeight,
		config->u + uvOffset, config->uvStride, destWidth, destHeight);
	AnyRatio_2D_Scale((Rva009AA260Context *)pp, frame + pp->reconV, (pp->frameWidth >> 1) + pp->border, sourceWidth, sourceHeight,
		config->v + uvOffset, config->uvStride, destWidth, destHeight);
	return result;
}
