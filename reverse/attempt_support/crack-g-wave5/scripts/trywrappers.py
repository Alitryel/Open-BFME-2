from lab import Lab
from pathlib import Path
import re
l=Lab('002af236',261,source='build/crack-g/0x002af236/lifetimes/best.cpp',label='map_wrapper');b=l.base
for typ in ['ExistingNameMap','ExistingNameTable']:
 for decl in ['ExistingNameTable::iterator initial=view->begin(); it=initial;','it=view->begin();','ExistingNameTable::iterator initial = (view->begin()); it=initial;']:
  s=b.replace('ExistingNameTable *view = reinterpret_cast<ExistingNameTable *>(table);',f'{typ} *view = reinterpret_cast<{typ} *>(table);').replace('ExistingNameTable::iterator initial=view->begin(); it=initial;',decl)
  l.test(typ+decl,s)
l.done()
l=Lab('0026ef50',315,source='build/crack-g/0x0026ef50/main/best.cpp',label='vector_wrapper');b=l.base
s=b.replace('#include "ascii_string.h"','#include "ascii_string.h"\n#include <vector>\n// stlport')
s=re.sub(r'UpgradeTemplate \*\*m_prerequisitesBegin;[^\n]*\n\s*UpgradeTemplate \*\*m_prerequisitesEnd;[^\n]*\n\s*char m_pad24\[0x34 - 0x24\];','_STL::vector<UpgradeTemplate *> m_prerequisites;\n char m_pad28[0x34 - 0x28];',s)
s=s.replace('if (m_prerequisitesBegin != (object ? (__vref(m_prerequisitesEnd)) : (__vref(m_prerequisitesEnd))))','if (!m_prerequisites.empty())').replace('UpgradeTemplate **it = m_prerequisitesBegin; it != m_prerequisitesEnd','_STL::vector<UpgradeTemplate *>::const_iterator it = m_prerequisites.begin(); it != m_prerequisites.end()')
l.test('actual_vector',s)
l.test('vector_compare',s.replace('!m_prerequisites.empty()','m_prerequisites.begin() != m_prerequisites.end()'))
for init in ['int cost;\n\tif (player == 0)\n\t\treturn m_cost;\n cost=m_cost;','int cost = player ? m_cost : m_cost;\n\tif (player == 0)\n\t\treturn cost;']:
 l.test('defer_cost',s.replace('int cost = m_cost;\n\tif (player == 0)\n\t\treturn cost;',init))
l.done()
l=Lab('000470d5',216,source='build/crack-g/0x000470d5/binding/best.cpp',label='ownership');b=l.base
# Real RefCountPtr hierarchy as used by owner, preserving inline acquisition.
start=b.index('class BFME2ParticleTextureHandle\n');end=b.index('\nclass ShroudFilter',start)
old=b[start:end]
for dtor in ['~RefCountPtr() {if(Ptr)Ptr->Release_Ref();}','~RefCountPtr();']:
 for ctor in ['BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle&o):RefCountPtr<TextureClass>(o){}','']:
  rep='template<class T> class RefCountPtr {public: T*Ptr; RefCountPtr(const RefCountPtr&o):Ptr(o.Ptr){if(Ptr)++Ptr->m_refCount;} '+dtor+'};\nclass BFME2ParticleTextureHandle: public RefCountPtr<TextureClass> {public: '+ctor+'};\n'
  l.test('base_'+dtor+ctor,b[:start]+rep+b[end:])
l.done()
