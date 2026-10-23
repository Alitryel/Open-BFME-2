from lab import Lab
import re,itertools
l=Lab('2af236',261,source='build/crack-g/0x002af236/lifetimes/best.cpp',label='scope2');s=l.base
# Natural map idiom uses a const_iterator on the saving branch; its converting
# constructor keeps the two-word begin copy that an iterator initializer elides.
for style in ('init','assign','named'):
 t=s.replace('ExistingNameTable::iterator it;','ExistingNameTable::const_iterator it;')
 if style=='init':t=t.replace('ExistingNameTable::const_iterator it;\n  ExistingNameTable::iterator initial=view->begin(); it=initial;','ExistingNameTable::const_iterator it(view->begin());')
 if style=='assign':t=t.replace('ExistingNameTable::iterator initial=view->begin(); it=initial;','it=view->begin();')
 l.test('const_iterator_'+style,t)
# With real begin visible, two-word copy comes from conversion to const_iterator.
for kind in ('iterator','const_iterator'):
 for st in ('assign','direct'):
  t=s.replace(' template<> ExistingNameTable::iterator ExistingNameTable::begin();','').replace('ExistingNameTable::iterator it;','ExistingNameTable::'+kind+' it;')
  if st=='direct':t=t.replace('ExistingNameTable::'+kind+' it;\n  ExistingNameTable::iterator initial=view->begin(); it=initial;','ExistingNameTable::'+kind+' it(view->begin());')
  l.test('visible_begin_'+kind+st,t)
# Loop local name/value lifetime must end before incrementing the cursor.
for kind in ('','{'):
 for decl in ('before','after'):
  t=s
  if kind:t=t.replace('   AsciiString name(it->first);','   { AsciiString name(it->first);').replace('   xfer->real(&values.value);','   xfer->real(&values.value); }')
  if decl=='before':t=t.replace('  AsciiString name;','  float value;\n  AsciiString name;').replace('   float value;','')
  l.test('loop_scope_'+kind+decl,t)
l.done()
