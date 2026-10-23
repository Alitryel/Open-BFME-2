// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
//
// ?rva00496E05@BannerCarrierUpdate@@QAEXPAX_N@Z, retail 0x00496E05 (299B, ret 8).
// BannerCarrierUpdate's morph step for one banner-carrier entry (its name is
// the AsciiString at entry +0x64): look up the entry's model-condition set in
// the module data (rowed 0x00496D43), clear every morph condition (a
// function-static mask built once from the 81-entry table at 0x00C4F6E0)
// while setting that set on the object (rowed Object::rva0028CFB2), refresh
// the object's shroud when it has a non-zero position, play the module
// data's +0x30 FX when asked, and switch the AI to the entry's locomotor set
// when the module data names one (rowed 0x00496DA3, the INI index worker
// 0x0002BCAB over TheLocomotorSetNames, AI virtual slot 0x238).
//
// Evidence (target): the ret 8 and this layout (+4 module data, +8 object),
// the static guard 0x00E03AC4 / mask 0x00E03A78 (memset 0x4C) / init byte
// 0x00E03A70, the table values read from retail .rdata, every call rowed.
// The entry's type and the method's name are not established.

#include <string.h>
#include "ascii_string.h"
#include "Lib/Coord3D.h"

// A 19-word model-condition mask; the zeroing constructor is the mask
// form, the bare words are what the set lookup fills in place.
struct BannerMorphConditionBits
{
	int m_bits[19];
};

struct BannerMorphConditionMask : public BannerMorphConditionBits
{
	BannerMorphConditionMask() { memset(m_bits, 0, sizeof(m_bits)); }
	void set(unsigned int bit) { m_bits[bit >> 5] |= 1 << (bit & 0x1F); }
};

class AIUpdateInterface
{
public:
#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
	SLOT08(v00,v01,v02,v03,v04,v05,v06,v07) SLOT08(v08,v09,v0A,v0B,v0C,v0D,v0E,v0F)
	SLOT08(v10,v11,v12,v13,v14,v15,v16,v17) SLOT08(v18,v19,v1A,v1B,v1C,v1D,v1E,v1F)
	SLOT08(v20,v21,v22,v23,v24,v25,v26,v27) SLOT08(v28,v29,v2A,v2B,v2C,v2D,v2E,v2F)
	SLOT08(v30,v31,v32,v33,v34,v35,v36,v37) SLOT08(v38,v39,v3A,v3B,v3C,v3D,v3E,v3F)
	SLOT08(v40,v41,v42,v43,v44,v45,v46,v47) SLOT08(v48,v49,v4A,v4B,v4C,v4D,v4E,v4F)
	SLOT08(v50,v51,v52,v53,v54,v55,v56,v57) SLOT08(v58,v59,v5A,v5B,v5C,v5D,v5E,v5F)
	SLOT08(v60,v61,v62,v63,v64,v65,v66,v67) SLOT08(v68,v69,v6A,v6B,v6C,v6D,v6E,v6F)
	SLOT08(v70,v71,v72,v73,v74,v75,v76,v77) SLOT08(v78,v79,v7A,v7B,v7C,v7D,v7E,v7F)
	SLOT08(v80,v81,v82,v83,v84,v85,v86,v87)
	virtual void v88(); virtual void v89(); virtual void v8A(); virtual void v8B();
	virtual void v8C(); virtual void v8D();
	virtual void chooseLocomotorSet(int set);
#undef SLOT08
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void rva0028CFB2(const int *clearFlags, const int *setFlags);
	void updateShroudNow();
private:
	char m_pad000[0x38];
	Coord3D m_position;        // +0x38
	char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;   // +0x258
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

// The module data's set lookup (rowed under this receiver spelling).
class Rva00496D43
{
public:
	void *rva00496D43(void *out, const AsciiString &key);
};

class BannerCarrierUpdateModuleData
{
public:
	AsciiString rva00496DA3(const AsciiString &name) const;
	const FXList *getFX() const { return m_fx; }
private:
	char m_pad00[0x30];
	const FXList *m_fx; // +0x30
};

extern "C" int rva002bcab_scanIndex(const char *token, const char *const *nameList, bool *found, bool doThrow);
extern const char *TheLocomotorSetNames[];

class BannerCarrierUpdate
{
public:
	void rva00496E05(void *entry, bool playFX);
private:
	void *m_vtable;
	BannerCarrierUpdateModuleData *m_moduleData; // +0x04
	Object *m_object;                            // +0x08
};

static const unsigned int s_morphConditions[81] =
{
	214, 194, 195, 196, 197, 198, 184, 185, 186, 187, 188, 458,
	459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470,
	471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482,
	483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494,
	495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506,
	507, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518,
	519, 520, 521, 522, 523, 524, 525, 526, 527
};

// ?rva00496E05@BannerCarrierUpdate@@QAEXPAX_N@Z @0x00496E05
void BannerCarrierUpdate::rva00496E05(void *entry, bool playFX)
{
	Object *obj = m_object;
	BannerCarrierUpdateModuleData *bannerCarrierUpdateModuleData = m_moduleData;
	const AsciiString &name = *(const AsciiString *)((char *)entry + 0x64);

	BannerMorphConditionBits setFlags;
	((Rva00496D43 *)bannerCarrierUpdateModuleData)->rva00496D43(&setFlags, name);

	static BannerMorphConditionMask s_clearFlags;
	static bool s_clearFlagsBuilt = false;
	if (!s_clearFlagsBuilt)
	{
		s_clearFlagsBuilt = true;
		for (unsigned int i = 0; i < sizeof(s_morphConditions) / sizeof(s_morphConditions[0]); ++i)
			s_clearFlags.set(s_morphConditions[i]);
	}
	obj->rva0028CFB2(s_clearFlags.m_bits, setFlags.m_bits);

	if (obj->getPosition()->GetLength() > 0.0f)
		obj->updateShroudNow();

	if (bannerCarrierUpdateModuleData->getFX() && playFX)
		FXList::doFXObj(bannerCarrierUpdateModuleData->getFX(), obj, 0);

	AsciiString locomotor = bannerCarrierUpdateModuleData->rva00496DA3(name);
	if (!locomotor.isEmpty())
	{
		bool found = false;
		int set = rva002bcab_scanIndex(locomotor.str(), TheLocomotorSetNames, &found, true);
		obj->getAI()->chooseLocomotorSet(set);
	}
}
