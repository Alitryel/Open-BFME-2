# RenderObj destructor settings, 2026-10-22

Rva001684D6Ctor (99 current bytes), Copy (129) and Dtor (81) all remain
0 legacy linked bytes. Their RenderObj destructor copy is 60 bytes and uses
__EH_prolog; rowed RenderObjCopy.cpp owns the retail 79-byte inline-EH body at
0x13be20. Dtor additionally emits a conflicting unowned Rva001683A7 destructor.

Trials (no source retained):
- Changing the cl line from /O1 to /O2 is inert: flag_defaults chooses /O1
  for these units by majority matched RVA region. Do not repeat this as a
  compiler experiment without checking compiler_command.
- /EHsc -> /EHs keeps all 4/4 rows exact but leaves the same 60-byte copy.
- Explicit /Oy also keeps 4/4 exact and leaves the same blocker.

No verified linked gain, so every source restored and 4/4 gate rerun. A real
repair needs canonical destructor visibility or evidence-backed codegen
reconciliation; no pragma, shim copy, override or pin added. Header-wide edits
were not attempted for these small units. Inputs BFME2 66c176bd18, BFME1 verified
37c3022de1ab944c7ffe536440d637dc8199091c, census 08160bc2c9. Their original source
and flags are in git at that revision; this handoff records all tested deltas.
