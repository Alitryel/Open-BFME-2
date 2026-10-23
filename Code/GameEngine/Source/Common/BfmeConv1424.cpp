// cl: /Od /Gy

class BfmeRegVLY
{
public:
	void bfmeInitVLY();
};

extern BfmeRegVLY g_bfmeRegVLY;

class BfmeThingVLY
{
public:
	BfmeThingVLY *bfmeCtorVLY();
};

BfmeThingVLY *BfmeThingVLY::bfmeCtorVLY()
{
	if (0)
		g_bfmeRegVLY.bfmeInitVLY();
	return this;
}


class BfmeRegVLZ
{
public:
	void bfmeInitVLZ();
};

extern BfmeRegVLZ g_bfmeRegVLZ;

class BfmeThingVLZ
{
public:
	BfmeThingVLZ *bfmeCtorVLZ();
};

BfmeThingVLZ *BfmeThingVLZ::bfmeCtorVLZ()
{
	if (1)
		g_bfmeRegVLZ.bfmeInitVLZ();
	return this;
}
// ?g_bfmeRegVLY@@3VBfmeRegVLY@@A: the global at VA 0xddf570 is ?_S_lock@?$_Node_Alloc_Lock@$0A@$0A@@_STL@@2VNodeAllocMutex@2@A.
#pragma comment(linker, "/alternatename:?g_bfmeRegVLY@@3VBfmeRegVLY@@A=?_S_lock@?$_Node_Alloc_Lock@$0A@$0A@@_STL@@2VNodeAllocMutex@2@A")
// ?g_bfmeRegVLZ@@3VBfmeRegVLZ@@A: the global at VA 0xddf574 is ?_S_lock@?$_Node_Alloc_Lock@$00$0A@@_STL@@2VNodeAllocMutex@2@A.
#pragma comment(linker, "/alternatename:?g_bfmeRegVLZ@@3VBfmeRegVLZ@@A=?_S_lock@?$_Node_Alloc_Lock@$00$0A@@_STL@@2VNodeAllocMutex@2@A")
