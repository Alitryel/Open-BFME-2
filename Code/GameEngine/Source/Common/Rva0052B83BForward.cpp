// cl: /O1 /arch:SSE /G7 /MD
// ?rva0052B83B@Rva0052B7F8Owner@@QAEHHH@Z, retail 0x0052B83B (20 bytes,
// RET 8): forward both words to the rowed Rva0052B7F8Owner::fwd 0x0052B7F8
// on the same object and return the first, the hidden-result forwarder
// shape of the rowed map<int,int>::equal_range 0x002B8120 (the first word
// is the caller's result slot). Spelled with the callee row's int words;
// the container identity is not established.
class Rva0052B7F8Owner
{
public:
	int fwd(int result, int value);
	int rva0052B83B(int result, int value);
};

int Rva0052B7F8Owner::rva0052B83B(int result, int value)
{
	fwd(result, value);
	return result;
}
