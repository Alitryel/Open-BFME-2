# Wide numeric-input helper ownership

At BFME2 394c0e4320, stlport_wide_num_get.cpp failed the current legacy
link preview on two unsigned-int scanner helpers: __get_integer and
_M_do_get_integer for the wide stream-buffer iterator. Both already have
kept definitions in stlport_classic_locale.cpp. Neither has a retail address
in the index; these were first-copy disagreements for referenced helpers,
not proven incorrect retail-addressed bodies. Both units use the same
vendored STLport implementation and template argument types. Declaration-only
specializations make the numeric-input unit bind to those existing definitions.
No new identity, ABI, layout or retail-address claim is made for the helpers.

The first gate showed that removing these implicit scanner instantiations
also stopped four existing rowed iterator operations being emitted. Explicit
instantiation of those same operations retains their original bodies; no
new implementation or fallback is introduced. The second gate passes.
The index lists only these two units for each helper, completing this cause
sweep. The classic-locale provider is unchanged.

Current same-index ae3b3e68e2 predictions, with both objects refreshed:

- Before: classic-locale 1,369 B links, wide numeric-input 0/563 B.
- After: both link, 1,932 B total, net **+563 B legacy**.
- The 1,369 B provider already linked before the change and is not credited.
- ./build.sh: consumer 13/13 and paired cohort 50/50 rows exact; literal,
  float/import and parent-EH checks pass.
- link_check.py --prepare-current: both explicit providers have strict
  reusable compile receipts. No self-strict or closed-strict LINK closure
  and no full link-cycle result is claimed.
- find_declared_unmatched.py, check_csv.py and git diff --check pass.

No pin, linker alias, shared header, verifier or baseline was edited.
BFME1 verified inputs remain unchanged; the incomplete freshness check is
recorded in 20261022-pod900-link.md.
