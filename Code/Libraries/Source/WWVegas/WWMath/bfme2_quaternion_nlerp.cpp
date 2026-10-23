// cl: /EHsc /DNDEBUG /MD
// Descriptive BFME2 name; original retail function name is unrecovered.
// RVA 0x00717550: shortest-path normalized quaternion interpolation,
// called by encoding-0 channel evaluation at 0x001B3313. The retail dot
// product sums X then Z then Y then W; preserve that floating-point order.
// Complete 377-byte boundary ends at RET 0x00B176C8 before alignment.
class WWMath { public: static    float __fastcall Inv_Sqrt(float); };
class Quaternion { public:    float X, Y, Z, W; };
void BFME2_Nlerp(Quaternion &res,const Quaternion &quaternion,const Quaternion &q,float alpha)
{
    float dot=quaternion.X*q.X+quaternion.Z*q.Z+quaternion.Y*q.Y+quaternion.W*q.W;
    float beta=1.0f-alpha;
    if (dot<0.0f) {
    res.X=beta*quaternion.X-alpha*q.X;
    res.Y=beta*quaternion.Y-alpha*q.Y;
    res.Z=beta*quaternion.Z-alpha*q.Z;
    res.W=beta*quaternion.W-alpha*q.W;
    } else {
    res.X=beta*quaternion.X+alpha*q.X;
    res.Y=beta*quaternion.Y+alpha*q.Y;
    res.Z=beta*quaternion.Z+alpha*q.Z;
    res.W=beta*quaternion.W+alpha*q.W;
    }
    float length=res.X*res.X+res.Y*res.Y+res.Z*res.Z+res.W*res.W;
    if (0.0f!=length) {
    float scale=WWMath::Inv_Sqrt(length);
    res.X *= scale;
    res.Y *= scale;
    res.Z *= scale;
    res.W *= scale;
    }
}
