# Link-seat preparation recovery, 2026-10-23

Recover runner record phase syncing, saved head 34ff2a4a1c, onto recorded
upstream 202984df58. Preserve backup refs/runner/preparation/1792783841197168100
and stash 1f247304bf49ef1f003edaf415378e8adcfb99f9. No rebase abort or blanket
conflict resolution was used.

Resolved the Bridge conflict by retaining upstream 4bfe15ba2f's include roots
and destructor implementation, plus the saved supported STLport inventory
marker. Retain both independent evidence records. Resolved the deque conflict
by retaining upstream 3c44410e40's equivalent binding unchanged and preserving
the saved evidence and blocked STL records. Neither repair is credited again.
All five saved commits replayed. The map-cache export was already upstream,
so its replay retains only evidence.

The first dry-run push refused a duplicate BuildListInfo post-load row.
Upstream 8bf8041bea already defines the same method in Rva0032A186Finish.cpp.
Remove only the saved duplicate row and constructor-unit definition; retain
the upstream provider and the constructor's declaration. Its saved historical
+622 B preview is not new recovery progress.

Acceptance on reconciled sources:
- check_csv passes: 98186 function rows, 15796 symbols, 2169 data rows.
- build.sh on ArmorHashMapErase, Rva003ED2A3ManagerRemove, Bridge destructor
  and BuildListInfo constructor: 15/15 rows; string/float/import checks pass.
- link_check --prepare-current: all four explicit providers have strict
  reusable compiler receipts and pass the ordinary byte gates.
- eh_verify on Bridge destructor and BuildListInfo constructor: EXACT 3/3.
- find_declared_unmatched accepts all four sources.
- Same six-unit Armor preview against b711de3634: 6/6 link, 358 -> 511 B.
  Preserves the saved +153 B legacy scoped prediction; no closed-strict or
  placed-link claim is made. The saved before evidence is in the Armor note.
- All six untracked reverse/zh_sweep files restored from the stash's third
  parent and compared byte-for-byte. They remain untracked as originally saved.

Diagnostic logs stay in build/recovery-{byte-gate,prepare-current,armor-link}.log.
Publication must pass git push --dry-run origin HEAD:master before the recovery
publisher runs. No new lane tasks, census build, full link cycle or boot runner
were started. Backups remain available after successful publication.
