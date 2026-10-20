# GeometryInfo contact selector: control-flow and coordinate-copy evidence

Target `GeometryInfo::getBestContactPoint`, RVA `0x006BEF80`, has a complete
1082-byte extent ending after `RET 0x18` at `0x006BF3B7`. The inventory's 1079
omits that return. WB `0x006F91B0`, its Geometry.cpp diagnostic string and the
native six-argument caller establish the identity independently of matching.
The picker served a stale Pathfinder name; that proposed identity was rejected.

The full bank and current `GeometryInfoCollidesWith.cpp` owner were read. ZH
Geometry.cpp supplies the distance-helper pattern and shape enums, not the
BFME2 contact-list behavior. Native accesses establish contact stride 16 at
+0x38/+0x3C, shape stride 36 at +0x2C/+0x30, and positions +0x44/+0x50.

The new bank retains the whole owner. Native-supported changes are ordinary
Coord3D assignment instead of a scalar copy helper, nested caller/search-success
conditions with one final false return, separate label-call arms, an else-if
final height clamp, and a POD local for the selected nearest contact. The
preferred-position path calls the height getter a second time on clamping, as
native does; the old bank cached it. The interpolation path retains the cached
height and copy-constructed locals established by previous work.

With identical current inputs the old bank emits 1023 bytes; the new bank emits
1080. The diagnostic SequenceMatcher ratio rises from 0.647981 to 0.738205;
this is not exactness, not an instruction-aligned score, and not comparable to
scores recorded by earlier seats. `compile_function` patches DIR32 slots from
same-offset target data for diagnostics, even while code differs; those slots
must not be interpreted as resolved data identities or meaningful operands.
All REL32 calls resolve. The existing CollidesWith sibling still verifies all
821 bytes exactly from the bank.

Remaining: frame 0x18 versus native 0x1C (first difference +7), native best-index
stack slot versus compiler register allocation, logging/caller argument homes,
and some interpolation/distance x87 scheduling. Native first reads seed into
EDI and caller into ECX; the bank holds caller and preference in saved registers.
The origin at VA 0x00E0C140 still needs a real data owner; the probe at E0C150
uses the existing g_Va00E0C150 owner. No production source, global, pin or ledger
row was changed, and no +C++ exact progress is claimed for this bank.

Ruled out in this pass: free/member copy helper forceinline/dllimport annotations;
return-by-reference copy; distance helper, square template, reversed sum or
coordinate temporary; alternate empty ctor and local lifetimes; positive
label/collision nesting; and visible/hidden CollidesWith plus a visible verified
height-getter implementation. These are unchanged or worse than the bank.
RTM, SP1 and DDK4035 agree on the 1081-byte intermediate; /G5 and /Ob1 agree too.
/G7 regresses; /Op creates a different size-exact but much worse body. A
size-exact body is not proof. Do not repeat these families without new evidence.

Inputs: BFME2 d8961f14c218725a3dc0890fe1dcc313d533d469, verified BFME1
f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. Flags remain /O2 /Ob2 /G6 /DNDEBUG
/MD /EHs-c- with the bank's existing ASCII and Lib include paths. Copy the bank
to a unique build/ path, then run tools/explain_mismatch.py with the exact
decorated symbol, --rva 0x006BEF80 --size 1082 and --source that path.
The included old source, baseline/final diagnostics, sibling check and trial
results preserve the comparison; the trial driver records all tested shapes.

## Round r2 (2026-10-19, opus-5.5): element pointer closes the frame

Retail keeps `&contactsBegin[i]` in EDI across the case-0 loop body (label
compare `this`=EDI+0xC, position copy from [EDI]); that extra live value is
what spills `best` to the native stack local [esp+0x10] and widens the frame
to 0x1C, with `i` homed in the preference slot and `bestDistance` in the seed
slot. Assigning `const GeometryContactRecord *c=&contactsBegin[i]` in each
label arm (then `pos=c->position`) reproduces the 0x1C frame, the arg homes
and EDI/ESI roles. In case 3 a pointer `p=&contactsBegin[index]` with
`first=p[0]`, `second=p[1]` removes one more region. SequenceMatcher (same
trials.py method) 0.738205 -> 0.893420; structural regions 28 -> 11; register
diffs 44 -> 16; 1076 B vs 1082 (first diff +176).

Remaining: (1) native computes the element pointer separately in each label
arm (`mov edx|eax,[esi+0x38]; lea edi,[ebx+reg]`), ours head-merges it above
the `test label` (6 bytes). Unchanged by: one ref before the if, pointer per
arm via &a[i] / a+i / byte arithmetic, `!label` arm order, ternary call,
nested continues, pos copy inside each arm, pointer declared at case scope or
initialised before the loop. (2) case 3 keeps begin in EBP and copies it
(`mov eax,ebp`), ours holds begin in ECX and count-1 in EBP; a begin local
does not change it. (3) final `add eax,ecx` order in the found copy.

- r2 follow-up: inline accessor `contactAt(i)` / `contactData()+i` / reference-bound local per arm: still 11 regions, head-merge unchanged (disproven).

## Round r3 (2026-10-19, claude-opus-5-5): no gain, 11 regions kept

Disproven on top of the r2 bank (regions/bytes): compare arg ternary `c->label.compare(label?label:"")`
26/1079, same without c 25/1072; arms without c plus `pos=contactsBegin[i].position` 16/1066; result int
`r` set in each arm then `if(r)continue` 25/1080 (with per-arm c: 13/1076). Case 3: direct
`contactsBegin[index]`/`[index+1]` 12, `p=contactsBegin;p+=index` 11 (same regs), `p=&begin[seed%(count-1)]`
with `++p` 14, `count>1` 12. Ours also hoists `lea ecx,[edi+0xc]` above the label test (retail sinks it
to the join after the per-arm push), so the whole arm head is merged, not just the pointer.

## Round r4 (2026-10-20, claude-opus-5-5): 0.8934 -> 0.9420, banked

Lever: a vector view with inline accessors in place of a raw begin pointer:

    struct GeometryContactVector {
     GeometryContactRecord *_M_start,*_M_finish,*_M_end_of_storage;
     const GeometryContactRecord *begin() const {return _M_start;}
     const GeometryContactRecord *end() const {return _M_finish;}
     unsigned int size() const {return (unsigned int)(end()-begin());}
     const GeometryContactRecord &operator[](unsigned int n) const {return *(begin()+n);}
    };

Case 3 written as `contacts[index].position` / `contacts[index+1].position`
(index = `seed%(count-1)`, count = `(int)contacts.size()`) is now exact except
for one `fmul`/`mov edx,[eax+0x18]` swap at 0x6bf091; begin is held in EBP as
retail. The case-0 distance spelled `dz*dz+(dx*dx+dy*dy)` gives retail's x87
order (fld st(1); fmul st(2); fld st(3); fmul st(4); faddp; fld st(1); fmul
st(2); faddp). Bytes (trials.py SequenceMatcher) 0.942049, permute fitness
0.9545, 1075 B vs 1082. Bank: `reverse/attempts/0x006bef80.cpp`.
CollidesWith (same file, 821 B) stays exact.

WorldBuilder twin (va 0x6f91b0, Geometry.cpp, `tools/wb_show.py`) evidence:
Coord3D scale/add/sub/GetLengthSqrd are out of line there; case 0 pushes
`label` or `""` through a branch (two pushes, `lea ecx,[eax+ebp+0xc]` at the
join) with no element pointer, and the position copy groups its three loads
after reloading `[esi+0x38]`. Game retail instead computes the element pointer
in each arm (`mov edx|eax,[esi+0x38]; lea edi,[ebx+reg]`) and keeps it in EDI.

Residue on the bank: (1) the per-arm element pointer is head-merged above the
label test (`mov edi,[esi+0x38]; ...; add edi,ebx; test; lea ecx,[edi+0xc]`),
7 bytes; (2) the position copy interleaves load/store where retail groups the
three loads; (3) `best=i` uses EAX, retail EDX; (4) the case-3 swap above.

Disproven on the vector view (bytes, all <= bank): case-3 spellings via a
pointer `p`, `begin()+index`, `p+=index`, `++p`, `n+begin`, `_M_start[n]`;
other distance orders and a Coord3D difference struct; mixed per-arm
spellings, assignment inside the call, comma operator, function-scope `c`,
dropping `!= 0`, `label!=0`; ContactPoint `pos`; position copy per field,
by assignment, via contactCopy, as float locals (worse), via getters by
value/pointer/reference; ternary-argument forms T1-T4 (lose EBX strength
reduction); `int r` per arm; ternary of assignments; no element pointer (0.80);
reference bound before the if (0.858); element pointer through
`i*16+(int)_M_start`, `_M_start+i*16`, `&_M_start[i]`, `begin()+i*sizeof`,
mixed arms (all identical to the bank, 0.942049). `tools/permute.py --flags`
was inert in r2.

A real STLport `std::vector<GeometryContactRecord>` (`/D_STLP_USE_STATIC_LIB
/D_CRTIMP=`, stdio fprintf) is worse: 0.857671, 1092 B (the control without the
vector stays 0.942049). `tools/permute.py 0x006BEF80 --minutes 30 --jobs 6` from
this bank: 1147 trials, start = best 0.9545, stopped with no gain in 600.

Untried: the case-0 arm head as an inline member with a body that returns the
element (e.g. `const GeometryContactRecord *matching(i,label)`), declared in a
shared header; an out-of-line Coord3D::sub/GetLengthSqrd like the WB twin
(game retail inlines case 3's scale/add, so this applies to case 0 only).
