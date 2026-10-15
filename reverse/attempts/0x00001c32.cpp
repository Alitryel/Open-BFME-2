// ?trimArgument@@YAPADPAD@Z
// partial score=0.95 date=2026-10-15
// Bank for 0x00001C32 (64 B): ZH WinMain.cpp strtrim, here the static
// trimArgument already defined in Code/GameEngine/Source/Main/WinMain.cpp
// (called once from WinMain's argv loop; cl gives it an esi-argument
// convention). Compiled in place it is byte-exact except the epilogue order:
// compiled `mov eax,esi; pop edi; ret`, retail `pop edi; mov eax,esi; ret`.
// ZH's `if (buffer != NULL) { ... } return buffer;` produces retail's epilogue
// order but adds `test esi,esi; je` that retail lacks. Tried without effect:
// return inside the else, while-loop trailing clip, result temp, non-inline,
// --index loop, __assume(buffer != 0) with the NULL test, guarded lead loop.
static inline char *trimArgument(char *buffer)
{
	char *source = buffer;
	while (*source != 0 && (unsigned char)*source <= ' ')
		source++;
	if (source != buffer)
		_mbscpy(buffer, source);
	for (int index = strlen(buffer) - 1; index >= 0; index--)
	{
		if (*source != 0 && (unsigned char)buffer[index] <= ' ')
			buffer[index] = 0;
		else
			break;
	}
	return buffer;
}
