# Link setup: lazy import thunks after retail groups

model=gpt-6 lane=R budget=30m. The completed authoritative ab0e4d81fe snapshot exposes an actual placement prerequisite: appended import CODE objects enlarge .text by 0x165C, shift .text$x/.text$yc, and align the six newly ordered teardown functions +0x1660 away from retail. None of those six is quarantined; their existing closure failures are independent. A narrow bound-map extract is in ../txn-section-20261024/import-section-drift.txt. The 62 already closed transaction initializers need this prerequisite after their separately committed native .text$yc repair.

The second snapshot 685c82bb60629d763d296185554a294f38d063a8 was deliberately stopped before its native links; actual process exit 241 after 1094 seconds. No completed receipt or earned credit is claimed for it. Its remaining compiler children finished before subsequent native probes. This avoids repeating an already evidenced section-offset problem.

Reference review at BFME1 32774ab03393709a7f14331ba8d98d281a55ffd9 found the same short-import/code-section setup without a relocation repair to inherit. A private /LINK50COMPAT probe was refused as an unknown option by lib.exe 7.10.3077; no production fallback uses it. An independent private native probe instead linked without /FORCE after retaining the same DATA IAT imports and moving their FF25/DIR32 callable stubs into .text$zz.

The separate tools change uses that mechanism in link preparation only. It reads original runtime libraries, preserves each short import's DLL/name mode/hint, changes CODE imports to DATA in private copies, and rebuilds their archive indexes using the original librarian. Each unowned callable thunk is a separate lazy archive member in .text$zz; original source-owned callable definitions are retained. The archive precedes IAT-only libraries so callable lookup never relies on stale CODE indexes. An unused runtime import stays unselected. No original runtime library or ledger input is modified.

The existing COFF writer gains optional named relocations for these generated stubs. The source-recovery and closure rules, byte equality, data checks, address mapping, shift checks and credit formula are unchanged. The actual measurement binds the changed tool digest. This repair does not certify any helper or credit its generated thunks.

Regression checks cover COFF COMDAT and DIR32 encoding, native source-owned import compatibility, unowned stdcall import identity, oldnames CRT aliases, no forced duplicate linking, preservation of the first constructor-group address, unchanged original library hashes, and lazy exclusion of wscanf. All gate exploit regression tests remain enabled; the one empty optional fixture parameter is reported separately. Full actual credit remains pending the repaired immutable measurement.

Tool implementation and scoped regression elapsed: 7.9 minutes; the complete measurement is separate verification time.

## Final full verification

The repaired immutable 5c98b266eefeb20ef18e4fee427d671c4c320ec8 cycle is authoritative, actual exit 0, zero missing/failed objects and final drift 0. Native placement is restored for all 62 transaction initializers and six teardown wrappers. Unique closed-and-placed credit rises by 233,839 bytes (1,435,102 -> 1,668,941), with 2,105 newly credited rows and none lost. Exactly one canonical object changes (the initializer's native section); all other 23,459 canonical objects and the three ledger receipt inputs agree. No byte, data, relocation, closure or shift admission rule was relaxed. The complete receipt, input reconstruction and controlled comparison live in ../txn-section-20261024/.
