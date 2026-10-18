# SphereClass Add_Sphere provider repair

Base e00c007df5a738c1f35112618bc49bfc496a0f3e; paired index c2c5ac8c27,
2026-10-18 11:36. Its SHA256 and both object hashes are in proof.json.

The three SSE donor consumers emitted wrong Add_Sphere bodies before the
retail-exact 277-byte owner at RVA 0x0019BE00. Each has one direct call to
that name. The donor-derived SphereClassLink.h preserves sphere.h's class,
layout and other inline definitions, while declaring Add_Sphere externally.
Include it after each unit's existing vector/matrix/iterator setup. No
function is renamed, imported, pinned or replaced with an address binding.

Donor basis: verified BFME1 64d369b90170b7e9ec917d646f020b11f13eb0d5,
game/Libraries/Source/WWVegas/WWMath/sphere.h. The header remains identical
apart from its provenance comment, trailing whitespace cleanup and removal
of the Add_Sphere definition and inline declaration qualifier. Existing target layout/identity evidence
belongs to the unchanged owner and consumer rows; this repair adds no new
layout or donor-identity claim. Reviewed donor repair 67f4eab2's use of a
single retail helper owner; its particular Thing helper is inapplicable.
Official BFME1 master was fetched at 8619c4c5. The prior documented freshness
blocker (Rva005E394EPrimaryBase conflicting vftable relocation bases) remains;
no successful old/new full gate or freshness stamp is claimed, and the
verified pointer remains unchanged.

Acceptance:

* Before and after bounded link_check --prepare-current: 188/188 matched
  rows, strict reusable receipts, one string literal and two empty-string
  references, 21 float literals and two named imports; no skipped refs.
  ./build.sh on the three edited consumers also passes all 187 rows.
* Full retained nondebug section bytes, flags, definitions and symbolic
  relocations are identical. All retained COMDAT digests/extents match.
  Exactly three wrong Add_Sphere definitions disappear. hlod also stops
  emitting Vector3 +/- used only by that copy; their new kept providers have
  identical retail digests. The sole changed kept function body is
  Add_Sphere, which changes from wrong SSE to its rowed retail owner.
* Paired current-provider legacy prediction: owner LINKED 0 -> 277 B.
  The three consumers keep independent blockers and receive no gain credit;
  their finding sets only shrink. Ordinary link_check agrees, 1/4 clean.
  This is self-strict object acceptance and a legacy local link preview,
  not closed-strict, a census measurement or executable-placement proof.
* Enforced data check, frozen definitions, class gate and whitespace pass.
  Placement resweep finds zero bodies/pins. Hooks additionally check header
  dependents and converged data.

An initial include-order trial passed all rows but changed incidental
Matrix3D and compiler-iterator copies. Restoring each existing prelude's
order removed those differences; only the removals proved above remain.
Proof baseline objects remain under ignored build/seat-sphere-link/before.
No census/index/status/history file, verifier rule, pin or ledger row changes.
