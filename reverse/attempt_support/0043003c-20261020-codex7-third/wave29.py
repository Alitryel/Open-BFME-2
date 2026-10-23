header=Path('reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/SelectionXlat.h').read_text()
variants=[]
for n in range(64):
 s=BASE
 f=fn
 # Two signed 32-bit field types; raw compare and stores retain the native accesses.
 if n&1:s=s.replace('#include "GameClient/SelectionXlat.h"',header.replace('Int m_lastGroupSelGroup;','long m_lastGroupSelGroup;'))
 if n&2:
  # An independently scoped, genuinely used group for the guard and the body.
  f=f.replace('Int group = t - ((GameMessage::Type)62);','Int guardedGroup = t - ((GameMessage::Type)62);',1)
  f=f.replace('if ( group >= 0 && group < 10 )','if ( guardedGroup >= 0 && guardedGroup < 10 )',1)
  pos=f.index('    DEBUG_LOG(')
  f=f[:pos]+'    Int group = t - ((GameMessage::Type)62);\n'+f[pos:]
 if n&4:
  start=f.index('    if ( now - m_lastGroupSelTime');end=f.index('    else',start)
  f=f[:start]+f[start:end].replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(group)')+f[end:]
 if n&8:
  # Retain initialized values, separate declaration order from lexical nesting.
  f=f.replace('   Int group = t - ((GameMessage::Type)62);','   Int group; group = t - ((GameMessage::Type)62);',1)
 if n&16:f=f.replace('Int group','long group')
 if n&32:
  f=f.replace('    m_lastGroupSelTime = now;\n    m_lastGroupSelGroup = group;','    m_lastGroupSelGroup = group;\n    m_lastGroupSelTime = now;')
 s=s.replace(fn,f,1)
 variants.append((f'w29_{n:02d}',s))
