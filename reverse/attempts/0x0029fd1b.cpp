// ?rva0029FD1B@InGameUI@@QAEXHPAVMaterialPassClass@@PAVOverridable@@H@Z
// partial score=0.781467 date=2026-10-14
// ?rva0029FD1B@InGameUI@@QAEXHPAVMaterialPassClass@@PAVOverridable@@H@Z
// partial score=0.752 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0029FD1B@InGameUI@@QAEXHPAVMaterialPassClass@@PAVOverridable@@H@Z
// @0x0029FD1B 387B, retail-guided InGameUI radius decal.
class Object;
class Player;
class MaterialPassClass;
class Overridable;
class RadiusDecalTemplate;
class Shadow;

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Player
{
public:
	Object *findNaturalCommandCenter();
	Object *rva002AC629();
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Shadow
{
public:
	void rva00330995(int color);
};

struct Coord3D { float x, y, z; };

struct Rva0029FD1BNode
{
	char m_pad00[8];
	RadiusDecalTemplate *m_template; // +0x08
};

class TextureClass;
class MaterialPassClass
{
public:
	TextureClass *Peek_Texture(int arg) const;
};
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};
class RadiusDecal {};
class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &pos, float radius, const Player *player, RadiusDecal &decal) const;
};

class InGameUI
{
public:
	void rva0029FD1B(int id, MaterialPassClass *mp, Overridable *ov, int arg3);
protected:
	void handleRadiusCursor();
public:
#define BFME_V8(a,b,c,d,e,f,g,h) virtual void v##a(); virtual void v##b(); virtual void v##c(); virtual void v##d(); virtual void v##e(); virtual void v##f(); virtual void v##g(); virtual void v##h();
	BFME_V8(00,01,02,03,04,05,06,07) BFME_V8(08,09,10,11,12,13,14,15)
	BFME_V8(16,17,18,19,20,21,22,23) BFME_V8(24,25,26,27,28,29,30,31)
	BFME_V8(32,33,34,35,36,37,38,39) BFME_V8(40,41,42,43,44,45,46,47)
	BFME_V8(48,49,50,51,52,53,54,55) BFME_V8(56,57,58,59,60,61,62,63)
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69();
	virtual bool v70();
	virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void *v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79(); virtual void v80();
	virtual void v81();
#undef BFME_V8
private:
	char m_pad000[0x238];
	void *m_238; // +0x238
	char m_pad23C[0x874 - 0x23C];
	char m_hashtable[0x888 - 0x874]; // +0x874
	int m_888;   // +0x888
	RadiusDecal m_curRadiusCursor; // +0x88C
	Shadow *m_890; // +0x890
	int m_894;
	int m_898;
	int m_89C; // +0x89C
};

void *rva002888D4(void *table, int *key);


void InGameUI::rva0029FD1B(int id, MaterialPassClass *mp, Overridable *ov, int arg3)
{
	if (m_888 != (id ? id : id))
	{
		v81();
		Rva0029FD1BNode *node = (Rva0029FD1BNode *)rva002888D4(m_hashtable, &id);
		if (!node)
			return;

		Object *obj = 0;
		if (m_238)
		{
			int t = *(int *)((char *)m_238 + 0x14);
			if (t == 0x20)
			{
				Player *p = ThePlayerList ? ThePlayerList->m_localPlayer : 0;
				if (p)
					obj = p->findNaturalCommandCenter();
			}
			else if (t == 0x26)
			{
				Player *p = ThePlayerList ? ThePlayerList->m_localPlayer : 0;
				if (p)
					obj = p->rva002AC629();
			}
		}
		if (!obj)
		{
			if (!v70())
				return;
			void *v = v75();
			if (!v)
				return;
			obj = *(Object **)((char *)v + 0xFC);
			if (!obj)
				return;
		}
		{
		Player *pl = obj->getControllingPlayer();
		if (!pl)
			return;

		float radius;
		if (id == m_89C)
		{
			TextureClass *tex = mp->Peek_Texture(arg3);
			if (tex)
			{
				float *f = *(float **)((char *)tex + 4);
				radius = f[0x34 / 4] + (obj ? f[0x38 / 4] : f[0x38 / 4]);
			}
			else
				radius = 0.0f;
		}
		else
		{
			if (!ov)
				return;
			const Overridable *fo = ov->friend_getFinalOverride();
			radius = *(float *)((char *)fo + 0x54);
		}
		if (radius <= 0.0f)
			return;

		Coord3D pos;
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
		node->m_template->createRadiusDecal(pos, radius, pl, m_curRadiusCursor);
		}
		m_888 = id;
		this->handleRadiusCursor();
	}

	int color = arg3 ? -1 : (int)0xFFFF1414;
	if (m_890)
		m_890->rva00330995(color);
}
