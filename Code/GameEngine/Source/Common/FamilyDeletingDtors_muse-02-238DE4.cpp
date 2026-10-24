// cl: /O1 /MD /Ireference/shims/bfme2_ascii
// stlport
// The retail flag test and ret 4 prove the nonvirtual deleting destructor, which calls ~HeaderTemplateManager then scalar delete.
#include "../GameClient/GUI/HeaderTemplateView.h"
// ?famgenDelete00201B64@@YAXPAVHeaderTemplateManager@@@Z present-unmatched
void famgenDelete00201B64(HeaderTemplateManager *p) { delete p; }
