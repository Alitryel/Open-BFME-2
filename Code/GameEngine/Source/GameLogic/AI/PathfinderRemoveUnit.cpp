// cl: /DNDEBUG /MD /EHsc
// ?removeUnitFromPathfindMap@Pathfinder@@QAEXPAVObject@@@Z
// Retail 0x006D5CB0, 27 bytes. Dedicated TU.
// Zero Hour AIPathfind.cpp verbatim (Pathfinder::removeUnitFromPathfindMap
// calls removePos plus removeGoal on the unit).

class Object;

class __declspec(novtable) Pathfinder
{
public:
	void removePos(Object *obj);
	void removeGoal(Object *obj);

// ?removeUnitFromPathfindMap@Pathfinder@@QAEXPAVObject@@@Z
	void removeUnitFromPathfindMap(Object *obj);
};

// ?removeUnitFromPathfindMap@Pathfinder@@QAEXPAVObject@@@Z
void Pathfinder::removeUnitFromPathfindMap(Object *obj)
{
	removePos(obj);
	removeGoal(obj);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x006D5B50 -> ?TrimRight@EAStringC@@QAEAAV1@PBD@Z
#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?TrimRight@EAStringC@@QAEAAV1@PBD@Z")
//   0x006D59F0 -> ?rva006D59F0@EAStringC@@QAEAAV1@PBD@Z
#pragma comment(linker, "/alternatename:?removePos@Pathfinder@@QAEXPAVObject@@@Z=?rva006D59F0@EAStringC@@QAEAAV1@PBD@Z")
