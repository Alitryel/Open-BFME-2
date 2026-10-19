// ?rva00601C53@@YAXPAXH000@Z
// partial score=0.9372256759793274 date=2026-10-16
// cl: /O1 /arch:SSE /G7 /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme_stlport_int_dealloc_link
// stlport
//
// The 0x34-byte helper BFME 2 added to INI at +0x838 (INI_ctor.cpp):
//   ??0Rva00601BBCHelper@@QAE@XZ   0x00601BBC  constructor
//   ??1Rva00601BBCHelper@@UAE@XZ   0x00601BF3  destructor
//   ??_GRva00601BBCHelper@@UAEPAXI@Z 0x00602056 scalar deleting destructor
// Layout from these bodies: a one-slot vtable (0x00C7A6B0, slot 0 the
// deleting destructor), a 0x18-byte member at +4 built by the rowed
// Rva00524415 constructor (two vectors) and torn down by 0x00601AE9, and two
// four-byte-element vectors at +0x1C and +0x28 whose storage is freed
// directly. The constructor runs the once-only table init 0x006016C9; the
// destructor first clears everything through 0x00601A8D. The class's identity
// (a token/lexer table, by its ctype-table init) is not established, so the
// names stay address-derived; the callees are pinned.

#define _strcmpi bfmeStatic_strcmpi_unused
#define strcmp bfmeStatic_strcmp_unused
#define strncpy bfmeStatic_strncpy_unused
#include <vector>
#include "ascii_string.h"
#undef _strcmpi
#undef strcmp
#undef strncpy
extern int TextFileCharacterClasses[256];
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char*,const char*,unsigned);
extern "C" __declspec(dllimport) int __stdcall PathRemoveFileSpecA(char*);
extern "C" __declspec(dllimport) int __stdcall PathAppendA(char*,const char*);
extern "C" __declspec(dllimport) int __stdcall PathCanonicalizeA(char*,const char*);
void *operator new[](unsigned,unsigned);
class ModuleData;
class File {public:virtual void v0();virtual void v1();virtual void close();virtual int read(void*,int);virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual int size();AsciiString filename;};
class FileSystem {public:File *openFile(const char*,int,int);};
extern FileSystem *TheFileSystem;
class Debug {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void output(const char*);virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void finish(int);virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void skip();virtual void v25();virtual void v26();virtual Debug *start(int,int,int);class Format {public:Format(const char*,...);operator const char*()const{return data;}private:char data[512];};};
extern Debug *theDebug;
void _bfme_debugRecordCallsite(int);
class Rva00601B30 {public:void add(unsigned,unsigned,const char*);};
char *Rva006017DAParse(const char*,char*,int);
typedef _STL::vector<const char*> CStringVector;
__forceinline void appendCString(CStringVector &v,const char *const &s) {reinterpret_cast<_STL::vector<const ModuleData*>&>(v).push_back(reinterpret_cast<const ModuleData *const &>(s));}

#include "int_dealloc.h"

void Rva006016C9Init() throw();

// ?rva00601C53@@YAXPAXH000@Z @0x00601C53 1027B worker (unrowed): __cdecl 5-param
// (outer, flag, m_1C, m_28, &m_04); address-derived ABI from the native call; semantic identity remains unknown.
void __cdecl rva00601C53(void *outer, int flag, void *vec1, void *vec2, void *member);

struct Rva00524415
{
	Rva00524415();
	~Rva00524415();
	char m_body[0x18];
};

class Rva00601BBCHelper
{
public:
	Rva00601BBCHelper();
	Rva00601BBCHelper(void *outer);
	virtual ~Rva00601BBCHelper();

	void rva00601A8D();
	bool rva00602072(void *outer);

private:
	Rva00524415 m_04;            // +0x04
	_STL::vector<int> m_1C;      // +0x1C
	_STL::vector<int> m_28;      // +0x28
};

Rva00601BBCHelper::Rva00601BBCHelper()
{
	Rva006016C9Init();
}

Rva00601BBCHelper::~Rva00601BBCHelper()
{
	rva00601A8D();
}

// ?rva00602072@Rva00601BBCHelper@@QAE_NPAX@Z @0x00602072 31B wrapper: forwards
// outer/1/m_1C/m_28/&m_04 into worker 0x00601C53, returns true. Retail:
// 8d4104 push &m_04, 8d4128 push m_28, 83c11c push m_1C, 6a01 push 1,
// ff742414 push outer, e8 -> 0x00601C53, 83c414, b001, c20400.
bool Rva00601BBCHelper::rva00602072(void *outer)
{
	rva00601C53(outer, 1, &m_1C, &m_28, &m_04);
	return true;
}

// ??0Rva00601BBCHelper@@QAE@PAX@Z @0x00602091 95B: same member init
// as the void ctor (vtable + m_04 + two vectors + once-only init) then tail
// forwards the incoming outer pointer through the rowed 0x00602072 wrapper.
// __thiscall 1-arg ret4; wrapper result discarded. EH unwinds members if the
// worker throws (init itself is throw()).
Rva00601BBCHelper::Rva00601BBCHelper(void *outer)
{
	Rva006016C9Init();
	rva00602072(outer);
}

void rva00601C53(void *outer,int lineFlag,void *vec1,void *vec2,void *member) {
 File *file=(File*)outer;CStringVector &stack=*(CStringVector*)vec1,&buffers=*(CStringVector*)vec2;
 int lineStart=1;int size=file->size();const char *token=0;int line=1;
 for(unsigned j=0;j<stack.size();++j)if(_strcmpi(file->filename.str(),stack[j])==0) {
  _bfme_debugRecordCallsite(1);theDebug->skip();const char *errorName=file->filename.str();const char **entries=stack.begin();Debug *d=theDebug->start(0,0,0);
  d->output(Debug::Format("ERROR: Circular include in %s line %d, Circular file %s, parent file %s",entries[stack.size()-1],lineFlag,errorName,entries[0]));d->finish(1);return;
 }
 const char *filename=file->filename.str();appendCString(stack,filename);
 char *data=new(0x737472) char[size+1];const char *owned=data;appendCString(buffers,owned);
 file->read(data,size);data[size]=0;
 int i=0;int cls=TextFileCharacterClasses[(unsigned char)data[0]];int tokenPosition=0;
 while(i<size) {
  switch(cls) {
  case 4:
   if(i<size-1 && data[i+1]=='/') {while(i<size && cls!=1) {data[i]=0;cls=TextFileCharacterClasses[(unsigned char)data[i+1]];++i;}lineStart=1;break;}
   cls=0;
  case 0:case 2:{
   bool meaningful=cls==0;
   if(lineStart==1){token=data+i;++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];tokenPosition=i;}
   lineStart=0;
   while((i<size && cls==0) || cls==2) {
    if(cls==2)data[i]=' ';else meaningful=true;
    ++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];
   }
   if(meaningful) {
    char includeName[260];int limit=size-tokenPosition<260?size-tokenPosition:260;
    char *include=Rva006017DAParse(token,includeName,limit);
    if(include) {
     char path[260],canonical[260];strncpy(path,file->filename.str(),260);path[259]=0;
     PathRemoveFileSpecA(path);PathAppendA(path,include);
     for(char *p=path;*p;++p)if(*p=='/')*p='\\';
     char *name=path;if(PathCanonicalizeA(canonical,path))name=canonical;
     File *child=TheFileSystem->openFile(name,1,0);
     if(!child){_bfme_debugRecordCallsite(1);theDebug->skip();const char **entries=stack.begin();Debug *d=theDebug->start(0,0,0);d->output(Debug::Format("ERROR: Could not open include in %s line %d, file %s, parent file %s",entries[stack.size()-1],lineFlag,name,entries[0]));d->finish(1);return;}
     rva00601C53(child,line,vec1,vec2,member);child->close();
    }else((Rva00601B30*)member)->add((unsigned)token,line,file->filename.str());
   }else token=0;
   break;}
  case 3:while(i<size && cls!=1){data[i]=0;++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];}lineStart=1;break;
  case 1:lineStart=1;while(i<size && cls==1){line+=data[i]=='\r';data[i]=0;++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];}break;
  }
 }
 struct VectorWords {const char **begin,**end,**capacity;};--((VectorWords*)&stack)->end;
}
