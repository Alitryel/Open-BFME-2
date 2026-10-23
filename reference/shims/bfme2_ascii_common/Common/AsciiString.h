#pragma once

// Opt-in route for ports that include Common/AsciiString.h.
// Use BFME2's frozen shared view before donor ini/string shims.
#include "../../bfme2_ascii/ascii_string.h"
#define ASCIISTRING_H
