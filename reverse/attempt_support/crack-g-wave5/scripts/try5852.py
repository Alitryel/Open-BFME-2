from lab import Lab
import re
l=Lab('5852df',1556);s=l.base
# The rowed Object layer getter is a call-free 20-byte leaf. Visibility can
# change the caller's clobber analysis without altering its ABI.
getter='''__declspec(noinline) inline int Object::rva0028B511() const {
 if (*(const unsigned char*)((const char*)this+0x48c)) return 16;
 return *(const int*)((const char*)this+0x40c);
}
'''
for mask in range(1,8):
 t=s
 if mask&1: t=t.replace('Bool HordeMeleeFormation::findMeleeAttackPosition',getter+'\nBool HordeMeleeFormation::findMeleeAttackPosition')
 if mask&2: t=t.replace('const Coord3D * volatile victimPos','const Coord3D *victimPos')
 if mask&4: t=t.replace('const volatile Int &ringLimit=rings','const Int &ringLimit=rings')
 l.test('visible_layer_'+str(mask),t)
# Lexical lifetime of the independent main-ring counters vs the escape-ring
# counters controls reuse; test hoisting the declarations within their scopes.
for which in (0,1,2):
 t=s;pat='for (Int r = 1; r <= '+('2 && blocked' if which==0 else 'ringLimit')+'; r++)'
 t=t.replace(pat,'Int r, i, j;\n '+pat.replace('Int r','r'),1)
 start=t.find('Int r, i, j;');a=t[:start];b=t[start:]
 if which<2:
  b=b.replace('for (Int i = -r;', 'for (i = -r;',1).replace('for (Int j = -r;', 'for (j = -r;',1)
 else:
  b=b.replace('for (Int i = -r;', 'for (i = -r;').replace('for (Int j = -r;', 'for (j = -r;')
 l.test('counter_scope_'+str(which),a+b)
l.done()
