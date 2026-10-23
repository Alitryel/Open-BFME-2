// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva003B83B1@ScriptList@@QAEPAVRva003BScriptReference@@ABV?$StringBase@D@@@Z, retail 0x003b83b1, 76 bytes. Banked partial (score 0.9473684211) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Banked reference-factory reconstruction, not a matched source unit.
// Native extents: 0x003B8337..0x003B8383 and 0x003B83B1..0x003B83FD,
// 76 bytes each, RET 4. ScriptListCtor.cpp independently places the two
// 32-byte subrecords at +0x0C/+0x2C. ScriptListSubrecordRemove.cpp proves
// their 20-byte record layout, record-array +0x0C, and count +0x0E.
// Both bodies reproduce all non-relocation bytes and the resolved allocation
// call. Their first calls remain unresolved: native 0x003B7EC2/0x003B8141
// create the underlying node; these 111-byte EH providers are not rowed.
// Do not add pins without separately establishing and verifying providers.
// Names of the reference class and its three fields remain provisional.
#include "ascii_string.h"
void *__cdecl operator new(unsigned int size);
struct Rva003BRefRecord {
 int previous,next;
 AsciiString name;
 unsigned char released,pad;
 unsigned short references;
 void *nodes;
};
class Rva003BRefSubrecord {
public:
 int rva003B7EC2(const StringBase<char> &key);
 int rva003B8141(const StringBase<char> &key);
 char unknown00[12];
 Rva003BRefRecord *records;
 char unknown10[16];
};
// The rowed int*-payload add 0x003B80B8 (ScriptListSubrecordAddRva003B80B8.cpp)
// on the same 32-byte subrecord, under that row's class spelling.
class Rva003B573E {
public:
 int rva003B80B8(const StringBase<char> &key, int *value);
};
class Rva003BScriptReference {
public:
 Rva003BScriptReference() {next=0;index=-1;references=0;}
 Rva003BScriptReference *next;
 int index,references;
};
class ScriptList {
public:
 Rva003BScriptReference *rva003B8337(const StringBase<char> &key);
 Rva003BScriptReference *rva003B83B1(const StringBase<char> &key);
 Rva003BScriptReference *rva003B83FD(const StringBase<char> &key, int *value);
private:
 char unknown00[12];
 Rva003BRefSubrecord first,second;
};
Rva003BScriptReference *ScriptList::rva003B83B1(const StringBase<char> &key) {
 int index=second.rva003B8141(key);
 if(index!=-1) {
  Rva003BScriptReference *result=new Rva003BScriptReference;
  result->index=index;
  result->references=(short)second.records[index].references;
  return result;
 }
 return 0;
}
// Native 0x003B83FD..0x003B844D, 80 bytes, RET 8: the int*-payload twin of
// rva003B83B1 above, adding through the rowed 0x003B80B8 on the +0x2C
// subrecord before building the same 12-byte reference.
Rva003BScriptReference *ScriptList::rva003B83FD(const StringBase<char> &key, int *value) {
 int index=((Rva003B573E *)&second)->rva003B80B8(key,value);
 if(index!=-1) {
  Rva003BScriptReference *result=new Rva003BScriptReference;
  result->index=index;
  result->references=(short)second.records[index].references;
  return result;
 }
 return 0;
}
