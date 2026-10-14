// cl: /O1 /G7 /arch:SSE /I. /DNDEBUG /MD /EHsc
// stlport
// WB F54650 names getSingleObjectFromSelection (GameLogicDispatch.cpp:360).
// Native 003775F7..00377613 has the same null test, getAllIDs36F710,
// first ObjectID read and findObjectByID49DC5. Its optimized local-function
// calling contract passes the group in ECX and returns with ret 0; fastcall
// expresses that observed one-argument contract, not the WB debug ABI.
// ZH donor at BFME1 cee35b7d8 supplies vector semantics; native calls and
// WB independently establish identity. This replaces the erroneous donor
// BfmeObjectReference name and its member-pointer reinterpretation.
#include <vector>
class Object;
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class AIGroup { public: const _STL::vector<ObjectID, _STL::allocator<ObjectID> > &getAllIDs() const; };
extern GameLogic *TheGameLogic;
Object *__fastcall getSingleObjectFromSelection(const AIGroup *group) {
 if(group) {
  const _STL::vector<ObjectID, _STL::allocator<ObjectID> >& ids=group->getAllIDs();
  return TheGameLogic->findObjectByID(*ids.begin());
 }
 return 0;
}
