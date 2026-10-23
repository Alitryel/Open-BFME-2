OpenContain constructor link prerequisite, 2026-10-23

At census 491a8b3d87, current scoped legacy check remains 0/290 B.
The sole unresolved name is `_STL::_Rb_tree<Rva00463D59Element,...>::~_Rb_tree`.
Native constructor 465124 reaches the matched set constructor 463D59 at
this+4C; its unwind action 78AC44 reaches wrapper 256641. The existing
rowed method `Rva00256641::rva00256641` tail-jumps to the rowed
`Rva00255CD1::~Rva00255CD1` at 256461. These are target call relationships;
the original element identity is unresolved.

Trials with original /O1 /G7 /arch:SSE /EHsc flags:
- Forceinline wrapper destructor calling rowed rva00256641 preserves 11/11
  parent/funclet byte checks, but implicitly destroys the set afterwards;
  link check still reports missing tree dtor and now a wrong wrapper copy.
- Replace the set member lifetime with same-size opaque Rva00255CD1 storage,
  construct its proven set header in place, and use the genuine dtor name.
  Typedef-qualified explicit constructor syntax is rejected by VC7.1.
  Standard placement construction compiles, but an implicit Rva00256641
  constructor remains out of line: native call463D59 becomes unresolved
  ??0Rva00256641@@QAE@XZ at the same parent call site. No pin was added.

Original source restored. No linked-byte gain. A correct complete tree/member
contract or inline construction boundary is still needed; do not repeat these
forms. The published set ctor unit suppresses the same unavailable destructor.
Diagnostic source delta: lifetime-trial.patch (apply only as an experiment;
its parent does not byte-match). The original source was restored and rechecked.
