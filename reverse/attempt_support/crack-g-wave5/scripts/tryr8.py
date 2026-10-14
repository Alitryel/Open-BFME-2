from lab import Lab
import re
l=Lab('001e6007',1295);b=l.base
s=b.replace('MoveCoordinate newGoal(goal->x,goal->y,goal->z);','Coord3D newGoal;').replace('} else {\n  newGoal.x-=obj->m_pos38.x;', '} else {\n  newGoal.x=goal->x;newGoal.y=goal->y;newGoal.z=goal->z;\n  newGoal.x-=obj->m_pos38.x;')
l.test('branch_coordinate_init',s)
for source in [b,s]:
 l.test('result_direct_init',source.replace('Rva003642DFResult result;\n  result=path->rva00364521','Rva003642DFResult result=path->rva00364521'))
 l.test('result_field_copy',source.replace('Coord3D m_pos; };','Coord3D m_pos; Rva003642DFResult(){} Rva003642DFResult(const Rva003642DFResult&o):m_node(o.m_node){m_pos.x=o.m_pos.x;m_pos.y=o.m_pos.y;m_pos.z=o.m_pos.z;} };'))
l.done()
l=Lab('002f07f5',637);b=l.base
# True footprint records give the two traversals independent lexical lifetimes.
s=b.replace('Int lastX=cell.x+above;','struct Bounds {int x0,x1,y0,y1;}; Bounds bounds={cell.x-below,cell.x+above,cell.y-below,cell.y+above};\n  Int lastX=bounds.x1;').replace('Int x=cell.x-below;','Int x=bounds.x0;').replace('Int firstY=cell.y-below,lastY=cell.y+above;','Int firstY=bounds.y0,lastY=bounds.y1;')
l.test('source_footprint_record',s)
l.test('neighbor_clean',s.replace('(found->y ? (y+deltaY[i]) : (y+deltaY[i]))','y+deltaY[i]'))
s=b.replace('Int lastX=destX+above;','struct Bounds {int x0,x1,y0,y1;}; Bounds bounds={destX-below,destX+above,destY-below,destY+above};\n Int lastX=bounds.x1;').replace('Int x=destX-below;','Int x=bounds.x0;').replace('Int firstY=destY-below,lastY=destY+above;','Int firstY=bounds.y0,lastY=bounds.y1;')
l.test('destination_footprint_record',s)
l.done()
l=Lab('0027b18c',755);b=l.base
# Read each volatile damage-kind test only where its original branch requires it.
s=b.replace('int event=templ->event598,other;','struct EventChoice {int event,other;}; EventChoice choice; choice.event=templ->event598;')
a=s.index('struct EventChoice');e=s.index('\n if(data->flag113',a)
part=s[a:e];part=re.sub(r'(?<![.\w])event(?!\w)','choice.event',part);part=re.sub(r'(?<![.\w])other(?!\w)','choice.other',part);part=part.replace('int choice.event,choice.other;','int event,other;')
s=s[:a]+part+s[e:]
l.test('event_choice_record',s)
l.test('event_choice_nonvolatile',s.replace('volatile int damageType','int damageType'))
l.done()
l=Lab('0009b7ea',698);b=l.base
s=b.replace('float width=hi.X-lo.X;float height=hi.Y-lo.Y;','Vector2 extent(hi.X-lo.X,hi.Y-lo.Y);').replace('*width','*extent.X').replace('*height','*extent.Y')
l.test('view_extent_vector',s)
l.test('view_extent_subtract',s.replace('Vector2 extent(hi.X-lo.X,hi.Y-lo.Y);','Vector2 extent=hi-lo;'))
l.test('projected_point',b.replace('const float &xx=Vector3::Find_X_At_Z','Vector2 projected; projected.X=Vector3::Find_X_At_Z').replace('float yy=Vector3::Find_Y_At_Z','projected.Y=Vector3::Find_Y_At_Z').replace('out[i].x=xx;out[i].y=yy;','out[i].x=projected.X;out[i].y=projected.Y;'))
l.done()
l=Lab('000e0856',621);b=l.base
for types in [('const float&','float'),('float','const float&'),('const float&','const float&')]:
 l.test('uv_constructor_refs'+str(types),b.replace('Vector2(float a,float b)',f'Vector2({types[0]} a,{types[1]} b)'))
l.test('uv_phase_lifetime',b.replace('float phase;\n Vector2 uv(0,phase=1.0f-(timeGetTime()%1000)/1000.0f);','const float &phase=1.0f-(timeGetTime()%1000)/1000.0f;\n Vector2 uv(0,phase);'))
l.done()
l=Lab('002a4bfc',547);b=l.base
# A real count cursor carries the shared remaining value across the two scans.
s=b.replace('int remaining=total;','struct Remaining {int value; __forceinline bool any()const{return value>0;} __forceinline void consume(){--value;}} remaining;remaining.value=total;').replace('remaining>0','remaining.any()').replace('--remaining;','remaining.consume();').replace('remaining=total;','remaining.value=total;')
l.test('count_cursor',s)
l.test('count_cursor_unsigned',s.replace('struct Remaining {int value;','struct Remaining {unsigned value;'))
l.done()
