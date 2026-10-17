// cl: /DNDEBUG /MD
//
// Destructor-only views of the five states constructed by the already matched
// TurretStateMachineCtor.cpp. Their names follow those constructor identities
// and the Zero Hour TurretAI.cpp semantic guide. Native evidence independently
// establishes their cleanup: each constructor installs the following vtable,
// whose slot zero is deleting destructor 4D8507, which calls 4D7B93.
//   Idle      ctor4D7B98 tableC607D8   IdleScan ctor4D7BBF tableC60830
//   Aim       ctor4D7BEA tableC60890   Recenter ctor4D7C0D tableC608F0
//   Hold      ctor4D7C30 tableC60950
// Native 4D7B93 is the complete five-byte tail to State::~State at49B47C.
// The latter is the canonical Snapshot lifetime fold. No state-specific
// resource teardown or separate complete-destructor address exists here.
//
// novtable applies only to this destructor context; the separate constructors
// continue to install their native tables. State's32-byte prefix and the three
// scalar tails at20 agree with those constructors; no full vtable or additional
// class layout is claimed by these views.

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class State : public Snapshot
{
public:
 virtual ~State();
private:
 unsigned char m_prefix04[0x20 - 4];
};

class __declspec(novtable) Rva004D7B70 : public State
{
public:
 virtual ~Rva004D7B70() {}
};

class __declspec(novtable) TurretAIIdleState : public Rva004D7B70
{
public:
 virtual ~TurretAIIdleState();
private:
 unsigned int m_nextIdleScan;
};

class __declspec(novtable) TurretAIIdleScanState : public Rva004D7B70
{
public:
 virtual ~TurretAIIdleScanState();
private:
 float m_desiredAngle;
};

class __declspec(novtable) TurretAIAimTurretState : public Rva004D7B70
{
public:
 virtual ~TurretAIAimTurretState();
};

class __declspec(novtable) TurretAIRecenterTurretState : public Rva004D7B70
{
public:
 virtual ~TurretAIRecenterTurretState();
};

class __declspec(novtable) TurretAIHoldTurretState : public Rva004D7B70
{
public:
 virtual ~TurretAIHoldTurretState();
private:
 unsigned int m_timestamp;
};

typedef char StatePrefixSize[(sizeof(State) == 0x20) ? 1 : -1];
typedef char IdleStateSize[(sizeof(TurretAIIdleState) == 0x24) ? 1 : -1];
typedef char IdleScanStateSize[(sizeof(TurretAIIdleScanState) == 0x24) ? 1 : -1];
typedef char AimStateSize[(sizeof(TurretAIAimTurretState) == 0x20) ? 1 : -1];
typedef char RecenterStateSize[(sizeof(TurretAIRecenterTurretState) == 0x20) ? 1 : -1];
typedef char HoldStateSize[(sizeof(TurretAIHoldTurretState) == 0x24) ? 1 : -1];

TurretAIIdleState::~TurretAIIdleState() {}
