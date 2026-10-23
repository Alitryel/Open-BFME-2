from lab import Lab
from pathlib import Path
import re
l=Lab('00294471',570,source='build/crack-g/0x00294471/main/best.cpp',label='returnabi');b=l.base
for extra in ['ObjectListView(){}','ObjectListView(){} ~ObjectListView(){}','ObjectListView(){} ObjectListView(const ObjectListView&o):first(o.first),list(o.list){}']:
 s=b.replace('void*first;const ObjectList*list;','void*first;const ObjectList*list;'+extra).replace('virtual void listA(ObjectListView*);','virtual ObjectListView listA();').replace('virtual void listB(ObjectListView*);','virtual ObjectListView listB();').replace('sub->listA(&view);','view=sub->listA();').replace('current->listB(&view);','view=current->listB();')
 l.test('aggregate_return_'+extra,s)
l.done()
source=Path('reverse/attempts/0x002a0161.cpp').read_text().replace('../Common/GameLogicObjectLookupView.h','Code/GameEngine/Source/Common/GameLogicObjectLookupView.h').replace('../../../Libraries/Include/Lib/ICoord2D.h','Code/Libraries/Include/Lib/ICoord2D.h').replace('// cl:','// cl: /I.',1)
Path('build/crack-g/postdraw.cpp').write_text(source)
l=Lab('002a0161',2854,source='build/crack-g/postdraw.cpp',label='exit_lifetime');b=l.base
s=re.sub(r'\s*if \(marginExceeded\)\s*break;','',b).replace('Bool marginExceeded = false;','').replace('marginExceeded = true;\n\t\t\t\t\t\t\tbreak;','goto superweaponsDone;').replace('\n\tif (TheGameLogic->getFrame() > 0 && m_showNamedTimers)', '\nsuperweaponsDone:\n\tif (TheGameLogic->getFrame() > 0 && m_showNamedTimers)')
l.test('direct_exit',s)
l.test('direct_exit_no_barrier',s.replace('\t_ReadWriteBarrier();',''))
# Stop condition at loop entry preserves the same nested string cleanup path.
s=b.replace('i < MAX_PLAYER_COUNT','i < MAX_PLAYER_COUNT && !marginExceeded').replace('mapIt != m_superweapons[i].end()','!marginExceeded && mapIt != m_superweapons[i].end()').replace('listIt != mapIt->second.end()','!marginExceeded && listIt != mapIt->second.end()')
s=re.sub(r'\s*if \(marginExceeded\)\s*break;','',s)
l.test('loop_guard_lifetimes',s)
l.done()
l=Lab('0007a847',2586,symbol='?setModelState@W3DHordeModelDraw@@QAE_NPAUHordeModelState@@_NPAURva000C3886Obj@@@Z',label='track_view');b=l.base.replace('// W3DHordeModelDraw::setModelState','// ?setModelState@W3DHordeModelDraw@@QAE_NPAUHordeModelState@@_NPAURva000C3886Obj@@@Z',1)
old='const char *right=m->right.str(); const char *file=m->trackFile.str(); const char *left=m->left.str();'
for t in ['const char *const &','const char *']:
 for fields in [('right','file','left'),('file','left','right')]:
  init=' '.join(t+name+' = '+ ('m->trackFile' if name=='file' else 'm->'+name)+'.str();' for name in fields)
  l.test('bind_ref_'+t+str(fields),b.replace(old,init))
# A typed view of the actual string subobjects changes dataflow without changing ABI.
s=b.replace(old,'const AsciiString &rightName=m->right; const AsciiString &fileName=m->trackFile; const AsciiString &leftName=m->left; const char*right=rightName.str();const char*file=fileName.str();const char*left=leftName.str();')
l.test('string_subobject_refs',s)
# Keep valid decorated bank header even if baseline wins.
if l.besttext.startswith('// W3DHordeModelDraw::setModelState'): (l.dir/'best.cpp').write_text(l.besttext.replace('// W3DHordeModelDraw::setModelState','// '+l.symbol,1))
l.done()
