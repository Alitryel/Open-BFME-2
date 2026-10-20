# EmotionTrackerUpdate::update 0x4B1633, r48 (2026-10-20, claude-opus-5-5, ~75 min)

Bank now = scratch w3LO.cpp: same bytes as the previous bank (2194/2200, 2
regions, 25 mem, 3 reg; only the case-2 compare at +0x572), but more faithful:
real EmotionNugget::OnActivation (0x4DCC84, landed today) instead of a cast pin,
real STLport hash_map lookup in GameLogic::findObjectByID (ObjectPtrHash as in
Rva00397756IdSweep.cpp), WB-spelled getters (getEmotionTrackerUpdateModuleData,
getContainedBy x5, TauntPointFilter::wasTested, TheEmotionSystem->getObjects,
the +0x454 byte getter, getTemplate, EmotionNugget::getType re-called as WB
does, obj->getPosition in getClosestObject), nugget scans as
for(it){EmotionNugget *nugget=*it; if(getType()==K && CanBeActivatedFor()) break;}.

Meter (diagnostic only, not landable): N chained int locals in the range test
needed for exact 2200: bank 122 -> hash_map 97 -> getters 63..69 -> scans +
OnActivation ~56..62. The count is per function (testStatus visibility or the
0x4B13D8 selector placed earlier in the file do not move it). Chain position
matters: range test / nugget scans / case-2 scan work; countdown condition and
entry do nothing; loop top or countdown block overshoot (2202 B).
`Coord3D pos=*obj->getPosition();` in the debug-draw copy breaks (2190 B).

Strongest lead: the two kind-of tests through real layers Object::isKindOf ->
ThingTemplate::isKindOf -> KindOfMaskType::test (mask at template+0x108) give
retail's exact case-1/case-2 compare shapes with no chain, but
_STL::bitset<218>::test is not inlined (push 0x90; lea ecx,[eax+0x108]; call)
where retail tests bytes (test byte ptr [eax+0x11a],1 / [eax+0x113],4): 2219 B.
Int-mask spelling (m_bits[i>>5] & (1<<(i&31))) inlines; bit 0x90 matches but
bit 0x5A compiles shr eax,0x1a; test al,1 (2198 B); size_t/unsigned index stops
inlining. WB shows BFME2 BitFlags.h:383 test as a cdecl (words*, bit) helper with
an assert: find the real BFME2 BitFlags/KindOf test shape that inlines to byte
tests for both bits. Remaining WB-called getters not yet used: the distance
filter ctor argument and ThingFactory::findTemplate (ledger name at 0x2D06CA).
Scratch build/nbr/r48/4b1633 (w3LKOb.cpp bitset version, w3LKOf1..4 mask
shapes, meter.sh chain meter).
