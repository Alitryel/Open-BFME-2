# Primary-template annotation trials (owner, 2026-10-23)
Original source flags; isolated compiler_command/subprocess objects, never shared cache.
All production and vendor files unchanged. No gate/pin/baseline edits.

v0: original wide imbue exact238B; conflicting narrow copy operator present.
v1: macro annotating operator keyword with dllimport: C2491 auto_ptr conversion
operators plus ignored-attribute warnings; too broad and invalid.
v2: keyword macro dllimport+forceinline: original238B preserved, conflicting
assignment remains (declaration position ignores attributes); no repair.
v3: scratch copies of string wrapper and _string.h, annotate only original
primary copy operator at beginning of declaration with dllimport+forceinline.
This removes external narrow copy assignment, but imbue becomes243B:
first stack-home differences at +0x2A/+0x46/+0x50, added tag-byte zero at +0x98,
changed cleanup free binding. Original primary body alone does not preserve
caller state after import annotation. No shared-header edit is justified.

Exact diagnostic sources and objects remain here. v3.asm.txt vs target.asm.txt.
The helper independently tests explicit imbue-body temporary/assignment variants.
