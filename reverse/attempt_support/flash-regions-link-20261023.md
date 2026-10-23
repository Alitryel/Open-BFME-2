# FlashRegions parser link repair

Inputs: BFME 2 d1c7442a9f; published census b711de3634 (2026-10-23
14:28). BFME 1 remains the verified committed 96c88c73a5 pointer; its
6d943426 parser was already the source's semantic donor. No donor update
or new authored function bytes are claimed.

Native parser 4E14E8 passes table VA C619E0 and calls thunk 56655F.
The complete 64-byte table contains DelayFromActStart/FlashTime with
callback 2F0F7, offsets 4/C, SummaryEvent with parseBool 2E850 at offset
8, null user data, and a full zero terminator. Define its existing
data-ledger owner and call the existing rowed thunk through its reference
ABI. Elem003AF9E0 remains a callable view, not an original identity claim.

Paired current-object legacy preview with Rva0056654FThunk.cpp changes
65 -> 182 linked bytes: parser 0 -> 117, provider unchanged at 65.
The index counts the older parser extent; the current ledger separately
verifies the 118-byte parser and its 10-byte EH handler. Do not report
128 linked bytes or closed-strict closure from this preview. Normal byte
verification also checks all 64 data bytes and relocations. Strict receipt
preparation, EH graph, frozen-file/class checks, check_csv and enforced
data identity are acceptance checks; no executable link was run.

Sibling WorldText/EnableRegion providers are already repaired upstream or
by the previous session. They supply no additional gain here.

Other trials this session, both reverted and claims released:

- DX8SkinClearVisibleList: extern-template declaration preserves 9/9 byte
  matches but still emits the losing DynamicVectorClass<Vector3> deleting
  destructor. dllimport changes Render's allocation/register schedule.
  No gain; the existing fold-pin rejection is not bypassed.
- FormationTemplate: isolating the LightPoint constructor and both EH rows
  preserves 11/11 byte matches, but the parser preview needs the moved
  constructor provider, which the current index cannot preview as a new
  unit. No gain retained. Formation CameraMarker is 24 bytes, whereas the
  weather view is 8; native cleanup uses vector<LightSubPoint> at 425717.
  A coherent container identity repair is needed, not a tag-only rename.
