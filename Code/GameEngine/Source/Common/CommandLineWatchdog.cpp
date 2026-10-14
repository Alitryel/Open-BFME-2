// cl: /DNDEBUG /MD
// BFME1 T3CommandLineParsers global-flag parser family, adapted using
// BFME2's live command table. -Watchdog at81FBA8 identifies3B94CD (9B).
// Names follow the live token; the global name is descriptive, VA E02D79.
extern bool BFME2WatchdogEnabled;
// BFME2WatchdogEnabled: matched references place it at VA 0xe02d79 (zero-filled .bss).
bool BFME2WatchdogEnabled;
int parseWatchdog(char *args[],int num) {
    BFME2WatchdogEnabled=true;
    return 1;
}

// -noWatchdog at81FBB0 identifies3B94F1 (11B), clearing the same global.
int parseNoWatchdog(char *args[],int num) {
    BFME2WatchdogEnabled=false;
    return 1;
}

// 3B9516 (11B), another handler of this family (not referenced from the live
// table): clears BfmeFormationPreviewUseDecals (VA DC84F4, defined in
// Rva0029B1C2.cpp, retail initial value 1; 3B9400 is its setter). Name
// address-derived; option string unknown.
extern bool BfmeFormationPreviewUseDecals;
int Rva003B9516(char *args[],int num) {
    BfmeFormationPreviewUseDecals=false;
    return 1;
}

// 3B9400 (10B): the setter of the same BfmeFormationPreviewUseDecals byte.
void Rva003B9400Set(bool enabled) {
    BfmeFormationPreviewUseDecals=enabled;
}
