# 0x758DE0: recovered by correcting argument ownership

**All 333 bytes match, with zero relocations.** The body now lives in
`Code/Libraries/Source/collisionmanager/collisionmanager_impl.cpp` under the
existing pinned identity `CollisionManagerImpl::bfmeTwoCGD`. The old diagnostic
bank is removed by add_match. This closes the unfinished task.

## Decisive target evidence

The previous bank assigned the two geometry arguments to the inner slot-0C
call and only its result to the outer slot-20/24 call. That was the wrong ABI.
The pushes alone do not establish which nested call consumes them.

Retail Object's interface table is at **VA 0xBFC290 / RVA 0x7FC290**:

| Slot | Target RVA | Independently observed behavior |
| --- | --- | --- |
| 00 / 04 | 28C037 / 28C08D | Bounding-box corners, through Object+70. |
| 0C | 299C78 | `lea eax,[ecx-70h]; ret`: primary Object pointer, no stack arguments. |
| 18 / 1C | 299C7C / 42272 | Setter/getter of the same interface+45C field. |
| 20 | 28C0E3 | Forwards the first argument to Object's geometry test; **RET 12**. |
| 24 | 28E868 | Dispatches object, location and normal to collision modules; **RET 12**. |

`interface.json` retains the ten table entries and selected native bodies;
`native.txt` includes the complete target, getter, test, response and Update
driver. The target ends with RET at 758F2C; three INT3 bytes follow its 333-byte
extent. Update's CALL at 75A4AB independently targets 758DE0.

The table was found by searching for the known setter/getter pair and checking
the bounding-box slots. This discovery alone was only a lead. Existing matched
`ObjectInterfaceSlots.cpp` establishes the table installation at Object+70 by
constructor 298EA9 and destructor 299CE4. The matched
`ObjectGeometryInterfaceRva0028C0E3.cpp` independently records the same table,
the three-argument cleanup, and accepted runtime transfers from this loop.
No new runtime or maintainer-only verification runner was started.

The corrected expression is therefore:

```cpp
first->test(second->primaryObject(), point, normal);
```

The point/normal pushes precede the zero-argument getter, remain on the stack,
and are consumed by the outer callback together with its Object argument.
Changing these three call expressions and declarations in the bank immediately
reproduced the whole retail body. This explains the old scheduling/register
residue without a compiler workaround. The reverse-only fastcall interface,
raw member targets and other signature experiments are unnecessary. Earlier
negative searches of the wrong nested-call ABI do not constrain this source.

## Production integration and uncertainty

The real collision-manager home already defined UpdateSort and its merge-sort
worker. Its opaque +AE10..C068 area now exposes the measured contact buckets,
active list, index at C060 and cursor at C064. The data's existing +04 source
pointer is typed with a TU-local collision interface; the owner and every
other measured offset remain intact. The sibling sweep's stale comments were
corrected to those actual offsets and the now-present provider.

The existing shared `Coord3DCtorView.h` supplies the copy constructor. A small
`CollisionReverseNormal` temporary owns a copied Coord3D and negates its three
components; its conversion keeps the value alive through the outer call.
This ordinary C++ form matches exactly, without binding a temporary to a
non-const reference or introducing a new private Coord3D definition.

The existing method identity is retained. Contact-node field names and the
interface's method spellings describe observed roles, not recovered original
identifiers. Reference parameters are source choices with the proven pointer
ABI; no target evidence distinguishes pointer/reference spelling. No new pin,
global, assembly, pragma or alternate interface is introduced.

## Checks

- Started clean at 118b2a898b; pulled master and passed the initial ledger check
  (98,108 rows). Instructions were unchanged and under 24 hours old. Claimed
  758DE0 before work; read its scoped history and prior handoffs.
- BFME 1 checkout equals verified pointer
  `138757e9b74645fbcbb7724a7af2764e34931e11`. The fresh shared updater lock
  belongs to codex8; skipped the update as instructed, without writing a
  freshness-success stamp. Refreshed the published link-index/object cache.
- The corrected bank and production TU independently emit SHA256
  `a830ee554464c0064933a020cdfe0f488ee4d57104722706c9234324b2833f31`, 333 bytes,
  zero relocations. `checks.json` also records five canonical-type diagnostics:
  the reference helper and both temporary wrappers match; a named local and
  by-value returning helper do not. Only the owning wrapper is used in Code.
- Production keeps its existing `/O2 /G6 /DNDEBUG /MD` settings. add_match ran
  `./build.sh` on the complete home: **3/3 matched, 2,037 bytes**. The sibling
  sweep also passes its full 193-byte gate. No EH handlers/funclets are emitted.
- `find_declared_unmatched` and class_gate pass. Placement rescan finds
  **0 new bodies, 0 pins**. check_csv passes after staging the removed bank:
  **98,109 functions, 15,858 symbols, 2,140 data rows**. Its unstaged-worktree
  check initially encountered the already-deleted bank in git's tracked list;
  staging the intended deletion resolved that input-state issue.
- link_check: the home links **1,704 -> 2,037 bytes** and the sibling sweep
  links 193 bytes. The separate 41-byte Update driver still has its existing
  unresolved `?bfmeGlobalCGD@@YAXXZ` reference (pin 759600, also UpdateSort's
  address). That is a pre-existing caller identity/declaration repair; this
  landing introduces no such reference and does not alter that driver.

`corrected-abi.cpp.txt` isolates the successful signature correction. To repeat
the discovery scan, copy `find_interface.py.txt` to a directory directly under
build/, drop `.txt`, and run it there. It reads retail only and writes scratch
JSON; the selected table still needs the independent evidence above.

There is no remaining mismatch or missing-callee blocker for 758DE0. The
current user request limits this session to this unfinished task, so no next
body is selected.
