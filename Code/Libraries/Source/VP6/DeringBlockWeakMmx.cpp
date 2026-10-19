// cl: /Z7
// Clean room: reverse/vp6_cleanroom/specs/001cea80.md plus retail only. No decoder
// source was consulted.
//
// DeringBlockWeak_MMX (retail 0x001CEA80, 2608 bytes): MMX weak deringing of
// one 8x8 block (postproc dispatch slot 16 of the MMX tier). The spec supplies
// the identity; the body is the previously matched placeholder body (BFME1
// byte-identical donor b1 0x009BE180), renamed. MSVC cannot schedule these
// packed-byte SIMD kernels from scalar C++, so the vector work stays inline
// assembly.
//
//
// VP6 adaptive edge filter, wide variant. Genuine hand-vectorized MMX retail
// body (movd/punpcklbw/pcmpgtb/pandn, plain 64-bit MMX only, no SSE2/xmm).
// Same aligned-frame prologue and parameter/table ABI as the diag4 filter at
// 0x009C2320 (see DeringBlockStrongWmt.cpp for the /Z7 recipe writeup): a single
// 8-iteration loop computes vertical/left/right edge-weight planes into two
// __declspec(align(16)) frame buffers, then eight literal (unrolled, no
// branch) reconstruction blocks -- one per output row -- fold the planes
// into the final pixels. Mechanically transcribed from the retail bytes;
// see reverse/re_attempts.log for the derivation notes.

// g_vp6SharpenModifier: the dering sharpen modifier by block q index (VA
// 0xdb7a28, 64 dwords, retail contents; specs 001ce050 / 001cea80). The
// zig-zag order that follows it at 0xdb7b28 is QuantizeWmt.cpp's g_vp6ZigzagSimd.
extern "C" int g_vp6SharpenModifier[64] = {
	-12, -11, -10, -10, -9, -9, -9, -9,
	-6, -6, -6, -6, -6, -6, -6, -6,
	-4, -4, -4, -4, -4, -4, -4, -4,
	-2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxWord128: matched references place it at VA 0xdb7ff0; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxWord128[16] = {
	128, 0, 128, 0, 128, 0, 128, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxWord64: matched references place it at VA 0xdb8000; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxWord64[16] = {
	64, 0, 64, 0, 64, 0, 64, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxByte64: matched references place it at VA 0xdb8010; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxByte64[16] = {
	64, 64, 64, 64, 64, 64, 64, 64,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxByte32: matched references place it at VA 0xdb8020; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxByte32[16] = {
	32, 32, 32, 32, 32, 32, 32, 32,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxByte127: matched references place it at VA 0xdb8030; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxByte127[16] = {
	127, 127, 127, 127, 127, 127, 127, 127,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxByte128: matched references place it at VA 0xdb8040; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxByte128[16] = {
	128, 128, 128, 128, 128, 128, 128, 128,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_vp6DeringMmxByte231: matched references place it at VA 0xdb8060; retail contents, sized to the
// 0x10-byte gap before the next known global there.
extern "C" unsigned char g_vp6DeringMmxByte231[16] = {
	231, 231, 231, 231, 231, 231, 231, 231,
	0, 0, 0, 0, 0, 0, 0, 0,
};

extern "C" void __cdecl DeringBlockWeak_MMX(
	void *unused, void *sourceArgument, void *destinationArgument,
	int stride, int selector, int *filterTable)
{
	__declspec(align(16)) short vertical[9][8];
	__declspec(align(16)) short horiz[16][8];
	int localStride = stride;
	unsigned char *source = (unsigned char *)sourceArgument;
	unsigned char *dest = (unsigned char *)destinationArgument;
	short *bufV = &vertical[0][0];
	short *bufH = &horiz[0][0];
	int selectorWeight = filterTable[selector];
	int edgeTag = g_vp6SharpenModifier[selector];

	__asm {
		push esi
		push edi
		mov esi, source
		mov edi, bufV
		push ecx
		push edx
		mov ecx, localStride
		xor edx, edx
		push eax
		push ebx
		mov eax, selectorWeight
		mov ebx, edgeTag
		movd mm0, eax
		movd mm2, ebx
		punpcklbw mm0, mm0
		sub edx, ecx
		punpcklbw mm2, mm2
		pxor mm7, mm7
		punpcklbw mm0, mm0
		mov eax, bufH
		punpcklbw mm2, mm2
		lea ebx, [esi + ecx*8]
		punpcklbw mm0, mm0
		movq mm1, mm0
		punpcklbw mm2, mm2
		paddb mm1, mm0
		paddb mm1, mm0
		paddusb mm1, qword ptr [g_vp6DeringMmxByte231]
		paddb mm0, qword ptr [g_vp6DeringMmxByte32]
		psubusb mm1, qword ptr [g_vp6DeringMmxByte231]
		movq mm3, qword ptr [g_vp6DeringMmxByte127]
		pandn mm1, mm3
	vloop:
		movq mm3, qword ptr [esi]
		movq mm4, qword ptr [esi + edx]
		movq mm5, mm3
		psubusb mm3, mm4
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [g_vp6DeringMmxByte128]
		paddb mm4, qword ptr [g_vp6DeringMmxByte64]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		pxor mm5, mm5
		pxor mm4, mm4
		punpcklbw mm5, mm6
		psraw mm5, 8
		movq qword ptr [edi], mm5
		punpckhbw mm4, mm6
		psraw mm4, 8
		movq qword ptr [edi + 8], mm4
		movq mm3, qword ptr [esi]
		movq mm4, qword ptr [esi - 1]
		movq mm5, mm3
		psubusb mm3, mm4
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [g_vp6DeringMmxByte128]
		paddb mm4, qword ptr [g_vp6DeringMmxByte64]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		pxor mm5, mm5
		pxor mm4, mm4
		punpcklbw mm5, mm6
		psraw mm5, 8
		movq qword ptr [eax], mm5
		punpckhbw mm4, mm6
		psraw mm4, 8
		movq qword ptr [eax + 8], mm4
		movq mm3, qword ptr [esi]
		movq mm4, qword ptr [esi + 1]
		movq mm5, mm3
		psubusb mm3, mm4
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [g_vp6DeringMmxByte128]
		paddb mm4, qword ptr [g_vp6DeringMmxByte64]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		pxor mm5, mm5
		pxor mm4, mm4
		punpcklbw mm5, mm6
		psraw mm5, 8
		movq qword ptr [eax + 0x80], mm5
		punpckhbw mm4, mm6
		psraw mm4, 8
		movq qword ptr [eax + 0x88], mm4
		add esi, ecx
		add edi, 0x10
		add eax, 0x10
		cmp esi, ebx
		jne vloop
		movq mm3, qword ptr [esi]
		movq mm4, qword ptr [esi + edx]
		movq mm5, mm3
		psubusb mm3, mm4
		psubusb mm4, mm5
		por mm3, mm4
		movq mm6, mm0
		paddusb mm3, mm3
		movq mm4, mm0
		psubusb mm6, mm3
		movq mm5, qword ptr [g_vp6DeringMmxByte128]
		paddb mm4, qword ptr [g_vp6DeringMmxByte64]
		pxor mm4, mm5
		pxor mm3, mm5
		pcmpgtb mm3, mm4
		pand mm3, mm2
		paddsb mm6, mm1
		psubsb mm6, mm1
		por mm6, mm3
		pxor mm5, mm5
		pxor mm4, mm4
		punpcklbw mm5, mm6
		psraw mm5, 8
		movq qword ptr [edi], mm5
		punpckhbw mm4, mm6
		psraw mm4, 8
		movq qword ptr [edi + 8], mm4
		mov esi, source
		mov edi, dest
		mov eax, bufV
		mov ebx, bufH
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		add esi, ecx
		add edi, ecx
		add eax, 0x10
		add ebx, 0x10
		movq mm0, qword ptr [esi + edx]
		pxor mm7, mm7
		movq mm1, mm0
		punpcklbw mm0, mm7
		movq mm4, qword ptr [eax]
		punpckhbw mm1, mm7
		movq mm5, qword ptr [eax + 8]
		pmullw mm0, mm4
		movq mm2, qword ptr [esi + ecx]
		pmullw mm1, mm5
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [eax + 0x10]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [eax + 0x18]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi - 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 8]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi + 1]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [ebx + 0x80]
		punpckhbw mm3, mm7
		paddw mm4, mm6
		pmullw mm2, mm6
		movq mm6, qword ptr [ebx + 0x88]
		paddw mm0, mm2
		paddw mm5, mm6
		pmullw mm3, mm6
		movq mm2, qword ptr [esi]
		paddw mm1, mm3
		movq mm3, mm2
		punpcklbw mm2, mm7
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		punpckhbw mm3, mm7
		psubw mm6, mm4
		pmullw mm2, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord128]
		paddw mm0, mm2
		psubw mm6, mm5
		pmullw mm3, mm6
		movq mm6, qword ptr [g_vp6DeringMmxWord64]
		movq mm7, mm6
		paddw mm0, mm6
		paddw mm1, mm3
		psllw mm7, 8
		paddw mm0, mm7
		paddw mm1, mm6
		paddw mm1, mm7
		psubusw mm0, mm7
		psubusw mm1, mm7
		psrlw mm0, 7
		psrlw mm1, 7
		packuswb mm0, mm1
		movq qword ptr [edi], mm0
		pop ebx
		pop eax
		pop edx
		pop ecx
		pop edi
		pop esi
	}
}
