SlowDeath phase-parser link repair, 2026-10-22

The current 807 authored-byte unit had two unresolved names: its phase-name
array and the by-value WeaponTemplateSetHead complement ABI. The retail
complement provider at RVA 0x0045D859 instead declares an explicit output
pointer. A by-value inline wrapper introduced a 76-byte local plus copy;
an in-place constructor wrapper removed that copy but changed saved registers
and constant allocation. Both failed the parseDeathFlags byte gate. Neither
trial is retained in Code. The useful second trial is preserved below.

Keep the original byte-exact DeathFlags body in a separate unit with its EH
handler and unwind funclet, moved through three verified add_match calls.
The moved parent's bytes and relocation names equal the saved before object.
Its unresolved by-value ABI name remains explicit; it is not reported linked.
Define the phase-name array in the remaining parser unit under its existing
ledger name. Retail RVA 0x009C9598 contains four pointers (00BEE8D8,
00C42014, 00BEE8C8, 00C42008) followed by NULL. Their terminated strings are
INITIAL, MIDPOINT, FINAL, HIT_GROUND. A new 20-byte data_rows ownership row
passes the data byte/relocation/size verifier. The BFME1 donor 37c3022de1ab
SlowDeathBehavior.cpp confirms phase semantics; the target table proves values.
No donor update, alias, pin, marker, gate or baseline change is involved.

Paired frozen-index legacy preview: phase unit 0 -> 556 authored bytes;
separate DeathFlags unit remains unlinked (251 authored bytes). The unchanged
retail complement provider remains linked (46 bytes). All 11 code rows across
these three units pass byte/EH gates, with strict current compiler receipts.
Both touched units pass declared-definition and shadow data checks. No
closed-strict closure or full census gain is claimed. The remaining ABI call
needs a codegen-preserving C++ representation before the DeathFlags unit links.

Second rejected trial against the original unit:

```diff
--- before
+++ pointer-constructor-trial
@@ -119,7 +119,11 @@
 class WeaponTemplateSetHead
 {
 public:
-	WeaponTemplateSetHead rva0045D859() throw();
+	WeaponTemplateSetHead *rva0045D859(WeaponTemplateSetHead *out) throw();
+	enum Complement { COMPLEMENT };
+	// The rowed helper takes the destination explicitly; initialize it in place.
+	__declspec(dllimport) __forceinline WeaponTemplateSetHead(WeaponTemplateSetHead &src, Complement) throw()
+	{ src.rva0045D859(this); }
 	void rva000B3ED3(const WeaponTemplateSetHead &other);
 	unsigned int m_words[19];
 };
@@ -175,7 +179,8 @@
 	SD_PHASE_COUNT = 4
 };
 
-extern const char *TheSlowDeathPhaseNames[];
+// Retail table at RVA 0x009C9598: four phase strings followed by NULL.
+const char *TheSlowDeathPhaseNames[] = { "INITIAL", "MIDPOINT", "FINAL", "HIT_GROUND", NULL };
 
 class SlowDeathBehaviorModuleData
 {
@@ -267,7 +272,7 @@
 void SlowDeathBehaviorModuleData::parseDeathFlags(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
 {
 	static Rva000B6253 s_allowedModelFlags(0, 0x95, 0x96, 0x97, 0x98, 0xB1);
-	static WeaponTemplateSetHead s_disallowedModelFlags = ((WeaponTemplateSetHead &)s_allowedModelFlags).rva0045D859();
+	static WeaponTemplateSetHead s_disallowedModelFlags((WeaponTemplateSetHead &)s_allowedModelFlags, WeaponTemplateSetHead::COMPLEMENT);
 
 	SlowDeathBehaviorModuleData *self = (SlowDeathBehaviorModuleData *)instance;
 	WeaponTemplateSetHead &modelFlags = self->m_deathModelFlags;
```
