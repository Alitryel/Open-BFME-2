variants=[]
cond='group == m_lastGroupSelGroup'
start=fn.index('    if ( now - m_lastGroupSelTime')
end=fn.index('    else',start)
# The first else after this position is the branch for normal selection.
assert 'rva002AA176(group)' in fn[start:end]
for n in range(64):
 s=fn
 if n&1:
  s=s[:start]+s[start:end].replace('rva002AA176(group)','rva002AA176(m_lastGroupSelGroup)')+s[end:]
 if n&2:s=s.replace(cond,'m_lastGroupSelGroup == group',1)
 if n&4:s=s.replace(old,direct)
 if n&8:s=s.replace('Int group =','long group =')
 if n&16:s=s.replace('Bool valid','Int valid')
 if n&32:
  s=s.replace('now - m_lastGroupSelTime < (UnsignedInt)BfmeLogicFramesPerSecond','nativeRecentGroup43003C(now, m_lastGroupSelTime)',1)
  helper='static __forceinline Bool nativeRecentGroup43003C(UnsignedInt now, UnsignedInt then) { return now - then < (UnsignedInt)BfmeLogicFramesPerSecond; }\n'
 else:helper=''
 whole=BASE[:a]+s+BASE[b:]
 if helper:whole=whole.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage')
 variants.append((f'w22_{n:02d}',whole))
