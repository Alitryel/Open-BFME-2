// cl: /MD /EHsc /DNDEBUG
//
// ?rva0009A361@Rva0009A361@@QAEXH@Z @0x0009A361 34B: guarded forward.
// Calls the pinned method 0x000F4AB7 on the 0x00DEBCD8 object (kept in
// ecx across the member test) when the global is non-null and the flag
// byte at +0x0 is set, then clears the flag. Honest address-derived
// names; boundary verified (push esi at 0x9A361, pop esi + ret 4 at end).

// 0x000F4AB7 is rowed as W3DVolumetricShadowManager::renderShadows
// (W3DVolumetricShadowRenderShadows.cpp); the forwarded word is its
// RenderInfoClass reference.
class RenderInfoClass;
class W3DVolumetricShadowManager
{
public:
	void renderShadows(RenderInfoClass &rinfo);
};

class Rva0009A361
{
public:
	void rva0009A361(int v);

private:
	bool m_0;
};

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;

// ?rva0009A361@Rva0009A361@@QAEXH@Z
void Rva0009A361::rva0009A361(int v)
{
	if (TheW3DVolumetricShadowManager != 0 && m_0)
		TheW3DVolumetricShadowManager->renderShadows(*(RenderInfoClass *)v);
	m_0 = 0;
}

