from lab import Lab
import re
l=Lab('000eafa4',232);b=l.base
for kind in ['ref','ptr']:
 s=b.replace('int typeIndex = records[index].type;', ('Rva000EAFA4Record &tree = records[index];\n        int typeIndex = tree.type;' if kind=='ref' else 'Rva000EAFA4Record *tree = &records[index];\n        int typeIndex = tree->type;'))
 a=s.index('int typeIndex =');s=s[:a]+s[a:].replace('records[index].','tree.' if kind=='ref' else 'tree->')
 l.test('typed_record_'+kind,s)
 l.test('reuse_arg_'+kind,s.replace('int typeIndex =','index =').replace('typeIndex','index'))
 for qual in ['const','volatile']:
  l.test('type_lifetime_'+kind+qual,s.replace('int typeIndex =',qual+' int typeIndex ='))
l.done()
l=Lab('004b13d8',470);b=l.base
s=b.replace('#include "Code/Libraries/Include/Lib/Coord3D.h"','#include "Code/Libraries/Include/Lib/Coord3D.h"\n#include <vector>\n// stlport')
s=s.replace('Rva004DD018 **m_begin;\n\tRva004DD018 **m_end;\n\tchar m_pad98[4];','_STL::vector<Rva004DD018 *> m_entries;')
s=s.replace('frame.cursor = m_begin; frame.cursor != m_end','frame.cursor = m_entries.begin(); frame.cursor != m_entries.end()')
l.test('actual_vector',s)
l.test('vector_unqualified_iterator',s.replace('**volatile cursor','**cursor'))
l.test('vector_const_iterator',s.replace('Rva004DD018 **volatile cursor','_STL::vector<Rva004DD018 *>::const_iterator cursor'))
l.done()
l=Lab('00032830',227);b=l.base
s=b.replace('int volatile m_count;','int volatile m_count;\n void acquire(){EnterCriticalSection(this);++m_count;}\n void release(){--m_count;LeaveCriticalSection(this);}')
s=s.replace('EnterCriticalSection(lock);\n\t\t++lock->m_count;','lock->acquire();')
s=re.sub(r'--lock->m_count;\s*LeaveCriticalSection\(lock\);','lock->release();',s)
l.test('visible_lock',s)
for e in ['(unsigned char)addressType != 0','(addressType & 0xff) != 0','*(const unsigned char *)&addressType != 0']:
 l.test('lock_flag_'+e,s.replace('*(volatile unsigned char *)&addressType != 0',e))
l.done()
l=Lab('00759490',363);b=l.base
s=b.replace('unsigned char buf[44];','struct PairSeed { Rva009A3540OpaqueOwner *a,*b; unsigned key0,key1,count; Rva009A3540PairNode::Link l14; unsigned pad1c; Rva009A3540PairNode::Link l20; unsigned pad28; } seed;')
for old,new in [('*(Rva009A3540OpaqueOwner **)buf','seed.a'),('*(Rva009A3540OpaqueOwner **)(buf + 4)','seed.b'),('*(unsigned int *)(buf + 8)','seed.key0'),('*(unsigned int *)(buf + 0xc)','seed.key1'),('*(unsigned int *)(buf + 0x10)','seed.count')]:s=s.replace(old,new)
s=s.replace('memcpy(fresh, buf, 0x2c);','memcpy(fresh, &seed, sizeof(seed));').replace('(Rva009A3770Node *)buf','(Rva009A3770Node *)&seed')
l.test('typed_seed',s)
l.test('typed_seed_clean_conditions',s.replace('(bucket ? bucket : bucket)','bucket').replace('(bucket ? ((Rva009A3540PairNode::Link **)((char *)a + 0x20)) : ((Rva009A3540PairNode::Link **)((char *)a + 0x20)))','((Rva009A3540PairNode::Link **)((char *)a + 0x20))'))
l.done()
