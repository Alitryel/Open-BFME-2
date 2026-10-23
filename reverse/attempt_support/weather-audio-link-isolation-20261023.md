# Weather audio link isolation

Base a3a0f792a9; published census 0393df10e2, 2026-10-23 19:47,
retail-truth-4. Current-object preview of GlobalWeatherSystemAudio.cpp before
editing excluded all 272 nonpadding bytes: WeatherData construction/destruction,
GlobalWeatherSystem destruction and Rva00318588Handle destruction were unresolved.

Separate the existing constructor and its EH graph into
GlobalWeatherSystemCtorDeferred.cpp. Keep the independent 119-byte audio routine
in its indexed unit. No body, layout, ABI, flags, pin or target identity changes.
The original source's retail call/field evidence is retained; current BFME1
f5140c1cff6a was reviewed at the verified pointer. This follows the accepted
PerFrameStats/CameraMarker/Armor isolation repair, not a new donor reconstruction.

Final same-unit current-object legacy preview: LINKS 0 -> 119 B. The new
constructor unit is absent from the census and receives no credit; it still needs
the four lifetime providers above. Correctly classify both existing compiler EH
handlers as gen-ehstub, so neither counts as authored C++ or linked C++ credit.
This is not a self-strict or closed-strict link result or an executable link.
New authored C++ bytes: zero.

Acceptance: link_check --prepare-current byte-verifies both explicit providers
8/8 with strict reusable receipts, and string/float/import gates pass. Parent EH
verification, declared-definition, class, pin-admission and new-variant gates
pass. Four stale local-label hints resolve through the verified parent EH graph;
no new alias row or verifier change. Scratch logs: build/link-seat-weather/ and
build/link-seat-weather-before.txt.
