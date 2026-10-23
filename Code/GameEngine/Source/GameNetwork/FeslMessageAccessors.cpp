// cl: /O2
// Rva007E8810Message's key/value accessors and error slot, under the names
// their 20-odd FESL callers already use (symbols.csv pins at 0x00655950 -
// 0x00655B50, 0x0065D7E0 and 0x0066DD00). Retail folded each body with an
// identical one that holds the address's row under another name, so every
// member here lands as an ICF alias of that row:
//   hasError  0x00655950  W3DVideoBuffer::valid       (+0x24 != 0)
//   addInt    0x00655960  BfmeThingCIB::bfmeGoCIB
//   getInt    0x00655990  BfmeThingRF::bfmeGoRF
//   addBool   0x00655A10  Rva007E8980::go
//   getBool   0x00655A50  BfmeThingVMQ::bfmeGoVMQ
//   addString 0x00655AA0  BfmeThingCIC::bfmeGoCIC
//   getString 0x00655B10  BfmeThingUPB::bfmeGoUPB
//   reset     0x00655B50  Rva007E8AC0::run
//   setError  0x0065D7E0  BuildListInfo::setAngle     (+0x24 = value)
//   getError  0x0066DD00  Rva0066DD00DwordField::get  (+0x24)
// Layout: record text at +0x10 and its capacity at +0x14 (the rowed
// Rva007EBCA0/Rva007EC5C0/Rva007ECE60 record helpers take them), write
// position +0x18, error +0x24 (-100 when a write fails), +0x2C reset to 4.
// Model/flags: FeslMessage_getInt64_rva007E8930.cpp (// cl: /O2).

char *Rva007EBCA0(const char *record, const char *key);
int Rva007EC5C0(char *record, int capacity, const char *key, int value);
int Rva007ECE60(char *record, int capacity, const char *key, const char *value);
extern "C" int Rva007EE720(char *text, int defaultValue);
extern "C" int __cdecl Rva007EEC30(const char *text, unsigned char *dest,
	int destSize, const char *defaultText);

class Rva007E8810Message
{
public:
	bool hasError();
	void addInt(const char *key, int value);
	int getInt(const char *key, int defaultValue);
	void addBool(const char *key, bool value);
	bool getBool(const char *key, bool defaultValue);
	void addString(const char *key, const char *value);
	bool getString(const char *key, char *out, int size);
	void reset();
	void setError(int error);
	int getError();

private:
	char m_pad[0x10];
	char *m_record;       // +0x10
	int m_capacity;       // +0x14
	int m_position;       // +0x18
	char m_pad1C[8];
	int m_error;          // +0x24
	char m_pad28[4];
	int m_state;          // +0x2C
};

bool Rva007E8810Message::hasError()
{
	return m_error != 0;
}

void Rva007E8810Message::addInt(const char *key, int value)
{
	if (Rva007EC5C0(m_record, m_capacity, key, value) < 0)
		m_error = -100;
}

int Rva007E8810Message::getInt(const char *key, int defaultValue)
{
	char *text = Rva007EBCA0(m_record, key);
	if (!text)
		return defaultValue;
	return Rva007EE720(text, defaultValue);
}

void Rva007E8810Message::addBool(const char *key, bool value)
{
	if (Rva007EC5C0(m_record, m_capacity, key, value != 0) < 0)
		m_error = -100;
}

bool Rva007E8810Message::getBool(const char *key, bool defaultValue)
{
	int fallback = (defaultValue != 0);
	char *text = Rva007EBCA0(m_record, key);
	int value;
	if (text == 0)
		value = fallback;
	else
		value = Rva007EE720(text, fallback);
	return value != 0;
}

void Rva007E8810Message::addString(const char *key, const char *value)
{
	if (Rva007ECE60(m_record, m_capacity, key, value) < 0)
		m_error = -100;
}

bool Rva007E8810Message::getString(const char *key, char *out, int size)
{
	char *text = Rva007EBCA0(m_record, key);
	if (!text) {
		*out = 0;
		return false;
	}
	Rva007EEC30(text, (unsigned char *)out, size, "");
	return true;
}

void Rva007E8810Message::reset()
{
	*m_record = 0;
	m_position = 0;
	m_error = 0;
	m_state = 4;
}

void Rva007E8810Message::setError(int error)
{
	m_error = error;
}

int Rva007E8810Message::getError()
{
	return m_error;
}
