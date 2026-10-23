// cl: /O1 /MD
// ??_GRva0023D377@@QAEPAXI@Z @0x0023DACC 28B; calls rowed ??1Rva0023D377@@QAE@XZ @0x0023D377 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x0023D377 landing.
class Rva0023D377 { public: ~Rva0023D377(); };
// ?famgenDelete0023DACC@@YAXPAVRva0023D377@@@Z present-unmatched
void famgenDelete0023DACC(Rva0023D377 *p) { delete p; }
