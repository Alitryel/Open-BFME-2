# EmotionTracker filter linking, 2026-10-24

Inputs: BFME2 e46a0ba24c; verified BFME1 pointer 32774ab0; unchanged MSVC7.1
flags and dependencies. Published index 268f876e3b (retail-truth-4).
No tools, headers, pins, baselines or function rows changed.

The 2,200-byte update and its compiler EH rows contribute 2,207 unique bytes.
Its original local PartitionFilter, RvaDistanceFilter and RvaPlayerFilter
spellings emitted conflicting base/Taunt cleanup and unbound virtual methods.

Target facts, read independently from native update relocations and tables:

| Native table VA | Update body offset | Three native slot RVAs |
| --- | --- | --- |
| BC26E0 | 28F (cleanup) | 421D5, 3B810, 36CC7A |
| C0719C | 198 | 395A19, 261513, 36CC7A |
| BF8FE4 | 1BA | 395A19, 26109D, 36CC7A |
| C56520 | installed by existing Taunt constructor | 395A19, 4B0FEB, 4B0D28 |

Existing Rva00261513Filter and Rva00261058 providers establish the first two
derived filter identities. Their native +8 object/player, +C flag and +10
scalar fields agree with this caller's initialization. The polymorphic
prefix and +4 chain agree with Rva000421C8. The canonical PartitionFilter::And
owner remains a call view: casts pass these layout-compatible native chain
prefixes to its existing 46-byte implementation at 625790.

The Taunt constructor is already external and owns its runtime vtable.
novtable keeps this consumer from emitting another table; its local declaration
has the same destructor/predicate/mask slot order and inherited eight-byte
prefix. The existing provider's Allow spelling is unchanged; the consumer
does not emit or reference a new predicate definition. Base cleanup now emits
the same seven-byte Rva000421C8 vptr reset as the constructor unit's Taunt
destructor. No new function identity or descriptive member name is claimed.

BFME1's reviewed linking repairs at 32774ab0 provide the general pattern of
using existing providers and reconciling private ABI views. The addresses,
slots and field claims above come from BFME2, not from donor assumptions.

Paired checks used unchanged providers and identical production inputs:

* Before: update fails with three unresolved names and two COMDAT conflicts;
  the four-unit cohort links 418 bytes.
* After: all four units link, 2,625 bytes, **net +2,207 bytes**. Providers:
  Rva004B0FEBCtor.cpp (240), Rva00261058Ctor.cpp (144), Rva00261513.cpp (34).
* Both source versions pass build.sh, 3/3 rows. The changed parent retains all
  2,200 bytes and every relocation; the handler and eight-byte cleanup remain
  exact despite compiler-local label renumbering. String, float and import
  checks pass. find_declared_unmatched passes.

The earlier isolated flattened Taunt-layout experiment also matched but was
discarded: the landed implementation preserves real inheritance and uses no
cast destructor call. Only ordinary constructor-owned virtual dispatch and
the existing canonical chain-call view remain.

This is a scoped legacy link prediction, not a fresh full-link census or
closed-strict coverage claim. Paired logs remain in ignored
build/link-emotion-20261024/{before,after}-{byte,link}.txt.
