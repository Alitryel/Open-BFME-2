// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.325518 date=2026-10-19
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.187 date=2026-10-17
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.414 date=2026-10-15
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.4 date=2026-10-14
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.4 date=2026-10-14
// Bank draft of the clipped textured-quad draw at 0x0044776F (1105B, RET1C).
// Retail-only transcription (the WB twin 0x972E60 is a different revision:
// it has the lazy shader constants and Set2DShader the retail body lacks).
// Structure: render-state switch, texture handle getter + set, the clip
// clamp/interpolate path for m_17C != 0, Add_Tri x2 or Add_Quad, then the
// render-state restore.
// cl: /O1 /arch:SSE /G7 /MD /EHsc

// Geometry is adapted from GeneralsMD W3DDisplay::drawImage at the donor revision in the handoff.
// Retail proves the float ABI, render states, counted-handle calls and member offsets used here.
class TextureClass { public: virtual void slot00(); unsigned short m_refCount; void Release_Ref(); };
class Render2DClass;
class Vector2 { public: float X, Y; Vector2(float x, float y) : X(x), Y(y) {} };
class RectClass
{
public:
    float Left, Top, Right, Bottom;
    RectClass() {}
    RectClass(float l, float t, float r, float b) : Left(l), Top(t), Right(r), Bottom(b) {}
    RectClass &operator=(const RectClass &r) { Left=r.Left; Top=r.Top; Right=r.Right; Bottom=r.Bottom; return *this; }
    float Width() const { return Right - Left; }
    float Height() const { return Bottom - Top; }
};
struct Rva000470D5Source;
class BFME2ParticleTextureHandle
{
public:
    TextureClass *Ptr;
    BFME2ParticleTextureHandle() : Ptr(0) {}
    BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr) { if (Ptr) ++Ptr->m_refCount; }
    ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};
BFME2ParticleTextureHandle __cdecl Rva000470D5GetTexture(const Rva000470D5Source *);
template<class T> class RefCountPtr;
class Rva000456C9
{
public:
    void rva000456C9(const RefCountPtr<TextureClass> *);
};
class Render2DClass
{
public:
    int m_0;					// +0x00
    unsigned char m_pad4[0x48 - 4];
    unsigned char m_48;				// +0x48
    void Set2DShader(int);
    void Add_Tri(const Vector2 &, const Vector2 &, const Vector2 &,
        const Vector2 &, const Vector2 &, const Vector2 &, unsigned long) throw();
    void Add_Quad(const RectClass &, const RectClass &, unsigned long, unsigned long,
        unsigned long, unsigned long) throw();
};

class Rva0044776F
{
public:
    void rva0044776F(void *texture, float x1, float y1, float x2, float y2,
        unsigned long color, int mode);

private:
    unsigned char m_pad0[0x168];
    Render2DClass *m_render;			// +0x168
    int m_16c, m_170, m_174, m_178;		// +0x16c..+0x178
    unsigned char m_17c;			// +0x17c
};


#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))

// W3DDisplay::drawImage ======================================================
/** Draws an images at the screen coordinates and keeps it within the end
    * screen coords specified */
//=============================================================================
void Rva0044776F::rva0044776F(void *texture, float startX, float startY, float endX, float endY,
    unsigned long color, int mode)
{
    // sanity
    if (texture == 0)
        return;

    // !!
    // Remember to update the GUIEditDisplay::drawImage when you make
    // changes to this, it technically uses W3D code to render itself,
    // but it not derived on the W3DDisplay
    // !!

    const float *uv = (const float *)((const char *)texture + 0x14);
    m_render->m_48 = 1;
    switch (mode)
    {
    case 0: m_render->m_0 = 0; break;
    case 1: m_render->m_0 = 3; break;
    case 3: m_render->m_0 = 1; break;
    case 4: m_render->m_0 = 4; break;
    case 5: m_render->m_0 = 6; break;
    default: break;
    }

    // if we have raw texture data we will use it, otherwise we are referencing filenames
    ((Rva000456C9 *)m_render)->rva000456C9(
        (const RefCountPtr<TextureClass> *)&Rva000470D5GetTexture((const Rva000470D5Source *)texture));

	RectClass screen_rect, uv_rect;
    uv_rect.Left=uv[0];
    screen_rect.Left=startX; screen_rect.Top=startY;
    screen_rect.Right=endX; screen_rect.Bottom=endY;
    uv_rect.Top=uv[1]; uv_rect.Right=uv[2]; uv_rect.Bottom=uv[3];

	if (m_17c)
	{	//need to clip this quad to clip rectangle

		//
		//	Check for completely clipped
		//
		if (	endX <= m_16c ||
				endY <= m_170)
		{
			return;	//nothing to render
		} else {
			RectClass clipped_rect;
			RectClass clipped_uv_rect;

			if( (*(unsigned int *)((char *)texture + 0x30) & 1) )
			{

	
				//
				//	Clip the polygons to the specified area
				//
				
				clipped_rect.Left		= __max (screen_rect.Left, m_16c);
				clipped_rect.Right	= __min (screen_rect.Right, m_174);
				clipped_rect.Top		= __max (screen_rect.Top, m_170);
				clipped_rect.Bottom	= __min (screen_rect.Bottom, m_178);

				//
				//	Clip the texture to the specified area
				//
				
				float percent				= ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width ());
				clipped_uv_rect.Top		= uv_rect.Top + (uv_rect.Height () * percent);

				percent						= ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width ());
				clipped_uv_rect.Bottom	= uv_rect.Top + (uv_rect.Height () * percent);

				percent						= ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height ());
				clipped_uv_rect.Right	= uv_rect.Right - (uv_rect.Width () * percent);

				percent						= ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height ());
				clipped_uv_rect.Left		= uv_rect.Right - (uv_rect.Width () * percent);
			}
			else

			{
			
				//
				//	Clip the polygons to the specified area
				//
				
				clipped_rect.Left		= __max (screen_rect.Left, m_16c);
				clipped_rect.Right	= __min (screen_rect.Right, m_174);
				clipped_rect.Top		= __max (screen_rect.Top, m_170);
				clipped_rect.Bottom	= __min (screen_rect.Bottom, m_178);

				//
				//	Clip the texture to the specified area
				//
				
				float percent				= ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width ());
				clipped_uv_rect.Left		= uv_rect.Left + (uv_rect.Width () * percent);

				percent						= ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width ());
				clipped_uv_rect.Right	= uv_rect.Left + (uv_rect.Width () * percent);

				percent						= ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height ());
				clipped_uv_rect.Top		= uv_rect.Top + (uv_rect.Height () * percent);

				percent						= ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height ());
				clipped_uv_rect.Bottom	= uv_rect.Top + (uv_rect.Height () * percent);
			}

			//
			//	Use the clipped rectangles to render
			//
			screen_rect = clipped_rect;
			uv_rect		= clipped_uv_rect;
		}
	}

	// if rotated 90 degrees clockwise we have to adjust the uv coords
	if( (*(unsigned int *)((char *)texture + 0x30) & 1) )
	{

		m_render->Add_Tri( Vector2( screen_rect.Left, screen_rect.Top ), 
												 Vector2( screen_rect.Left, screen_rect.Bottom ),
												 Vector2( screen_rect.Right, screen_rect.Top ),
												 Vector2( uv_rect.Right, uv_rect.Top),
												 Vector2( uv_rect.Left, uv_rect.Top),
												 Vector2( uv_rect.Right, uv_rect.Bottom ),
												 color );

		m_render->Add_Tri( Vector2( screen_rect.Right, screen_rect.Bottom ),
												 Vector2( screen_rect.Right, screen_rect.Top ),
												 Vector2( screen_rect.Left, screen_rect.Bottom ),
												 Vector2( uv_rect.Left, uv_rect.Bottom ),
												 Vector2( uv_rect.Right, uv_rect.Bottom ),
												 Vector2( uv_rect.Left, uv_rect.Top ),
												 color );

	}  // end if
	else
	{

		// just draw as normal
		m_render->Add_Quad( screen_rect, uv_rect, color, color, color, color );

	}  // end else

    //reset to default states for next time this method is called.
    if (mode != 2)
        m_render->m_0 = 2;
}  // end drawImage
