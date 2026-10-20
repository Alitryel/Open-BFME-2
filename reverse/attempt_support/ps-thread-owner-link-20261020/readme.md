PSThreadClass constructor ownership repair
=========================================

Starting revision be64bfb461. Published predictor index: 3f413ed3ff,
2026-10-20 18:52 (hash and object hashes in paired.json).

The constructor's native vtable at VA 0x00C6B0D0 has slots pointing to
RVAs 0x005543B9 (deleting destructor), 0x006104B0 (ThreadClass::Execute),
and 0x005580FB (PSThreadClass::Thread_Function). The existing named destructor
provider at 0x0055405A installs that same table and supplies the worker method.
This establishes constructor/deleting-destructor identity independently of
byte equality. Rename the opaque constructor owner to PSThreadClass, declare
its two real virtual slots in both constructor/caller views, and remove the
obsolete destructor alias pin. The pointer-map payload view remains provisional;
its existing verified offsets and template instantiation are retained.

Paired legacy prediction refreshes constructor, caller and named provider
against the same index on both sides. The before case uses saved original
objects and original symbol ownership/pin facts; the after case uses current
objects and repaired facts. Constructor 0 -> 107 B; caller 142 -> 142 B;
provider 21,845 -> 21,845 B. Total +107 B. This is a legacy prediction, not a
closed-strict measurement. No authored-byte growth is claimed.

Checks: ./build.sh on both edited units: 7/7 MATCH; strict --prepare-current:
7/7; EH verifier: EXACT 2/2; converged-data check: no second names or unjudged
rows; class gate and frozen-source check pass; check_csv and diff --check pass.
The named provider is unchanged and predicts LINKS together with both units.

paired.py.txt records the comparison method. Its saved before objects remain
local scratch; their hashes and original blockers are preserved in paired.json.
