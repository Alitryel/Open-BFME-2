// cl: /O1 /MD
// ??_GRva00216108@@QAEPAXI@Z @0x002161C2 28B; calls rowed ??1Rva00216108@@QAE@XZ @0x00216108 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x00216108 landing.
class Rva00216108 { public: ~Rva00216108(); };
// ?famgenDelete00216108@@YAXPAVRva00216108@@@Z present-unmatched
void famgenDelete00216108(Rva00216108 *p) { delete p; }
