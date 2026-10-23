# AutoDeposit parser provider repair

Base: 7bb1b74b (master after selection). Published census: 2026-10-17 02:26
at fb06805bf5. Stale local provider definitions were refreshed in memory;
no census status, verifier, flags, pin, header or function row was changed.

ModuleFactory.cpp's compiler-only emission anchor took the Zero Hour
AutoDepositUpdate::friend_newModuleData address. That instantiated its ZH
buildFieldParse plus a five-field table (DepositTiming, DepositAmount,
InitialCaptureBonus, ActualMoney, UpgradedBoost). It was selected ahead of
the independently byte-verified BFME2 parser in ModuleDataBuildFieldParse.cpp,
which registers the native table at 0x00BF1CC8. The registered BFME2 factory
is already implemented by AutoDepositUpdateModuleDataFriendNew.cpp; the
compiler anchor is not the retail module registry.

The anchor only needs AutoDepositUpdateModuleData's 28-byte deleting
destructor row at 0x0025528B. Construct that type directly instead of taking
the ZH factory address. This preserves its constructor/vtable/destructor
emission without pulling in the foreign parser or factory.

Paired comparison substituted the saved original and repaired objects at
the same position in one refreshed index. Nine COMDATs disappear; none are
added. Of 1,017 retained COMDATs, only the explicitly non-retail compiler
anchor changes. No strong name is added or removed, and a consumer scan
finds no other users of the names losing their last definition.

ModuleDataBuildFieldParse.cpp loses its only COMDAT conflict and now links:
0 -> 1,477 nonpadding bytes across its existing function rows. ModuleFactory
still has independent blockers; its unresolved count falls 7 -> 6, while
its other finding counts stay unchanged. The broader two-file preview exits
nonzero because those pre-existing factory blockers remain. This is a local
published-census prediction, not a full executable/runtime link test.

Validation: 139/139 provider/consumer function rows byte-exact; EH 24/24
EXACT, no baselines or missing objects. Placement rescan: zero new bodies or
pins. comparison.json preserves the paired findings. Full scratch logs and
original provider object are in ignored build/local-macos/next-batch/.

BFME1 revision 5bb8ca80 was reviewed. Its recent global-owner corrections
(7a1a968b) and unwanted inline-provider suppression (2566e00d) establish
repair patterns only; the actual conflicting copies, native table address,
retained deleting-destructor row and byte proof above are BFME2 evidence.
