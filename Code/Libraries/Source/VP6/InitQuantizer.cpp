// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b71f0.md plus retail only.
// No decoder source was consulted.
//
// VP6_init_quantizer (retail 0x001B71F0, 945 bytes): cdecl builder of the
// fixed-point reciprocal quantizer multipliers, rounding values, zero-bin
// sizes and zero-run corrections for both planes from the frame Q index.
// The second (version) argument is unused.

#include <string.h>
// g_bfmeApplyTableA (VA 0x00BD7860, retail .rdata contents): 64 dword luma DC/AC quantizer steps by Q index, read as 16-bit low halves by the dequantizer
extern const unsigned short g_bfmeApplyTableA[128] = {
	94, 0, 92, 0, 90, 0, 88, 0, 86, 0, 82, 0, 78, 0, 74, 0,
	70, 0, 66, 0, 62, 0, 58, 0, 54, 0, 53, 0, 52, 0, 51, 0,
	50, 0, 49, 0, 48, 0, 47, 0, 46, 0, 45, 0, 44, 0, 43, 0,
	42, 0, 40, 0, 39, 0, 37, 0, 36, 0, 35, 0, 34, 0, 33, 0,
	32, 0, 31, 0, 30, 0, 29, 0, 28, 0, 27, 0, 26, 0, 25, 0,
	24, 0, 23, 0, 22, 0, 21, 0, 20, 0, 19, 0, 18, 0, 17, 0,
	16, 0, 15, 0, 14, 0, 13, 0, 12, 0, 11, 0, 10, 0, 9, 0,
	8, 0, 7, 0, 6, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1, 0,
};
// g_bfmeApplyTableB (VA 0x00BD7960, retail .rdata contents): the matching 64 dword chroma steps
extern const unsigned short g_bfmeApplyTableB[128] = {
	94, 0, 92, 0, 90, 0, 88, 0, 86, 0, 82, 0, 78, 0, 74, 0,
	70, 0, 66, 0, 62, 0, 58, 0, 54, 0, 53, 0, 52, 0, 51, 0,
	50, 0, 49, 0, 48, 0, 47, 0, 46, 0, 45, 0, 44, 0, 43, 0,
	42, 0, 40, 0, 39, 0, 37, 0, 36, 0, 35, 0, 34, 0, 33, 0,
	32, 0, 31, 0, 30, 0, 29, 0, 28, 0, 27, 0, 26, 0, 25, 0,
	24, 0, 23, 0, 22, 0, 21, 0, 20, 0, 19, 0, 18, 0, 17, 0,
	16, 0, 15, 0, 14, 0, 13, 0, 12, 0, 11, 0, 10, 0, 9, 0,
	8, 0, 7, 0, 6, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1, 0,
};
// g_bfmeApplyTableC (VA 0x00BD7E60, retail .rdata contents): 64 16-bit luma DC steps by Q index
extern const unsigned short g_bfmeApplyTableC[64] = {
	47, 47, 47, 47, 45, 43, 43, 43, 43, 43, 42, 41, 41, 40, 40, 40,
	40, 35, 35, 35, 35, 33, 33, 33, 33, 32, 32, 32, 27, 27, 26, 26,
	25, 25, 24, 24, 23, 23, 19, 19, 19, 19, 18, 18, 17, 16, 16, 16,
	16, 16, 15, 11, 11, 11, 10, 10, 9, 8, 7, 5, 3, 3, 2, 2,
};
// g_bfmeApplyTableD (VA 0x00BD7EE0, retail .rdata contents): 64 16-bit chroma DC steps by Q index
extern const unsigned short g_bfmeApplyTableD[64] = {
	47, 47, 47, 47, 45, 43, 43, 43, 43, 43, 42, 41, 41, 40, 40, 40,
	40, 35, 35, 35, 35, 33, 33, 33, 33, 32, 32, 32, 27, 27, 26, 26,
	25, 25, 24, 24, 23, 23, 19, 19, 19, 19, 18, 18, 17, 16, 16, 16,
	16, 16, 15, 11, 11, 11, 10, 10, 9, 8, 7, 5, 3, 3, 2, 2,
};
// g_bfmeYAcZeroBin (VA 0x00BD7A60, retail .rdata contents): Y AC zero-bin sizes by Q index.
extern const int g_bfmeYAcZeroBin[64] = {
	330, 314, 298, 284, 264, 246, 228, 213, 201, 190, 178, 167, 156, 153, 149, 146,
	144, 141, 138, 135, 132, 130, 127, 124, 121, 115, 110, 104, 99, 96, 94, 90,
	85, 82, 79, 76, 74, 71, 69, 66, 63, 61, 58, 55, 53, 50, 47, 45,
	43, 40, 38, 36, 33, 31, 28, 24, 21, 18, 16, 13, 10, 7, 4, 2,
};
// g_bfmeUvAcZeroBin (VA 0x00BD7B60, retail .rdata contents): UV AC zero-bin sizes by Q index.
extern const int g_bfmeUvAcZeroBin[64] = {
	330, 314, 298, 284, 264, 246, 228, 213, 201, 190, 178, 167, 156, 153, 149, 146,
	144, 141, 138, 135, 132, 130, 127, 124, 121, 115, 110, 104, 99, 96, 94, 90,
	85, 82, 79, 76, 74, 71, 69, 66, 63, 61, 58, 55, 53, 50, 47, 45,
	43, 40, 38, 36, 33, 31, 28, 24, 21, 18, 16, 13, 10, 7, 4, 2,
};
// g_bfmeYAcRounding (VA 0x00BD7C60, retail .rdata contents): Y AC rounding values by Q index.
extern const int g_bfmeYAcRounding[64] = {
	48, 56, 64, 70, 78, 82, 86, 88, 91, 92, 94, 94, 99, 103, 102, 100,
	99, 97, 95, 93, 91, 89, 87, 85, 83, 79, 77, 73, 71, 69, 67, 65,
	64, 62, 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34,
	32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2,
};
// g_bfmeUvAcRounding (VA 0x00BD7D60, retail .rdata contents): UV AC rounding values by Q index.
extern const int g_bfmeUvAcRounding[64] = {
	48, 56, 64, 70, 78, 82, 86, 88, 91, 92, 94, 94, 99, 103, 102, 100,
	99, 97, 95, 93, 91, 89, 87, 85, 83, 79, 77, 73, 71, 69, 67, 65,
	64, 62, 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34,
	32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2,
};
// g_bfmeYDcZeroBin (VA 0x00BD7F60, retail .rdata contents): Y DC zero-bin sizes by Q index.
extern const int g_bfmeYDcZeroBin[64] = {
	170, 162, 152, 150, 140, 130, 125, 121, 121, 118, 113, 111, 110, 108, 108, 106,
	105, 96, 93, 87, 86, 83, 83, 83, 83, 78, 78, 78, 66, 66, 63, 63,
	61, 61, 58, 58, 56, 56, 46, 46, 46, 46, 43, 43, 41, 38, 38, 38,
	38, 38, 35, 24, 24, 24, 23, 23, 20, 19, 16, 13, 6, 6, 4, 4,
};
// g_bfmeUvDcZeroBin (VA 0x00BD8060, retail .rdata contents): UV DC zero-bin sizes by Q index.
extern const int g_bfmeUvDcZeroBin[64] = {
	170, 162, 152, 150, 140, 130, 125, 121, 121, 118, 113, 111, 110, 108, 108, 106,
	105, 96, 93, 87, 86, 83, 83, 83, 83, 78, 78, 78, 66, 66, 63, 63,
	61, 61, 58, 58, 56, 56, 46, 46, 46, 46, 43, 43, 41, 38, 38, 38,
	38, 38, 35, 24, 24, 24, 23, 23, 20, 19, 16, 13, 6, 6, 4, 4,
};
// g_bfmeYDcRounding (VA 0x00BD8160, retail .rdata contents): Y DC rounding values by Q index.
extern const int g_bfmeYDcRounding[64] = {
	20, 28, 38, 40, 44, 46, 50, 50, 51, 57, 59, 61, 62, 64, 66, 67,
	67, 62, 63, 64, 64, 62, 62, 62, 62, 62, 62, 62, 54, 54, 52, 52,
	50, 50, 48, 48, 46, 46, 38, 38, 38, 38, 36, 36, 34, 32, 32, 32,
	32, 32, 30, 22, 22, 22, 20, 20, 18, 16, 14, 10, 6, 6, 4, 4,
};
// g_bfmeUvDcRounding (VA 0x00BD8260, retail .rdata contents): UV DC rounding values by Q index.
extern const int g_bfmeUvDcRounding[64] = {
	20, 30, 38, 40, 44, 46, 50, 50, 51, 57, 59, 61, 62, 64, 66, 67,
	67, 62, 63, 64, 64, 62, 62, 62, 62, 62, 62, 62, 54, 54, 52, 52,
	50, 50, 48, 48, 46, 46, 38, 38, 38, 38, 36, 36, 34, 32, 32, 32,
	32, 32, 30, 22, 22, 22, 20, 20, 18, 16, 14, 10, 6, 6, 4, 4,
};
// g_bfmeZeroRunCorrection: the zero-run zero-bin correction percentages by run length (VA 0xbd8360, retail .rdata contents).
int g_bfmeZeroRunCorrection[64] = {
	-8, 0, 5, 0xa, 0xa, 0xa, 0xa, 0xa,
	0xf, 0xf, 0xf, 0xf, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
	0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
	0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
};
extern double g_Rva01142610;
// g_Rva01142610: matched references place it at VA 0xbd8768 (retail .rdata value 65536.0).
double g_Rva01142610 = 65536.0;
// g_Rva01142608: matched references place it at VA 0xbd8760; retail contents, sized to the
// 0x8-byte gap before the next known global there.
unsigned char g_Rva01142608[8] = {
	0, 0, 0, 0, 1, 1, 0, 0,
};
// vp6DequantIndex: the zig-zag scan order (transmission index -> raster
// position) at VA 0xbd8460; retail contents. The dequantiser, quantiser and
// quantiser-index builders all read it under this name.
unsigned int vp6DequantIndex[64] = {
	0, 1, 8, 16, 9, 2, 3, 10,
	17, 24, 32, 25, 18, 11, 4, 5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13, 6, 7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63,
};
struct Rva009A6780State {
    int index,at0004;
    short at0008[8],at0018[8],at0028[8];
    unsigned char pad0038[0x158];
    int at0190[2][64],at0390[2][64],at0590[2][64],at0790[2][64];
};
extern "C" void __cdecl VP6_init_quantizer(Rva009A6780State* s,int version)
{
    int index=s->index;
    double reciprocal=1.0/(((const short *)g_bfmeApplyTableC)[index]*4);
    reciprocal*=g_Rva01142610;
    s->at0190[0][0]=(int)(reciprocal+0.5);
    s->at0390[0][0]=g_bfmeYDcRounding[index];
    s->at0590[0][0]=g_bfmeYDcZeroBin[index];
    int i;
    for(i=1;i<64;++i) {
        reciprocal=1.0/(((const unsigned *)g_bfmeApplyTableA)[s->index]*4);
        reciprocal*=g_Rva01142610;
        s->at0190[0][i]=(int)(reciprocal+0.5);
        s->at0390[0][i]=g_bfmeYAcRounding[s->index];
        s->at0590[0][i]=g_bfmeYAcZeroBin[s->index];
    }
    index=s->index;
    reciprocal=1.0/(((const short *)g_bfmeApplyTableD)[index]*4);
    reciprocal*=g_Rva01142610;
    s->at0190[1][0]=(int)(reciprocal+0.5);
    s->at0390[1][0]=g_bfmeUvDcRounding[index];
    s->at0590[1][0]=g_bfmeUvDcZeroBin[index];
    for(i=1;i<64;++i) {
        reciprocal=1.0/(((const unsigned *)g_bfmeApplyTableB)[s->index]*4);
        reciprocal*=g_Rva01142610;
        s->at0190[1][i]=(int)(reciprocal+0.5);
        s->at0390[1][i]=g_bfmeUvAcRounding[s->index];
        s->at0590[1][i]=g_bfmeUvAcZeroBin[s->index];
    }
    for(i=0;i<8;++i) {
        s->at0008[i]=(short)s->at0390[0][1];
        s->at0018[i]=(short)s->at0190[0][1];
        s->at0028[i]=(short)s->at0590[0][1]-1;
    }
    for(i=0;i<64;++i) {
        s->at0790[0][i]=(int)(((const unsigned *)g_bfmeApplyTableA)[s->index]*g_bfmeZeroRunCorrection[i]*4)/100;
        s->at0790[1][i]=(int)(((const unsigned *)g_bfmeApplyTableB)[s->index]*g_bfmeZeroRunCorrection[i]*4)/100;
    }
}
