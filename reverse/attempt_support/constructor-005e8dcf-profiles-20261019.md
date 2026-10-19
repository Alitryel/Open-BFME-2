# Constructor 0x005E8DCF: compiler scheduling comparison

At BFME2 `95f0f83963d7246d0dbb84f066914581fa07f7db`, using the committed
BFME1 inputs `a18d9ed50607e9175de4d6568798d7d73119de09`, the existing
`reverse/attempts/0x005e8dcf.cpp` remains the best candidate. It was not changed.

The native boundary is 0x005E8DCF..0x005E8E64 (149 bytes, RET 8). The picker
label `ScriptList::ParseScriptsDataChunk` is unsupported: native construction,
the existing destructor at 0x005E8D71 and the two vtables support the provisional
Rva005E8D71 owner instead. The bank's field-base organization remains a source
inference, not proof of the original class declaration.

Fresh trials used `tools/explain_mismatch.py` and the bank's flags:
`/Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /DNDEBUG /EHsc /MD`.
Default 13.10.3077, authenticated vc71-ddk-4035, and vc71-sp1 all emitted 149
bytes with the same ordering discrepancy. Separate /G6, /G5, /Oi, /Og,
/O2 /Os, /Oy- and /Ob1 trials also retained it. No production source or pin
was changed, and no compiler profile is proposed for landing.

The residual diagnostic at native +0x5D is:

```text
native:   8B CE       mov ecx,esi
          89 46 20    mov [esi+20h],eax
compiled: 89 46 20    mov [esi+20h],eax
          8B CE       mov ecx,esi
```

Earlier attempt-log entries already rule out provider visibility, receiver
spellings, field/base constructor rearrangements and artificial barrier trials.
Do not repeat those or these compiler-profile trials without new evidence.
Resume from the unchanged tracked bank when a genuine source-level scheduling
or class-layout explanation becomes available.

The adjacent existing destructor was separately built and its complete EH graph
verified EXACT. Its own cleanup at 0x007A3FCA is independently recoverable from
that parent; this does not make the blocked constructor exact.
