// cl: /Oy-
// A three-way kind test that keeps its frame.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5FiftyOne.cpp); trimmed to the single T1
// body the sweep places.

// ?bfmeIsBasic@@YGHH@Z
int __stdcall bfmeIsBasic(int kind)
{
	if (kind == 0 || kind == 1 || kind == 2)
		return 1;

	return 0;
}
