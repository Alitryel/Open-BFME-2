# Mutable pair construction at 0x00523DD4

Target identity comes from the actual owner. Native
AptOverButtonHandlerAdder::AddOverButtonHandler at 0x00524845 passes the result
of factory 0x0023FC23 directly to the vector at this+0x0C through
push_back 0x0052480E. Its fast path calls Construct 0x00523DD4; growth 0x005244DC
and copy/fill 0x00523E01/0x00523E27 reach the same construction helper.
The paired WorldBuilder function0x013CD4D0 names the class and source, and its
assertion at AptCallbackAdders.cpp:183 explicitly uses
`std::find(m_overButtons2.begin(), m_overButtons2.end(), std::make_pair(levelIndex, buttonName))`.
Thus std::pair is target evidence rather than a name inferred from matching bytes.

Native erase 0x00523EC8 copies survivors through 0x00288A5C -> 0x0048C897 ->
assignment 0x0028876F. The assignment writes the first dword at 0x0028877B,
then assigns the string at+4 through canonical StringBase 0x000366F0.
This proves first-word mutability and excludes the const key of a map value.
The eight-byte element and owned narrow string are independently established
by that path and copy 0x000CF475 -> StringBase copy 0x000365F0.

The source consistently uses the existing producer's `pair<int, AsciiString>`
view. Exact signedness is a retained source convention/structural inference,
not a recovered original signature: these operations copy or compare for
equality. AptPlayer's separate level API uses unsigned bounds in WB; that
does not establish the adder's formal parameter type. No primitive spelling
was changed to evade a spent name. Neither this mutable-pair Construct name
nor its copy-constructor name has another row or pin address. The already
owned const-int and const-unsigned map-value types remain separate.

The isolated whole-source trial preserves the owning unit's effective
O1/G7/SSE, Ob2, EHsc and MD settings and canonical ASCII/STLport headers.
All 37 existing rows remain strict exact with identical resolved byte hashes,
extents and EH verdicts. The genuine pair copy is 29 bytes, exactly the
existing 0x000CF475 body including its sole+19 relocation to0x000365F0.
Its name needs ordinary fold-proof admission, not another row at CF475.
The null-guarded placement parent is 45 bytes at 0x00523DD4.

The parent prologue names handler 0x00796630. That 10-byte handler names
FuncInfo 0x0094A02C; its single-state unwind map 0x0094A024 selects the 14-byte
cleanup 0x00796622. The complete parent/EH relocation graph is EXACT without
placement conflicts, independently placing natural local label $L3955.
The cleanup is already owned; new genuine C++ coverage is the 10-byte handler.
The original TreeKey parent 0x000A7876 and handler 0x00760AB8 remain intact.

All four consumer sources retain their complete 38/37/55/178-byte bodies.
The vector/layout views remain; the fill worker has its genuine pair template
identity. Their construction calls now name the genuine external pair Construct
directly; the two vector units suppress duplicate Construct emission with
extern-template declarations. The obsolete void duplicate declarations,
function-pointer casts and two corresponding alternatename pragmas are removed.
No compatibility alias, optimization pragma, synthetic class, raw-byte body,
compiler-label adjustment or verifier change is introduced.

Inputs: BFME1 stays at cf0a80c228583af789772b794ab27abcab2debbf.
Detailed ignored receipts are under
`build/direct-loop/zh/b5004c8a12/mutable-pair/`: whole-source-proof.json,
consumer-proof.json and consumer-inputs.json, with WB listings one level up.
They record source/object hashes, effective flags, every old/new row verdict,
and each new copy/parent/cleanup/handler relocation and native destination.
Independent review confirmed the pair/mutability evidence and the stated
signedness limitation before integration.

Production verification: build.sh passes all 42 rows across the five affected
units; all 23 EH graphs are EXACT. Declaration and canonical-class checks
pass, and pin consistency is clean. The scoped link preview links all five
units using the published census index (8eecc93d07); the new handler adds
10 bytes to the current source coverage. The required placement rescan finds
zero further bodies or pins. The hatch register retires exactly the two
alternatename entries, the old object-symbol row and the obsolete duplicate
pin, while retaining the official CF475 fold registration and every unrelated
HEAD allowance.

The code-identity hook correctly exposed a further legacy type conflation:
the 37-byte fill worker at 0x00523E27 retained the shared TreeKey template
name, whose first COMDAT came from an incidental count-constructor emission
in stlport_uninitialized_fill_n.cpp. Its sole relocation called the unrelated
canonical TreeKey Construct. The three actual vector-family definitions
called the genuine mutable-pair Construct instead. The kept legacy definition
was therefore wrong at 0x00523E27 despite identical non-relocation bytes.

The minimal repair gives the dedicated fill worker its genuine
`__uninitialized_fill_n<pair<int, AsciiString> *>` identity and adds an inline
layout-view bridge in the overflow and push-back units. Native overflow at
0x005244DC is the only matched caller, with its displacement at 0x00524547.
The broad legacy unit and its TreeKey helper remain unchanged. Keeping the
real generic fill definition visible preserves native handling of its unused
empty tag; an extern-template trial materialized a zero store and grew the
overflow body to 193 bytes, so that trial was discarded.

The final absolute COFF audit proves one legacy helper copy in the untouched
broad unit and three identical genuine-pair copies, each exactly 37 bytes
and independently retail-certified at 0x00523E27. All have the sole +20 REL32
to Construct at 0x00523DD4. There are zero family divergences or debt keys,
and the actual scoped code-identity check reports zero problems across all
42 rows. Both vector bodies remain exactly 178/55 bytes; all final byte,
EH, declaration, class, pin, link and placement checks pass again.
The detailed audit is
`build/direct-loop/zh/b5004c8a12/mutable-pair/fill-repair/identity-absolute-after.json`.
