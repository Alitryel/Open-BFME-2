// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Script@@MAE@XZ, retail 0x003B35B1 (177 bytes): Script::~Script.
//
// Target facts (retail bytes + vtable 0x00C1F424 + unwind evidence):
// - The body re-stores vtable 0x00C1F424, so this is Script's own destructor
//   (protected virtual: MAE), called by the slot-0 scalar deleting
//   destructor 0x003B41F8. It ends by restoring the Snapshot base vtable
//   0x00BBB554 (see the matching Script dtor family: the Condition/Action
//   dtors in ScriptConditionActionDtors.cpp restore their own tables the
//   same way).
// - Members released: the owned pointer at +0x30, the two-element owned
//   array at +0x34, and AsciiString members at +0x04/+0x08/+0x0C, at +0x0C
//   of the 16-byte subrecord at +0x10, and at +0x44. Member names and the
//   subrecord shape follow the TU-local Script view in
//   ScriptWriteDataChunk.cpp (m_text0/1/2, Rva003B3536 m_subrecord,
//   m_condition, m_actions[2], m_runtimeName44); the untouched middle
//   regions stay padding.
// - Each owned pointer is released through its slot-0 virtual with flag 0
//   and the returned block goes to the global operator delete, including
//   for null (xor + push + call): `::operator delete(p ? p->v0(0) : 0)`.
//   The Zero Hour donor (Scripts.cpp) calls deleteInstance() at the same
//   sites; ScriptConditionActionDtors.cpp proves the BFME 2 lowering, where
//   `::delete` through the virtual destructor emits the identical
//   push-0-vcall-then-operator-delete shape. Rva003B35B1Owned models that
//   slot-0 callee (OrCondition/ScriptAction per the WriteDataChunk view);
//   the vcall bytes carry no static-type information.
// - Base: the real Snapshot header (inline dtor, three pure slots, no
//   undefined refs); the EH states match the string members above.

#include "ascii_string.h"
class Xfer;
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva003B35B1Owned
{
public:
	virtual void *v0(int x);
};
void __cdecl operator delete(void *p);

struct Rva003B3536
{
	bool a, b;
	int value;
	bool c;
	AsciiString name;
};

class __declspec(novtable) Script : public Snapshot
{
public:
	// Full interface per the ScriptWriteDataChunk.cpp view (Script(),
	// duplicate, parse, loadPostProcess, GetSnapshotName, xfer); only the
	// destructor is defined here, so the remaining slots stay __purecall
	// and this TU emits no undefined refs.
protected:
	virtual ~Script();
	virtual const char *GetSnapshotName() const;
private:
	AsciiString m_text0, m_text1, m_text2;	// +0x04/+0x08/+0x0C
	Rva003B3536 m_subrecord;		// +0x10 (string name at +0x1C)
	char m_pad20[0x10];			// +0x20: m_delay, m_mask, m_active..m_flag (untouched)
	Rva003B35B1Owned *m_condition;		// +0x30 (OrCondition per writer view)
	Rva003B35B1Owned *m_actions[2];		// +0x34 (ScriptAction per writer view)
	char m_pad3C[0x08];			// +0x3C: m_frame, m_currentActive, m_otherFlag (untouched)
	AsciiString m_runtimeName44;		// +0x44
	float m_conditionTime, m_currentTime;	// (untouched)
	int m_conditionExecutedCount;		// (untouched)
};

// ?GetSnapshotName@Script@@MBEPBDXZ: slot 2 of vtable 0x00C1F424.
// The ledger rowed this body at 0x003B3662 under the placeholder name
// ?name@Rva003B3662Named@@QBEPBDXZ (SubsystemNameGetters4.cpp); the rename
// moves the definition here so the Script link can resolve it by its real
// name. Six bytes: mov eax,offset "Script" / ret.
const char *Script::GetSnapshotName() const
{
	return "Script";
}

// ??1Script@@MAE@XZ present-unmatched
Script::~Script()
{
	::operator delete(m_condition ? m_condition->v0(0) : 0);
	Rva003B35B1Owned **pp = m_actions;
	int i = 2;
	int *pi = &i;
	(void)pi;
	do {
		Rva003B35B1Owned *p = *pp;
		::operator delete(p ? p->v0(0) : 0);
		++pp;
	} while (--i);
}
