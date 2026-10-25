// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native fullC838F..C8492 CDECL animation-record parser and tableBCA560.
// ZH W3DModelDraw::parseAnimation supplies the semantic lead; BFME2 uses
// nested eleven-field INI parsing and a64B record (existing copy/dtor/ctor).
// Exact field tokens, offsets and callback pointers establish animation
// behavior; retained Bfme neutral record identity and original meanings
// only where table tokens prove them. All enum/token data explicitly owned.
// Native unused76B zeroed stack area retained without a class identity claim.
// size()!=0 gives native masked byte distance; barriers keep both separate
// front-pointer loads across the string calls instead of adding ESI save.
#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord000BDF17 {
 _STL::vector<AsciiString>names;AsciiString text0,text1;
 float word14,word18;int word1C;float word20,word24,word28;
 bool flag2C,flag2D;int word30;float word34,word38;bool flag3C;
 BfmeVectorRecord000BDF17(const AsciiString&,float);
 BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17&);
 ~BfmeVectorRecord000BDF17();
};

#include <string.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class INI;typedef void(*INIFieldParseProc)(INI*,void*,void*,const void*);
struct FieldParse{const char*token;INIFieldParseProc parse;const void*userData;int offset;};
class INI{public:static void parseAsciiStringVector(INI*,void*,void*,const void*);static void parseIndexList(INI*,void*,void*,const void*);static void parseReal(INI*,void*,void*,const void*);static void parseBool(INI*,void*,void*,const void*);static void parseInt(INI*,void*,void*,const void*);AsciiString getNextAsciiString();void initFromINI(void*,const FieldParse*);};
extern const FieldParse BfmeAnimationRecordFields[];
struct Rva000C838FOwner{char prefix[0x50];_STL::vector<BfmeVectorRecord000BDF17>animations;};
namespace _STL{template<>void vector<BfmeVectorRecord000BDF17>::push_back(const BfmeVectorRecord000BDF17&);}
void Rva000C838FParse(INI*ini,void*instance,void*store,const void*userData){
 AsciiString token=ini->getNextAsciiString();
 AsciiString original(token);((StringBase<char> &)token).toLower();
 BfmeVectorRecord000BDF17 record(token,0.0f);record.text1=original;
 unsigned char scratch[76];memset(scratch,0,sizeof scratch);
 if((unsigned)userData==1)record.word1C=2;
 ini->initFromINI(&record,BfmeAnimationRecordFields);
 if(record.word30<0)record.word30=0;
 if(record.word30>100)record.word30=100;
 if(record.names.size()!=0&&(_ReadWriteBarrier(),!record.names.front().isEmpty())&&(_ReadWriteBarrier(),!record.names.front().isNone()))
  ((Rva000C838FOwner*)instance)->animations.push_back(record);
}

class ModelConditionInfo{public:static void parseRealRange(INI*,void*,void*,const void*);};
extern const char g_animationModeManual[]="MANUAL";
extern const char g_animationModeLoop[]="LOOP";
extern const char g_animationModeOnce[]="ONCE";
extern const char g_animationModeLoopPingPong[]="LOOP_PINGPONG";
extern const char g_animationModePlayToFrame[]="PLAY_TO_FRAME";
extern const char g_animationModeLoopBackwards[]="LOOP_BACKWARDS";
extern const char g_animationModeOnceBackwards[]="ONCE_BACKWARDS";
const char*animationModeNames[]={g_animationModeManual,g_animationModeLoop,g_animationModeOnce,g_animationModeLoopPingPong,g_animationModePlayToFrame,g_animationModeLoopBackwards,g_animationModeOnceBackwards,0};
extern const char g_animationNameField[]="AnimationName";
extern const char g_animationModeField[]="AnimationMode";
extern const char BfmeAnimationField2[]="Distance";
extern const char g_animationBlendTimeField[]="AnimationBlendTime";
extern const char g_animationMustCompleteBlendField[]="AnimationMustCompleteBlend";
extern const char g_animationSpeedFactorRangeField[]="AnimationSpeedFactorRange";
extern const char g_useWeaponTimingField[]="UseWeaponTiming";
extern const char g_animationPriorityField[]="AnimationPriority";
extern const char g_fadeBeginFrameField[]="FadeBeginFrame";
extern const char g_fadeEndFrameField[]="FadeEndFrame";
extern const char g_fadingInField[]="FadingIn";
extern const FieldParse BfmeAnimationRecordFields[]={{g_animationNameField,INI::parseAsciiStringVector,0,0},{g_animationModeField,INI::parseIndexList,animationModeNames,28},{BfmeAnimationField2,INI::parseReal,0,20},{g_animationBlendTimeField,INI::parseReal,0,32},{g_animationMustCompleteBlendField,INI::parseBool,0,44},{g_animationSpeedFactorRangeField,ModelConditionInfo::parseRealRange,0,0},{g_useWeaponTimingField,INI::parseBool,0,45},{g_animationPriorityField,INI::parseInt,0,48},{g_fadeBeginFrameField,INI::parseReal,0,52},{g_fadeEndFrameField,INI::parseReal,0,56},{g_fadingInField,INI::parseBool,0,60},{0,0,0,0}};
