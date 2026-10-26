#pragma once

// Scoped receiver shared by the matched collision and pool-key bodies.
// This retains the collision body's existing base/interface layout; it does
// not model the separate opaque constructor or emit a vtable.
class Object;
class ModuleData;
struct Coord3D;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
	virtual ~Module();
protected:
	const ModuleData *m_data;
};

class ObjectModule : public Module
{
protected:
	Object *m_object;
	Object *getObject() const { return m_object; }
};

class BehaviorModule : public ObjectModule
{
};

class BehaviorModuleInterface
{
public:
	virtual void anchor();
};

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *, const Coord3D *, const Coord3D *) = 0;
};

class CollideModule : public BehaviorModule,
	public BehaviorModuleInterface, public CollideModuleInterface
{
};

class SquishCollide : public CollideModule
{
public:
	virtual void onCollide(Object *, const Coord3D *, const Coord3D *);
	virtual NameKeyType getModuleNameKey() const;
};
