// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// partial score=0.98787 date=2026-10-16
// cl: /O2 /MD /EHsc /ICode/Libraries/Source/Apt/AptObject
// Clean WB175EA50-shaped body (no hacks): direct PopAndPush of the native call, nFormal<nParams?nFormal:nParams min.
// Residue: only savedPool vs GetConstantPool-temp/state stack-slot order (retail state/temp@+14, pool@+1C; ours swapped).
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "AptScriptFunction.h"
class BfmeAptValue006DCD20 { public: int isNativeFunction() const; int isScriptFunction() const; bool isUndefined() const;int rva006E03A0() const; BfmeAptValue006DCD20 *rva006DCF20(); BfmeAptValue006DCD20 *rva006DCEE0(); };
class Rva006CD650{public:void*rva006CD650();};
struct NativeFunctionView { char opaque[0x20]; AptValue *(__cdecl *function)(AptValue *,int); };
class AptCIH : public AptValue { char opaque[0x5c-8]; public: unsigned int state; const AptCIH *rva006E0CB0() const; };
extern AptValue *gpUndefinedValue;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptBasePtrStack { public: int GetSize() const {return count;} int count,capacity; AptValue **items; BfmeAptValue006DCD20 *At(int); void rva006E3AA0(int); void PopAndPush(int,BfmeAptValue006DCD20 *); void rva006FDF30(BfmeAptValue006DCD20*);void PushNoInc(AptValue *v) {if(count>=capacity){g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h",0x90);if(g_bfmeAptBreakOnAssertAtDDC01C){__debugbreak();}}items[count++]=v;} };
template<class T>struct AptValuePtrStack { int count,capacity; AptValue **items; void push(AptValue *); void pop(){if(count<=0){g_bfmeAptAssertAtE17734("size() > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C){__debugbreak();}}items[count-1]->Release();--count;} };
struct AptActionInterpreter {
 AptBasePtrStack stack; char pad[0x24-12]; AptValuePtrStack<AptValue> thisStack; AptScriptFunctionBase *mpCurrentFunction; char debug[12]; AptConstantPool constantPool; char pad2[0x60-0x48]; int unwind;
 const unsigned char *runStream(const unsigned char *,AptCIH *,int,struct AptCharacterInst*);
 void callFunction(AptValue *,AptValue *,int);
};
void AptActionInterpreter::callFunction(AptValue *context,AptValue *function,int nParams) {
 int nStackElementsPre=stack.count-nParams;
 if(function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isNativeFunction()) {
  AptConstantPool savedPool=constantPool;
  stack.PopAndPush(nParams,(BfmeAptValue006DCD20*)((NativeFunctionView *)((BfmeAptValue006DCD20 *)function)->rva006DCF20())->function(context,nParams));
  constantPool=savedPool;
 } else if(function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isScriptFunction()) {
  AptConstantPool savedPool=constantPool;
  AptScriptFunctionBase *pPrevFunction=mpCurrentFunction;
  mpCurrentFunction=(AptScriptFunctionBase *)((BfmeAptValue006DCD20 *)function)->rva006DCEE0();
  constantPool=mpCurrentFunction->GetConstantPool();
  if(((BfmeAptValue006DCD20*)mpCurrentFunction->mpCIH)->isUndefined()
   || ((unsigned char)((BfmeAptValue006DCD20*)mpCurrentFunction->mpCIH)->rva006E03A0() && (mpCurrentFunction->mpCIH->state&0xc0000)==0)
   || ((unsigned char)((BfmeAptValue006DCD20*)mpCurrentFunction->mpCIH)->rva006E03A0() && (mpCurrentFunction->mpCIH->state&0xc0000)==0x80000)) {
   stack.rva006E3AA0(nParams);
   stack.rva006FDF30((BfmeAptValue006DCD20*)gpUndefinedValue);
   mpCurrentFunction->mpCIH=(AptCIH *)gpUndefinedValue;
  } else {
   thisStack.push(context);
   mpCurrentFunction->AddRef();
   _AptScriptFunctionState state;
   mpCurrentFunction->SetupBeforeExecution(&state,context);
   int nFormalArgs=mpCurrentFunction->GetNumArguments();
   int nArgs=nFormalArgs<nParams ? nFormalArgs : nParams;
   int i;
   for(i=0;i<nArgs;++i){AptValue *param=(AptValue*)stack.At(i);mpCurrentFunction->SetArgument(param,i);}
   for(;i<nFormalArgs;++i)mpCurrentFunction->SetArgument(gpUndefinedValue,i);
   stack.rva006E3AA0(nParams);
   const AptCIH *root=mpCurrentFunction->mpParentAnim->rva006E0CB0();
   AptCharacterInst *character=root?(AptCharacterInst*)((Rva006CD650*)root)->rva006CD650():0;
   runStream(mpCurrentFunction->GetByteCodeBase(),mpCurrentFunction->mpCIH,mpCurrentFunction->GetByteCodeSize(),character);
   mpCurrentFunction->CleanupAfterExecution(&state);
   mpCurrentFunction->Release();
   thisStack.pop();
  }
  mpCurrentFunction=pPrevFunction;
  constantPool=savedPool;
 } else {
  stack.rva006E3AA0(nParams);
  stack.PushNoInc(gpUndefinedValue);
 }
 int nStackElementsPost=stack.count;
 if(unwind){if(nStackElementsPost>nStackElementsPre)stack.rva006E3AA0(nStackElementsPost-nStackElementsPre);}
 else if(!(nStackElementsPost==nStackElementsPre || nStackElementsPost==nStackElementsPre+1)){g_bfmeAptAssertAtE17734("nStackElementsPost == nStackElementsPre || nStackElementsPost == (nStackElementsPre+1)","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x837);if(g_bfmeAptBreakOnAssertAtDDC01C){__debugbreak();}}
}
