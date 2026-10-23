# Remaining Gen_p12pod provider blockers

Resume after 88457d2ee5, which already links the 182-byte insertion by fixing
all three copies of its four-word construction helper. These follow-up trials
are restored; no additional gain is claimed.

The map431B still emits the non-retail hinted insert that duplicates the
explicit native712B owner, plus a non-retail pair-key table clear. The hinted
owner also emits the non-retail allocator variant of _M_insert.

Trial1: declaration-only specialization of hinted insert in MapIndex,
imported-inline vector<void*> begin/size/subscript, declaration-only _M_insert
in the712B owner. Trial2: extern-template hinted insertion instead. Both byte
gates fail the map117B operator[] by moving zero initialization before the
argument-address setup, and stop emitting its rowed no-hint insert227B.
The712B owner itself still passes, but alone still meets the duplicate bad
hinted insertion from MapIndex. Keep both complete failed diagnostics and a
minimal candidate patch. No third unchanged declaration variant was tried.

The next repair needs visible callee behavior without duplicate emission and
explicit retention of the no-hint227B row. Do not repeat these two forms.
Inputs: BFME2 88457d2ee5, donor92f6bbe8e1, existing per-file cl flags unchanged.
The committed memberwise key copies are better verified work and are retained.

The diagnostic patch has zero context; use `git apply --unidiff-zero`.
