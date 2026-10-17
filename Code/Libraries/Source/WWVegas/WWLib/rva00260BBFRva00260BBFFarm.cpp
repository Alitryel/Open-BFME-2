// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// Native260BBF..260DCF RET8 and WBDA5180 callgraph prove same subtitle6C receiver.
// Retail reconstructed word scan/measurement/record lifetimes; original method spelling unknown.
#include "unicode_string.h"
#include <vector>
#include <algorithm>
// bfme link decl-only begin
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
// bfme link decl-only end
struct Rva00260B88Element
{
 int a[2];
 
}
;
class Rva0025FB9B
{
 public:void rva0025FB9B();
 
}
;
class GameFont;
class ModuleData;
struct BfmeStringRecord005DDD40 
{
 UnicodeString text;
 unsigned word;
 
}
;
class DisplayString

{
 public:
 virtual void s00();
 virtual void setText(UnicodeString s);
 virtual void s02();
 virtual void s03();
 virtual void s04();
 virtual void s05();
 virtual void setFont(GameFont *font);
 virtual void s07();
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void getSize(int *w, int *h);
 
}
;
class DisplayStringManager

{
 public:
 virtual void s00();
 virtual void s01();
 virtual void s02();
 virtual void s03();
 virtual void s04();
 virtual void s05();
 virtual void s06();
 virtual void s07();
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual DisplayString *newDisplayString();
 virtual void freeDisplayString(DisplayString *s);
 
}
;
extern DisplayStringManager *TheDisplayStringManager;
class BfmeItemKA;
extern BfmeItemKA **g_bfmeBegKA, **g_bfmeEndKA;
struct Rva00260826 : _STL::_Vector_base<BfmeStringRecord005DDD40,_STL::allocator<BfmeStringRecord005DDD40> > 
{
 __forceinline Rva00260826():_STL::_Vector_base<BfmeStringRecord005DDD40,_STL::allocator<BfmeStringRecord005DDD40> >(_STL::allocator<BfmeStringRecord005DDD40>())
 {
  
 }
 ~Rva00260826();
 
}
;
class SubTitleWindow

{
 public:
 ~SubTitleWindow();
 void rva00260BBF(const StringBase<unsigned short>&, unsigned);
 SubTitleWindow(GameFont *font, float f2, float f3, int i4, int count, int i6, int i7);
 private:
 DisplayString *m_00;
 GameFont *m_04;
 Rva00260826 m_vec;
 int m_14;
 int m_18;
 int m_1c;
 int m_20;
 int m_24;
 int m_28;
 int m_2c;
 int m_30;
 DisplayString **m_34;
 DisplayString **m_38;
 int m_3c;
 int m_40;
 float m_44;
 float m_48;
 float m_4c;
 float m_50;
 float m_54;
 float m_58;
 float m_5c;
 float m_60;
 float m_64;
 float m_68;
 
}
;
// SubTitleWindow::SubTitleWindow is rowed in its home unit; this copy was a duplicate definition.
// SubTitleWindow::~SubTitleWindow is rowed in its home unit; this copy was a duplicate definition.
__forceinline bool SubtitleSeparator(unsigned short c)
{
 return c==0x20||c==0x95;
 
}
void SubTitleWindow::rva00260BBF(const StringBase<unsigned short>&text,unsigned color)
{
 int available=(int)(m_64-m_5c);
 const unsigned short*p=text.str();
 while(*p)
 {
  const unsigned short*start=p;
  while(*start&&SubtitleSeparator(*start))++start;
  p=start;
  const unsigned short*lastBreak=start;
  if(*p==0)continue;
  do
  {
   while(*p&&(( *p==0x20)||(*p==0x95)))
   {
    ++p;
   }
   if(!*p)goto subtitle_word_done;
   while(*p&&!( *p==0x20||*p==0x95)&&*p!='\n')++p;
   subtitle_word_done:
   UnicodeString measured(start,(int)(p-start));
   m_00->setText(measured);
   int w,h;
   m_00->getSize(&w,&h);
   if(w<=available)
   {
    lastBreak=p;
    if(*p&&*p!='\n')continue;
    
   }
   if(lastBreak==start)lastBreak=p;
   
   {
    UnicodeString line((const UnicodeString&)text,(int)(start-text.str()),(int)(lastBreak-start));
    BfmeStringRecord005DDD40 value=
    {
     line,color
    }
    ;
    ((_STL::vector<Rva00260B88Element>*)&m_vec)->push_back(*(const Rva00260B88Element*)&value);
    
   }
   if(*p=='\n')++p;
   if(SubtitleSeparator(*lastBreak))p=lastBreak;
   break;
   
  }
  while(*p);
  
 }
 
 {
  UnicodeString blank;
  BfmeStringRecord005DDD40 value=
  {
   blank,color
  }
  ;
  ((_STL::vector<Rva00260B88Element>*)&m_vec)->push_back(*(const Rva00260B88Element*)&value);
  
 }
 ((Rva0025FB9B*)this)->rva0025FB9B();
 
}
