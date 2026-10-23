# Debug-description bitset wrapper repair

BFME2 base: `18389c4ef77d7d5a93436914a297565ccc3fe762`.
Consumer: `Code/GameEngine/Source/Common/Rva0059B5A3Describe.cpp`, complete
552-byte body at `0x0059B5A3`. Provider witness:
`Code/Libraries/Source/WWVegas/WWLib/stlport_BaseBitset32IsAny.cpp`, 20-byte
`_STL::_Base_bitset<32>::_M_is_any` at `0x000454A6`.

The consumer's private UpgradeMaskType::any wrapper forwards to the 32-word
provider. It is inlined into the description but also emits an unused
five-byte tail-jump COMDAT. The supplied census selects a different wrapper
from SpawnBehavior_update.cpp first, leaving this consumer with one competing
COMDAT finding. Remove the redundant wrapper and call the same inherited
provider directly. Preserve the private mask representation and its test
helper; no new identity, layout, header, pin, flag, row, extent or data owner
is asserted. Both explicit files were claimed before modification/verification.

Target evidence: the consumer's REL32 operand at body offset 382 reaches
`0x000454A6` in retail. The matched provider loops over 32 words and returns
whether any is nonzero. Before and after consumer objects retain exactly the
same call spelling, full bytes, and relocations. This repair uses existing
target evidence; it imports no donor body or target layout.

Acceptance:

- Bounded `link_check.py --prepare-current` before/after verifies 2/2 rows
  with reusable strict compiler receipts. Independent `./build.sh` verifies
  2/2 rows, eight literals and two imports; zero skipped/baselined references.
- Complete object proof: all 13 retained consumer COMDATs and all 539 provider
  COMDATs retain raw bytes, size and relocation digests. Every non-debug and
  non-directive section retains its flags, size, bytes and actual relocation
  targets, except the deleted five-byte wrapper section. MSVC's local EH labels
  and the `.sxdata` handler symbol index are compared by their actual targets.
  External bindings are identical except the removed unused wrapper definition.
  The provider object is unchanged. Strict receipts remain current.
- EH: 1/1 EXACT; no missing, nonexact or baselined graph. Class, undeclared
  definition, variant admission, CSV and whitespace checks pass. Data shadow:
  zero findings. Enforced converged data: eight addresses, zero second names
  or unjudged rows. Consumer placement resweep: zero bodies, zero pins.
- Same-index paired local legacy previews: consumer 0 -> 552 existing linked
  bytes, provider 20 -> 20, cohort 1/2 -> 2/2 clean and 20 -> 572 bytes.
  Available index measurement: `147cfae2cb`, 2026-10-14 07:27, SHA256
  `690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
  The committed queue at `67e1365aa9` is discovery only. No census, index,
  status or history is written. Authored matched coverage grows by zero.

Verified improvement: one competing wrapper removed and 552 existing bytes
unblocked in the local legacy preview. Strict receipts establish current byte
verification, not self-strict placed linkage or closed-strict closure. No
closed-strict or measured census gain is claimed. Broader linking still needs
the runner's refreshed census; no maintainer-only verification runner was used.

Donor review: retained clean verified checkout/gitlink `23b143233b5a8664a3bdf8572df6d905c310a5a1`;
official master fetched to `a7c38d3b2597121f178ab5190b3062478823257d`.
Reviewed BFME1 repair `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`:
removing surplus forwarding definitions is applicable, while its constructor
identity and alias scaffold are unrelated. Its lack of a local census preview
is not inherited as evidence here. Reuse the prior broader dedicated donor
review rather than repeating it. The overdue reference update remains reserved
by the live foreign `file:reference/open-bfme-1` claim; prior compiler/cache
verification blockers remain documented. No donor pointer or success stamp
changes and no successful freshness update is claimed.

Discovery: repair_queue.py link; link_rank.py help, --top 15, and the A/S/L/D
rankings. Prior logs exclude the unchanged disabled-until, private curve
destructor and tab-list ABI blockers; already repaired getter candidates were
confirmed rather than retried. The supplied index lists only this description
as blocked by this wrapper; the sibling description does not use UpgradeMaskType.
Scratch source/object backups, complete logs and reproducible proof script are
under `build/upgrade-mask-any-link-20261014/`; tracked object-proof.json retains
the verified before/after evidence.
