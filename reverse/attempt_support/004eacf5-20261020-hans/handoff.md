# 0x4EACF5 distSqToSegment (helper of 0x4EADBA) - hans session 2026-10-19 23:00 PT
Baseline (bank reverse/attempts/0x004eadba.cpp): struct 0 mem 4 reg 0, 197 B; only diff = apy (ecx+4/eax+4 -> xmm0) scheduled before apx (ecx/eax -> xmm1) at +0x09..+0x16; retail computes apx first.
Note: obj symbol is ?distSqToSegment@@YAMPBVCoord2D@@00@Z (class Coord2D), not the PBU name in the bank header.
Inert (still 4/0): apy declared first; split apx=pt->x; apx-=...; dy before dx loads; comma decl; separate decl+assign; const Coord2D& alias for lineStart; pt alias; inline subexpressions in dot; dy*apy commuted mults; apx*=1.
Worse (reg 2, R=6): any dot form starting with apx*dx or a single-expression sum; temp for apx*dx; apx*=dx.
Worse (struct): Coord2D ap struct (2/4/6); inline dotp helper with arg-order tricks (size 206, not inlined at /O1 like this).
Conclusion: schedule order follows first use in dot (apy*dy) and the accumulate form is what fixes reg; untried: different dx/dy representation (Coord2D dir from lineEnd copy), ZH-literal Vector2 type with operator-.
