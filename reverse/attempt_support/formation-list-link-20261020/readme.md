# Formation-change list helper repair blocked

BFME2 88457d2ee5, donor92f6bbe8e1, existing /O1 /G7 /arch:SSE /EHs.
Baseline current-object preview:819 matched bytes do not link (iterator-base
operator!= and the local find copy). Typed static iterator!= removes its
wrapper while retaining both matched parent/EH bodies, but find still loses.
Its current handwritten direct loop differs from native0029B694/42, a wrapper
calling __find0029B2C4/35 with input_iterator_tag (existing proved providers
OpenContain and AIGroupMembership, pin already present).

Trial2 declaration-only find changes parent frame74 to70 and the later list
count loop/stack slots. Trial3 reconstructs the observed find->__find wrapper
with a visible noinline loop and typed inequality: helper link preview clears,
but the parent still takes frame70 and changes that count loop. Both trials
fail the811B parent; no more variants tried. Minimal final patch and complete
byte diagnostics retained. Original production source restored and verified.
Do not land only typed inequality: it leaves0 newly linked bytes. Next work
must preserve caller-visible summary/lifetimes while binding real list search.

The diagnostic patch has zero context; use `git apply --unidiff-zero`.
