// cl: /O2 /G6 /MD
//
// _VP6_PickPostProcessingLevel, retail 0x001B5AC0..0x001B5C53 (404 bytes), cdecl.
// Clean room: reverse/vp6_cleanroom/specs/001b5ac0.md plus retail only.
// Field names are descriptive labels from the spec text.

struct VP6TimingInstance
{
	unsigned char pad000[0x1A0];
	int level;							// +0x1A0 current post-processing level
	unsigned char pad1A4[0x1A8 - 0x1A4];
	unsigned int cpuFree;				// +0x1A8 CPU-free percentage
	unsigned char pad1AC[0x910 - 0x1AC];
	int thisFrameDecodeTime;			// +0x910
	int averageDecodeTime;				// +0x914
	int averagePostProcTime[10];		// +0x918 indexed by level
	int averageBlitTime;				// +0x940
};

extern "C" int __cdecl VP6_PickPostProcessingLevel(VP6TimingInstance *pbi)
{
	int baselineCost = pbi->thisFrameDecodeTime + pbi->averagePostProcTime[8] + pbi->averageBlitTime;
	int projectedCost = baselineCost + pbi->averagePostProcTime[pbi->level];
	int averageCost = pbi->averageDecodeTime + pbi->averageBlitTime;

	if (pbi->averagePostProcTime[6] == 0)
		pbi->averagePostProcTime[6] = averageCost >> 1;
	if (pbi->averagePostProcTime[5] == 0)
		pbi->averagePostProcTime[5] = averageCost >> 1;
	if (pbi->averagePostProcTime[4] == 0)
		pbi->averagePostProcTime[4] = averageCost >> 2;
	if (pbi->averagePostProcTime[8] == 0)
		pbi->averagePostProcTime[8] = averageCost >> 3;

	if (pbi->cpuFree == 0)
		return pbi->level;

	if (projectedCost > (int)(31000 * pbi->cpuFree / 100))
	{
		unsigned int criticalWatermark = 31000 * pbi->cpuFree / 100;

		pbi->averageDecodeTime = pbi->thisFrameDecodeTime;
		if ((unsigned int)(pbi->averagePostProcTime[6] + baselineCost) < criticalWatermark)
			return 6;
		if ((unsigned int)(pbi->averagePostProcTime[5] + baselineCost) < criticalWatermark)
			return 5;
		if ((unsigned int)(pbi->averagePostProcTime[4] + baselineCost) < criticalWatermark)
			return 4;
		if ((unsigned int)(pbi->averagePostProcTime[8] + baselineCost) < criticalWatermark)
			return 8;
		return 0;
	}

	if (projectedCost < (int)(30000 * pbi->cpuFree / 100) && projectedCost > (int)(28000 * pbi->cpuFree / 100))
		return pbi->level;

	unsigned int upperWatermark = 28000 * pbi->cpuFree / 100;

	if ((unsigned int)(pbi->averagePostProcTime[6] + averageCost) < upperWatermark)
		return 6;
	if ((unsigned int)(pbi->averagePostProcTime[5] + averageCost) < upperWatermark)
		return 5;
	if ((unsigned int)(pbi->averagePostProcTime[4] + averageCost) < upperWatermark)
		return 4;
	if ((unsigned int)(pbi->averagePostProcTime[8] + averageCost) < upperWatermark)
		return 8;
	return 0;
}
