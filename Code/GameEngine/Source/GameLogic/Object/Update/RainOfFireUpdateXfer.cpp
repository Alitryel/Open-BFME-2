// cl: /DNDEBUG /MD
//
// ?xfer@RainOfFireUpdate@@MAEXPAVXfer@@@Z, retail 0x004AC1CB, 92 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00854C74, same primary as rowed ctor
// 0x004AC0A8 (135B) and poolkey 0x004AC148. Base UpdateModule xfer via rowed
// 0x0044DF9F, IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then uint at +0x24 via Xfer slot 0x78 plus four floats at
// +0x28/+0x2C/+0x30/+0x34 via Xfer slot 0x70. Layout is the rowed 0x38-byte
// class (UpdateModule base 0x20 plus +0x20 slot plus +0x24 frame plus four
// floats); BFME1 donor has uint/uint/float/uint/float but retail xfer proves
// BFME2 is uint plus four floats so retail is followed. Recipe is the
// SlowDeathBehaviorXfer/Rva004C908BXfer slot-3 pattern.
//
// ?rva004AC18D@RainOfFireUpdate@@QAEXM@Z, retail 0x004AC18D, 62 bytes.
// Honest address name (no donor): stores float arg to +0x28 then gated
// 1.0-minus-product to display slot 0xC0 via global 0x009FE9D8 when module
// data at +0x04 and display are present. ModuleData +0x14 is darkness per
// the rowed ModuleData table and callers at 0x004AC246/0x004AC28B/0x004AC321
// prove the RainOfFireUpdate file-unit.
//
// ?loadPostProcess@RainOfFireUpdate@@MAEXXZ, retail 0x004AC227, 38 bytes.
// Slot 1 (offset 0x04) of vtable 0x00854C74: base loadPostProcess via pinned
// 0x0058B03E then secondary +0x20 slot 0 with +0x2C float then setter
// 0x004AC18D with +0x28 float. Secondary is the +0x20 interface (no null-check
// lea) holding vtable 0x00C54BA0 per the rowed ctor.

#include "RainOfFireUpdateView.h"

class Display
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void setLevel(float v);
};

extern Display *TheDisplay;

void RainOfFireUpdate::rva004AC18D(float value)
{
	darkness = value;
	if (data == 0)
		return;
	if (TheDisplay == 0)
		return;
	TheDisplay->setLevel(1.0 - (data->darkness * scale * value));
}

void RainOfFireUpdate::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	rvaSlot0(scale);
	rva004AC18D(darkness);
}

void RainOfFireUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == frame;
	*xfer == darkness;
	*xfer == scale;
	*xfer == pending;
	*xfer == ramp;
}
