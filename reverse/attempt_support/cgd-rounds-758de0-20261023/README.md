# 0x758DE0: allocation-round comparison and address boundaries

The best bank remains **333 bytes, zero relocations, 31 positional byte
differences**, with **308/333 complete instruction-pair bytes aligned**
(score 0.924924924924925). Emitted SHA256:
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
No body landed. Continue this assignment next session.

The remaining mismatches are in the test and first-response virtual-call
windows. The reverse-only fastcall pair interface is still an **unproven ABI
diagnostic**. The ordinary thiscall control is retained as `control.cpp.txt`.
The Contact* names are structural diagnostic names; this packet establishes
no new retail class layout, donor identity or original parameter type.

## Inputs and prior negatives

Input HEAD was `14c61458f5e03a7f0129b2345c2b2ff83eff0493` and the clean BFME 1
checkout/pointer was `f890413e75e671748215ba2ef3304aa7953993e9`. Another seat,
`codex4`, owned the fresh BFME 1 update lock. This seat skipped updating and
did not mark freshness successful. `inputs.json` records hashes and totals.
Compiler: stock RTM c2.dll 13.10.3077, base 0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`,
with `/O2 /MD /EHsc /I.`. The actual retail extent is 333 bytes, ending at
RET 0x758F2C, followed by three INT3 bytes.

Before editing, the per-RVA history was read through `pick-hard --rva`, along
with the relevant vcall, global-homes, edges and barriers packets and recipes.
Those already ruled out ordinary source/getter/layout changes, declaration
padding, control-flow copies, pointer-bit identities, callee/header visibility,
compiler versions/settings/LTCG, and the recorded ABI models. These were not
repeated as independent new discoveries.

## Completed round comparison

The previous handoff requested allocation-round comparison of the bank with
`identity/v0008`: the integer round trip at the first response's point address.
Both new debugger runs reached compiler termination and emitted exactly their
untraced controls (`trace-checks.json`). They only read compiler state.

* Both inputs initially give normal/point raw symbols H307/H308, candidates
  25/26, spanning the first and reverse responses. The point is subsequently
  split into a first-response and a reverse-response record in both inputs.
  The integer boundary does **not** make it a local expression before global
  allocation, nor prevent this splitting.
* The bank's point records have raw field 3 values 78 initially, then 56/64.
  The integer input's corresponding values are 86, then 64/64. These are raw
  observations, not recovered compiler field meanings.
* The integer input also has **H324, candidate 28**, initially flags 0xD02,
  field 3=96, field 9=3, field 16=12, confined to the first-response block.
  The next round retains it as candidate 22, field 3=64, field 9=2,
  field 16=4. The bank has no corresponding extra candidate in these records.
* Selected IR identifies H324 as the **saved outer source pointer**, rather
  than a second point-address temporary: a load from node->first->source goes
  from R1 into H324 before prepare; H324 goes back to R2 after prepare for the
  response's this argument. `receiver-ir.txt` preserves the selected lines,
  and `identity-324.json` their raw snapshot nodes. This accounts for an extra
  allocation competitor and the changed receiver lifetime. The exact causal
  interference edge assigning point EDX/ECX instead of EAX is still unproven.

`round-comparison.json` is compact; the two complete rounds JSON files preserve
all sampled rows. Raw candidate numbers/heap addresses are pass-specific.

## New factorial searches

All 8,384 compiles below succeeded with zero relocations. They use eight
private-object workers through `compiler_command`, never the shared match
cache. `trial-summary.json` records full instruction-pair scores and regional
winners. Search.py's mnemonic-first alignment is a different metric; use
regions.py's pair_sum when comparing banks.

| Family | Compiles | Distinct bodies | Best pair-aligned / positional differences |
| --- | ---: | ---: | ---: |
| reservation | 1,024 | 361 | 308 / 31 |
| addressof | 960 | 67 | 308 / 31 |
| zerocopy | 4,096 | 1,539 | 308 / 31 |
| combine | 2,304 | 1,119 | 303 / 27 |

* **Reservation:** an explicit raw fastcall dispatch reserves EDX for a
  selected value while retaining two stack arguments. It varies eight dummy
  values, three call-site masks, four dispatch forms, helper convention and
  bank/uniform control. This is an unproven ABI probe, never a landing source.
  v0144 forces the first-response point into EDX and its inner vtable into EAX.
  Its return reload/push sequence becomes retail's. It has only 27 positional
  differences at 333 bytes, but only **303 aligned bytes**, losing five versus
  the bank. The vtable load remains ahead of the address pushes. Preserve this
  tradeoff for diagnosis; do not replace the stronger bank with it.
* **Address-of boundary:** overloaded vector operator& varies five bodies,
  constness, member/cdecl/fastcall convention, three sites and the two controls.
  The plain boundaries collapse; unsigned boundaries reproduce worse alias
  effects, and volatile pointer homes add unwanted memory operations.
* **Zero-count intrinsic boundary:** eight memcpy/memset return-value forms
  vary six argument sites, helper convention, bridge and uniform control.
  This tests late simplification of an address without a nonzero memory copy,
  unlike the earlier four-byte pointer-bit memcpy family. v2640 improves local
  pair counts in both unresolved call windows (17/22 bytes), but adds reloads
  and XORs and grows to 349 bytes. No complete candidate beats the bank.
* **Recombination:** three reservation values crossed with three intrinsic
  forms, six independent argument sites, helper convention and uniform control.
  No combination retains the prefix and combines the regional improvements.
  Its best is the same 333-byte/27-difference/303-aligned reservation tradeoff.

Selected sources and `call-windows.txt` make these distinctions reviewable.
These metrics are diagnostic; none constitutes recovered coverage.

## Checks and continuation

Pulled master; check_csv passed (98,083 functions, 15,851 symbols, 2,138 data).
Fetched the published link index and claimed 0x758DE0 before work. Independent
variant.py compilation reproduced the bank's exact size/hash and expected
31-byte mismatch. Path-case and whitespace checks accompany this evidence
commit. No Code, ledger, symbol pin, gate or compiler change was made.
Maintainer-only runners and unrelated broad queues were not started.

The concrete unfinished task remains the two call windows at 0x758DE0. The
next useful investigation is the interference/priority change caused by H324:
compare the saved-receiver and point records around the splitting/allocation
routine, then construct a source boundary that changes the point's home while
retaining retail's post-prepare receiver reload. This session identifies the
extra candidate but does not recover that allocator rule. There is no missing
callee or supported blocked-on RVA. Do not repeat address-of-only, the recorded
zero-count families, or their reservation recombination.

To reproduce, copy the .py.txt and .cpp.txt files to build/<directory>, removing
only .txt. Run reservation.py, addressof.py, zerocopy.py, combine.py, then
search.py FAMILY for each family and regions.py with all four family names.
combine.py uses reservation's generated inputs. Run rounds.py bank and
rounds.py identity separately, redirecting output to the corresponding .out.
The debugger runs require stock c2 at the recorded base. The prior barriers
packet contains the selected pre-global IR that receiver-ir.txt excerpts.
