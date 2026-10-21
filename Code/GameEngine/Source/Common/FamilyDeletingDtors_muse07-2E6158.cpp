// cl: /O1 /MD
// ??_GGameTextTable@@QAEPAXI@Z @0x002E6415 28B; calls rowed ??1GameTextTable@@QAE@XZ @0x002E6158 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x002E6158 landing.
class GameTextTable { public: ~GameTextTable(); };
// ?famgenDelete002E6158@@YAXPAVGameTextTable@@@Z present-unmatched
void famgenDelete002E6158(GameTextTable *gameTextTable) { delete gameTextTable; }
