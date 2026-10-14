# Shroud and taint interpolation max link repair

BFME 2 source base: c3331d441aaaa434670eeacef12bcfee5bb429d1.
The unchanged runner census index was measured at 147cfae2cb,
2026-10-14 07:27, SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
The older committed link status is used only for discovery.

W3DShroudInterpolate.cpp and W3DTaintInterpolate.cpp each emit a nonretail
standalone `_STL::max<unsigned int>` COMDAT. Add the established TU-local
unsigned overload before including set/vector. The comparison and reference
return semantics are identical to STLport's template, and every use in these
units was already inlined. Neither flags nor class layouts change.

Target identity and layout evidence remain the existing rows: the shroud
parent at 0x00073426 and taint parent at 0x000741C0 each cover 514 bytes;
complete associated EH handlers are at 0x0075EE4A and 0x0075EEC7. No new
identity or layout inference is made. Zero Hour/BFME 1 provenance in the
sources is retained; the comparison semantics come from STLport.

Acceptance:

- Ordinary byte gate: 4/4 rows exact; four float literals and two named
  imports verified; no literal baselines or skips. Bounded
  link_check.py --prepare-current passes the same 4/4 rows before and after
  with strict reusable compiler receipts.
- Whole-object proof: 48 retained COMDAT bodies in each unit have identical
  bytes, sizes and relocation digests. All other nondebug sections and exact
  linker directives agree after normalizing COFF section/symbol indices.
  The only removed external binding is max. Each object adds one unreferenced
  private eight-byte comparison helper with no relocations or nondebug calls.
  Source and object hashes, plus the unchanged index hash, are in
  object-proof.json. The comparison script and originals remain under
  build/fog-max-link-20261014.
- EH: 2/2 EXACT, no baseline or missing object. Enforced converged-data check:
  eight protected addresses, zero second names and zero unjudged rows.
  Shadow data check has zero findings. Declared functions, class gate and
  new-variants admission pass. Whitespace check passes with cr-at-eol for
  the taint file's preserved existing CRLF format. Placement resweep finds
  zero new bodies or pins. No ledger, pin, shared header or baseline changes.
- Same-index, same-cohort legacy local preview refreshes only the two
  explicit units in memory. Saved-before objects keep their canonical
  filenames. Each unit's findings decrease 5 -> 4; link-proof.json proves
  that the only removed finding is max. Local CLI results agree.

This is a verified two-finding reduction, with zero authored C++ growth
and legacy local LINKED 0 -> 0. Remaining findings in both units are the
Rb-tree iterator inequality, int allocator and alloc-proxy deallocate copies,
and the selected int-vector-base destructor. These independent blockers
were unchanged and were not retried. Strict compiler currency is established
for the two units; no self-strict LINK closure or closed-strict gain is
claimed. The closed-strict current-ledger check refuses judgment because
418 objects are missing. No fresh census placement or runtime result is
claimed. Maintainer-only runners and census build/measure/history were not run.

Donor review: retained verified BFME 1 revision
23b143233b5a8664a3bdf8572df6d905c310a5a1; reviewed linking repair
d3f9000fe08615a100e844adfff57fa4a39cd615 (suppress incidental nonretail
emission). Its principle applies, while its TileData identities/layouts do
not. The preceding BFME 2 vector-growth and armies-page repairs supply the
concrete max pattern; this pair's object proof establishes applicability.
No donor code is imported.

Official BFME 1 master was fetched as bc9907824. Compared with the retained
verified gitlink, only one Apt source, attempt records and donor conversion
gate/test code changed; no source headers changed. The clean verified
checkout/gitlink is retained. Comparative full verification remains
outstanding from earlier sessions, whose old-input gate required thousands
of stale TUs and was interrupted. No freshness-success stamp is written and
no unverified pointer is adopted.
