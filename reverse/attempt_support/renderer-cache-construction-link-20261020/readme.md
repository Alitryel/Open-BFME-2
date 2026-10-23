Renderer cache construction link repair, 2026-10-20

Parent 3d72ec1044. Unchanged published legacy census 5366c4f808, 12:21 UTC.
Rva00785FD0RendererReset.cpp defines the rowed 64-byte BFME2World cache. Its
implicit default construction emits a conflicting Matrix4 default constructor.
Use the existing bool constructor with false: the reviewed BFME1 header at
92f6bbe8e1dcdb46b5d27da0674313efc822b790 performs no stores on that path.
Static zero initialization therefore remains intact. No class or address alias,
new provider, layout inference or semantic owner change is introduced.

Paired current-object legacy preview before: reset 0, current begin/end provider
2740. After: reset 1195, provider 2740, total 3935. Gain attributable to this edit
is 1195 bytes; the provider's already-landed increase over census is excluded.
Self-strict preparation verifies 8/8 rows, the 64-byte data row and 14 float
references. Scoped gate verifies 6/6 rows, data and 11 floats, with the existing
funclet's renumbered label resolved by its parent EH graph. No failed byte trial.
No closed-strict or full-link claim. Declared definitions, class and ledger
checks pass; hooks verify EH and converged globals normally.

Same-cause sweep: texproject, decalsys, StreakRendererSetTextureBFME1 have local
matrix temporaries and respectively 16/9/23 independent census blockers; the
water draw unit has an independent private Matrix4 view and six blockers. This
static-cache constructor repair is not applied to their different lifetimes.

Hook shadow identity findings remain for Matrix4 assignment, subscript and row
Init copies. The enforced byte/data/EH gates pass; the gain above is legacy
preview only and does not establish their closed-strict identity. Follow-up
string assignment probe is recorded in re_attempts.log: extern-template erase
suppression changes the 153-byte caller frame 14 -> 0C. That trial was restored;
no speculative source edit is included with this measured repair.
