from lab import Lab
from pathlib import Path
l=Lab('2af236',261,source='build/crack-g/0x002af236/lifetimes/best.cpp',label='count_lifetime');s=l.base
# Xfer sees the count only during its word transfer. End that scalar lifetime
# before constructing the two-word begin return; scope the float per element.
for source in [Path('build/crack-g/0x002af236/main/best.cpp').read_text(),s]:
 for form in ('scope','helper'):
  t=source
  if 'struct SaveValues' in t:
   t=t.replace('struct SaveValues {float value;unsigned int count;} values; values.count=reinterpret_cast<NameFloatTablePrefix *>(table)->count;','unsigned int count=reinterpret_cast<NameFloatTablePrefix *>(table)->count;').replace('&values.count','&count').replace('values.value =','float value =').replace('&values.value','&value')
  if form=='scope':
   t=t.replace('  unsigned int count = reinterpret_cast','  { unsigned int count = reinterpret_cast').replace('  unsigned int count=reinterpret_cast','  { unsigned int count=reinterpret_cast').replace('xfer->word(&count);\n  ExistingNameTable','xfer->word(&count); }\n  ExistingNameTable',1)
  else:
   helper='static __forceinline void transferCount(NameMapXferView*x, unsigned int c){ x->word(&c); }\n'
   t=t.replace('void Player::rva002AF236',helper+'void Player::rva002AF236',1).replace('xfer->word(&count);','transferCount(xfer,count);',1)
  for init in ['ExistingNameTable::iterator initial=view->begin(); it=initial;','{ExistingNameTable::iterator initial=view->begin(); it=initial;}','it=view->begin();']:
   u=t.replace('ExistingNameTable::iterator initial=view->begin(); it=initial;',init)
   l.test('count_'+str(len(source))+form+init,u)
l.done()
