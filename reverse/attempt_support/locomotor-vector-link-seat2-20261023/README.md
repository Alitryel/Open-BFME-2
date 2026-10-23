# LocomotorSet real pointer-vector link repair (Seat2, 2026-10-23)

## Scope and provenance

Only production edit: `Code/GameEngine/Source/GameLogic/Object/LocomotorSet_addLocomotor_Rva001E88CE.cpp`.
Existing `LocomotorSet::addLocomotor`, RVA `0x001E88CE`, remains its full 92-byte
body; no new coverage is claimed. The undefined `LocomotorPtrVector` facade is
replaced with the actual STLport `_STL::vector<Locomotor *>` member. No casts,
provider aliases, artificial wrappers, shared headers, provider edits, or markers
were added. Four genuine typed instantiations are admitted by the normal fold
proof tool; these are not four independently recovered retail bodies.

BFME2 baseline: `b8ba69a0ba159fcac887fe58744e3d619296fda8`.
Verified donor used locally: `138757e9b74645fbcbb7724a7af2764e34931e11`.
Parent must reverify against its newer donor `96c88c73`; this seat did not update
the submodule. Semantic reference: donor
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/LocomotorSet.h`
(`LocomotorVector` member, typedef `vector<Locomotor *>`) and corresponding
`Source/GameLogic/Object/Locomotor.cpp`, `LocomotorSet::addLocomotor` at line 2777.
This establishes donor type/role, not independent BFME2 naming or layout proof.
BFME2 retail establishes the 12-byte vector at +4, surfaces at +0x10, the native
allocation/copy/free chain and four-byte elements. Existing getter identities,
pass-through Bool, downhill flag, and unknown template +0x150 -> set +0x15 flag
are preserved. The latter flag's payload meaning remains unknown.

## Evidence-backed trials

All trials used own OrbStack env/cache/prefix, pool1 and objstore off, via normal
`./build.sh`. No global build, census, link_cycle or manual compiler was run.

1. Real typed STLport vector: parent92/push49 nonrelocation bytes agreed; growth
   134B versus native140B exposed stock allocation semantics.
2. Add `/Ireference/shims/bfmealloc`: real C2950 allocator<char> explicit
   specialization/template-export diagnostic; this did not produce a successful
   new object.
3. Add `/D_STLP_USE_STATIC_LIB`: parent92, push49, allocator28, fill32 agree;
   growth141 differs from native140 by imported `FF15 __imp__free` versus native
   direct `E8 _free`.
4. Add `/D_CRTIMP=`: every byte and every relocated operand of all five bodies
   agrees, including native direct `_free`. No EH flags changed.

Final explicit flags: `/MD /DNDEBUG /Ireference/shims/bfmealloc
/D_STLP_USE_STATIC_LIB /D_CRTIMP=`, plus normal `// stlport` dependency selection.
Normal inspect_command/compiler_command mapping confirmed seat-local compiler,
source, include/header paths and INCLUDE/LIB/WINEPATH before compilation. No
implicit CL/_CL_ flags, response files, fallback runtime, or consumer forced
include. Final consumer object SHA256:
`7738dfae02d91a379d73c2f998e1689fe626645a5ae1572eb85a3ad10156b366`.

## Full bodies, relocations, EH and native callees

`recursive-proof.json` preserves complete emitted/native byte strings and each
relocation's exact resolved operand. Its original diagnostic candidate mapping
is explicitly labeled; the subsequent normal admissions independently established
all four fold grants against every eligible existing owner row.

| RVA | Size | Genuine emitted body | Relocations |
| --- | ---: | --- | --- |
| 00068E15 | 28 | allocator<Locomotor *>::allocate | +0F REL32 byte allocator 000307F0 |
| 0007E48F | 32 | fill_n<Locomotor **, unsigned int, Locomotor *> | none |
| 002DFCF6 | 140 | vector<Locomotor *>::_M_insert_overflow | +2C allocator, +3A/+5E copy, +46 fill, +70 free |
| 004DFCB0 | 49 | vector<Locomotor *>::push_back | +29 REL32 growth 002DFCF6 |
| 001E88CE | 92 | LocomotorSet::addLocomotor | +0F DIR32 global, +14 newLocomotor, +29 push |

Exact typed mangled names are retained in `recursive-proof.json` and the four
normal admission logs in `verification.txt`. Other native identities touched by
the emitted call chain:

- `?allocate@?$allocator@D@_STL@@SAPADIPBX@Z`, RVA `0x000307F0` (native game allocation).
- `?__copy_trivial@_STL@@YAPAXPBX0PAX@Z`, RVA `0x000179B0` (two non-inline copy calls).
- `_free`, RVA `0x00030830` (native game free, not imported CRT free).
- `?newLocomotor@LocomotorStore@@QAEPAVLocomotor@@PBVLocomotorTemplate@@_N@Z`, RVA `0x001E4A81`.
- `TheLocomotorStore`, RVA `0x009FDC5C`, VA `0x00DFDC5C` (existing canonical global).

`eh-graphs.json`: all five function sections have empty associated EH graphs;
no CxxFrameHandler/EH_prolog/unwindfunclet symbols. Normal EH verifier: zero EH
rows, zero nonexact and zero missing objects. This is not a claim of untested EH
placements. Consumer strict `--prepare-current` succeeded with 1/1 full body,
all literal/float/import refs exact (zero present), strict reusable current
receipt. Frozen/class and pin consistency checks pass.

## Official admission and scope

Normal bottom-up `tools/pin_admission.py --add` admitted allocator, fill, growth,
then push, each with `fold-proof=<consumer source>`. Their complete owner-byte
and relocation checks succeeded. No manual ledger/pin/receipt edits. The normal
`add_match.py --replace-existing` then verified the existing consumer and wrote
its notes plus landed log. The pre-existing 827 ungranted other pin addresses
were reported by the admission tool and were not repaired or regranted.

`owner-scope.json` lists the exact 15 owner TUs / 30 owner rows admitted for
proof, plus three external native provider TUs. These 18 plus consumer were the
approved production verification footprint. Before proof their owner caches were
absent; normal admissions compiled them, without copying or linking cache files.
Full read-only command mapping is saved locally in
`build/seat2-locomotor-owner-command-mapping.json`; its concise summary is in
`verification.txt`. ModuleFactory's unchanged `/FIzh_ascii.h` was explicitly
approved after the parent corrected/validated the ignored guest mapping wrapper.
Its 74 include directories and native forced-include search target were checked:
`reference/shims/bfme2_ascii_zh/zh_ascii.h`; quoted `ascii_string.h` resolves first
in `reference/shims/bfme2_ascii`. Wrapper SHA256 at validation:
`2593693806e098a4ba25f4fe8528a6cd4cfd36b4660f4a3434a748c557ccd51c`.
No wrapper/runtime/donor edits were made by this work.

Normal admission globally rewrote unrelated hatch grants. Those unrelated edits
were surgically restored byte-for-byte from the pre-admission snapshot. Final
hatch diff contains only the four tool-admitted count changes 58->59, 6->7,
30->31, 57->58 at the four fold RVAs, with the tool's final symbols.csv hash.
This records genuine ICF allowances, not a verifier relaxation.

## Supported paired preview and limitations

Exact command and complete output are in `verification.txt`. The normal explicit
8-TU preview used this seat's historical census `2026-10-23 06:28`, commit
`456ce161c5`; it did not refresh globally, mutate the index or claim complete
current-ledger closure. Consumer: **LINKS, LINKED 0 -> 92 bytes**. Six of eight
explicit units link; aggregate 416 -> 508 linked bytes in this snapshot.
Command exit1 is retained, not relabeled success: unchanged ModuleFactory still
has GrantScienceUpgrade buildFieldParse unresolved, ModuleData/UpgradeModuleData
COMDAT debt and BridgeTowerBehavior selected-copy debt. Unchanged narrow-string
provider retains three unrelated string COMDAT/selected-copy blockers. Other
explicit owners/providers remain linked at their prior byte counts. These old
index provider-TU debts are not consumer byte/relocation failures and were not
hidden or edited. Parent must check the consumer against its newer published
index and donor before publication. No current global closure claim is made.

No new retail coverage: the measured gain is only this snapshot's existing92B
consumer becoming linkable. Claims remain held for parent publication.

Staged normal plan before commit: `tools/name_dependents.py --staged` exit0,
empty output (zero lost-name dependent expansion); `tools/delta_sources.py
--staged` exit0 lists only the claimed LocomotorSet consumer. All four pins are
additive. All-owner fold validation is the separate approved 15-owner footprint,
not hidden name-dependent expansion. Pin consistency: six pre-existing
multi-pinned names of 15,808, zero baselined/new/stale violations.
