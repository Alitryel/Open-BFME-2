# ScreenMotionBlurFilter setter and EH owner

The native setter at RVA `0x000FDB21` is the public virtual
`ScreenMotionBlurFilter::set(FilterModes)`, returning `int` with a thiscall
`RET4`. It occupies 438 bytes through `0x000FDCD7`.

The independent target evidence is the seven-entry table at RVA `0x007CF410`:

| Slot | Entry RVA | Target RVA | Existing identity |
| --- | --- | --- | --- |
| 0 | 7CF410 | FD4B3 | rowed initialization body |
| 1 | 7CF414 | 910FB | shared shutdown body |
| 2 | 7CF418 | FD4CE | ScreenMotionBlurFilter::preRender |
| 3 | 7CF41C | FD5B7 | ScreenMotionBlurFilter::postRender |
| 4 | 7CF420 | FD4E1 | ScreenMotionBlurFilter::setup |
| 5 | 7CF424 | FDB21 | this setter |
| 6 | 7CF428 | FD551 | shared reset body |

The rowed constructor at `0x000FD58A` installs table VA `0x00BCF410` and
initializes the same 28-byte object layout used by the existing postRender
view. The setter does not access instance fields. The old postRender source
and ledger note incorrectly said `7CF430`; that address is after the table and
contains floating-point constants. Both current descriptions are corrected.

The source guide is Open-BFME-1 revision
`cf0a80c228583af789772b794ab27abcab2debbf`,
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`,
`ScreenMotionBlurFilter::set` at line 1149. The corresponding header explicitly
redeclares the derived setter public, although its base interface setter is
protected. This independently supports the `UAEH` mangling. Its material preset,
opaque shader, two empty textures, render-state application, depth comparison
23/8, depth-write state 14/0 and final application agree with the target. Donor
semantics and access declarations are source evidence; the table, addresses,
boundaries, calls and EH relationships are target evidence.

The native parent prologue selects handler `0x00764045`. The complete 10-byte
handler loads FuncInfo RVA `0x00907EF8` and jumps to `__CxxFrameHandler`. Its
unwind states 2 and 3 select `0x00764035` and `0x0076403D`, respectively. Both
existing eight-byte temporary-texture cleanups uniquely match the new parent's
compiler group (`$L638` and `$L650` at this source revision). Their existing rows
are rehomed, preserving their RVAs and sizes. The previous generic parent alias
and its other class's handler name were insufficient identity evidence; this
table relationship resolves that blocker without an alias or pin.

Normal `explain_mismatch.py` verifies the complete parent and handler. Normal
`add_match.py` replaces the `gen-alias` parent, rehomes both cleanups, admits the
new handler and re-verifies the sibling's corrected provenance. The supported
tool removes the landed `0x00764045` bank. The final prescribed `build.sh` check
passes all nine rows across the new source, the unchanged old owner and the
postRender sibling, including the parent EH graphs, twelve floating-point
literals and all relocations. Existing old-owner rows remain intact.

The new source names the existing shader and render-state globals directly and
uses canonical DX8 helper signatures. It adds no optimization pragma,
alternatename, pin or address-named global. Compiler settings are
`/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc`. Raw scratch diagnostics are under ignored
`build/direct-loop/zh/b4ea340f90/`. No restricted verification runner was used.
The required post-import `place_bodies.py` search reports zero additional bodies
and zero pins. No incidental claim is retained.
