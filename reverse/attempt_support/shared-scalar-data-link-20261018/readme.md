Shared scalar data ownership, 2026-10-18

Target evidence: Rva003B9E58's complete 108-byte command handler writes an
AsciiString view at VA DFE7AC. The next key begins at DFE7B0; the existing
one-pointer AsciiString definition owns those four loader-zero bytes. Its
address-derived name and unknown option meaning are retained.

RandomValue's 47-byte initializer at 7ADBFF stores its computed multiplier
at VA DFE738. The native 127/72/72-byte logic/client/audio readers all multiply
through that same address. Define one four-byte loader-zero float in the
client reader (the derived data ledger's existing owner), declare it in the
other three units, and remove the disconnected local constants. The native
initializer still computes the value; no constant initializer is substituted.
The ZH RandomValue.cpp at the retained BFME1 pointer
64d369b90170b7e9ec917d646f020b11f13eb0d5 supplies the original theMultFactor
spelling and shared role (lines 54, 293, 317, 341). Retail operands establish
BFME2 identity/address independently; the target's startup ordering is not
newly proved here. The separately fetched donor HEAD was not installed or
marked as a successful verified reference update.

Legacy link_check, same five units against published census c2c5ac8c27:
- Before: only the three readers link, 271 B. The initializer and command
  handler each have one undefined datum.
- After: 5/5 link, 426 B; additional linked bytes 155 (108 + 47).
Strict reusable compile receipts were prepared for all five units; normal
byte gates verify all five existing rows, both new data rows, seven float
literals, one string literal and one import. This is a legacy preview gain;
no self-strict placement, closed-strict, full-link or runtime gain is claimed.
No census/index/status, pin, header, baseline or verifier change is made.

CSV, frozen-definition, whitespace and converged-data checks pass. The four
RandomValue units pass data_check --enforce (two existing baseline findings,
none new). The command handler retains the unchanged flag reference
?g_00DFE7A8@@3EA: the old derived data ledger calls it ?g_Va00DFE7A8@@3IA,
while the byte-verified data_rows owner is Rva003B9EC4's unsigned char. The
manual enforce diagnostic is inherited, not a new name or definition. It is
not hidden by a baseline edit. The normal data ownership checks verify both
new definitions against retail.

Preparation recovery: upstream e6fae26dd3 already repaired the command handler
by addressing DFE7AC as an offset into its existing DFE7A8 datum. Keep that
owner/view and omit this patch's independent AsciiString definition and data
row. The original +155 B preview above is historical; only the independent
47-byte multiplier-initializer repair remains new relative to that upstream.
