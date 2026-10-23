// cl: /Od

void *__cdecl operator new(unsigned int size, void *where);

int **bfmeFillQL(int **first, int **last, int **out)
{
	int **at = out;

	for (; first != last; ++first, ++at)
	{
		int *got = (int *)::operator new(4, at);

		(got != 0) ? (*got = *(int *)first, (void *)got) : (void *)0;
	}

	return at;
}
