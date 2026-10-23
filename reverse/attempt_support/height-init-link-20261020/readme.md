Terrain height initialization link handoff, 2026-10-20

Original self-strict7/7, frozen e7a7769fe5 legacy0/1101 nonpadding B.
Three blockers: inline BoundedShortGrid getter62A58 loses against its
38B /Oy owner; pointer-set default ctor loses; unresolved detailOpaqueShader.
Existing terrain-extents-link-20261013 handoff read before attempting.

Target fact: RVA6DAE8 bytes A14041DB00 load a DWORD at VA DB4140 into
[ebx+3814]. Retail RVA9B4140 starts1B58510000000000. A trial unsigned
4B detailOpaqueShader=0x0051581B plus a data row passed Data rows1/1
byte+sizeof verification. Shader role/name is carried from HeightMap/ZH,
not independently proven as the original target identifier. Nothing else
owns that data address in the current ledger. This ownership trial is
reverted with the source because no whole-unit gain was achieved.

Trial1 set ctor declaration plus import-forceinline visible getter inlines
the native getter call into the parent, frame28->38, parent and EH actions
fail. Trial2 plain getter declaration plus set declaration keeps the call,
but loses native callee visibility: frame28->2C and X-extent is spilled
rather than reread after the call. Parent and unwind byte verification fail.
No new pin or unwind workaround justified. Both diagnostic zero-context
patches retained. Original source/data ledger restored after two failed gates.

Remaining prerequisite: preserve the getter's native call-site optimizer
knowledge while keeping its /Oy owner rather than this /Oy- COMDAT. A new
optimization pragma would be hatch growth and was not attempted. Set ctor
and shader storage alone cannot free the unit. BFME1 review unchanged
4483e88da1c2; target source is existing BFME2 recovery with ZH role lead.
No source/ledger/verifier change retained. t=8min model=gpt-6.1-sol.
