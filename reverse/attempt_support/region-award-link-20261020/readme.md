RegionAwardDispute link repair, blocked at thunk admission (2026-10-20).

Base9e55e2f4f7; BFME1 reviewed92f6bbe8e1 for ownership-reconciliation method only.
Target table RVA7FE280/VA BFE280 contains2B647C,4FBFFD,2B6476,4FBDF7.
The existing parameter ctor4FC002 and default ctor2B644A share it. Existing
opaque destructor4FC05C called by deleting wrapper2B647C is therefore the same
RegionAwardDispute owner. Named getter2B6476 returns RegionAwardDispute;
4FBDF7 is the already rowed Xfer;5B4FBFFD tail-calls rowed evaluation4FBF8E.
The latter needs to be admitted as the real loadPostProcess member. Identity
and slots come from BFME2 table/calls, not donor bytes or class-name inference.

candidate.patch reconciles six units: public virtual destructor plus its pin,
default ctor/caller, full four-slot Snapshot views in table emitters, getter,
Xfer.48/48 existing rows byte-verify,40 strings exact; byte-check.txt records it.
A separate object inspection proves the new loadPostProcess member is exactly
5B including its sole REL32 to4FBF8E. Scoped same-index legacy link preview
changes the184B parameter-ctor unit from blocked to linked; other five units
retain their current bytes. No closed-strict or landed gain is claimed.

Admission command:
 python3 tools/add_match.py '?loadPostProcess@RegionAwardDispute@@UAEXXZ' 0x004FBFFD 5 Code/GameEngine/Source/Common/Rva002B644ACtor.cpp --replace-rva 0x004FBFFD --notes 'Native slot1 of the same BFE280 table as the named dispute constructors; complete five-byte member tail call to rowed evaluation4FBF8E; real C++ post-load override replaces anonymous thunk'
It refuses because old ?j_004fbffd@@YAXXZ in Code/gen_small/gthunks_000_admitted.cpp
has notes gen-thunk;gap;target=0x004FBF8E, a scaffold category absent from
replacement_scaffold. It requests retraction as a separate real-claim commit.
No workaround or verifier edit was attempted. Tooling lane should reproduce
this false rejection and add a regression proving safe replacement of an
identity-free generated thunk, preserving exploit refusals.

All production source/ledger changes restored; full patch banked here. The
preexisting BfmeE16 versus uint vector views are not reconciled by this patch.
Do not infer a new element layout from the matched ctor or destructor alone.
A global link_check --refresh was accidentally started, then stopped after
noticing it scans beyond explicit sources. All reported previews are from the
subsequent explicit six-source command without --refresh. No census or full
link verification runner was used.
