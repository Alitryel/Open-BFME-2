// cl: /MD
// Scalar deleting destructors with no direct data or call reference in
// retail, so neither caller- nor vtable-based discovery served them. Four
// are reached only through an adjustor thunk (sub ecx,N; jmp) that sits in
// a secondary vftable; 0x005F5087 has no reference at all. All five share
// the 28B shape (dtor call, flags byte test, conditional scalar delete
// through pinned ??3@YAXPAX@Z 0x0002FD60, return this), same recipe as
// VslotSmallBodiesAR.cpp. Each dtor is declared but not defined here and
// resolves through a pin in reverse/symbols.csv read from the wrapper's own
// REL32 at +4, so the dtors are non-virtual here; the thunks themselves are
// not modelled. Owner identities and layouts are not recovered; class names
// are the dtor addresses. 0x005F501E carries an existing pin.
//  0x00254008 is now the compiler's ??_GGateProxyBehavior in GateProxyBehaviorCtor.cpp
//  0x002F312E is now the typed Pathfinder MI cleanup in AI/PathfinderDestructor.cpp
//  0x005E7EBB is now the compiler's ??_GRva005E7ED7 in StrategicInGameUIBuildQueueIconSelect.cpp
//  0x005F06D3 is now the compiler's ??_GRva005F0584 in Rva005F0584Dtor.cpp
//  0x005F5087 via dtor 0x005F501E, unreferenced


class Rva005F501E { public: ~Rva005F501E(); };

void operator delete(void *p);

void Rva005F501E_DeleteAnchor(Rva005F501E *p) { delete p; }
