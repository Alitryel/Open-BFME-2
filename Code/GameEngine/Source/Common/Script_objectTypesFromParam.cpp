// cl: /EHsc /MD
// ?Script_objectTypesFromParam@@YAXPAVParameter@@PAVObjectTypes@@@Z at 0x00566E6C (113B). INI token to ObjectTypes.
// Zero Hour's Script_objectTypesFromParam takes the script Parameter; its string sits at +0x10.
// Evidence: temp copy via 0x365F0 plus inlined empty check; global ScriptEngine 0x00DFE16C via getObjectTypes 0x357651;
// ObjectTypes assign 0x376A9C when found else check-add 0x376B50; release 0x36410; chain via 0x376B50.
template <typename T> struct BfmeStringData;
template <typename T> class StringBase {
	friend class AsciiString;
	StringBase(const StringBase &);
	void releaseBuffer();
protected:
	BfmeStringData<T> *m_data;
public:
	void *data() const { return m_data; }
	void toLower();
};
class AsciiString : public StringBase<char> {
public:
	AsciiString(const AsciiString &asciiString) : StringBase<char>(asciiString) {}
	~AsciiString() { releaseBuffer(); }
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class ObjectTypes;
class ScriptEngine {
public:
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
};
extern ScriptEngine *TheScriptEngine;

class ObjectTypes {
public:
	ObjectTypes &operator=(const ObjectTypes &that);
	void addObjectType(const AsciiString &objectType);
};

class Parameter {
public:
	unsigned char m_pad[0x10];
	StringBase<char> m_10;
};

void Script_objectTypesFromParam(Parameter *src, ObjectTypes *dst);

void Script_objectTypesFromParam(Parameter *src, ObjectTypes *dst)
{
	if (!dst)
		return;
	AsciiString tmp((const AsciiString &)src->m_10);
	void *p = tmp.data();
	if (!p || *(unsigned short *)((char *)p + 4) == 0)
		return;
	ObjectTypes *found = TheScriptEngine->getObjectTypes(tmp);
	if (!found)
		dst->addObjectType(tmp);
	else
		*dst = *found;
}
