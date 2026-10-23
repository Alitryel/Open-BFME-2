// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// HAnimComboDataClass::Set_HAnim, retail 0x001007B0 (37 B). Retail's body sits in
// the size-optimised /O1 region (inc/dec reference counts), not with the /O2 /G7
// hanim.cpp bodies, so it is built here under that region's flags.
#include "hanim.h"

inline __declspec(noinline) void HAnimComboDataClass::Set_HAnim(HAnimClass *motion)
{
	if ( motion != NULL ) {
		motion->Add_Ref();
	}
	if ( HAnim != NULL ) {
		HAnim->Release_Ref();
	}
	HAnim = motion;
}

// The counted-holder callers also emit this header inline. Keep the rowed
// provider as a select-any copy, with this non-retail anchor retaining emission.
// ?bfmeAnchorHAnimComboDataSetHAnim absent-from-retail
void bfmeAnchorHAnimComboDataSetHAnim(HAnimComboDataClass *data, HAnimClass *motion)
{
	data->Set_HAnim(motion);
}
