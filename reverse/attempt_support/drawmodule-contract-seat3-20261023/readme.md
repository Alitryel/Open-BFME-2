# DrawModule contract prerequisite audit — Seat3, 2026-10-23

Evidence only. No source/header/provider/ledger/gate change, compilation,
runtime mapping, alias, pin, dummy virtual, or coverage/linking gain.

## Inputs and inventory

Exact commits, image SHA256, table RVAs and extraction method: provenance.json.
Local HEAD: 695d1c9ec1d8cf3503e0ee32beb27dc2b7b36fcc.
Read-only origin snapshot: 2fad51776a7ca7870b503572ab54f0155db29f0c.
Donor remains 138757e9b74645fbcbb7724a7af2764e34931e11; no donor update.

- slots.tsv: every primary DrawModule slot (62), primary scripted slot (68),
  scripted +0C secondary slot (49), and +10 secondary slot (1): 180 rows.
- providers.tsv: all 306 current ledger spellings for their 114 targets;
  the primary union contains 66 distinct targets. No target lacks a ledger row.
- Fields retain exact provider decoration, source access and owning TU.
  These are CURRENT PROVIDER views, not proof of original virtual signatures.
  Folded stubs, tail transfers and purecall cannot supply missing types.
- Native table RVAs: 7C9690 base, 7CA090 scripted, 7CC588 secondary+0C,
  7CA08C secondary+10. The +0C table has 49 code entries then a null word;
  its recorded 200-byte data extent does not imply a fiftieth virtual method.

## Independent target evidence

Compact native-witnesses.disasm retains bytes and exact caller boundaries.

1. Scripted C79C9/507 installs all three vptrs, then restores the base table
   at C7BAA. CEB6F/11 and B19A1/28 also install the base table. Declaration-only
   suppression cannot legitimately remove destructor vtable emission.
2. Native Snapshot order is dtor/loadPostProcess/class-name getter/xfer.
   Canonical moduledata/Common/Snapshot.h documents this; crc(Xfer*) is ZH
   compatibility, not a native CRC slot. Class-contract Snapshot JSON has no
   complete vslot map. No complete canonical DrawModule/scripted contract exists.
3. Real DrawModule xfer at 4CBF58/21 is protected (MAEXPAVXfer), while the
   scripted destructor declares public. Its real owner is DrawModuleXfer.cpp.
   Base loadPostProcess B3FD0/1 is protected. Dtor CEB6F has already-verified
   public and protected spellings; native code alone cannot choose source access.
4. Slot55/+DC: scripted B5FD5/17 returns an AL predicate; Drawable caller
   272C1E/36 ORs AL at 272C32. Existing scripted int declaration is not a
   justified canonical 32-bit result. Slot60/+F0: 78AC6/8 forwards to moduledata
   slot30, whose 6520B/7 returns byte+15E. Drawable 272C9E/101 tests AL at
   272CE3. The current void forwarder does not express that result contract.
5. Primary slots9/10 return null-guarded outer+10 via CF155/12. Drawable ctor
   2797BD/2111 calls slot10 at 279D97/279E74/279F3A and appends results to
   its +158 vector. updateDrawable 27566B/1844 invokes each interface slot0
   at 2756D9 with 19-word condition flags and two zeros. Actual BFB76/513
   owns that secondary receiver and has (const ModelConditionFlags&,bool,int).
   The ctor view spelling const ModuleData* is not the genuine interface.
6. Primary slots41/42 return outer+0C via CA841/12. Const bone caller
   27274D/123 acquires +A4 at 272767; mutable broadcaster 2724FD/72 acquires
   +A8 at 27250B. Existing drawing methods support ObjectDrawInterface identity,
   not a one-slot void interfaceC. Const pairing comes from typed callers and
   donor context, not identical getter bytes; original acquisition symbols and
   exact owner/access remain unresolved. Slot49/225A98 returns render-object
   storage, not evidence that the original result was int.
7. Slot65/+104: B710D/1068 copies twelve matrix floats to ESI, then pushes
   ESI at B73C3 and calls +104 at B73C6. Matched source declares
   adjustAttachedTransform(Matrix3D*). Native proves matrix-storage argument,
   not original name, pointer versus reference, cv or unused return type.
   Unrelated folded EmissionVelocityInfo::DoXfer is not signature proof.

## Ownership gaps and bounded follow-on

Primary providers alone span 46 TUs, with additional secondary owners. Neutral
Rva getter/method owners and W3DModelDraw/scripted spellings are not proof of a
real intermediate base. Slots43-48 interface result types remain unsupported.
A correct hierarchy requires real provider AND consumer reconciliation; no
placeholder signatures or alias-only binding are proposed.

Existing light-draw-base-link-20261018/evidence.txt and remaining-sweep.txt
already establish ctor-only repair versus destructor table restoration. Prior
scripted-opacity-binding-link-20261015/readme.md and drawmodules-link-20261014
are declaration/getter repairs, not complete hierarchy solutions.

Two independent lifecycle prerequisites remain outside this contract bank:
- BridgeBehaviorListCleanup.cpp has a genuine pointer/delay/AsciiString+8
  twelve-byte record but declaration-only dtor. 577998/8 currently has a real
  ProductionPrerequisite record owner. A genuine Bridge definition requires
  actual owner work, not an alias. Parent routes this to Seat2; Seat3 will not edit.
- TerrainTrackEdgeInfoO1.cpp supplies free stdcall 83CD7/18; scripted TU asks
  for an unprovided thiscall owner. re_attempts.log entry50418 already tested
  the free provider: 505 instead of507 bytes, losing ECX staging. Do not repeat
  that trial or add a dummy wrapper. Real ownership/ABI evidence is still needed.

No bounded one-file hierarchy implementation is justified. Any eventual shared
header needs explicit owner/consumer migration scope across Device/Common/
GameLogic/WWLib, dependent byte/ref/EH/declared checks and the normal full header
hook. No new include/flag/runtime mapping is requested or attempted here.
Research claims are released after this evidence-only commit, per parent.
