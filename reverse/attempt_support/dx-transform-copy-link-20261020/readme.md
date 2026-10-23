# Matrix transform copy prerequisite

At BFME2 88457d2ee5, copying the sixteen scalar matrix fields directly in a
TU-local inline helper preserves the complete1042B Set_Transform row and
all references. It avoids instantiating the non-retail Vector4 assignment
copy without a shared-header edit. Candidate kept as a patch, not production.

Current-object legacy preview remains zero: an earlier Set_Transform COMDAT
is proven non-retail. Making this owner strong also preserves1042B but creates
an exclusive/select-any duplicate and does not fix selection. Keep select-any.
The earlier consumers must be reconciled together; ringobj, camera, dx8renderer,
HeightMap and decalmsh appear before this owner in the published census.
The existing wwlib-helper-link-20261020 handoff records that broad prerequisite
and a then-held provider. No gain is claimed and original source is restored.
Reapply the scalar copy patch only with a verified selection repair.

The diagnostic patch has zero context; use `git apply --unidiff-zero`.
