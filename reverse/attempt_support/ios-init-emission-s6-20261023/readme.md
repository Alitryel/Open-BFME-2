# Narrow the generic-widening initializer emissions

Scope: stlport_basic_ios_init.cpp, 16 existing matched rows, following cafc9cee46.
SureForge Light: one source template-instantiation repair; retail bytes, strict
raw extents, EH, data and combined-provider preview are the acceptance checks.

BFME1 donor at138757e9b74645fbcbb7724a7af2764e34931e11,
game/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_init.cpp, already replaces
whole stream classes with explicit basic_ios<char>::init. Direct transfer cannot
preserve the additional BFME2 helper rows, so this adapts that established approach.
The unchanged vendored STLport4.5.3 supplies every function body and identity.

Replace three broad class instantiations with the six rowed basic_ios members.
Explicit get(char&) retains the to_char_type leaf without whitespace scanning;
peek retains _FILE_I_next through sgetc. Keep the wide ostream class: MSVC7.1
emits the rowed21-byte ??_D complete destructor only through that whole-class
instantiation in the tested variants. This helper destroys the virtual base;
research notes call it a deleting dtor imprecisely. Suppress the incidental wide
init through a declaration, binding the existing stlport_wide_ios.cpp owner.
The previous four string helper instantiations remain. No hand-written runtime
body, flag, shared header, pin, alias, ledger rehome or baseline is added.

Candidate research: removing all classes keeps4/16; precise IOS members keep13;
get and peek keep15; retaining wide ostream makes16/16. Directly instantiating
_M_gptr of the fully specialized basic_streambuf<char> causes MSVC C1001. Explicit
wide ctor/dtor and auto_ptr delete do not emit ??_D. See findings.md and diagnostics.

Owner validation on the production path: scoped build16/16; independent raw-symbol
extent equality and resolved-byte equality for all16 (owner-raw-extents.txt), no
unresolved relocations; EH1 EXACT; enforceddata0. Research harness accepted raw
length >= target, but every reported extent equals target and the owner assertion
uses strict equality. Source editability passes. Source SHA256 is recorded below.

Object inventory: external bodies476->141,335 removed/38857 compiler bytes, no
added external and no retained body size changes. All335 removed names have another
provider in published index456ce161c5, so this source is not their sole indexed
provider. No scan_not or __find_if reference remains. This is a scoped index-based
provider check, not a whole-image link or fresh census.

Combined link preview: initializer0->331; narrow imbue325, wide imbue238 and wide
IOS296 all link. Only331 is new in this follow-up: the prior563 landed in cafc9cee46,
and wide IOS was already linked. The index was fetched after rebasing and remains
456ce161c5 (2026-10-23 06:28). No census, boot or link.exe runner was used.
