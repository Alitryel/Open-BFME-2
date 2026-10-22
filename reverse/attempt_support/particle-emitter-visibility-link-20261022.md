# Particle emitter visibility linkage, 2026-10-22

BFME 2 input: 6387755047; BFME 1 donor: 42bba2ddbd5cb895d99293583891d3b7315fa49e.
Published census: 08160bc2c9 (2026-10-22 17:08), retail-truth rules as supplied.

The standalone ParticleEmitterVisibilityWrappers unit supplies the rowed
Set_Hidden and Set_Animation_Hidden bodies. Constructor, copy, and destructor
units instead emitted inline donor wrappers calling RenderObjClass out of line.
Those copies conflict with the rowed wrappers. The constructor already used the
BFME 2 particle shim; copy and destructor bypassed it. All three now use that
shim with declarations of the two externally owned methods. This changes no
class layout or vtable slots. The remaining shim differences affect constructor
and texture-handle declarations, not the copy/destructor layout.

Joint legacy link_check of the wrapper, constructor, copy and destructor:
before 0/1848 B, after 135/1848 B. The wrapper unit now links its four rows
(135 B); the three consumer units retain RenderObjClass vtable and Get_LOD_Count
COMDAT conflicts. This is a legacy prediction, not a closed-strict gain.

build.sh verifies 13/13 consumer rows, one string literal and eight float
literals; three EH funclets are verified past renumbered compiler labels.
link_check --prepare-current verifies all four explicit providers (17 rows)
with strict reusable receipts; it does not check LINK closure or change census
status. No closed-strict improvement is claimed.

The next prerequisite for linking the three consumers is reconciliation of
their RenderObjClass base view with its kept vtable/method definitions. Do not
silence those conflicts merely by removing an unreferenced copy: these copies
are live under the supplied census rules.
