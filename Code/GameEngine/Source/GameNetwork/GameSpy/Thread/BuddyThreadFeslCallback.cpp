// cl: /O1 /G7 /Ow /arch:SSE /DNDEBUG /MD
// /Ow matches native scheduling across the distinct queue object and flag storage.
// Native550921..550995 is the sole slot of listener vtableC6AC08.
// Constructor550918 installs it; native Thread_Function552027 allocates four
// bytes and installs the same table before registering the listener at658680.
// This is an event callback with three stack words (RET12), not a destructor.
// Event4 sets ready; event0 plus a non-null error header whose first word is
// -204 emits BuddyResponse kind6/result4/error6/fatal1 and sets failed.
// Target bytes establish offsets and ABI; original API and argument names
// remain unknown. The second word is unused and modeled without a type claim.
// Sole storage for native one-byte flags E05FC0/E05FC1. No defined global at
// either address occurs in the current compiled ledger's DIR32 address index.
bool g_buddyFeslReady;
bool g_buddyFeslFailed;

class BuddyResponse {
public:
 int kind;
 int unknown04;
 int result;
 int unknown0C;
 int error;
 char unknown14[0x80];
 int fatal;
 char unknown98[0x864-0x98];
};
typedef char BuddyResponseSize[sizeof(BuddyResponse)==0x864?1:-1];
class GameSpyBuddyMessageQueueInterface {
public:
 virtual void unknown0(); virtual void unknown1();
 virtual void unknown2(); virtual void unknown3();
 virtual void unknown4(); virtual void unknown5();
 virtual void unknown6(); virtual void unknown7();
 virtual void addResponse(const BuddyResponse &response);
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
// The existing linker alternate binds this canonical name to the sole queue
// storage in Rva00627AA0Call.cpp; no new storage or alternate is introduced.

class Rva00550918 {
public:
 Rva00550918();
 virtual void rva00550921(int event, unsigned int opaque, const int *error);
};
void Rva00550918::rva00550921(int event, unsigned int opaque, const int *error)
{
 if(event!=0) {
  if(event==4)g_buddyFeslReady=true;
  return;
 }
 if(error && *error==-204) {
  BuddyResponse response;
  response.kind=6;
  response.result=4;
  response.error=6;
  response.fatal=1;
  g_buddyFeslReady=false;
  g_buddyFeslFailed=true;
  TheGameSpyBuddyMessageQueue->addResponse(response);
 }
}
