# Floating-point guard provider blocker

At source base dc7e44f01d, local index19a2565407 selects the constructor
??0Rva0004224C@@QAE@XZ from W3DDisplayGatherAnimationDebuggingInfo.cpp.
That wrapper copy has digest48285ccf61a3 and is proven wrong; copies emitted
by Rva0042CB81.cpp, LivingWorldLogic.cpp and GameLogicInit.cpp have the
retail digestae7c2d5e36a9. Rva0042CB81.cpp's eight rows, 2337 bytes, fail
link prediction because the selected provider is wrong, not because its own
constructor bytes differ. The selected provider file is claimed elsewhere.

One consumer-side trial replaced the direct forceinline guard constructor
with the provider's wrapper expression. The 1005-byte message handler at
0x0042CC7B then placed its empty guard in [ebp-18], rather than retail's dead
message slot [ebp+8], increased its frame by one byte and shifted the call.
The ordinary byte gate refused it. Restore the exact original source rather
than weakening checks or changing the correct consumer to suit the provider.
The restored ordinary byte gate verifies all8/8 rows and five float literals.
The consumer file and class claims were released; no provider claim acquired.

No source change is retained. The future repair belongs in the selected
provider and must verify its consumers together. Full failure output, original
source/object and wrapper trial remain in build/fp-guard-link-20261015.
This is a link-shape trial, not evidence against the already matched body.
