// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

class LightPoint
{
public:
	~LightPoint();
};

void __cdecl operator delete(void *p);

void __stdcall Rva00425B75Delete(LightPoint *lightPoint)
{
	if (lightPoint != 0)
	{
		lightPoint->~LightPoint();
		operator delete(lightPoint);
	}
}
