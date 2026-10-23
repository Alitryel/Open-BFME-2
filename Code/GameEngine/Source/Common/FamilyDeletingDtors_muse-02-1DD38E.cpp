// cl: /O1 /MD
// ??_GBfmeRecord001DD3BC@@QAEPAXI@Z @0x001DD38E 28B; calls rowed ??1BfmeRecord001DD3BC@@QAE@XZ @0x001DD1FF then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x001DD1FF landing.
class BfmeRecord001DD3BC { public: ~BfmeRecord001DD3BC(); };
// ?famgenDelete001DD38E@@YAXPAVBfmeRecord001DD3BC@@@Z present-unmatched
void famgenDelete001DD38E(BfmeRecord001DD3BC *p) { delete p; }
