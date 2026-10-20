# 0x43003C SelectionTranslator::translateGameMessage - session 2026-10-19 22:46-22:53 PT (hans-agent-oct5)
Bank: 4048 vs 4054 B, struct 4, mem 106 (mostly relocation noise), reg 3. Real differing instructions 92/90, but almost all are relocation noise. There are two real regions:
- A (+0x439): retail loads containedBy into EAX and the template into ECX, then `mov esi,eax; mov ecx,esi` before getDrawable. Ours preferences containedBy into ECX (`mov esi,ecx`, no copy), 2 bytes short.
  Inert: direct reinterpret field, a draw=(obj=c)->getDrawable() chain, a local copy, a const pointer, `!= NULL`/`== 0` spellings, the ternary null check.
  Worse: a separate template local.
- B (+0xC5C, case 72-81 select-team double-tap): ours hoists `group` ([ebp-0x10]) into ESI above the `now - m_lastGroupSelTime` test (it's used on both paths).
  Retail reloads it into EAX for `group == m_lastGroupSelGroup` / push, and again into ESI in the else arm after the deselect calls.
  This looks like retail treated `group` as aliased (no hoist across calls). Inert: const/cast/split declarations. Worse: swapped or reordered && operands.
