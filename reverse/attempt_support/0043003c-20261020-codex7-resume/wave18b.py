variants=[]
for n in range(64):
 ref=n&1;ptr=n&2;unsg=n&4;usevalid=n&8;timeptr=n&16;swap=n&32
 ty='UnsignedInt' if unsg else 'Int'
 block=old if usevalid else direct
 block=block.replace('m_lastGroupSelGroup','lastGroup').replace('m_lastGroupSelTime','lastTime')
 if ptr: arg=ty+' *lastGroupArg';block=block.replace('lastGroup','(*lastGroupArg)');call='&m_lastGroupSelGroup'
 elif ref: arg=ty+' &lastGroup';call='m_lastGroupSelGroup'
 else:arg=ty+' lastGroup';call='m_lastGroupSelGroup'
 if timeptr:timearg='const UnsignedInt *lastTimeArg';block=block.replace('lastTime','(*lastTimeArg)');timecall='&m_lastGroupSelTime'
 else:timearg='UnsignedInt lastTime';timecall='m_lastGroupSelTime'
 if unsg:block=block.replace('(*lastGroupArg) >= 0','(Int)(*lastGroupArg) >= 0').replace('lastGroup >= 0','(Int)lastGroup >= 0')
 # Unsigned reference diagnostic uses an explicit equal-width read view.
 if unsg and (ptr or ref):call=('(UnsignedInt *)&m_lastGroupSelGroup' if ptr else '(UnsignedInt &)m_lastGroupSelGroup')
 args=arg+', '+timearg;calls=call+', '+timecall
 if swap:args=timearg+', '+arg;calls=timecall+', '+call
 rt='void' if ptr or ref else ty
 ret='' if rt=='void' else '\nreturn lastGroup;'
 helper='static __forceinline '+rt+' validateGroup43003C('+args+') {\n'+block+ret+'\n}\n'
 statement='validateGroup43003C('+calls+');'
 if rt!='void':statement='m_lastGroupSelGroup = '+statement
 s=BASE.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage')
 assert helper in s
 s=s.replace(old,'    '+statement+'\n')
 variants.append((f'w18b_{n:02d}',s))
