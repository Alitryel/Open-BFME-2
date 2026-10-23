The file-factory unit no longer emits an unused, non-retail external copy of
`StringClass::Is_Empty`. It uses the existing
`reference/shims/bfme_part_emt_inline/wwstring.h` view directly, after `always.h`,
instead of the forced teardown include. The optimization, runtime and exception
flags remain unchanged. No shared header, pin, baseline or ledger range changes.

The two StringClass views retain the same donor declarations, layout and inline
bodies (recorded donor 6d9434269164392c5ba62aaa7c15a86b5b020d76). This unit uses
none of the named-terminator constructor option that the older inline view lacks.
The existing inline view adds dllimport/forceinline to Is_Empty. Its meaning
remains first-character comparison against m_NullChar. This follows the same
compiler-emission repair as BFME 1 commit 53d32d6b4b377317a3397971629ca3ad20b870e9;
the BFME 2 object comparison independently establishes acceptance here.

Before/after source base: bbcd996c12f8ca4e8283accf22d3d6869e72a3bc. Both snapshots
were prepared with strict reusable receipts and the ordinary byte gate:
33/33 rows exact, four string literals and three named imports verified.
The object proof removes exactly one 18-byte text COMDAT. Every other nondebug
section, including directives, and every relocation is identical after resolving
local labels by section content and offset. Is_Empty has no remaining definition
or reference in the after object. No caller, virtual table, EH action or data
binding changes.

Both local link predictions refresh the same explicit object against the frozen
runner index at a2839ea429 (2026-10-15 13:35), original census 5986a99448 (04:52).
Index SHA256: c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37.
Committed link_status.csv is a different measurement and was discovery only.
Legacy local findings fall from three to one: the Is_Empty losing COMDAT and
wrong-selected finding disappear. The FileFactoryClass scalar deleting destructor
still loses against retail; ordinary link_check therefore exits 1. Local LINKED
gain and new authored C++ bytes are both zero. This is self-strict object evidence
with a legacy local prediction; no closed-strict closure or full-link gain is
claimed. No census, index or status was written.

Additional acceptance: EH 9/9 EXACT; class and frozen-source checks pass;
data identity has zero findings; converged-data enforcement passes across eight
protected addresses; new-variants passes. Placement resweep reports zero bodies
and zero pins. CSV and diff checks pass. proof.json records the paired findings
and all object/source/receipt hashes; proof.py reproduces the comparison while
the local build/ffactory-empty-link-20261015 snapshots and frozen index remain.
Binary snapshots remain local scratch.

The remaining FileFactoryClass deleting destructor is the rowed 29-byte body
at RVA 0x0007827B in InlineDtorDeletingDtorsC01.cpp. Its nondeleting destructor
restores vtable 0x00BC6778 at RVA 0x00078274. The unwanted factory-unit copy
needs its own evidence-backed codegen repair. Do not repeat the particle-binder destructor suppression tried this
session: forceinline moves the saved-ECX reload and ordinary inline adds imported
destructor calls. Both failed the normal 70-byte destructor gate, the source and
receipt were restored, the claim released, and the blocked verdict recorded.

BFME 1 freshness remains outstanding: clean verified checkout/gitlink
a7c38d3b2597121f178ab5190b3062478823257d, fetched official master
95eeb3bef370a7cd730b0ad5f228c317c8756e72. Its pointer is held by another seat's
file claim. No pointer advance or successful freshness stamp is asserted.
