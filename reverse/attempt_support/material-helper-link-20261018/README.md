MaterialInfo constructor/destructor: +357 B in the legacy link preview.

MaterialInfoClassCtor.cpp gains 142 B and MaterialInfoDtor.cpp gains 215 B.
The two private RefCountClass definitions now compile their inline helper
copies with the size settings used by the selected hlod.cpp provider. The
scalar deleting destructor becomes its identical 29-byte copy (formerly 31).
An unemitted static array-delete use in the destructor unit likewise selects
the native 75-byte RefCountPtr<TextureClass> array deleting destructor, replacing
its 84-byte copy; TextureHandleAssignment.cpp owns the verified retail body at
0x4559C. No emitted anchor, new alias, pin, or global is introduced. This adds
three scoped optimization regions; the settings restore at each boundary.

Paired objects were refreshed against the same c2c5ac8c27 census index without
writing it. Before: both units fail; after: both link in the legacy preview.
All ten ledger bodies, float/string/import checks, source-claim checks and the
declared-definition check pass. Both units have strict current compiler receipts.
All other nondebug bytes and relocations and all data facts are unchanged;
helper alignment changes from 16 to one byte where the size regions apply.
Data shadow checks report no findings; converged-data checks report no second
names at nine referenced addresses. No closed-strict gain is claimed.

The first-use helper emission pattern follows BFME1 1399ad37 (already used by
TextureHandleAssignment.cpp); RefCountClass settings follow the existing
BFME2 hlod.cpp provider, with exact object-body and relocation equality.
MaterialInfoCopyCtor.cpp remains blocked by its VectorClass<ProxyClass>
assignment provider, which has incompatible ProxyClass/helper definitions.
No zero-gain edit to that consumer or provider is included.

Separate restored attempts are logged in re_attempts.log: narrow ifstream
specialization changes lost matched emitters/bodies; Line3D needs cross-unit
class/vtable reconciliation; RenderObj ctor helper suppression changed its
native straight-line body into EH/array construction. Their claims were released.
