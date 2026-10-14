// ?objectMemberLookup@AptString@@UBEPAVAptValue@@QAV2@QBVEAStringC@@@Z
// cl: /O2 /MD /EHsc
// Full native6D7D80..6D8489 + 3B alignment + 52B switch table through6D84C0.
// WB177FAB0 names AptString::objectMemberLookup and independently supplies
// all 13 property cases. The 12 cache slots are owned by Rva008A98B0ReleaseAll.
// Callback identities and signatures come from their matched provider rows;
// Rva006D6500 stores the callback word at +0x20 in a 36-byte native function.
// Keep the existing cache globals and cast only at each typed use.
// The Ghidra 1885-byte boundary includes the next 29-byte integer constructor;
// the actual lookup body ends after its 52-byte switch table at 006D84C0.
class EAStringC { void *data; public: EAStringC(); ~EAStringC();
 unsigned int rva006D3750()const; const char*rva00620090()const;
 int rva006D5EC0(); bool rva006D3510(const char*)const;
};
class AptValue {public: virtual void AddRef(); void toString(EAStringC&)const;};
class BfmeAptValue006DCD20 {public:void setGCRootCount(unsigned int);};
class AptString {public:
 virtual AptValue*objectMemberLookup(AptValue*const,const EAStringC*const)const;
 static AptValue*sMethod_charCodeAt(AptValue*,int);
 static AptValue*sMethod_slice(AptValue*,int);
};
class AptInteger {public:static AptValue*Create(int);};
struct R4Word {const char*name;int value;};
const R4Word*Rva008A9710(const char*,unsigned int);
class Rva006D2A60 {public:void*allocBlock(int);void freeBlock(void*,int);};
extern Rva006D2A60*g_pChainBlockAllocatorF4;
class Rva006D6500 {
 char payload[0x24];
 public:Rva006D6500(int);
 static void*operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void*p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
};
class Rva008A98B0Releasable;
class Rva006DCE50Opaque; class Rva006DD6C0;
void*rva006D7350(Rva006DCE50Opaque*);
AptString*rva006d74e0(BfmeAptValue006DCD20*,int);
AptValue*rva006D75A0(void*,int);
AptValue*Rva006D6EF0Find(AptValue*,int);
int Rva006F5100Get();
AptValue*rva006D77B0(BfmeAptValue006DCD20*,int);
AptString*rva006d7a60(BfmeAptValue006DCD20*,int,int);
AptString*rva006d7b60(BfmeAptValue006DCD20*,int,int);
AptString*rva006d7c80(BfmeAptValue006DCD20*);
AptString*rva006D7D00(Rva006DD6C0*);
void __cdecl Rva006CC110Log(int,const char*,...);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern Rva008A98B0Releasable*g_rva008A98B0_0;
extern Rva008A98B0Releasable*g_rva008A98B0_1;
extern Rva008A98B0Releasable*g_rva008A98B0_2;
extern Rva008A98B0Releasable*g_rva008A98B0_3;
extern Rva008A98B0Releasable*g_rva008A98B0_4;
extern Rva008A98B0Releasable*g_rva008A98B0_5;
extern Rva008A98B0Releasable*g_rva008A98B0_6;
extern Rva008A98B0Releasable*g_rva008A98B0_7;
extern Rva008A98B0Releasable*g_rva008A98B0_8;
extern Rva008A98B0Releasable*g_rva008A98B0_9;
extern Rva008A98B0Releasable*g_rva008A98B0_10;
extern Rva008A98B0Releasable*g_rva008A98B0_11;

AptValue*AptString::objectMemberLookup(AptValue*const context,const EAStringC*const name)const {
 const R4Word*word=context?Rva008A9710(name->rva00620090(),name->rva006D3750()):0;
 if(word) {
  switch(word->value) {
   case 1: { EAStringC value; context->toString(value); return AptInteger::Create(value.rva006D5EC0()); }
   case 2: {
    if(!g_rva008A98B0_0) {
     g_rva008A98B0_0=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006D7350);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_0)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_0)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_0;
   }
   case 3: {
    if(!g_rva008A98B0_1) {
     g_rva008A98B0_1=(Rva008A98B0Releasable*)new Rva006D6500((int)&AptString::sMethod_charCodeAt);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_1)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_1)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_1;
   }
   case 4: {
    if(!g_rva008A98B0_2) {
     g_rva008A98B0_2=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006d74e0);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_2)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_2)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_2;
   }
   case 5: {
    if(!g_rva008A98B0_3) {
     g_rva008A98B0_3=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006D75A0);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_3)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_3)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_3;
   }
   case 6: {
    if(!g_rva008A98B0_4) {
     g_rva008A98B0_4=(Rva008A98B0Releasable*)new Rva006D6500((int)&Rva006D6EF0Find);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_4)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_4)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_4;
   }
   case 7: {
    if(!g_rva008A98B0_5) {
     g_rva008A98B0_5=(Rva008A98B0Releasable*)new Rva006D6500((int)&Rva006F5100Get);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_5)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_5)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_5;
   }
   case 8: {
    if(!g_rva008A98B0_6) {
     g_rva008A98B0_6=(Rva008A98B0Releasable*)new Rva006D6500((int)&AptString::sMethod_slice);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_6)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_6)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_6;
   }
   case 9: {
    if(!g_rva008A98B0_7) {
     g_rva008A98B0_7=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006D77B0);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_7)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_7)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_7;
   }
   case 10: {
    if(!g_rva008A98B0_8) {
     g_rva008A98B0_8=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006d7a60);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_8)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_8)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_8;
   }
   case 11: {
    if(!g_rva008A98B0_9) {
     g_rva008A98B0_9=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006d7b60);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_9)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_9)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_9;
   }
   case 12: {
    if(!g_rva008A98B0_10) {
     g_rva008A98B0_10=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006d7c80);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_10)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_10)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_10;
   }
   case 13: {
    if(!g_rva008A98B0_11) {
     g_rva008A98B0_11=(Rva008A98B0Releasable*)new Rva006D6500((int)&rva006D7D00);
     ((BfmeAptValue006DCD20*)g_rva008A98B0_11)->setGCRootCount(1);
     ((AptValue*)g_rva008A98B0_11)->AddRef();
    }
    return (AptValue*)g_rva008A98B0_11;
   }
  }
 }
 if(name->rva006D3510("length")||name->rva006D3510("charAt")||name->rva006D3510("charCodeAt")||name->rva006D3510("concat")||name->rva006D3510("fromCharCode")||name->rva006D3510("indexOf")||name->rva006D3510("lastIndexOf")||name->rva006D3510("slice")||name->rva006D3510("split")||name->rva006D3510("substr")||name->rva006D3510("substring")||name->rva006D3510("toLowerCase")||name->rva006D3510("toUpperCase")) {
  Rva006CC110Log(3,"AptString: Incorrect case for '%s'.\n",name->rva00620090());
  g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptString.cpp",0x26A);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return 0;
}
