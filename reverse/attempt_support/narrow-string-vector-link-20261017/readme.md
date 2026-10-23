# Narrow-string vector provider selection

Base: 28833619c4164247daf8ab24fdeb1467024975a9.
Published census: 2026-10-17 02:26 at fb06805bf5. Local compiled definitions
were refreshed; no census or status ledger was rewritten.

## Cause and change

The basic_string view in stlport_vector_narrow_string_destroy.cpp models only
destruction and a 12-byte layout. Instantiating the entire vector class also
emitted copying, insertion and growth routines using implicit byte copies.
Several of those definitions were selected ahead of verified retail providers.
For example, push_back(const string&) had digest 461361843254 (proven wrong),
while the three other copies had retail digest 3c274cfd2e65. The 55-byte owner
at 0x0007A773 calls the verified string constructor 0x00079A41 and vector
growth routine 0x0007A307, not implicit byte copying.

Instantiate only the vector destructor, _M_clear, clear and pop_back. Their
range-destroy dependency is still emitted; all five ledger bodies are exact.
No header, flags, pin, function row, alias, layout or baseline changes.

## Paired proof and verification

A single in-memory index was evaluated with the saved original object and
repaired object substituted at the same position. The edit removes 68 COMDAT
sections, adds none, and preserves all 20 retained COMDAT digests.
Of the removed names, 43 have no other definition; the repository's dependent
scanner found no additional consumers outside the evaluated source set.

comparison.json records all 29 evaluated sources. Unresolved names (29) and
duplicates (3) are unchanged; COMDAT conflicts fall 401 -> 392 and wrong
selected definitions fall 46 -> 25. No finding count increases. Two formerly
blocked units become clean: BfmeRva00C7B388Xfer.cpp and
stlport_uninitialized_copy_narrow_string.cpp. Other units retain their own
unrelated blockers. This is a local census prediction, not an executable or
runtime test. No new C++ coverage is claimed.

- Normal byte gate: 102/102 functions across all 29 sources.
- EH: 15/15 EXACT; zero baseline and missing-object cases.
- String, float and import checks pass with no unverified references.
- New-COMDAT-variant admission passes; placement rescan finds zero bodies/pins.
- Strict receipt preparation was attempted but cannot certify the text-transfer
  unit because an existing included header lies outside inventoried search
  roots. This does not replace the successful normal byte gate above; no
  closed-strict linkage claim is made and no verifier was changed.

## Reference review

Reviewed BFME 1 revision 3ce339fbfa7655686c7cf4d70088991e27a3062c. Its
BitFlags inverse-counter wrappers demonstrate explicit provider routing but
supply no narrow-string layout or body proof. Existing BFME 2 declaration-only
provider repairs supplied a lead; retail's vector/string providers and the
cleanup unit's actual compiled copies establish this repair independently.

Scratch proof script, before object and full logs remain in ignored
build/local-macos/linker-round2/.
