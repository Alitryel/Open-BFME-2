from lab import Lab
from pathlib import Path
import re,itertools
s=Path('reverse/attempts/0x00265514.cpp').read_text()
helpers='''
__declspec(noinline) inline Coord3D *Object::getPlanarDirectionTo(Coord3D*out,const Object*other)const { Get2DCenterVectorTo(out,(const Coord3D*)((const char*)other+0x38));return out; }
__declspec(noinline) inline void Object::Get2DCenterVectorTo(Coord3D*out,const Coord3D*pos)const { const Coord3D*p=(const Coord3D*)((const char*)this+0x38);out->x=pos->x-p->x;out->y=pos->y-p->y;out->z=0; }
'''
# Eliminate bank's always-true condition and volatile stores to recover the
# debug scalar temporary semantics before helper/reference experiments.
clean=s.replace('r1_vwrite(((&(x)) ? (x) : (x)))','x').replace('r1_vwrite(y)','y')
for r,sz,sym in [('00265514',130,None),('002c986b',119,'?rva002C986B@Object@@QBEPAUCoord3D@@PAU2@PBU2@@Z')]:
 l=Lab(r,sz,symbol=sym,source='reverse/attempts/0x00265514.cpp')
 for visible in (False,True):
  src=clean
  if visible:src=src.replace('Coord3D *Object::rva00265514',helpers+'\nCoord3D *Object::rva00265514',1)
  l.test('natural_visible_'+str(visible),src)
  for typ in ['const float','const float &','float const volatile &']:
   t=src.replace('float scale=',typ+' scale=')
   l.test('coefficient_'+typ+'_v'+str(visible),t)
  for param in ['float','const float&']:
   for body in ['v.x*=s;v.y*=s;v.z*=s;','v.x=s*v.x;v.y=s*v.y;v.z=s*v.z;']:
    f='static __forceinline void scaleBorder(Coord3D&v,'+param+' s){'+body+'}\n'
    t=src.replace('class Object',f+'class Object',1)
    t=t.replace('y=dir.y*scale;\n  z=dir.z*scale;\n  x=dir.x*scale;','scaleBorder(dir,scale); x=dir.x;y=dir.y;z=dir.z;')
    l.test('scale_helper_'+param+body+'_v'+str(visible),t)
 l.done()
