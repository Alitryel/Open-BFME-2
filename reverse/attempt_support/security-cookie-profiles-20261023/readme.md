# Security-cookie compiler lowering controls

Inputs: BFME2 6b48d28f03, verified BFME1 pin
42bba2ddbd5cb895d99293583891d3b7315fa49e, native Debian x86 QEMU/Wine
compiler runner. The normal hash-pinned RTM, DDK4035 and SP1 profiles are
selected through tools/compiler_profiles.py; headers are unchanged.

The full retail boundary is 0x00629BAB..0x00629BB9, 14 bytes. The entry ABI
is ECX cookie, with EAX/EDX preserved. Previous evidence is in
../security-check-contract-20261018/ and ../local-vm-probes-20261022/.

Eighteen new profile/optimization controls and three C-front-end controls
all fail. Every optimized RTM/DDK/SP1 /O1,/O2,/G5,/G7 body is the same
14-byte CMP/JE/JMP/RET, whereas retail is CMP/JNE/RET/JMP. /Og- adds an
EBP frame and produces 27 or 29 bytes. Full COFF extents were inspected;
these larger bodies are not 14-byte matches. C /TC with /O1,/O2,/G7 also
reproduces the original branch order. No Code, pin, ABI or verifier change
was made. The existing ASM remains the owner; no weaker bank is substituted.

The result rules out a supported compiler-version, CPU-tuning, global-
optimizer or C-versus-C++ front-end explanation for the existing residue.
The replay drivers and all results are retained here. Future work needs a
new backend/control-flow explanation, not another profile retry.

Reference freshness: upstream advanced to 19d28f2b, with no changed
header/toolchain files, but file:reference/open-bfme-1 is held by
yasinschroeder-codex3. The last verified inputs were preserved; no successful
freshness timestamp or submodule update is claimed by this attempt.
