# ProductionPrerequisite identity-contract prerequisite

2026-10-23, Seat2, gpt-6.1-sol; read-only native/COFF investigation.
No source/header/ledger/pin/tool/runtime/donor changes or compiler invocation.
This is an identity-contract prerequisite, NOT missing-body, semantic-failure,
false-reject or lane-exhaustion evidence. No replacement identity is proposed.

## Inputs and corrected counts

Seat HEAD: `37da166e7f2c3dd3130bc1042c66e765af3a3341`; inspected origin/master:
`11b387270007ad3228dc5dd261a5041b99d7f5ec`. Seat donor:
`138757e9b74645fbcbb7724a7af2764e34931e11`; root donor:
`96c88c73a5cd1a58fc2f8db691beea50acd996db`. Both relevant sources unchanged
against historical index b711de3634, 2026-10-23 14:28.

ProductionPrerequisiteCtor.cpp owns **9 main rows/385B + 7 EH rows/69B =
16 rows/454B**. ThingFactory.cpp separately owns **7 code rows/135B and one
4B datum**. Historical preview's 385B excludes EH; it is not the full TU.

## Native identity evidence

Addresses are RVAs; image base is 0x400000.

### 0x626DF0: signed /24, supported identity unresolved

`reverse/functions.csv:2144`: ThingFactory.cpp, 25B, nonweak signature
`?size@?$vector@VProductionPrerequisite@@V?$allocator@VProductionPrerequisite@@@_STL@@@_STL@@QBEIXZ`.

```text
8b018b51042bd0b8abaaaa2af7eac1fa028bc2c1e81f03c2c3
mov eax,[ecx]; mov edx,[ecx+4]; sub edx,eax
mov eax,2aaaaaabh; imul edx; sar edx,2
mov eax,edx; shr eax,31; add eax,edx; ret
```

Signed (end-begin)/24. Ctor target accesses instead support three vectors at
+0/+C/+18, parent36B, nested record pointer/flags/owning string +0/+4/+8,
stride12. Prior `reverse/re_attempts.log:80350` already records createContent's
36B stride versus this /24 identity issue; entry65262 does not resolve it.

Bounded scans: zero raw .text E8/E9 rel32 sites targeting626DF0; zero exact
little-endian four-byte VA00A26DF0 occurrences across PE raw sections. Neither
excludes computed/indirect references nor establishes dead stripping/type/name.
No independent name_basis/WB naming basis found. Normal naming helper says
non-placeholder; identifier rename preserves template/signature.
`docs/naming.md:90` and `docs/naming.md:145` prohibit inferred replacement of
real names or silent signature changes. No speculative rename/dry-run performed.

### 0x42816E: paired calls to the real 41B string assign

`reverse/functions.csv:2468`: ProductionPrerequisite::operator=,33B,
ThingFactory.cpp. Exact native bytes and calls:

```text
56578b7c240c578bf1e8449fbeff83c70c578d4e0ce8389fbeff5f8bc65ec20400
428177: call120C0 (this+0); 428183: call120C0 (this+C)
```

`reverse/symbols.csv:5073` binds nested-record vector assignment to120C0.
But `reverse/functions.csv:1629` names its actual 41B owner:
`?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ABV12@@Z`,
WWLib/stlport_narrow_string_assign_copy.cpp. Exact body delegates120F0:

```text
8b442404568bf13bc674188b50048b008d4c24085152508bcec644241400e80d0000008bc65ec20400
```

ThingFactory's emitted nested-record vector assignment is290B with allocation,
copy/destroy branches, not a whole-body ICF twin. This contradiction does NOT
recover the original parent assignment identity.

### 0x4EE1A9: real PerTurnStats owner, not owning-string copy

Nested-record copy pin: `reverse/symbols.csv:2119`. Actual39B owner:
`reverse/functions.csv:13219`, V3PolyCopyCtors.cpp,
`??0PerTurnStats@LivingWorldScoreKeeper@@QAE@ABV01@@Z`:

```text
8bc18b4c2404c700282ac600668b510466895004668b510666895006668b490866894808c20400
```

Vptr plus three16-bit fields, unlike emitted40B owning-string record copy with
imported InterlockedIncrement. Preserve prior bank
`reverse/attempt_support/prereq-copy-provider-20261023-bce2/readme.md` and
`reverse/re_attempts.log:82284`; no substitute pin/type follows.

## Selected historical COFF contracts

Root `build/orbstack/bridge12-parent-six-preview.log` and exact-name-only
inspection of `build/link_census/link_index.pkl`: all four names select
ThingFactory.obj ordinal4426 before ctor9505. Raw bodies and external-relocation
digests match the historical b711 selected entries, not global index currency.

| Nested-record emission | Selected ThingFactory | Ctor | Distinction |
| --- | --- | --- | --- |
| allocator::deallocate |32B/05f34940b7ad|20B/083eb30a50cf|NEWALLOC import vs game free|
| record operator= |79B/775f10fd69ea|34B/8a04f2b6e40e|inline atomic lifetime vs StringBase::set|
| alloc_proxy::deallocate |same32B/digest|same20B/digest|same allocation-family issue|
| range _Destroy |33B/226667acd409|25B/221ba106111a|selected wrong; ctor retail|

Minimal bytes/relocations (offsets section-relative):

```text
selected allocator/proxy deallocate:
8b4c240485c974158b4424088d0440c1e0025051ff150000000083c408c20800
 +22 DIR32 __imp_?deallocate@__new_alloc@_STL@@SAXPAXI@Z
ctor deallocate: 837c240400740aff742404e80000000059c20800
 +12 REL32 _free
selected _Destroy:
568b742408578b7c24103bf774108bff8bcee80000000083c60c3bf775f25f5ec3
 +19 REL32 ??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ
ctor _Destroy: 568b742408eb0a8bcee80000000083c60c3b74240c75f05ec3
 +10 REL32 same real destructor
selected record assignment:
8b4424045356578bf98b08890f8b50048d58088d77083bde895704742a8b0685c0741550ff15000000008b0683380075078bcee8000000008b0385c08906740750ff15000000008bc75f5e5bc20400
 +38 DIR32 __imp__InterlockedDecrement@4
 +52 REL32 ?freeBytes@AsciiString@@AAEXXZ
 +67 DIR32 __imp__InterlockedIncrement@4
ctor assignment:
8b442404568bf18b08890e8b480483c008894e04508d4e08e8000000008bc65ec20400
 +25 REL32 StringBase<char>::set (366F0)
```

Shared record teardown ALREADY agrees:577998/8 is `83c108e900000000`, +4 REL32
to36410. Selected AsciiString::releaseBuffer has existing real binding
`reverse/symbols.csv:9731`; ctor uses canonical StringBase::releaseBuffer.
No unresolved/wrong destructor lifecycle claim.

Pairing evidence: selected allocate32 multiplies count*12, imports NEWALLOC
allocate; allocate_and_copy146 uses it and proxy cleanup. Assignment290 reaches
that helper, clear78, copy141, rangeDestroy33; clear78 imports NEWALLOC free.
Native typed allocate395928/28 calls307F0(count*12,hint0); clear2D044B/30 calls
rangeDestroy2D02A8 then game free30830. Native307F0 and30830 use allocation
class3; NEWALLOC deallocate237B0/12 calls delete2FD60/21 using class1.
No independent deallocator swap is justified.

## Active source and immutable root artifacts

Ctor source: ProductionPrerequisiteCtor.cpp:1,40,66, canonical bfme2_ascii,
MD/GX, static STLport/malloc/no-exceptions/CRTIMP empty. ThingFactory.cpp:1
searches nat before bfme2_ascii_native_copy; receipt actually includes
nat/Common/AsciiString.h; sweep/PreRTS.h:19 selects NEWALLOC. ZH parent24B
has two vectors. Declaration-only suppression at ThingFactory.cpp:329..455
is INSIDE inactive CHECK_THING_NAMES (commented define328); it does nothing.
This corrects the earlier text-only reading.

Static configuration inspection: ctorO1; ThingFactory existing empty override
(`reverse/flag_overrides.csv:316`) leaves baseO2. Both truthful STLport, noFI.
Explicit include dirs exist seat-local. Runtime Windows translations remain
unresolved: no compiler_command/inspect_command/currency invocation performed.

Root-only artifacts inspected in place, never copied/restamped:
`build/match/^code_^game^engine_^source_^common_^thing_^thing^factory.obj`
and matching `.deps.json`. Before/after/final stat/hashes unchanged:

| Artifact | Bytes | inode | mtime_ns | ctime_ns | SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
|obj|58591|649784544|1792743502415759409|1792743502432538307|38c71a49b1a3678371e5f72947d0cfdac926fcb2f8276e65bb3ba42f366845af|
|deps|27977|649784545|1792743502431741596|1792743502433069351|854c09d7205435a90a6bbb615fc64ab19b7f0521c20b44f8164ed79062753d87|

Receipt sourceMD5 `47420438ea3cc3c7eb97db529943e806`, command hash
`d7cb461eb76dea08b9c1c87c8d4a83c9`. All256 dependencies match current root
and historical inputs (141 b711 repo blobs,115 donor138 blobs). Legacyv1 lacks
strict include inventory/compiler executable hashes; cannot establish strict
current receipt, runtime argv or current link closure. Root96 does not change
these particular headers. Reproduce only listed PE extents/four exact COFF
names and receipt dependencies; no full-index enumeration or compilation.

Verdict: identity reconciliation under normal naming rules is prerequisite.
No source-repair trial, layout/copy/deallocator swap, rename or rebinding.
