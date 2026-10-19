# Camera-derived destructor handler

Native parent 0x0007C454 is the existing 75-byte CameraClass-derived destructor
in Rva007C454Dtor.cpp. Its complete source and prior parent/handler attempts
were read before work; body, handler and file reservations were pushed first.
The existing class name remains address-derived; no new original-name claim is
made. No game source, compiler flag, pin, alias or class contract changes.

The parent installs handler RVA 0x0075F2F9. Its complete exact EH relocation
graph binds FuncInfo 0x00901D20 and the cleanup call to the existing CameraClass
destructor at 0x00133A00. The emitted natural handler is exactly ten bytes,
including its FuncInfo pointer and runtime jump to 0x00629182. The proof compares
all ten relocated bytes, using the parent graph and existing runtime binding.
Both cleanup/runtime bindings agree with existing owners. Source/object hashes
and strict dependency currency are in handler-proof.json; callee-audit.json
records both external targets.

Normal build.sh verifies both parent and handler. find_declared_unmatched passes;
place_bodies over the complete source finds zero further bodies and zero pins.
The ordinary compiler lifetime emits the handler: no assembly, dead throw or
volatile barrier is introduced. This adds ten unique strict C++ bytes only;
the existing parent was already counted. No incremental linked-byte or runtime
claim is made. No maintained verification runner was started.

Inputs: origin/master af5db01a38b60e7352497e9f01e32c504e7fe053;
verified BFME 1 pointer 6b9d92bf92debd03e4357462bab41f701651e67c.
Model gpt-6.1-sol; about five minutes including shared publication cooldown.
