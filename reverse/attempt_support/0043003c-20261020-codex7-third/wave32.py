variants=[]
for n in range(64):
 s=fn;st=s.index('    if ( now - m_lastGroupSelTime');en=s.index('    else',st)
 branch=s[st:en]
 asserts=[]
 # True-arm facts follow from the actual dominating comparisons and range guard.
 if n&1:asserts.append('__assume(group == m_lastGroupSelGroup);')
 if n&2:asserts.append('__assume(m_lastGroupSelGroup >= 0);')
 if n&4:asserts.append('__assume(m_lastGroupSelGroup < 10);')
 if n&8:asserts.append('__assume(group >= 0 && group < 10);')
 if asserts:
  branch=branch.replace('     Player *player = localPlayer43003C();','     '+' '.join(asserts)+'\n     Player *player = localPlayer43003C();',1)
 if n&16:branch=branch.replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(group)')
 s=s[:st]+branch+s[en:]
 if n&32:
  s=s.replace('    // check for double-press to jump view','    __assume(group >= 0 && group < 10);\n    // check for double-press to jump view',1)
 variants.append((f'w32_{n:02d}',BASE[:a]+s+BASE[b:]))
