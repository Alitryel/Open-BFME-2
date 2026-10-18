# Prerequisite vector size providers

Two units lost against ThingFactory.cpp's rowed vector<ProductionPrerequisite>::size
at RVA 00626DF0. They emitted the same 12-byte idiv copy where retail keeps the
25-byte reciprocal-multiply body. The imported forceinline technique reviewed in
BFME 1 commit 66b19a8e95a4add525ef808fcea088e306798e2b preserves inline semantics
while suppressing the unused out-of-line bodies; no import reference is emitted.
Target layout remains the existing independently verified 36-byte element stride.

Controlled before/after against the same published index (c2c5ac8c27,
2026-10-18 11:36), refreshing only both consumers and their unchanged provider:
legacy local linkable matched bytes 0 -> 592 (386 + 206). This is not a
closed-strict link result. Both changed consumers and ThingFactory have strict
current compile receipts; self-strict byte verification passes 9/9 consumer rows
and 8/8 provider rows. All 25 retained consumer COMDATs have unchanged bytes and
relocations. Every other non-debug section, external binding and linker directive
is unchanged, except each removed definition; both removed bodies have no
non-debug references. The provider is unchanged and classified retail. See
proof.json for hashes, exact removed/provider bytes and findings.

Checks: build.sh both consumers; link_check.py --prepare-current both consumers
and ThingFactory; link_check.py --new-variants; eh_verify.py (no EH rows);
find_declared_unmatched.py; place_bodies.py (zero new bodies or pins).

The same size blocker also appears in ProductionPrerequisiteVectorPushBack and
PlayerCanBuild_CanBuild. Neither would link after size suppression alone: both
still touch wrong kept definitions from ThingTemplate.cpp (__copy and getBuildable,
respectively). They were inspected without source changes. The BFME 1 pointer
remains at verified 64d369b9; freshness update is held by another claimant, so no
freshness-success timestamp or reference pointer was changed.
