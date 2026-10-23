// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva004A1950@Rva004A1950@@UAEXXZ @0x004A1950 45B
// A virtual of the module whose vtable at 0x00C51F30 also carries the
// SlavedUpdate name getter 0x004A18BA, its pool key 0x004A1875 and the
// deleting destructor 0x004A1926 (target evidence). When the float at +0x34 of
// the module data (+0x04) is positive, the owning object (+0x08) gains
// model-condition bit 94 (word 2 of the +0x10C condition words, mask
// 0x40000000) and the rowed notifier 0x0028AE6D runs, tail-called. WB's twin
// (0x0090C460) is an empty stub, so the names stay address-derived.
//
// Codegen: the test reads the word through the module's object pointer and
// the update writes it through a reference to the same word; with one view
// cl 7.1 hoists the word address into a register, where retail keeps the
// mask in EAX and both accesses as [ecx+0x114].

class Object
{
public:
	void rva0028AE6D();				// 0x0028AE6D, model-condition notifier
	unsigned char m_pad00[0x10C];
	unsigned int m_modelConditionWords[10];		// +0x10C
};

struct Rva004A1950Data
{
	unsigned char m_pad00[0x34];
	float m_34;					// +0x34
};

class Rva004A1950
{
public:
	virtual void rva004A1950();

private:
	Rva004A1950Data *m_data;			// +0x04
	Object *m_object;				// +0x08
};

void Rva004A1950::rva004A1950()
{
	if (m_data->m_34 > 0.0f) {
		Object *obj = m_object;
		unsigned int &word = obj->m_modelConditionWords[2];
		if (!(m_object->m_modelConditionWords[2] & 0x40000000)) {
			word |= 0x40000000;
			obj->rva0028AE6D();
		}
	}
}
