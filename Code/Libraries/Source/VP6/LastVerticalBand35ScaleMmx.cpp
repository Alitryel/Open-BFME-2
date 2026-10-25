// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d2550.md plus retail only.
// No decoder source was consulted.
//
// LastVerticalBand_3_5_Scale_MMX (retail 0x001D2550, 293 bytes): in-place 3-to-5 vertical scaling of the last band of an image; row 4 is a copy of the original row 2 because no row 5 exists.
// The 16-bit weight tables are the retail constants at image 0x00BD9910 (51),
// 0x00BD9920 (102), 0x00BD9930 (154), 0x00BD9940 (205) and 0x00BD9950 (128).

// The shared native coefficient tables are owned by VerticalBandInterpMmx.cpp.
extern "C"
{
	extern const unsigned short g_bfmeW51c[4];
	extern const unsigned short g_bfmeW102c[4];
	extern const unsigned short g_bfmeW154c[4];
	extern const unsigned short g_bfmeW205c[4];
	extern const unsigned short g_bfmeW128c[4];
}

// RVA 0x001D2550
extern "C" void __cdecl LastVerticalBand_3_5_Scale_MMX(void *band, int pitch, int width)
{
	__asm
	{
		mov esi, band
		mov ecx, pitch
		lea edi, [esi+ecx*2]
		add edi, ecx
		pxor mm7, mm7
		mov edx, width
	bfmeNext:
		movq mm0, qword ptr [esi]
		movq mm1, qword ptr [esi+ecx]
		movq mm2, mm0
		punpcklbw mm0, mm7
		movq mm5, g_bfmeW102c
		punpckhbw mm2, mm7
		pmullw mm0, mm5
		movq mm3, mm1
		punpcklbw mm1, mm7
		pmullw mm2, mm5
		movq mm6, g_bfmeW154c
		movq mm4, mm1
		pmullw mm4, mm6
		punpckhbw mm3, mm7
		movq mm5, mm3
		pmullw mm5, mm6
		paddw mm0, mm4
		paddw mm2, mm5
		paddw mm0, g_bfmeW128c
		paddw mm2, g_bfmeW128c
		psrlw mm0, 8
		psrlw mm2, 8
		packuswb mm0, mm2
		movq qword ptr [esi+ecx], mm0
		movq mm0, qword ptr [esi+ecx*2]
		movq mm4, mm1
		pmullw mm1, g_bfmeW205c
		movq qword ptr [edi+ecx], mm0
		movq mm5, mm3
		pmullw mm3, g_bfmeW205c
		movq mm2, mm0
		pmullw mm4, g_bfmeW51c
		punpcklbw mm0, mm7
		pmullw mm5, g_bfmeW51c
		movq mm6, mm0
		punpckhbw mm2, mm7
		pmullw mm6, g_bfmeW51c
		movq mm7, mm2
		pmullw mm7, g_bfmeW51c
		paddw mm1, mm6
		paddw mm3, mm7
		movq mm6, mm0
		pmullw mm6, g_bfmeW205c
		movq mm7, mm2
		pmullw mm7, g_bfmeW205c
		paddw mm4, mm6
		paddw mm5, mm7
		paddw mm1, g_bfmeW128c
		paddw mm3, g_bfmeW128c
		psrlw mm1, 8
		psrlw mm3, 8
		packuswb mm1, mm3
		movq qword ptr [esi+ecx*2], mm1
		paddw mm4, g_bfmeW128c
		paddw mm5, g_bfmeW128c
		psrlw mm4, 8
		psrlw mm5, 8
		packuswb mm4, mm5
		movq qword ptr [edi], mm4
		add edi, 8
		add esi, 8
		sub edx, 8
		jg bfmeNext
	}
}
