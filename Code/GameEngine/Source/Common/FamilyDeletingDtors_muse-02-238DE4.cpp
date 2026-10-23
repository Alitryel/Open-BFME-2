// cl: /O1 /MD
// ??_GRva00201B64@@QAEPAXI@Z @0x00238DE4 28B; calls rowed ??1Rva00201B64@@QAE@XZ @0x00201B64 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x00201B64 landing.
class Rva00201B64 { public: ~Rva00201B64(); };
// ?famgenDelete00201B64@@YAXPAVRva00201B64@@@Z present-unmatched
void famgenDelete00201B64(Rva00201B64 *p) { delete p; }
