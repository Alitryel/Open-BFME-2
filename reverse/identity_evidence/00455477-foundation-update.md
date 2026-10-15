# FoundationAIUpdate::update at 0x00455477

The complete native body is 550 bytes, ending at the RET at 0x0045569C.
The existing FoundationAIUpdate constructor at 0x004551B3 installs the
UpdateModuleInterface vtable 0x00C40538 at complete-object offset 0x10.
Its update receiver reads the owner at this-8, the ObjectID at this+0x18,
and the initialization flag at this+0x1C. The initial primary callback is
slot 0x40 on this-0x10. WorldBuilder's corresponding body at 0x01170FB0
independently confirms the interface, two CastleMemberBehavior keys, and
the two separate UI paths. This is an argument-free callback returning
the 32-bit UpdateSleepTime value 1.

Reference provenance: Open-BFME-1 commit
0d78ce459f0371de7d7cd597fccc607f2d0d5c8b, inspected at verified donor
39df6df1f29418b4b600d985d421079617e8daa8, recovered its 0x002BAC00 update.
That source and targets/game/reverse/identity_evidence/002bac00-update.md
supplied the availability Boolean and construction-state setter semantics.
A normal BFME2 compile/placement trial of the unchanged donor found no
placements; the implementation here retains BFME2 offsets and control flow.
The BFME1 shared UI tail and by-value setter were not copied: BFME2 has two
UI paths and caller-owned string temporaries around StringBase::set.

Native evidence establishes Object's construction-state string at +0x424,
dead flag at +0x438, template kind bit150 at +0x11A, and Drawable's tested
byte at +0x43C. The Castle member's +0x14 and +0x18 values are ObjectIDs:
the already matched 80-byte BfmeItemE63::checkValid at 0x00397B89 passes
+0x14 to GameLogic::findObjectByID. The Castle result's +0x38 is copied
into that ID. Address-suffixed inline methods are descriptive local views,
not claims that their names were recovered from the target.

The whole home retains its existing bodies and uses the canonical GameLogic
lookup declaration. The visible 47-byte ObjectIdMap::find and 37-byte
GameLogic::findObjectByID providers are existing exact implementations;
their calls remain out of line. The const-reference state setter produces
the native ESI receiver reuse. WorldBuilder's outer pending-ID test and
inner availability predicate produce the native MOV/test sequence, closing
the last one-byte discrepancy. No new pin, assembly, barrier, dummy local,
or gate exception is required.

Validation: add_match verified 16/16 rows in the home, including all 15
previous rows. EH verification reports all four parents EXACT, including
the update's static-guard and string-temporary cleanup states. The source
has no undeclared definitions; link_check reports LINKS for the whole unit.
The required placement rescan found no additional bodies or pins. Local
raw evidence is under build/resume-foundation/ and
build/resume-foundation-native.txt.
