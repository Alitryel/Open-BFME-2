// cl: /DNDEBUG /MD /GX
// stlport
//
// ?xfer@DynamicShroudClearingRangeUpdate@@QAEXPAVXfer@@@Z retail 0x0048B505
// ~165 bytes. Behavior-side xfer completing the DynamicShroudClearingRangeUpdate
// file-unit (behavior ctor/dtor/??_G, ModuleData proc/ctor/factory, poolkey,
// instance factory and killGridDecals all rowed).
//
// Transcribed from the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/
// DynamicShroudClearingRangeUpdate.cpp): base xfer, light-CRC early-out,
// Version1, two int runs, five unsigned runs, one bool run, three real runs.
// The Xfer declaration is the SkirmishGameInfoXfer proven spelling (slot 4
// IsLightCRC guard, Version1 direct row, == overloads in reverse slots:
// int 0x7C, uint 0x78, bool 0x90, float 0x70). UpdateModule::xfer rides the
// pinned 0x44DF9F base xfer.

#include "DynamicShroudClearingRangeUpdateView.h"

// ?xfer@DynamicShroudClearingRangeUpdate@@QAEXPAVXfer@@@Z @0x0048B505
void DynamicShroudClearingRangeUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	xfer->Version1();

	*xfer == m_stateCountDown;
	*xfer == m_totalFrames;
	*xfer == m_growStartDeadline;
	*xfer == m_sustainDeadline;
	*xfer == m_shrinkStartDeadline;
	*xfer == m_doneForeverFrame;
	*xfer == m_changeIntervalCountdown;
	*xfer == m_decalsCreated;
	*xfer == m_visionChangePerInterval;
	*xfer == m_nativeClearingRange;
	*xfer == m_currentClearingRange;
}
