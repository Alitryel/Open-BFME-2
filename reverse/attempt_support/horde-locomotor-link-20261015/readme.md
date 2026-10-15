# HordeContain locomotor-set emitter repair

Base tree: 930ce69af9f0ebb03c4810d5020afd24ec6179ff.
Frozen local index: a2839ea429, 2026-10-15 13:35; underlying census
5986a99448, 2026-10-15 04:52. Index hash is in index-meta.json.
This is a paired LEGACY local prediction, not the differently measured
committed link_status.csv or a new census.

HordeContainIface11CSlots.cpp emits an unused seven-byte private
AIUpdateInterface::getLocomotorSet copy (digest 1e3de62314d1). It loses
against the first copy in link order. Mark its existing definition
__declspec(dllimport) __forceinline, preserving the inline +0x1CC address
calculation in the already matched returnToFormation caller. No standalone
retail identity or correctness is asserted for either helper copy.

This completes the available ninth consumer excluded by the earlier
locomotor-set-inline-link-20261015 repair while another worker held it.
The file claim was available and acquired before this change. No shared
header, layout, compiler flag, data owner, ledger row or pin changed.

Donor technique reviewed: official BFME1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
suppresses surplus DamageInfo constructor emitters. Only its emission technique
is applicable here. Donor types, addresses and layouts are not imported.
The clean verified BFME1 gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Official master was fetched at 95eeb3bef370a7cd730b0ad5f228c317c8756e72.
Pointer advancement remains blocked by the foreign submodule claim and the
previously recorded old/new full-verification comparison; no success stamp
was written.

Acceptance: bounded strict preparation before and after and ./build.sh pass
144/144 rows, five strings plus two empty references and 34 floats. EH is
11/11 EXACT before and after. Class, declared-definition, CSV and whitespace
checks pass. Placement rescan finds zero new bodies or pins.
Converged-data enforcement checks eight addresses with no second name or
unjudged row. Shadow data enforcement exits 1 for two pre-existing local-static
wrong-name findings at 0x00A03674 and 0x00A03684; paired complete data facts are
identical. No baseline was changed.

proof.py uses ignored before-source/object snapshots in
build/horde-locomotor-link-20261015/before. Compile parent and changed source
with the same inputs to reproduce snapshots. It proves strict current currency,
removal of only the unused helper, no incoming nondebug relocation to it,
all 631 retained COMDAT digests and all other nondebug section bytes, flags,
definitions and symbolic relocations unchanged. Data bindings and the winning
provider are unchanged, and no new variant is admitted. Detailed hashes and
paired findings are in object-proof.json.

Local findings fall 44 -> 43: unresolved 10 -> 10, duplicates 1 -> 1,
COMDAT conflicts 26 -> 25, selected conflicts 7 -> 7. All other findings are
unchanged. The file owns 18,417 existing nonpadding bytes but remains blocked;
LEGACY linked bytes remain 0 -> 0. Added authored C++ bytes: zero.
Self-strict objects are current; closed-strict closure/gains are unmeasured.
No census, index, link status or history is rewritten. Full link cycles,
nightlies and boot runners were not started.
