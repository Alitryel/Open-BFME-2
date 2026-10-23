#ifndef FXPARTICLE_LINK_MODULE_TEMPLATE_H
#define FXPARTICLE_LINK_MODULE_TEMPLATE_H

namespace FXParticleSystem
{
// Retail table 0x00BBB52C contains only the deleting destructor.
class ModuleTemplate
{
public:
    ModuleTemplate();
    ModuleTemplate(const ModuleTemplate &that);
    virtual ~ModuleTemplate();
};
}

#endif
