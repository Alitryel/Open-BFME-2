# DirtySDK crypto: provenance and target evidence

This record supports the identities and layouts used by `cryptsha1.c` and
`cryptrsa.c` under `Code/Libraries/Source/DirtySock/`. The import replaces 12
already-matched reconstructions with original EA function bodies. **It adds
zero matched bytes.** Donor names, target observations, and unresolved claims
are distinguished below, as required by `AGENTS.md`'s donor-provenance rule.

## Donor source and adaptations

Donor: [achellies/DuiBrowser at
03db25634fe8696ee060e1c01bff8fa0911fcba8](https://github.com/achellies/DuiBrowser/tree/03db25634fe8696ee060e1c01bff8fa0911fcba8/Duibrowser/src/EAWebkit/EAWebKitSupportPackages/DirtySDKEAWebKit),
supplied in `ea-dirtysdk-source-handoff.zip`. Paths below are relative to that
package's `source/dirtysdk/local/`. Hashes cover the archive payloads before
whitespace normalization.

| Donor file | SHA-256 |
| --- | --- |
| `core/source/crypt/cryptsha1.c` | `1cd5241b3162c9ec654c35aaa420c96aa53ce45b3874e41f64c408a2f0f5b164` |
| `core/include/cryptsha1.h` | `80acde2660906aa86d8faa500f5877f067d1ff7b117419d3bcb27913953e7f5a` |
| `core/source/crypt/cryptrsa.c` | `eb3d97333967e39f5696491fe3ecafbf5486be641e178dc26d665fe27b79255e` |

The donor supplies function/type/field spellings and identifies itself as
DirtySDK 7.5.3 (`DIRTYVERS 0x07050300`). **BFME2's exact DirtySDK release is
not established.** Original EA notices remain in both imported units.

The 12 function definitions retain donor bodies and linkage. Adaptations are
limited to whitespace and include scaffolding: TU-local Win32 integer types,
the donor SHA-1 context and hash-size constant, and `dirtylib.h`'s non-debug
`NetPrintf(_x) { }` macro. `<string.h>` comes from MSVC 7.1. Both units use
`/Od /GZ /GS /MD /DNDEBUG`. The existing opaque RSA entry moves beside the
private helpers so they retain static linkage.

## Target evidence

Target: Workshop vanilla BFME2 1.06 `game.dat`, SHA-256
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
All addresses are BFME2 RVAs; all ledger extents are preserved.

| C function | RVA | Retained bytes |
| --- | --- | ---: |
| `CryptSha1Init` | `0x0067D080` | 74 |
| `CryptSha1Update` | `0x0067D0D0` | 317 |
| `_CryptSha1ProcessBlock` | `0x0067D210` | 913 |
| `CryptSha1Final` | `0x0067D5B0` | 388 |
| `_CryptSha1CopyHash` | `0x0067D740` | 120 |
| `_Exponentiate` | `0x0067B4A0` | 1,359 |
| `_Multiply` | `0x0067BA40` | 437 |
| `_Addition` | `0x0067BC30` | 146 |
| `_Subtract` | `0x0067BCD0` | 149 |
| `_BitTest` | `0x0067BD70` | 94 |
| `_ToWords` | `0x0067BDD0` | 211 |
| `_FromWords` | `0x0067BEB0` | 101 |

### SHA-1

Init and CopyHash match whole bodies without relocation masking. Target SHA-1
initial values, round constants, and the `/GZ` local `W` of size `0x140`
corroborate the algorithm. Five target calls connect the matched bodies:
Update calls ProcessBlock at REL32-field offsets 150 and 212; Final calls it
at offsets 136 and 347, then CopyHash at 367. These offsets are relative to
each caller's start.

Target field accesses establish the donor context layout independently:

| Donor field | Offset | Target observation |
| --- | --- | --- |
| `uCount` | `0x00` | Block-byte count and final length encoding |
| `uPartialCount` | `0x04` | Partial-buffer index and reset |
| `H[5]` | `0x08` | Initialization, round accumulation, digest output |
| `strData[64]` | `0x1C` | Input copies, padding, block arguments |

The wrapper at `0x00679520` allocates this 92-byte context, calls init/update/
final, and requests 20 output bytes. Its original function name remains
unestablished; it retains `Rva0080D620` and the target-recorded local `Sha1`.
ProcessBlock's 913-byte ledger span includes its 891 instruction bytes and
22 existing metadata bytes. That metadata is not new function coverage.

### RSA

Addition, Subtract, BitTest, ToWords, and FromWords match whole bodies without
relocation masking. Target instructions establish 16-bit, most-significant-first
limbs, carry/borrow behavior, and big-endian conversion. The target call graph
corroborates the donor helper identities:

| Caller | Matched callees and call-site counts |
| --- | --- |
| `_Exponentiate` | `_ToWords` × 2; `_Multiply` × 26; `_FromWords` × 1 |
| `_Multiply` | `_Addition` × 2; `_Subtract` × 2; `_BitTest` × 1 |

The exponentiator's fast paths for 3, 17, and 65537 also agree. Its 1,359-byte
and Multiply's 437-byte instruction extents exclude the donor's trailing
`/GZ` metadata; the larger compiled spans are not claimed.

The moved 68-byte entry at `0x0067B450` retains `Rva0080F550` and its opaque
byte-pointer state. Target instructions establish its argument offsets
`0x404`, `0x400`, `0x48C`, and `0x488`. **A complete donor `CryptRSAT` layout
and public-API equivalence are not established.** For example, donor
`CryptRSAInit` has size-clamping branches absent from the target setup helper.

These identities rest on whole bodies, target behavior, and consistent call
relationships together. They do not establish identities or layouts for other
DirtySDK modules. Ledger rows and the normal byte gate remain the verification
authority; this document is supporting evidence, not a coverage claim.
