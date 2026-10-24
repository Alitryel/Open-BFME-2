# DX8 skin deleting-wrapper controls

No successful repair or linked-byte gain. Production trials restored.

The current DX8SkinClearVisibleList.cpp still loses only
`??_G?$DynamicVectorClass@VVector3@@@@UAEPAXI@Z` to FXShaderRendererSkin.cpp.
Both wrappers call the same normal destructor and global delete. DX8 emits
30 bytes with `add esp,4` and the first provider emits 28 with `pop ecx`.
The normal destructor specialization declaration preserves all 8 native rows
and exact EH but does not resolve this wrapper conflict.

Additional controls: size-oriented pragmas around that declaration, around
vector.h, and around the first vector constructor do not fix it. A final-TU
size pragma preserves the 8 rows but changes several other virtual template
copies and adds blockers. A gsy pragma around Render fails its 1400-byte body
and EH; restore it. A non-emitted gty automatic-vector anchor in the first
provider preserves its 8 rows but leaves the conflict. Throw specifications
and a size-only Render pragma also retain the 30-byte deleting wrapper.

The attempted command-line /Os is discarded by region defaults and is not
evidence of a compiler trial under that flag. No region override or protected
baseline was edited. Further work needs a supported way to reconcile the
generated wrapper's optimization context without changing Render or the full
vector virtual contract described in link-seat-20261023b.md.
