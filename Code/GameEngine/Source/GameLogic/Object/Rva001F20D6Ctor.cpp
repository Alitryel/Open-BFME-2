// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/ocls /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// ??0Rva001F20D6@@QAE@IABV?$allocator@H@_STL@@@Z @0x001F20D6 69B:
// Single-proxy count ctor: two pointers at +0/+4 plus
// _STLP_alloc_proxy<unsigned int,int,allocator<int> > at +8 via rowed
// 0x0014F3C4 with (alloc 0) then count*4 bytes via rowed
// allocator<char>::allocate 0x000307F0 with zero-count guard.
// Evidence: unlock lane; caller 0x001F206E vector copy path;
// neighbours ObjectCreationList 0x001F1609 and 0x001F311B share flags.
#include <deque>
class Rva001F20D6
{
public:
    Rva001F20D6(unsigned int n, const _STL::allocator<int> &a);
private:
    void *m_start;
    void *m_finish;
    _STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_end;
};
Rva001F20D6::Rva001F20D6(unsigned int n, const _STL::allocator<int> &a)
    : m_start(0), m_finish(0), m_end(a, 0)
{
    void *tmp = m_finish;
    if (n != 0)
        tmp = (void *)_STL::allocator<char>::allocate(n * sizeof(int), 0);
    else
        tmp = 0;
    m_start = tmp;
    m_finish = tmp;
    m_end._M_data = (unsigned int)((char *)tmp + n * sizeof(int));
}

// Native1F206E and its creator/consumer1F1634/1F2F0E use this storage for
// four-byte Object pointers; 1F2F0E dereferences entries through Object::findModule.
// The existing neutral count constructor above and this typed STLport form
// reproduce the same complete69B body. Expand the allocator byte-count path
// as retail does; preserve the zero-count branch and proxy at +8.

#include <vector>
class Object;
namespace _STL {
template<> _Vector_base<Object*,allocator<Object*> >::_Vector_base(unsigned int n,const allocator<Object*>&a)
 : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {
 void* tmp=_M_finish;
 if(n!=0) tmp=(void*)allocator<char>::allocate(n*sizeof(Object*),0); else tmp=0;
 _M_start=(Object**)tmp;_M_finish=(Object**)tmp;
 _M_end_of_storage._M_data=(Object**)((char*)tmp+n*sizeof(Object*));
}
}
template _STL::_Vector_base<Object*,_STL::allocator<Object*> >::_Vector_base(unsigned int,const _STL::allocator<Object*>&);

// Native1F206E returns the empty Object allocator through retail21983A.
template _STL::allocator<Object*> _STL::vector<Object*>::get_allocator() const;
