// ?Draw_Sentence@Render2DSentenceClass@@QAEXKKKK@Z
// partial score=0.9026288151577504 date=2026-10-16
// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

void __cdecl operator delete[](void *) throw();
#include "vector.h"
#include "vector2i.h"
#include "vector2.h"
#include "../../../../../reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h"
#include <math.h>
typedef unsigned long uint32;

// Donor BFME1 9cbfb551fe20 Render2DSentenceClass_Allocate_New_Surface.cpp.
// BFME2 native 158C60..158E87/551B: no leading Unlock; spacing uses loadCharacterData.
// Target class fields and complete COM surface and PendingSurface lifecycle match donor.
// Target sentence layout/font pointer4C and resource operations attest owner.
// Font record layout is carried from BFME1 source; native width/extra and
// 68/6C texture-offset clears independently support use. Retail constructs
// PendingSurfaceStruct with the owned integer-vector table at VA00BBB5AC,
// whereas the donor's pointer-vector table is VA00BD6C24 in BFME2.

class BfmeSurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

class W3DRadarResetSurface
{
public:
	__declspec(dllimport) __forceinline W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that)
	{
		if (that.m_surface)
			that.m_surface->AddRef();
		if (m_surface)
			m_surface->Release();
		m_surface = that.m_surface;
		return *this;
	}

	BfmeSurfaceResource *m_surface;
};

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

// The callsite sets ecx to this font object, pushes one WCHAR, and the body
// returns a character-record pointer with RET 4.  This name and ABI are
// already pinned independently by the matching font-spacing thunk.
class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short character);

	__forceinline int Get_Char_Height() const
	{
		return char_height;
	}

	__forceinline int Get_Char_Spacing(unsigned short character)
	{
		const FontCharsClassCharDataStruct *data = loadCharacterData(character);
		if (data != 0 && data->Width != 0) {
			if ((character >= 0x0e01 && character <= 0x0e3a)
				|| (character >= 0x0e3f && character <= 0x0e5b)) {
				return data->Width + data->ExtraSpacing;
			}
			return data->Width - pixel_overlap - char_overhang;
		}
		return 0;
	}

private:
	char fields00[0x2c];
	int char_height;
	char fields30[4];
	int char_overhang;
	int pixel_overlap;
};

enum WW3DFormat
{
	// The retail constructor receives 0x15; the semantic format name is
	// intentionally neutral pending an enum witness.
	WW3D_FORMAT_008FC560 = 0x15
};

enum _D3DPOOL
{
	D3DPOOL_SYSTEMMEM = 2
};
typedef _D3DPOOL D3DPOOL;

// SurfaceClass is the one-pointer native wrapper whose constructor writes
// the COM resource at offset zero.  Its implicit destructor invokes the
// native W3DRadarResetSurface base destructor for the temporary lifetime.
class SurfaceClass
	: public W3DRadarResetSurface
{
public:
	SurfaceClass(unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);
	void Unlock();
 struct SurfaceDescription { int Format; unsigned Width, Height; };
 void Get_Description(SurfaceDescription &desc);
};

class Render2DClass
{
public:
	Render2DClass();
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv, unsigned long color1, unsigned long color2, unsigned long color3, unsigned long color4);

private:
	unsigned char m_pad[0x4C];
};

class DX8Wrapper
{
public:
	static unsigned int Get_Resolution_Width() { return ResolutionWidth; }
	static unsigned int Get_Resolution_Height() { return ResolutionHeight; }

protected:
	static int ResolutionWidth;
	static int ResolutionHeight;
};



class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		bool operator==(const SentenceDataStruct &) { return false; }
		bool operator!=(const SentenceDataStruct &) { return true; }
		RectClass ScreenRect, UVRect;
	};

	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		// Retail destruction uses the shared four-byte scalar base table BBB5AC.
		// This is an ABI view; the renderer-pointer element type is donor
		// provenance and has not been established independently in the target.
		DynamicVectorClass<int> rendererStorage;

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	struct RendererDataStruct { Render2DClass *Renderer; W3DRadarResetSurface Surface; bool operator==(const RendererDataStruct &) { return false; } bool operator!=(const RendererDataStruct &) { return true; } };
 void Draw_Sentence(uint32,uint32,uint32,uint32);
	virtual void reset();
	private:
	void Allocate_New_Surface(const unsigned short *text, bool justCalcExtents);

	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct> pending_surfaces;
	DynamicVectorClass<RendererDataStruct> renderers;
	FontCharsClass *font;
	float base_location_x;
	float base_location_y;
	Vector2 Location;
	float cursor_x;
	float cursor_y;
	Vector2i texture_offset;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	W3DRadarResetSurface cur_surface;
	char remaining_fields[0x0C];
 RectClass ClipRect, DrawExtents;
	bool IsClippedEnabled; char padAD[3];
 unsigned short *locked_ptr;
 Vector2 DefaultScale; float TargetWidth, TargetHeight;
};

// Keep the native PendingSurfaceStruct Add body out-of-line at its already
// matched address; the generic header definition is otherwise small enough
// for this TU to inline it into the caller.
template <>
bool DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Add(
	const Render2DSentenceClass::PendingSurfaceStruct &object);

typedef char rva00941a00_surface_wrapper_must_be_4[(sizeof(W3DRadarResetSurface) == 4) ? 1 : -1];
typedef char rva00941a00_pending_surface_must_be_1c[
	(sizeof(Render2DSentenceClass::PendingSurfaceStruct) == 0x1c) ? 1 : -1];
typedef char rva00941a00_pending_vector_must_be_18[
	(sizeof(DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>) == 0x18) ? 1 : -1];

void Render2DSentenceClass::Allocate_New_Surface(
	const unsigned short *text, bool justCalcExtents)
{

	int text_width = 0;
	for (int index = 0; text[index] != 0; index++) {
		text_width += font->Get_Char_Spacing(text[index]);
	}

	int char_height = font->Get_Char_Height();

	current_texture_size = 256;
	int best_tex_mem_usage = 999999999;
	for (int pow2 = 6; pow2 <= 8; pow2++) {
		int size = 1 << pow2;
		int row_count = (text_width / size) + 1;
		int rows_per_texture = size / (char_height + 1);

		if (rows_per_texture > 0) {
			int texture_count = row_count / rows_per_texture;
			texture_count = max(texture_count, 1);
			int texture_mem_usage = texture_count * size * size;
			if (texture_mem_usage < best_tex_mem_usage) {
				current_texture_size = size;
				best_tex_mem_usage = texture_mem_usage;
			}
		}
	}

	current_texture_size = max(texture_size_hint, current_texture_size);

	if (!justCalcExtents)
	{
		if (cur_surface.m_surface) {
			cur_surface.m_surface->Release();
			cur_surface.m_surface = 0;
		}

		cur_surface = SurfaceClass(current_texture_size, current_texture_size,
			WW3D_FORMAT_008FC560, D3DPOOL_SYSTEMMEM);

		Render2DSentenceClass::PendingSurfaceStruct surface_info;
		static_cast<W3DRadarResetSurface &>(surface_info) = cur_surface;
		pending_surfaces.Add(surface_info);
	}

	texture_offset.Set(0,0);
	texture_start_x = 0;
}

void Render2DSentenceClass::Draw_Sentence(uint32 color1, uint32 color2, uint32 color3, uint32 color4)
{
	Render2DClass *curr_renderer = 0;
	W3DRadarResetSurface curr_surface;

	Vector2 scale(DefaultScale);
	DrawExtents.Set(0, 0, 0, 0);

	int index;
	if (TargetWidth > 0 && TargetHeight > 0)
	{
		for (index = 0; index < sentence_data.Count(); index++)
		{
			SentenceDataStruct &data = sentence_data[index];
			if (DrawExtents.Width() == 0)
				DrawExtents = data.ScreenRect;
			else
				DrawExtents += data.ScreenRect;
		}
		float width = DrawExtents.Width();
		if (width != 0)
			scale.X = TargetWidth / width;
		float height = DrawExtents.Height();
		if (height != 0)
			scale.Y = TargetHeight / height;
		DrawExtents.Set(0, 0, 0, 0);
	}

	for (index = 0; index < sentence_data.Count(); index++)
	{
		SentenceDataStruct &data = sentence_data[index];

		if (data.m_surface != curr_surface.m_surface)
		{
			curr_surface = data;

			bool found = false;
			for (int renderer_index = 0; renderer_index < renderers.Count(); renderer_index++)
			{
				if (renderers[renderer_index].Surface.m_surface == curr_surface.m_surface)
				{
					found = true;
					curr_renderer = renderers[renderer_index].Renderer;
					break;
				}
			}

			if (found == false)
			{
				curr_renderer = new Render2DClass;
				curr_renderer->Set_Coordinate_Range(RectClass(0, 0, (float)DX8Wrapper::Get_Resolution_Width(), (float)DX8Wrapper::Get_Resolution_Height()));

				RendererDataStruct render_info;
				render_info.Renderer = curr_renderer;
				render_info.Surface = curr_surface;
				renderers.Add(render_info);

				for (int surface_index = 0; surface_index < pending_surfaces.Count(); surface_index++)
				{
					PendingSurfaceStruct &surface_info = pending_surfaces[surface_index];
					if (surface_info.m_surface == curr_surface.m_surface)
						surface_info.rendererStorage.Add((int)curr_renderer);
				}
			}
		}

		RectClass screen_rect = data.ScreenRect;
		RectClass uv_rect = data.UVRect;
		Vector2 size(screen_rect.Width(), screen_rect.Height());
		screen_rect.Left *= scale.X;
		screen_rect.Top *= scale.Y;
		screen_rect.Right = size.X * scale.X + screen_rect.Left;
		screen_rect.Bottom = size.Y * scale.Y + screen_rect.Top;
		screen_rect += Location;
		screen_rect.Left = floor(screen_rect.Left + 0.5f);
		screen_rect.Top = floor(screen_rect.Top + 0.5f);
		screen_rect.Right = floor(screen_rect.Right + 0.5f);
		screen_rect.Bottom = floor(screen_rect.Bottom + 0.5f);

		if (IsClippedEnabled)
		{
			if (screen_rect.Right <= ClipRect.Left || screen_rect.Bottom <= ClipRect.Top)
				continue;

			RectClass clipped_rect;
			clipped_rect.Left = (screen_rect.Left > ClipRect.Left) ? screen_rect.Left : ClipRect.Left;
			clipped_rect.Right = (screen_rect.Right < ClipRect.Right) ? screen_rect.Right : ClipRect.Right;
			clipped_rect.Top = (screen_rect.Top > ClipRect.Top) ? screen_rect.Top : ClipRect.Top;
			clipped_rect.Bottom = (screen_rect.Bottom < ClipRect.Bottom) ? screen_rect.Bottom : ClipRect.Bottom;

			RectClass clipped_uv_rect;
			float percent = ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width());
			clipped_uv_rect.Left = uv_rect.Left + (uv_rect.Width() * percent);

			percent = ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width());
			clipped_uv_rect.Right = uv_rect.Left + (uv_rect.Width() * percent);

			percent = ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height());
			clipped_uv_rect.Top = uv_rect.Top + (uv_rect.Height() * percent);

			percent = ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height());
			clipped_uv_rect.Bottom = uv_rect.Top + (uv_rect.Height() * percent);

			screen_rect = clipped_rect;
			uv_rect = clipped_uv_rect;

			if (screen_rect.Right <= screen_rect.Left || screen_rect.Bottom <= screen_rect.Top)
				continue;
		}

		SurfaceClass::SurfaceDescription desc;
		((SurfaceClass *)&curr_surface)->Get_Description(desc);

		float inv_width = 1.0f / (float)desc.Width;
		uv_rect.Left *= inv_width;
		uv_rect.Right *= inv_width;
		float inv_height = 1.0f / (float)desc.Height;
		uv_rect.Top *= inv_height;
		uv_rect.Bottom *= inv_height;

		curr_renderer->Add_Quad(screen_rect, uv_rect, color1, color2, color3, color4);

		if (DrawExtents.Width() == 0)
			DrawExtents = screen_rect;
		else
			DrawExtents += screen_rect;
	}
}
