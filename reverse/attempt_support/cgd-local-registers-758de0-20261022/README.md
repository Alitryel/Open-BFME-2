# 0x00758de0: transient register allocation, 2026-10-22

Continue the assigned 333-byte `bfmeTwoCGD` body. The best bank is unchanged:
333 emitted bytes, zero relocations, 41 positional differences, first +0x94.
The historical score 0.9069 means 302/333 bytes in order-aligned instructions
whose mnemonic and operands both match. The mnemonic-first diagnostic in
`search.py.txt` reports 292 instead. No trial in this packet beats the bank.
No Code source, ledger, pin, compiler, or gate was changed.

The production pin belongs to `CollisionManagerImpl`; the bank's inherited
`BfmeThingCGD` name remains diagnostic scaffolding. The proven extent is 333B,
not the ordinary four-INT3 boundary finder's 411B. See the previous
`cgd-source-shapes-758de0-20261022/README.md` and
`cgd-vcall-758de0-20261020/README.md` for identity and source-shape evidence.

## Inputs and checks

- Start tree `9e45654020`; clean committed BFME 1 pointer and checkout
  `37c3022de1ab944c7ffe536440d637dc8199091c`.
- Pulled master; `check_csv.py` passed (98,064 functions, 15,855 symbols,
  2,128 data rows). Read this body's history through `pick-hard --rva`.
  Acquired its claim before work. Broad reference and dump queues were skipped
  for the standing assignment.
- The fresh BFME 1 update lock belonged to `claudec2`; under the runner's lock
  rule this seat skipped updating and did not mark freshness successful.
  `link_check.py --fetch-index` reused the local published index and fetched
  matching objects. No maintainer-only verification runner was started.
- MSVC c2.dll is 13.10.3077, image base 0x10700000, from the committed BFME 1
  VS2003 inputs. The bank uses `/O2 /MD /EHsc /I.`.
- Ten read-only debugger runs all emitted the bank's same 333B and zero
  relocations: SHA256
  `fb1009de36137ad2a9d51456fb0b4b6f75176beeca9c0e6292549ec39c845eb3`.
  `trace-checks.json` records these checks. The final steps replay was checked
  again after replacing a heap-address selector with ordinal 370.
- `tools/variant.py` independently recompiled the retained bank: 333B versus
  333B, 41 differing, first +0x94. These are diagnostic mismatches, not a match
  or an acceptance-gate rejection. Objects are private; no compile_source()
  call wrote the shared match cache.

## New compiler finding

The scratch-register choice is a rotating cursor, not a fixed EAX-first scan.
This rules out the earlier suspicion that EAX must be live at the inner test
vtable load. It is free and not forbidden at that allocation.

Read-only breakpoints traced local allocation at c2+0x75a70 and +0x75a87.
The former precedes choosing a destination; the latter precedes writing its
physical register. c2+0x75acc chooses a register when +0x759c0 supplies none;
the final assignment is `mov [ebp+0x1c],ecx` at +0x75ac4. Separate hardware
watchpoints confirmed that final write for the test's vtable and outer reload.
The watchpoint experiment is not needed to reproduce the retained cursor trace.

Key data in this compiler image:

- Physical symbols: 0x108a97a4 + 96 * register ID. IDs 1..8 are EAX, ECX,
  EDX, EBX, ESP, EBP, ESI, EDI. At +0x75a87, EAX is a descriptor whose word 2
  points to the selected physical symbol. The operand's word 7 has not yet
  been updated there; do not read it as the selection.
- 0x108a74f0 is the per-register holding array. 0x108a73c8 holds forbidden-set
  roots. Each root points to sparse chunks `[ordinal_base,next,bits]`.
- 0x108a7d0c points into the candidate list at 0x108a9738, beginning
  `[1,2,3,7,8,4,6,0]`. For this 0x1004 type, +0x7542e returns the current
  cursor. +0x7687e writes the advanced cursor; +0x76d36 supplies the wrap base.
- The unrelated chooser at +0x85179 mainly handles PUSH operands/renames.
  Its separate cursor at 0x108b022c is not the vtable-load allocator.

`cursor.json` retains before/after records, instruction words, symbols,
forbidden memberships and selections. `cursor-summary.json` is a compact
25-allocation view. Cursor offsets below are relative to 0x108a9738:

| Test-call operation | Ordinal in this stage | Cursor before -> after | Selection | Forbidden IDs |
| --- | --- | --- | --- | --- |
| first source | 220 | 0 -> 4 | EAX | 2,4,7 |
| outer vtable | 372 | 4 -> 4 | EDI | 1,2,3,4,7 |
| inner vtable | 370 | 4 -> 0 | EDX | 2,4,7 |
| normal address | 221 | 0 -> 4 | EAX | 2,4,7 |
| point address | 163 | 4 -> 4 | EAX | 2,4,7 |
| outer receiver reload | 371 | 4 -> 8 | ECX | 4,7 |

The 109-instruction `steps.json` replay follows the inner-vtable allocation.
It starts its search at ECX, finds ECX held, then accepts free EDX. It does not
consider free EAX before that choice. In the first response, the inner vtable
is forced to EDX by forbidden IDs 1,2,4,7,8; merely rotating the cursor will not
fix that region. The final reverse receiver reload again starts at ECX.

This is an observed compiler mechanism, not a claim that changing the cursor
alone solves the body. Retail also puts the inner target load after the
argument-address pushes. The bank's target load is already ahead of those
arguments in the pre-local-allocation IR. A source explanation must account
for that ordering and the different forbidden sets as well.

Do not correlate frozen HashVar creation records with these late symbols solely
by heap address or ordinal. Earlier exploratory tracing found that the IR and
symbol representations mutate/reuse storage across passes. H370's early
creation snapshot is not automatically the late vtable expression. The saved
cursor trace records the actual local-stage instruction and operand together.

## New source hypotheses tested

All 208 variants compiled; `trials.json` records counts, distinct hashes and
best scores. These families follow the transient-allocation investigation;
they do not repeat the older flag, profile, padding or permutation scans.

- **48 receiver-role models:** distinct first/second source and data types;
  common and separate bases; prepare-only, outer-only and full overrides;
  shared versus distinct opaque prepare-result types, including zero-offset
  covariance where legal; enum versus unsigned state. Every variant emits
  the exact bank bytes. The tested nominal role/type metadata does not move
  the scratch allocations.
- **32 explicit dispatch-table models:** dynamically read one-word member
  pointers at the proven ABI slots, mixed with compiler virtual dispatch;
  plain table storage, inline table accessors and inline method adapters.
  Nine distinct bodies, none better. This tests a different lowering from
  the old constant `&ContactSource::method` trials that add adjustor thunks.
  It is an ABI diagnostic, not target evidence for a hand-written table.
- **128 storage models:** full-width 32-bit state/index bitfields, anonymous
  unions, state signedness and pack 1/2/4/8 at unchanged field offsets.
  Two distinct bodies, none better. These test whether bitfield lowering
  leaves transient work that changes the local allocator's cursor.

Earlier independent explanations remain in the previous packets: control flow,
lifetimes and scopes, real BFME 1 vector headers and inline visibility, ABI,
compiler flags and LTCG profiles. No new missing function or prerequisite was
identified, so there is no justified blocked-on RVA. The best body is retained;
no nonmatching reconstruction was installed in Code.

## Continue here

Next investigate the pre-local ordering of the virtual-target load versus the
argument-address pushes, comparing a changed source's cursor trace with this
one. A useful source trial must change that ordering, the first response's
forbidden set, or the preceding zero-cost allocations; more nominal-type or
initialized-local scans without such evidence repeat known negative results.
No compiler or IR modification is a valid landing mechanism.

Copy the saved `.py.txt` files to an ignored directory two levels below the
repository root, remove `.txt`, and copy the bank there as `base.cpp`:

```text
python3 build/cgd-resume/trace_cursor.py
python3 build/cgd-resume/trace_steps.py
python3 build/cgd-resume/typedroles.py
python3 build/cgd-resume/search.py typedroles
```

The breakpoint addresses require this c2 image. Heap addresses in saved records
are observations from one run, not stable API. The steps selector uses late
ordinal 370 and must be reidentified after changing the source. The cursor
script reads the current pointers, so it is the safer comparison tool.
All debugger interactions are reads, breakpoints and stepping. The final
candidate is banked with the existing score; the unresolved task remains the
same three virtual-call sequences.
