// cl: /O1 /MD
// ??_GRva003F0C6C@@QAEPAXI@Z @0x003F1180 28B; calls rowed ??1Rva003F0C6C@@QAE@XZ @0x003F0C6C then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x003F0C6C landing.
class Rva003F0C6C { public: ~Rva003F0C6C(); };
// ?famgenDelete003F0C6C@@YAXPAVRva003F0C6C@@@Z present-unmatched
void famgenDelete003F0C6C(Rva003F0C6C *p) { delete p; }
