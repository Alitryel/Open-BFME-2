# AptString charCodeAt composition prerequisite, 2026-10-25

Seat codexb, Libraries pool. The original ordinary AptString dry run accepted
no donor. The destination's declarations depended on definition order, and
its selected EAStringC and AptString views omitted existing charCodeAt donor
methods. Forward declarations plus those existing method declarations let
the two sources compose without changing either function body or layout.

The donor now includes stdio.h instead of declaring sprintf privately.
Its /D_CRTIMP= keeps the direct retail call: row 0x006D7410, offset +0x6F,
_sprintf to RVA 0x006291B4, classified as an alias of the existing
?ji_006291b4@@YAXXZ owner. No import, pin or alias is added. Byte verification
before and after preserves all three rows, including charCodeAt's 195 bytes
and its handler. EH verification reports two EXACT parents, no missing objects.
Declared-unmatched, data identity and code identity pass (three rows, zero new
identity findings in shadow). The Microsoft-header scan finds zero local
definitions; its owning scoped refresh removes just this donor's sprintf ABI
queue row, preserving all unrelated entries. No identity key is retired.

The final ordinary dry run accepts the seed and charCodeAt donor, three rows,
with /MD /EHsc /D_CRTIMP= and the tool's include paths. Leave this compatible
subset for Luna. Remaining rejected donors have separate boundaries: find's
EAStringC methods; split's nested StringDataC declaration ordering; member
lookup's selected AptString declaration; Common donors' additional string
methods and differing member names. Common donors are outside this seat's
repair pool. Protected-register and mixed donors remain untouched.

Receipts: build/sol-aptstring-{plan,before,after}.txt and
build/sol-apt-char-{before-build,build,freeze,data,eh,headers,identity,queue}.txt.
No merge, row move, file reduction or recovered C++ bytes are claimed.

Publication audit: the two pending mesh/tree prerequisites and this edit have
no source path changes (own outgoing commits from 1cd28a3a88 plus staged
changes, compared against origin/master d7fa8a31bf). Incoming upstream changes
in the two-tip diff are not outgoing moves. Active tools, hooks, workflows,
includes, build inputs and registries require no repointing; historical EA
paths remain intact. Keep the seed/donor/handoff file claims and 0x006D7410
until publication is confirmed, then release them for Luna.
