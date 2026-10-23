import collections
import json
import re
import subprocess
import sys
from pathlib import Path

root = Path(__file__).resolve().parents[2]
scratch = root / 'build/resume-eh-local'
sys.path.insert(0, str(root / 'tools'))
import build

base = (scratch / 'turn48-money-visible-whole-dtor.cpp').read_text()
symbol = base.splitlines()[0][3:]
prefix = '''
// Preserve the vendor allocator machinery. Reconstruct just the proxy's
// destructor visibility locally; the data layout remains one pointer and
// its original allocator base. No shared header is changed.
#define _STLP_alloc_proxy _Turn48VendorAllocProxy
#include <stl/_alloc.h>
#undef _STLP_alloc_proxy
namespace _STL {
enum { _Turn48LeakCheck = 0 };
template<class Value, class T, class Alloc>
class _STLP_alloc_proxy : public Alloc {
public:
 Value _M_data;
 _STLP_alloc_proxy(const Alloc &a, Value p):Alloc(a),_M_data(p) {}
 DESTRUCTOR_BODY
};
}
'''
variants = {
    'empty-proxy': '~_STLP_alloc_proxy() {}',
    'native-proxy-lifetime': '~_STLP_alloc_proxy() { if (_Turn48LeakCheck) free(_M_data); }',
}
results = []
for label, destructor in variants.items():
    source = base.replace('#define private public',
                          prefix.replace('DESTRUCTOR_BODY', destructor) + '\n#define private public')
    path = scratch / ('turn48-money-' + label + '.cpp')
    path.write_text(source)
    proc = subprocess.run([sys.executable, str(root / 'tools/align_diff.py'),
        path.relative_to(root).as_posix(), symbol, '0x0000DF20', '2610'],
        cwd=root, capture_output=True, text=True)
    log = scratch / ('turn48-money-' + label + '.txt')
    log.write_text(proc.stdout + proc.stderr)
    size = re.search(r'ours (\d+) B / (\d+) insns', proc.stdout)
    result = {'variant': label, 'exit': proc.returncode,
              'size': int(size[1]) if size else None,
              'instructions': int(size[2]) if size else None,
              'log': log.relative_to(root).as_posix()}
    for key in ('memory', 'register'):
        match = re.search(r'^\s+(\d+)\s+' + key + r'\s', proc.stdout, re.M)
        result[key] = int(match[1]) if match else None
    match = re.search(r'== structural regions: (\d+)', proc.stdout)
    result['structural'] = int(match[1]) if match else None
    if proc.returncode == 0 and size:
        raw, relocs = build.read_object_symbol_bytes(build.obj_path(path), symbol, code_only=True)
        names = collections.Counter(name for offset, kind, name in relocs if kind == build.REL32)
        result['whole_dtors'] = sum(v for k, v in names.items() if k.startswith('??1?$basic_string@G'))
        result['base_dtors'] = sum(v for k, v in names.items() if k.startswith('??1?$_String_base@'))
        result['free_calls'] = sum(v for k, v in names.items() if 'free@' in k or k == '_free')
    results.append(result)
    print(json.dumps(result), flush=True)
(scratch / 'turn48-money-proxy.json').write_text(json.dumps(results, indent=2) + '\n')
