# Explicit data ownership in executable sections

At BFME2 `007527709d`, the existing matched `_BFMEKeyboardObjectFormats`
row owns all 4096 bytes at RVA 0x00629F20 in retail .text. Its two-row source
and the existing keyboard consumer pass ordinary byte verification. The earlier
handoff is `directinput-keyboard-format-20261023.md` (attempt 82407).

The original data_rows.Resolver returns VA 0x00A29F20 for an untyped lookup,
rejects it for a data relocation, and accepts it for a function relocation.
Section permissions alone invert this explicit data ownership. This prevents
replacing the consumer's raw DIDATAFORMAT pointer bytes with a real relocation.

The resolver now retains explicit data-row provenance separately. A matched
row whose positive extent fits its declared retail section grants its own
name a data home, including .text. That home cannot be used as a function,
including through a pin. Pins, function rows and the legacy untyped DIR32
register still cannot supply an executable data home without that symbol's
own data row. Invalid row metadata grants no exemption. Existing whole-object
size, initializer and relocation verification remains mandatory; no byte
proof, baseline, pin or image-wide classification rule is bypassed.

An additional negative control found that verify_row followed an E9 jump
stub for data pointers as well as functions. Stub following now applies only
to function relocations; a data pointer must name the actual datum. Existing
DIR32/DIR32NB function-stub tests remain passing.

New controls cover explicit RVA and VA data ownership, DIR32 and DIR32NB
with zero/nonzero addends, function-pointer rejection, pin/function/DIR32
names without data ownership, invalid metadata, exact data-pointer equality
and data-stub rejection. Before repair, the initial 14 controls fail 8 and
pass 6; the exact-pointer negative control was added afterwards. All 108
tests across data_rows, empty-ledger behavior, parallel verification, real
hook integration and gate exploits pass after repair; one empty audit-fixture
parameter set is skipped.

The empty-ledger image-independence test also failed with the original
resolver: replacing today's populated data ledger with an empty fixture
exposes 12 data-only sources to the unchanged 6-source orphan limit. The test
now compares absent-ledger and header-only-ledger results while retaining its
retail-image trap. It neither suppresses orphan checking nor raises a baseline.

Ordinary build verification of DirectInputKeyboardOpen.cpp,
DirectInputKeyboardFormat.cpp and CRT/RuntimeDispatchSlots.cpp passes all
8 data rows and the complete 188-byte openKeyboard function. This includes
all five currently registered .text data extents and all 256 keyboard-table
GUID relocations. The live keyboard table resolves only as data at its
explicit VA after repair.

This commit changes tools/tests only. Consumer integration is separate;
no C++ or linked-byte gain is claimed for the verifier repair.
