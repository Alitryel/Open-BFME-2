variants=[]
start=fn.index('    if ( now - m_lastGroupSelTime')
end=fn.index('    else',start)
for n in range(128):
 mode=n//32; c=n%32
 rt='Int' if c&1 else 'Bool'
 args=['const Int &groupArg' if c&2 else 'Int groupArg','const Int &lastArg' if c&4 else 'Int lastArg']
 calls=['group','m_lastGroupSelGroup']
 if c&8:args.reverse();calls.reverse()
 body='if (groupArg != lastArg) return FALSE; return TRUE;' if c&16 else 'return groupArg == lastArg;'
 helper='static __forceinline '+rt+' groupEqualNew43003C('+', '.join(args)+') { '+body+' }\n'
 s=fn
 branch=s[start:end]
 if mode==0:branch=branch.replace('rva002AA176(group)','rva002AA176(m_lastGroupSelGroup)')
 elif mode==1:
  branch=branch.replace('     Player *player = localPlayer43003C();','     const Int selectedGroup = m_lastGroupSelGroup;\n     Player *player = localPlayer43003C();').replace('rva002AA176(group)','rva002AA176(selectedGroup)')
 elif mode==2:
  branch=branch.replace('     Player *player = localPlayer43003C();','     group = m_lastGroupSelGroup;\n     Player *player = localPlayer43003C();')
 else:
  branch=branch.replace('rva002AA176(group)','rva002AA176(m_lastGroupSelGroup)')
 s=s[:start]+branch+s[end:]
 if mode==3:s=s.replace(old,direct)
 s=s.replace('group == m_lastGroupSelGroup','groupEqualNew43003C('+', '.join(calls)+')',1)
 whole=BASE[:a]+s+BASE[b:]
 whole=whole.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage')
 variants.append((f'w23_{n:03d}',whole))
