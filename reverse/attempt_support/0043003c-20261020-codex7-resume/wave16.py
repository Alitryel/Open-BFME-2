def endbrace(s,i):
 depth=1;j=i+1
 while depth:
  depth+=(s[j]=='{')-(s[j]=='}');j+=1
 return j
start=fn.index('    if ( now - m_lastGroupSelTime')
x=fn.index('{',start); xe=endbrace(fn,x)
y=fn.index('{',xe); ye=endbrace(fn,y)
tap=fn[x+1:xe-1]; normal=fn[y+1:ye-1]
A='now - m_lastGroupSelTime < (UnsignedInt)BfmeLogicFramesPerSecond'
B='group == m_lastGroupSelGroup'
variants=[]
for n in range(128):
 form=n&7; c=A;d=B;v=normal;t=tap
 if n&8:c='!('+A.replace('<','>=')+')'
 if n&16:d='!('+B.replace('==','!=')+')'
 if form==0:body='if ('+c+') { if ('+d+') {'+t+'} else {'+v+'} } else {'+v+'}'
 elif form==1:body='if (!('+c+')) {'+v+'} else if (!('+d+')) {'+v+'} else {'+t+'}'
 elif form==2:body='if ('+d+') { if ('+c+') {'+t+'} else {'+v+'} } else {'+v+'}'
 elif form==3:body='if ('+c+' && '+d+') {'+t+'} else if ('+c+') {'+v+'} else {'+v+'}'
 elif form==4:body='if ('+c+') { if (!('+d+')) goto normal16; '+t+' goto end16; } normal16: {'+v+'} end16:;'
 elif form==5:body='Bool doubleTap = FALSE; if ('+c+') { if ('+d+') doubleTap=TRUE; } if (doubleTap) {'+t+'} else {'+v+'}'
 elif form==6:body='Int doubleTap = ('+c+') ? (('+d+') ? 1 : 0) : 0; if (doubleTap) {'+t+'} else {'+v+'}'
 else:body='switch (('+c+') ? (('+d+') ? 1 : 0) : 0) { case 1: {'+t+'} break; default: {'+v+'} break; }'
 s=fn[:start]+body+fn[ye:]
 if n&32:s=s.replace(old,direct)
 if n&64:s=s.replace('    m_lastGroupSelTime = now;\n    m_lastGroupSelGroup = group;','    m_lastGroupSelGroup = group;\n    m_lastGroupSelTime = now;')
 variants.append((f'w16_{n:03d}',BASE[:a]+s+BASE[b:]))
