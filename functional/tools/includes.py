"""Resolve bank include paths without choosing between competing headers."""
import re,subprocess
from pathlib import Path

def resolve(text,root,owner=None):
    resolved={};files=None
    def replacement(m):
        nonlocal files
        name=m.group(1)
        path=Path(name)
        if path.is_absolute():return m[0]
        choices=[root/path]
        if owner:choices.append((root/owner).parent/path)
        existing=[p.resolve() for p in choices if p.is_file()]
        if existing:
            selected=existing[0]
        else:
            # Historical bank TUs moved between Source subtrees. Accept an
            # unchanged Include/... suffix only when it names exactly one file.
            parts=list(path.parts)
            while parts and parts[0]=='..':parts.pop(0)
            if len(parts)<3 or parts[0]!='Include':return m[0]
            suffix='/'.join(parts)
            if files is None:
                files=subprocess.check_output(['rg','--files','Code'],cwd=root,text=True).splitlines()
            matches=[root/p for p in files if p.endswith('/'+suffix)]
            if len(matches)!=1:return m[0]
            selected=matches[0].resolve()
        resolved[name]=str(selected)
        return '#include "'+str(selected)+'"'
    return re.sub(r'^\s*#include\s+"([^"\n]+)"',replacement,text,flags=re.M),resolved
