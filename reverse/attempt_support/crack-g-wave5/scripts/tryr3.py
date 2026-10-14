from lab import Lab
import re,itertools
l=Lab('52dd75',230);s=l.base
# Actual vector operators can make the coefficient/accumulator loads coexist.
# Explore value-return scale/add versus in-place compound operations.
for val in ('float','const float&'):
 for param in ('const FacingCoord&','FacingCoord'):
  helper='''\ninline FacingCoord scaled('''+param+'''p, '''+val+''' f){return FacingCoord(p.x*f,p.y*f);}
inline FacingCoord added('''+param+'''a,'''+param+'''b){return FacingCoord(a.x+b.x,a.y+b.y);}\n'''
  src=s.replace('struct Rva0052DD75Inner',helper+'\nstruct Rva0052DD75Inner')
  for form in ['acc += scaled(delta,factor);','acc=added(acc,scaled(delta,factor));','delta*=factor; acc=added(acc,delta);']:
   l.test('vector_'+val+param+form,src.replace('delta *= factor;\n        acc += delta;',form))
# Real add method receiving independent x/y arguments, with sequence established
# by argument temporaries, may change the accumulator's lifetime without fences.
for order in ('xy','yx'):
 for ref in ('float','const float&'):
  method='__forceinline void accumulate('+ref+' dx,'+ref+' dy){'+('x+=dx;y+=dy;' if order=='xy' else 'y+=dy;x+=dx;')+'}\n'
  src=s.replace('FacingCoord()\n',method+'FacingCoord()\n',1).replace('acc += delta;','acc.accumulate(delta.x,delta.y);')
  l.test('component_add_'+ref+order,src)
l.done()
l=Lab('33930',325);s=l.base
# Split the reused header variable into the two actual boundary tags; then use
# an address-free inline bitfield accessor instead of casting the header storage.
for nexttype in ('unsigned','const unsigned'):
 t=s.replace('head = *(unsigned *)((char *)neighbor + 4)',nexttype+' nextHead = *(unsigned *)((char *)neighbor + 4)').replace('neighbor + head + 4','neighbor + nextHead + 4').replace('base += head;','base += nextHead;')
 l.test('split_header_'+nexttype,t)
 for ref in ('const unsigned &','const unsigned'):
  l.test('split_saved_'+nexttype+ref,t.replace('unsigned savedHead = head;',ref+' savedHead = head;'))
for rettype in ('unsigned','const unsigned'):
 method='__forceinline '+rettype+' clearedHead() const { return m_head04&0x7ffffffbU; }\n'
 t=s.replace('unsigned m_size00;',method+'unsigned m_size00;').replace('block->m_head04 & 0x7ffffffbU','block->clearedHead()')
 l.test('header_member_'+rettype,t)
# Loop control based on current block is the source-level coalescing idiom.
for form in ('while (block != 0);','while (block);'):
 l.test('block_loop_'+form,s.replace('while (next != 0);',form))
l.done()
l=Lab('31f90',179);s=l.base
# Native count accumulates the byte flag before comparing the top block size.
# Snapshot both values from the same boundary tag, once, with proper width.
old='''result+=(next[1]&0x7ffffff8)<0x10;
   result+=((unsigned char)~(*(unsigned char*)(next+1)))&1&&1;'''
for order in ('byte','word'):
 for v in ('','volatile '):
  decl1='unsigned char flag=*(const '+v+'unsigned char*)(next+1);'
  decl2='unsigned tag=next[1];'
  body=(decl1+decl2 if order=='byte' else decl2+decl1)+'result+=(tag&0x7ffffff8)<0x10;result+=((unsigned char)~flag)&1&&1;'
  l.test('top_snapshot_'+order+v,s.replace(old,body))
for type_ in ('bool','unsigned int','int'):
 body=type_+' freeFlag=(((unsigned char)~(*(unsigned char*)(next+1)))&1)!=0;\n result+=freeFlag; result+=(next[1]&0x7ffffff8)<0x10;'
 l.test('flag_first_'+type_,s.replace(old,body))
l.done()
