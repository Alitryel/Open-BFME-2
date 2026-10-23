// ?rva0026c90@@YAPADPAD000D@Z @0x00026C90 365B via caller 0x00027540 Rva00028B90Thing::bfmeDoPF and LINK BONUS
// cl: /Od /Ob1
inline bool bfmeBytesEqual2(const char &left, const char &right)
{
	return left == right;
}
char *rva0026c90(char *first1, char *last1, char *first2, char *last2, char tag)
{
	char *tmp;
	char *p2;
	char *p;
	char *p1;
	(void)tag;
	if (first1 == last1 || first2 == last2)
		return first1;
	tmp = first2;
	++tmp;
	if (tmp == last2) {
		while (first1 != last1 && !bfmeBytesEqual2(*first1, *first2))
			++first1;
		return first1;
	}
	p2 = first2;
	++p2;
	while (first1 != last1) {
		while (first1 != last1) {
			if (bfmeBytesEqual2(*first1, *first2))
				break;
			++first1;
		}
		while (first1 != last1 && !bfmeBytesEqual2(*first1, *first2))
			++first1;
		if (first1 == last1)
			return last1;
		p = p2;
		p1 = first1;
		++p1;
		if (p1 == last1)
			return last1;
		while (bfmeBytesEqual2(*p1, *p)) {
			++p;
			if (p == last2)
				return first1;
			++p1;
			if (p1 == last1)
				return last1;
		}
		++first1;
	}
	return first1;
}
