// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// UpgradeCenter constructor installs retail's fourteen-slot table at 0x007FABB8.
#include "../../../../reference/shims/upgradecenter_bfme2/upgrade_center.h"

UpgradeCenter::UpgradeCenter()
    : m_upgradeList(0), m_nextTemplateMaskBit(0), m_buttonImagesCached(false), m_extra()
{
}
