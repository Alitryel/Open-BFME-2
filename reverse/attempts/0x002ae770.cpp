// ?update@Player@@QAEXXZ
// partial score=0.75 date=2026-10-03
// cl: /O1 /G7 /MD /EHsc /DNDEBUG
// Reference: ZH Player::update via BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Target boundary2AE770-2AE8CF proves virtualAI+2DC; map countdown2BC,
// copy-list32C/team head334, native PMF8, local-player and frame/retaliation message.
// Map field names are inferred from operations; tail helper purposes unknown.
// This bank has354B vs351B: memory/register scheduling, saved list end, loop
// rotation and EH frame/state differ. Six native callee interfaces remain unpinned.
// No original container or opaque-tail identity is asserted. See native/trial logs.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Rva000411084 { public: void *next(); void *current; void *owner; };
class Rva000427195 { public: void *first(Rva000411084 *); };
struct CounterNode { CounterNode *next; int key; unsigned remaining; };
class Rva001FDE3FMap { public: int &lookup(const int &); };
class Rva005C4AF5DwordField { public: int get() const; char lead[0x40]; int value; };
class TeamView { public: void updateGenericScripts(); char lead[0x334]; Rva005C4AF5DwordField*head; };
struct TeamNode { TeamNode*next; TeamNode*prev; TeamView*team; };
class TeamCopy { public: TeamCopy(const void*); ~TeamCopy(); TeamNode*head; };
class UpdateAI { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void update(); };
class GameMessage { public: void appendIntegerArgument(int); void appendBooleanArgument(bool); };
class StreamView { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual GameMessage*appendMessage(int); };
class PlayerList;extern PlayerList*ThePlayerList; struct PlayerListView { char lead[0x10]; void*local; };
class GameLogic;extern GameLogic*TheGameLogic; struct FrameView { char lead[0x40]; unsigned frame; };
class GlobalData;extern GlobalData*TheGlobalData; struct ClientView { char lead[0x11BC]; bool retaliation; };
class MessageStream;extern MessageStream*TheMessageStream;
extern const int g_009BA4E4;
class Player {
public:
 char lead0[0x54];int index;char lead1[0x294-0x58];Rva001FDE3FMap mapA;char gapA[0x2A8-0x295];Rva001FDE3FMap mapB;char gapB[0x2BC-0x2A9];Rva000427195 counters;char gapC[0x2DC-0x2BD];UpdateAI*ai;char gapD[0x32C-0x2E0];void*teams;char gapE[0x33E-0x330];bool retaliation;char gapF[0x3BC-0x33F];char tail;
 void update();void tailUpdate();
};
class TailView { public: void update(unsigned); };
void Player::update()
{
 if(ai)ai->update();
 Rva000411084 it; counters.first(&it);
 while(it.current) {
  CounterNode*n=(CounterNode*)it.current;
  if(n->remaining) {
   --n->remaining;
   if(!n->remaining)mapA.lookup(n->key)=mapB.lookup(n->key);
  }
  it.next();
 }
 TeamCopy copy(&teams);
 for(TeamNode*n=copy.head->next;n!=copy.head;n=n->next) {
  typedef int (Rva005C4AF5DwordField::*Next)()const;
  Next next=&Rva005C4AF5DwordField::get;
  for(Rva005C4AF5DwordField*team=n->team->head;team;team=(Rva005C4AF5DwordField*)((team->*next)())) {
   ((TeamView*)team)->updateGenericScripts();
  }
 }
 if(((PlayerListView*)ThePlayerList)->local==this) {
  unsigned now=((FrameView*)TheGameLogic)->frame;
  if(now%g_009BA4E4==0 && ((ClientView*)TheGlobalData)->retaliation!=retaliation) {
   GameMessage*msg=((StreamView*)TheMessageStream)->appendMessage(0x462);
   if(msg){msg->appendIntegerArgument(index);msg->appendBooleanArgument(((ClientView*)TheGlobalData)->retaliation);}
  }
 }
 tailUpdate();((TailView*)&tail)->update(((FrameView*)TheGameLogic)->frame);
}
