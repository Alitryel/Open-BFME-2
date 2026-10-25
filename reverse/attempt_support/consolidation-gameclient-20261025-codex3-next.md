# GameClient consolidation follow-up, 2026-10-25, codex3

Scope: `Code/GameEngine/Source/GameClient/`. Continued the preserved two-commit
batch from the previous session without discarding its changes or initial
untracked generated assembly and reverse/zh_sweep inputs. Read current AGENTS.md
and consolidation workflow, pulled/rebased, and passed check_csv. The BFME 1
freshness receipt (2026-10-24 04:42 UTC) is under 72 hours old.

## RadiusDecal parser

Prerequisite 93c3230942 supplies the parser fragment's existing static declaration
to the destination class view, with an INI forward declaration. No fields,
compiler flags, hatches or body statements change. All six original rows and
three float literals freshly verify. The supported dry run now accepts the
parser; the prior missing-member composition failure is cleared for this donor.

The claimed merge accepts RadiusDecal.cpp and RadiusDecalParseTemplate.cpp:
seven rows preserved, one source removed. Fresh ./build.sh verifies 7/7;
find_declared_unmatched and check_csv pass. The map diff is a single source-column
repoint, not a map regeneration. Mixed donors remain intact. The GameLogic
update/xfer donors still lack a baseline match at this destination, clear needs
its destructor declaration, and setOpacity needs a compatible shadow view.
Those unchanged blockers were not repaired or relabelled as coverage regressions.

## Publication audit

Fetched origin/master=ce5e16cd06. Reviewed origin/master..HEAD (preserved
LoadScreen prerequisite and handoff plus 93c3230942) together with the staged
RadiusDecal merge. The complete pending path move is
RadiusDecalParseTemplate.cpp -> RadiusDecal.cpp. Searched its full path, basename
and stem across tools, hooks, workflows, Code/includes, docs, reverse registers
and root build/configuration files. Remaining mentions are historical link_status
and generated provenance/placeholder comments. No active hard-coded consumer,
include or protected-register key needs repair. Source ledgers are repointed;
the fresh destination receipt is used. Local audit output:
build/gameclient-session2-path-audit.txt.

Accepted file/RVA claims remain held until confirmed publication. Rejected donor
claims are released separately. Publication runs only with the commit through
/opt/runner/publish; a deferred batch remains the runner's responsibility.
