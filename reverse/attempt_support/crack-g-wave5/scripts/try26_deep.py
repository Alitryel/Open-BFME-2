from lab import Lab
import re,itertools
l=Lab('26ef50',315,source='build/crack-g/0x0026ef50/main/best.cpp',label='iterator');s=l.base
check='if (m_prerequisitesBegin != (object ? (__vref(m_prerequisitesEnd)) : (__vref(m_prerequisitesEnd))))'
for begin in ['UpgradeTemplate **begin=m_prerequisitesBegin;', 'UpgradeTemplate *const *begin=m_prerequisitesBegin;', 'UpgradeTemplate ** const begin=m_prerequisitesBegin;']:
 for cond in ['begin != m_prerequisitesEnd','begin != __vref(m_prerequisitesEnd)']:
  t=s.replace(check,begin+'\n if ('+cond+')').replace('UpgradeTemplate **it = m_prerequisitesBegin','UpgradeTemplate *const *it = begin')
  l.test('begin_contract_'+begin+cond,t)
# A genuine typed two-pointer range and iterator on the by-value range preserve
# the element type without relying on a conditional that's equal on both arms.
for name in ('range.begin','range.first()'):
 definition='struct UpgradeRange { UpgradeTemplate **begin,**end; UpgradeTemplate**first()const{return begin;} };\n'
 t=s.replace('class ThingFactory',definition+'class ThingFactory',1)
 t=t.replace(check,'UpgradeRange range={m_prerequisitesBegin,m_prerequisitesEnd};\n if ('+name+'!=range.end)').replace('UpgradeTemplate **it = m_prerequisitesBegin','UpgradeTemplate **it = '+name).replace('it != m_prerequisitesEnd','it != range.end')
 l.test('range_view_'+name,t)
# The actual iterator lifetime may be scoped to the prerequisite branch and its
# first value used by the test; while/body advancement form vs for increment.
t=s.replace(check,'UpgradeTemplate **it=m_prerequisitesBegin;\n if (it!=m_prerequisitesEnd)').replace('for (UpgradeTemplate **it = m_prerequisitesBegin; it != m_prerequisitesEnd; ++it)','for (; it != m_prerequisitesEnd; ++it)')
l.test('iterator_outer_lifetime',t)
l.done()
