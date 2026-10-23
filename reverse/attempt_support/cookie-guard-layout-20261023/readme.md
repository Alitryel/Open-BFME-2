# Cookie guard layout: new block-fact and exception-boundary controls

Target @__security_check_cookie@4, RVA 0x00629BAB, whole 14-byte body.
Read the October 18 contract, October 22 layout trials and October 23
compiler-profile handoffs before testing. Existing assembly remains exact.
New inputs: BFME2 8dbeb84c3c; reference pin 96c88c73a5; normal MSVC7.1.

Seventeen new source controls tested legitimate optimizer facts on the good
and bad arms, an explicit good label with a proven equality assumption,
a boolean domain fact, unreachable continuation after a declared-noreturn
failure, force-inlined guards, and empty SEH finally boundaries. Both normal
and noreturn failure declarations were checked where semantically valid.
No contradictory assumption was used on a reachable path.

Every ordinary guard is still exactly 14 bytes but has JE/JMP/RET rather
than retail JNE/RET/JMP. SEH variants are 85, 87 or 116 bytes, not 14-byte
matches. Full object extents were checked in addition to the bounded scorer.
No Code, ledger ownership, pin, gate or assembly body changed. Existing bank
was not replaced. results.json and representative sources preserve the trials.

This closes these new block-fact/inlining/SEH hypotheses. The SDK's explicit
assembly entry remains justified by its EAX/EDX preservation contract. A
future attempt needs a new backend explanation, not another flag or guard
spelling scan. No exact C++ recovery or new bytes are claimed.
