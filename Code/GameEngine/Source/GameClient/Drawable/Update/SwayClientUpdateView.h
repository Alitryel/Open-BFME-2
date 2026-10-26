// Shared receiver for the matched sway update, pool-key and transfer bodies.
// Member offsets are measured by those bodies and the existing 0x2C-byte ctor.
// This partial view does not describe the complete retail virtual-slot order;
// no constructor or destructor is defined through it.
#ifndef BFME_SWAY_CLIENT_UPDATE_VIEW_H
#define BFME_SWAY_CLIENT_UPDATE_VIEW_H

class Drawable;
class ModuleData;
class Xfer;

enum NameKeyType { NK_UNKNOWN = 0 };

class Module
{
public:
	virtual ~Module();

private:
	const ModuleData *m_moduleData; // +0x04
};

class DrawableModule : public Module
{
protected:
	Drawable *getDrawable() const { return m_drawable; }

private:
	Drawable *m_drawable; // +0x08
};

class ClientUpdateModule : public DrawableModule
{
public:
	virtual void clientUpdate() = 0;
};

class SwayClientUpdate : public ClientUpdateModule
{
public:
	virtual void clientUpdate();
	virtual NameKeyType getModuleNameKey() const;

	void stopSway() { m_swaying = false; }

protected:
	float m_curValue; // +0x0C
	float m_curAngle; // +0x10
	float m_curDelta; // +0x14
	float m_curAngleLimit; // +0x18
	float m_leanAngle; // +0x1C
	short m_curVersion; // +0x20
	bool m_swaying; // +0x22
	bool m_unused; // +0x23
	float m_directionSin; // +0x24
	float m_directionCos; // +0x28

	void updateSway();

	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

#endif
