start=fn.index('    if ( now - m_lastGroupSelTime');end=fn.index('    else',start)
block='''     GameMessage *deselectMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)1004);
     deselectMsg->appendBooleanArgument(TRUE);
     ((NativeUI43003C *)TheInGameUI)->deselectAllDrawables();'''
assert block in fn
variants=[]
for n in range(128):
 form=n&3; c=n>>2;s=fn;helper=''
 if form==1:s=s.replace(block,'     {\n'+block+'\n     }')
 elif form==2:
  helper='static __forceinline void normalDeselect43003C() {\n'+block+'\n}\n'
  s=s.replace(block,'     normalDeselect43003C();')
 elif form==3:
  helper='struct NormalSelection43003C { static __forceinline void deselect() {\n'+block+'\n} };\n'
  s=s.replace(block,'     NormalSelection43003C::deselect();')
 if c&1:
  normal=s.index('    else',s.index('    if ( now - m_lastGroupSelTime'))
  tail=s[normal:]
  tail=tail.replace('    {\n','    {\n     Player *player;\n',1)
  tail=tail.replace('Player *player = localPlayer43003C();','player = localPlayer43003C();',1)
  s=s[:normal]+tail
 if c&2:
  normal=s.index('    else',s.index('    if ( now - m_lastGroupSelTime'))
  tail=s[normal:]
  tail=tail.replace('     if (player)\n','     if (player)\n',1)
  tail=tail.replace('      Squad *selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);','      Squad *selectedSquad; selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);',1)
  s=s[:normal]+tail
 if c&4:
  st=s.index('    if ( now - m_lastGroupSelTime');en=s.index('    else',st)
  s=s[:st]+s[st:en].replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(group)')+s[en:]
 if c&8:s=s.replace('Bool valid = TRUE;','Int valid = TRUE;')
 if c&16:
  s=s.replace('    m_lastGroupSelTime = now;\n    m_lastGroupSelGroup = group;','    m_lastGroupSelGroup = group;\n    m_lastGroupSelTime = now;')
 whole=BASE[:a]+s+BASE[b:]
 if helper:whole=whole.replace('GameMessageDisposition SelectionTranslator::translateGameMessage',helper+'GameMessageDisposition SelectionTranslator::translateGameMessage',1)
 variants.append((f'w30_{n:03d}',whole))
