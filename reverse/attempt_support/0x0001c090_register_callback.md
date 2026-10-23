# 0x0001C090 ios_base::register_callback (132 B) - tail edx/ecx wall

Bank: `reverse/attempts/0x0001c090.cpp` (129/132; only `&_iob[2]` temp at
+0x66/+0x6C/+0x6E is ecx where retail has edx). Session 2026-10-19,
claude-opus-5-5, t=40.

Target fact: retail iword (0x0001BF90, matched, same tail source) gets edx, so
the tail spelling itself can produce edx; the success path decides.

Bisection (same tail, /Ob0 /MD, scratch TU; register of the iob temp):

| success path                                              | tail | size |
|-----------------------------------------------------------|------|------|
| iword-shaped, `m_callbacks=..; return;` (no stores)       | EDX  | 105  |
| no tmp, `m_callbacks[i].first=fn; .second=index; i++`     | EDX  | 132 (success reloads index/base, 30 diffs) |
| tmp copy + `Callback *slot=&m_callbacks[idx]` field stores| EDX  | 127  |
| tmp copy + field stores through m_callbacks[m_callback_index] | EAX | 131 |
| tmp/local index + field stores (several spellings)        | EAX  | 125-128 |
| any 8-byte aggregate store `m_callbacks[idx++] = cb` (with or without tmp, cb fields in either order, `Callback cb={fn,index}`, ctor'd Callback, make_cb) | ECX | 132 (bank) / 136 |

So the ECX tail follows the struct-copy store; every non-aggregate spelling
that frees the tail loses retail's success shape (index cached once in edi,
fn/index in ecx/edx, then reloaded `m_callback_index` incremented in eax).

Also ruled out this session: `__forceinline` STLport helpers
(setstate/clear/_M_check_exception_mask/_M_throw_failure) - outlined under
/Ob0; without /Ob0 they inline and reproduce the bank's 3-byte diff exactly
(/Ob0 is not what decides it). grow_array returning a ctor'd GrowPair by value
(STLport `pair __tmp = _Stl_expand_array(...)`): base reloads (136 B), tail still
ECX. Tail respellings (`x = x | 1`, mask local, `_iob + 2`, msg/err locals,
`(void)index`, `+= 1`, ref-to-slot then `dst = cb`): all unchanged.

Untried lead: a no-op extra IL temp before the tail to rotate the scratch
choice (q1-q9 above found none that survives optimisation).
