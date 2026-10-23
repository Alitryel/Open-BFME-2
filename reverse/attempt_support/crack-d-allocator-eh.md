# Crack-d: retained empty allocator cleanup at 0x001F1609

The complete retail parent is 43 bytes, ending at 0x001F1634. Its EH state 0
protects the allocator proxy at `this + 8`; the cleanup eventually calls the
shared empty return at 0x000B3FD0. The 14-byte bank omits that lifetime state.
The existing Object-pointer vector name is already pinned with caller evidence;
this experiment does not add identity evidence.

A newly tested compiler lever **can reproduce the complete 43-byte parent**:

```cpp
template<class P, class T, class A>
struct _STLP_alloc_proxy : A {
    P _M_data;
    __declspec(dllimport) __forceinline ~_STLP_alloc_proxy() {}
};
```

The ordinary parent scorer reports exact bytes with resolved calls. This is
**not a valid recovery**. COFF `.text$x` contains a DIR32 relocation to
`__imp_??1?$_STLP_alloc_proxy@PAPAVObject@@PAV1@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ`.
Retail's unwind action directly transfers to its empty destructor, with no such
import. No import alias, data address, pin, or matched row was added.

Two other diagnostic categories also retain the state and emit a 43-byte parent:

* A destructor containing a compile-time dead deallocation branch. This is an
  artificial source operation without donor evidence, so it was not landed.
* Explicitly calling the allocator base destructor through a cast or reference
  in the proxy destructor. That also leaves implicit base destruction to occur;
  it is not an acceptable lifetime model. It was not landed.

These probes narrow the wall: the compiler must see substantive destruction
before optimizing the cleanup to an empty return. An empty destructor's mere
visibility, `noinline`, export, force-inline, delayed definition, an ordinary
empty member cleanup hook, and a scalar pointer pseudo-destructor all retain the
14-byte result. Generic helpers calling a base destructor exhibit the same
invalid repeated-destruction issue; scalar generic destruction is neutral.

The saved production-eligible bank remains the honest 14-byte reconstruction,
score 0.5730462519936204. No attempt to exploit the fact that a parent-only
byte check does not validate the whole unwind graph was made.

Reproduction scratch (this worktree only): `build/crack-d/allocator/`:
`proxy_14.cpp` (imported inline parent exact), `body_38.cpp` / `body_39.cpp`
(dead branches), `destruction_4.cpp` / `destruction_6.cpp` (repeated base
lifetime), and `member_6.cpp` / `scalar_0.cpp` (honest neutral controls).
Scripts: `build/crack-d/allocator_trials.py` and `allocator_round{2,3,4}.py`.
No census or verification runner was started. Model: GPT-6.
