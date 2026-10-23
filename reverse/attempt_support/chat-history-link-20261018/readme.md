Chat-history storage and helper bindings, 2026-10-18

Paired replacement of the same four objects against census c2c5ac8c27 predicts
three newly clean units: clear 30 B, LANChatHistory 132 B, AddChatText 107 B;
0 -> 269 nonpadding matched bytes. This is a legacy preview, not a measured
closed-strict link cycle. All four objects have strict reusable byte receipts:
14/14 functions and the new 24-byte datum pass verification.

Target evidence: retail initializer 7AF10C constructs two 12-byte vectors at
VA E022F8 and registers cleanup 7B7DD1; clear381C2D, read381618 and write381C82
independently use that storage. The old vector declaration had no definition.
One inert six-word storage provider preserves the retail explicit lifetime.
The descriptive global name does not assert an original source identity.

The reader imports out-of-line UnicodeString inlines; the writer declares the
already rowed push_back specialization and binds the existing listener list
using its owner's type and a local view. These avoid wrong helper copies and
an undefined alternative global mangling. Retained COMDAT bytes are unchanged;
the only changed relocations rename those two globals. proof.py compares every
retained COMDAT, lists all removed helper closure members, verifies current
receipts, and performs before/after predictions against one index hash.
Baseline objects are local in build/seat8-chat/before; their hashes are recorded.

The initializer consumer also uses the sole storage name, but still has ten
independent unresolved names listed in proof.json. It gains no linked bytes.
The listener list's existing legacy storage providers need separate cleanup;
no closed-strict data closure gain is asserted here.

Checks: ./build.sh on all four files; link_check.py --prepare-current on all
four before and after; data_rows.py --verify on owner; data_check.py --converged;
paired proof.py; check_csv.py; normal commit/push hooks. No full link runner.
