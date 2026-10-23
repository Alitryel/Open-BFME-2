Wide-string default cleanup, 2026-10-20
=====================================

Follow-on to8f9c79dbc7; same cause as the six callers in
../string-cleanup-import-link-20261020. The wide default constructor atDBC0
also called the rowed _String_base destructor through a nonexistent DLL
import in its exceptional cleanup. Declare that destructor out of line.
The normal allocation path and both matched rows remain byte exact.

Paired same-index proof: current baseline0/1 clean ->1/1, LEGACY0->110B
nonpadding linked. Strict-current2/2 touched rows and unchanged4/4 destructor
provider rows. All retained external COMDAT bytes/relocations are identical,
no added/removed external COMDATs. EH1 graph improves bytes_differ/dllimport
->EXACT. Drop this repaired baseline row(37->36), shrink-only checked.
Class, declared-definition, ledger, data and converged checks pass.
Closed-strict closure/gain is unmeasured. Other uses of inline-only imported
string destructors were inspected; empty/nothrow destructors not called out
of line do not share this exceptional-cleanup cause and were not changed.
