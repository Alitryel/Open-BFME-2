# AIRingHeroTactic::update: compiler context trial

Target: `?update@AIRingHeroTactic@@UAEXXZ`, RVA `0x005ACBFF`, complete
229-byte boundary `0x005ACBFF..0x005ACCE4` (RET). Identity and receiver layout
are carried from the existing bank and its vtable evidence: AIRingHeroTactic
table `0x008723E8`, slot 7. This trial establishes no new original names or
layout facts.

Inputs: BFME 2 `9bc9d37e48e9dfea48691889f89f50b7c2bc62a5`, official BFME 1
pointer `a18d9ed50607e9175de4d6568798d7d73119de09`. Existing candidate
`reverse/attempts/0x005acbff.cpp` was copied to scratch and remains unchanged.
Its intended home is `Code/GameEngine/Source/Common/Rva005AC7E1Tactic.cpp`.
The home has no undeclared definitions and was not edited.

## Hypothesis and measurements

Tested whether authentic compiler versions or the actual direct-callee bodies
visible in the translation unit change MSVC's saved-register placement or the
end-call scheduling. Scratch builds used `/O1 /G7 /arch:SSE /MD /GX /DNDEBUG`
and the existing bfme2_ascii shim. Explicit scratch flags avoid generic
`build/` defaults; the real source's flags were not changed.

- RTM, hash-pinned DDK 4035 and SP1 all emit the same 229-byte body.
- Canonical GameLogic lookup header plus its actual 37-byte findObjectByID
  definition, plain/inline/noinline and before/after update, is unchanged.
  This confirms the earlier visibility verdict rather than supplying a new
  lever.
- Actual aiMoveToObject parameter-block construction, alone or with the
  equivalent command-0x17 rva0026C347 body, before/after update, is unchanged.
  The command interface's real virtual slot 0 was included in the scratch view.
- Actual AITactic::end control flow, plain/noinline and before/after update,
  is unchanged. Its accessed base layout was reconstructed from the existing
  provider in scratch: prototype/team vectors, ended flag, owner, target and
  coordinate members. This diagnostic view was never proposed as a shared
  class definition or a new provider match.
- Default arguments, return-void expression, qualified base call, inline
  member wrapper, inline default wrapper and constant member-function pointer
  all preserve the same body. Inline range begin/end accessors also preserve
  it. Caching the range end changes register allocation and regresses strongly.
- `/Os /G7 /arch:SSE` reproduces the same baseline. No existing bank was
  overwritten with a differently scored equivalent.

Every baseline call resolves; the COFF function section has exactly 229 bytes.
Current scorer fitness is 0.96230, not the historical bank's 0.985. The scorer
copies retail DIR32 bytes at compiled relocation offsets; the one-byte
save-placement shift therefore makes its first global operand look corrupt
in a naive disassembly. `inspection.txt` restores the two already-ledgered
global values at their actual COFF sites for readable diagnostics only. It is
not alternate verification and makes no matching claim.

## Remaining mismatch and handoff

Retail saves EDI between the running test and its branch, saves EBX only after
that branch, and restores EBX/EDI in the corresponding order. The compiler
saves both after the branch. At the end call, retail moves ESI into ECX between
the two argument pushes, while the candidate does so after both pushes.
See `inspection.txt` for the exact instruction diff and relocation list.

No new provider-context hypothesis remains supported by this trial. A future
attempt needs evidence for a different compiler IL/lifetime shape; repeating
the tested visibility or wrapper forms is unlikely to help. The best existing
candidate remains the bank above. No pins, source, function rows or matched
bytes were added. Approximate active effort: 8 minutes, model gpt-6, lane R,
budget 30m.
