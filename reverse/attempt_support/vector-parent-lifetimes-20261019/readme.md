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
