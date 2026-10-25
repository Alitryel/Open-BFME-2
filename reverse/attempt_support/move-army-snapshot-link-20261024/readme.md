# MoveArmy Snapshot record ownership repair

Status: separate retirement of eight mistaken/dependent claims (277B); production
source is unchanged and no new byte or LINKED gain is claimed. The source patch is a review artifact,
not an applied change. Original donor TracerFXNugget remains intact.

The live parser143B unit does not link because its one-slot class named
TracerFXNugget conflicts with the real multi-slot FX tracer and its constructor.
Native ctor4E1AEF17B clears strings4/8 and installs C61DB4. The69B destructor
4E1B00 destroys8 then4 and restores canonical Snapshot BBB554. Native C61DB4
has exactly four entries: deleting destructor4E1B45, empty post-loadB3FD0,
MoveArmy getter4E133C and DoXfer4E1302. Parser field tableC61830 names
ArmyScriptingName4 and TargetRegionName8, while DoXfer transfers those strings.
The existing Rva004E1B00 address name is retained because original C++ type
spelling is unknown. The adjacent Rva004E1B72 SetPlayerControlOfArmy record
already uses the same complete canonical Snapshot contract.

A real ZH/BFME1 TracerFXNugget initializes GenericTracer, two strings, multiple
float fields and RGBColor, and has FX execution virtuals. Its full constructor
cannot be the17B native MoveArmy record constructor. Its donor implementation
is preserved, with no invented register/lifetime consumers.

Private candidate proofs at d0247c24e4:

* Complete17/69/28/6/58/126-byte bodies agree after resolving only the new
  destructor callee name to its independently proved69B native target. All
  other known call relocations agree. No instruction prefix or extent is hidden.
* The complete MoveArmy literal, including NUL, equals native C61860.
* Both complete16B vtables resolve byte-exactly. Compiler-generated weak _E
  defaults to the actual new scalar _G28B; canonical Snapshot uses the existing
  strong _ESnapshot74B provider at1750, as the native table requires, rather
  than pretending the weak scalar fallback is its native table entry.
* The real empty LoadPostProcess override is exactly C3 with no relocations,
  independently matching the existing B3FD0 owner and native slot1.
* Existing eh_verify.verify_row reports EXACT for record destructor69B and
  parser126B. Its exact graph locates destructor cleanups791AD8/791AE0 and
  parser cleanup791B07. No cleanup location is inferred merely from equal bytes.

Cached experiments are diagnostic only. Unchecked DIR32 values are explicitly
listed in the proof and closed by the separate data/EH/literal graph above;
normal source admission and hooks remain required. No profile, pin, baseline,
whitelist or verifier is modified.

## Supported production workflow

Automatic approval review rejected an earlier combined source/ledger/tombstone
rewrite before execution because candidates still had needs-work diagnostic
labels and it would change real ownership before normal admission. No rejected
command was executed or reissued indirectly. The supported route documented in
add_match.py is a separate reviewable retirement commit for real claims,
followed by ordinary new-owner add_match verification. The plan JSON identifies
eight mistaken/dependent rows totaling277B to withdraw; native DoXfer58B is
already the correct address-named member and remains rowed in its source.
The final patch uses consistent full12B TU-local class views and the existing
Snapshot header; no new shared header is required. Existing copy-provider data
binding follows the corrected real table without adding another linker alias.
Actual new record functions and legitimate empty override must be admitted only
through normal add_match/ICF proof and all byte/EH/data/literal/import/identity
and provider/consumer link gates. No unsupported migration exception is used.

## Ordinary retirement hook dependency refusal

The unchanged-source retirement commit hook exited1 after44,496 bodies across
10,875 completed source units. No commit was created. Its final data check
correctly refused the complete256B LivingWorld act field table C6CD50: the
MoveArmy callback at+0x34 references the temporarily withdrawn4E1BFC parser.
This is a real dependency, not a false reject. Separate proof confirms all
256 initializer bytes,30 symbolic relocations, literals and sizeof agree with
retail when only the historical parser address is supplied to a private
in-memory diagnostic resolver; this is not a gate/admission receipt.

The private review plan preserves the exact correct data row for restoration
after ordinary parser admission. Any temporary proof-claim withdrawal must be
reviewable, leave all sources unchanged, pass ordinary dependency gates and
never be published before coherent restoration. The data identity is correct;
no false-identity tombstone, pin, alias, baseline or exception is proposed.
Normal store restores observed in the captured hook output total515 across37
reports; that is not a claim that all6,105 imported objects were used.

The reviewed narrow dependency withdrawal is now part of this retirement:
only the exact correct C6CD50 data proof claim is temporarily unrowed, with no
false-identity tombstone. Production code and table source stay unchanged.
The exact row and full30-relocation proof are retained here. This intermediate
commit must never be published alone. Restore the exact data row after ordinary
parser admission and pass full ordinary data verification before publication.

## Live copy-table bridge and shadow classification

The normal current copy-constructor object references external data symbol
`?g_00C61DB4@@3QBQBXB` through a DIR32 field at offset 34 of its complete
77-byte body; retail points to C61DB4. Its existing linker directive targets
`??_7Rva004E1B00@@6B@` with exactly the same alias mangling. The bridge is live
and not misspelled. The object hash, symbol, relocation and directive are
preserved in copy-alias-actual-object-proof.json.

The code-identity shadow scan calls this unreferenced because
allowed_symbols.Identity.row_refs deliberately excludes native targets outside
.text. A data-table target therefore cannot enter judge_alternatename targets.
This is a shadow classification limitation, not an enforced refusal, and no
check/register is changed. Ordinary data checks report no new findings.
Publication still requires complete current16-byte vtable/four-target proof,
the exact copy77 body and the final provider-consumer family link proof.
The parser now forward-declares Xfer only; its unused Version definition and
BfmeXfer dependency were removed without changing constructor17. The actual
DoXfer TU retains its required Version definition.

The real LoadPostProcess override is a complete C3 with no relocations; native
C61DB4 slot1 points to B3FD0. Ordinary add_match --icf-owner admitted it against
the adjacent Snapshot record and verified all owner bytes. The TU-ownership
shadow A1 second-row diagnostic is the shared empty-code address classification,
not a second physical body or an enforced refusal. No ownership/register rule
is suppressed and this folded method claims zero new unique bytes.
