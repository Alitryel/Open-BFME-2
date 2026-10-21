Decimal-reader link repair, 2026-10-21

Baseline parent: 704ddb5f0f. Published census: 2b4d1fb42a, 2026-10-21 06:00.
The current narrow and wide decimal-reader objects each had one unresolved
__get_integer<iterator,int> reference. Their long accumulator providers
already linked (392 bytes each); both readers held out 133 bytes each.

Instantiate int beside long in the two existing STLport 4.5.3 providers.
MSVC 7.1 gives both signed types 32-bit arithmetic and reference ABI here.
This is a donor/language relationship; target identity is established
separately by the full pin_admission fold proof, not by type width alone.
Both int names reproduce the entire corresponding native 392-byte body,
including every owner relocation, and have no other retail address.
The admitted pins carry fold-proof=<their matched provider source>.
No owner, consumer source, retail extent or verification rule changes.

Acceptance: build.sh passes both existing provider rows; prepare-current
passes all four code rows and strict reusable receipts; pin_admission --add
accepts both complete fold proofs; pin_consistency --check and declared
source checks pass. The admission tool updates its hatch register itself.

Paired link_check with all four explicit sources and unchanged frozen
providers: baseline 2/4 units, 784 bytes; after 4/4 units, 1050 bytes.
Gain: 266 legacy linked matched bytes, zero new authored retail bytes.
Self-strict byte verification passed. Closed-strict LINK closure is
unmeasured; no census, LINK cycle or maintainer-only runner was started.

Reproduce using tools/link_check.py on the four files named
stlport_{narrow,wide}_get_decimal_{long,reader}.cpp in
Code/Libraries/Source/WWVegas/WWLib/. Admission can be rechecked with
python3 tools/pin_admission.py --range 704ddb5f0f HEAD after commit.
The int accumulator blockers occur only in those two readers in this census.
