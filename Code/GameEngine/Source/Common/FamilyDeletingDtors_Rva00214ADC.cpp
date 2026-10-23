// cl: /O1 /MD
// ??_GRva00214ADC@@QAEPAXI@Z @0x00214AE4 28B; calls rowed ??1Rva00214ADC@@QAE@XZ @0x00214ADC then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x00214ADC landing.
class Rva00214ADC { public: ~Rva00214ADC(); };
// ?famgenDelete00214ADC@@YAXPAVRva00214ADC@@@Z present-unmatched
void famgenDelete00214ADC(Rva00214ADC *p) { delete p; }
