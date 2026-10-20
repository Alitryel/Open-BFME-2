// cl: /O1 /EHsc /DNDEBUG /MD
// ?FindIndex@BFME2Encoding0MotionChannel@@QAEHIPAPAH@Z @0x001B2EFC 215B
// Timecode search and quaternion slot of the BFME 2 encoding-0 motion channel (WorldBuilder twin:
// MotionChannelTimeCoded.cpp). Layout from the factory/ctor units: Count +0xC, Components +0x10,
// TimeCodes +0x14, Samples +0x18. Retail inlines both searches into the slots and emits them standalone.
class Quaternion { public: float X, Y, Z, W; };
class Vector3;
class ChunkLoadClass;
void BFME2_Nlerp(Quaternion &, const Quaternion &, const Quaternion &, float);
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
 unsigned short *TimeCodes;
 float *Samples;
 // Retail 0x001B2DC4: binary search over TimeCodes masked with ~0x8000 for the key at or below
 // time; each outcome returns from inside the search.
 __forceinline int rva001B2DC4(unsigned int time)
 {
  if (time <= (TimeCodes[0] & ~0x8000)) return 0;
  if (time >= (TimeCodes[Count-1] & ~0x8000)) return Count-1;
  int low = 0;
  int high = Count-2;
  for (;;) {
   int mid = (low+high)/2;
   unsigned short *key = &TimeCodes[mid];
   if (time < (key[0] & ~0x8000)) { high = mid; continue; }
   if (time < (key[1] & ~0x8000)) return mid;
   if (low ^ mid) low = mid; else ++low;
  }
 }
 int FindIndex(unsigned int time, int **context);
 virtual void UnknownSlot3(float, float *, unsigned char **);
 virtual void UnknownSlot4(float, Vector3 *, unsigned char **);
 virtual void UnknownSlot5(float, Quaternion *, unsigned char **);
};
// ?FindIndex@BFME2Encoding0MotionChannel@@QAEHIPAPAH@Z, retail 0x001B2EFC, 215 bytes (RET8): walk the
// cached cursor record when it is in range, else binary search; the result is written back to the cursor.
__forceinline int BFME2Encoding0MotionChannel::FindIndex(unsigned int time, int **context)
{
 if (context) {
  int *rec = *context;
  if ((unsigned int)*rec < (unsigned int)Count) {
   int index = *rec;
   while (index && (TimeCodes[index] & ~0x8000) > time) --index;
   while (index < Count-1 && (TimeCodes[index+1] & ~0x8000) <= time) ++index;
   *rec = index; ++*context;
   return index;
  }
 }
 int index = rva001B2DC4(time);
 if (context) { **context = index; ++*context; }
 return index;
}

// ?UnknownSlot5@BFME2Encoding0MotionChannel@@UAEXMPAVQuaternion@@PAPAE@Z, retail 0x001B3313, 376 bytes:
// quaternion sample at frame, held keys copied, otherwise BFME2_Nlerp between the two bracketing keys.
void BFME2Encoding0MotionChannel::UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor)
{
 int index = FindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
 if (index == Count-1 || (TimeCodes[index+1] & 0x8000)) {
  float *samples = Samples + index*Components;
  value->X = samples[0]; value->Y = samples[1]; value->Z = samples[2]; value->W = samples[3]; return;
 }
 float t0 = float(TimeCodes[index] & ~0x8000), t1 = float(TimeCodes[index+1] & ~0x8000);
 float ratio = (frame-t0)/(t1-t0);
 float *samples = Samples + index*Components;
 BFME2_Nlerp(*value, *reinterpret_cast<Quaternion *>(samples), *reinterpret_cast<Quaternion *>(samples+Components), ratio);
}
