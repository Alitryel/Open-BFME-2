# Reconcile the existing 16-byte record interface

The 180-byte vector overflow at 0x00213E3B and 55-byte append at 0x00214243
used `struct Rva002111C8`, while the existing constructor, placement-copy,
assignment and range-copy providers declare `class Rva002111C8`. The two
spellings emit different MSVC names. Forwarding construction alone preserves
the wrong PAU/PBU interface even with an early class declaration: the later
struct definition controls the final mangling. The tested correction keeps
the same identifier, layout, members and public access and uses the existing
providers' class interface consistently. It also updates the opaque record
view in LivingWorldManagerCleanup, whose native call at 0x002142EA+240 reaches
this append body. This is an ABI correction, not a new application-name claim.

Target evidence establishes the 16-byte stride, the tracked 12-byte member
and trailing integer through the constructor/assignment bodies at 0x2111C8
and 0x2111E3 and their handle operations. Placement construction at 0x211DFB
is 18 bytes; the 38-byte copy and 37-byte fill at 0x211E0D/0x211E33 call it.
The 30-byte clear at 0x21397C calls the existing 25-byte destruction loop at
0x212AD6 and game free at 0x30830. The destruction loop steps by 16 and calls
the tracked-member destructor at 0x2115C5. These call edges supply the basis
for the two TU-local inline adapters; no empty destructor or alternate symbol
alias is introduced. Rva002115C5 is the existing opaque destruction view of
that record; the adapter does not read it through a new layout.

STLport 4.5.3 supplies the container algorithms; retail supplies the sizes,
boundaries and call relationships. BFME1 inputs remain at the already verified
0bf534ea7ccde110c456edb9cd2dd5dae823c953. The original application record name
and the opaque manager view's individual member meanings remain unrecovered.
No shared header, compiler option, record size or calling convention changes.

Normal pin admission proves four emitted template instantiations, including
every owner relocation: allocator 28 bytes at 0x2226BE, copy 38 at 0x211E0D,
fill 37 at 0x211E33 and clear 30 at 0x21397C. They have no separate target
addresses and carry fold-proof naming the consumer source. Five obsolete
struct-interface pins are removed; construction now directly calls its real
provider. The protected counter changes only from 2 to 1 at 0x211DFB; all
unrelated allowances and ordering are preserved. No new row or gen-alias is
used. Tombstones record the two superseded template signatures.

Fresh private before/after compiles preserve the entire 180/55-byte consumer
bodies and the manager's 112/283/10-byte bodies. Only the expected template
and constructor relocation names change; the manager changes one append
relocation and preserves the complete EH thunk. whole-body-proof.json records
the complete before/after relocation lists. No new runtime forwarding body
is required by either owned body.

Normal verification passes 13 rows across the two consumers and four native
provider units. The current linking preview, refreshed at 43103255a8,
passes all six units: 654 -> 889 existing linked bytes, a net 235-byte gain.
The manager and native providers retain all 654 previously linked bytes.
This is a prediction against the current shared index, not a new executable
link, census, boot test or C++ coverage gain.

Both changed units have strict current reusable receipts. The complete EH
graph is EXACT (one row, no baseline and no missing object), and the identity
shadow check reports zero new findings across five rows. The staged lost-name
scan finds no referencing units among 23,431 checked objects. Frozen-file
checks pass. Pin consistency and ledger checks pass without new debt.
