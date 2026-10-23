// cl: /O2
// Clean room: reverse/vp6_cleanroom/specs/001c28c0.md plus retail only. No
// decoder source was consulted.
//
// DeringBlock (retail 0x001C28C0, 701 bytes): cdecl generic deringing of one
// 8x8 block with a spread-measure argument (seven stack arguments: instance,
// source, destination, pitch, fragment Q index, scale table, spread). Nothing
// in retail references it. The spec supplies the identity; the body is the
// previously matched placeholder body (BFME1 byte-identical donor b1
// 0x009B1ED0), renamed.
extern "C" int g_vp6SharpenModifier[64];

struct Rva009B1ED0Info
{
    int opaque[2];
    int field08;
};

// _rva009B1ED0
extern "C" void __cdecl DeringBlock(const Rva009B1ED0Info *info, const void *sourceArgument, void *destinationArgument, int stride, int selector, const int *thresholds, unsigned variance)
{
    const unsigned char *source = (const unsigned char *)sourceArgument;
    unsigned char *dest = (unsigned char *)destinationArgument;
    int strength = thresholds[selector];
    int slope = 4;
    int edgeTag = g_vp6SharpenModifier[selector];
    if (info->field08 > 100)
        strength = info->field08 - 100;
    if (variance > 32768)
        slope = 4;
    else if (variance > 2048)
        slope = 8;
    int cap = 3 * strength;
    if (cap > 32)
        cap = 32;
    unsigned pixels[8];
    for (unsigned row = 0; row < 8; ++row)
    {
        for (unsigned col = 0; col < 8; ++col)
        {
            pixels[0] = source[col - stride - 1];
            pixels[1] = source[col - stride];
            pixels[2] = source[col - stride + 1];
            pixels[3] = source[col - 1];
            pixels[4] = source[col + 1];
            pixels[5] = source[col + stride - 1];
            pixels[6] = source[col + stride];
            pixels[7] = source[col + stride + 1];
            int remaining = 256, sum = 128;
            unsigned center = source[col];
            for (unsigned i = 0; i < 8; ++i)
            {
                unsigned sample = pixels[i];
                int difference = center - sample;
                if (difference > 0)
                    difference = center - sample;
                else
                    difference = sample - center;
                int weight = strength - ((difference * slope) >> 2) + 32;
                if (weight < -64)
                    weight = edgeTag;
                else if (weight < 0)
                    weight = 0;
                else if (weight > cap)
                    weight = cap;
                remaining -= weight;
                sum += weight * pixels[i];
            }
            int value = (int)(remaining * center + sum) >> 8;
            dest[col] = (unsigned char)(value < 0 ? 0 : value > 255 ? 255 : value);
        }
        source += stride;
        dest += stride;
    }
}
