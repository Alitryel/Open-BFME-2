from lab import Lab
import re,itertools
l=Lab('470d5',216);s=l.base
# Both branches construct a counted handle and set the same filter. A single
# return object makes NRVO's lifetime explicit, preserving branch-only quality.
start=s.index('\n{',s.index('BFME2ParticleTextureHandle Rva000470D5GetTexture'))
head=s[:start]
for const in ('','const '):
 for form in (0,1):
  body='''
{
 '''+const+'''unsigned int flags=src->m_flags30;
 BFME2ParticleTextureHandle tex((flags&2) ? *src->m_texture2C : BFME2LoadParticleTexture(src->m_name08.str(),1,0));
 ((ShroudTexture*)&tex)->getFilter()->m_10=1;
 ((ShroudTexture*)&tex)->getFilter()->m_0C=1;
 if (!(flags&2)) ((TextureAsset*)&tex)->rva00132FE9(true);
 return tex;
}
'''
  if form:body=body.replace('BFME2ParticleTextureHandle tex(','BFME2ParticleTextureHandle tex = ').replace('src->m_name08.str(),1,0));','src->m_name08.str(),1,0);')
  l.test('unified_return_'+const+str(form),head+body)
# Constructor delegates reference ownership through the established copy path,
# with a source reference local to expose the destination before the copy.
for cls in ('const BFME2ParticleTextureHandle&','BFME2ParticleTextureHandle&'):
 t=s.replace('BFME2ParticleTextureHandle tex(*src->m_texture2C);',cls+' from=*src->m_texture2C; BFME2ParticleTextureHandle tex(from);')
 l.test('held_ref_'+cls,t)
l.done()
l=Lab('599870',186);s=l.base.replace('/arch:SSE2','/G7 /arch:SSE')
l.test('correct_native_flags',s)
# Square helper returning a scalar versus references lets each component's
# copy exist at the native point rather than folding into the multiply.
for param in ('float','const float&'):
 helper='static __forceinline float distanceSquare('+param+' value){return value*value;}\n'
 t=s.replace('enum ObjectID',helper+'enum ObjectID',1)
 for expr in ['distanceSquare(dx)+distanceSquare(dy)','distanceSquare(dy)+distanceSquare(dx)']:
  l.test('square_'+param+expr,t.replace('dx * dx + dy * dy',expr))
# Keep the selected id and distance together as the real search result.
for order in (0,1):
 decl='struct Best { '+('float distance; ObjectID id;' if order==0 else 'ObjectID id;float distance;')+' } chosen; chosen.distance=0;chosen.id=INVALID_OBJECT_ID;'
 t=s.replace('float bestDist = 0.0f;\n    ObjectID best = INVALID_OBJECT_ID;',decl)
 t=re.sub(r'\bbestDist\b','chosen.distance',t);t=re.sub(r'\bbest\b','chosen.id',t)
 l.test('result_record_'+str(order),t)
l.done()
l=Lab('2af236',261);s=l.base
# Typed iterator's return value has two words. Actual increment body retained
# in header, so remove the declaration-only suppression for that single helper.
inc=' template<> ExistingNameTable::iterator &ExistingNameTable::iterator::operator++();'
t=s.replace(inc,'').replace(' (this?_ReadWriteBarrier():_ReadWriteBarrier());','')
l.test('visible_increment',t)
for bind in ['ExistingNameTable::iterator initial=view->begin(); it=initial;','const ExistingNameTable::iterator &initial=view->begin(); it=initial;','it=ExistingNameTable::iterator(view->begin());']:
 l.test('begin_value_'+bind,t.replace('it = view->begin();',bind))
for place in (0,1):
 u=t.replace('  unsigned int count = reinterpret_cast<NameFloatTablePrefix *>(table)->count;','  unsigned int count;\n  float value;\n  count = reinterpret_cast<NameFloatTablePrefix *>(table)->count;')
 u=u.replace('   float value = *reinterpret_cast<const float *>(&it->second);','   value = *reinterpret_cast<const float *>(&it->second);')
 if place:u=u.replace('  unsigned int count;\n  float value;','  float value;\n  unsigned int count;')
 l.test('save_local_scope_'+str(place),u)
l.done()
l=Lab('294471',570);s=l.base
# The two-word containment-list descriptor is an out parameter at the ABI but
# likely a returned view in source. Give it a real iterator/predicate API,
# retaining the exact storage and calls.
for countstyle in (0,1):
 t=s.replace('struct ObjectListView {void*first;const ObjectList*list;};','struct ObjectListView {void*first;const ObjectList*list; ObjectNode *begin()const{return list->head->next;} ObjectNode *end()const{return list->head;} bool empty()const{return begin()==end();} };')
 t=t.replace('ObjectNode*endNode=view.list->head;','ObjectNode*endNode=view.end();').replace('ObjectNode*first=view.list->head->next;if(first==view.list->head)','ObjectNode*first=view.begin();if('+('view.empty()' if countstyle else 'first==view.end()')+')')
 l.test('list_api_'+str(countstyle),t)
for ntype in ('const int','unsigned int','const unsigned int'):
 l.test('count_contract_'+ntype,s.replace('int n=current->countFor(0);',ntype+' n=current->countFor(0);'))
# Explicit narrow scalar contract at retail's AL reads.
for n in ['rva002933CD','rva0028F518']:
 t=s.replace('int '+n+'();','unsigned char '+n+'();')
 if t!=s:l.test('narrow_'+n,t)
l.done()
