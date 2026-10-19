# Word-vector identities and four-byte constructor repair

Target evidence establishes element widths and call relationships; donor source
supplies the unsigned port type. No new C++ coverage is claimed by this repair.

## Identity evidence

- Original ZH `GameNetwork/GameSpy/GSConfig.cpp:103` and BFME1 revision
  `b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`'s corresponding source at line107
  declare `m_manglerPorts` as `vector<UnsignedShort>`. BFME2 commit3072735325
  substituted signed short while reconstructing the constructor; its signed
  identifier evidence concerns the VIP tree, not the ports.
- Retail's constructor54E8DC calls port push54E89C at54EF67; push reaches
  overflow7EAA7 and two-byte allocation17710. Getter54E7EA copies a word into
  an UnsignedShort output. This establishes width and donor relationship,
  without pretending that a word copy independently proves signedness.
- Constructor54E955 calls empty base7FAEA, which calls proxy7410. The former
  draft candidates211E58/14F3C4 were rejected against that actual call chain
  and are not part of this change. The final G-name pins pass full-body and
  every-owner relocation fold admission at the actual called addresses.
- The SightingInfo pointer-deque base620690 calls proxy7410 at6206C4.
  Its genuine deque instantiation emits the exact11-byte proxy; it replaces
  the legacy int-proxy gen-alias owner using `add_match --replace-rva`.
- Unsigned-word overflow7EAA7 calls two-byte fillAD8C9. The previous G fill
  pin7E48F instead copies DWORDs at stride4. The admitted replacement fold
  atAD8C9 reproduces the entire34-byte owner and its relocations.
- Count constructor2339F3 and fill constructor511E1C call base4F62A4 and
  fill7E48F. Those providers allocate n*4 and store DWORDs. WB twin687CB0
  confirms the DWORD fill. Existing uint/HKL/ScienceType family providers
  support a four-byte storage view; the original application element type
  remains unknown. Remove the false G claims, retain the existing uint fill
  owner, and row the already-emitted uint count constructor. The two native
  constructor consumers5BEA06/58062B now use that four-byte view.
- Word resize824F9 reaches fill-insert7FF18 and insert81A1F. Rehome those and
  port push/overflow to the compatible unsigned-word provider, removing the
  old fill gen-alias/object-symbol token rather than introducing new aliases.

## Verification and limits

Normal `./build.sh` over the six related vector/provider/consumer units and
the two deque units: **71/71 exact**,49 literals plus16 empty-string references,
and2 named imports verified. Frozen-definition checks pass for all eight;
pin consistency passes with6 multi-pinned symbols and no new/stale exception.
Normal pin admission verified each new fold. No shared headers, tools, compiler
flags, gate exemptions or dependencies were weakened.

Paired `link_check.py` against published indexd5ae1ce9c2,2026-10-19 19:24,
replacing all eight current provider/consumer objects together:

| Unit | Prior census linked bytes | Current preview linked bytes |
| --- | ---: | ---: |
| short vector provider | 0 | 0 |
| word vector provider | 0 | 468 |
| uint constructor provider | 44 | 95 |
| GameSpy config | 0 | 0 |
| constructor5BEA06 | 0 | 28 |
| constructor58062B | 0 | 27 |
| int deque | 960 | 960 |
| SightingInfo deque | 265 | 276 |
| Total | 1269 | 1854 |

This is a prediction of **585 more linked bytes**, not a newly run census.
The word provider preserves the vendor's inline `_Construct<G,G>` semantics
with the existing dllimport/forceinline idiom so its external copy comes from
the canonical wide-string provider19A00. This passes both byte and link checks.

GameSpy retains its prior unresolved methods and private tree/string/vector
definition conflicts; changing the port type moves its existing short-family
definition debt to the correct word family. Trials of declaration-only push,
declaration-only overflow, inline import construction, and inline import
deallocation suppressed copies but shifted constructor local stack homes and
invalidated associated EH placements. None of those GameSpy trials is landed.
Their reproducible directions are enough to resume a separate linking repair;
do not repeat them as though a declaration alone preserves the constructor.

The legacy UTF16 count/base513DD0/513D55 chain also calls proxy7410 and
allocation17710; its original signedness remains unproven. Its historical
short allocator candidate is retained unchanged, alongside the
independently proven signed allocatorAD722. This repair does not rename that
unrelated chain or claim to have unblocked shader Init18C84E yet.
