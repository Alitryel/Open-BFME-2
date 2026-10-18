# Canonical getBuildable provider

RVA 0033A632 was already recovered as a 44-byte address-view method. The ZH
ThingTemplate::getBuildable implementation, the three native calls from the
matched Player::canBuild, the previously harvested pin, and the target's signed
byte access at +5F2 support its canonical name and ABI. Rename that existing
owner, preserving its exact body, instead of adding an alias or another pin.
Remove ThingTemplate.cpp's conflicting donor definition. Its field access and
GameLogic callee differ from retail. The donor is semantic evidence for identity;
the target body and calls establish the offset and compiled implementation.

PlayerCanBuild_CanBuild also emitted a non-retail vector<ProductionPrerequisite>
size copy. The same imported forceinline size implementation verified in the
preceding repair removes that unused body without imports or caller changes.
The technique is inherited from BFME 1 repair 66b19a8e95a4add525ef808fcea088e306798e2b;
all acceptance evidence here is from BFME 2.

Controlled local preview against unchanged published index c2c5ac8c27,
2026-10-18 11:36: 44 -> 219 matched bytes link, a +175 B legacy local gain.
The renamed provider remains retail and linkable, the player unit becomes
linkable, and ThingTemplate remains blocked by its other dependencies.
The two dependent callers were migrated from the old address-view method name
to the canonical getter. Their bytes and directives are unchanged, and their
only external binding change names that same retail entry. The expanded local
preview reports 4,922 -> 5,097 bytes linked, the same +175 B gain. There is no
closed-strict gain claim. All five units and the unchanged size provider
ThingFactory have strict-current compile receipts.

Self-strict byte gate passes 37/37 rows; EH passes 6/6 EXACT. The renamed body has
identical bytes and relocations. All 1,221 retained consumer COMDATs are identical;
other non-debug sections and directives are unchanged apart from the two removed
bodies. No competing body is introduced. Check proof.json for object hashes,
provider bytes/relocations, and before/after findings. The two dependent
callers are checked separately in dependent-proof.json.

Additional checks: link_check --new-variants, pin_consistency --symbol/--check,
find_declared_unmatched, check_csv, place_bodies (zero new bodies or pins).
The broader prerequisite __copy issue remains blocked: the other candidate copy
calls operator= at 0042816E rather than the native 002D0C44 method. It was left
unchanged and recorded in re_attempts.log. Reference freshness remains held by
another worker's submodule claim; no pointer or success timestamp changed.
