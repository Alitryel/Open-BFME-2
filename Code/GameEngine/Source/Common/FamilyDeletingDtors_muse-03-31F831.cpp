// cl: /O1 /MD
// ??_GRva0031F831@@QAEPAXI@Z @0x0031F856 28B; calls rowed ??1Rva0031F831@@QAE@XZ @0x0031F831 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x0031F831 landing.
class Rva0031F831 { public: ~Rva0031F831(); };
// ?famgenDelete0031F831@@YAXPAVRva0031F831@@@Z present-unmatched
void famgenDelete0031F831(Rva0031F831 *p) { delete p; }
