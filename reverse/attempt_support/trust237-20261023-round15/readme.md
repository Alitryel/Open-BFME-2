# 0x237D3D: compiler pipelines on the NOP16 region winners

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA **0x237D3D**, extent **226**.
Previous handoff: `../trust237-20261023-round14/readme.md`. These trials use
BFME2 `0fa5a5b477dbcce1ec612e730ed954120ff59f11` and the unchanged bank,
with baseline flags `/O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc`.
Model GPT-6.1-sol. No BFME2 game source, function row, pin or verifier change.

## Hypothesis and finite results

The scoped history already disproved the recorded layout, lifetime, cleanup,
boolean, loop, barrier, atomic, return-carrier and ordinary padding matrices.
Round14 resolved every byte outside +CD..+DC. Earlier native/LTCG comparisons
used older source shapes, so this session tests the two new 226-byte region
winners through the available complete compiler pipelines. It does not repeat
the earlier source-shape matrices.

| Family | Choices | Successful outputs |
| --- | --- | ---: |
| Native | selected/alternate; RTM/SP1/DDK4035; O1/O2/O1+Og-; G5/G6/G7 | 54 |
| Ordinary LTCG | selected/alternate; complete SP1/DDK4035; same optimization and CPU choices | 36 |
| Recognition probes | RTM/SP1/DDK4035; `__nop`/`_nop`, sixteen calls | 6 compiled; **0 recognized intrinsics** |

The 90 candidate outputs form **12 distinct code-and-relocation groups**.
Every body decodes completely, and none contains a decoded NOP. Native and
ordinary LTCG produce the same group set. Both complete non-RTM tool profiles
were checked against the previously recorded tool hashes before use.
All three native profiles reproduce the selected bank's exact raw bytes under
O1/G6. Best remains **226 bytes, prefix 205, 16 positional differences**, all
at +CD..+DC. Mnemonic score remains **70/86 = 0.813953**. Raw body SHA256:
`ffcdd41b39c5b09965e653b339f650fa9177c99056e8f6c4fcd52292d53753f3`.

The recognition probes all emit C4163, sixteen unresolved external calls, and
no NOP. Compilation success is not intrinsic recognition; these are not
candidate recoveries. They rule out these two intrinsic spellings under the
tested profiles, not an unknown compiler producer.

## Independent checks

`audit.py.txt` rereads all 54 COFF bodies and all 36 linked PE exports, checking
lengths, hashes, complete disassembly, call relocations and import/thunk names.
Its comparison uses actual API identities for operands. The native generator's
diagnostic resolver fills DIR32 operands from retail at the corresponding
offset; that shortcut is checked separately and is not used to establish the
audit's final differing positions. Linked calls are independently normalized
through their actual import tables. No full-byte gate landing is claimed.

The round14 independent Unicorn harness receives these 12 new groups, with
APIs relocated by name. All **7,968 executions** pass (166 statuses and four
LocalFree-return/argc combinations per group): constant return 1, stack
balance, callee-saved registers, caller-saved clobbers, API order/counts, GUID,
file16 and data44 fields. These finite behavior checks do not establish source
identity or byte equality. `audit.json`, `emulation.json` and `summary.json`
retain counts, group/body hashes and reproducibility digests.

## Remaining prerequisite and resume

The sole byte residue remains retail's **sixteen 0x90 bytes at +CD..+DC**.
There is still no evidenced C++ producer for that span and no missing game
callee. The current bank and round14 alternate are preserved unchanged.
Do not repeat the matrices above or the older matrices without new evidence.

`image_context.py.txt` adds a bounded target-image check that earlier padding
trials did not establish. In game.dat's executable sections, the target span
at RVA **0x237E0A** is the **only** maximal run of at least sixteen raw 0x90
bytes (894 runs of length at least two, maximum sixteen). WorldBuilder's
executable .text has 455 runs of length at least two, maximum two, and no
sixteen-byte run. `image-context.json` records section extents, image hashes
and the target context. This is a raw-byte distribution, not a classification
of every shorter run as instructions. It makes the span demonstrably unusual
within these images, but proves neither a patch nor an impossible C++ source.

The previously attempted PGO path remains a setup blocker: the complete
SP1/DDK profiles lack `pogodb71.dll` and instrumented links fail C1350/LNK1257.
A bounded search of local toolchain/support files found no DLL or installation
archive. GitHub code-search requests were filtered (403), so they establish
nothing about availability. No new PGO compile was run, and this session adds
no negative result against PGO-generated source. No asm/emit workaround or
post-link-patch claim is justified.

To reproduce, restore `pipelines.py.txt` and `audit.py.txt` under
`build/trust237-round15`, plus the previously tracked round9 frontend, round14
emulation harness, round5 base source and complete private LTCG profiles as
described by their handoffs. Run `pipelines.py native`, `pipelines.py ltcg`,
`pipelines.py intrinsics`, then `audit.py`. Generators use eight isolated
workers and unique object/PDB paths, never the production compile cache.

The separate BFME1 freshness prerequisite is recorded in
`../bfme1-freshness-20261023-f36a/readme.md` with its own receipts.
The target claim was released after recording the partial and preserving the
unchanged best bank. `check_csv.py` passed at session start and again after preparing the
evidence. Paired full gates passed for the reference update; they do not
make the banked nonmatching body an exact recovery. Authored C++ delta is zero.
This session's unfinished task remains the same 16-byte internal NOP span.
