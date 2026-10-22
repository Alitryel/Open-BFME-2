# 0x758DE0: point-address global home and argument sharing

Continue the same assigned 333-byte body. The best bank is unchanged:
**333 bytes, zero relocations, 31 positional byte differences, first +0x94**,
SHA256 `01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
Its full-instruction alignment remains 308/333 (0.924924924924925).
No Code source, ledger row, pin, compiler setting or gate changed.

The production identity remains CollisionManagerImpl's pinned provider; the
bank's Contact* and BfmeThingCGD names are diagnostic structural names. Its
alternate fastcall interface on the reverse call is still an unproven ABI
experiment. Neither the smaller positional residue nor this packet establishes
that interface as original source. Keep the uniform thiscall control.

## New compiler evidence

The first response's point address already has an EAX home before local
allocation. A local scratch-cursor change alone cannot free EAX for its inner
vtable load. The two address values are shared into the reverse-response block.

Read-only traces use the same RTM c2.dll 13.10.3077 as the preceding packets,
base 0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
The flow graph is still `fw[2]`, not `fw[8]`.

- At +0xb0030 and +0x7c0b0 (after +0x7dfd0), the first response's normal and
  point LEA destinations have raw symbol word 7 equal to zero.
- After the call to **+0x7c367**, at +0x7c0c8, those words are 25 and 26.
  They remain so after +0x80353 (+0x7c0e1) and on entry to +0x821a7.
- At +0xb0037, after +0x821a7, the corresponding destinations have physical
  homes EDI and EAX. Local allocation has not run yet.
- The initial allocation-round record for point candidate 26 has raw field 3
  equal to 78, field 9 equal to 3, and first/last blocks spanning the first and
  reverse responses. Later rounds split it into records 8 and 22, confined to
  the respective blocks. `allocation-rounds.json` freezes the actual fields;
  these descriptions do not claim recovered compiler structure names.

`address-stages.json` identifies the values by LEA offset and block, not solely
by reused heap addresses. Raw symbol word 7 changes meaning across these
passes; do not treat 26 as a stable source-local name. Five completed debugger
compiles reproduced their corresponding untraced bodies, as recorded in
`trace-checks.json`. An initial rounds wrapper continued after the compiler
had terminated; its completion handling was fixed and rerun successfully.

## Address-sharing ablation

The seven `ablate` inputs are **deliberately non-equivalent diagnostics**, not
candidates. Changing only the reverse call's point argument from node+0x14 to
node+0x18 removes the first response's shared point home: its LEA stays local
through global allocation, while the normal still gets EDI. The first response
then ends with retail's reload/push sequence:

```text
0d8 mov ecx,[esi]
0da mov ecx,[ecx+4]
0dd push eax
0de call [ebp+24h]
```

Its inner vtable still loads into EDX at +0xcb, ahead of the normal and point
pushes. This isolates an effect of the point's cross-block sharing; it does
not explain retail's later vtable load or justify changing an argument.
Removing the reverse block or copying the point into a temporary also fails
to produce a usable candidate. Selected source and call disassembly are kept.

The follow-up `repoint` family tests equivalent pointer-to-member, pointer-bit
copy, memcpy and unsigned address identities at independently chosen sites.
It does not improve the bank. In particular, memcpy model v0386 changes the
first response's load order but keeps its early inner-vtable load and wrong
return push/reload order. The float-union model is diagnostic only: do not
assume arbitrary pointer bits survive an x87 float transfer. No such input was
banked. The 64-bit arithmetic models preserve the low 32-bit address; the
simple casts and arithmetic already disproved by earlier packets were not
presented as new source discoveries.

## Searches and ruled-out explanations

All searches use eight workers, `compiler_command` and private objects. They
never call `build.compile_source` or write the shared match cache. Metrics in
`trials-summary.json` use complete `(mnemonic, operands)` instruction alignment.
The search helper's mnemonic-first score differs (301 for the bank).

| Family | Compiled | Distinct bodies | Best aligned / positional differences |
| --- | ---: | ---: | ---: |
| address | 1280 | 2 | 308 / 31 |
| wide | 1024 | 16 | 285 / 43 |
| nodehandle | 1024 | 6 | 204 / 193 |
| narrow | 128 | 4 | 308 / 31 |
| membertarget | 1024 | 39 | 308 / 31 |
| switchstate | 480 | 18 | 308 / 31 |
| coherent | 2048 | 6 | 164 / 182 |
| statetype | 1536 | 24 | 308 / 31 |
| repoint | 512 | 72 | 308 / 31 |

There are 9,056 successful family compiles, eight small vector-volatility
probes and seven ablation compiles (9,071 total, excluding independent
reproduction/traces). Initial malformed switch inputs, unsupported annotation
probes and repeated historical interface/thiscall controls are excluded.

- **Types/layout and argument lowering:** address forms combine nested vector
  storage, a vector array, six floats or 24 bytes, byte/word/float pointer
  arithmetic, and an inherited-node view with the diagnostic/uniform controls.
  Only the two control bodies result. Some factorial axes are inert. The
  generator was not retained; both distinct source controls are preserved.
- **ABI:** coherent 64-bit scalar prepare arguments, signed/unsigned packing,
  union/word stores, OR/add construction, helper argument order/convention and
  per-site direct calls do not beat the prior consistent pair interface.
  This shows the aggregate itself is not necessary for that diagnostic body.
  Matching narrow prepare results with equally narrow callback parameters
  avoids an obligatory MOVSX but still does not improve either control.
- **Lifetime/callee boundaries:** a saved-node value handle, const/reference
  arrow results, empty destructor/copy/fastcall constructor and factory/NRVO
  forms all lose solved bytes. Dynamic one-word member-function-pointer
  dispatch was recombined with the newly banked data bridge, receiver boundary,
  helper parameter order and independent prepare/outer-callback sites; no gain.
- **Control flow/state:** switch case order, bool-result lifetime, assignment
  spelling and split guards change allocations but lose solved bytes. The
  signedness/enum/full-width-bitfield types were already negative in earlier
  packets; statetype tests their interactions with these new switch/bridge
  forms, not a newly discovered type lever. A nominal 19-byte test-region
  alignment is not a usable winner: register roles and the prefix differ.
- **Consistent interface:** virtual prepare with one eight-byte class argument
  plus one-word class arguments for test/respond, independently default or
  fastcall, was tested together with the data bridge, copy/constructor/order,
  const-reference/pointer fields and throw declarations. All 2,048 are worse.
  These combinations are distinct from the earlier raw-table all-fastcall
  model and prepare-only consistent-interface family.
- **Vector volatility:** eight component-volatility masks do not change the
  unsolved call regions; several worsen the reverse floating-point code.
  `__restrict`, `__declspec(restrict)` and `__declspec(noalias)` are unsupported
  by this toolchain (C4235/C2485), not viable alias-control levers.
- **Settings/context:** the prior real-header, sibling, compiler-version,
  optimization/profile and declaration-padding negatives still apply. No new
  supported compiler-setting hypothesis was found, so those scans were not
  repeated. Relevant BFME 1 collisionmanager donor history since the committed
  pointer contains no new source; the already optimized WorldBuilder twin is
  not an unoptimized local-frame oracle.

## Inputs, validation and continuation

Input HEAD was `e98a774b6d73fed0e44f103d2f507bf6f6ac2494`, with two preserved
unpublished evidence commits. Pulled master and passed check_csv (98,069
functions, 15,856 symbols, 2,131 data). Claimed the assigned body before work
and read its history with `pick-hard --rva 0x758DE0`. The committed and checked
out BFME 1 pointer was clean at
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. Another seat, claudec2, owned the
fresh update lock, so this seat skipped updating and did not mark freshness
success. Broad reference/dump queues and maintainer-only runners were skipped
for the standing assignment. AGENTS.md remained unchanged and within 24 hours
of its prior read.

`tools/variant.py base.cpp bfmeTwoCGD 0x758DE0 333` independently reproduced
333B/31 differences, first +0x94. This is an expected diagnostic mismatch, not
a false gate rejection. Ledger, path-case and whitespace checks accompany the
banking commit. No matched-body acceptance is claimed.

Continue the point-address lifetime and call-argument lowering investigation.
A useful new hypothesis must explain both the shared point home and why the
inner target is lowered after its last address push, preserving the solved
iterator, guards and x87 reverse normal. More identical nominal types, inline
getters, initialized-local padding or flags do not address this evidence.
The mixed reverse interface also still needs a consistent source explanation.
No missing function or external prerequisite was identified; there is no
justified blocked-on RVA. The claim is released with this handoff.

For reproduction, copy the `.py.txt` and `.cpp.txt` files into an ignored
directory two levels below the repository root and drop `.txt`. The inputs are
self-contained. Run a generator, `search.py FAMILY`, then `regions.py FAMILY`.
`global.py early-global base.cpp` and `global.py early-offset
ablate-reverse-offset.cpp` reproduce the checkpoints; `trace_rounds.py` reads
allocation rounds. Do not use the ablation source as a bank or landing.
