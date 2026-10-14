#pragma once

#include "ascii_string.h"

class Drawable;
class TerrainResourceBehaviorModuleData;
class FeedbackDisplayString;

// InGameUI embeds this 20-byte settings record at +0x574. The Impl
// constructor reads font +4, size +8, bold +C and color +10; the decal
// worker reads the first string. It is distinct from the pixel position
// passed to update at InGameUI +0x558.
struct FeedbackParams {
    AsciiString sound, font;
    int size;
    bool bold;
    char padD[3];
    int color;
};

struct Rva004E669APoint {
    int x, y;
    Rva004E669APoint(int xx, int yy) : x(xx), y(yy) {}
};

class PlaceTerrainResourceClaimantFeedback {
public:
    class Impl;
    PlaceTerrainResourceClaimantFeedback(FeedbackParams *, Drawable *,
        const TerrainResourceBehaviorModuleData *);
private:
    Impl *m_impl;
};

class PlaceTerrainResourceClaimantFeedback::Impl {
    PlaceTerrainResourceClaimantFeedback *m00;
    FeedbackParams *m04;
    Drawable *m08;
    const TerrainResourceBehaviorModuleData *m0C;
    FeedbackDisplayString *m10;
    Rva004E669APoint position;
    void *decal;
public:
    Impl(PlaceTerrainResourceClaimantFeedback *, FeedbackParams *, Drawable *,
        const TerrainResourceBehaviorModuleData *);
    void createPotentialClaimDecal();
};
