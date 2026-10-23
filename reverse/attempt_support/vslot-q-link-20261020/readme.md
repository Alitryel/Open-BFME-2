# VslotSmallBodiesQ link repair handoff

Current legacy link check is 0/263 nonpadding bytes: four undefined globals,
three message key pointers and the lookup table at native VA DD8320.
No C++ or ledger change survives this attempt, and no link gain is claimed.

Retail proves DD8280 -> CE315C (complete `errorCode`), DD8288 -> CE313C
(complete `decodedSize`), DD8310 -> BED340 (complete `ID`). The last address
already has a data-ledger owner, `g_bfmeWhatBKG` in BfmeConv482.cpp. The trial
uses that owner rather than defining a second global. Both new pointer data
rows passed the ordinary byte gate, and the eight remaining function rows
still matched after moving the lookup out. The source patch preserves this
useful preparation, but the new data rows were reverted with the trial.

The native DD8320 lookup table points to larger protocol objects (including
E0A3E0, E0A434, E0A50C, E0A3EC); its full object providers remain unresolved.
Do not manufacture pointers or partial objects merely to satisfy the link.
The supported repair pattern was to isolate its unchanged 57-byte lookup,
allowing the other 206 nonpadding bytes to link.

Blocker: identical lookup C++ in the new TU does not emit the original body.
Target starts `8b442404 8b501c 83faff 7505 33c0 c20400 a12083dd00`;
the split emits `... 83faff 7423 a1...`, sharing the zero-return epilogue
instead of retaining the native early return. Loop alignment also differs.
First trial retained the original source comment `/DNDEBUG /MD`; the second
explicitly supplied the original effective `/O2 /arch:SSE /DNDEBUG /MD`.
Both failed the normal add_match gate, which automatically restored the row.
The original effective flags and source are preserved in build/vslot-q-link;
the exact split candidate is banked here as table-lookup.cpp.txt. This was a
placement/compilation repair, not a new function reconstruction or identity
claim. No unsupported pragma, alternate identity or row extent was introduced.

Investigate why the original TU keeps separate returns before retrying a split,
or recover the full table and native object providers so the original TU can
link intact. The first two key definitions alone free no bytes and were reverted.
Baseline source restoration is checked with ./build.sh. Published census used:
144ed0ccab; BFME 1 donor 4483e88da1 was not a source for this target-data repair.
