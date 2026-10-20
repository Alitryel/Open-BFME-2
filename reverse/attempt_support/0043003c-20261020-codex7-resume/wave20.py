variants=[]
frame='((NativeUI43003C *)TheInGameUI)->slot120()'
for n in range(64):
 pointer=n&1;timeptr=n&2;usevalid=n&4;order=(n>>3)&3;expr=n&32
 block=old if usevalid else direct
 # Keep original outer test in caller, so the getter is never called on a negative group.
 first=block.index('{');block=block[first+1: block.rfind('}')]
 block=block.replace(frame,'frameChanged').replace('m_lastGroupSelTime','lastTime').replace('m_lastGroupSelGroup','lastGroup')
 if pointer:garg='Int *lastGroupArg';gcall='&m_lastGroupSelGroup';block=block.replace('lastGroup','(*lastGroupArg)')
 else:garg='Int &lastGroup';gcall='m_lastGroupSelGroup'
 if timeptr:targ='const UnsignedInt *lastTimeArg';tcall='&m_lastGroupSelTime';block=block.replace('lastTime','(*lastTimeArg)')
 else:targ='UnsignedInt lastTime';tcall='m_lastGroupSelTime'
 args=[garg,targ,'UnsignedInt frameChanged'];calls=[gcall,tcall,'frameChanged']
 perm=[[0,1,2],[2,1,0],[1,0,2],[1,2,0]][order]
 if expr:calls[2]=frame
 helper='static __forceinline void validateFrameGroup43003C('+', '.join(args[i] for i in perm)+') {\n'+block+'\n}\n'
 stmt='    if (m_lastGroupSelGroup >= 0) {\n'
 if not expr:stmt+='     UnsignedInt frameChanged = '+frame+';\n'
 stmt+='     validateFrameGroup43003C('+', '.join(calls[i] for i in perm)+');\n    }\n'
 s=BASE.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage')
 s=s.replace(old,stmt)
 variants.append((f'w20_{n:02d}',s))
