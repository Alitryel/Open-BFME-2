// cl: /MD /EHsc /DNDEBUG
// Native 36247C (23B) and 362D25 (65B). The first pointer is the real
// GlowMaterial vtable C16FE8, not the four-byte string "s.v" formerly used.
// Keep both constructors visible: retail preserves EDX/XMM0 across the
// embedded material constructor and clears the color after that call.
#include "../../GameClient/BuffManager.h"

GlowMaterial::GlowMaterial() throw() : m_04(0), m_08(0), m_0C(0), m_10(0) {}
BuffInstance::BuffInstance() throw()
    : m_active(false), m_type(0), m_subType(0), m_duration(0),
      m_frameLimit(0), m_glow(0), m_thing(0), m_intensity(0.0f)
{
    m_color.red=0.0f; m_color.green=0.0f; m_color.blue=0.0f;
}
