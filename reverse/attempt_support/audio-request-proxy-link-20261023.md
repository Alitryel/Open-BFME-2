# Audio request-set allocator link blocker

Inputs: BFME2 `ebe74e6818`, verified BFME1 donor
`f5140c1cff6a58e16276fd6de6788186286953d4`, published census
`0393df10e2` (2026-10-23 19:47). Source:
`Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00056BFE.cpp`.
Flags: `/O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
/D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc`, STLport 4.5.3.

This follows the landed identity correction, not the obsolete string-hash
attempts. Target caller 0x00057B27 and helper 0x00051B89 support the request
pointer set; the source documents that evidence. The remaining problem is
allocator code generation, not another proposed container identity.

Paired unchanged legacy preview of this TU, string-uint resize, and
`XferBlockWriter_rva009D86E0_Rva0060CB97.cpp` reports:

- Request-set resize, 197 B: blocked by the referenced constructor
  `??0?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV?$allocator@PAX@1@PAPAX@Z`,
  differing from the first kept copy, with no retail address.
- String-uint resize, 382 B: already links unchanged. This gain belongs to the
  preceding identity correction and is not a gain from this investigation.
- XferBlockWriter, 34 B: unresolved node allocator allocation/deallocation.

Two careful byte-gate trials, both inserted immediately after `<vector>`:

```cpp
namespace _STL {
template <> __declspec(dllimport) __forceinline
_STLP_alloc_proxy<void **, void *, allocator<void *> >::_STLP_alloc_proxy(
    const allocator<void *> &alloc, void **data)
    : allocator<void *>(alloc), _M_data(data) {}
}
```

The second trial replaced that definition with the corresponding plain
declaration-only specialization, ending `throw();`. Both produced the same
202-byte resize instead of retail's 197 bytes. After hashing and unlinking a
node, retail retains the indexed bucket address (`lea eax,[ecx+eax*4]`);
the trials shift the index, reload the vector start, and reload the loop index.
The loop grows five bytes, changing its branches. The first difference is a
forward branch displacement. This is a real byte mismatch, not a
verifier false reject. No suppression, alias, pin, or flags change was retained.

Both trials were reverted. `./build.sh` on the restored source passes 1/1
matched bodies plus string, float and import reference checks. The file and
0x00056BFE claims were released. Further work needs an evidence-backed way to
retain the original compiler summaries and register allocation while reconciling
the referenced allocator constructor copy; do not repeat either trial unchanged.

The surrounding link audit used legacy scoped previews, not a closed-strict
measurement: 334 current authored units with one or two census blockers and
312 with three to six. Nineteen units in the latter set already link unchanged
(19,958 B); no authored gain is claimed. Rankings, class-view blockers and the
repair queue were checked. `name_globals.py --dry-run` found zero edits.
`rehome_rows.py --limit 12` could not run without the unpublished `census.log`;
no census or link cycle was started. No matching data-back artifact was present.
BFME1's current linking leads were reviewed; no new transferable repair was
established. ParticleSystemManagerDtor's layout/callee lead remains with its
live file claimant. Preserve that claim and include current providers in future
baselines so inherited gains are not counted again.
