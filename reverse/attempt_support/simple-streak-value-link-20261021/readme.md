Simple streak render value repair, 2026-10-21

Paired bounded legacy preview: 0 -> 150 matched nonpadding bytes for
Rva001684D6Render.cpp. Both phases refresh the same current, self-strict
SimpleStreakRendererRenderStreak.cpp provider (2/2 rows, 14 float references).
Its recently landed RenderStreak definition was missing from the frozen index;
provider refresh alone leaves the consumer blocked on ShaderClass's competing
copy constructor. The provider's own unrelated blockers remain unchanged.
No closed-strict closure or executable placement gain is claimed.

Get_Shader returns ShaderClass(shader.Get_Bits()) instead of copying shader.
Both operations preserve its complete unsigned ShaderBits value. The temporary
and native parent bytes remain identical, including every relocation. The
losing copy-constructor body disappears. New unsigned-value constructor and
Get_Bits diagnostics have no incoming nondebug relocation or retail address;
retail-truth-2 correctly does not charge them. All other nondebug sections,
flags, definitions and symbolic relocations compare identically in proof.py.

Existing donor/target provenance is retained: BFME1 simplestreak.cpp at
575ba2b04 is a semantic guide; WB A1B020 and A1E840 and target table BD41C8
establish the renderer relationship. No new identity, layout or pin is claimed.
The cause sweep found no other Get_Shader consumer with this sole copy blocker.

Acceptance: ordinary gate 1/1; self-strict consumer and provider 3/3, 14 float
references, no strings/imports; undeclared definitions and new variants clean.
A const-reference return trial removed the native temporary and failed; reverted.
The value-construction form is byte exact. t=8 model=gpt-6.1-sol.
