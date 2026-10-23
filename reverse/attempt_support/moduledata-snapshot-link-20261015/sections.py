"""Read-only COFF section and relocation comparison."""
import collections, hashlib, struct
import link_census as lc
def normalized(name):return name
def sections(path):
 data=path.read_bytes();count=struct.unpack_from('<H',data,2)[0];optional=struct.unpack_from('<H',data,16)[0];syms=lc._coff_symbols(data);by_index={s['index']:s for s in syms};parts=[]
 for i in range(count):
  h=20+optional+40*i;name=data[h:h+8].rstrip(b'\0').decode('latin1');size,ptr,relptr=struct.unpack_from('<III',data,h+16);nrel=struct.unpack_from('<H',data,h+32)[0];flags=struct.unpack_from('<I',data,h+36)[0];body=data[ptr:ptr+size] if ptr else None
  defs=tuple(sorted((normalized(s['name']),s['value'],s['storage']) for s in syms if s['section']==i+1 and s['storage'] in (2,105)))
  parts.append((name,flags,defs,body,relptr,nrel,size))
 def target(s):
  if s['storage'] in (2,105):return ('external',normalized(s['name']),s['value'],s['storage'])
  if s['section']>0:
   p=parts[s['section']-1];return ('local',p[:3],s['value'],s['storage'],hashlib.sha256(p[3] or b'').hexdigest(),p[6])
  return ('other',s['name'],s['value'],s['storage'])
 result=[]
 for name,flags,defs,body,relptr,nrel,size in parts:
  if name.startswith('.debug'):continue
  rel=[]
  for r in range(nrel):
   at,sidx,kind=struct.unpack_from('<IIH',data,relptr+10*r);rel.append((at,kind,target(by_index[sidx])))
  if name=='.sxdata':
   assert body is not None and len(body)%4==0
   body=tuple(target(by_index[sidx]) for (sidx,) in struct.iter_unpack('<I',body))
  result.append((name,flags,defs,body,tuple(rel),size))
 return collections.Counter(result)
