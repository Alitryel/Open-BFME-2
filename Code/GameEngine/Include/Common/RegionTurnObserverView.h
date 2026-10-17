// Structural view; the original interface name remains unknown.
// Native C62A20 is exactly two three-byte RET8 callbacks (50B238), without
// a virtual destructor. Native LivingWorldBuildPlot C63528 overrides the
// first entry with4FC23E; RegionManager BE4350 overrides both.
// Registration in TheLivingWorldLogic+1C and the +4 subobject accesses
// establish the two-int callback ABI independently of the shared no-op bytes.
#pragma once
class RegionTurnObserverView
{
public:
    virtual void BeginTurn(int, int) {}
    virtual void EndTurn(int, int) {}
    ~RegionTurnObserverView() {}
};
