from lab import Lab
from pathlib import Path
import re,itertools
l=Lab('2af236',261,source='build/crack-g/0x002af236/main/best.cpp',label='lifetimes');s=l.base
# The native frame packs the returned iterator and save/load scalar values.
# Vary only legal lexical lifetimes of the returned begin temporary and value.
for bind in [
 '{ExistingNameTable::iterator initial=view->begin(); it=initial;}',
 'const ExistingNameTable::iterator initial=view->begin(); it=initial;',
 'ExistingNameTable::iterator initial=view->begin(); it=static_cast<const ExistingNameTable::iterator&>(initial);',
 'ExistingNameTable::iterator initial=view->begin(); it.operator=(initial);']:
 l.test('iterator_lifetime_'+bind,s.replace('ExistingNameTable::iterator initial=view->begin(); it=initial;',bind))
# Save count and load value are path-exclusive and non-destructible. Hoisting
# their declarations expresses that scope without artificial alignment/padding.
for where in ('all','save','load'):
 for constref in (False,True):
  t=s
  if where=='all':
   t=t.replace(' if (xfer->saving()) {',' unsigned int count; float value;\n if (xfer->saving()) {').replace('unsigned int count = reinterpret_cast','count = reinterpret_cast').replace('unsigned int count = 0;','count=0;').replace('float value = *reinterpret_cast','value = *reinterpret_cast').replace('   float value;','')
  elif where=='save':
   t=t.replace('  ExistingNameTable *view','  float value;\n  ExistingNameTable *view').replace('   float value =','   value =')
  else:
   t=t.replace('  AsciiString name;\n  for','  float value;\n  AsciiString name;\n  for').replace('   float value;','')
  if constref:t=t.replace('ExistingNameTable::iterator initial=view->begin();','const ExistingNameTable::iterator &initial=view->begin();')
  l.test('scalar_scope_'+where+str(constref),t)
# Count/value wrapper lifetime (same two scalar words already in target) as in
# successful water and other snapshot transfers; no added representation bytes.
for order in (0,1):
 t=s.replace('  unsigned int count = reinterpret_cast<NameFloatTablePrefix *>(table)->count;', '  struct SaveValues {'+('unsigned int count;float value;' if order==0 else 'float value;unsigned int count;')+'} values; values.count=reinterpret_cast<NameFloatTablePrefix *>(table)->count;')
 pos=t.index(' } else {',t.index('void Player::'))
 save=t[:pos].replace('xfer->word(&count)','xfer->word(&values.count)').replace('float value =','values.value =').replace('xfer->real(&value)','xfer->real(&values.value)')
 l.test('save_record_'+str(order),save+t[pos:])
l.done()
