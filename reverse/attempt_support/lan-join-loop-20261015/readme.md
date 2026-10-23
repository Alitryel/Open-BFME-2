# LAN join serial-loop frontier

Base cab7de80b0, retained BFME1 inputs f76203cb023f923b97cd8687679ea29ef121d875.
Target: LANAPI::handleRequestJoin at 0x0058277C, 1,844 bytes through 0x00582EB0.
The existing LANAPI::update row and its jump-table dispatch establish the caller
and target. The Zero Hour GeneralsMD LANAPIhandlers.cpp supplies the serial/name
validation structure; BFME2 packet offsets, address handling, and CRC additions
remain target-derived facts from the previous bank, not donor layout claims.

No exact match was found. No production source, pin or matched row changed.
The previous bank contained an uninitialized read of player in an equal-arm
conditional selecting GameToJoin.iniCRC. That is not a legal recovery technique.
The bank now uses GameToJoin.iniCRC directly and removes stacked stale score
headers. The clean body compiles to 1,841 bytes with all calls resolved;
variant_search.fitness reports 0.9613670988700406. The old invalid body compiles
to 1,844 bytes and scores 0.9793776763737313; its size is not proof of a match.

The clean body's serial scan rotates retail's top cmp/jge and unconditional
back edge into a bottom cmp/jl. Restoring the Zero Hour canJoin-first condition
restores the top test, but keeps constant 5 in EBX across the later name scan,
spilling its slot pointer and changing stack allocation (1,849 bytes).

62 isolated compiles covered both baselines; serial/name/both inline scan
helpers with reference/value counters; typed inline message setters; explicit
continue/increment labels; equivalent loop predicates and counter scopes;
inline serial predicates; LANGameSlot/const pointer types and byte flag types.
The helper, setter and type families were inert. No trial improved on the
known legal frontier. The measured compile experiment took approximately five
minutes; the bounded search was stopped under AGENTS.md's failed-shape rule.

results.json records the individual measurements. Scores use the existing
variant_search metric, not a percentage of verified bytes or a probability of
landing. nd counts positional byte differences; code shifts and DIR32 masking
make it unsuitable as an instruction-difference count. Exact size alone is
never accepted. No EH, full-byte-gate, or linked-byte gain is claimed.

Scratch sources, objects, disassembly and the four trial drivers are retained
under build/lanjoin-20261015. They use build.try_compile_source with explicit
private object paths and compile_function for scoring; the shared match cache
was not used for exploratory compiles. Existing bank history remains in Git.
