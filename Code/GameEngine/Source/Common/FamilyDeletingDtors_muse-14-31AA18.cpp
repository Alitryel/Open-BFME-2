// cl: /O1 /MD
// ??_GControlBarSchemeManager@@QAEPAXI@Z, retail 0x0031AA18, 28 bytes. Deleting dtor calls rowed ??1ControlBarSchemeManager@@QAE@XZ @0x003204D9 then operator delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x003204D9 landing.
class ControlBarSchemeManager { public: ~ControlBarSchemeManager(); };
// ?famgenDelete0031AA18@@YAXPAVControlBarSchemeManager@@@Z present-unmatched
void famgenDelete0031AA18(ControlBarSchemeManager *controlBarSchemeManager) { delete controlBarSchemeManager; }
