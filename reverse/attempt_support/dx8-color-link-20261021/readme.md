# DX8 colour helper ownership

At 97b9990df9, published index 2b4d1fb42a (2026-10-21 06:00), current-object
link_check reports this unit 0/654 real bytes linked: duplicate Clamp_Color
and Convert_Color_Clamp definitions. The owner emits strong functions; both
renderer consumers emit COMDAT copies. Change the owners to noinline inline
functions and keep both emitted with an absent-from-retail anchor. This
changes linkage only; the native bodies, flags and existing inline assembly
are unchanged. No new address, name, pin, layout or source identity claim.

Acceptance: whole-unit build 3/3 exact rows (250,399,6 B), three float
references, zero skipped references; --prepare-current repeats the byte and
reference gates with a strict reusable receipt. No EH-bearing rows. Class,
declared-definition, enforced converged-data (10 addresses, zero second names
or unjudged rows), and whitespace checks pass. Same-index current-object
link_check now LINKS, 0 -> 654 B. This is self-strict byte verification with
a legacy census prediction; no actual placement or closed-strict gain claimed.

Cause sweep: index consumers SimpleStreakRendererRenderStreak.cpp and
StreakRendererRenderStreak.cpp have many independent blockers; the former is
foreign-claimed. No additional linked bytes claimed or source edits made.
Existing BFME1 emitter ownership repair evidence and verified donor revision
are recorded in ../metaimpact-float-link-20261021/readme.md. This repair imports
no donor code; the source already carries the ZH/BFME1 semantic provenance.
No full census or maintainer-only verification runner was started.
