# S4 partition call binding

At BFME 2 3135430de3, the current-object preview of
`stlport_unguarded_partition_s4sortelem20.cpp` fails only its undefined
`bfmeIterSwapS4SortElem20` call. Its existing pin names retail RVA 0x3373D9,
which already owns the complete 75-byte `_STL::swap<S4SortElem20>` row in
`stlport_introsort_loop_s4sortelem20.cpp`. The pointer arguments passed to the
helper are the addresses of the two elements, as the rowed reference-argument
swap requires. The donor-established partition semantics remain unchanged.

Declare that existing template and call it with the dereferenced iterators.
No new pin, alias, body, header or compiler setting is introduced. This does
not resolve uncertainty about the original names of the neutral S4 fields.

Acceptance: `./build.sh` passes 1/1 rows and all reference checks;
`find_declared_unmatched.py` accepts the unit; `link_check.py
--prepare-current` prepares its strict receipt through the normal byte gate.
Same-index explicit current-object previews move 0 -> 99 nonpadding bytes,
with the entire 101-byte ledger extent still matching. This is a legacy
preview, not a self-strict or closed-strict link-cycle measurement. The index
is census 2026-10-22 17:08 at 08160bc2c9. Logs: ignored
`build/s4swap-{before,gate,after,strict}.log`.
