# Closer wide monetary formatter bank

Result: partial. Target `?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GABV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z` at RVA `0x0000DF20`, retail extent 2610 bytes, is banked in `reverse/attempts/0x0000df20.cpp`. No Code source, function row or pin changed. Input revision `dd0ca72bda0e0ed0ad70d6dcaef88267c6f7bf45`; BFME 1 input revision `a18d9ed50607e9175de4d6568798d7d73119de09`. Model `gpt-6.1-sol`.

## Measurement

`measurement.json` is the result record. `before-align.txt` and `after-align.txt` are unedited align_diff output, each obtained after deleting that trial's object and dependency receipt with BFME_OBJSTORE=off. Both complete bodies exceed the comparison size threshold. Relocation and branch categories are excluded from the recovery decision.

| Measurement | Before | After |
| --- | ---: | ---: |
| Emitted bytes | 2564 | 2528 |
| Structural regions | 34 | 21 |
| Memory differences | 144 | 132 |
| Register differences | 47 | 47 |
| Positional differing bytes, including extent delta | 2378 | 1921 |

The score is the fraction of retail instructions without unmatched structure or memory/register operand differences, calculated in the raw evidence script. It is not a byte-exactness claim and does not reuse the farm's scoring method.

## Identity and semantics

`retail.txt` records the complete boundary and following CC padding. `evidence.txt` records the actual RTTI name for the wide money_put specialization, its vtable entry at RVA 0x7BBA68 between the deleting destructor and matched long-double overload at RVA 0xBE50, and retail's ret 0x1C. Target FuncInfo at RVA 0x8FD718 has 23 states and handler RVA 0x75BCA7. These establish the function identity independently of matching bytes. Donor `_monetary.c` supplies the monetary algorithm; target call sites and the helper ledger establish the two external __copy calls. The modified source retains every inherited comment plus the vendor copyright notice and formatter comments. The existing inherited header measurements are historical and superseded by this handoff.

The candidate removes the unrelated volatile padding variable, aligns the pattern local, and keeps the currency and zero-fraction copies as calls to the existing __copy helper. Sign-tail and fractional copies remain inline. The output iterator's dereference and increment operators return itself, so wrapper assignment preserves output order and failure handling. Grouping, sign choice, fractional padding and all donor operations are retained. No equal-arm ternary, volatile store, inline assembly or optimization pragma was introduced.

## Experiments and remaining prerequisite

Alignment and padding removal alone reduced structure but increased memory/register differences, so that trial was rejected. Selective helper boundaries alone also traded fewer structural regions for more operand differences. Their combination passes the monotonic comparison. An initial three-helper trial incorrectly outlined the sign tail; a complete reading of the native block refuted that choice and the retained source restores the inline tail. The two external target helper sites are VA 0x40E620 and VA 0x40E7CE.

Retail still needs three whole-string destructor calls, six base-destructor calls and six frees. The candidate emits nine wide whole-string destructor calls and three frees. Its local frame is 0x110 instead of retail's 0x118. The first structural mismatch is retail +0x27E in the first early-return cleanup; another early return at +0x410 and final teardown at +0x7F0 remain different. The EH comparison fails with bytes_differ in the associative text section. A wide allocator-base constructor remains unresolved: its whole emitted body matches the existing narrow owner's non-relocation bytes, but its proxy-callee relocation needs complete fold proof before any pin. No pin was added.

Earlier verdicts already rule out blanket destructor declarations, compiler flags and global allocator/proxy lifetime changes. This pass does not repeat those sweeps. A new cleanup experiment needs evidence for selective destruction that preserves the caller's states, rather than another global declaration change. The raw scripts, all trial sources, assembly and outputs are retained under `build/df20-worker-20261019/`. No background task was started.

## Checks

`checks.json` records results and raw log paths. Both check_csv and pin_consistency --check pass. Fresh final-bank compilation reproduces the candidate's alignment and emitted size. Byte exactness fails, as expected for this partial; bank-explain.txt records the unresolved allocator-base constructor and the first byte difference at +0x1D in the frame size. EH verification also fails. No matched Code source was edited, so build.sh and find_declared_unmatched were not run. Every trial used BFME_OBJSTORE=off. Original bank LF endings and every inherited comment are preserved. The assignment requested retaining all trial sources and raw logs under build; they remain in the dedicated task directory. No background process remains.

## Destructor site map (claude-opus-5-5, 2026-10-19)

Calls in retail's main flow, by retail offset (WHOLE = 0x142D70 `~basic_string<wchar_t>`, BASE = 0xB3C0 `~_String_base<wchar_t>`):

- grouping temps (narrow, flags 1,2) at +0x17D/+0x1A8: inline free.
- curr_symbol ternary temps (flags 4,8) at +0x236/+0x259: WHOLE.
- early return 1 (`digits.size()==0`): WHOLE on curr_sym (esp+0x68) at +0x28C, then `jmp +0x841`.
- sign ternary temps (flags 0x10..0x80) at +0x375/+0x398/+0x3BB/+0x3D7: BASE.
- early return 2: BASE on sign (esp+0x5C) at +0x41E, BASE on curr_sym at +0x42F, then `jmp +0x841`.
- final teardown at +0x807..+0x852: new_digits, sign, curr_sym and grouping all inline free.

So one variable, curr_sym, is destroyed three ways (WHOLE, BASE and inline) in one function. That looks like the c2 inliner running out of budget per call site, not a declaration choice. The unwind funclets (0x75BB60..0x75BCA7) agree: WHOLE for grouping, BASE for curr_sym and sign, and WHOLE/BASE for new_digits states 21/22.

Trials:

- **v2 = bank without the `~basic_string<wchar_t>` specialization declaration.** Everything inlines: 2576 B, 29 regions. The final teardown lines up with retail +0x807..+0x852, but the early returns tail-merge into it (`jmp` into the free chain). Retail does not merge them, because its early-return dtors are calls.
- **Forceinline helpers wrapping the dtor sites (v3/v4).** Refuted: MSVC 7.1 never inlines a forceinline helper whose body holds EH-tracked temporaries (2176 B).
- **`/W4 /w14710 /w14714` to list non-inlined calls.** The build helper reports nothing.

Not yet tried: reproducing the budget, which means finding which inlinee retail took that we force differently. Retail is 34 B larger than v2 while inlining less.
