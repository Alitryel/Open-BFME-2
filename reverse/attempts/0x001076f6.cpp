// ?rva001076F6@W3DVolumetricShadowManagerV2@@QAEXXZ
// partial score=0.8804 date=2026-10-14
// ?rva001076F6@W3DVolumetricShadowManagerV2@@QAEXXZ
// partial score=0.859196 date=2026-10-14
// ?rva001076F6@W3DVolumetricShadowManagerV2@@QAEXXZ
// partial score=0.775 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva001076F6@W3DVolumetricShadowManagerV2@@QAEXXZ @0x001076F6 367B,
// retail-guided: bind the manager's vertex/index buffers, install the preset
// material and shader, reset the identity texture matrix, then apply the DX8
// render states and issue the two manager virtuals.
void *rva0013D230(int preset);
void rva000662E5(const void *shader);
void rva0011D4A0(const void *buf, int zero);
void rva0011D530(const void *buf, int zero);
void rva0011D930();
void rva0006615F(int state, int value);
class RefCounted
{
public:
	virtual void Release();
	int m_refs; // +0x04
};

class W3DVolumetricShadowManagerV2
{
public:
	void rva001076F6();
private:
	void *m_vertexBuffer; // +0x00
	void *m_indexBuffer;  // +0x04
};


void W3DVolumetricShadowManagerV2::rva001076F6()
{
	void *m = rva0013D230(0);
	if (m)
		((RefCounted *)m)->m_refs++;

	RefCounted *old = *(RefCounted **)0x00DEE5DC;
	if (old)
	{
		old->m_refs--;
		if (old->m_refs == 0)
			old->Release();
	}
	*(unsigned char *)0x00DEC4F5 |= 0x40;
	*(void **)0x00DEE5DC = m;
	if (m && --((RefCounted *)m)->m_refs == 0)
		((RefCounted *)m)->Release();

	rva000662E5((const void *)0x00DB5E98);
	rva0011D4A0(m_vertexBuffer, 0);
	rva0011D530(m_indexBuffer, 0);

	if ((*(unsigned char *)0x00DEC4F6 & 4) == 0)
	{
		*(unsigned int *)0x00DEC4F4 |= 0x40001;
		((float *)0x00DEE7C4)[0] = 1.0f; ((float *)0x00DEE7C4)[1] = 0.0f; ((float *)0x00DEE7C4)[2] = 0.0f; ((float *)0x00DEE7C4)[3] = 0.0f;
		((float *)0x00DEE7C4)[4] = 0.0f; ((float *)0x00DEE7C4)[5] = 1.0f; ((float *)0x00DEE7C4)[6] = 0.0f; ((float *)0x00DEE7C4)[7] = 0.0f;
		((float *)0x00DEE7C4)[8] = 0.0f; ((float *)0x00DEE7C4)[9] = 0.0f; ((float *)0x00DEE7C4)[10] = 1.0f; ((float *)0x00DEE7C4)[11] = 0.0f;
		((float *)0x00DEE7C4)[12] = 0.0f; ((float *)0x00DEE7C4)[13] = 0.0f; ((float *)0x00DEE7C4)[14] = 0.0f; ((float *)0x00DEE7C4)[15] = 1.0f;
	}

	rva0011D930();
	rva0006615F(0x34, 1);
	rva0006615F(0x38, 8);
	int v = *(int *)(*(int *)0x00DE5DFC + 8);
	rva0006615F(0x3A, -1);
	rva0006615F(0x3B, ~v);

	void *obj = *(void **)0x00DEDA34;
	int *vt = *(int **)obj;
	((void (__stdcall *)(void *, int))vt[0x170 / 4])(obj, 0);
	++*(int *)0x00DEDA98;
	obj = *(void **)0x00DEDA34;
	vt = (m_indexBuffer ? (*(int **)obj) : (*(int **)obj));
	((void (__stdcall *)(void *, int))vt[0x164 / 4])(obj, 2);
	++*(int *)0x00DEDA98;
}
