# VP6 border caller binding: measurement prerequisite

At BFME2 39e67823b1, upstream 6a5bda74c5 has recovered `_UpdateUMVBorder`
at RVA 0x001B96A0, 1047 bytes. This resolves the former missing-body prerequisite
recorded for `?d_009a8c50@@YAXXZ`. No external decoder source was consulted:
only approved spec `reverse/vp6_cleanroom/specs/001b96a0.md` and existing repo code.
The approved spec establishes a cdecl function with two pointer arguments.

Four current caller units still reference the old zero-argument placeholder via
two-argument function-pointer casts:

| Unit under Code/Libraries/Source/VP6/ | Matched bytes |
| --- | ---: |
| CopyFrame.cpp | 299 |
| ScaleOrCenter.cpp | 126 |
| PostProcess.cpp | 1192 |
| DecodeFrameToYUV.cpp | 500 |

The legacy preview reports all four blocked solely by the placeholder, totaling
2117 bytes. All four pass `find_declared_unmatched.py`. The next repair should
declare the real C-linkage function and bind these calls to its rowed name,
retaining the existing two argument words, then prove all caller bytes and
measure the paired cohort including the new provider.

The supplied published census index is 0fa62a2841 (2026-10-22 23:07,
retail-truth-4). The new provider is absent. Explicitly including it in
`link_check.py` refuses measurement because its link position is unknown:

```
link_check: not in census 0fa62a2841, so not previewable (the next census measures it): Code/Libraries/Source/VP6/UpdateUMVBorder.cpp
```

No source trial, pin, index modification or linked gain is claimed. No claims
were acquired. Wait for a runner-supplied index admitting this provider; do not
start a maintainer-only census or inject a synthetic provider to bypass this
boundary. `--current-ledger` also requires receipt-current providers across the
ledger, which this checkout does not have. This is a measurement prerequisite,
not a rejection of the recovered callee or its clean-room implementation.

Raw caller-only preview and the explicit-provider refusal are preserved beside
this note. Reassess this cohort once the index changes, rather than retrying the
now-solved callee reconstruction.
