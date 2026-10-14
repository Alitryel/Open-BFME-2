// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Retail 0x00130FFC..0x0013101E; return receiver and RET16.
// BFME1 W3DRadarAlphaBlob6x6.cpp provides the related one-pointer lock-guard
// semantics; retail calls the owned bool-discard SurfaceClass lock view.
// The historical guard name is unknown; use an address-qualified operation.
class Rva00116680 {
public: void *rva00116680(int *pitchOut,bool discard);
};
class Rva00130FFC {
 Rva00116680 *surface;
public:
 Rva00130FFC *rva00130FFC(Rva00116680 *input,void *&bits,int *pitch,bool discard);
};
Rva00130FFC *Rva00130FFC::rva00130FFC(Rva00116680 *input,void *&bits,int *pitch,bool discard) {
 surface=input;
 bits=surface->rva00116680(pitch,discard);
 return this;
}
