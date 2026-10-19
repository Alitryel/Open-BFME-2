# GameState record construction at 0x002DCD64

The existing proper GameStateAddSnapshotBlock.cpp source naturally emits the
real `_Construct<GameState::SnapshotBlock>` parent, copy and complete EH graph.
No new type, class view, function body or compiler setting is needed.

Target evidence establishes the record's role and layout independently of the
matching copy. Registration at 0x002DE34B tests its Snapshot pointer and block
name, builds an eight-byte record and inserts it into one of five lists at
receiver+0x10. The verified native chain is
`2DE34B -> 2DDEA6 -> 2DDE02 -> 2DD021 -> 2DCD64 -> CF475 -> 365F0`.
The node creator allocates 16 bytes and constructs the record at node+8.
Lookup 0x002DCDBF compares its string at record+4; xferSaveData 0x002DCE24
uses the pointer at record+0 as the snapshot passed to the transfer operation.
Thus this is a Snapshot pointer and owned AsciiString, rather than an integer
key inferred solely from identical copy instructions.

The original nested `GameState::SnapshotBlock` spelling is carried from the
GameState reference contract already used by the verified registration source;
it is not an original BFME2 type signature decoded from the native bytes.
The current reference declaration is GeneralsMD/Code/GameEngine/Include/Common/
GameState.h:217, with its pointer/string fields at219/220 and list typedef222.
The prior BFME1 registration donor was revision1281192f682ce6f29b8f06b7daea4b5e8fdfbb24;
the current verified reference pointer stays cf0a80c228583af789772b794ab27abcab2debbf.
The canonical ASCII headers supply the existing string ABI.

The genuine copy is the complete 29-byte body at 0x000CF475, including its
sole +19 relocation to the rowed StringBase copy 0x000365F0. The actual
45-byte placement parent is 0x002DCD64..0x002DCD91. Existing pins already name
both real helpers at those addresses; this repair adds no pin or alias.

The native parent prologue loads handler 0x00778035. The complete ten-byte
handler names FuncInfo 0x0091FE50; its single-state unwind table independently
binds the fourteen-byte cleanup 0x00778027. The actual existing home emits the
entire associative graph EXACT with no placement conflicts. Its natural
current cleanup label is $L4812. All copy, parent, cleanup and handler code
and relocations match strictly, including the ordinary placement-delete call.

The previous refusal at 0x00778027 was correct: the old alias reused the
TreeKey parent and compiler label already owned at another address. The proper
GameState source now supplies the real independently supported parent identity.
Rehoming the existing 45-byte parent and fourteen-byte cleanup adds no coverage;
the previously unclaimed ten-byte handler is the new C++ recovery. The original
TreeKey parent at 0x000A7876 and its EH ownership remain unchanged.

Before admission, all 47 existing rows in both source homes were strict exact,
with the full-source hashes, effective flags, resolved hashes and EH verdicts
recorded in ignored `build/direct-loop/zh/41365ff056/gamestate-proof.json`.
Both declaration checks passed. The source change only corrects the stale
provenance comment; no body, lifetime, layout, label or optimization adjustment
is introduced. Independent review confirmed the target role/layout evidence
and distinguished the reference-carried type spelling before admission.

The shadow TU-routing diagnostic names GameState.cpp from agreeing neighboring
anchors (`by=C`, range 0x002DCB9C..0x002DCD9A). The current main unit explicitly
delegates registration and lookup to GameStateAddSnapshotBlock.cpp, which already
owns the verified node creator and insertion/lookup/transfer chain. Current COFF
shows that this established split home emits the sole genuine Construct; the
main unit emits none. The rehome follows that actual provider/consumer and EH
evidence. No routing manifest or verifier exception is changed.

Final verification passes all 48 rows across both homes and all 26 EH graphs
are EXACT. The actual code-identity check reports zero scoped problems;
there is one genuine parent definition with its exact owner/EH graph and no
family divergence. The normal fold judge reports unknown for that EH-bearing
owner, which requires no fold exemption: its ordinary owner binding is backed
by the full byte/EH checks. The SnapshotBlock copy separately certifies as a
fold at CF475. Declaration, canonical-class and pin checks pass, both source
units link cleanly, and the placement rescan finds no additional body or pin.
Only the obsolete parent object-symbol hatch key is retired; no pin or
verifier rule changes. Detailed final receipts are gamestate-identity.json,
gamestate-final-build.log, gamestate-link.log and gamestate-place.log beside
the ignored initial proof above.
