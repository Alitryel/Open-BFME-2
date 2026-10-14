from lab import Lab
from pathlib import Path
import re
l=Lab('001e756d',1726,symbol='?moveTowardsPositionHorde@Locomotor@@QAEXPAVObject@@ABUCoord3D@@MM@Z');b=l.base
old='''Coord3D goal;
  goal.x = goalPos.x;
  goal.y = goalPos.y;
  goal.z = goalPos.z;
  bool reverse = false;
  if (m_template->m_D8 && obj->isKindOf((KindOfType)0x41))
  reverse = true;'''
assert old in b
copy='goal.x=goalPos.x;goal.y=goalPos.y;goal.z=goalPos.z;'
s=b.replace(old,'Coord3D goal; bool reverse; if(m_template->m_D8){'+copy+' reverse=obj->isKindOf((KindOfType)0x41);}else{'+copy+' reverse=false;}')
l.test('reverse_guard_coordinate_copy',s)
l.test('reverse_before_copy',b.replace(old,'bool reverse=m_template->m_D8 && obj->isKindOf((KindOfType)0x41);Coord3D goal;'+copy))
if not l.besttext.startswith('// '+l.symbol): (l.dir/'best.cpp').write_text('// '+l.symbol+'\n'+l.besttext)
l.done()
l=Lab('005863e5',1607);b=l.base
# Copy the actual deltas directly instead of staging three scalar locals.
a='float x=last.x,y=last.y,z=last.z;\n   x-=unit->m_position.x; y-=unit->m_position.y; z-=unit->m_position.z;\n   delta.x=x; delta.y=y; delta.z=z;'
c='float x=point->x,y=point->y,z=point->z;\n    x-=attacks[follows].previousPosition.x; y-=attacks[follows].previousPosition.y; z-=attacks[follows].previousPosition.z;\n    delta.x=x; delta.y=y; delta.z=z;'
assert a in b and c in b
x='delta.x=last.x-unit->m_position.x;delta.y=last.y-unit->m_position.y;delta.z=last.z-unit->m_position.z;'
y='const Coord3D &previous=attacks[follows].previousPosition;delta.x=point->x-previous.x;delta.y=point->y-previous.y;delta.z=point->z-previous.z;'
l.test('direct_path_delta',b.replace(a,x))
l.test('direct_follower_delta',b.replace(c,y))
l.test('both_deltas',b.replace(a,x).replace(c,y))
l.done()
l=Lab('0008458a',1422);b=l.base
# Different legitimate helper argument ownership; no shared math header changes.
for sig in ['const Matrix3D&A,Vector3 v','Matrix3D A,const Vector3&v']:
 l.test('transform_argument_value_'+sig,b.replace('const Matrix3D&A,const Vector3&v',sig))
l.done()
l=Lab('004e7506',1355);b=l.base
# Title/details form one real value sent to the help constructor.
s=b.replace('UnicodeString title;\n UnicodeString details;','struct HelpText {UnicodeString title;UnicodeString details;} text;')
a=s.index('struct HelpText');e=s.index('\n TreeHintRef00217D4C help',a)
part=s[a:e];part=re.sub(r'(?<![.>\w])title\b','text.title',part);part=re.sub(r'(?<![.>\w])details\b','text.details',part);part=part.replace('UnicodeString text.title;UnicodeString text.details;','UnicodeString title;UnicodeString details;')
# Avoid shadowing with existing detail-local variables.
part=part.replace('} text;','} helpText;').replace('text.title','helpText.title').replace('text.details','helpText.details')
s=s[:a]+part+s[e:].replace('new InGameSimpleHelp(title,details)','new InGameSimpleHelp(helpText.title,helpText.details)')
l.test('help_text_record',s)
l.test('help_text_reverse_members',s.replace('UnicodeString title;UnicodeString details;','UnicodeString details;UnicodeString title;'))
l.done()
# Reconstruct the existing patch against its named original blob in scratch only.
s=Path('build/crack-g/game_refresh.cpp').read_text().replace('// cl:','// cl: /I.',1)
for x,y in [('../../../../Libraries/','Code/Libraries/'),('../../../../../reference/','reference/'),('../../../Include/','Code/GameEngine/Include/')]:s=s.replace(x,y)
Path('build/crack-g/game_refresh_ready.cpp').write_text(s)
l=Lab('0024877a',1349,source='build/crack-g/game_refresh_ready.cpp');b=l.base
# Keep the visibility Boolean in a nested class with the real conversion, instead of extending its live range.
s=b.replace('bool hidden = true;','struct Visibility {bool hidden; __forceinline bool isHidden()const{return hidden;}} visibility; visibility.hidden=true;').replace('hidden = false;','visibility.hidden = false;').replace('if (hidden)','if (visibility.isHidden())')
l.test('visibility_value',s)
l.test('visible_only_const',b.replace('bool visibleOnly =','const bool visibleOnly ='))
l.done()
