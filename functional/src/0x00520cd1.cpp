// ?rva00520CD1@AptTimeLine@@QAEXXZ
// partial score=0.97 date=2026-10-16
// ?rva00520CD1@AptTimeLine@@QAEXXZ
// partial score=0.97 date=2026-10-16
// ?rva00520CD1@AptTimeLine@@QAEXXZ
// partial score=0.97 date=2026-10-16
// W9-O3 2026-10-16: callees renamed to their rows (AptScoreScreen::PreCollectGameData 0x51C241, CollectAllPlayerData 0x51FA13, CollectPlayerData(Player*,const GameSlot*) 0x520792: the bank had 3 unresolved calls); volatile slot dropped (inert). nd 12 size exact: retail keeps slot (=0 home [ebp-0x1c], reload mov edi,[ebp-0x1c] on the not-found exit) in EDI after the j loop and spills tactical into the same home; ours keeps slot in memory and gives EDI to tactical. Inert: early-init tactical/slot at function scope, split decl, extra tactical copy, j-after-loop getSlot forms (worse).
// ?rva00520CD1@AptTimeLine@@QAEXXZ
// partial score=0.94614 date=2026-10-13
// ?rva00520CD1@AptTimeLine@@QAEXXZ
// partial score=0.94614 date=2026-10-13
// ?rva00520CD1@AptTimeLine@@QAEXXZ
// partial score=0.82 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /I. /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <vector>
struct Rva00520211Element { char storage[80]; };
extern template Rva00520211Element *_STL::vector<Rva00520211Element>::erase(Rva00520211Element *,Rva00520211Element *);
extern template void _STL::vector<Rva00520211Element>::reserve(unsigned);
class Rva00520703Vector {public:void resize(unsigned);};
struct Rva0051C0E7;
class AptScoreScreen {public: static void PreCollectGameData(Rva0051C0E7*);};
class IDBufferClass {public:void Enable_Two_Sided_Rendering(bool);};
class ParticleSystem {public:bool isSaveable()const;};
enum NameKeyType {NAMEKEY_INVALID=0};
class Player;
class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString &);};
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerList {public:Player *findPlayerWithNameKey(NameKeyType);char pad00[0x10];Player *m_local;};
extern PlayerList *ThePlayerList;
class Player {public:bool rva002AA223()const;};
class GameSlot {public:bool isOccupied()const;char pad00[0x34];AsciiString m_name;char pad38[0x4c-0x38];void *m_template;};
class GameInfo {public:GameSlot *getSlot(int);};
class SkirmishGameInfo;
extern GameInfo *TheGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;
class LivingWorldPlayer;
class Rva002E2903Player;
class Rva002BA8F1Logic {public:Rva002E2903Player *rva002B52A8(int);char pad00[0x8c];_STL::vector<LivingWorldPlayer*>m_players;};
extern Rva002BA8F1Logic *TheLivingWorldLogic;
class LivingWorldPlayer {public:char pad00[0x14];void *m_template;};
class Rva002E0687 {public:bool rva002E0687()const;};
extern int g_rva0059EB6FFlag;
class StatsReporter {public:static void ProcessOnlineGameResults(Player*);};
class Rva00520923Source;
class AptTimeLine {public:
 void rva00520CD1();void CollectPlayerData(Player*,const GameSlot*);
 void CollectPlayerData(LivingWorldPlayer*,Rva00520923Source*);
 void CollectAllPlayerData();
 char pad000[0x280];void *m_stats;int m_mode;
 _STL::vector<Rva00520211Element> m_players;
 bool m_observer;char pad295[0x2c4-0x295];char m_extra[48];
};
void AptTimeLine::rva00520CD1()
{
 m_players.clear();
 m_players.reserve(8);
 m_observer=false;
 reinterpret_cast<IDBufferClass*>(m_stats)->Enable_Two_Sided_Rendering(false);
 if(m_mode==6 || m_mode==7){
  reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
  GameInfo *game=0;
  if(m_mode==6)game=reinterpret_cast<GameInfo*>(TheSkirmishGameInfo);
  else if(m_mode==7)game=TheGameInfo;
  if(game) {
   for(int i=0;i<(int)TheLivingWorldLogic->m_players.size();++i) {
    LivingWorldPlayer *player=reinterpret_cast<LivingWorldPlayer*>(TheLivingWorldLogic->rva002B52A8(i));
    GameSlot * slot = 0;
    for(int j=0;j<8;++j) {
     if(game->getSlot(j)->m_template==player->m_template) {slot=game->getSlot(j);break;}
    }
    if(g_rva0059EB6FFlag && (j ? (reinterpret_cast<Rva002E0687*>(player)->rva002E0687()) : (reinterpret_cast<Rva002E0687*>(player)->rva002E0687())) && m_mode==7) {
     AsciiString name=slot->m_name;
     Player *tactical=(m_mode ? (ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name))) : (ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name))));
     if(tactical && !tactical->rva002AA223())StatsReporter::ProcessOnlineGameResults(tactical);
    }
    CollectPlayerData(player,reinterpret_cast<Rva00520923Source*>(slot));
   }
  }
 }else{
  if(TheGameInfo) {
   m_observer=ThePlayerList->m_local->rva002AA223();
   reinterpret_cast<IDBufferClass*>(m_stats)->Enable_Two_Sided_Rendering(m_observer);
   if(!m_observer)reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
   for(int i=0;i<8;++i) {
    GameSlot *slot=TheGameInfo->getSlot(i);
    if(slot->isOccupied()) {
     AsciiString name=slot->m_name;
     if(!name.isEmpty()) {
      Player *player=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
      if(player && !player->rva002AA223())CollectPlayerData(player,slot);
     }
    }
   }
  } else {
   reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
   Player *player=ThePlayerList->m_local;
   if(!player)return;
   CollectPlayerData(player,0);
  }
 }
 if(m_mode==1||m_mode==6||m_mode==7)AptScoreScreen::PreCollectGameData(reinterpret_cast<Rva0051C0E7*>(m_extra));
 CollectAllPlayerData();
}
