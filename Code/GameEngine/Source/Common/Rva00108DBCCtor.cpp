// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// Native unwind action76457B calls the existing base destructor10846E.
class Rva00108475 {
public:
 virtual ~Rva00108475();
 virtual void rva0010BE72()=0; virtual void *rva0010C065(void *)=0;
 virtual void *rva0010C145(void *,void *,bool,bool)=0; virtual void forward(unsigned,unsigned,unsigned)=0;
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned)=0;
};
class LightEnvironmentClass {
public: LightEnvironmentClass();
private: char body[0x228];
};
// The virtual view matches Rva0010C785Lifecycle.cpp (the destructor's unit),
// so both units emit the one vtable 0x7CF9C4 this constructor installs.
class W3DProjectedShadowManager : public Rva00108475 {
public:
 W3DProjectedShadowManager();
 __declspec(noinline) virtual ~W3DProjectedShadowManager();
 virtual void rva0010BE72(); virtual void *rva0010C065(void *) = 0;
 virtual void *rva0010C145(void *,void *,bool,bool) = 0; virtual void forward(unsigned,unsigned,unsigned) = 0;
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned) = 0;
 virtual unsigned dispatch(unsigned,void *,unsigned,unsigned) = 0;
private:
 unsigned m_04,m_08,m_0c,m_10,m_14,m_18,m_1c,m_20;
 LightEnvironmentClass m_light;
 unsigned m_24c,m_250,m_254,m_258,m_25c,m_260,m_264,m_268,m_26c,m_270;
};
W3DProjectedShadowManager::W3DProjectedShadowManager() {
 m_0c=0;m_04=0;m_08=0;m_10=0;m_14=0;m_18=0;m_1c=0;
 m_250=0;m_24c=0;m_20=0;m_254=0;m_258=0;m_25c=0;
 m_260=0;m_264=0;m_268=0;m_26c=0;m_270=0;
}
