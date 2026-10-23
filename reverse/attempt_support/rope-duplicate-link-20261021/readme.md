# Rope duplicate prerequisite, 2026-10-21

At ebfb4fa883 plus particle repair 7a2d918535, the frozen 03035cf02c census
selects the obsolete donor buildSegments copy in Drawable/W3DRopeDraw.cpp,
blocking the 131 B initRopeParms unit. The rowed retail body belongs to
Drawable/Draw/W3DRopeDraw.cpp. The donor retains five matched rows, notably
35 B _Construct<SegInfo,SegInfo> at RVA 16CC80.

Prior attempt (re_attempts line 77265) removed the duplicate but lost that
helper. Two new trials:

* Explicitly instantiate _Construct<SegInfo,SegInfo> at file scope: VC7.1
  C2248 because SegInfo is private; this compiler does not exempt the
  explicit-instantiation spelling from its access check.
* Remove duplicate and keep a function-pointer anchor in doDrawModule,
  where SegInfo is accessible: helper survives, four rows pass, but VC7.1
  emits a local-static initialization guard and grows the 384 B native
  draw routine. Candidate patch preserves this diagnostic only.

No gain; source restored. Need a supported class-scope declaration/header
reconciliation or compiler-supported instantiation mechanism. Do not keep
an obsolete code body merely as an instantiation anchor. The native owner
also has independent E16 clear/overflow conflicts; removing the donor alone
would not make that owner link. Logs: build/seat8-rope-{before,byte,byte2}.log.
No donor revision changed: 68c5ce2789e974f36b6c742d57437d157bc159e9.
