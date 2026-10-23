// cl: /O1 /MD
// ??_GRva005B72E7@@QAEPAXI@Z @0x005B7352 28B; calls rowed ??1Rva005B72E7@@QAE@XZ @0x005B72E7 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x005B72E7 landing.
class Rva005B72E7 { public: ~Rva005B72E7(); };
// ?famgenDelete005B72E7@@YAXPAVRva005B72E7@@@Z present-unmatched
void famgenDelete005B72E7(Rva005B72E7 *p) { delete p; }
