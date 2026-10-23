# Link seat handoff, 2026-10-18

Preserved and reverified the existing unpublished Vector3 (+951 B), pointer
deque (+713 B), and horde exit iterator (+261 B) repairs. This session added
HeroTransfer's allocator-constructor repair (+280 B), documented in
../uint-vector-link-20261018/readme.md. All are local legacy preview gains,
not a new census or closed-strict measurement.

After rebasing onto origin a9d73a713f, all 30/30 rows in the five outgoing
Code units pass the normal byte/literal/import gates with strict reusable
receipts. All five link cleanly in the local legacy preview against published
index c2c5ac8c27 (2026-10-18 11:36). It reports 2,215 B: our attributed repair
gains sum to 2,205 B; the additional 10 B is an upstream horde-exit EH row.
No new authored C++ bytes or official census gain is claimed. Final hashes
and complete check output are attached. Adding the handoff files invalidated
the horde unit's whole-root include-directory inventory; its strict receipt
was refreshed after all evidence filenames were present.

Two independently verified repairs landed upstream during publication:
coordinate initialization (865c54fdb5) and ImageSubscriptMap rehoming
(4d3d8c4a6c). Their duplicate local commits were skipped during rebase;
neither gain is credited here. Upstream also repaired HostValidateColors'
remaining helpers (03a1f5a1ae). All failed source trials were restored and
all claims taken by this seat were released.

Restored failed trials, recorded through re_log.py in re_attempts.log:

* PeerDefsGameOptions: declaration-only and inline-only string helpers change
  native cleanup/register allocation (peer-gate*).
* ChatWindowsOnlineRoom, UpgradeCenterFindUpgradeByKey and
  StlportRegionIconSlotFillInsert: suppressing overflow copies changes
  matched frames/registers/cleanup (helpers-gate*).
* GameInfo::getConstSlot: ordinary COMDAT linkage loses same-TU preserved-EDX
  knowledge, a known blocker confirmed in constslot-before/after-gate.log.
  The new late-inline-declaration hypothesis is rejected by MSVC7.1 C2761
  (constslot-late-gate.log). All three source files were restored.
* The 567-B uninitialized_fill_n unit lacks a typed provider for
  _Construct<Rva0039A48EElement>. Its 37-B worker at 0x3961F0 calls 0x396170,
  currently owned by a legacy object-symbol alias. An inline bridge to the
  pair Construct preserves instructions but calls the distinct 0x1DD745
  twin. The gate correctly refuses that call target; do not add a fold pin
  for a name with distinct retail addresses. A future repair needs an
  ABI-correct provider replacing the alias owner (fill-*-gate.log).

The separately recorded BFME1 freshness blocker remains conflicting
Rva005E394EPrimaryBase vtables at verified donor 64d369b9017; official HEAD
95ca17f14 was fetched but not adopted. Do not mark freshness successful or
repeat unchanged trials. See ../bfme1-freshness-20261018/readme.md. No
maintainer-only verification runner or new census was started.

progress.py origin/master reports +0 authored C++ and +0 official linked
bytes because these are linking repairs and the census is unchanged. The
seat ends at its context handoff boundary with verified commits preserved
for publication. Unrelated untracked dumps and reverse/zh_sweep remain.
