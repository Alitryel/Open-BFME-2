// cl: /GX-
// Retail thunk at 0x0031AD8F (5B) calls the matched free enabler at
// 0x0043C96F. RET at 0x0031AD8E and the next start at 0x0031AD94
// corroborate the thunk inventory extent; its JMP targets that provider.
// Target caller 0x00376D49 loads TheControlBar at VA 0x00E01CFC for
// this call and the following rowed hideSpecialPowerShortcut member.
// That global's identity is established by ControlBarFields.cpp's matched
// DIR32 uses. The receiver is unused; no object layout is claimed here.
// Named ControlBar::hidePurchaseScience: Zero Hour's GeneralsExpPoints.cpp
// calls TheControlBar->hidePurchaseScience(), and retail
// GeneralsExpPointsSystem calls this thunk at the same point (REL32 at
// 0x0050DE08, recorded by the existing pin); the closeWindows-style caller
// 0x00376D49 then calls hideSpecialPowerShortcut, as Zero Hour's callers do.
void __cdecl Rva0043C96FEnable();
class ControlBar
{
public:
    void hidePurchaseScience();
};
void ControlBar::hidePurchaseScience()
{
    Rva0043C96FEnable();
}
