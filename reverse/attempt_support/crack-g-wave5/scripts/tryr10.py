from lab import Lab
from pathlib import Path
import re
l=Lab('0019db50',2501);b=l.base
for typ in ['const SphereClass &','SphereClass']:
 helper='static __forceinline SphereClass transformLocalSphere('+typ+'input,const Matrix3D&matrix){SphereClass result=input;result.Transform(matrix);return result;}\n'
 s=b.replace('void HLodClass::Update_Obj_Space_Bounding_Volumes(void)',helper+'void HLodClass::Update_Obj_Space_Bounding_Volumes(void)',1).replace('tmpsphere.Transform(bonetm);','tmpsphere=transformLocalSphere(tmpsphere,bonetm);')
 l.test('sphere_value_flow_'+typ,s)
l.done()
l=Lab('0024797e',2195);b=l.base
# Use a real map accessor wrapper / iterator value instead of a separately assigned result.
for repl in ['BuildableMap::iterator initial = m_buildableStatus.begin(); it=initial;','it = m_buildableStatus.begin();']:
 # Actual member name is read below if this bank uses a differently named map.
 found=re.findall(r'it\s*=\s*(\w+)\.begin\(\);',b)
 if found:
  member=found[-1];s=b.replace('it = '+member+'.begin();',repl.replace('m_buildableStatus',member))
  l.test('begin_result_'+repl,s)
# An owning name temporary has the same live range as the comparison expression.
s=b.replace('bool changed = xfer->isLoading() && differs(prefs.Rva0043B9F5(), name);','bool changed=false; if(xfer->isLoading()){UnicodeString current=prefs.Rva0043B9F5();changed=differs(current,name);}')
l.test('comparison_name_lifetime',s)
l.done()
l=Lab('000c6e1a',2175);b=l.base
# Const input iteration: each copied source record is immutable in this loop.
s=b.replace('for (_STL::list<BfmePod32>::iterator it = bones.begin();','for (_STL::list<BfmePod32>::const_iterator it = bones.begin();')
l.test('immutable_record_iterator',s)
s=b.replace('BfmeStringRecord000B75AE rec(*(const BfmeStringRecord000B75AE *)&*it);','const BfmeStringRecord000B75AE &sourceRecord=*(const BfmeStringRecord000B75AE *)&*it;\n BfmeStringRecord000B75AE rec(sourceRecord);')
l.test('record_subobject_view',s)
l.done()
l=Lab('002fad13',2117);b=l.base
s=b.replace('struct {float x,y;} step;','struct AttackStep {float x,y; __forceinline void set(const Coord3D&v){x=v.x*10.0f;y=v.y*10.0f;}} step;').replace('step.x=(*(const volatile float*)&delta.x)*10.0f;step.y=(*(const volatile float*)&delta.y)*10.0f;','step.set(delta);')
l.test('semantic_xy_step',s)
s=b.replace('ICoord2D startIndex;\n    { ICoord2D scratch; startIndex=*Rva002E7875WorldToCell(&scratch,true,&objectPos); }','ICoord2D startIndex; Rva002E7875WorldToCell(&startIndex,true,&objectPos);')
l.test('actual_world_cell_output',s)
l.done()
