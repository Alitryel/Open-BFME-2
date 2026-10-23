// ?add@Rva0039C7A5Holder@@QAEXPBVModuleData@@@Z @ 0x0039C7A5 (19B): vector
// push_back wrapper (lea eax,[esp+4] / push eax / add ecx,0x304 / call
// push_back<vector<ModuleData*>> at 0x004DFCB0 / ret 4). Caller at 0x0055A959;
// prev 0x0039C3A6 is a name getter (no // cl:) and next 0x0039D40F is /O1.
// Identity unrecovered: opaque address-derived holder.
// No // cl: line (defaults match the frameless 19-byte shape).
class ModuleData;
namespace _STL
{
template <class T> class allocator
{
};
template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}
class Rva0039C7A5Holder
{
public:
	void add(const ModuleData *data);
private:
	char m_pad[0x304];
	_STL::vector<const ModuleData *> m_vec;
};
void Rva0039C7A5Holder::add(const ModuleData *data)
{
	m_vec.push_back(data);
}
