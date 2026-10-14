// cl: /O1 /Oy- /MD /GX-
// ScriptList::clear, native 0x003B7812..0x003B7836 (36B, RET0).
// SidesInfo::init calls this member for its by-value ScriptList at +8;
// the rowed constructor and destructor establish the 0x4C-byte extent.
// The constructor at 0x003B7720 only initializes the two pointer fields,
// vtable and two empty records. Its complete callee chain allocates nothing.
// Placement construction forwards the constructor result to swap, as retail
// does, while cleanup uses the original storage address after the swap.
// This is the same proven lifetime pattern as ScriptListSubrecordReset.cpp;
// original field identities beyond the known virtual prefix remain opaque.

#include <new>
class ScriptList {
public:
 ScriptList() throw();
 virtual ~ScriptList();
 void swap(ScriptList *other);
 void clear();
private:
 char data[0x48];
};
void ScriptList::clear() {
 char storage[sizeof(ScriptList)];
 ScriptList *temp=new(storage) ScriptList;
 temp->swap(this);
 ((ScriptList *)storage)->ScriptList::~ScriptList();
}
