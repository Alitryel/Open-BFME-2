# AIPlayer::queueSupplyTruck: exact C++ recovery

RVA **0x004F37B0..0x004F3DB1**, 1,537 bytes. The normal compiler and relocated
byte comparator reproduce the complete body, with no unresolved relocations.
The normal EH verifier also reports `EXACT`, including all five associated
cleanup funclets. This is source reconstruction, with no assembly, object-byte
patching, compiler-decision patching, or fabricated diagnostic operations.

Source: `Code/GameEngine/Source/GameLogic/AI/AIPlayerQueueSupplyTruck.cpp`.
The previous bank was `reverse/attempts/0x004f37b0.cpp`, last improved by
`39984ac88c`. Read the preceding handoffs, particularly `af0a96e14e`'s
`queue-supply-truck-20261023d`, before interpreting the controls below.

## What closed it

1. `/Ow`, in addition to the bank's VC7.1 `/O1 /Ob1 /G7 /arch:SSE /Oy-`
   configuration, keeps the base-filter vtable in ESI with its sole load inside
   the repeated build-list header. It also restores the first ESI/EDI iterator
   pair. It does this without the two dummy globals used by the previous
   diagnostic. This is a tested compiler adaptation, not proof of retail's
   original command line.
2. Express the later object walks with an explicit Object cursor. In the
   recount, an equivalent same-arm cursor selection and a compiler barrier
   after the KindOf test preserve the native ESI object / EDI supply-center
   allocation and shared EDX zero. The loose-harvester walk has its own barrier
   on the existing non-null object arm. These are code-generation adaptations;
   the branches do not introduce additional game behavior.
3. Keep the initial total-harvester count in a forced-inline member helper.
   In this context it restores the later native cash-multiply sequence as well
   as the initial count. Inlining context can affect distant allocation and
   instruction selection; a source spelling that previously failed may work
   after that context changes.
4. Use a guarded do loop for the recount's prototype list. Its initial guard
   reads Player's proven list sentinel at +0x32C directly. The back edge still
   reads `m_player->getPlayerTeams()->end()` afresh after callbacks. Keeping an
   initial end value across the entire walk would lose that native behavior.
5. Barriers preserve the queue-field stores before the frame-counter read and
   the player/flag load order on both ordinary build-flag restoration paths.
   The string is destroyed before restoration. There is deliberately no
   exception-time restoration absent from retail; a restore-on-unwind guard
   would change its behavior and EH graph.
6. **Remove the earlier phase-storage union after fixing those other choices.**
   The six-byte near miss had exactly the native 450 instructions, registers,
   calls, extent and EH, but exchanged two stack homes. Ordinary independent
   locals let stock C2 choose every native stack home. The earlier sharing
   workaround had become the final obstacle.

The exact result retains the native 45-call sequence, temporary filter
destruction on both search outcomes, fresh iterator/end and field reads across
callbacks, and both ordinary flag restores. Numerical plausibility was not used
as a substitute for byte or EH verification.

## Useful controls and limits

- The six-byte control used a local union for desired count, source pointer,
  filter-constructor return and factory pointer. Its raw body SHA-256 is
  `3641fdf2fea61d9d5158cd651708d3a96a5ea1217ffbd5195cdb0c69de16f6ab`.
  Only offsets +0x28D, +0x2EA, +0x2FB, +0x33B, +0x354 and +0x59B differed after
  normal relocation resolution: the -0x14 and -0x24 stack displacements.
- A read-only C2 trace confirmed that control's phase union and recount
  iterator shared -0x14, while recount AI and a later argument temporary
  shared -0x24. It observed the normal compiler's stack groups and assignments;
  the traced body and relocations equaled an ordinary compile. No allocation
  decision was changed. A union additionally sharing recount AI got eight
  differences, including a wrong string home and a failing EH cleanup.
- Removing all phase-sharing members produced the exact body. Keeping only
  the desired-count member or only the source-pointer member did too; sharing
  both did not. Re-evaluate interacting workarounds rather than treating a
  locally helpful earlier change as permanently necessary.
- Renaming locals, moving ordinary declarations, scalar integer spellings,
  equivalent inline helper interfaces, and most additional flag switches did
  not resolve the six-byte control. Volatile counters and multi-field records
  introduced other differences. These controls do not rule out every possible
  use of those techniques in another context.
- Applying `/Ow` to the existing AIPlayerTeamBuild translation unit changes
  other recovered bodies. The recovery therefore has its own unit and reuses
  the canonical `WorkOrder.h` and `TeamInQueue.h`; existing units keep their
  compiler settings and source.

## Inputs and reproduction

Donor behavior: Zero Hour's `AIPlayer::queueSupplyTruck` in the vendored
GeneralsMD `GameEngine/Source/GameLogic/AI/AIPlayer.cpp`. BFME2 layouts, call
targets, filter-chain lifetime and additional tests come from the retail body
and prior packets. The WorldBuilder center-coordinate cleanup correction in
`queue-supply-truck-20261023-resumed` remains applicable.

Compiler: stock Microsoft C/C++ 13.10.3077, from committed BFME1 reference
`f5140c1cff6a58e16276fd6de6788186286953d4`. Publication preparation used BFME2
`4a9f14eefa`; the exact scratch experiment preceded that pull and was rechecked
with its current inputs. Commands and hashes are in `verification.json`.

On Windows, use the installed interpreter directly:

```powershell
$py = 'C:\Users\vvval\AppData\Local\Programs\Python\Python313\python.exe'
& $py tools/build.py Code/GameEngine/Source/GameLogic/AI/AIPlayerQueueSupplyTruck.cpp
& $py tools/eh_verify.py Code/GameEngine/Source/GameLogic/AI/AIPlayerQueueSupplyTruck.cpp
```

`verification.json` records private-object verification through the same
`build.compile_function` and `eh_verify.verify_row` paths. The normal `add_match`
build also passed before publication. Cleanup locations are evidence from the
parent graph, not five additional newly recovered byte claims in this change.

## Dependent EH handler

With the parent recovered, its compiler-emitted
`__ehhandler$?queueSupplyTruck@AIPlayer@@IAEXXZ` is now rowed at
**0x00792E4C..0x00792E56 (10 bytes)** in the same source. The parent's EH
prologue explicitly installs this address; `Image.frame_funcinfo(0x004F37B0)`
returns handler 0x00792E4C and FuncInfo RVA 0x009457DC. The handler loads
FuncInfo VA 0x00D457DC and jumps to `__CxxFrameHandler` at RVA 0x00629182.
The normal relocated byte gate verifies both parent and handler. No new source
body, assembly implementation or adjacency-based identity inference is needed.
