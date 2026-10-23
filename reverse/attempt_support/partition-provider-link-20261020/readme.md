# PartitionManager provider binding remains blocked

At c51892d061, legacy preview against census 144ed0ccab reports 0/2499 bytes
linked for `partitionmanager_impl.cpp`. The private pair<int,int> vector
assignment differs from its retail provider 0x00627CC0. Query growth touches
non-retail selected FlightDeckInfo allocation/fill/overflow definitions.

The adjacent patch declares the existing assignment and 0x00627BC0 growth
providers. One careful byte trial fails two of nine rows:

- SetTreeDepth (266B) switches the receiver from EBP to EBX, reloads the
  temporary's start pointer after assignment, and changes the loop layout.
- GetClosestObject (1830B) changes the seed record's homes (native +0x70,
  trial +0x58) and first-level loop allocation. The remaining seven rows match.

These are compiler knowledge/lifetime differences when removing visible
callee bodies, not unresolved retail addresses. No declaration was retained.
The original source was restored and all nine rows reverified. Existing
native algorithm and donor provenance remain in the source; no new type
identity is asserted. Resume with a way to preserve callee analysis while
binding the canonical definitions, or a target-supported provider repair.
Do not repeat the unchanged declaration-only trial.
