// _DiagonalBlur
// partial score=0.9974580556193978 date=2026-10-22
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c2b80.md plus retail only.
// No decoder source was consulted.
struct BlurCursor {
    unsigned char *source;
    unsigned char *dest;
};
static __forceinline void blurImpl(BlurCursor cursor,int pitch)
{
    unsigned char *source=cursor.source;
    unsigned char *dest=cursor.dest;
    unsigned char *src = source;
    unsigned char *dst = dest;
    int row, col;
    for (row = 0; row < 8; row++)
    {
        for (col=0; col<8; col+=4)
        {
            {
                int pixelSample0=src[(col+0)];
                int pixelSample1=src[(col+0) - pitch - 1];
                int pixelSample2=src[(col+0) + pitch - 1];
                int pixelSample3=src[(col+0) - pitch + 1];
                int pixelSample4=src[(col+0) + pitch + 1];
                int pixelSample5=src[(col+0) - 2 * pitch - 2];
                int pixelSample6=src[(col+0) + 2 * pitch + 2];
                int pixelSample7=src[(col+0) + 2 * pitch - 2];
                int pixelSample8=src[(col+0) - 2 * pitch + 2];
                dst[(col+0)] = (unsigned char)((16 + 8 * pixelSample0
                + 4 * (pixelSample1 + pixelSample2 + pixelSample3 + pixelSample4)
                + 2 * (pixelSample5 + pixelSample6 + pixelSample7 + pixelSample8)) >> 5);
            }
            {
                int pixelSample0=src[(col+1)];
                int pixelSample1=src[(col+1) - pitch - 1];
                int pixelSample2=src[(col+1) + pitch - 1];
                int pixelSample3=src[(col+1) - pitch + 1];
                int pixelSample4=src[(col+1) + pitch + 1];
                int pixelSample5=src[(col+1) - 2 * pitch - 2];
                int pixelSample6=src[(col+1) + 2 * pitch + 2];
                int pixelSample7=src[(col+1) + 2 * pitch - 2];
                int pixelSample8=src[(col+1) - 2 * pitch + 2];
                dst[(col+1)] = (unsigned char)((16 + 8 * pixelSample0
                + 4 * (pixelSample1 + pixelSample2 + pixelSample3 + pixelSample4)
                + 2 * (pixelSample5 + pixelSample6 + pixelSample7 + pixelSample8)) >> 5);
            }
            {
                dst[(col+2)] = (unsigned char)((16 + 8 * src[(col+2)]
                + 4 * (src[(col+2) - pitch - 1] + src[(col+2) + pitch - 1] + src[(col+2) - pitch + 1] + src[(col+2) + pitch + 1])
                + 2 * (src[(col+2) - 2 * pitch - 2] + src[(col+2) + 2 * pitch + 2] + src[(col+2) + 2 * pitch - 2] + src[(col+2) - 2 * pitch + 2])) >> 5);
            }
            {
                dst[(col+3)] = (unsigned char)((16 + 8 * src[(col+3)]
                + 4 * (src[(col+3) - pitch - 1] + src[(col+3) + pitch - 1] + src[(col+3) - pitch + 1] + src[(col+3) + pitch + 1])
                + 2 * (src[(col+3) - 2 * pitch - 2] + src[(col+3) + 2 * pitch + 2] + src[(col+3) + 2 * pitch - 2] + src[(col+3) - 2 * pitch + 2])) >> 5);
            }
        }
        dst += pitch;
        src = src + (pitch);
    }
    for (row = 0; row < 8; row++)
    {
        for (col = 0; col < 8; col++)
        {
            int value = (1 + 6 * src[col] - src[col - 1] - src[col - pitch] - src[col + pitch] - src[col + 1]) >> 1;
            if (value < 0)
            value = 0;
            else if (value > 255)
            value = 255;
            dst[col] = (unsigned char)value;
        }
        dst += pitch;
        src += pitch;
    }
}
extern "C" void DiagonalBlur(void *instance,unsigned char *source,unsigned char *dest,int pitch)
{
    BlurCursor cursor={
        source,dest
    }
    ;
    blurImpl(cursor,pitch);
}
