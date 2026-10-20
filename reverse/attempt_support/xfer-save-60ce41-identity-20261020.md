# XferSave slot 11: prerequisite identity repair

Target: 0x0060CE41..0x0060CF5A, 281 B, ret 4. Resume the w4 handoff and bank;
retain its opaque slot-11 argument identity rather than the refuted PooledString name.
Inputs: BFME2 43c6a1a69e, BFME1 4483e88da1c2f3b9a273f779baac7458bd8bb891.

## Retired placements

| RVA | Size | Old attribution | Native evidence |
| --- | ---: | --- | --- |
| 0060CAD8 | 5 | NameKeyType table bucket wrapper | jumps to string-key bucket helper 0060C9C3 |
| 0060CC85 | 20 | NameKeyType map find | calls string-key iterator find 0060CB7C |
| 0060CCD2 | 68 | NameKeyType table insert | calls resize 0060CBAC, string-key bucket 0060C9C3, allocate 003ED191 |
| 0060CDFD | 63 | NameKeyType map subscript | calls string-key find 0060CB7C and insert 0060CCD2 |
| 0060CBAC | 197 | basic_string-keyed table resize | rehash calls 0060C9A7 with the node key slot |

The bucket helper 0060C9A7 (23 B) dereferences its key-reference argument,
passes that char pointer to __stl_hash_string 0002BA61 and takes the bucket-count
modulus. The 54 B lookup 0060CB2B uses that string hash and compares node keys
by pointer. The 68 B insert links a 12 B node and increments table+0x10.
The save body writes a four-byte offset into node+8. These are native type/layout
observations: interned const char* keys, four-byte integer offset payload.
They do not establish the original typedef name.

The genuine integer-key subscript at 0041F4E5 also has 63 B, but calls
00148B27 and 0053F3B1, not 0060CB7C and 0060CCD2. It is therefore not an
ICF twin of the string-key subscript, despite the identical masked shape.
The old NameKeyType table find pin is corrected to 00148B27 with whole-body
fold proof from Rva00427157Ctor.cpp. The other four NameKeyType callee pins
and two resize-template pins lack the claimed identity evidence and are removed.
The existing NameKeyType node-allocation pin at 003ED191 is retained: allocation
and an eight-byte pair copy can genuinely fold across these key types.

Retraction is separate from the replacement recovery, as add_match requires.
The five old rows total 353 B; this is a correction of attribution, not new
reconstruction. A differently typed resize might fold in principle, but the
old opaque callee pins do not prove that; do not infer such a fold from masked bytes.

## Verification of the remaining GUI bodies

Normal build.sh after removal and corrected find pin: 11/11 rows exact in
Rva00427157Ctor.cpp, data row exact, string/float/import checks pass. Existing
EH label renumberings are verified by the parent EH graph. No GUI body edited.

## Replacement experiment

The bank's visible noinline find/subscript definitions plus the real STLport
hashtable<pair<const char*, int>, const char*, ...>::_M_insert produce the target
281 B and the prerequisite 63 B subscript, 68 B insert and 197 B resize with
unchanged instruction structure. Scratch flags /O1 /arch:SSE /G7 /DNDEBUG /MD,
_STLP_USE_STATIC_LIB, _STLP_NO_EXCEPTIONS, _CRTIMP=, existing bfmealloc shim.
The last macro affects STLport cleanup scaffolding only; XferSave still throws
normal C++ XferException values. Final acceptance requires all calls resolved,
whole-byte checks, EH graph checks and the normal hooks, not align_diff alone.

Do not add a flag_overrides.csv entry: the home xfer_save.cpp already receives
/O1 /arch:SSE /G7 from the retail TU region. Standalone scratch files do not,
so omitting those scratch flags misleadingly produces 439 B instead of 281 B.

Model: GPT-6 (Codex); original successful bank/compiler experiments: w4,
claude-opus-5-5, reverse/attempt_support/0x0060ce41-w4-20261020.md.

## Final integration and reusable compiler findings

Use the real STLport hashtable<pair<const char*, int>, const char*, ...>
insert, not a second guessed NameKeyType symbol. Whole-body checks, including
every call displacement, prove its 68 B insert, the 37 B node allocation,
23 B pair construction, 22/23 B bucket helpers and 48 B next-size helper.
The existing address-derived find/subscript views preserve the bank's visible
callee bodies, so the save body keeps EBX and its 0xC frame.

Keep resize in its existing StlSweepW4Rva0060CBAC.cpp provider with corrected
char-pointer/int types. The save unit declares that specialization out of line.
Moving resize into the save unit pulled in 14 conflicting vector COMDAT copies.
Suppressing those vector definitions with declaration-only specializations
changed the 197 B resize to 226/231 B with an EH frame; adding non-throwing
contracts removed the EH frame but still left 202 B and a different bucket
address calculation. This is further evidence that visibility affects alias
analysis and temporary lifetimes even when functions stay out of line.
MSVC 7.1 extern-template declarations did not suppress these inline copies.
Do not repeat those variants unchanged. The simple provider split preserves
exact 197 B resize and avoids those extra copies in the save unit.

The resize provider already had unresolved STL COMDAT selection debt in the
published index; repairing the table type does not claim that family fully linked.
The save-unit preview must be checked with the corrected resize provider and
retired lookup provider together, rather than against stale index definitions.

The save unit keeps only inline-only pointer-vector begin/size/subscript bodies;
these accessors have no competing out-of-line definitions there. The old strong
lookup provider is removed after moving its exact 54 B and 27 B rows into the
save unit. No artificial address anchor, header edit or compiler-override entry
is needed. The old five placements total 353 B and their replacements total
353 B; only the save body contributes 281 newly recovered unique bytes.

The prerequisite retraction commit passed all 13,672 rows in 1,556 candidate
caller units, their string/float/import checks and converged-data checks. EH:
1,798 exact of 1,799 checked, with one existing baseline difference and no new
debt. Removed names and an initially cold cache expanded this check; there was
no full-repository build or flag-override change. Concrete template spelling
and payload signedness are reconstruction choices, not independently proven
original target type names. Native key/payload access is separate evidence.
