import collections
import json
import re
import subprocess
import sys
from pathlib import Path

root = Path(__file__).resolve().parents[2]
scratch = root / 'build/resume-eh-local'
sys.path.insert(0, str(root / 'tools'))
import build, eh_verify

base = (scratch / 'turn48-money-visible-whole-dtor.cpp').read_text()
symbol = base.splitlines()[0][3:]
definition = 'template <> _MoneyOut money_put<wchar_t, _MoneyOut>::do_put'
variants = {f'parent-depth-{depth}': base.replace(definition, f'#pragma inline_depth({depth})\n' + definition)
            for depth in (1, 2, 3, 4, 8)}
force = '''namespace _STL {
template <> __forceinline basic_string<wchar_t>::~basic_string() {
 _STL::_Destroy(this->_M_start, this->_M_finish + 1);
}
}
'''
variants['force-whole'] = base.replace('#include <locale>', force + '\n#include <locale>')
results = []
image = eh_verify.Image()
for label, source in variants.items():
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
              'log': log.relative_to(root).as_posix()}
    for key in ('memory', 'register'):
        match = re.search(r'^\s+(\d+)\s+' + key + r'\s', proc.stdout, re.M)
        result[key] = int(match[1]) if match else None
    match = re.search(r'== structural regions: (\d+)', proc.stdout)
    result['structural'] = int(match[1]) if match else None
    if proc.returncode == 0 and size:
        output = build.obj_path(path)
        raw, relocs = build.read_object_symbol_bytes(output, symbol, code_only=True)
        names = collections.Counter(name for offset, kind, name in relocs if kind == build.REL32)
        result['whole_dtors'] = sum(v for k, v in names.items() if k.startswith('??1?$basic_string@G'))
        result['base_dtors'] = sum(v for k, v in names.items() if k.startswith('??1?$_String_base@'))
        result['free_calls'] = sum(v for k, v in names.items() if 'free@' in k or k == '_free')
        result['eh'] = eh_verify.verify_row(image, eh_verify.Obj(output), symbol, 0xdf20)
    results.append(result)
    print(json.dumps(result), flush=True)
(scratch / 'turn48-money-depth.json').write_text(json.dumps(results, indent=2) + '\n')
