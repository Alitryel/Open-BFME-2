// Native 41BB26..41BB49 RET12: Object+330 WeaponSet availability query.
// InGameUI native29CE45/29CE57 loads TheActionManager in ECX before this call.
// The receiver is unused by the leaf; preserve that observed member-call view.
// Existing WeaponSet getter2C7469 is established by independent Object attack calls.
// Named after BFME 1's ActionManager::canFireWeapon (0x000C4300): the same body,
// called from InGameUI::canSelectedObjectsEffectivelyUseWeapon in both games.
// cl: /O1 /arch:SSE /G7 /MD
class Object;
class Weapon;
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum CommandSourceType { CMD_FROM_PLAYER=0 };
class WeaponSet { public: Weapon *getWeaponInWeaponSlot(WeaponSlotType) const; };
class ActionManager { public: unsigned char canFireWeapon(const Object*,WeaponSlotType,CommandSourceType); };
unsigned char ActionManager::canFireWeapon(const Object *object,WeaponSlotType slot,CommandSourceType unused) {
 if(!object) return 0;
 const WeaponSet *weapons=reinterpret_cast<const WeaponSet*>(reinterpret_cast<const char*>(object)+0x330);
 return weapons->getWeaponInWeaponSlot(slot)!=0;
}
