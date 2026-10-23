// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 005533E1..005533F5 is a separate RET8 body. It forwards the
// byte-key reference with the same receiver to the proven tree lookup at
// 005B8053 and stores its node pointer in a four-byte hidden return object.
// STLport's non-POD iterator supplies that return ABI; original owner/name
// unresolved, so reuse only the existing address-named lookup view.
struct Rva005533E1Iterator {
 void *node;
 Rva005533E1Iterator(void *p):node(p){}
};
class Rva005B8053 {
 void *header;
public:
 __declspec(nothrow) void *rva005B8053(unsigned char const *key);
 Rva005533E1Iterator rva005533E1(unsigned char const *key);
};
Rva005533E1Iterator Rva005B8053::rva005533E1(unsigned char const *key) {
 return Rva005533E1Iterator(rva005B8053(key));
}
