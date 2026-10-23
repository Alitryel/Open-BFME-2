# Camera continuation, 2026-10-21

Active target stays RVA 0x00102F83, 4299 retail bytes. Nothing here is landed.
Claim owner: codex-camera-102f83-20261021-root. Production tree remains unchanged.

## Main causal discoveries

1. `component_merges/readme.md` and proof.json identify actual SSE arithmetic
   ownership: `InitialSplitPoints` calls `SubsumePseudos` at native C2 RVA 0x97082.
   Bank's class-3 load/arithmetic temporary merges into the class-2 target field.
   Paired by-value position arguments instead own the arithmetic first; the later
   copy cannot merge class2 to class2. It is not SubsumeGlobregs or an alias flag.
2. `paired_live/both_xy` makes target X/Y negative-cost memory values. Adding
   `pitch_lifetime/value_vector` makes all four XY components memory and assigns
   sourceZ xmm1 / targetZ xmm0, as retail. Ordinary objects equal read-only traces.
3. Separate `translated(Vector3,const Coord3D&)` calls preserve separate position
   loads, unlike paired arguments. Best complete ordinary candidate so far is
   `translation_lifetime/value_reference.cpp`: 4286 bytes, fitness .9311709691,
   57 relocs. Anonymous by-value aggregate owns arithmetic, but X/Y stores are
   still delayed and Y addressing uses edi+4 rather than retail ebx+50.
4. `distance_order/readme.md`: FactCanonSort determines arithmetic association
   before allocation. Direct field spelling changes struct-piece numbering; it
   does not preserve source term order. `distance_grouping/x_square_group.cpp`
   solves native +A54..ACE exactly (122 contiguous relocation-free bytes), with
   `WWMath::Sqrt(((delta.X*delta.X)+delta.Z*delta.Z)+delta.Y*delta.Y)`.
   Whole body 4295B/.910885657; live-matrix code changes, so retain as a solved
   local mechanism, not simply best overall score.
5. `rotate_y_order/readme.md`: both current Y inlines sort oldX/Z before trig.
   Shaker matches; final should reverse. Current final symbols s/c/oldX/oldZ
   1909/1910/1911/1912. Key = 0x10000|(32*F); a real context crossing F2048 could
   reverse this ordering. No dummy declarations are allowed. Full donor headers
   give 2247/2251/2252/2253 (all after wrap), still wrong. They also change actual
   matrix copy/listener context, not just a uniform symbol count.

## Closed narrow controls on the new allocation baseline

All objects/sources/results are retained under their named directories.

- `pitch_lifetime/scalar`: inert. `delayed_pair`: correct main allocation but
  deferred stores and wrong 1.0 register later. `value_vector`:4283B/.903836.
- `translation_lifetime/value_scalar`:4286B/.916534; reference variant better.
- `component_lifetime`: per-axis returned vectors still differ; pitch_components
  4295B/.931759, translate_components4286B/.923565, both4280B/.925715. Score alone
  hides new hold allocation differences; no exact candidate.
- `pitch_snapshot`: source snapshot4307B/.758319; target snapshot and explicit
  source/out helper both4309B/.844066. No solution.
- `consume_component`: consuming only returned X or Y collapses useful boundary;
  translation4305B/.847067, pitch4284B/.879275. Do not repeat.
- `pitch_grouping`: whole sum and quotient-only parentheses both4307B/.757602.
- `translation_parens`: whole sums and individually parenthesized addends both
  byte+reloc identical to direct translation baseline4291B/.865321.
- `shared_intermediate`: reused scalar/vector translation temporaries worsen
  allocation/scheduling (4304/.846595 and4297/.832807).
- `height_join`: common targetHeight restores semantic join but worsens targetZ
  allocation;4278B/.898532.
- `matrix_donor`: real two-arg const-in/out plus one-arg forwarding mulVector3,
  Row.X/Y/Z/W accesses:4289B/.878441; changes179->265 instructions.
- `matrix_grouping`: explicit first-two-products parentheses on mulVector3 Y/Z
  adds spill/frame0x8C,4306B/.859181; changes179->328. No broader grid.
- `tail_lifetime`: Rotate_X two-term swap fully inert. Explicit ungrouped XZY
  distance emits YZX and worsens. Predicted grouping above solves the distance.
- `full_math/donor`: actual donor matrix3d/vector3/vector4 headers,4261B/.806138.
  Actual include receipt and sizeof checks retained. Its sole unresolved local
  AnimatedTransform ctor is an exact byte+relocation twin of the existing22B
  Matrix3D ctor0x423C5 (`constructor-proof.json`); no pin was added.
- `native_reciprocal`: explicit inversePitch4309B/.842930; old hold delta ctor
  spelling4282B/.914146. Old r60 vs r63 git diff showed these and addXY were
  changed, so do not assume old first508B exactness applies to current bank.
- `row_assignment/donor`: restoring actual Matrix3D row assignment + Vector4
  field assignment gives4306B/.906200. It FIXES the early +2AD zoom operand order,
  leaves first matrix main region mostly stable, worsens live matrix, and changes
  finalY mismatch32->30. Reference seat tracing keys.

`compare_current.py` writes normalized .diff.txt and .asm.txt for explicit
scratch objects. It masks call/jump targets and global addresses for diagnosis;
these normalized comparisons are never final byte verification.

## Admission preparation

Existing caller pin is `?rva00102F83@Rva00102F83Owner@@QAEXPAVRva0010274F@@@Z`.
Current scratch symbol changes both owner and context struct/class spelling.
Read-only `rename.py class --name Rva00102F83Owner --new W3DCamTransform
--basis canonical:wb --evidence '...0x00102B83...' --dry-run` refused because
name_evidence has no wb-assert candidate for this owner. No edits occurred.
Do not call this a conclusive repo blocker yet: docs/naming.md:285 allows
otherwise-unexpressible canonical hand renames with strict evidence, pin/caller
updates, tombstones and re_log, leaving name_basis alone. The tool additionally
refuses class-name merges into existing names. Resolve actual class evidence and
preserve the existing neutral descriptor class Rva0010274F if necessary.
There is no authorization issue and no need to ask the user for permission.

Canonical Coord3D lengthSqr declaration and ICoord2D integration remain necessary
only once there is a valuable production candidate. No shared header edits yet.

