from lab import Lab
import re
l=Lab('003b5ea5',1818,label='member_repair');b=l.base
arm='''if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[1] = new Parameter((Parameter::ParameterType)0x34, 0);
				pScriptAction->m_parms[2] = new Parameter((Parameter::ParameterType)0x34, 0);
			}'''
for spec in ['__forceinline','inline','']:
 s=b.replace('static ScriptAction *ParseAction(', 'static void repairLegacyPair(ScriptAction*);\n static ScriptAction *ParseAction(',1)
 pos=s.index('ScriptAction *ScriptAction::ParseAction')
 s=s[:pos]+spec+' void ScriptAction::repairLegacyPair(ScriptAction *pScriptAction){'+arm+'}\n'+s[pos:].replace(arm,'repairLegacyPair(pScriptAction);')
 l.test('member_helper_'+spec,s)
 l.test('member_without_pragma_'+spec,re.sub(r'^#pragma optimize.*\n','',s,flags=re.M))
l.done()
