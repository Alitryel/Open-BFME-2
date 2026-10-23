# vector element placeholder link wall: 0x00565B7D `_M_insert_overflow`

`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod40_overflow.cpp`
(`?_M_insert_overflow@?$vector@UBfmePod40...`, 183 B at 0x00565B7D) is matched
byte-for-byte but `link_check` reports it does not link. The census keeps
another unit's copy of the same COMDAT names; this is a class-identity wall,
not a body defect.

## Census copies (link order; digest, retail verdict)

| Name | Copies | Overflow's copy |
|---|---|---|
| `_M_insert_overflow<vector<BfmePod40>>` | pod_vector_bodies 240 B wrong, pod_vector_malloc 240 B wrong, pod_noexc 189 B wrong, pod_deque 240 B wrong, pod40_lower_bound 240 B wrong | 183 B **retail**, ledger owner |
| `_M_clear<vector<BfmePod40>>` | the four pod units 14 B each, all wrong | 30 B unknown |
| `_Construct<BfmePod40>` | pod_vector_malloc/pod_vector_bodies/pod_noexc/pod_deque 22 B each, all wrong | declared only (calls the pin) |
| `_Destroy<BfmePod40*>` / `__destroy_aux<BfmePod40*>` | five pod units 1 B each | 24/26 B |

The link keeps the first copy (`stlport_pod_vector_bodies.obj`), whose
`_M_insert_overflow` is 240 B and proven wrong, so the matched 183 B row is
held out.

## Retail call map of the 183 B body

```
0x565BAC -> 0x4B4039  allocate (rowed)
0x565BBE -> 0x52C915  __uninitialized_copy (rowed)
0x565BD3 -> 0x52C320  _Construct (row 0x52C320 = _Construct<Rva0052BD59>, 45 B)
0x565BDE -> 0x565BF6  tail
0x565BEB -> 0x56561E  __uninitialized_fill_n (rowed)
0x565C09 -> 0x52C915  __uninitialized_copy
0x565C16 -> 0x5659E8  30 B tidy (row Rva005659E8::tidy, Rva005659CATidy.cpp)
```

The tidy at 0x5659E8 is 30 B and calls `Rva0052C266DestroyRange` (0x0052C266,
24 B, `Rva0052BF33DestroyTagged.cpp`) then `free`. That destroy range takes
`Rva0052BF4DElem *`, and `Rva0052BF4DElem` is declared with a **virtual dtor**
(`Rva0052BF33DestroyTagged.cpp:30-32`, same in `Rva005659CATidy.cpp:30`).
So the real 40 B element is `Rva0052BF4DElem`, not a synthetic
virtual-dtor `BfmePod40`. `symbols.csv` line 68 pins
`_Construct<BfmePod40>` to 0x0052C320 with no note, aliasing a third spelling
onto the `_Construct<Rva0052BD59>` row.

## Root cause and prerequisite

Two real 40 B types share the placeholder `BfmePod40`:

* the pod units' trivial `int a[10]` (find/push_back/copy-ctor rows depend on
  `a[0]` at offset 0);
* this unit's virtual-dtor / `Rva0052BF4DElem`-like element (the 183 B body and
  the 30 B tidy need the nontrivial destroy path).

The COMDAT names collide because the placeholder spelling is the same. A
correct fix is a class-contract/identity change, not a body edit:

1. adopt `Rva0052BF4DElem` (or the real 40 B type) as this unit's element;
2. repoint the 30 B tidy row 0x5659E8 to the canonical
   `_M_clear<vector<...>>` owner, and the 183 B row's symbol to the same type;
3. keep the pod units' trivial type distinct (their rows depend on its layout),
   or suppress their five wrong helper copies together with the class decision.

Suppressing only the four wrong `_M_insert_overflow` copies lets the 183 B
body win, but the `_M_clear`/`_Construct`/`_Destroy` blockers remain, so the
unit still does not link. Do not make a one-unit edit without the type
decision; it would leave the helper names split and could change the pod
units' verified bytes.

No source or pin was changed for this finding. `link_check` on the unit:

```
Code/Libraries/Source/WWVegas/WWLib/stlport_vector_pod40_overflow.cpp: does not link
  comdat    __destroy_aux<BfmePod40*> (differs from the first copy, no retail address)
  comdat    _Destroy<BfmePod40*> (differs from the first copy, no retail address)
  selected  _Construct<BfmePod40> (kept definition is not retail's)
  selected  _M_clear<vector<BfmePod40>> (kept definition is not retail's)
  selected  _M_insert_overflow<vector<BfmePod40>> (kept definition is not retail's)
```
