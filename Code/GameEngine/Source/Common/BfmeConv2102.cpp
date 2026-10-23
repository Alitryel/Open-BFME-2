struct Gen009F5040Node
{
};

class BfmeThingZU
{
public:
	void bfmeUnhookZU();
};

class BfmeThingYQ
{
public:
	virtual void bfmeV0YQ() = 0;
	virtual void bfmeV1YQ() = 0;
	virtual void bfmeV2YQ() = 0;
	virtual void bfmeV3YQ() = 0;
	virtual void bfmeV4YQ() = 0;
	virtual void bfmeClearYQ(int flag) = 0;
	virtual Gen009F5040Node *bfmeTakeYQ() = 0;
};

class PartitionManagerImpl
{
public:
	void remove(Gen009F5040Node *n);
	void bfmeDropYQ(BfmeThingYQ *t);
};

void PartitionManagerImpl::bfmeDropYQ(BfmeThingYQ *t)
{
	if (t == 0)
		return;

	Gen009F5040Node *n = t->bfmeTakeYQ();

	if (n == 0)
		return;

	remove(n);
	t->bfmeClearYQ(0);
	((BfmeThingZU *)n)->bfmeUnhookZU();

	::operator delete(n);
}
