// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class RenderObjClass;

// scene.h's four pure iterator slots follow the dtor, as in scene.cpp's copy of
// the table (first in link order).
class SceneIterator
{
public:
	virtual ~SceneIterator() {}
	virtual void First(void) = 0;
	virtual void Next(void) = 0;
	virtual bool Is_Done(void) = 0;
	virtual RenderObjClass *Current_Item(void) = 0;
};

template <class T> class RefMultiListClass
{
public:
	void *m_unused[2];
	void *m_first;
};

class SimpleSceneClass;

class __declspec(novtable) SimpleSceneIterator : public SceneIterator
{
public:
	virtual ~SimpleSceneIterator() {}
	virtual void First(void);
	virtual void Next(void);
	virtual bool Is_Done(void);
	virtual RenderObjClass *Current_Item(void);

protected:
	SimpleSceneIterator(RefMultiListClass<RenderObjClass> *render_list) :
		m_render_list(render_list),
		m_current(render_list->m_first)
	{
	}

private:
	RefMultiListClass<RenderObjClass> *m_render_list;
	void *m_current;

	friend class SimpleSceneClass;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual SceneIterator *Create_Iterator();

private:
	unsigned char m_before_render_list[0x58];
	RefMultiListClass<RenderObjClass> m_render_list;
};

SceneIterator *SimpleSceneClass::Create_Iterator()
{
	return new SimpleSceneIterator(&m_render_list);
}
