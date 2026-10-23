variants=[]
for k,key in enumerate(['int','long','unsigned int','unsigned long','ObjectID']):
 for tr in range(2):
  for explicit in range(2):
   maptype='_STL::hash_map<'+key+', Bool'+(', _STL::hash<int> ' if explicit else '')+'>'
   # ObjectID has no generic hash operator, but the real hash<int> accepts its enum key.
   if key=='ObjectID' and not explicit:continue
   s=BASE.replace('_STL::hash_map<int, Bool> selectedIDs;',maptype+' selectedIDs;')
   s=s.replace('selectedIDs.find((int)id)','selectedIDs.find(('+key+')id)').replace('selectedIDs[(int)id]','selectedIDs[('+key+')id]')
   if tr:
    st=s.index('    if ( now - m_lastGroupSelTime',s.index('   Int group = t - ((GameMessage::Type)62);'));en=s.index('    else',st)
    s=s[:st]+s[st:en].replace('rva002AA176(m_lastGroupSelGroup)','rva002AA176(group)')+s[en:]
   variants.append((f'w33_{k}_{tr}_{explicit}',s))
