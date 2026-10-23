// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// Complete retail 0x0009A30A..0x0009A338. Existing 0x0009A328 is
// only its last null-guarded call. BFME1 S3GuardedGlobalTriples.cpp and
// matched W3DShadowManagerToggleLists.cpp supply the manager-call pattern.
class W3DVolumetricShadowManager;
class W3DProjectedShadowManager;
class Rva00108660ResourceManager;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
class Rva000F0AB2 { public: void rva000F0AB2(); };
class Rva00107152 { public: void rva00107152(); };
class Rva00109236 { public: void rva00109236(); };
void rva0009A30A() {
 if(TheW3DVolumetricShadowManager) reinterpret_cast<Rva000F0AB2 *>(TheW3DVolumetricShadowManager)->rva000F0AB2();
 if(TheW3DProjectedShadowManager) reinterpret_cast<Rva00107152 *>(TheW3DProjectedShadowManager)->rva00107152();
 if(Rva00DEC2D8Manager) reinterpret_cast<Rva00109236 *>(Rva00DEC2D8Manager)->rva00109236();
}
