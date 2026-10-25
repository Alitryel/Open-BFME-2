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


## GameWindowGlobal canonical string context

Prerequisite 2f2ea4eeb3 removes the donor-wide header environment and uses the
registered BFME 2 UnicodeString header, with callable-only declarations for the
two existing GameWindowManager bodies. The rowed names preserve virtual
winMakeColor and nonvirtual winGetTextSize; no complete manager layout or slot
is asserted. Both original rows verify. The old duplicate donor/canonical
AsciiString composition failure is cleared for winFindFont.

The supported merge accepts the existing TU and GameWindowManager_winFindFont:
three matched rows preserved and one fragment removed. The two other approved
addresses remain in mixed Common sources, untouched. Only functions.csv and
current tu_map source columns are repointed; no map regeneration is staged.

Expanded the batch consumer audit to both absorbed paths (RadiusDecal parser
and GameWindowManager_winFindFont), using full paths, basenames and stems across
active tools, hooks, workflows, source/includes, build/configuration files and
registers. Remaining references are historical link_status, retained donor
provenance and generated placeholder comments. No active consumer or protected
register key needs a transfer. Audit output remains in ignored build/ reports;
accepted claims stay held while the runner defers publication.

Fresh destination build verifies 3/3, find_declared_unmatched and check_csv pass.
The pre-commit hook supplies the normal data, identity, ownership, include, EH,
case and byte checks. The fetched upstream may advance independently while the
batch waits; source-path audit concerns the outgoing commits plus staged merge,
not unrelated upstream changes that will be retained by the publisher's rebase.
