# GameWindowGlobal declaration prerequisite

The GameClient mechanical-seat handoff recorded C2039 for winMakeColor in
the image donor. A fresh normal dry run reproduced that error and accepted
neither donor. The scoped planner's original-path catalogue names the
WorldBuilder GameWindowGlobal path; ZH/BFME1 names remain donor hints. The
current skeleton rebuild approves the existing seed and image donor; its
mixed VslotSmallBodiesB source remains excluded.

Both sources now include a TU-scoped GameWindowGlobalView.h. It retains the
image donor's existing virtual padding through slot 69 and replaces its
slot-70 padding with the seed's existing winMakeColor declaration. Direct
reads of retail vtable RVA 0x007C7C90 confirm slot 70 = VA 0x00714C1D and
slot 71 = VA 0x00714C3E. The existing nonvirtual winGetTextSize and winFindFont
declarations are retained unchanged in ABI. No complete object layout or
additional method identity is inferred. The explicit GUI include directory
lets the same include resolve from both the donor and approved destination.

Checks on 2026-10-25:

- Scoped planner regenerated without concurrent compiler scratch files;
  its snapshot check passed. An earlier survey collided with a transient
  scratch file, so that survey was discarded and regenerated.
- Both files passed find_declared_unmatched.py before and after editing.
- ./build.sh verifies all three seed rows and both image-donor rows;
  string, float and import checks pass.
- Normal merge dry run now accepts both sources, five matched rows,
  with no rejected clean donor. A separate scratch Verifier check confirms
  all five ledger rows, including the image body's EH handler.
- check_csv.py and git diff --check pass. Reports remain locally at
  build/windowglobal-prerequisite-{before,after,plan}.txt.

Leave the now-compatible image donor for Luna. No merge was applied, no file
removed, no authored bytes added and no identity/header debt retired. The
mixed sweep source is unchanged.

Publication audit: fetched origin/master at 7d1555ce5f; the previous five
prerequisite commits are already ancestors of origin/master. This pending
prerequisite changes no existing source path. Searches through active tools,
hooks, workflows, includes and build inputs found no consumer to repoint;
only the two source includes consume the new TU-scoped header. Normal builds
and the composed verifier confirm its include resolution. Historical EA
paths and protected registers are unchanged. Hold the two source file claims
and new-header file claim until this commit is published.
