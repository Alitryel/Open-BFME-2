// W3DTankDraw::loadPostProcess, retail 0x000CEA39 (23 bytes), ported from
// Zero Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DTankDraw.cpp (GeneralsMD tree vendored under reference/open-bfme-1/
// inputs/reference).
//
// Target evidence: slot 1 of ??_7W3DTankDraw 0x00BCCBE8 (W3DTankDraw::xfer
// 0x000CE03C is slot 3). The body
// calls 0x000B3A2D, the base loadPostProcess the matched
// W3DTankTruckDraw::loadPostProcess (0x000CDE47) also calls, then 0x000CE7B4
// (tossEmitters, unrowed; its 131-byte body tests and releases the +0x2E8 and
// +0x2F4 emitter handles createEmitters fills), then tail-jumps to the
// matched W3DTankDraw::createEmitters 0x000CE837 -- ZH's toss-and-recreate.

class W3DModelDraw
{
protected:
	virtual void loadPostProcess(void);
};

class W3DTankDraw : public W3DModelDraw
{
protected:
	virtual void loadPostProcess(void);
	void createEmitters(void);
	void tossEmitters(void);
};

void W3DTankDraw::loadPostProcess(void)
{
	// extend base class
	W3DModelDraw::loadPostProcess();

	// toss any existing ones and re-create 'em (since this module expects 'em to always be around)
	tossEmitters();
	createEmitters();
}
