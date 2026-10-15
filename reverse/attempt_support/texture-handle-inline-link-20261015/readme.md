# Texture-handle emission trial and reserve blocker

This is an independently verified trial, superseded by upstream fa5260064b
before publication. That commit repairs the same two conflicts with local
initialization tags. Rebase preserves its implementations; this commit changes
no C++ and claims no incremental linked or authored bytes. The imported-inline
variant below is trial evidence, not the final source. The before/after object
proof and prepare-touched/prepare-peers receipts describe that discarded variant.
The final upstream implementations are checked again in upstream-prepare.txt
and upstream-link.txt.

Terrain and snow initialize their existing one-pointer texture handles inline.
The trial marked that inline constructor imported to suppress two unused standalone
six-byte COMDAT copies which differ from the first copy in dx8wrapper.cpp.
Every retained nondebug section, data byte and symbolic relocation is identical;
no retained section references either removed copy. No new import, pin, alias,
header, layout or exception-policy change is involved.

Paired objects use BFME 2 base 36fd143744acb9bdd0d4d9cd74ed1925660ef13e
and the same runner index, census 28269d8e8d (2026-10-15 09:31). Its SHA256,
object hashes, provider selection and complete before/after findings are in
paired-object-proof.json. Both losing copies disappear; the selected
dx8wrapper constructor and every remaining copy's keep rule stay unchanged.
The terrain destructor, texture factory and dx8wrapper findings are unchanged.

Terrain's local legacy preview goes from zero to 276 existing unique bytes
(the matched constructor has a 277-byte extent, including one padding byte).
Snow loses one finding but retains its missing W3DSnowManager destructor and
the wrong Overridable::getFinalOverride copy. No new authored bytes or
closed-strict gain is claimed. Strict-current input receipts and byte checks
are established for the five sources; dependency closure is not established.
No census, full link cycle, shared index or link-status file is changed.

Checks: build.sh and strict preparation pass all 11 rows in the two touched
sources, one empty-string reference and four float literals, with zero imports.
Preparation of four peers (including snow before editing) passes 208 rows,
79 strings plus two empty references, 26 floats and 24 imports. The union is
209 rows in five sources. EH has two EXACT graphs, no baseline discrepancies.
Normal and converged data enforcement, class gate, undeclared-definition
checks, check_csv and diff whitespace checks pass. Placement finds no bodies
or pins. The trial's ordinary five-source link preview exits 1 because the unchanged
dx8wrapper and remaining snow blockers are still reported; terrain is clean.

The reviewed BFME 1 revision remains a7c38d3b2597121f178ab5190b3062478823257d.
The earlier linking review of d3f9000f/d2e21369 supplied the inline-emission
technique; the current target object comparison proves its application here.
No donor address, layout or identity is imported. A freshness fetch found
upstream a8148f4e, but the reference pointer is held by another live file
claim; verified inputs are preserved and no success stamp is written.

An independent ScienceType reserve suppression trial was rejected and reverted.
Although its four rows remained exact and a narrow preview admitted 825 bytes,
a paired 15-unit cohort exposed new wrong-selected reserve/allocation-chain
findings in 14 consumers. The working implicit provider must be reconciled with
the reserve owner and allocator dependencies before suppressing it. The blocked
verdict is in re_attempts.log; its source claim was released. This is not an
improvement credited to this session. Its blocked verdict and the independently
verified texture-handle trial remain useful handoff evidence; the latter's
276-byte preview gain belongs to the already-published upstream repair.
