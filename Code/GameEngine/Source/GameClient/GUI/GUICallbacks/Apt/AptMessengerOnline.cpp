// ?UpdatePlayerTabButtons@AptMessengerOnline@@QAEXXZ
// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Retail 0x005AED3C..0x005AEF16, 474 bytes, thiscall RET0.
// Identity: WB 0x01515B40 names UpdatePlayerTabButtons in AptMessengerOnline.cpp;
// four identical APT labels and the selection/buddy/profile call graph agree.
// Target evidence: the menu is a vector of eight-byte label/enabled entries at
// +0x28C; the pending-friend flag is +0x2A0. Existing GetSelectedPlayers,
// MyBuddyList_ snapshot and profile-query providers establish the local ABI.
// Opaque provider names and unused interface slots remain address-derived.
// The WB early returns preserve both vector cleanup paths. String assignment
// and vector indexing produce the retail stack iterator and retained zero.
// Recovered from the October 8 bank using retail and WorldBuilder evidence.
#include <vector>
#include "ascii_string.h"
void Rva00030830FreeAllocation(void *);
struct BfmeE8 {void *p;unsigned char flag;char pad[3];};
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,size_t) const {if(p)::Rva00030830FreeAllocation(p);}
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *p, size_t n) {static_cast<const allocator<int> &>(*this).deallocate(p, n);}
}
class PlayerInfo {public: bool isIgnored();};
class GameSpyInfoInterface {public:
 virtual void _M_slot_00();
 virtual void _M_slot_04();
 virtual void _M_slot_08();
 virtual void _M_slot_0c();
 virtual void _M_slot_10();
 virtual void _M_slot_14();
 virtual void _M_slot_18();
 virtual void _M_slot_1c();
 virtual void _M_slot_20();
 virtual void _M_slot_24();
 virtual void _M_slot_28();
 virtual void _M_slot_2c();
 virtual void _M_slot_30();
 virtual void _M_slot_34();
 virtual void _M_slot_38();
 virtual void _M_slot_3c();
 virtual void _M_slot_40();
 virtual void _M_slot_44();
 virtual void _M_slot_48();
 virtual void _M_slot_4c();
 virtual void _M_slot_50();
 virtual void _M_slot_54();
 virtual void _M_slot_58();
 virtual PlayerInfo *rva00382D0A(int profile);
 virtual void _M_slot_60();
 virtual void _M_slot_64();
 virtual void _M_slot_68();
 virtual void _M_slot_6c();
 virtual void _M_slot_70();
 virtual void _M_slot_74();
 virtual void _M_slot_78();
 virtual int getLocalProfileID();

};
extern GameSpyInfoInterface *TheGameSpyInfo;

class AptMessenger
{
public:
    __declspec(noinline) void GetSelectedPlayers(int, int, int);
};
class Rva005AEB2C
{
public:
    Rva005AEB2C();
    _STL::vector<BfmeE8> m_vec;
};
class Rva005AE7A5Class
{
public:
    int rva005AE7A5(int);
};
extern int g_Va00E046BC;
struct MessengerOnlineButton
{
    AsciiString text;
    bool enabled;
    char pad[3];
};
class AptMessengerOnline : public AptMessenger
{
public:
    void UpdatePlayerTabButtons();
private:
    char prefix[0x28c];
    _STL::vector<MessengerOnlineButton> buttons;
    char middle[8];
    bool acceptingFriend;
};
void AptMessengerOnline::UpdatePlayerTabButtons()
{
    if (!TheGameSpyInfo)
        return;
    buttons[0].text = "APT:AddFriend";
    buttons[1].text = "APT:Ignore";
    buttons[0].enabled = false;
    buttons[1].enabled = false;
    acceptingFriend = false;
    _STL::vector<int> selected;
    GetSelectedPlayers(g_Va00E046BC, (int)&selected, 0);
    if (selected.size() != 1)
        return;
    int ignored, notIgnored, notBuddy, pendingBuddy;
    int *it;
    ignored = 0;
    notIgnored = 0;
    notBuddy = 0;
    pendingBuddy = 0;
    int local = TheGameSpyInfo->getLocalProfileID();
    Rva005AEB2C buddies;
    for (it = selected.begin(); it != selected.end(); ++it)
    {
        int profile = *it;
        if (profile == local)
            return;
        BfmeE8 *buddy = (BfmeE8 *)((Rva005AE7A5Class *)&buddies)->rva005AE7A5(profile);
        if (buddy)
        {
            if (!buddy->flag)
                return;
            ++pendingBuddy;
        }
        else
            ++notBuddy;
        PlayerInfo *player = TheGameSpyInfo->rva00382D0A(profile);
        if (player)
        {
            if (player->isIgnored())
                ++ignored;
            else
                ++notIgnored;
        }
    }
    if (notBuddy)
        buttons[0].enabled = (pendingBuddy == 0);
    else if (pendingBuddy)
    {
        buttons[0].text = "APT:AcceptFriend";
        buttons[0].enabled = true;
        acceptingFriend = true;
    }
    if (notIgnored)
        buttons[1].enabled = (ignored == 0);
    else if (ignored)
    {
        buttons[1].enabled = true;
        buttons[1].text = "APT:RemoveIgnore";
    }
}
