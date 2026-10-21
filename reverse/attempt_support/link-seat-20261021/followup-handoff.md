# Link-repair follow-up, 2026-10-21

Three locally verified repairs recover 3,077 nonpadding bytes in paired
current-object legacy previews using the same explicit source sets on each
side. Water was independently published upstream in 41db846694 during this
seat's publication rebase; the two remaining novel repairs total 2,686 B:

* Wall placement: visible Coord2D::toAngle calls retail float ACos, +2,218 B.
  Evidence: ../wall-angle-link-20261021/.
* Water-track flush: bind the existing WW3D shadow-map flag instead of the
  unresolved DX8 statistics aggregate, +391 B locally verified and already
  upstream. The rebase retains upstream's accessor/header view.
  Evidence: ../water-shadow-flag-link-20261021/.
* HordeContain onContaining: deferred int/int map helper uses retail's
  frame-omitting profile, +468 B. Its complete 56-byte COFF section matches
  retail without masking or relocations. Evidence: ../horde-find-link-20261021/.

The wall and Horde repairs have separate source commits. The water commit
preserves verification evidence and corrects its ledger note. All three have
ordinary byte acceptance and self-strict reusable receipts. No closed-strict closure or full link cycle is claimed.
The Horde repair adds one optimization pragma to the shadow hatch count;
no baseline was enlarged. The BFME1 donor review remains at verified
5987fd1b859e86801d093256eadc6fb63d87785f, as documented in the earlier handoff.

Final validation after rebasing onto 41db846694: all four rows across the three
edited units pass build.sh, with 12 float literals verified. The five-source
link_check cohort (three consumers, coord2d.cpp and stlport_map_int_int_os.cpp)
links all five units, 5,872 B. The two unchanged providers contribute 2,795 B;
the three consumers contribute 3,077 B, including the concurrent upstream
water repair. These preview totals are not additive gains over origin/master. check_csv passes with 97,919
function rows, 15,939 symbols and 1,381 data rows. The published census remains
17918792f6; progress.py origin/master reports +0 authored C++ and +0 census
LINKED delta. These are link repairs, not new C++ coverage or a census update.

## Remaining leads and checked queues

link_rank --top 30, --near 2, class_views --blockers and repair_queue link were
reviewed. Many reported sole blockers already link with current objects:
SceneSpatialCollect (1,317 B), PlaceEventTranslator, map insert/create-node
siblings, Rva0046152FFinish, and the int-map provider (503 B when its current
Pathfinder/Emotion peers are included). Do not claim those stale census arrows
as new repairs. The prior tracked handoff and attempt log cover unchanged
allocator, string/vector visibility, math helper, EH and class-identity blockers.

The most concrete newly checked lead is the case-insensitive tree create-node
copy at 0x002CFA8E. Its canonical provider exists and is retail-equal. Current
stlport_rb_tree_clone_node_nocase4_002CFE27.cpp (30 B) and
stlport_rb_tree_copy_nocase4_002D0399.cpp (304 B) lose only their local non-retail
copies. Both file claims were refused because nbr-N7 holds them. No edit or
trial was made. Their existing typedef can support a declaration-only member
specialization, subject to ordinary bytes/EH and a paired provider/consumer
preview. The similar less<AsciiString> siblings already link (715 B together
with Rva002214A6Dtor); do not include them as gains.

Other active foreign claims include pathfinder.cpp, the LivingWorld building
types pair cleanup, MetaImpactNugget and OpenContainExitObjectInAHurry. Avoid
repeating their recorded failed imports or changing their units concurrently.
The Rva00598CFD destructor blocker was recorded this session and its claims
released: the native second vtable slot needs the real AIUnitBuilder owner.

The rehome_rows fallback cannot run because build/link_census/census.log is
absent. This is a missing artifact, not proof of an empty rehome queue. The
index exists; no census rebuild, full link cycle, nightly or boot runner was
started. Reassess these leads after upstream repairs, claim release or the
runner's next published index refresh. No nonmatching source is left behind.
