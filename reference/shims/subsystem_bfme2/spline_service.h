// Retail subsystem contracts from tables 0x00BD77A0 and 0x00BE7150.
// Consumers supply the registry layout separately.
#ifndef BFME2_SPLINE_SERVICE_H
#define BFME2_SPLINE_SERVICE_H

#include "ascii_string.h"

class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
    virtual void init() = 0;
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad() {}
    virtual bool vslot04(int) { return false; }
    virtual bool vslot05() { return false; }
    virtual int vslot06() { return 0; }
    virtual void vslot07(int) {}
    virtual void vslot08() {}
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual bool vslot11(int) { return false; }
    virtual void vslot12() {}
    virtual void vslot13(int) {}

    SubsystemInterface(const SubsystemInterface &that);
    void setName(AsciiString name);
    bool m_flag;
    AsciiString m_name;
};

class Rva0022B3F6Subsystem : public SubsystemInterface
{
public:
#ifdef BFME2_SPLINE_INLINE_CTOR
    __declspec(dllimport) __forceinline Rva0022B3F6Subsystem() {}
#else
    Rva0022B3F6Subsystem();
#endif
    virtual ~Rva0022B3F6Subsystem();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}
};

#endif
