#ifndef BFME_SPECIAL_POWER_CREATE_VIEW_H
#define BFME_SPECIAL_POWER_CREATE_VIEW_H

// Scoped pool/callback receiver, preserving the callback's measured accesses:
// primary prefix 0x10, create interface at 0x10, flag at 0x14, Object modules
// at 0x244. The constructor's secondary table 0x008596A4 slot 1 identifies the
// callback. Neutral interface slots retain their existing unresolved names.
// The pool body does not inspect its receiver. Its primary virtual declaration
// completes this pair's method set, not the full retail table or constructor
// contract. Neither consumer instantiates this view or emits its vtable.
enum NameKeyType { NK_UNKNOWN = 0 };

class SpecialPowerBuildResult {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
};
class SpecialPowerModuleScanFace {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
 virtual SpecialPowerBuildResult *s8();
};
struct SpecialPowerModuleScan { unsigned char prefix[0xC]; SpecialPowerModuleScanFace face; };
class Object {
public: unsigned char prefix[0x244]; SpecialPowerModuleScan **modules;
};
struct SpecialPowerCreateHead {virtual void anchor();unsigned char prefix[4];Object *object;unsigned char tail[4];};
class SpecialPowerCreateFace {
public:
 virtual void s0();virtual void onBuildComplete();virtual void s2();virtual bool shouldDoCreate();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();
 virtual void s8();virtual void s9();virtual void s10();virtual void s11();
 virtual void s12();
};
class SpecialPowerCreate : public SpecialPowerCreateHead, public SpecialPowerCreateFace {
public:
 virtual void onBuildComplete();
 virtual NameKeyType getModuleNameKey() const;
 bool flag;
};

#endif
