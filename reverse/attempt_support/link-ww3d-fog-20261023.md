# WW3D Fog namespace linkage

Base 4918fcf957; published retail-truth-4 index 456ce161c5, 2026-10-23
06:28. Model gpt-6.1-sol.

The constructor at 18BEC7 embeds the namespace at +4. Its standalone
constructor 18BE7E installs native table BD5BD4, whose slot 1 is the
already-rowed SourceNamespace_Fog::ResolveBindings at 18BFCE. The paired
WorldBuilder body A38B40 asserts the complete nested name at
fxshadernamespaceww3d.cpp:102. This is target identity evidence, not an
inference from matching bytes. Existing two-slot prefix views and offsets
are preserved; this does not claim a complete class contract.

Reconcile both lifetime units to the existing nested class and rename the
three member rows plus the data-ledger vtable. No pins, aliases, or new
coverage. rename.py dry-run refuses a qualified destination as not a C++
identifier, so the documented manual canonical-rename procedure is used;
all three old rows have tombstones.

Paired current-object legacy preview before: constructor 0/120 B, destructor
92/92 B, binder 603/603 B. After: 120/120, 92/92, 603/603 B. Thus +120 B
newly linkable, not the index's misleading +815 B total. No closed-strict
or census gain is claimed.

Acceptance: 18/18 functions, one data row, nine strings, three floats and
two imports pass link_check --prepare-current with strict reusable receipts
for all three providers. Both EH parents are EXACT. check_csv and
find_declared_unmatched pass; converged data check has zero second names
and zero unjudged rows. Whole-tree data_ledger --check is unavailable: 1,519
matched sources lack local objects. It was not treated as a passing check;
only the proven table spelling is changed.

Freshness: official BFME1 master fetched to f5140c1cff6a58e16276fd6de6788186286953d4
from verified pointer 96c88c73a5cd1a58fc2f8db691beea50acd996db. Its intervening
link repairs were reviewed (EAStringC inline default constructor, string
assign(first,last), empty AsciiString, ScoreScreen global and road duplicate
removal). EAStringC pattern is already inherited in BFME2. No pointer
change: baseline full byte verification was cancelled after waiting over
five minutes on the shared compiler lock. No successful freshness stamp
was written; rerun the paired verification when that compiler is available.
