// cl: /Od

void *bfmeFwdV26(int one, int two, int three, int four, int five, int six, char seven);

void bfmeGoPA(void *one, void *two, void *three, void *four, unsigned char five)
{
	unsigned char second;

	unsigned char first;

	(void)bfmeFwdV26((int)one, (int)two, (int)three, (int)four, (int)&second, (int)&first, (char)five);
}
