# Lobby pair destructor binding

At 3882266a14, using published census c2c5ac8c27 (2026-10-18 11:36), the current lobby unit has 240 unique matched bytes and is blocked only by its implicit AsciiUnicodePair destructor copy. Declaring the destructor binds the existing 53-byte copy instead of emitting this unit's conflicting copy. Current-object legacy predictions change from 61 to 301 linked bytes across the consumer and BfmeNodeValueEBDDestructor.cpp: +240 bytes. No closed-strict or runtime claim.

The two caller rows pass the strict byte gate with normal literal/import checks; after restoring the PeerDefs provider object, code identity reports one shadow wrong-binding finding for the folded destructor. Its EH-local relocation is unproven, rather than byte-disproved. The earlier provider-absent scan reported no finding; that incomplete result is superseded by identity.txt. Existing pin consistency identifies the destructor with the 53-byte BfmeMappedValueEBD owner at 0x0038240F. The kept same-name PeerDefs.cpp copy is 53 bytes and calls wide releaseBuffer and AsciiString destruction in that order, matching the owner's member operations; PeerDefs' 104 ledger rows independently passed strict provider preparation. Its local EH identity remains an unproven census copy, so this is a legacy link prediction, not a closure certificate. No pin, alias or class layout was added.

The blocker index and source users were searched for this same destructor cause; no second blocked consumer was found. The existing BFME 1 pointer and donor scan are unchanged from the preceding repairs; the target caller and provider establish this local repair.

## Preserved session evidence

Upstream d7c6e39c53 already holds the identical destructor declaration.
Recovery retains that source and its comment; no additional 240-byte gain
is claimed. Its detailed provider/identity caveats above supersede any
less complete earlier statement. The independently saved report follows.

# Lobby pair destructor ownership

Rva0059FD3APopulate.cpp generated an implicit AsciiUnicodePair destructor
that differed from the kept PeerDefs.cpp copy. Declare the destructor and
call the existing provider. Both views contain AsciiString at +0 and
UnicodeString at +4 followed by six integers. Existing copy ctor 0x382444,
the consumer's native cleanup call and the pre-existing destructor pin at
0x38240F establish this shared lifetime. No new pin, name or layout change.

The current PeerDefs object contains the complete 53-byte destructor at
0x0038240F: build.compile_function with the existing object (no compilation)
compares equal to retail, with no unresolved relocations. Its wide release
and narrow destructor targets agree with the owned BfmeMappedValueEBD body.
pin_consistency.py --symbol reports consistent with that owner's 53B extent.

Explicit current-object link_check.py consumer before: 0 -> 0 B, sole pair
COMDAT blocker. After, with current PeerDefs provider: consumer LINKS,
0 -> 240 B; PeerDefs remains independently blocked. Index c2c5ac8c27,
2026-10-18 11:36. Legacy same-index gain only; no closed-strict gain claimed.
The current-ledger check still lacks 46 objects (layer-vector3-link-20261018).

build.sh and link_check.py --prepare-current pass 2/2 rows, data row passes,
zero string/float/import references, strict reusable receipt. Definition
check passes. The index has only these two pair-destructor emitters, so the
consumer completes this cause's eligible sweep. No full link/census run.
