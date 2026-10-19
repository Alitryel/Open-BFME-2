# ??0DamageInfo@@QAE@XZ: 12 wrong COMDAT copies, body rowed under a placeholder (lane C, seat8)

Diagnosis only; no source changed.

- Retail body: 0x00263895, 45 B, rowed as `??0Rva00263895Member@@QAE@XZ` in
  `Code/GameEngine/Source/Common/RTS/Rva00263895Init.cpp`; `??0DamageInfo@@QAE@XZ` is only a
  symbols.csv pin there. Bytes: `push esi; mov esi,ecx; lea ecx,[esi+4]; mov [esi],0xBF9200;
  call 0x00263653; xorps; mov [esi+6C],0xBF91AC; movss [esi+70],[esi+74]; mov byte [esi+78],0;
  mov eax,esi; pop esi; ret` (target facts): no EH frame, no out-of-line Snapshot ctor call,
  DamageInfoInput ctor out of line at +4 (0x68 B), DamageInfoOutput constructed inline at +0x6C
  with its own vptr 0xBF91AC, floats +70/+74, bool +78. Size 0x7C.
- The census (13:17) judges the pin home 0x00263895: all 12 copies are `wrong`, two digests,
  both from Zero Hour Damage.h views in ZH-port units:
  - 37a97af02616 (9: DumbProjectileBehavior, JetAIUpdate, CreateObjectDie, Weapon,
    HackInternetAIUpdate, OpenContain, FlammableUpdate, PhysicsUpdate, StickyBombUpdate):
    67 B, EH prolog, calls ??0Snapshot, ??0DamageInfoInput, ??0DamageInfoOutput out of line.
  - d1030fcaa0f5 (3: FlightDeckBehavior, ParkingPlaceBehavior, RailroadGuideAIUpdate): 188 B,
    EH frame, everything inlined incl. a Snapshot base for DamageInfoInput/Output.
- class_views: DamageInfo has 56 units and 45 layouts and no canonical header.
- Fix shape: a BFME2 Damage.h view (header_adopt_lane / class_contract) where DamageInfoInput's
  ctor is out of line and nothrow, DamageInfoOutput's is inline and the DamageInfo ctor is
  declared, not defined, in consumers; then rename the row to ??0DamageInfo@@QAE@XZ (retire
  the pin and the two /alternatename hatches in Rva00263895Init.cpp). Retail calls the
  out-of-line ctor from 40+ sites, so consumers keep `call ??0DamageInfo` byte-identical.
