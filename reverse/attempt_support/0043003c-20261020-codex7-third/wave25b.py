variants=[]
for n in range(64):
 s=BASE.replace('GameMessageDisposition SelectionTranslator::translateGameMessage', 'GameMessageDisposition SelectionTranslator::translateGameMessage',1)
 start=s.index('{', s.index('GameMessageDisposition SelectionTranslator::translateGameMessage'))+1
 s=s[:start]+''.join('\n Int diagnosticUnused%d = 0; (void)diagnosticUnused%d;'%(k,k) for k in range(n))+s[start:]
 variants.append((f'w25b_{n:02d}',s))
