// cl: /Oy-
class Rva0082AFF0
{
public:
    Rva0082AFF0 *value(Rva0082AFF0 *argument) const;
};

Rva0082AFF0 *Rva0082AFF0::value(Rva0082AFF0 *argument) const
{
    Rva0082AFF0 * volatile self = const_cast<Rva0082AFF0 *>(this);
    return argument;
}
