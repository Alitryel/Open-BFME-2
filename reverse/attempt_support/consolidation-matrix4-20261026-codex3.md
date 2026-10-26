# Mechanical consolidation blocker: matrix4 destination

Date: 2026-10-26
Allocated destination: `Code/Tools/WW3D/pluglib/matrix4.cpp`

The allocator's `--check-tu` passed, but the destination directory
`Code/Tools/WW3D/pluglib` is absent. The planner scoped to that parent found no
source files. The merge dry run failed before donor verification with:

```text
FileNotFoundError: [Errno 2] No such file or directory:
.../Code/Tools/WW3D/pluglib/.matrix4.fee4166dfd935a4c.tu_skeleton.cpp
```

`reverse/tu_map.csv` shows these Matrix4 rows as `proposed` or `displaced` under
that path, while the matching source files are under
`Code/Libraries/Source/WWVegas/WWMath/`. No files or claims were changed. Sol
should reconcile the destination against the current approved TU map before
re-serving it.
