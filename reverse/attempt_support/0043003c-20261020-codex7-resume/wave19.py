variants=[]
for n in range(64):
 s=BASE
 form=n&3
 if form:
  if form==1:decl='__declspec(noinline) Drawable *getDrawable() const { return *(Drawable *const *)((const char *)this + 0x84); }'
  elif form==2:decl='Drawable *getDrawable() const { return *(Drawable *const *)((const char *)this + 0x84); }'
  else:decl='Drawable *getDrawable() const;';s=s.replace('class Rva0029C138 {','__declspec(noinline) Drawable *Object::getDrawable() const { return *(Drawable *const *)((const char *)this + 0x84); }\nclass Rva0029C138 {')
  s=s.replace('Drawable *getDrawable() const;',decl)
 if n&4:
  s=s.replace('Rva004D6BCD *rva002AA176(Int);','__declspec(noinline) Rva004D6BCD *rva002AA176(Int i) { return i >= 0 && i < 10 ? ((Rva004D6BCD *const *)((const char *)this + 0x708))[i] : 0; }')
 if n&8:s=s.replace(old,direct)
 if n&16:s=s.replace('virtual UnsignedInt slot120();','virtual UnsignedInt slot120() { return *(const UnsignedInt *)((const char *)this + 0x570); }')
 if n&32:
  s=s.replace('const VecObjectPtr &objects = *(const VecObjectPtr *)((Gen_0018BC70 *)squad)->bfmeCompact(FALSE);','const VecObjectPtr *objectPtr = (const VecObjectPtr *)((Gen_0018BC70 *)squad)->bfmeCompact(FALSE);\n        const VecObjectPtr &objects = *objectPtr;')
 variants.append((f'w19_{n:02d}',s))
