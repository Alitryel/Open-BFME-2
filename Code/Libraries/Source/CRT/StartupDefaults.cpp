// cl: /O1 /G7 /Ob1 /MD
// Native crtexew.obj calls _setargv and passes _matherr as callback; both
// resolve to the same complete relocation-free xor eax,eax/ret retail body.
// Purpose and C signatures follow these native symbol/call relationships.
// No CRT implementation source was read. Folding adds zero unique bytes.
struct _exception;
extern "C" {
int __cdecl _setargv() {return 0;}
// ?_matherr present-unmatched
int __cdecl _matherr(_exception *) {return 0;}
}
