forms=[
 '{x} == {y}', '{y} == {x}',
 '!((UnsignedInt){x} - (UnsignedInt){y})', '!((UnsignedInt){y} - (UnsignedInt){x})',
 '!({x} ^ {y})', '(~{x}) == (~{y})', '-{x} == -{y}',
 '(UnsignedInt){x}+1u == (UnsignedInt){y}+1u', '({x} ^ 0x55) == ({y} ^ 0x55)',
 '{x} <= {y} && {x} >= {y}', '!({x} < {y} || {x} > {y})',
 '({x} == {y}) ? TRUE : FALSE', '({x} != {y}) ? FALSE : TRUE',
 '((unsigned __int64)(UnsignedInt){x}) == ((unsigned __int64)(UnsignedInt){y})',
 '(({x} <= {y}) == ({y} <= {x}))',
 '(({x} < {y}) == ({y} < {x}))',
 '!((UnsignedInt){x} + ~(UnsignedInt){y} + 1u)',
 '(Bool)({x} == {y})', '(Int)({x} == {y})',
 '({x} & ~{y}) == ({y} & ~{x})',
]
variants=[]
for mode in range(4):
 for k,form in enumerate(forms):
  helper=''
  if mode:
   ty='const Int &' if mode==2 else 'Int '
   rt='Int' if mode==3 else 'Bool'
   helper='static __forceinline '+rt+' groupComparison43003C('+ty+'x, '+ty+'y) { return '+form.format(x='x',y='y')+'; }\n'
   expr='groupComparison43003C(group, m_lastGroupSelGroup)'
  else:expr=form.format(x='group',y='m_lastGroupSelGroup')
  s=BASE[:a]+fn.replace('group == m_lastGroupSelGroup','('+expr+')',1)+BASE[b:]
  if helper:s=s.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage',1)
  variants.append((f'w27_{mode}_{k:02d}',s))
