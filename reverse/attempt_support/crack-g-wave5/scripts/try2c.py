from lab import Lab
l=Lab('2c986b',119,label='own2');s=l.base
for t,n in [(s,'base')]:
 for typ in ['const float','const float &','float const volatile &']:
  import re
  v=re.sub(r'float (scale|s|f)\s*=',typ+r' \1=',t)
  if v!=t:l.test('coefficient_'+typ,v)
# Prefix exactly52B means the leaf call boundaries are already right. Preserve
# that while varying only the source-coordinate representation at the merge.
for order in [('x','y','z'),('z','y','x'),('y','z','x')]:
 for param in ['float','const float&']:
  helper='static __forceinline void scaleBorder(Coord3D&v,'+param+' s){'+''.join('v.'+a+'*=s;' for a in order)+'}\n'
  t=s.replace('void Object::Get2DBorderVectorTo',helper+'void Object::Get2DBorderVectorTo',1)
  import re
  t=t.replace('oy=temp.y*f;oz=temp.z*f;ox=temp.x*f;', 'scaleBorder(temp,f);ox=temp.x;oy=temp.y;oz=temp.z;')
  l.test('helper_'+str(order)+param,t)
l.done()
