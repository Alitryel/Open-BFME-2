// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

// Native2AB894..2AB8D0 is a complete RET4 body between the rowed
// null-guarded UpgradeTemplate predicate2AB87D and Player brownout handler.
// It tests every pointer in the supplied vector and returns true when empty.
// Initialize the index before the end-minus-begin count: this preserves the
// native zeroing instruction before the count shift. Original method name
// is unknown; the Player receiver follows the established predicate owner.

class UpgradeTemplate;
class Player {
public:
 bool rva002AB87D(const UpgradeTemplate*)const;
 bool rva002AB894(const _STL::vector<UpgradeTemplate*>& upgrades)const;
};
bool Player::rva002AB894(const _STL::vector<UpgradeTemplate*>& upgrades)const {
 unsigned i = 0;
 unsigned count = upgrades.end() - upgrades.begin();
 if (count) {
  UpgradeTemplate *const *it = upgrades.begin();
  do {
   if (!rva002AB87D(*it)) return false;
   ++i;
   ++it;
  } while (i < count);
 }
 return true;
}
