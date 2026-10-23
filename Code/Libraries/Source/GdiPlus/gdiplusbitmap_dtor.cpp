// cl: /O1 /GX-
// Microsoft Platform SDK GDI+ 1.0 GdiPlusBitmap.h inlines, emitted out of line
// by the ATL 7.1 CImage translation unit that carries the Gdiplus::Image and
// Gdiplus::Bitmap vtables.
//
// Bitmap's constructors and scalar deleting destructor share this unit. Its 36 bytes are
// ~Image folded in whole - the vftable store at 0x00BBB524 and the dispose -
// because the destructor is DEFINED here rather than declared. The main unit
// keeps the out-of-line definition, which is what lets Image's own scalar
// deleting destructor at 0x00002111 stay a 27-byte call; define it in the
// class there and that body grows to 30.

typedef unsigned int size_t;
typedef int INT;
typedef unsigned int UINT;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WCHAR;

namespace Gdiplus
{

enum Status
{
    Ok = 0,
    GenericError = 1,
    InvalidParameter = 2,
    OutOfMemory = 3,
    ObjectBusy = 4,
    InsufficientBuffer = 5,
    NotImplemented = 6,
    Win32Error = 7,
    WrongState = 8,
    Aborted = 9,
    FileNotFound = 10,
    ValueOverflow = 11,
    AccessDenied = 12,
    UnknownImageFormat = 13,
    FontFamilyNotFound = 14,
    FontStyleNotFound = 15,
    NotTrueTypeFont = 16,
    UnsupportedGdiplusVersion = 17,
    GdiplusNotInitialized = 18,
    PropertyNotFound = 19,
    PropertyNotSupported = 20
};

typedef INT PixelFormat;

class Rect;
class BitmapData;
struct ColorPalette;

class GpImage;
class GpBitmap;

namespace DllExports
{
extern "C" void *__stdcall GdipAlloc(size_t size);
extern "C" void __stdcall GdipFree(void *ptr);
extern "C" Status __stdcall GdipDisposeImage(GpImage *image);
extern "C" Status __stdcall GdipCloneImage(GpImage *image, GpImage **cloneImage);
extern "C" Status __stdcall GdipGetImageWidth(GpImage *image, UINT *width);
extern "C" Status __stdcall GdipGetImageHeight(GpImage *image, UINT *height);
extern "C" Status __stdcall GdipGetImagePixelFormat(GpImage *image, PixelFormat *format);
extern "C" Status __stdcall GdipGetImagePaletteSize(GpImage *image, INT *size);
extern "C" Status __stdcall GdipGetImagePalette(GpImage *image, ColorPalette *palette, INT size);
extern "C" Status __stdcall GdipCreateBitmapFromFile(const WCHAR *filename, GpBitmap **bitmap);
extern "C" Status __stdcall GdipCreateBitmapFromFileICM(const WCHAR *filename, GpBitmap **bitmap);
extern "C" Status __stdcall GdipCreateBitmapFromScan0(
    INT width, INT height, INT stride, PixelFormat format, BYTE *scan0, GpBitmap **bitmap);
extern "C" Status __stdcall GdipBitmapLockBits(
    GpBitmap *bitmap, const Rect *rect, UINT flags, PixelFormat format, BitmapData *lockedBitmapData);
extern "C" Status __stdcall GdipBitmapUnlockBits(GpBitmap *bitmap, BitmapData *lockedBitmapData);
}

class GdiplusBase
{
public:
    void(operator delete)(void *in_pVoid) { DllExports::GdipFree(in_pVoid); }
    void *(operator new)(size_t in_size) { return DllExports::GdipAlloc(in_size); }
    void(operator delete[])(void *in_pVoid) { DllExports::GdipFree(in_pVoid); }
    void *(operator new[])(size_t in_size) { return DllExports::GdipAlloc(in_size); }
};

class Image : public GdiplusBase
{
public:
    virtual ~Image() { DllExports::GdipDisposeImage(nativeImage); }
    virtual Image *Clone();

    UINT GetWidth();
    UINT GetHeight();
    PixelFormat GetPixelFormat();
    INT GetPaletteSize();
    Status GetPalette(ColorPalette *palette, INT size);

protected:
    Image() {}
    Image(GpImage *nativeImage, Status status);

    void SetNativeImage(GpImage *nativeImage);

    Status SetStatus(Status status) const
    {
        if (status != Ok)
            return (lastResult = status);
        else
            return status;
    }

    GpImage *nativeImage;
    mutable Status lastResult;
    mutable Status loadStatus;

private:
    Image(const Image &C);
    Image &operator=(const Image &C);
};

class Bitmap : public Image
{
public:
    Bitmap(const WCHAR *filename, BOOL useEmbeddedColorManagement);
    Bitmap(INT width, INT height, INT stride, PixelFormat format, BYTE *scan0);

    Status LockBits(const Rect *rect, UINT flags, PixelFormat format, BitmapData *lockedBitmapData);
    Status UnlockBits(BitmapData *lockedBitmapData);
};


// These two native constructors emit Bitmap own vtable and its deleting
// destructor. Other SDK methods are provided by gdiplusbitmap.cpp.
Bitmap::Bitmap(const WCHAR *filename, BOOL useEmbeddedColorManagement)
{
    GpBitmap *bitmap = 0;

    if (useEmbeddedColorManagement)
    {
        lastResult = DllExports::GdipCreateBitmapFromFileICM(filename, &bitmap);
    }
    else
    {
        lastResult = DllExports::GdipCreateBitmapFromFile(filename, &bitmap);
    }

    nativeImage = (GpImage *)bitmap;
}

Bitmap::Bitmap(INT width, INT height, INT stride, PixelFormat format, BYTE *scan0)
{
    GpBitmap *bitmap = 0;

    lastResult = DllExports::GdipCreateBitmapFromScan0(width, height, stride, format, scan0, &bitmap);

    nativeImage = (GpImage *)bitmap;
}


}
