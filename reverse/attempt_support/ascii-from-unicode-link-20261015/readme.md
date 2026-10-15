# Narrow StringBase constructor link repair

Base: 998217dc446646f94f034f8f5942c8a3cb7aadc4. Frozen published index:
a2839ea429, 2026-10-15 13:35, underlying census 5986a99448 at 04:52.
The committed link status served discovery only. proof.json records the exact
index hash, objects, paired findings, and removed body for each consumer.

AsciiFromUnicode.cpp and GeometryInfoCalcBoundingStuff.cpp each emitted a
surplus 9-byte StringBase<char> default constructor. The native 6-byte provider
is string_base_clear.cpp at RVA 00326BE6. TU-local imported forceinline
specializations preserve the null-store semantics and inlined callers while
suppressing the external copies. Both files were claimed and passed the frozen
file check before editing. No flags, headers, layouts, pins or ledger rows change.

## Evidence and provenance

Existing target evidence identifies the exported narrow conversion at 00038250,
its wide translate callee, and native EH graph. Geometry's existing target
callers, 36-byte records and field accesses establish its identity and layout;
this repair makes no new identity or layout claim.

Reviewed BFME 1 repair c1315665a1b22beb7e6d9279548fe5b1c26ed1f9,
suppressing unused DamageInfo constructor copies, plus BFME 2's existing
UnicodeFromAscii.cpp specialization (6c347cbcf0). The suppression technique
applies; BFME 1 addresses/layouts are not transferred. Target object comparison
independently proves unchanged semantics and bindings for each retained body.

## Acceptance

- Strict bounded --prepare-current passes 18/18 rows across both consumers and
  string_base_clear.cpp, before/after preparation for each edited unit. Direct
  build.sh also passes 3/3 conversion and 5/5 geometry rows; five float literals
  pass. The provider's object is byte-for-byte unchanged.
- proof.py compares ignored build/ascii-from-unicode-link-20261015 before
  snapshots with strict-current objects. All 7 conversion and 22 geometry retained
  COMDATs preserve bytes, extent and normalized relocation digest. All other
  nondebug sections and normalized relocations are identical; directives are
  identical. Only the 9-byte constructor COMDAT disappears in each object.
  No retained code/data references it. External bindings lose just its definition;
  no __imp reference is added.
- Deep copies of the same frozen index, refreshed with exactly these three
  explicitly prepared objects, give conversion legacy findings 1 -> 0, provider
  0 -> 0, geometry 6 -> 5. Ordinary link_check agrees: conversion LINKS with
  0 -> 101 unique nonpadding bytes (parent and rowed EH), provider stays at 18,
  geometry stays at 0. These are local legacy predictions using strict-current
  inputs. No self-strict executable-placement or closed-strict gain is claimed.
- EH verification: one applicable graph EXACT, zero missing/nonexact. Class,
  declared-definition, enforced data, converged data and new-variant checks pass.
  Placement rescans of both edited sources find zero bodies and zero pins.
  CSV and whitespace checks pass. Commit hooks provide the final staged checks.

This repair adds zero authored C++ bytes. Census index/status/history are not
modified. No full census, link cycle, nightly, boot or scheduler operation ran.
proof.py depends on local ignored before snapshots; proof.json preserves the
result, rather than asserting portable standalone verification.

## Sweep and remaining blockers

sweep.json lists all 18 indexed narrow default-ctor emitters: 16 already have
the retail digest; only these two have the divergent 9-byte digest. The reverse
wide conversion already suppresses its surplus constructor and passes its local
check. No additional consumer of this specific divergent body remains in the
sweep. Geometry still needs GeometryNames, Coord3D::zero, bfmeMin<float>,
bfmeMax<float>, and AsciiString's default-ctor provider reconciliation. This
repair does not claim it links. Existing string-record destructor/import-EH
blockers and the floating-point guard codegen blocker were not retried.

Official BFME 1 master fetched at 464e5b6023f9ac16b1e824d410021bea73e48190;
the clean verified gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Another worker holds file:reference/open-bfme-1. Its overdue comparative update
also has the old-input full baseline rebuild blocker recorded in attempt 53899;
no pointer advancement or successful freshness stamp was made here. Dependency
receipts for the geometry unit resolve the donor headers under game/, including
WWMath/coord.h, WWLib/ascii_string.h and WWLib/string_base.h; no header was
silently substituted. The checked-in old include paths are resolved by the
existing build layout resolver.
