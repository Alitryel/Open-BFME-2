// Retail observer tables have four callbacks and nonvirtual teardown.
#ifndef LIVING_WORLD_OBSERVERS_H
#define LIVING_WORLD_OBSERVERS_H

class Rva004E06FBPtrChase32Field;
struct Rva004EF2ABArg;

class LivingWorldBuildingObserver
{
public:
	~LivingWorldBuildingObserver() {}
	virtual void event1_0(Rva004E06FBPtrChase32Field *) {}
	virtual void event1_1(int) {}
	virtual void NotifyBuildingAboutToBeDestroyedByUI(int) {}
	virtual void event1_3(const Rva004E06FBPtrChase32Field *, int) {}
};

class LivingWorldRegionObserver
{
public:
	~LivingWorldRegionObserver() {}
	virtual void event4_0(int, int, int) {}
	virtual void event4_1(int, int, int) {}
	virtual void event4_2(int, int) {}
	virtual void event4_3(int, int) {}
};

class LivingWorldPlayerObserver
{
public:
	~LivingWorldPlayerObserver() {}
	virtual void event5_0(Rva004EF2ABArg *) {}
	virtual void event5_1(int, int, int) {}
	virtual void event5_2(int, int, int) {}
	virtual void event5_3(int) {}
};

#endif
