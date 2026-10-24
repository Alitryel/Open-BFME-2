// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /EHsc
// ?fetch@GameTextManager@@UAE?AVUnicodeString@@PBDPA_N@Z 0x002E5719 35B
// Evidence: vslot 15 offset 0x3C of vtable 0x00804FA8 class GameTextManager; forwards to slot 17 offset 0x44 then StringBase<G> copy 0x00037050
#include "unicode_string.h"

class GameTextManager
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists);
	virtual void slot16(void) = 0;
	virtual UnicodeString *slot17(const char *label, bool *exists) = 0;
};

UnicodeString GameTextManager::fetch(const char *label, bool *exists)
{
	return *slot17(label, exists);
}
