// cl: /O1 /MD
// ??_GRva0048C200Owner@@QAEPAXI@Z @0x00201A17 28B; calls rowed ??1Rva0048C200Owner@@QAE@XZ @0x002019E1 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x002019E1 landing.
class Rva0048C200Owner { public: ~Rva0048C200Owner(); };
// ?famgenDelete0048C200Owner@@YAXPAVRva0048C200Owner@@@Z present-unmatched
void famgenDelete0048C200Owner(Rva0048C200Owner *p) { delete p; }
