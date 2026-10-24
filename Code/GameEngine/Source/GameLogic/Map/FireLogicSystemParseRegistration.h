#pragma once
// Native DBB750 object: vptr BFB730, use count at +4, total8 bytes.
// BFB730 has one by-value getter at286356; it has no virtual destructor.
// The composed wrapper preserves the existing global symbol and emits no
// additional table. Evidence: firelogic-lifetime-link-20261024/readme.md.
class Rva003ED658;
struct Rva00285D27Count
{
    unsigned int m_useCount;
    Rva00285D27Count() : m_useCount(0) {}
};
class Rva00285D27 : public Rva00285D27Count
{
public:
    Rva00285D27();
    virtual Rva003ED658 rva00286356();
};
struct FireLogicSystemParseRegistration
{
    Rva00285D27 m_registration;
};
extern FireLogicSystemParseRegistration theFireLogicSystemParseRegistration;
