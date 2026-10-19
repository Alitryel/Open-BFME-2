# Exact recovery of 0x0005AC80

The coordinator can review the uncommitted source and ledger change, including deletion of the bank. The symbol is `?rva0005AC80@MilesAudioManager@@QAE?AVRva0036CA00Str@@ABVAsciiString@@H@Z`, size 291, in `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`. The input revision is `604081338152cd97711b8d9dd88d57a6db4f4e8b`. Model: `gpt-6.1-sol`.

## Evidence and uncertainty

Retail has a preceding RET12 at 0x0005AC7D, an independent EH prologue at 0x0005AC80, and RET12 at 0x0005ADA0 followed immediately by the next function at 0x0005ADA3. Vftable RVA 0x007C55B0 slot 73 contains VA 0x0045AC80. The body uses the manager's map at +0xBC, owning vector at +0xD4, flag at +0x6A4 and mutex at +0x9D4. Its find writes both iterator words. The complete raw-construction, copy, try-addref and release bodies establish four-byte counted handles and the atomic reference word at pointee+4. Raw target disassembly is in `build/5ac80-w4/retail.txt`; helper bytes and relocations are in `build/5ac80-w4/extra-helper-final.txt`.

The source retains the address-derived method, return-handle and metadata names. The four-byte storage views reconcile existing providers without asserting source-level inheritance or metadata identity. This is a retail reconstruction using existing BFME 2 helpers, not a Zero Hour or BFME 1 donor transfer.

## Experiments

All eight exact-RVA prior verdicts and the complete bank were read before experiments. None cited a separate evidence path. New hypotheses and their refutation conditions were written in `build/5ac80-w4/hypotheses.md` before their trials. Every trial source and raw output remains in that directory. Builds and measurements used `BFME_OBJSTORE=off`.

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Patched positional byte differences |
| --- | ---: | ---: | ---: | ---: | ---: |
| Original bank (`before`) | 280 | 5 | 5 | 7 | 167 |
| Explicit slot evaluation (`slot_first`) | 280 | 3 | 6 | 7 | 169 |
| Visible find (`visible_find`) | 280 | 5 | 5 | 7 | 167 |
| Visible copy (`visible_copy`) | 292 | 4 | 6 | 7 | 62 |
| Final home source (`home-trial4`) | 291 | 0 | 0 | 0 | 0 |

The slot and copy trials trade defect classes and were rejected. Visible vector push_back together with the existing visible construct/copy chain enables the retail stack overlap and distinct cleanup paths. The integrated source preserves the existing unchecked opaque-handle destructor by using checked AudioEventInfoRef locals. Explicit raw construction follows the home unit's existing storage-view convention and avoids MSVC's placement-new null guard. The helper audit corrected a trial's trivial-copy tag to the required nontrivial-copy tag. It also suppressed a competing vector clear instantiation by declaring the existing checked clear provider. The final 29-byte raw constructor, 31-byte copy, 18-byte construct, 55-byte push_back and 178-byte overflow match their full retail bodies with all relocations resolved.

## Validation

`add_match.py` admitted the body, appended its landed verdict and deleted the bank (`build/5ac80-w4/add-match-verified.txt`). No later verdict was recorded. The initial admission command rejected a comma in notes before making any ledger change (`build/5ac80-w4/add-match.txt`). Final gate outputs are `build-final.txt`, `declared-final.txt` and `pins-after.txt` under `build/5ac80-w4/`. `check_csv.py` fails because its tracked-file scan still includes the deleted, unstaged bank (`csv-after.txt`). Stage the bank deletion with the source and ledger changes before the coordinator reruns that check. No pins were added. No commit, network operation, claim command or background task was started.
