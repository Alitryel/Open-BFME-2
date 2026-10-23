// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Native 18F900..18F909 is surrounded by INT3 padding. The four-byte
// prefix is the frame sentinel used by the adaptive-delta caches in hcanim.
// This address-qualified view does not assert the original owner or full size.
class Rva0018F900FramePrefix {
 unsigned int frame;
public: Rva0018F900FramePrefix *reset();
};
Rva0018F900FramePrefix *Rva0018F900FramePrefix::reset() {
 frame=0x0fffffff;
 return this;
}
