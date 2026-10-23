# All offsets independently read from retail vtable 0x7FD410 leaf bodies.
getters=[
 ('UnsignedInt slot120()', 'return *(const UnsignedInt *)((const char *)this + 0x570);'),
 ('Int getSelectCount()', 'return *(const Int *)((const char *)this + 0x568);'),
 ('const DrawableList *getAllSelectedDrawables()', 'return (const DrawableList *)((const char *)this + 0x20);'),
 ('Bool isScrolling()', 'return *(const Bool *)((const char *)this + 0x7F8);'),
 ('const CommandButton *getGUICommand()', 'return *(const CommandButton *const *)((const char *)this + 0x238);'),
 ('Bool isQuitMenuVisible()', 'return *(const Bool *)((const char *)this + 0x810);')]
variants=[]
for n in range(64):
 s=BASE
 for bit,(decl,body) in enumerate(getters):
  if n&(1<<bit):
   needle='virtual '+decl+';'
   assert s.count(needle)==1,needle
   s=s.replace(needle,'virtual '+decl+' { '+body+' }')
 variants.append((f'w17_{n:02d}',s))
