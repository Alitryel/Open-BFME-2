variants=[]
for n in range(128):
 s=fn
 if n&1:s=s.replace(old,direct)
 if n&2:s=s.replace('    m_lastGroupSelTime = now;\n    m_lastGroupSelGroup = group;','    m_lastGroupSelGroup = group;\n    m_lastGroupSelTime = now;')
 if n&4:s=s.replace('Int group =','long group =')
 if n&8:s=s.replace('Bool valid','Int valid')
 if n&16:s=s.replace('m_lastGroupSelGroup','(*(Int *)((char *)this + 0xC))')
 if n&32:s=s.replace('m_lastGroupSelTime','(*(UnsignedInt *)((char *)this + 8))')
 if n&64:s=s.replace('Int count = objects.size();','const Int count = objects.size();').replace('for (Int i = 0; i < count; ++i)','for (Int i = 0; i != count; ++i)')
 variants.append((f'w15_{n:03d}',BASE[:a]+s+BASE[b:]))
