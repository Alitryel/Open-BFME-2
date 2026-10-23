# Full donor math-header context

One candidate derived from `../translation_lifetime/value_reference.cpp`.
Prior adaptation was read from `build/nbr/r53/102f83/base_real.cpp` and br2.cpp.
The reduced Vector3/Vector4/Matrix3D classes and duplicate Length/Distance
definitions are replaced by actual donor matrix3d.h and its includes.
The source adds the real WWMath include directory, retaining the compiler
settings. Compile-time checks establish Vector3=12, Vector4=16, Matrix3D=48.

Necessary API adaptations (explained before compilation):

- Donor Vector3 has no assignment from Coord3D, so mode-2 `sourcePos=v->pos`
  becomes `sourcePos.Set(v->pos.x,v->pos.y,v->pos.z)`.
- Donor Matrix3D::Row is protected, so the listener-position block uses the
  same Get_Translation()+XYZ copy adaptation as the previous full-header trial.

Compilation succeeds. The include receipt confirms actual donor matrix3d,
vector2/3/4, wwmath, always and visualc headers, without substituted math headers.
The include-inventory wrapper reports unknown macro/parent-traversing roots;
the actual dependency-content hashes are nevertheless preserved in donor.deps.json.
This is scratch diagnostic evidence, not a valid census receipt.

Result: complete extent 4261 bytes, fitness 0.8061378482, 57 relocations;
baseline 4286 bytes / 0.931171. Normalized full diff worsens179 to466 changed
instructions. No integration or broader full-header variants were attempted.

The sole unresolved target relocation is the emitted local AnimatedTransform
default constructor. Its complete emitted body is22 bytes, byte-exact after
relocation against existing Matrix3D default constructor RVA0x000423C5, with no
unresolved references (constructor-proof.json). It calls the already-matched
Vector4 default ctor and vector constructor iterator. Thus it is a compiler-local
folded-name admission issue, not a missing semantic method. No pin was added.

The candidate was sent to the other support seat for read-only final Rotate_Y
symbol/key comparison; actual nested donor context may explain symbol numbering
differences even though the full candidate regresses overall.

Reproduce with `python build/camera-causal-20261021/full_math.py`.
