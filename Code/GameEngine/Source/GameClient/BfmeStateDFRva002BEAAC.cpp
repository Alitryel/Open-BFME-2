// cl: /O1 /arch:SSE /G7
// ?rva002BEAAC@BfmeStateDF@@QAEMMMM@Z, retail 0x002BEAAC, 33 bytes.
// Evidence: unlock caller 0x002BECBA, pin callee Curve 0x00504BA9
// ??RFCurve@@QAEMM@Z, same BfmeStateDF curve +0x28
// and single-lerp x87 shape as BfmeStateDF::interpolate in
// LivingWorldPairInterpolate.cpp (which needs /Oy- for its EBP frame;
// this frameless 33B leaf needs no /Oy-).
class FCurve
{
public:
    float operator()(float progress);
};

struct BfmeStateDFVector3
{
    float x, y, z;
};

class BfmeStateDF
{
public:
    float rva002BEAAC(float from, float to, float progress);
    void rva002BEACD(BfmeStateDFVector3 *from, BfmeStateDFVector3 *to,
                    BfmeStateDFVector3 *result, float progress);
private:
    unsigned char prefix28[0x28];
    FCurve curve;
};

// ?rva002BEAAC@BfmeStateDF@@QAEMMMM@Z
float BfmeStateDF::rva002BEAAC(float from, float to, float progress)
{
    float factor = curve.operator()(progress);
    return (to - from) * factor + from;
}

// Retail 0x002BEACD..0x002BEB6F: RET 0x10 follows the third float store.
// Caller 0x002BECBA shares this receiver with the scalar helper above and
// the matched two-component interpolate at 0x002BEB6F. The target calls the
// same curve at receiver+0x28 three times, returning ST0 each time, and writes
// floats at result+0/4/8. A three-component vector is a structural inference;
// the target method's original name remains unknown.
void BfmeStateDF::rva002BEACD(BfmeStateDFVector3 *from, BfmeStateDFVector3 *to,
                             BfmeStateDFVector3 *result, float progress)
{
    float factor;
    FCurve *fCurve = &curve;
    factor = fCurve->operator()(progress);
    float start = from->x;
    result->x = (to->x - start) * factor + start;
    float secondFactor = fCurve->operator()(progress);
    start = from->y;
    result->y = (to->y - start) * secondFactor + start;
    progress = fCurve->operator()(progress);
    start = from->z;
    result->z = (to->z - start) * progress + start;
}
