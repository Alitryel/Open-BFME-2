// cl: /O1 /MD
// ??_GRva003EF728@@QAEPAXI@Z @0x0020E32A 28B; calls rowed ??1Rva003EF728@@QAE@XZ @0x003EF728 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x003EF728 landing.
class Rva003EF728 { public: ~Rva003EF728(); };
// ?famgenDelete003EF728@@YAXPAVRva003EF728@@@Z present-unmatched
void famgenDelete003EF728(Rva003EF728 *p) { delete p; }
