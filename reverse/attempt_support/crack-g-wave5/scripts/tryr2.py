from lab import Lab
import re
l=Lab('953b3',1134);s=l.base
s=re.sub(r'#include "(?:\.\./)+Libraries/Include/','\x23include "Code/Libraries/Include/',s).replace('// cl:','// cl: /I.',1)
l.test('resolved_includes',s)
# The implicit RGBColor copy is three words; retain that legitimate aggregate
# copy while introducing a real derived local lifetime (no artificial padding).
for dtor in ('','~ColorLocal() {}'):
 for member in (False,True):
  definition=('struct ColorLocal { RGBColor value; '+dtor+' };' if member else 'struct ColorLocal : RGBColor { '+dtor+' };')
  t=s.replace('void Gen006E2310::rva000953B3()',definition+'\nvoid Gen006E2310::rva000953B3()',1)
  if member:
   t=t.replace('RGBColor color = m_30;','ColorLocal owned; RGBColor &color = owned.value; color=m_30;')
  else:t=t.replace('RGBColor color = m_30;','ColorLocal owned; RGBColor &color = owned; color=m_30;')
  l.test('real_color_lifetime_'+str(member)+dtor,t)
# Exact aggregate assignment still owns the load; reference return before the
# copy permits the existing state value to determine the address lifetime.
for form in ['const RGBColor &from=m_30; RGBColor color=from;', 'RGBColor color; const RGBColor *from=&m_30; color=*from;']:
 l.test('copy_local_'+form,s.replace('RGBColor color = m_30;',form))
l.done()
l=Lab('32e02b',1097);s=l.base.replace('// cl:','// cl: /O1 /G7 /arch:SSE',1)
l.test('explicit_flags',s)
# Last loop repeatedly recomputes the same indexed team entry. Use an actual
# iterator-style reference to express the one record lifetime on this path.
old='''\tfor (i = m_teamrec.entryRaw(0).m_next; i != 0; i = m_teamrec.entryRaw(i).m_next) {
\t\tif (m_teamrec.entryRaw(i).m_free != 0)
\t\t\tcontinue;
\t\tDict *tdict = &m_teamrec.entryRaw(i).m_dict;'''
for accessor in ['m_teamrec.entryRaw(i)','m_teamrec.m_teams[i]']:
 for style in ['ptr','ref']:
  typ='TeamInfoRec' # replaced with actual nested record after inspection below
  for prefix in ('','const '):
   # derive m_teams pointee from its declaration
   m=re.search(r'(\w+)\s*\*\s*m_teams\s*;',s)
   if not m:continue
   typ=m.group(1)
   if prefix: continue
   decl=typ+(' *entry = &' if style=='ptr' else ' &entry = ')+accessor+';'
   expr='entry->' if style=='ptr' else 'entry.'
   new='''\tfor (i = m_teamrec.entryRaw(0).m_next; i != 0; i = m_teamrec.entryRaw(i).m_next) {\n'''+decl+'\n if ('+expr+'m_free != 0) continue;\n Dict *tdict=&'+expr+'m_dict;'
   if old not in s:raise RuntimeError('loop not located')
   l.test('record_'+accessor+style,s.replace(old,new))
# A small inline accessor retaining the Dict subobject is source-level CSE.
for qual in ('','const'):
 t=s.replace('Dict *tdict = &m_teamrec.entryRaw(i).m_dict;','Dict *'+qual+' tdict = &m_teamrec.m_teams[i].m_dict;')
 l.test('dict_direct_'+qual,t)
l.done()
