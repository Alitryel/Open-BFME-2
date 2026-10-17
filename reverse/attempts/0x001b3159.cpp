// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.82 date=2026-10-17
// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.78 date=2026-10-14
// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.8 date=2026-10-13
// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.8 date=2026-10-13
// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.80 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// Retail 0x001B3159 (442B). Port target: Code/Libraries/Source/WWVegas/WW3D2/BFME2Encoding0MotionChannelCtor.cpp
// (merge with its BFME2MotionChannel views; FindIndex in-class __forceinline: O1/O2 never auto-inline it,
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
 __forceinline short FindIndex(unsigned time, int **cursor)
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
static __forceinline float lerpMotion(float a, float b, float t) { return (b - a) * t + a; }
void BFME2Encoding0MotionChannel::UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor)
{
 int index = FindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
 if (Count - 1 == index || (TimeCodes[index + 1] & 0x8000)) {
  float *samples = Samples + index * Components;
  value->X = samples[0]; value->Y = samples[1]; value->Z = samples[2]; return;
 }
 float t0 = float(TimeCodes[(index ? index : index)] & ~0x8000), t1 = float(TimeCodes[index + 1] & ~0x8000);
 float ratio = (frame - t0) / (cursor ? ((t1 - t0)) : ((t1 - t0)));
 float *samples = Samples + index * Components;
 value->X = lerpMotion(samples[0], samples[Components], ratio);
 value->Y = lerpMotion(samples[1], samples[Components + 1], ratio);
 value->Z = lerpMotion(samples[2], samples[Components + 2], ratio);
}
