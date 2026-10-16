// Native28B virtual deleting-destructor wrapper: direct qualified virtual destructor call, then optional class deallocation.
// Existing11B destructor0x000658BA installs native vtable0x00BC5C74 and tails to MultiListObjectClass::~MultiListObjectClass.
// Pool data evidence associates0x00065D0E with the camera-shaker allocator; complete object layout is unused here.
// cl: /O1 /EHsc /MD
class Rva000658BA {
public:
 virtual ~Rva000658BA();
};
void rva00065D0EReleaseShakerMemory(void*);
class Rva00065D24Element {
public:
 void* deletingDestructor(unsigned flags);
};
void* Rva00065D24Element::deletingDestructor(unsigned flags) {
 Rva00065D24Element* saved = this;
 ((Rva000658BA*)this)->Rva000658BA::~Rva000658BA();
 if(flags & 1) rva00065D0EReleaseShakerMemory(saved);
 return saved;
}
