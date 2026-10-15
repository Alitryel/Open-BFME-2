# Terrain and snow texture-reference initialization, 2026-10-15

At BFME 2 c92eba543ed67d69557ae81a24c2c2e7ae26e20c, both units emitted an
unused six-byte BfmeResetTextureRef default constructor. The frozen link index
rejects that copy against the first-in-order nine-byte copy in dx8wrapper.cpp;
no independent retail address is asserted for this constructor.

Use explicit terrain/snow null-initialization overloads in the existing holder
views. Snow's RefCountPtr default constructor forwards to its local overload.
The one-pointer layout and visible null initialization are unchanged. These
source-level tags distinguish the initialization helpers from the shared default
constructor; they assert no new retail identity. The emitted helpers have no
non-debug caller relocations before or after. No flags, headers, pins, ledger
rows, data names or verification rules change.

## Paired evidence

Both sources were file-claimed. Each baseline passed --prepare-current before
editing; the final pair passes it with strict reusable receipts and the same
ordinary byte gate. All six retained terrain COMDATs and all retained snow
COMDATs have identical complete bodies, sizes and relocation digests. Every
other non-debug section and the linker directives are unchanged. The only
section changes are the unused constructor helpers: six-byte RET0 becomes an
eight-byte RET4 under the distinct tag-taking signatures. Neither helper is
referenced by emitted code. Full snow EH graphs remain EXACT (2/2).

proof.py uses the ignored before/after objects and receipts under
build/terrain-texture-link-20261015/; proof.json preserves their hashes, source
hashes, normalized section comparison and the before/after findings. Both
sides refresh only the two explicit objects into the same frozen index:

- Index SHA256 a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3.
- Index measurement 19a2565407, 2026-10-15 09:33.
- Underlying census 5986a99448, 2026-10-15 04:52.

Terrain findings fall 1 -> 0; snow findings fall 3 -> 2. Paired legacy local
LINKED grows 0 -> 276 non-padding retail bytes (terrain's row extent is 277).
Both edited objects are self-strict current. Other census providers are not
collectively proven current, so closed-strict gain is unmeasured. Authored C++
byte gain is zero. No census, status or index artifact was rewritten.

Acceptance checks:

- ./build.sh on each source and paired --prepare-current: 11/11 rows exact,
  four float literals and one empty-string reference verified; no skips.
- eh_verify.py: EXACT 2/2, no baseline or missing objects.
- find_declared_unmatched.py, class_gate.py and --new-variants: pass.
- data_check.py: zero findings; --converged: eight addresses, no second names.
- Paired assertion proof: exactly two findings removed, none added; all
  retained code, relocations, other non-debug sections and directives identical.
- Normal paired link_check.py: terrain LINKS; snow retains its two old blockers.
  Exit 1 is expected for those unchanged snow findings.
- place_bodies.py on both units: zero bodies, zero pins.
- check_csv.py and git diff --check: pass. Normal hooks are required on commit.

## Donor review, sweep and remaining blockers

Reviewed BFME 1 verified a7c38d3b2597121f178ab5190b3062478823257d and the
constructor/wrapper reconciliation principles in d3f9000fe08615a100e844adfff57fa4a39cd615,
de59a7e9f891b3ed2d4221d151ca881f4b75a583 and
d003077f0b7ce97622adb7a53f1fe76653433c5c. Declaration-only forwarding is
inapplicable here: the visible member initialization must remain for the
matched parent shape. BFME 2's existing Rva00136032Factory.cpp uses a
holder initialization tag for the same emission problem. No donor body,
layout or identity is imported by this repair. Target row byte checks and
whole-object comparison, rather than donor naming, establish preservation.

The index has exactly three default-constructor copies in this family:
terrain, snow and the kept dx8wrapper copy. The two losing copies are repaired
in this batch; the keeper is unchanged. Snow still needs its native destructor
and a separate Overridable::getFinalOverride reconciliation. Those are distinct
blockers; no snow linking gain is claimed. Its deferred 2403-byte renderAsQuads
reconstruction was not retried.

The initial repair_queue.py link and link_rank.py passes also found already
repaired stale-index entries and unchanged banked compiler blockers. Official
BFME 1 master was fetched at 4d506dbb57690a913403c09a0ab83b2a22e80f83;
the verified gitlink remains a7c38d3b2597121f178ab5190b3062478823257d. A peer
holds the submodule update claim, and the previous handoff records a blocked
comparative full gate. No freshness success was recorded or pointer advanced.
No maintainer-only verification runner was started.
