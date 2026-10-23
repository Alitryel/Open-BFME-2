// cl: /G7 /MD /EHsc /DNDEBUG
//
// BFME2 CritterDesync logging gate, VA 0x00E03744 (RVA 0x00A03744, .data).
// Twenty-six retail sites compare this zero-initialized byte and, when set,
// call fprintf(g_00DFEFF0, "CritterDesync: ...") -- the AI animal-state
// updates at 0x0047EE26..0x0047F8E3 ("animal %s is doing periodic search",
// "dice roll failed", "finished update", ...) and CastleBehavior::
// onTriggerEntered at 0x00396C43. BFME1 owns the same-role flag at VA
// 0x012F0239 (26 converged references; data row source
// S3CritterDesyncCountdown.cpp at game/GameEngine/Source/Common, dir32 alias
// _bfmeRetailCritterDesyncFlag): its five ComputePath desync counters read
// that byte the same way. No EA identifier is recovered in either image, so
// this is a neutral descriptive name, not an assertion of the original
// spelling. The adjacent 0x00E03745 byte is a second CritterDesync gate
// (already owned in AIUpdateInterfaceIgnoreObstacle.cpp), so the two are
// declared separately rather than as one array.
bool g_bfmeCritterDesyncLog = false;
