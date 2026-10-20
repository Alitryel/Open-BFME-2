Path::rva00365B8A link handoff, 2026-10-20

Strict original row 0x00365B8A..0x00365DF0 (614 bytes) passes. Frozen
5366c4f808 legacy preview holds 611 nonpadding bytes solely on the emitted
Coord3D::length copy: private /Os body is 33-byte x87 fsqrt, retail's rowed
owner in coord3d.cpp at 0x3571 is 69-byte SSE arithmetic with external sqrt.
The caller itself calls rowed Coord3D::normalize (0x35B6); its emitted 86-byte
copy calls length and matches. Thus length remains referenced by a COMDAT.

Two trials restored: dllimport forceinline on only the definition fails C2375
because canonical Lib/Coord3D.h declares ordinary linkage. Removing the local
length definition leaves a direct owner call but loses the compiler's no-escape
summary: main frame 0x4C becomes 0x58, many stack homes/registers move, byte gate
fails. No canonical-header or pragma experiment was made. Any future repair
must preserve interprocedural effects or reproduce the retail helper under the
caller's flags. Do not repeat simple definition removal/import redeclaration.
Original source restored; no altered C++ or pin landed. No closed-strict gain.
