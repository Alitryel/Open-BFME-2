import itertools
variants=[]
orders=list(itertools.permutations(range(4)))
for n in range(192):
 order=orders[n%24]; mode=n//24
 ptr=mode&1;cref=mode&2;ret=mode&4
 args=['Int *groupDst' if ptr else 'Int &groupDst','UnsignedInt *timeDst' if ptr else 'UnsignedInt &timeDst','const Int &groupSrc' if cref else 'Int groupSrc','const UnsignedInt &timeSrc' if cref else 'UnsignedInt timeSrc']
 calls=['&m_lastGroupSelGroup' if ptr else 'm_lastGroupSelGroup','&m_lastGroupSelTime' if ptr else 'm_lastGroupSelTime','group','now']
 g='*groupDst' if ptr else 'groupDst';t='*timeDst' if ptr else 'timeDst'
 rt='Int' if ret else 'void'
 helper='static __forceinline '+rt+' storeGroupSelection43003C('+', '.join(args[i] for i in order)+') { '+t+'=timeSrc; '+g+'=groupSrc;'+(' return groupSrc;' if ret else '')+' }\n'
 statement='    storeGroupSelection43003C('+', '.join(calls[i] for i in order)+');'
 s=BASE.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage')
 f=fn.replace('    m_lastGroupSelTime = now;\n    m_lastGroupSelGroup = group;',statement)
 s=s.replace(fn,f)
 variants.append((f'w21_{n:03d}',s))
