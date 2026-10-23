import sys,subprocess,json,itertools,concurrent.futures
from pathlib import Path
sys.path.insert(0,str(Path('tools').resolve()));import build
from locate import object_functions
D=Path('build/selection43003c-class-import').resolve()
s=Path('reverse/attempt_support/0043003c-20261020-codex7-prereqs/constructor-input.cpp.txt').read_text()
s=s.replace('template <> void **vector<void*>::end();','template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return this->_M_finish; }')
s=s.replace('template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &);','template <> __declspec(dllimport) __forceinline void vector<void *, allocator<void *> >::insert(void **p, unsigned int n, void *const &x) { _M_fill_insert(p,n,x); }')
