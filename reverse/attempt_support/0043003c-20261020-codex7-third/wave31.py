start=fn.index('    if ( now - m_lastGroupSelTime');end=fn.index('    else',start)
# Under the dominating equality these conditionals all select the same full-width value.
args=[
 'group == m_lastGroupSelGroup ? group : m_lastGroupSelGroup',
 'group == m_lastGroupSelGroup ? m_lastGroupSelGroup : group',
 'group != m_lastGroupSelGroup ? m_lastGroupSelGroup : group',
 'group != m_lastGroupSelGroup ? group : m_lastGroupSelGroup',
 'group < m_lastGroupSelGroup ? group : m_lastGroupSelGroup',
 'group <= m_lastGroupSelGroup ? group : m_lastGroupSelGroup',
 'group > m_lastGroupSelGroup ? group : m_lastGroupSelGroup',
 'group >= m_lastGroupSelGroup ? group : m_lastGroupSelGroup',
 'm_lastGroupSelGroup < 0 ? group : m_lastGroupSelGroup',
 'm_lastGroupSelGroup >= 0 ? m_lastGroupSelGroup : group',
 'group >= 0 ? group : m_lastGroupSelGroup',
 'group < 0 ? m_lastGroupSelGroup : group',
 '*(const Int *)&m_lastGroupSelGroup',
 '*(&m_lastGroupSelGroup)',
 '(const Int &)m_lastGroupSelGroup',
 'group',
]
variants=[]
for n in range(64):
 mode=n//16;expr=args[n%16];helper='';s=fn;branch=s[start:end]
 if mode==0:
  branch=branch.replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(('+expr+'))')
 elif mode==1:
  branch=branch.replace('     Player *player = localPlayer43003C();','     Int tapGroup = '+expr+';\n     Player *player = localPlayer43003C();',1)
  branch=branch.replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(tapGroup)')
 else:
  ty='const Int &' if mode==3 else 'Int '
  helper='static __forceinline Int tapGroupChoice43003C('+ty+'group, '+ty+'lastGroup) { return '+expr.replace('m_lastGroupSelGroup','lastGroup')+'; }\n'
  branch=branch.replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(tapGroupChoice43003C(group, m_lastGroupSelGroup))')
 s=s[:start]+branch+s[end:]
 whole=BASE[:a]+s+BASE[b:]
 if helper:whole=whole.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage',1)
 variants.append((f'w31_{n:02d}',whole))
