// cl: /DNDEBUG /MD /EHsc

typedef void *(__stdcall *D3DXMatrixInverseFunction)(void *, float *, const void *);
// Name the real import pointer supplied by the D3DX import library.
// Pointer-only forwarding preserves the existing opaque argument views.
extern "C" D3DXMatrixInverseFunction __identifier("_imp__D3DXMatrixInverse@12");

extern "C" void *__stdcall D3DXMatrixInverse(void *output, float *determinant,
                                              const void *input)
{
    return __identifier("_imp__D3DXMatrixInverse@12")(output, determinant, input);
}
