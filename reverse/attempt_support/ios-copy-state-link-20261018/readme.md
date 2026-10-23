# Stream copy-state CRT binding repair, 2026-10-18

Recovery status: the source repair is deferred; see recovery.md and the
complete deferred-repair.patch. The measurements below describe that patch,
not a currently landed linked-byte gain.

The matched 432-byte `_STL::ios_base::_M_copy_state` at RVA 0x0001C300
used unresolved BFME 1-derived placeholders for the CRT stream array and
failure output routine. Its private inline helper also emitted a non-retail
outlined copy. Keep the native inline failure path, declare the helper
dllimport/forceinline, and name its actual operands `stderr` and `fputs`.
The separately rowed outlined helper remains owned by narrow_istream.

Target evidence: the byte gate verifies all three failure paths against
retail, including their `_iob` and `fputs` imports. The existing rowed
`_M_throw_failure` at RVA 0x0001BC50 uses the same CRT operation. Donor
64d369b901's game/Libraries/Source/STLport/IosBaseCopyState.cpp also names
these CRT operands; only those bindings are inherited, preserving BFME 2's
existing class layout and inline control flow. The verified donor pointer
remains unchanged while another seat owns its freshness update.

A declaration-only helper trial changed the parent body and was rejected;
the retained implementation passes 1/1 function, three literals and thirteen
named import references. object-proof.json confirms identical function bytes
and exactly six relocation changes (three `_iob`, three `fputs`), with every
other relocation unchanged. No other current STLport/WWLib consumers of the
two placeholders remain to sweep.

Paired current-object checks against census c2c5ac8c27 change 0/1 to 1/1
clean, adding 429 non-padding linked bytes. Self-strict reusable receipts
also pass. This is a legacy link prediction, not a closed-strict or full-link
measurement; authored C++ coverage does not grow.
