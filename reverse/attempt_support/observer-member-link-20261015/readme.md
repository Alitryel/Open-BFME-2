# Observer-storage destructor link repair

Source base: efb456d3700e3335172301dc58079ce5326f397a. Paired checks use the
runner index at 19a2565407, 2026-10-15 09:33 UTC, underlying census
5986a99448, 04:52. object-proof.json records the index hash, source/object
hashes, strict self receipts, all remaining findings and before/after
previews. Committed link_status.csv was discovery only. No census, index,
status, history, data-back artifact, ledger, pin or baseline was changed.

Six constructor units declared the existing Rva00330757Member storage as a
BfmeE16 vector plus flags. Their implicit destructors consequently emitted
five-byte jumps to the 63-byte BfmeE16 vector destructor at 0x0052D1CD. Those
copies disagree with the existing 14-byte observer-storage destructor at
0x0007FAB3. Its owner in LivingWorldRegionConstructor.cpp frees the first
storage pointer; its row's original class/template spelling remains unknown.
The existing constructor row, verified destructor row and retail lifetime
accesses support this relationship; no new identity or element-layout claim
comes from the vector stand-in or from matching bytes alone.

Declaring the existing destructor in the six views removes their competing
implicit definitions. The main constructor bodies retain exact bytes. Two
incidental outer destructors emitted by Rva00542379Ctor.cpp retain their
53-byte instruction bodies and change only the member-cleanup relocation
at offset 36 from the stand-in vector destructor to the real member
owner. They gain no new row or identity claim. Strong definitions and weak
bindings stay identical. Undefined changes consist solely of removing unused
stand-in destructor references and referencing the existing member destructor.
All other retained COMDAT bodies and normalized relocations are unchanged.

Consumers: Rva00330757Member.cpp, Rva00542379Ctor.cpp,
Rva005F24F0CopyCtor.cpp, Rva0040E3EEFinish.cpp, Rva00541913CopyCtor.cpp and
Rva00541A6ECopyCtor.cpp. Each file was scope-claimed and passed the frozen
source check before editing. The index's two other losing emitters,
Rva00540B03Ctors.cpp and Rva00540517CopyCtor.cpp, are foreign-claimed and
were left to their owners. The other indexed copies already have retail
truth. Unchanged provider LivingWorldRegionConstructor.cpp was strictly
byte-verified alongside all consumers; its source and object hashes and
local findings are unchanged.

BFME1 donor repair de59a7e9f891b3ed2d4221d151ca881f4b75a583 (incidental Apt
helper ownership) was reviewed, reusing the earlier linking-repair review
of d003077f0b7ce97622adb7a53f1fe76653433c5c. The applicable principle is to
remove conflicting incidental definitions and use their existing owner;
no donor code or layout was imported. Verified donor checkout remains clean
at a7c38d3b2597121f178ab5190b3062478823257d. Official master is newer. The
overdue pointer update remains foreign-claimed and blocked by the prior
comparative full byte gate: 2,982 stale TUs, stopped after 21 minutes with
2,806 left. That unchanged blocker was not retried; no freshness success
stamp or pointer advance was made.

Acceptance:

- Normal build.sh passes the initial two-file repair. Bounded
  link_check.py --prepare-current passes before and after for all seven
  explicit units: 18/18 rows exact with strict reusable self receipts.
  No literal, import or reference was skipped or baselined.
- Reconstructed before/after object snapshots are refreshed together in
  separate in-memory copies of the same index. Six COMDAT findings vanish,
  zero findings appear, and every independent finding stays unchanged.
  Rva00330757Member.cpp alone previews LINKS, 0 -> 50 legacy local LINKED
  bytes. Its standalone prescribed link_check.py exits 0. The seven-file
  check exits 1 because the five other consumers and unchanged provider
  retain the findings recorded in object-proof.json.
- eh_verify.py on both snapshot sets reports seven EXACT parent graphs,
  zero baseline debt. No closed-strict closure, census gain or actual
  link.exe placement was measured. Broader verification belongs to the
  maintainer runner.
- New-variant admission, declared-definition, class, shadow data,
  converged data (eight addresses, zero second names/unjudged rows), CSV
  and whitespace checks pass. Normal hooks check staged hatch counts and
  publication gates. place_bodies.py rescanned all six changed units:
  zero new bodies or pins.

Remaining consumer blockers: Rva00541EB8 selected destructor; two unresolved
Rva005F2439Element methods; BfmePod28 allocator/vector copies and selected
providers; Rva0054103E construct/vector copies; Rva0040E3EEBase destructor.
The existing provider retains three unresolved names and four unrelated
COMDAT findings. These are outside this single shared-dependency repair.
Authored C++ coverage +0. Local legacy LINKED +50 bytes, six findings
removed. No full census, link cycle, nightly, boot or scheduler was run.
Snapshots and the comparison script are preserved under
build/observer-member-link-20261015. Unrelated untracked work is preserved.
