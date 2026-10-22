# FVF vector overflow ownership, 2026-10-22

Before: current-object legacy link_check reports 0/1715 bytes. The unit emits a
non-retail ICoord2D uninitialized-copy helper and the kept overflow definition
is also non-retail. The rowed overflow provider is MapUtil.cpp at 0x181770.

Two bounded trials failed the caller byte gate:
- Declaration-only explicit specialization of _M_insert_overflow adds writes to
  the dummy false-type argument and changes register allocation throughout the
  1705-byte parent.
- extern-template suppression retains the header definition but produces the
  same caller mismatch. The exact declaration is preserved in trial.patch.

Original source restored and reverified. No ownership suppression or pin was
landed. Next work must preserve MSVC 7.1 interprocedural empty-type analysis while
selecting the retail overflow/copy provider, or reconcile the element identity
and provider in a separately evidenced change. Existing canonical ICoord2D
storage is a layout stand-in for eight-byte D3D vertex elements, not a newly
established semantic identity.

Inputs: BFME2 HEAD 66c176bd18; verified BFME1 37c3022de1ab944c7ffe536440d637dc8199091c;
census 08160bc2c9. Source flags unchanged (/O2 /G7 /EHs /Ob2 /arch:SSE /Op,
STLport malloc/no-exceptions).
