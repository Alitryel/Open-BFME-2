#pragma once
class AsciiString;
class UnicodeString;
class GameWindow;
class GameFont;
class WinInstanceData;
// Target record view: field purpose follows the donor where native stores agree.
// Native factories independently read the instance pointer at +0x30.
class GadgetCreateView
{
public:
    GadgetCreateView();
    GameWindow *parent;
    unsigned int status;
    int x, y, width, height;
    void *unknown24;
    void *system;
    unsigned char unknown32[16];
    WinInstanceData *instance;
};
struct TabControlDataView { unsigned char opaque[84]; };
struct RadioButtonDataView { unsigned char opaque[8]; };
class DisplayString;
struct StaticTextDataView { DisplayString *text; unsigned int unknown4; };
struct SliderDataView { int minVal, maxVal; float numTicks; int position; };
// Declaration-only view of the native manager's observed virtual slots.
// Factory member names describe donor purpose; this view does not assert
// the original target record/type names or the factories' vtable positions.
class TabWindowManagerView
{
public:
#define V(n) virtual void unusedSlot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18)
    virtual GameWindow *createPushButtonFromView(GadgetCreateView *, GameFont *, bool);
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, bool);
    V(31) V(32) V(33)
    virtual GameWindow *createFromView(GadgetCreateView *);
    V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44)
    V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54)
    V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64)
    V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74)
    virtual UnicodeString winTextLabelToText(AsciiString);
#undef V
    GameWindow *gogoGadgetTabControl(GadgetCreateView *, TabControlDataView *, GameFont *, bool);
    GameWindow *gogoGadgetProgressBar(GadgetCreateView *, GameFont *, bool);
    GameWindow *gogoGadgetPushButton(GadgetCreateView *, GameFont *, bool);
    GameWindow *gogoGadgetCheckBox(GadgetCreateView *, GameFont *, bool);
    GameWindow *gogoGadgetRadioButton(GadgetCreateView *, RadioButtonDataView *, GameFont *, bool);
    GameWindow *gogoGadgetStaticText(GadgetCreateView *, StaticTextDataView *, GameFont *, bool);
    GameWindow *gogoGadgetSlider(GadgetCreateView *, SliderDataView *, GameFont *, bool);
};
