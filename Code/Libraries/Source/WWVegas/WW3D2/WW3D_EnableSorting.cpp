// cl: /DNDEBUG /MD /EHsc
// BFME1 WW3D donor narrowed to the exact target method. Retail stores the
// flag at 0x00DB5F7C and calls matched DX8MeshRendererClass::Invalidate at
// 0x00145FA0 with false.

class DX8MeshRendererClass
{
public:
	void Invalidate(bool shutdown);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class WW3D
{
public:
private:
	static bool IsSortingEnabled;
public:
	static void Enable_Sorting(bool enabled);
};

void WW3D::Enable_Sorting(bool enabled)
{
	IsSortingEnabled = enabled;
	TheDX8MeshRenderer->Invalidate(false);
}
