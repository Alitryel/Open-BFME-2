start=fn.index('    if ( now - m_lastGroupSelTime'); end=fn.index('    else',start)
# Isolate which uses participate in PRE. All forms preserve the complete int value.
forms=['group','*(const unsigned int *)&group','*(const long *)&group','*(&group)',
 'static_cast<Int>(static_cast<UnsignedInt>(group))','groupValue43003C(&group)',
 'groupValueRef43003C(group)','groupIdentity43003C(group)']
helpers='''
static __forceinline Int groupValue43003C(const Int *v) { return *v; }
static __forceinline Int groupValueRef43003C(const Int &v) { return v; }
static __forceinline Int groupIdentity43003C(Int v) { return v; }
'''
variants=[]
for tr in range(2):
 for mode in range(8):
  for mask in range(4):
   s=fn
   branch=s[start:end]
   branch=branch.replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(group)' if tr else 'rva002AA176(m_lastGroupSelGroup)')
   tail=s[end:]
   if mask&1:tail=tail.replace('((GameMessage::Type)1016) + group','((GameMessage::Type)1016) + ('+forms[mode]+')')
   if mask&2:tail=tail.replace('rva002AA176(group)','rva002AA176('+forms[mode]+')')
   s=s[:start]+branch+tail
   whole=BASE[:a]+s+BASE[b:]
   whole=whole.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helpers+'GameMessageDisposition SelectionTranslator::translateGameMessage',1)
   variants.append((f'w28_{tr}_{mode}_{mask}',whole))
