// cl: /O2 /G7 /MD 
// Native 006CBB80..006CBBF0; four-byte refcounted handle vector delete.
// The array branch passes the existing A9DF3 destructor and stride4 to ehvec_dtor.
// The scalar path expands the same decrement/drop that BfmeRefVGO owns.
// The existing A9DF3 out-of-line five-byte wrapper remains the array callback
// provider; this inline view describes its same four-byte handle semantics.
// The original class name is unknown; preserve the callback owner name.
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
void Rva006CD460Free(void *);
class Rva006DB270 {public:void freeBlock(void *,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva004A9DF3Element {
public:
 int *Pointer;
 ~Rva004A9DF3Element(){if(Pointer && Rva006CFDF0DecRef(Pointer)==0)bfmeDropVGO(Pointer);}
 static void operator delete(void *p,unsigned size){g_pChainBlockAllocator->freeBlock(p,size);}
 static void operator delete[](void *p){Rva006CD460Free(p);}
};
// ?EmitHandleArrayDelete absent-from-retail
void EmitHandleArrayDelete(Rva004A9DF3Element *p){delete[] p;}
