# Callback destructor duplicate: restored trial

At source base 3366f331c9, local index 19a2565407 (2026-10-15 09:33),
GameEngineControl.cpp has one duplicate blocker: its unrowed strong
Rva00211E75 destructor also appears as an identical inline copy in
AptTimeLineCallbacks.cpp. Both files and the class were claimed.

Strict baseline preparation passes all 16 rows. Removing the strong body
breaks the registration caller at 0x003FE7E6 (155B), including its cleanup
and register allocation. Making it inline passes all 16 rows and EH4/4,
but expands the derived Rva00211E75Callback destructor from a 5B tail call
to a 12B release, adding a COMDAT loser to GameEngineControl. Marking the
inline base destructor noinline also breaks the registration caller.
No trial is retained: the original file was restored and strict preparation
passes 16/16 again. Recorded blocked through re_log.py; all claims released.

A repair needs coherent derived-cleanup reconciliation; a declaration-only
or foldability change is insufficient. No pin, alias or compiler workaround
was introduced. Trial source/object/receipt snapshots and failure output remain
only in build/callback-dtor-link-20261015. No improvement is claimed.
