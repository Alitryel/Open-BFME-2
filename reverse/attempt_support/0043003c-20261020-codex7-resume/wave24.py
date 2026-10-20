variants=[]
start=fn.index('    if ( now - m_lastGroupSelTime');end=fn.index('    else',start)
declarations=['Int group = t - ((GameMessage::Type)62);','const Int group = t - ((GameMessage::Type)62);','const Int &group = t - ((GameMessage::Type)62);','const long &group = t - ((GameMessage::Type)62);','UnsignedInt group = t - ((GameMessage::Type)62);','register Int group = t - ((GameMessage::Type)62);','GameMessage::Type group = (GameMessage::Type)(t - ((GameMessage::Type)62));','Int groupCopy = t - ((GameMessage::Type)62); const Int &group = groupCopy;']
arguments=['m_lastGroupSelGroup','(Int)(unsigned char)m_lastGroupSelGroup','group & m_lastGroupSelGroup','group | m_lastGroupSelGroup','group ^ (group ^ m_lastGroupSelGroup)','m_lastGroupSelGroup + (group - m_lastGroupSelGroup)','m_lastGroupSelGroup - (m_lastGroupSelGroup - group)','m_lastGroupSelGroup & 15']
for n in range(128):
 branch=fn[start:end].replace('rva002AA176(group)','rva002AA176('+arguments[(n>>3)&7]+')')
 s=fn[:start]+branch+fn[end:]
 s=s.replace(declarations[0],declarations[n&7],1)
 if n&64:s=s.replace(old,direct)
 variants.append((f'w24_{n:03d}',BASE[:a]+s+BASE[b:]))
