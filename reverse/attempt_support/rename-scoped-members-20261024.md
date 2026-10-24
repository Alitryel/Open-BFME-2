# Scoped parameter/local member collision false reject

Base reviewed: `799f2d22cc5a8c8e621cf6606d143d3331008411`.
Reported case: the `RvaFireColor` attempt for the settings constructor at
RVA `0x0030AEB6`, 217 B. That address is a locator for the containing matched
settings code, not a newly established out-of-line address for the inline
color constructor. This is a verifier repair with zero new C++ bytes.

## Reproduction

`INIBfmeSettingsParsers.cpp` declares `S12::b` separately from the inline
`RvaFireColor(float redValue, float greenValue, float b)` constructor.
`RvaFireColor` derives from the declared `RGBColor`; neither owns `b`.
The existing agreement `nl-cf07ec57b1bb` proposes `blueValue`.

```
python3 tools/rename.py param \
  --source Code/GameEngine/Source/Common/INI/INIBfmeSettingsParsers.cpp \
  --function RvaFireColor --name b --new blueValue \
  --basis inferred --evidence agree:nl-cf07ec57b1bb \
  --dry-run --no-claim --no-object-scan
```

Before: exit 2, `b is also a member of S12 ...; the function may mean it`.
`other_declarations` treated all named class fields in the unit as possible
meanings of the selected function's word. A scoped rewrite cannot reach
`S12::b`, and the unrelated class's member cannot be the parameter's meaning.

The paired in-memory proof in `rename-scoped-member-proof-20261024.json`
loads the immutable old verifier and the repaired verifier against the same
real tree. Only the latter plans the rename: exactly the two code occurrences
in the constructor, plus its ordinary name-basis record. SHA-256 checks prove
the native source, votes, agreements, naming records and function/pin ledgers
were unchanged. No real rename was applied or agreement status advanced.

## Repair and limits

- Restrict the old word's named member owners to the function's class and
  bases, using the existing complete-chain proof. A free function has none.
- Missing/unparsed bases retain the all-member refusal. A nested owner or
  base declared in the unit or an included header also retains that refusal,
  since enclosing class lookup would require further evidence.
- Keep global, macro, explicit `->`/`.`/`::`, function-text, optimization,
  prototype, provenance and ordinary new-name checks.
- Permit the recorded exact inverse to restore its original word beside an
  unrelated named member. `check_restore` must first prove that exact inverse;
  a claimed `restored` basis without a landing does not authorize it. Added
  globals, own members, macros and unknown bases still block the inverse.
- Other callers of `other_declarations` and `meant_by_function` keep their
  existing defaults. No baselines, whitelist, C++ source or naming ledger changed.

## Validation

`tools/tests/test_rename_scoped_members.py`: 46 cases covering inline,
out-of-line and free functions, parameters and locals, known base chains,
unrelated fields left untouched, apply/check/revert, own/base/unknown/dependent
and nested classes (including headers), globals, macros, new-name collisions,
qualified accesses, forged restoration and changed lookup before restoration.

Final tests against the old verifier: **16 failed, 30 passed**. The 16 failures
are the eight newly admitted plans and eight restoration-hazard cases whose
initial plan was falsely rejected. Initial tests also exposed that fixing
admission alone leaves the inverse blocked; the final tests require both.

```
python3 -m pytest tools/tests/test_rename_scoped_members.py \
  tools/tests/test_rename_collisions.py \
  tools/tests/test_rename_class_member.py \
  tools/tests/test_rename_overload_scope.py \
  tools/tests/test_gate_exploits.py \
  tools/tests/test_pin_admission_renames.py -q
```

**293 passed, 1 existing skip**, no deselections. Gate exploit and pin controls
remain rejected as expected. `find_declared_unmatched` reports the real unit's
definitions are all already matched. The native source was not edited, so
this repair claims neither additional byte recovery nor a linking gain.
