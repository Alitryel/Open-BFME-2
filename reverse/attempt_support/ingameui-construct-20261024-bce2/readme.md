# InGameUI construction identity correction

Examined at BFME 2 `98770f15719`, with the committed BFME 1 reference
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. The served repair was the whole
`Code/GameEngine/Source/GameClient/InGameUI.cpp` unit, including its five
function rows. This is an identity/ownership repair, not new unique C++ bytes.

## Native evidence

The 66-byte construction wrapper at `0x006896F0` calls the 122-byte copy
constructor at `0x00689650`. That constructor copies three strings at offsets
0/4/8, then the byte/dword/byte/dword fields at C/10/14/18. Its existing
verified owner is `Rva001D28F0Element` in `Open2Records.cpp`.

The former `pair<const AsciiString, list<SuperweaponInfo *> >` callee pin was
incorrect. The actual emitted pair copy is 81 bytes, first diverging at +0x28:
it copies a string and then a list, rather than three strings. Earlier attempt
records at `0x00689650` already identified this layout contradiction. A later
record inferred the pair identity back from the masked wrapper and was circular.
The attached diagnostic retains the native/compiled instruction comparison.

The existing vector provider
`Code/Libraries/Source/WWVegas/WWLib/Rva001D25F0VectorInsertOverflow.cpp`
already emits `_Construct<Rva001D28F0Element>` with all 66 bytes exact. Its
existing admitted pin and its vector callers establish the same family; no
new pin or guessed class name is needed. Its full EH graph is EXACT and places
the compiler-local cleanup `$L5221` at `0x007A7B10` (17 bytes) and its handler
at `0x007A7B21` (10 bytes). The cleanup location comes from the parent EH graph,
not adjacency. The attached JSON records the object-derived result.

The address-qualified record identity is retained. The existing VideoPlayer
donor and callback evidence suggests a video record, but this correction does
not assert an original EA class or member name. Target bytes establish the
layout; existing donor source supplies the C++ expression of that layout.

## Separate retraction and readmission

Retract the three false pair-family rows and its copy-constructor pin, remove
the forced pair instantiation, and tombstone the false identities in one
reviewable commit. Then admit the correct provider's parent, cleanup and
handler through `add_match.py`, verifying each body normally. This follows
`add_match.py`'s explicit rule that a real claim must be retracted in its own
commit before a different identity can own the address.

## File repair and remaining prerequisite

The InGameUI release build previously hid existing declaration-only providers
inside nested debug guards. Moving them into release scope, using the already
established superweapon-list lifetime providers, and removing the stale ZH
FloatingTextData destructor preserves all five original function rows and both
data rows. COMDAT blockers fell from ten to three before identity correction.
The real FloatingTextData destructor is separately owned at `0x0029D3B0`.

The file is not yet link-clean. Unmatched donor popup functions still call
unresolved UpdateDiplomacyBriefingText, MemoryPool allocate/free,
WindowLayout::destroyWindows, legacy UnicodeString::set and the two-boolean
GameLogic::setGamePaused. The existing selected MemoryPoolObject::deleteInstance
and WindowLayout::runInit also differ from retail. BitFlags<116> construction
and less<AsciiString> retain competing copies. The popup path mentions
InGamePopupMessage.wnd, with no matching native string-xref/ledger identity
found in this pass; do not map it to BFME 2 by a spelling guess. Those donor
functions need native identity/ABI work before further provider suppression.

## Reproduction

- Use the source files' committed `// cl:` settings and normal `./build.sh`.
- `explain_mismatch.py` on the pair copy at `0x00689650`, extent 122, shows the
  three-string/list contradiction; on the record construction wrapper at
  `0x006896F0`, extent 66, it reports an exact match.
- The record provider uses `/MD /EHsc /D_STLP_USE_STATIC_LIB
  /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
  /Ireference/shims/bfmealloc` and the canonical ASCII shim.
- `eh_verify.verify_row` and `verified_funclet_locations` on its normal built
  object prove the full parent graph and the local cleanup location.
- `link_check.py` reports this vector provider LINKS (620 bytes before the
  three rows are rehomed). InGameUI's remaining failures are recorded above.
