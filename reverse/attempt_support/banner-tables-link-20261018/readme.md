Banner step tables (2026-10-18)

The current unit has four exact functions, but its two declared step tables
have no definitions. Current-object link_check reports only these two
unresolved names against the published c2c5ac8c27 index.

Target facts: 52A295 tests four thresholds (7,9,18,20), then returns the
fifth 12-byte record. C68440..C6847B holds the five complete banner records
whose x offsets are {0,0}, {0,60}, {60,60}, {60,102}, {102,102}; the final
unused threshold word is zero. 52A302 tests only two scale thresholds (7,18)
and reads values at offsets 0,8,16 from C6847C. The table therefore occupies
20 bytes: two pairs and a final float. C68490 already starts the following
string. The old three-record declaration extended into that string.

Use five four-byte union-backed words for the scale table, retaining the
existing address-derived global spelling, and index its alternating float
and integer words explicitly. Float bits are 00000000, 3D700000, 3DCC0000.
This retains every function byte while accurately describing the table's
extent. Both data rows verify complete initializers; no pins or aliases
are added and no bytes of the following string are claimed.

Acceptance: build.sh passes 4/4 functions. data_rows --verify passes 2/2
complete initializers. link_check --prepare-current passes those functions
and data with strict reusable receipts. find_declared_unmatched passes;
data_check --enforce and --converged report zero findings. check_csv passes
96634 functions, 15999 symbols, 933 data rows.

Same-index current-object measurement: before 0 bytes, after LINKS 184
bytes, census 2026-10-18 11:36 c2c5ac8c27. This is +184 legacy predicted
linked bytes. Self-strict byte verification passes; closed-strict linking
was not measured. Authored C++ coverage is unchanged. Ignored logs:
build/seat-link-oct18/banner-{before,after,build,data,strict}.log.
