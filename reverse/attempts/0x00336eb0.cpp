// ?rva002E9AA0ParseObjectStatusEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.95 date=2026-10-20
// stlport
// cl: /O1 /EHsc /MD /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// BF1 9cbfb551 LuaScriptEngineParseModelConditionEvent.cpp semantic source.
#include "ascii_string.h"
#include <vector>
#include <string.h>
class BfmeLexEAN {public: char *getTailEAN();};
class XmlNameSlotList {public:int count();int finish();const char *tagAt(int);const char *nameAt(int);};
class INIException {public:char *mFailureMessage;};
struct ConditionWords {unsigned long words[4];
 ConditionWords(){memset(words,0,sizeof(words));}
 void flip(){for(unsigned i=0;i<4;++i)words[i]=~words[i];}
};
class Rva003339CE {public:void rva00334506(AsciiString);};
class BfmeObject872Header {public:char bytes[16];};
class Rva00332FC1 {public:
 Rva00332FC1(const BfmeObject872Header &,const BfmeObject872Header &);
 bool rva00332FE7(const Rva00332FC1 &)const;
 unsigned char bytes[36];
};
struct EventFlagEntry {void setKeyFromName(const char *);};
struct Rva00336AECElement {unsigned char bytes[36];};
extern template void _STL::vector<Rva00336AECElement>::push_back(const Rva00336AECElement &);
class LuaScriptEngine {public:void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *);
 private:char pad[0xC8];_STL::vector<Rva00336AECElement> m_objectStatusEvents;
};
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int);
class LuaParseLog {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual LuaParseLog *write(const char *);
 virtual void v15();virtual void v16();virtual void v17();virtual void v18();
 virtual LuaParseLog *end(int);
};
class LuaParseDebug {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();
 virtual void v16();virtual void v17();virtual void v18();virtual void v19();
 virtual void v20();virtual void v21();virtual void v22();virtual void v23();
 virtual void v24();virtual void v25();virtual void v26();
 virtual LuaParseLog *line(int,int,int);
};
class Debug;
extern Debug *theDebug;
void LuaScriptEngine::rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser)
{
 AsciiString name;
 for(int i=0;i<reinterpret_cast<XmlNameSlotList *>(parser)->count();++i) {
  if(strcmp(reinterpret_cast<XmlNameSlotList *>(parser)->tagAt(i),"Name")==0)
   reinterpret_cast<StringBase<char> *>(&name)->set(reinterpret_cast<XmlNameSlotList *>(parser)->nameAt(i));
 }
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()!=1)return;
 bool isConditions=strcmp(parser->getTailEAN(),"Conditions")==0;
 if(!isConditions)return;
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()!=3)return;
 const char *text=parser->getTailEAN();
 bool found=false;
 try {
  AsciiString conditions(text);
  ConditionWords required,excluded;
  excluded.flip();
  reinterpret_cast<Rva003339CE *>(&required)->rva00334506(conditions);
  reinterpret_cast<Rva003339CE *>(&excluded)->rva00334506(conditions);
  excluded.flip();
  Rva00332FC1 record(*reinterpret_cast<BfmeObject872Header *>(&required),*reinterpret_cast<BfmeObject872Header *>(&excluded));
  reinterpret_cast<EventFlagEntry *>(&record)->setKeyFromName(name.str());

  for(Rva00336AECElement *it=m_objectStatusEvents.begin();it!=m_objectStatusEvents.end();++it) {
   if(record.rva00332FE7(*reinterpret_cast<Rva00332FC1 *>(it))) {found=true;break;}
  }
  if(!found)m_objectStatusEvents.push_back(*reinterpret_cast<Rva00336AECElement *>(&record));
  else return;
 } catch(...) {}
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()==2)reinterpret_cast<XmlNameSlotList *>(parser)->finish();
}
