# SimpleScene folded getter providers

At BFME2 549e305450 with published census b711de3634 (2026-10-23 14:28),
paired link_check of SimpleSceneClassConstructorBFME2.cpp and
SimpleSceneClass_dtor.cpp reported 0/1074 and 0/290 linked bytes. Both had
exactly three unresolved names: SceneClass Get_Ambient_Light, Get_Fog_Enable,
and Get_Fog_Color. The same paired check after supplying the definitions
reports LINKS for both: +1364 legacy linked bytes. This does not measure
self-strict or closed-strict gains. No unique retail bytes are newly recovered.

Target evidence: constructor142960 installs native SimpleScene vtable BD33D0.
Its slots7/9/11 are VA9C4AD5/8C54EC/8F5FA3, respectively. Complete bodies are
8d4108c3 / 8a411cc3 / 8d4120c3: member-address +8, byte +1C, member-address +20.
The already verified SceneClass constructor140C60 initializes these members.
Existing ledger owners at those addresses prove the complete four-byte extents;
there are no relocations. Added rows use exact gen-alias tokens and add_match's
--icf-owner admission; no owner was renamed and no symbol pin was introduced.

Names and semantic member labels come from existing SceneClass declarations and
BFME1 scene.h at verified donor96c88c73a5cd1a58fc2f8db691beea50acd996db.
The native slots, bodies, offsets and constructor are independent target facts;
byte equality alone is not the source of the names. Official donor master was
fetched at f5140c1cff6a58e16276fd6de6788186286953d4; linking changes through that
revision were reviewed, including604f6b70's named string-callee reconciliation.
The verified donor pointer stays unchanged pending its paired full-gate update.

Validation: add_match verified all9 provider rows; build.sh verified all11
consumer rows; find_declared_unmatched and check_csv passed. link_check used
both current objects together against the published index. No full census,
link_cycle, nightly or boot runner was started.
