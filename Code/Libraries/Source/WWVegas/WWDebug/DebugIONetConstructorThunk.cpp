// cl: /DNDEBUG /MD /EHa /Oy-
// readable body of ??0DebugIONet@@QAE@XZ: Code/Libraries/Source/WWVegas/WWDebug/debug_io_net.cpp
// Open-BFME: empty DebugIONet ctor. Inlines the DebugIOInterface vtable
// store, then stores the derived vtable, with the EH state around the
// derived store because the base has a virtual destructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
class DebugIOInterface
{
protected:
	virtual ~DebugIOInterface() {}

public:
	DebugIOInterface() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIONet : public DebugIOInterface
{
public:
	explicit DebugIONet(void);
	virtual ~DebugIONet();
};

// ??0DebugIONet@@QAE@XZ
inline DebugIONet::DebugIONet(void)
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeDebugIONetInlineAnchor@@YAXPAVDebugIONet@@@Z absent-from-retail
void _bfmeDebugIONetInlineAnchor(DebugIONet *debugIONet)
{
    debugIONet->DebugIONet::DebugIONet();
}
#pragma inline_depth()
