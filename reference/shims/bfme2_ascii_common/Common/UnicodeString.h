#pragma once

// Opt-in route for ports that include Common/UnicodeString.h.
// Use BFME2's frozen shared view before donor ini/string shims.
#include "../../bfme2_ascii/unicode_string.h"
#define UNICODESTRING_H
