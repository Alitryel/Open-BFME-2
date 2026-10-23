# Narrow integer-padding link repair

Source base: 35946f399fe18b6fc50561dcd01e4ebb5628106f. Paired checks use the
unchanged runner census index at 19a2565407, 2026-10-15 09:33 UTC (underlying
census 5986a99448, 04:52). object-proof.json records its SHA256, current-object
hashes, strict self receipts and paired local previews. The committed
link_status.csv was used only for discovery. No census, index, status,
history, data-back artifact, ledger, pin or baseline was changed.

stlport_narrow_copy_integer_and_fill.cpp emitted an unused external 53-byte
fill_n instantiation that fails retail truth. Its rowed provider is the
113-byte body at 0x0001A320 in stlport_narrow_num_put_bool.cpp. Every use in
the integer-padding body was already inlined. Giving this private helper
internal linkage removes only the surplus competing definition. The file
was scope-claimed and passed the frozen-definition check before editing.

Target evidence remains the whole 569-byte __copy_integer_and_fill row at
0x000095E0. Its body and relocations are unchanged, as are the other six
retained COMDATs, ordinary sections/linker directives, strong definitions,
undefined references and weak bindings. The iterator layout and algorithm
are existing reconstructed STLport 4.5.3 claims; this edit changes neither
and adds no identity, layout or recovered-byte claim. The rowed fill_n
provider was byte-verified alongside its consumer and remains unchanged.
The index contains only these two emitters for this exact helper spelling,
so no further losing emitter shares this cause.

BFME1 donor linking repairs de59a7e9f891b3ed2d4221d151ca881f4b75a583
(incidental Apt helper ownership) and d003077f0b7ce97622adb7a53f1fe76653433c5c
(removing a competing inline attach thunk) were reviewed. They support the
incidental-copy mechanism; no donor code or layout change was imported.
Verified donor inputs remain clean at a7c38d3b2597121f178ab5190b3062478823257d.
Official master was fetched during discovery; the overdue pointer update
still belongs to another worker's file:reference/open-bfme-1 claim and
requires the unfinished comparative full byte gate. The prior gate needed
2,982 stale TUs and stopped with 2,806 left after 21 minutes; that unchanged
blocker was not retried. No successful freshness stamp or pointer advance
is claimed.

Acceptance:

- Normal ./build.sh passes the complete consumer row and all reference
  checks. Bounded link_check.py --prepare-current passes before and after
  for consumer and provider: all 10 rows exact with strict reusable self
  receipts. No literals, imports or references were skipped/baselined.
- Whole-object comparison removes exactly the wrong fill_n COMDAT and
  preserves all seven retained bodies, extents, normalized relocations,
  digests and retail verdicts. Ordinary sections and bindings are identical.
  Provider source, object and local findings are unchanged.
- Same-index paired legacy preview reduces consumer findings 1 -> 0 and
  LINKED bytes 0 -> 569. Standalone prescribed link_check.py returns 0 for
  the consumer. The two-file check returns 1 because the provider retains
  eight independent COMDAT and four selected-definition findings involving
  allocator/string, locale, iterator assignment and integer-padding copies.
  These are explicitly retained in object-proof.json, not repaired here.
- New-variant admission, declared-definition, class, shadow-data,
  converged-data (eight addresses, zero second names/unjudged rows), EH
  (zero rows), CSV and whitespace checks pass. Normal hooks check staged
  hatch counts and publication gates.
- place_bodies.py rescanned the changed unit: zero new bodies or pins.

Authored C++ coverage +0; one unit gains 569 legacy local LINKED bytes.
Self-strict receipts prove the two explicit objects are current; closed-strict
closure, census gains and actual link.exe placement were not measured.
Broader link verification remains with the maintainer runner. No full census,
link cycle, nightly, boot or scheduler operation was started. Source/object/
receipt snapshots and comparison scripts remain under
build/narrow-fill-link-20261015. Unrelated untracked work is preserved.
