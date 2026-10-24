# Restore the native five-argument copy provider

Retail dispatcher 002B4410 is a complete 29-byte function. It pushes null
_distance, an address for the empty random-access category, then destination,
end and begin; it calls 002B442D and removes all 20 argument bytes. Native
002B442D is a complete 47-byte forward loop, advances four bytes per element,
and calls the existing 002B2F97 holder assignment. That body retains the
reference through the established +AC/+B0 representation.

The old row declared the worker as a three-pointer free function. Its bytes
were exact because the last two arguments are unused, but it did not define
the five-argument name emitted by the callers. A pin let those callers pass
the byte gate while leaving their external name undefined in the link.

The worker now declares its complete native cdecl interface, retaining the
same identifier, class views, source, address, extent, loop and assignment.
This is an ABI correction, not a newly inferred function or class name. The
ledger's old signature spelling is tombstoned and its successor owns the same
47 bytes once. No extra recovery is claimed. No external callers of the retired
three-argument spelling were found.

Two existing caller units use an ordinary TU-local forced-inline overload.
It preserves all five arguments and calls the real provider through its actual
typed interface. Only data pointers cross the existing opaque four-byte view;
no function-pointer call cast, new pin or public adapter symbol is introduced.
The original application element identity remains unknown. The compiled
29-byte dispatcher is unchanged except for its relocation's corrected name.
Each emitted local adapter copy has static COFF storage, a discardable COMDAT
and zero code or data references. Its absent-from-retail annotation records
that unused compiler copy. The already-matched single-erase function's stale
present-unmatched annotation is removed.

STLport 4.5.3 vendor/stlport/stl/_algobase.h:136 supplies the five-argument
random-access dispatch interface and forward-copy semantics. This donor fact
is separate from the target's independent complete caller, stride and callee
proof. The current BFME 1 0bf534ea import/provider repairs were reviewed; they
supply no direct repair for this target-specific neutral holder view.

## Verification and measured effect

- Normal three-source gate: 62/62 existing rows, literals/floats/imports green.
- Existing strict preparation: all five explicit providers current and byte
  verified, 66 rows including the unchanged assignment and ArmySummary consumer.
- EH: the cohort's one exception-data row is EXACT, no baseline use or missing
  object. Frozen-file checks pass.
- The dependency scan checks 23,435 objects and adds the unchanged ArmySummary
  consumer to verification. Its explicit copy instantiation is a definition;
  its matched GetEntries body remains exact without the removed pin. This unit
  is absent from the census and is not included in a linking-gain claim.
- Fresh isolated builds of all four baseline sources reproduce all 89 original
  emitted code bodies and relocations. Production compiler settings stay fixed.
  The isolated five-argument trial uses those original settings too.
- Normal repaired objects and their strict currency receipts reproduce the
  same-index paired prediction below. Both normal and isolated trials agree.

| Existing unit | Before | After |
| --- | ---: | ---: |
| Rva002B442DCopy | 47 | 47 |
| Rva002B6066Erase | 0 | 86 |
| StlportVectorEraseRangeDeferred | 0 | 2464 |
| Rva002B2FF4Swap | 147 | 147 |
| Total nonpadding matched bytes | 194 | 2744 |

Net **2550 existing C++ bytes predicted linkable**, zero newly recovered C++
bytes. This is a paired current-provider result, not a fresh census, a closed
strict dependency result or a placed executable. No maintainer-only runner
was started. The undefined template pin at 002B442D is removed, and its keyed
pin allowance falls from one to zero. No verification allowance grows.
