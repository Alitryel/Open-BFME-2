// cl: /O1 /MD
// ??_GRva002004FD@@QAEPAXI@Z @0x0031F83A 28B; calls rowed ??1Rva002004FD@@QAE@XZ @0x002004FD then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape identical to 0x0031F856; chain from 0x002004FD landing; QAE non-virtual so QAEPAXI.
class Rva002004FD { public: ~Rva002004FD(); };
// ?famgenDelete002004FD@@YAXPAVRva002004FD@@@Z present-unmatched
void famgenDelete002004FD(Rva002004FD *p) { delete p; }
