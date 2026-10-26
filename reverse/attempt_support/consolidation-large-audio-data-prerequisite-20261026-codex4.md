# LargeGroupAudioUpdate data prerequisite, 2026-10-26, codex4

Allocated family A shard 1/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupAudioUpdate.cpp`.
The current in-memory TU plan approves 26 rows, nine donor files and seven
mixed files. No map, source, declaration, flag or path is changed here.

The data baseline retained the old `g_00DFE1A8`/Rva0020DXXX pointer key at
0x009FE1A8 in LargeGroupAudioUpdate004AB90A.cpp. That source already declares
the real `LargeGroupAudio *TheLargeGroupAudio` and casts its use to the existing
view. Current data_check finds zero findings. The owning path
`python3 tools/repair_queue.py retire data
Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupAudioUpdate004AB90A.cpp`
passes and retires exactly one key, with zero remaining for this source.
This accounts for already-fixed identity before a later source move; it does
not fix or retire the separate pool-key debt.

Scoped evidence under `build/codex4-largeaudio-data-*`:

- `./build.sh` verifies the 152-byte body 1/1, including all literal checks;
  find_declared_unmatched passes. allowed_symbols reports four owner references
  and zero wrong bindings. Converged data checks ten protected addresses with
  zero second names and zero unjudged rows. EH verification reports zero
  applicable rows and zero missing objects.
- Before/after object snapshots compare equal. They retain the rowed body
  fingerprint ae42ac100067 and its COMDAT selection, the two existing non-COMDAT
  inline definitions Inv20 and GameLogic::getFrame, and the same six external
  references. Data references remain TheLargeGroupAudio at 10477992 and
  TheGameLogic at 10479500. No provider, consumer or selected definition is
  changed by this register-only retirement.
- The normal current-map trial is recorded separately; no composition gain,
  merge, file reduction or later Luna landing is claimed by this retirement.
  The scoped Update planner encountered a transient RiderChangeContain trial
  source disappearing and refused its scan. Do not reuse that planner snapshot;
  regenerate it after active trials finish before applying a merge.

The complete pending publication batch has no moved or deleted sources. Its
two inherited private headers still have their four verified consumers. This
retirement adds no include or build input and changes no path consumer, header
queue, identity register, hatch or compiler flag. Historical EA paths remain
intact. The earlier pending-batch tooling compatibility audit therefore still
applies; the new baseline delta is exactly this owning-tool deletion.

Additional allocated investigations: AutoFindHealingUpdate's destination claim
was refused because another worker holds it; no edit or trial was started.
ExperienceScalarUpgrade's pool-key baseline names an old generated function,
but current data_check still finds two wrong-name keys at 0x00A03EB0 and
0x00A03EAC. `repair_queue.py retire data` correctly refuses those new findings;
no key was removed. Its source/RVA claims were released and the blocker is
recorded in re_attempts.log. Reconcile actual data identity before retrying.

Measurements: one additional data key retired, zero code-identity keys retired,
zero files removed and zero recovered C++ bytes. Together with the separate
GameAudio retirement, this session removes two data-debt keys. Claims for this
destination, donor, evidence file and RVA 0x004AB90A remain held until confirmed
publication. The runner's final handoff lists the inherited pending claims too.
