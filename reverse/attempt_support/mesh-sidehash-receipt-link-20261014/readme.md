# Mesh side-hash reusable dependency receipt

BFME2 base: `81f74027847f3a700d1e40dd4fd59d9c33176e70`.
Local census index: `cb660e4d97`, measured 2026-10-13 04:02 UTC;
SHA-256 `4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
Committed link status measures `67e1365aa9`; it served discovery only.
No census/index/status was changed and no full link cycle ran.

## Supported dependency repair

The previous Vector3 equality repair left meshmdl_sidehash.cpp unable to
produce a strict reusable compiler receipt. Two already-opened dependencies
were outside its declared search roots: vector3_eq_link.h, included by a
parent-relative path in the source, and the donor GameEngine Debug.h,
included through wwdebug.h's parent-relative path.

Declare the shim directory and the donor GameEngine/Include directory in
the TU's existing compiler flags, then include vector3_eq_link.h by name.
The directory inventory now covers both dependencies. The final compile
opens exactly the same 45 header paths with the same hashes as the baseline;
input-evidence.json records this comparison and the version-2 receipt.
No header, class layout, body, pin, alias, row extent or gate rule changed.

The shim-only trial still refused the donor Debug.h dependency; its actual
refusal is retained. An intermediate Common-only search root shadowed the
toolchain string.h and failed compilation. The final parent Include root
avoids that shadow and retains every baseline header. No substitute header
or fallback was accepted.

## Acceptance

File claim obtained before editing. Commands ran against the same index:

```
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WW3D2/meshmdl_sidehash.cpp
./build.sh Code/Libraries/Source/WWVegas/WW3D2/meshmdl_sidehash.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/meshmdl_sidehash.cpp
```

Before: normal byte gate passes 19/19 rows, but strict preparation refuses
the version-1 receipt. After: strict preparation passes 19/19 rows with a
reusable version-2 receipt; compile_is_current(strict=True) returns true.
String, float and import checks pass without baselined or skipped references.
This is a self-strict dependency improvement for 2,408 existing retail bytes.

The before/after local link previews both report one of one units clean and
2,408 bytes. The historical index had zero bytes for this unit; that earlier
equality repair's gain is not credited again. Local previews remain legacy
index-based results, not closed-strict closure or executable-placement proof.
New authored C++ bytes and new LINKED bytes in this repair are both zero.

find_declared_unmatched and check_csv pass. The converged data check judges
eight addresses with zero second names or unjudged rows. Local new-variant
admission and git diff --check pass. Complete local transcripts are retained.

## Donor review and handoff

Retained clean BFME1 checkout/gitlink:
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Reviewed BFME1 direct StringBase binding repair
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`: relevant to the concat
rankings, already inherited by many BFME2 consumers, not an import here.
The donor supplies unchanged headers; receipt coverage and header equality
are established from this BFME2 compile, not inferred from donor names.

Fetched official upstream BFME1 master:
`23b143233b5a8664a3bdf8572df6d905c310a5a1`.
Its submodule scope has a foreign claim. The overdue comparative full-gate
update remains blocked as documented by earlier compiler-lock attempts;
the verified pointer and success stamp were preserved.

Link queue/rank checks found remaining voice-response consumers foreign
claimed, several missing providers, and previously rejected compiler/ABI
repairs. The rehome scan rediscovered the exact auto-resolve entry candidate,
whose unchanged owner-link regression is already documented in
entry-ctor-rehome-link-20261014; it was not retried. The lane is not exhausted.
A census including current providers would make those rankings more useful.
Broader link verification remains in the maintainer lane.
