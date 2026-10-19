# Independent vector lifetime recovery

The three old dup rows at D04E1, 48D003 and 5243BB name one vector object's
symbol through object-symbol annotations. They emit no independent parent
or EH graph. Their legacy notes do not classify them as gen-alias, so normal
add_match correctly requires a separately reviewable retraction before a
new name can own each address. retired-rows.json preserves exactly those
three records. The original canonical vector at CF60B remains unchanged.

Native callers establish the container roles separately: the streak module
destructor D057C destroys its WeatherTexture member at +28 through D04E1;
the flammable module destructor 48D075 destroys its +28 member through
48D003; the Apt-related destructor 524436 destroys its +C member through
5243BB. Each target destructor destroys the pointer range through 48CE25
and releases its allocation. That range helper advances eight bytes and
calls the existing element destructor 29D7C2. These establish the cleanup
behavior and representation, rather than an original template identity.

CameraMarker and CameraMarkerVec are existing descriptive target views.
W3DStreakWeatherVec is the existing caller-side member view. The third
container retains a neutral address-qualified name. Sharing the proven
eight-byte element cleanup does not prove that the original source used
one element class in all three contexts. No new original-name claim is made.

A scratch C++ trial uses STLport's existing three-pointer _Vector_base
representation and a real destructor which destroys [start, finish), then
lets the base release storage normally. All three complete 63-byte parents,
their independent EH graphs, and every cleanup callee binding are exact.
The forthcoming source recovery replaces two linker alias directives with
actual definitions and will admit the naturally emitted handlers through
the normal byte gates. No artificial lifetime, assembly or new pin is used.

This retraction and its following recovery form one publication batch. The
recovery will report only unique newly owned bytes; these 189 already
counted parent bytes are not credited again. BFME1 input: cf0a80c228.

## Verified recovery

The source now defines all three real destructors. Each naturally emits its
own complete ten-byte handler, for 30 new unique strict C++ bytes. Rehome
the three existing eight-byte generated cleanup actions to their actual
parent-scoped compiler labels. The named following handler and native
handler address both prove each action's extent. Each entire eighteen-byte
action/handler section is covered by the two whole-body proofs.

The actions call the existing shared fourteen-byte storage cleanup at
7FAB3. Normal admission first exposed that the emitted _Vector_base name
had no resolver binding. Admit its actual whole-byte-and-relocation ICF
twin through add_match --icf-owner, naming the existing int-vector owner.
No pin or object-symbol annotation is added. All three independent native
EH actions call that body, and its free relocation resolves to 30830.

The dependent Apt destructor at 524436 initially failed the scoped link
preview: its old vector<CameraMarker> call selected the canonical CF60B
body, whereas native calls the independent 5243BB member destructor. Replace
that member declaration with the recovered twelve-byte Rva005243BBVector
view. Its whole65-byte parent and complete EH graph remain exact; its
existing ten-byte handler remains exact. This is a provider/consumer repair,
not a new original class-name claim or an additional unique-byte recovery.

Normal verification passes30/30 provider rows and2/2 consumer rows. The
provider and all three direct callers preview as LINKS against the published
8eecc93d07 census; this is not a new census or a global link-coverage result.
The affected-unit placement rescan finds zero additional bodies or pins.
Frozen-file validation passes both edited units. proof.json records all ten
recovered/folded whole bodies, the two consumer bodies, all relocations, full
parent EH verdicts, current strict receipts and source/object hashes.
native-evidence.json records the retail callers, parents and cleanup helpers.

Six old object-symbol annotations and two linker alias directives are gone.
The old hatch allowances are left for later batched tightening. No generated
source, compiler flag, shared header, gate or baseline is changed. No runtime
test or maintained verification runner was needed for identical bytes.
About eight minutes; gpt-6.1-sol.
