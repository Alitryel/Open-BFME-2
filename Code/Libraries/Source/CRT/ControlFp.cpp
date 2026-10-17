// cl: /O1 /G7 /Ob1 /MD
// Typed callable import veneer. ABI: public float.h; target: native fp8.obj
// REL32 plus retail PE msvcr71.dll!_controlfp at IAT 0x00BBA588.
extern "C" {
extern unsigned int (__cdecl *_imp___controlfp)(unsigned int,unsigned int);
unsigned int __cdecl _controlfp(unsigned int value,unsigned int mask) {
 return _imp___controlfp(value,mask);
}
}
