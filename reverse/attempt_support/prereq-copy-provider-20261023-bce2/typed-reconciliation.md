# Scoped string-record constructor identity correction

Continuation at BFME 2 `0f2f7c97da7`, BFME 1 `138757e9b74645fbcbb7724a7af2764e34931e11`.
The preceding `readme.md` preserves the target call-chain evidence and failed trials.

The 96-byte vector copy at 0x002CFE45 invokes the string-bearing record worker
0x004F5097, whose construction chain is 0x002CF99D -> 0x002CF5B1. That chain is
already owned by `BfmeStringRecord002CF5B1`; it is not the raw three-word record
used by the separately verified push_back/overflow path. This is a scoped type
identity correction, not a global rename of PrereqUnitRec or a claim that the
original application record name has been proved. The existing address-derived
string-record name retains its uncertainty.

The new constructor trial uses that existing string-record declaration and its
natural AsciiString destruction. It emits the retail 96-byte instruction shape;
only the as-yet-unregistered typed allocator getter and count-base references
remain unresolved. Each helper independently emits the complete exact retail
body (7 bytes at 0x0021983A and 60 bytes at 0x005C8C37), including relocations.
They require normal verified ICF admission, not guessed address pins.

`eh_verify.verify_row` on the trial constructor returns EXACT. A diagnostic
`link_check.check_object` against census 456ce161c5 returns no unresolved,
duplicate, COMDAT, address or selected-provider blockers. This is preliminary
object evidence, not a final production link preview or byte admission.

The earlier conclusion that the parent's 96-byte local helper emission itself
prevented linking was too broad: current retail-truth-4 accepts the existing
retail-exact 38-byte provider under the same typed name. The raw global record
has no such correct provider. Declaring the typed worker external (both explicit
specialization and extern-template trials) instead produces a 105-byte parent;
neither variant is installed. A declared-only element destructor was unresolved;
natural AsciiString destruction removes that dependency without changing the
parent or its exact EH graph.

The old constructor and its associated handler claim are retracted separately,
as required by add_match.py for a real-name takeover. The original body remains
in its source until the replacement is verified. The retraction and corrected
provider/caller work must publish together; do not publish the interim deletion.
The historical raw constructor pin remains only during that transition, then
must be removed after its caller uses the typed provider.

## Completed production correction

The corrected source owns the 96-byte parent and 10-byte handler under the
existing string-record type. The typed 7-byte allocator getter and 60-byte base
are admitted through `add_match.py --icf-owner`, with complete bytes and
relocations verified against their existing owners. There are no new pins.
ProductionPrerequisiteCopyCtor.cpp now declares the same typed first vector;
its 77-byte constructor, 68-byte science-vector copy, handler and unwind body
remain exact. The obsolete raw constructor pin is removed. Other raw-record
users retain their distinct verified representation.

Production `build.sh` checks all three provider/caller/helper files: **11/11
rows exact**. Both parent exception graphs are **EXACT**. The caller's compiler
label changed from $L6107 to $L6736, but the verifier independently binds it to
the same 11-byte unwind at 0x00777283; no object-symbol alias was added or changed.
Both changed files pass find_declared_unmatched, and check_csv/pin_consistency
pass. place_bodies rescans both files and finds zero additional bodies or pins.
See `typed-build.txt` and `typed-link.txt`.

The link preview now reports all three files **LINKS**, 265 -> 437 attributed
file bytes. The corrected constructor source changes 0 -> 172 attributed bytes,
while the caller remains 145 and the existing helper provider remains 120.
The 172 includes the two pre-existing ICF bodies (67 bytes), so it is not a
172-byte unique recovery or a new census result. The substantive repair makes
the existing constructor and handler link; unique exact C++ coverage is unchanged.

The separate retraction commit's normal hook also verified all 440 affected
dependent sources (5,831 functions), 711 exact EH graphs, and converged data
identity. No gate, baseline or alias exception was needed.
