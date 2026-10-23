forms=[
 '_STL::equal(&group, &group + 1, &m_lastGroupSelGroup)',
 '_STL::equal(&m_lastGroupSelGroup, &m_lastGroupSelGroup + 1, &group)',
 '_STL::find(&group, &group + 1, m_lastGroupSelGroup) == &group',
 '_STL::find(&m_lastGroupSelGroup, &m_lastGroupSelGroup + 1, group) == &m_lastGroupSelGroup',
 '_STL::count(&group, &group + 1, m_lastGroupSelGroup) != 0',
 '_STL::count(&m_lastGroupSelGroup, &m_lastGroupSelGroup + 1, group) != 0',
 'memcmp(&group, &m_lastGroupSelGroup, sizeof(group)) == 0',
 'memcmp(&m_lastGroupSelGroup, &group, sizeof(group)) == 0',
]
variants=[]
for n in range(32):
 expr=forms[n&7];s=BASE;helper=''
 if n&8:
  expr=expr.replace('&group','&left').replace('&m_lastGroupSelGroup','&right').replace('m_lastGroupSelGroup','right').replace('sizeof(group)','sizeof(left)')
  # The algorithms' non-address value operands still use group on reversed forms.
  import re
  expr=re.sub(r'\bgroup\b','left',expr)
  helper='static __forceinline Bool groupRangeEqual43003C(const Int &left, const Int &right) { return '+expr+'; }\n'
  expr='groupRangeEqual43003C(group, m_lastGroupSelGroup)'
 s=s[:a]+s[a:b].replace('group == m_lastGroupSelGroup','('+expr+')',1)+s[b:]
 if n&16:s=s.replace('/EHs ', '/EHs /Oi ',1)
 if helper:s=s.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage',1)
 variants.append((f'w34_{n:02d}',s))
