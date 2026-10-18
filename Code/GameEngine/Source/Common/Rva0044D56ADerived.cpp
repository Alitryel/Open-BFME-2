// cl: /MD
//
// Single-inheritance destructors tail-calling the matched GameModePreferences
// base dtor at 0x0044D56A (vptr 0xC3EF60, AsciiString at +0x18, base dtor
// chain at 0x3B1F65). GameModePreferences.cpp establishes the base identity;
// Rva0054F508Ctor.cpp independently confirms that class's inheritance. Keep
// only the external base declaration here so calls resolve through the ledger
// address rather than a same-TU definition. Rva0044D285 remains opaque.

class AsciiString;
class UnicodeString;

// Virtual interface as Rva0054F508Ctor.cpp declares it (retail vftable 0x0086AA60:
// deleting dtor, then UserPreferences' load/write/get/set slots, GameModePreferences overrides).
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool load(const AsciiString &fname);
	virtual bool load(const UnicodeString &fname);
	virtual bool write(void);
	virtual bool getBool(const AsciiString &key, bool defaultValue) const;
	virtual float getReal(const AsciiString &key, float defaultValue) const;
	virtual int getInt(const AsciiString &key, int defaultValue) const;
	virtual int getEnumIndex(const char *key, const char **names, int count, int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;
	virtual void setBool(const AsciiString &key, bool val);
	virtual void setReal(const AsciiString &key, float val);
	virtual void setInt(const AsciiString &key, int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);
};

class GameModePreferences : public UserPreferences
{
public:
	virtual ~GameModePreferences();
	virtual bool write(void);
	virtual bool getBool(const AsciiString &key, bool defaultValue) const;
	virtual float getReal(const AsciiString &key, float defaultValue) const;
	virtual int getInt(const AsciiString &key, int defaultValue) const;
	virtual void setBool(const AsciiString &key, bool val);
	virtual void setReal(const AsciiString &key, float val);
	virtual void setInt(const AsciiString &key, int val);
};

class Rva0044D285 : public GameModePreferences
{
public:
	virtual ~Rva0044D285();
};

Rva0044D285::~Rva0044D285()
{
}

class Rva0054F508 : public GameModePreferences
{
public:
	virtual ~Rva0054F508();
};

Rva0054F508::~Rva0054F508()
{
}
