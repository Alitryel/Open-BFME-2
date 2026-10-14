// ?rva005B6A5E@Rva005B6A5E@@QAEXH@Z
// partial score=0.93 date=2026-10-14
// cl: /Ob2 /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB157DCE0 names Manager::PopulateHeroList; native5B6755..5B692F.
// Target prefixes and the comparator words are measured from retail.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class GameWindow;
class Image {public:char prefix[0x24];int width;};
class ImageCollection {public:const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
enum NameKeyType;
class CreateAHeroData {public:unsigned rva00408109(const NameKeyType *);char prefix[8];UnicodeString name;unsigned major,minor;char gap[0x48-0x14];bool isDefault;};
class Rva0040A3F9 {public:unsigned *first,*last,*limit;bool rva0040A441(CreateAHeroData *);};
class CreateAHeroManager {public:Rva0040A3F9 *rva0021F797();const AsciiString &GetSubClassNameTag(unsigned,unsigned);};
extern CreateAHeroManager *TheCreateAHeroManager;
class GameTextInterface {public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)
#undef V
virtual UnicodeString fetchLabel(const AsciiString &,bool *exists=0);
virtual UnicodeString fetchByName(const char *,bool *exists=0);
};
extern GameTextInterface *TheGameText;
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetSelected(GameWindow *,int);
int GadgetListBoxAddEntryImage(GameWindow *,const Image *,int,int,int,int,bool,int);
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
class Rva005B61B3 {public:int key0,key1;bool rva005B61B3(void *,void *);};
struct Rva005B61B3Less: Rva005B61B3 {Rva005B61B3Less(int a,int b){key0=a;key1=b;}};
namespace _STL {template<class I,class C> void sort(I,I,C);}
struct HeroListScreenPrefix {char prefix[0x284];UnicodeString selectedName;};
struct Rva005B5C70Box {void Run(int);};
extern "C" void __cdecl free(void *);
struct HeroListScratch {
 unsigned *first,*last,*limit;
 __forceinline HeroListScratch(const Rva0040A3F9 &source){reinterpret_cast<_STL::vector<unsigned> *>(this)->_STL::vector<unsigned>::vector(*reinterpret_cast<const _STL::vector<unsigned> *>(&source));}
 __forceinline ~HeroListScratch(){if(first)free(first);}
};
class AptCreateAHero {public:class Manager;};
class AptCreateAHero::Manager {public:
 char word0[4];HeroListScreenPrefix *screen;GameWindow *heroWindow,*otherWindow;
 CreateAHeroData *selectedHero;int word14;Rva005B61B3Less order;
 void rva005B6755();void rva005B6A05();void rva005B5F2E();
};
void AptCreateAHero::Manager::rva005B6755() {
 if(TheCreateAHeroManager) {
  Rva0040A3F9 *list=TheCreateAHeroManager->rva0021F797();
  unsigned count=list->last-list->first;
  HeroListScratch heroes(*list);
  GadgetListBoxReset(heroWindow);
  const Image *image=TheMappedImageCollection->findImageByName(AsciiString("AptUserMapMaxConquered"));
  int imageSize=(int)(image?(float)image->width*0.8f:0.0f);
  const UnicodeString *selectedName=&screen->selectedName;
  int selectedIndex=0;
  _STL::sort(reinterpret_cast<void **>(heroes.first),reinterpret_cast<void **>(heroes.last),Rva005B61B3Less(order.key0,order.key1));
  for(unsigned i=0;i<count;++i) {
   CreateAHeroData *hero=reinterpret_cast<CreateAHeroData *>(heroes.first[i]);
   if(!hero->isDefault && image)GadgetListBoxAddEntryImage(heroWindow,image,i,0,imageSize,imageSize,true,-1);
   GadgetListBoxAddEntryText(heroWindow,hero->name,-1,i,1,true);
   unsigned minor=hero->minor,major=hero->major;
   UnicodeString label=TheGameText->fetchLabel(TheCreateAHeroManager->GetSubClassNameTag(major,minor));
   GadgetListBoxAddEntryText(heroWindow,label,-1,i,2,true);
   GadgetListBoxSetItemData(heroWindow,(void *)hero,i,0);
   if(selectedName->compare(hero->name)==0)selectedIndex=i;
  }
  GadgetListBoxSetSelected(heroWindow,selectedIndex);
  reinterpret_cast<Rva005B5C70Box *>(this)->Run(0);
 }
}
void AptCreateAHero::Manager::rva005B6A05() {
 if(selectedHero) {
  Rva0040A3F9 *list=TheCreateAHeroManager->rva0021F797();
  list->rva0040A441(selectedHero);
  selectedHero=0;
  rva005B6755();
 }
}

class Rva00406E53 {public:int rva00406E53();};
class Rva00406E65 {public:int rva00406E65(unsigned);};
class Rva0040BAD0 {public:int rva0040AAF8(int);};
class Rva0040AAD5;
extern Rva0040AAD5 *g_00E02F74;
struct StatRecord {char prefix[0x54];AsciiString label;};
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void GadgetListBoxJustifyEntry(GameWindow *,int,int,int);
void AptCreateAHero::Manager::rva005B5F2E() {
 if(otherWindow) {
  int oldTop=GadgetListBoxGetTopVisibleEntry(otherWindow);
  GadgetListBoxReset(otherWindow);
  CreateAHeroData *hero=reinterpret_cast<CreateAHeroData *>((char *)screen+0x27c);
  for(unsigned i=0;i<(unsigned)reinterpret_cast<Rva00406E53 *>(hero)->rva00406E53();++i) {
   int key=reinterpret_cast<Rva00406E65 *>(hero)->rva00406E65(i);
   StatRecord *record=reinterpret_cast<StatRecord *>(reinterpret_cast<Rva0040BAD0 *>(g_00E02F74)->rva0040AAF8(key));
   if(record) {
    unsigned count=hero->rva00408109(reinterpret_cast<const NameKeyType *>(record));
    UnicodeString text;
    text.format(L"%d",count);
    int row=GadgetListBoxAddEntryText(otherWindow,TheGameText->fetchLabel(record->label),-1,-1,0,true);
    GadgetListBoxAddEntryText(otherWindow,text,-1,row,1,true);
    GadgetListBoxJustifyEntry(otherWindow,row,1,2);
   }
  }
  GadgetListBoxSetTopVisibleEntry(otherWindow,oldTop);
 }
}

// Retail 0x005B6A5E, 309 bytes: the hero list's delete step. With a hero
// selected (a default hero only while the cleared-global test passes) it asks
// "GUI:AreYouSureDelete" through the two-button prompt 0x00437F61 whose answer
// callbacks are this screen's 0x005B6A05 (delete the kept hero) and 0x005B5B07,
// then remembers the hero. The callbacks are bound by raw code address
// through the delegate holder 0x00579E47.
void __cdecl GadgetListBoxGetSelected(GameWindow *, int *);
void *GadgetListBoxGetItemData(GameWindow *, int, int);
extern unsigned char g_rva005B5C02Flag;
struct TargetRef00217D4C {void *vtbl;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct DelegateDesc {void *m_object;void *m_method;};
static __forceinline DelegateDesc MakeDelegate(void *object,void *method){DelegateDesc d;d.m_object=object;d.m_method=method;return d;}
class Rva00579E47 {public:Rva00579E47(const DelegateDesc &);private:void *m_ptr;};
struct Rva004F6986Member {
 TargetRef00217D4C *ptr;
 __forceinline Rva004F6986Member(DelegateDesc desc) {
  reinterpret_cast<Rva00579E47 *>(this)->Rva00579E47::Rva00579E47(desc);
 }
 Rva004F6986Member(const Rva004F6986Member &o):ptr(o.ptr){if(ptr)++ptr->references;}
 ~Rva004F6986Member(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
class Rva004C5DD0 {public:Rva004C5DD0(const Rva004C5DD0 &other);private:TargetRef00217D4C *a,*b;};
struct Rva0044BA4E : Rva004C5DD0 {
 Rva0044BA4E(Rva004F6986Member,Rva004F6986Member);
 ~Rva0044BA4E();
};
struct Rva0044BF40 {
 TargetRef00217D4C *ptr;
 Rva0044BF40(Rva004C5DD0 pair);
 Rva0044BF40(const Rva0044BF40 &o):ptr(o.ptr){if(ptr)++ptr->references;}
 ~Rva0044BF40(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
namespace n0044BF40 {extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0044BF40);}
class Rva005B5B07DwordClearer {public:void clear();};
template <class M> static __forceinline void *codeAddress(M method) {union {M m;void *p;} u;u.m=method;return u.p;}
class Rva005B6A5E {
public:
 void rva005B6A5E(int unused);
 char pad0[8];GameWindow *list;char pad0c[4];CreateAHeroData *selectedHero;
};
void Rva005B6A5E::rva005B6A5E(int unused) {
 int selected;
 GadgetListBoxGetSelected(list,&selected);
 if(selected<0)return;
 CreateAHeroData *hero=(CreateAHeroData *)GadgetListBoxGetItemData(list,selected,0);
 if(hero==0)return;
 if(hero->isDefault&&g_rva005B5C02Flag==0)return;
 UnicodeString title=TheGameText->fetchByName("GUI:DeleteFile");
 UnicodeString text=TheGameText->fetchByName("GUI:AreYouSureDelete");
 n0044BF40::Rva00437F61(2,title,text,Rva0044BF40(Rva0044BA4E(Rva004F6986Member(MakeDelegate(this,codeAddress(&AptCreateAHero::Manager::rva005B6A05))),Rva004F6986Member(MakeDelegate(this,codeAddress(&Rva005B5B07DwordClearer::clear))))));
 selectedHero=hero;
}
