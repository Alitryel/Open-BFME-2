// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- one-shot MD5 and SHA-1 wrappers plus the RSA one-shot
 * wrap, ported verbatim from BFME1
 * Code/GameEngine/Source/GameNetwork/Y4DirtySockHashWrap.c
 * (Rva0080D590, 120B; Rva0080D620, 120B; Rva0080D6C0, 200B).
 * Retail 0x00679490, 0x00679520 (120B Ghidra each) and 0x006795C0
 * (200B Ghidra).
 *
 * Init/update/finish live in Y4CommDigest.c and cryptsha1.c; this TU
 * only stacks a context, feeds it, and writes the digest. Retail names
 * the locals MD5 and Sha1 (from the /GZ frame descriptors).
 */

struct Rva00810060Context
{
	unsigned int m_count;
	unsigned int m_state[4];
	unsigned char m_block[0x40];
};

void Rva00810020(struct Rva00810060Context *context);
void Rva00810060(struct Rva00810060Context *context,
	const unsigned char *data, int length);
void Rva00810FF0(struct Rva00810060Context *context, char *out, int outSize);

void Rva0080D590(const unsigned char *data, int length, char *digest)
{
	struct Rva00810060Context MD5;

	Rva00810020(&MD5);
	Rva00810060(&MD5, data, length);
	Rva00810FF0(&MD5, digest, 0x10);
}

/* Donor names and target offsets: docs/reconstruction/dirtysdk-crypto.md. */
struct CryptSha1T
{
	unsigned int uCount;
	unsigned int uPartialCount;
	unsigned int H[5];
	unsigned char strData[0x40];
};

void CryptSha1Init(struct CryptSha1T *context);
void CryptSha1Update(struct CryptSha1T *context,
	const unsigned char *data, unsigned int length);
void CryptSha1Final(struct CryptSha1T *context, void *out,
	unsigned int size);

void Rva0080D620(const unsigned char *data, int length, unsigned char *digest)
{
	struct CryptSha1T Sha1;

	CryptSha1Init(&Sha1);
	CryptSha1Update(&Sha1, data, length);
	CryptSha1Final(&Sha1, digest, 0x14);
}

void *memcpy(void *dest, const void *src, unsigned int count);

void Rva0080F3D0(unsigned char *state, const void *first, int firstLength,
	const void *second, int secondLength);
void Rva0080F530(void *dest, const void *src, int length);
void Rva0080F550(unsigned char *state);

struct Rva0080D6C0Owner
{
	char m_gap[0x18];
	void *m_first;
	int m_firstLength;
	char m_second[4];
};

void Rva0080D6C0(struct Rva0080D6C0Owner *object, const void *data,
	int length, void *dest, int destLength)
{
	unsigned char RSA[0x518];
	int iOffset;

	iOffset = (length & ~1) - destLength;
	Rva0080F3D0(RSA, object->m_first, object->m_firstLength,
		object->m_second, 4);
	Rva0080F530(RSA, data, length);
	Rva0080F550(RSA);
	memcpy(dest, RSA + iOffset, destLength);
}
