// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.97 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// Retail 0x001B3159 (442B). Port target: Code/Libraries/Source/WWVegas/WW3D2/BFME2Encoding0MotionChannelCtor.cpp
// (append after the dtor; MERGE with its BFME2MotionChannel/views - do NOT redefine; reuse its base/derived,
// add only FindIndex (IN-CLASS: out-of-line defs trip find_declared_unmatched even though rowed at 0x1B2EFC -
// in-class is exempt and inlines identically) + virtual UnknownSlot4 + Vector3; NO present-unmatched marker (hatch)).
// 440/442 in the TU (existing ctor/dtor rows re-verified). Interpolation (SSE lerps) is exact modulo cascade.
// FIXED HERE vs prior bank: low=0 before high=Count-2 in the search arm (was high-first; retail ands low first).
// WALL (single allocator decision + cascade): retail puts the cursor param in EBX (pushes 3 regs) and derives
// timecodes/masked/index around it; ours keeps cursor in EDX (2 regs) rotating the rest (timecodesEDI/maskedEBX).
// Everything downstream (including the exact SSE lerps) follows from that one choice. Tried/neutral: decl order,
// ai-style splits (N/A here), xor elimination (retail HAS the xor; keep index^low order).
// Prescription (U1 T-probe): cursor is ~6 deref uses vs masked-temps; find what tips ebx (likely the masked-temp
// web merging vs cursor web weight at FindIndex entry). Sibling slots 3/5 share this blocker; fix rolls forward.
// t=25 model=muse-spark (seat W7-MP6).
// Round W8 (2026-10-17, opus): inline lerpRatio(frame, t0, t1) reproduces retail's whole XMM setup
// (frame->xmm0 early, lea &TimeCodes[index], t1->xmm2, t0->xmm1, no movaps); `index == Count - 1`
// gives retail's cmp operand order; the `cursor ? A : A` probe still puts cursor in EBX (without it
// cursor falls to EDX, 107/154). Dropped the (index ? index : index) probe. 440 vs 442 B: the ONLY
// structural miss is retail's `mov edx, eax` right after the inlined cursor write (index leaves eax);
// everything after is the same code with eax/edx swapped. SHARED DELTA: slot 3 (0x1B2FEF, mov edx,eax)
// and slot 5 (0x1B3313, mov edi,eax) copy the inlined FindIndex result out of eax at the same point.
// Disproven for the copy: unsigned index, separate declaration/assignment, index via inline member
// param, single-exit FindIndex (452 B), out-param wrapper. Permute 0.932 vs prior bank 0.936: the
// prior bank is size-exact by coincidence (extra movaps) and still has the XMM and copy misses.
// Parallel bank (other seat, 0.82) notes, kept for its disproven list:
// and retail has no call or pointer to the standalone 0x1B2EFC, so every slot inlines it).
// PROBE, NOT SOURCE: FindIndex returns `short` here. With `int` (the real type) this body is 22 diff rows;
// with `short` it is 7 (movsx edx,ax for retail's mov edx,eax; cmp operand order; frame load placement).
// Wall = retail copies the inlined result out of EAX into a separate caller live range (EDX). Retail slot3
// 0x1B2FEF (mov edx,eax) and slot5 0x1B3313 (mov edi,eax) copy the same way, so the cause is the shared
// caller pattern. Neutral/worse (do not retry): long/unsigned/unsigned long/__int64 returns, unsigned or
// long caller index, const index, dead `index = 0` init, assignment inside the condition, `last` local,
// split conditions, nested __forceinline sample helper, caller-side cursor writeback, single-exit FindIndex,
// `return *(*cursor)++ = index`, ternary dead uses of index/cursor anywhere but the ratio division.
// The `cursor ? x : x` in the ratio is what puts the cursor in EBX (only there; numerator form also works
// but swaps xmm1/xmm2); slot3 keeps the cursor in EDX. t=45 model=claude-opus-5-5.
// MERGED (2026-10-17 rebase, opus): this W8 body + the parallel bank's `short FindIndex` PROBE (not real
// source: the real return type is int) = 443 vs 442 B, 153/154 insns; the ONLY instruction diff is
// `movsx edx, ax` for retail's `mov edx, eax` at +0xA4 (the rest are 1-byte branch-target shifts). With int
// (W8 alone) eax/edx swap after that point; parallel bank alone (short + split t0/t1 + index?index:index +
// `Count - 1 == index`) is 446 B. Next: find the int-typed source that keeps this copy shape (a 32-bit
// value the compiler must copy out of eax, as the short probe forces) - shared with slots 3/5.
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
class ChunkLoadClass;
class BFME2MotionChannel {
public:
 virtual bool Load(ChunkLoadClass &); virtual ~BFME2MotionChannel(); virtual int UnknownSlot2();
 virtual void UnknownSlot3(float, float *, unsigned char **);
 virtual void UnknownSlot4(float, Vector3 *, unsigned char **);
 virtual void UnknownSlot5(float, Quaternion *, unsigned char **); virtual int UnknownSlot6();
 int Type, Pivot, Count, Components;
};
class BFME2Encoding0MotionChannel : public BFME2MotionChannel {
public:
 unsigned short *TimeCodes; float *Samples;
 __forceinline int FindIndex(unsigned time, int **cursor)
 {
  int low = 0;
  int index;
  if (cursor && (unsigned int)(index = **cursor) < (unsigned int)Count) {
   while (index && (TimeCodes[index] & ~0x8000) > time) --index;
   while (index < Count - 1 && (TimeCodes[index + 1] & ~0x8000) <= time) ++index;
   **cursor = index; ++*cursor;
   return index;
  } else {
   if (time <= (unsigned int)(TimeCodes[0] & ~0x8000)) index = 0;
   else if (time >= (unsigned int)(TimeCodes[Count - 1] & ~0x8000)) index = Count - 1;
   else {
    low = 0; int high = Count - 2;
    for (;;) {
     index = (low + high) / 2;
     if (time < (unsigned int)(TimeCodes[index] & ~0x8000)) high = index;
     else if (time >= (unsigned int)(TimeCodes[index + 1] & ~0x8000)) {
      int diff = index ^ low; if (diff) low = index; else ++low;
     } else break;
    }
   }
  }
  if (cursor) { **cursor = index; ++*cursor; }
  return index;
 }
 virtual void UnknownSlot3(float, float *, unsigned char **);
 virtual void UnknownSlot4(float, Vector3 *, unsigned char **);
 virtual void UnknownSlot5(float, Quaternion *, unsigned char **);
};
static __forceinline float lerpRatio(float frame, float t0, float t1) { return (frame - t0) / (t1 - t0); }
static __forceinline float lerpMotion(float a, float b, float t) { return (b - a) * t + a; }
void BFME2Encoding0MotionChannel::UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor)
{
 int index = FindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
 if (index == Count - 1 || (TimeCodes[index + 1] & 0x8000)) {
  float *samples = Samples + index * Components;
  value->X = samples[0]; value->Y = samples[1]; value->Z = samples[2]; return;
 }
 float ratio = lerpRatio(frame, float(TimeCodes[index] & ~0x8000), float(TimeCodes[index + 1] & ~0x8000));
 float *samples = Samples + index * Components;
 value->X = lerpMotion(samples[0], samples[Components], ratio);
 value->Y = lerpMotion(samples[1], samples[Components + 1], ratio);
 value->Z = lerpMotion(samples[2], samples[Components + 2], ratio);
}
