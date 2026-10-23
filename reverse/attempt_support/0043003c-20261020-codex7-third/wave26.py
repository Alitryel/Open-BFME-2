variants=[]
for family in ['17','19','20']:
 scope=dict(BASE=BASE,a=a,b=b,fn=fn)
 old=fn[fn.index('    if (m_lastGroupSelGroup >= 0)'):fn.index('    // check for double-press to jump view')]
 direct=old.replace('     Bool valid = TRUE;\n','').replace('valid = FALSE;','m_lastGroupSelGroup = -1;').replace('     if (!valid)\n      m_lastGroupSelGroup = -1;\n','')
 scope.update(old=old,direct=direct)
 p=Path('reverse/attempt_support/0043003c-20261020-codex7-resume')/('wave'+family+'.py')
 exec(compile(p.read_text(),str(p),'exec'),scope)
 variants.extend((f'w26_{family}_{name}',src) for name,src in scope['variants'])
