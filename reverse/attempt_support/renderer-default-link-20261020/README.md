Renderer matrix emitter repair, 2026-10-20

At parent 4e6029b1bd the reset unit has 1195 nonpadding matched bytes but loses
its Matrix4 default constructor to the first copy in link order. This name has
no proven retail address. Reuse the complete verified BFME1 matrix4.h at
4483e88da1c2f3b9a273f779baac7458bd8bb891 as a scoped header with only this
empty constructor marked imported forceinline. No type identity, layout,
algorithm or retail pin is changed; proof.py checks the donor difference.

The unwanted 22-byte constructor and its no-op BFME2World dynamic initializer
and .CRT registration disappear. The old constructor merely iterates four
empty Vector4 constructors, each MOV EAX,ECX; RET. Its initializer was only
MOV ECX,BFME2World; JMP constructor. proof.py checks their exact bytes,
relocations and the registration before omitting them from comparison. Every
retained nondebug section, definition, flag and relocation is identical.
BFME2World stays the same 64-byte Matrix4 global with its verified zero data.
No DLL-import call is emitted. This repair also removes unnecessary startup
work rather than adding another callable constructor name.

Normal verification passes all six code rows, one data row, eleven floats and
imports; EH remains EXACT and converged-data and declared definitions pass.
Strict current provider preparation passes. Paired frozen-index legacy
prediction: 0 -> 1195 linked nonpadding bytes. Closed-strict is unmeasured;
no census/full link cycle was run. proof.json records index and object hashes.
Keep build/renderer-default-link/before.obj, or rebuild parent source with its
original include in an isolated trial, to rerun the proof.

Current previews of the other four units with this constructor conflict still
have independent blockers: texproject/decalsys lack Projector providers;
StreakRendererSetTextureBFME1 has duplicate render bodies and native ABI/helper
conflicts; W3DWaterDrawOceanWater has HAnim cleanup and transform conflicts.
None gains linked bytes from suppressing this constructor alone, so they keep
their existing headers. The bridge classifier ranked nearby already LINKS
2431 B in the current checkout; no stale-census repair was attempted there.
