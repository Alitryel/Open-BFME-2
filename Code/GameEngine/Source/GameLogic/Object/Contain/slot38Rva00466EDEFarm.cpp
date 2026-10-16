// ?slot38@TransportContain@@UAE_NPAVObject@@HH@Z
// cl: /O1 /G7 /MD /DNDEBUG /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
enum ObjectStatusTypes { STATUS_62=62 };
enum KindOfType { KIND_NONE=0 };
class Object;
template<int N> class Rva00466EDESlots:public Rva00466EDESlots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00466EDESlots<1> { public: virtual void gap(char (*)[1]); };
struct Rva00466EDEPair { int unknown; const _STL::list<Object *> *list; };
class Rva00466EDEContained:public Rva00466EDESlots<5> { public: virtual bool slot5(); };
class Rva00466EDEListView:public Rva00466EDESlots<70> { public: virtual void slot70(Rva00466EDEPair *); };
class Rva00466EDECount:public Rva00466EDESlots<69> { public: virtual unsigned slot69(int); };
class Rva00466EDEMax:public Rva00466EDESlots<28> { public: virtual unsigned slot28(); };
class Object { public:
    bool testStatus(ObjectStatusTypes) const;
    bool isKindOf(KindOfType) const;
    int rva0028FBBE();
    char unknown00[4]; const unsigned char *type;
    char unknown08[0x250-8]; Rva00466EDEContained *contain;
};
class OpenContain { public: virtual bool isValidContainerFor(Object *,bool,bool); };
struct Rva00466EDEData { char unknown00[0x13D]; unsigned char flag13D; char unknown13E[0x14C-0x13E]; int ownerBit; };
class TransportContain:public Rva00466EDESlots<38> {
public:
    virtual bool slot38(Object *,int,int);
    __forceinline Rva00466EDEData *moduleData() const { return *reinterpret_cast<Rva00466EDEData *const *>(reinterpret_cast<const char *>(this)-0x1C); }
    __forceinline Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x18); }
    __forceinline unsigned count() { return reinterpret_cast<Rva00466EDECount *>(this)->slot69(0); }
    __forceinline unsigned maximum() { return reinterpret_cast<Rva00466EDEMax *>(this)->slot28(); }
    __forceinline unsigned extraSlots() const { return m_extraSlotsInUse; }
    char m_pad04[0xE0-4];
    unsigned m_extraSlotsInUse;	// +0xE0
};
bool TransportContain::slot38(Object *rider,int checkCapacity,int trailing)
{
    Rva00466EDEData *data=moduleData();
    if (!rider)
        return false;
    else {
        if (rider->testStatus(STATUS_62))
            return false;
        int required=data->ownerBit;
        if (required!=-1 && !object()->isKindOf(static_cast<KindOfType>(required)))
            return false;
            Rva00466EDEContained *const &contained=rider->contain;
            if (contained && contained->slot5()) {
                Rva00466EDEPair pair;
                reinterpret_cast<Rva00466EDEListView *>(contained)->slot70(&pair);
                const _STL::list<Object *> *items=pair.list;
                if (!items->empty()) {
                    Object *front=items->front();
                    if (front)
                        rider=front;
                }
            }
        if (!reinterpret_cast<OpenContain *>(this)->OpenContain::isValidContainerFor(rider,*reinterpret_cast<bool *>(&checkCapacity),*reinterpret_cast<bool *>(&trailing)))
            return false;
        if ((rider->type[0x118]&0x10) && moduleData()->flag13D) {
            unsigned used2=count();
            unsigned max2=maximum();
            return used2<max2;
        }
        unsigned slots=static_cast<unsigned>(rider->rva0028FBBE());
        if (slots==0)
            return false;
        if (*reinterpret_cast<const unsigned char *>(&checkCapacity)) {
            unsigned cnt=count();
            slots+=(1 ? cnt : cnt)+m_extraSlotsInUse;
            return maximum()>=(1 ? slots : slots);
        }
        return true;
    }
}
