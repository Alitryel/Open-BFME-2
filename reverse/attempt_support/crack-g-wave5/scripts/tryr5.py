from lab import Lab
import re,itertools
l=Lab('470d5',216,label='binding');s=l.base
s=s.replace('BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);','').replace('void rva00132FE9(bool flag);','static BFME2ParticleTextureHandle Get(const char*,int,int);\n void rva00132FE9(bool flag);').replace('BFME2LoadParticleTexture(','TextureAsset::Get(')
l.test('current_TextureAsset_Get',s)
# Return-copy destination is a reference within its constructor, so make that
# receiver/data order explicit through the actual member initializer semantics.
for form in ['Ptr = o.Ptr;', 'TextureClass *p=o.Ptr; Ptr=p;']:
 t=s.replace(': Ptr(o.Ptr)\n\t{','\n\t{\n'+form)
 l.test('copy_init_contract_'+form,t)
l.done()
l=Lab('26ef50',315);s=l.base
# Real source models prerequisites as a vector; a view local keeps its begin
# separate from the active iterator without an artificial equal-arm condition.
for cst in ('','const '):
 for test in ('!=','<'):
  t=s.replace('if (m_prerequisitesBegin != (object ? (__vref(m_prerequisitesEnd)) : (__vref(m_prerequisitesEnd))))',cst+'UpgradeTemplate *const *begin=m_prerequisitesBegin;\n if (begin '+test+' m_prerequisitesEnd)')
  t=t.replace('UpgradeTemplate **it = m_prerequisitesBegin','UpgradeTemplate *const *it = begin')
  l.test('prereq_begin_'+cst+test,t)
# Cap source by reference to its natural minimum operand; target x87/SSE spill
# scheduling can depend on conditional address versus conditional value.
old='''float change = 1.0f;
		if (change > __vref(g_00DFEEF8->m_850))
			change = g_00DFEEF8->m_850;'''
for choice in ('g_00DFEEF8->m_850 < one ? g_00DFEEF8->m_850 : one','one > g_00DFEEF8->m_850 ? g_00DFEEF8->m_850 : one'):
 for typ in ('const float&','float'):
  l.test('cap_reference_'+choice+typ,s.replace(old,'const float one=1.0f; '+typ+' change=('+choice+');'))
l.done()
l=Lab('2edff9',462);s=l.base
# Lifetime of radius outputs ends after the rectangle bounds are formed.
# Group only the genuine x/y bounds, with no padding and both source orders.
for order in (0,1):
 t=s.replace('int xStart = pair.x - half;\nint xEnd = pair.x + rest;', 'struct Bounds {'+('int first,last;' if order==0 else 'int last,first;')+'}; Bounds xBounds; xBounds.first=pair.x-half; xBounds.last=pair.x+rest;')
 t=t.replace('int yStart = pair.y - half;\nint yEnd = pair.y + rest;','Bounds yBounds; yBounds.first=pair.y-half; yBounds.last=pair.y+rest;')
 for a,b in [('xStart','xBounds.first'),('xEnd','xBounds.last'),('yStart','yBounds.first'),('yEnd','yBounds.last')]:t=re.sub(r'\b'+a+r'\b',b,t)
 l.test('rectangle_bounds_'+str(order),t)
for init in ('before','after'):
 t=s.replace('Coord3D *p = (Coord3D *)rva002EBC7F(&tmp, obj, (Rva002EBC7FPair *)&pair, layer);\n*out = *p;','rva002EBC7F(&tmp, obj, (Rva002EBC7FPair *)&pair, layer);\n*out = tmp;')
 if init=='before':t=t.replace('Coord3D tmp;','Coord3D tmp = *out;')
 l.test('owned_coord_return_'+init,t)
l.done()
l=Lab('3642df',578);s=l.base
# Keep a single next pointer across the loop condition and update, retaining
# the established node/next distinction; no opaque conditional carriers.
for start in ['Rva003642DFNode *next=result.m_node->optimized;\n while(next) {','Rva003642DFNode *next;\n while((next=result.m_node->optimized)!=0) {']:
 t=s.replace('while(result.m_node->optimized) {\n  Rva003642DFNode *next=result.m_node->optimized;',start)
 if 'while(next)' in start:t=t.replace('result.m_node=node;','result.m_node=node;next=node->optimized;')
 l.test('cursor_lifetime_'+start,t)
for param in ('const float&','float'):
 t=s.replace('peekScale(Coord3D &a,float f)','peekScale(Coord3D &a,'+param+' f)')
 t=t.replace('result.m_pos.x*=f;result.m_pos.y*=f;result.m_pos.z*=f;','peekScale(result.m_pos,f);')
 l.test('coordinate_scale_'+param,t)
l.done()
l=Lab('4dcc84',461);s=l.base
s=s.replace('(entry04?entry04:entry04)','entry04').replace('(object ? object : object)','object')
l.test('natural_record_access',s)
for which in ('duration','fx','both'):
 t=s
 if which in ('duration','both'):
  t=t.replace('else until2c = entry04->duration0c ? frame + entry04->duration0c : 0;','else { const unsigned duration=entry04->duration0c; until2c=duration ? frame+duration : 0; }')
 if which in ('fx','both'):
  t=t.replace('    if (entry04->fx30) {','    { const FXList *fx=entry04->fx30; if (fx) {').replace('FXList::doFXObj(entry04->fx30, object, target);\n    }','FXList::doFXObj(fx, object, target);\n    }}')
 l.test('record_value_lifetime_'+which,t)
l.done()
