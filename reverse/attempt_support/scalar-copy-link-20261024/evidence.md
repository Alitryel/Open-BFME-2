# Scalar-copy identity and link repair, 2026-10-24

Input BFME2 6958a56410; published census 268f876e3b (2026-10-24 02:54,
retail-truth-4). The current-object preview, not the old census delta, is the
before measurement. No closed-strict gain or new C++ recovery is implied.

## Target facts

Retail [0x0031BA18, 0x0031BA47) is a complete 47-byte cdecl worker. It computes
(last-first)>>3, copies through 0x002C99FB, advances both pointers by eight,
and returns the destination without popping arguments. The independently
rowed Rva0031BA18Copy.cpp already reproduces that complete body and callee.

Retail [0x002C99FB, 0x002C9A18) copies the dword at +0, then passes source+4
and receiver+4 to 0x00239099. The native Rva002C99FB view records that order.
The BfmeAsciiScalarValue8 view instead has AsciiString at +0 and scalar at +4;
its generated ordinary assignment is therefore not this native assignment.
The scalar unit's explicitly instantiated __copy row and both associated
pins were false attributions, despite a previously accepted masked match.
No application type or source donor identity is inferred from stride alone.

The scalar unit's four other body boundaries are independently retained:
Construct 0x000BBA1A/45, const uninitialized copy 0x000BBBA8/38,
uninitialized fill 0x000BBBCE/37, vector copy ctor 0x000BC61D/93, plus the
Construct cleanup at 0x00761BE6/14. Their byte gates must remain exact.

The separate stlport_copy_ptrs_scalar8.cpp already forwards to the native
Rva0031BA18Copy spelling through its five-push call view. That worker reads
only its first three arguments. No new forwarding shim or alias is required.

## Intended correction and acceptance

Remove only the false explicit instantiation and duplicate row; preserve the
existing native owner. Remove its __copy and member-assignment pins, then
verify all cached-object name dependents. Reduce the corresponding keyed pin
hatch counts; this adds no baseline debt. Record a tombstone for the false row.

Before: StringScalarVectorCopyBFME2.cpp links 0/260 nonpadding bytes because
its assignment copy is not retail's. Native Rva0031BA18Copy.cpp already links
47/47. Expected after: scalar unit links 213/213, native owner stays 47/47;
unique byte coverage is unchanged and the duplicate row disappears.

## Verified result

- `link_check.py --prepare-current` on the scalar unit and native worker:
  6/6 rows exact and both explicit providers have strict reusable compiler
  receipts. This proves self evidence; provider closure is not claimed.
- `./build.sh` on all nine family units plus the native worker and assignment:
  79/79 rows exact across eleven sources; literals, floats, imports and source
  claims pass. The source's cleanup label changed naturally and its full
  parent exception data placed it at the existing native funclet address.
- Before current-object previews: scalar 0/260, native worker 47/47; all eight
  other family units already link 7,532 B. After: all ten units link 7,792 B,
  versus the same current before total 7,579 B: **+213 nonpadding B linked**.
  This is the legacy scoped prediction against census 268f876e3b, not a
  closed-strict result or a fresh census measurement.
- Staged name_dependents: two call targets and one data target lost; zero
  referencing units among 23,437 scanned. The remaining five scalar-unit rows
  and existing native worker are all preserved. No caller rewrite is needed.
- check_csv: 98,199 functions, 15,761 symbols, 2,179 data rows; frozen-source
  and whitespace checks pass. One duplicate 47 B row and two false pins are
  gone; unique authored coverage is unchanged. Pin hatch debt falls by two.

The paired reference gates completed before any source or ledger edit. See
reference.md and reference-gates.txt. Current family previews are recorded
separately from the census's older state, so inherited gains are not credited.
