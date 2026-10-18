# Guard inner-state exit linkage

The refreshed current-object prediction left only `AIGuardInnerState::onExit(StateExitType)` unresolved in AIGuardStates.cpp. The published index still reported a second State::update blocker that current providers already resolve. Retaliate states also already link with current providers and are not claimed as new progress.

Target identity comes from the existing named tables: inner state VA C69780 slot 5 and attack-aggressor C69890 slot 5 both hold VA 942C87 (RVA 542C87). The corresponding slot-2 getters and separately verified constructors identify these tables. The complete 76-byte native body calls the attack sub-state exit, performs global deletion, clears state+3C and resets the owner team target. It is the existing attack-aggressor physical owner.

The semantic guide is Zero Hour AIGuard.cpp lines 459-479 at verified reference revision 64d369b90170b7e9ec917d646f020b11f13eb0d5. BFME 2 has no enter-state branch in this body. The existing BFME 2 sibling supplies the proven global-delete behavior and team offset, rather than copying Zero Hour allocation behavior. The real inner-state method compiles independently to the same full body and all relocations. Its folded row has no new pin, alias directive or unique-byte credit.

proof.json records the current-provider before/after linker prediction and raw-byte/relocation-site comparison of existing methods, with independent EXACT parent EH verification. This is a scoped linker prediction, not a full-game executable or runtime test.

The Unicode conditional-result cleanup receipts independently bind compiler-local labels to native addresses using the existing parent function’s EXACT EH graph. These are existing C++ result lifetimes; no synthetic emitters or new pins are added. Each standalone MASM row is retired only after full-byte and canonical destructor-call verification.
