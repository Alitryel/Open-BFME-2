# SelectionTranslator constructor contracts, 2026-10-20

Continued only the unfinished SelectionTranslator::translateGameMessage at
0x0043003C, claimed before work. Start from the unchanged score0.98 bank.
The preceding helper/handoff.md remains the authority for the now-admitted
free helper and typed bucket initializer. No production source or ledger row
was changed this session.

Fresh isolated parent compilation emits4054B and184 relocations, with zero
structural regions and two operand differences. Every non-relocation byte
except C6B..C6F agrees; extent and switch checks report no problems. The sole
unresolved name is hash_map<int,bool>'s default constructor at43001D/31B.
Its typed hashtable constructor at42FFC0/64B still needs analysis visibility
of its bucket-vector base without emitting the non-retail optimized provider.
The canonical provider remains the55B /Od body at25100. Hidden providers give
65B, using an extra stack byte rather than incoming-argument padding for the
empty allocator. constructor-diff.txt preserves the baseline disassembly.

Prior history already ruled out comparison control-flow/loop-entry changes,
local lifetimes/scopes, scalar and layout variants, callee bodies/inlining,
parent compiler flags, base/member visibility, empty allocator destructor
visibility, exception specifications, ordinary extern-template classes, and
imported base-constructor specializations (VC7.1 C1001). These were not rerun.

Three new hypotheses were concretely tested:

* Class-scope imported explicit instantiations may retain template body analysis
  while suppressing the conflicting provider. Fourteen combinations of extern
  versus ordinary dllimport instantiation and the base/vector/allocator-proxy
  classes were tested. Ten compile but produce59/66B constructors, indirect
  __imp_ calls, or conflicting providers. Four vector imports trigger C1001
  (msc1.cpp2701). None matches64B. These are compiler diagnostics, not false
  verifier rejects. class_import.py reproduces them.
* Empty allocator triviality may permit the hidden constructor's temporary to
  reuse the native argument slot. Twenty-eight combinations remove the generic
  allocator's explicit empty destructor, copy constructor and default constructor
  independently, with hidden base versus hidden vector and /EHsc versus /GX.
  Every constructor remains65B and every initializer59B. These are diagnostic
  header copies only; no altered allocator is proposed for production. The
  /showIncludes receipts confirm each private _alloc.h was actually included.
  An initial run placed its include directive in a second // cl: line, which
  build.py ignores; those invalid controls were discarded and rerun with the
  include on the first directive. Only the28 corrected trials count.
* Alias analysis and inline expansion may restore stack reuse without a visible
  provider. Ninety-six combinations test hidden base/vector, /Oa, /Ow, /Og-,
  /Ob0/1/2, and /EHsc versus /GX. Constructors emit65/75/82/84B, never64B;
  initializers59/66/90/96/133B. No flag combination solves the provider contract.
  alias_flags.py reproduces this family.

The138 new trials comprise134 successful compiles and four compiler crashes.
results.json retains compact outcomes; scripts regenerate private sources,
headers, objects and full per-body relocation reports under build/. No manual
build.compile_source call or shared object-cache write was used. The frozen
input is ../0043003c-20261020-codex7-prereqs/constructor-input.cpp.txt.
Run each script from the repository root. Raw comparison metrics are diagnostic,
not byte acceptance; all constructor candidates fail and none is banked.

Inputs: BFME2 HEAD99b09870df4373dc45484f368af9718085799798; clean BFME1
checkout92f6bbe8e1dcdb46b5d27da0674313efc822b790; MSVC7.1 via Wine with
flags in the frozen input plus each script's explicit controls. AGENTS.md is
unchanged and less than24h from the prior read. Startup pull and check_csv pass.
The live BFME1 update lock still names codex5, so this seat skipped updating as
instructed and did not certify freshness. Published link index144ed0ccab fetched;
no maintainer-only verification runner was started.

The best body is preserved, not replaced by a diagnostic. Release unfinished
43003C/42FFC0/43001D claims on session close. Continue the same concrete task:
resolve the typed constructor provider contract and the parent comparison's
requested-group EAX choice without restoring its premature ESI hoist. Do not
repeat these import/triviality/alias-flag families unchanged. No new missing
retail function is identified, and no padding or escape hatch was added.
