// ?rva007092F0@AptActionInterpreter@@AAEXPAVAptCIH@@PAVAptValue@@11H1@Z
// partial score=0.96 date=2026-10-15
// Rechecked 2026-10-15 in the complete current home TU: default, /G6,
// /EHs and /EHa all emit 491B with the same delayed ESI save; /G7 with
// /EHsc or /EHs emits 490B and retains that mismatch. All six resolve
// every call and have exact EH graphs. The earlier untested /G6 lead
// is now exhausted for this draft; do not repeat without new evidence.
// ?rva007092F0@AptActionInterpreter@@AAEXPAVAptCIH@@PAVAptValue@@11H1@Z
// Banked 0x007092F0 attempt: unified diff against AptActionInterpreterConstantHandlers.cpp at 7ffe28d8bf (the no-/arch:SSE '-O2' override unit that also owns the caller 0x...1627 and rowed 0x007065E0); apply with patch --binary -l (file is CRLF; diff is CR-stripped).
// 491/491 size-exact; only residue: retail pushes ESI at entry (pop after the name dtor), cl shrink-wraps it into the if(value) region (all later offsets shift by that push).
--- a/Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp
+++ b/Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp
@@ -1301,6 +1301,7 @@
     AptSpriteInstBase *GetSpriteInstBase() const;
     bool IsSpriteInstBase() const;
     bool IsCharacterInst() const;
+    void *rva006E1020() const;
     __forceinline AptSpriteInstBase *GetCharacterInst() const {
         if (!IsCharacterInst()) {
             g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xA5);
@@ -2693,6 +2694,7 @@
 // First-argument spelling at6FF850 preserves the already pinned bank ABI.
 class BfmeAptValue006DCD20 {
 public:
+    int rva006E0350() const;
     BfmeAptValue006DCD20 *rva006DCEA0();
     float rva006DD460();
     BfmeAptValue006DCD20 *rva006DD0E0();
@@ -2908,3 +2910,44 @@
         p->thisStack.pop(); savedObject->Release(); savedParams->Release();
     } else { p->stack.rva006E3AA0(nParams+3); p->stack.PushNoInc(gpUndefinedValue); }
 }
+
+// ?rva007092F0@AptActionInterpreter@@AAEXPAVAptCIH@@PAVAptValue@@11H1@Z, retail
+// 0x007092F0 (491 B): duplicate-movie-clip helper. The source value is
+// converted through the rowed 0x007065E0 (defined above), the target name
+// is stringified, and when the converted value's character instance has a
+// display-list parent the clone is submitted to the parent's display list
+// (rowed 0x006F8B70) with the depth, the child's matrix, colour transform,
+// clip actions, morph ratio (the level instance +0x18 float, copied as raw
+// bits) and init object; a clip whose sprite base +0x2C flag is 1 marks the
+// new clone (rowed 0x006F6BB0 / 0x006E3C80), then the animation pool ticks
+// new instances (0x006E4390). Built without /arch:SSE like the rest of this
+// unit: retail copies the morph float through EDX and stores the 0.0f
+// default as an immediate.
+class Rva006E3C80 { public: int rva006E3C80(); };
+class AptAnimationPoolData { public: void _tickNewInsts(); };
+class BfmeSubmitter1283 { public: void *bfmeSubmit1283(AptCIH*,int,int,int,int,int,int,float*,int,int,int,int); };
+class BfmeQuery1279 { public: void bfmeQuery1279(int,int,void**,void**); };
+struct Rva007092F0Character { char prefix[0x2c]; int flag2c; };
+void AptActionInterpreter::rva007092F0(AptCIH *context,AptValue *with,AptValue *source,AptValue *target,int depth,AptValue *init)
+{
+    AptValue *value=0;
+    rva007065e0((int)context,(int)with,(BfmeAptValue006DCD20*)source,(BfmeAptValue006DCD20**)&value);
+    EAStringC name;
+    target->toString(name);
+    if(value) {
+        AptCIH *child=value->c_cih(false);
+        if(child->mpDisplayListParent) {
+            float morphFloat=static_cast<unsigned char>(((BfmeAptValue006DCD20*)child)->rva006E0350()) ? *(float*)((char*)child->rva006E1020()+0x18) : 0.0f; int morph=*(int*)&morphFloat;
+            int actions=child->IsSpriteInstBase() ? (int)child->GetSpriteInstBase()->clipActions : 0;
+            AptSpriteInstBase *definition=child->SpriteBaseInline();
+            AptSpriteInstBase *parentDefinition=(child->mpDisplayListParent)->SpriteBaseInline();
+            ((BfmeSubmitter1283*)&parentDefinition->displayList)->bfmeSubmit1283(0,depth,(int)definition->character,(int)&name,(int)(child->mpDisplayListParent),1,-1,(float*)child->matrixToParent,(int)((char*)child+0xc),actions,morph,(int)init);
+            if(((((Rva007092F0Character*)child->SpriteBaseInline())->flag2c))==1) {
+                AptCIH *clone=0,*prev=0;
+                (*(BfmeQuery1279**)&child->mpDisplayListParent->GetSpriteInstBase()->displayList)->bfmeQuery1279(depth,(int)&name,(void**)&prev,(void**)&clone);
+                if(clone->isCIH(false)) ((Rva007092F0Character*)((Rva006E3C80*)clone)->rva006E3C80())->flag2c=1;
+            }
+            ((AptAnimationPoolData*)g_bfmeAptPtrAtE176D0)->_tickNewInsts();
+        }
+    }
+}
