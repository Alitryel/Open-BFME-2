# ThreadClass::Switch_Thread C++ getter, 2026-10-24

Target: `?Switch_Thread@ThreadClass@@SAXXZ`, RVA `0x006105C0`, 15 bytes.
The whole owner file contains this row and its force-inline event getter.

Keep that actual C++ getter but replace its assembly EAX load with
`return test_event;`. Under the current unchanged source flags and region
settings, the compiler emits exactly `A1 007CE000; push 1; push eax;
call [0xBBA228]; ret`, the entire native body. The scalar getter preserves
the existing argument-evaluation shape without adding a flag, intrinsic,
volatile access, register constraint or instruction emitter. The old source
comment's claim that assembly was required is superseded by this compile.

Complete emitted extent 15; all bytes and the native event/import operands
match. The ordinary whole-file gate passes 1/1 plus its one named import,
with no skipped references. Declared-definition check passes. Published-index
link preview at `7e43384268` reports LINKS, 15 -> 15 linked bytes.

The file was already counted as C++ coverage, so classification delta is zero;
this removes its last inline-assembly statement with a genuine C++ return.
Private diagnostics: `build/inline-family/pool-base.json`, `pool-link.log`.
Successful code is preserved in the tracked owner unit.
