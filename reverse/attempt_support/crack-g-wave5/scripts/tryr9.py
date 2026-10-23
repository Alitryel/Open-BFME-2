from lab import Lab
from pathlib import Path
import re
l=Lab('004dd018',494);b=l.base
s=b.replace('if ((unsigned int)b < (unsigned int)it->second)','const _STL::pair<const int,int> &expiry=*it;\n    if ((unsigned int)b < (unsigned int)expiry.second)').replace('if (TheGameLogic->m_frame < (unsigned int)it->second)','const _STL::pair<const unsigned short,int> &expiry=*it;\n    if (TheGameLogic->m_frame < (unsigned int)expiry.second)')
l.test('map_payload_reference',s)
s=b.replace('*(float *)&a = 0.0f;','float attributeValue = 0.0f;').replace('(float *)&a, 0','&attributeValue, 0').replace('0.5f > *(float *)&a','0.5f > attributeValue')
l.test('real_float_local',s)
l.test('map_and_float',s.replace('(arg->m_04->m_5D8 ? arg->m_04->m_5D8 : arg->m_04->m_5D8)','arg->m_04->m_5D8'))
l.done()
l=Lab('003b5ea5',1818);b=l.base
arm='''if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[1] = new Parameter((Parameter::ParameterType)0x34, 0);
				pScriptAction->m_parms[2] = new Parameter((Parameter::ParameterType)0x34, 0);
			}'''
assert arm in b
# Introduce a genuine legacy-schema repair helper before ParseAction, after the complete class.
pos=b.index('ScriptAction *ScriptAction::ParseAction') if 'ScriptAction *ScriptAction::ParseAction' in b else b.index('ScriptAction* ScriptAction::ParseAction')
for spec in ['static __forceinline','static inline','static']:
 helper=spec+' void repairLegacyPair(ScriptAction *pScriptAction) { '+arm+' }\n'
 l.test('legacy_pair_helper_'+spec,b[:pos]+helper+b[pos:].replace(arm,'repairLegacyPair(pScriptAction);'))
l.done()
l=Lab('0058277c',1844);b=l.base
b=b.replace('(player ? (msg->GameToJoin.iniCRC) : (msg->GameToJoin.iniCRC))','msg->GameToJoin.iniCRC')
l.test('remove_uninitialized_condition',b)
# Keep the genuine serial string lifetime scoped to the first loop; name/slot scans don't use it.
a=b.index('\t\t\t// check for a duplicate serial',b.index('void LANAPI::handleRequestJoin'))
z=b.index("\t\t\t// We're the host",a)
s=b[:a]+'\t\t\t{\n'+b[a:z]+'\t\t\t}\n'+b[z:]
l.test('serial_string_scope',s)
l.test('serial_scope_counter_init',s.replace('Int player;\n\t\t\tBool canJoin','Int player=0;\n\t\t\tBool canJoin').replace('\t\t\tplayer = 0;\n\t\t\tif( canJoin )','\t\t\tif( canJoin )'))
l.done()
l=Lab('0009b7ea',698,source='build/crack-g/0x0009b7ea/main/best.cpp',label='extent_lifetime');b=l.base
for scope in ['forward_first','extent_first']:
 s=b.replace('Vector2 extent(hi.X-lo.X,hi.Y-lo.Y);','Vector2 extent;extent.X=hi.X-lo.X;extent.Y=hi.Y-lo.Y;')
 if scope=='forward_first':s=s.replace('Vector2 extent;extent.X=hi.X-lo.X;extent.Y=hi.Y-lo.Y;\nVector3 forward=tm.Get_Z_Vector()*-1.0f;','Vector3 forward=tm.Get_Z_Vector()*-1.0f;\nVector2 extent;extent.X=hi.X-lo.X;extent.Y=hi.Y-lo.Y;')
 l.test(scope,s)
l.done()
