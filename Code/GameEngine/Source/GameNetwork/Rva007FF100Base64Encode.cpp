// cl: /O2 /MD
// EA FESL Base64 encoder, adapted from BFME1
// Rva007FF100Base64Encode.cpp. Retail 0x0066B5D0 (320B Ghidra, 327B BFME1).

// BFME2 VA 0x00CE3960; all 65 bytes, including the terminator, match retail.
extern const unsigned char g_base64EncodingAlphabet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void rva007FF100Encode(unsigned int length, const char *source, void *destination)
{
	int outputOffset = 0;
	int inputOffset = 0;
	if ((int)length >= 3)
	{
		unsigned int group = length / 3;
		length += group * -3;
		do
		{
			((unsigned char *)destination)[outputOffset] =
				g_base64EncodingAlphabet[
					((const unsigned char *)source)[inputOffset] >> 2];
			((unsigned char *)destination)[outputOffset + 1] =
				g_base64EncodingAlphabet[
					(((const unsigned char *)source)[inputOffset + 1] >> 4) |
					 (((source)[inputOffset] & 3) << 4)];
			((unsigned char *)destination)[outputOffset + 2] =
				g_base64EncodingAlphabet[
					(((source)[inputOffset + 1] & 0xf) << 2) |
					 (((const unsigned char *)source)[inputOffset + 2] >> 6)];
			((unsigned char *)destination)[outputOffset + 3] =
				g_base64EncodingAlphabet[
					(source)[inputOffset + 2] & 0x3f];
			outputOffset += 4;
			inputOffset += 3;
			--group;
		}
		while (group != 0);
	}
	if (--length != 0)
	{
		if (--length == 0)
		{
			((unsigned char *)destination)[outputOffset] =
				g_base64EncodingAlphabet[
					((const unsigned char *)source)[inputOffset] >> 2];
			((unsigned char *)destination)[outputOffset + 1] =
				g_base64EncodingAlphabet[
					((source[inputOffset] & 3) << 4) |
						 (((const unsigned char *)source)[inputOffset + 1] >> 4)];
			((unsigned char *)destination)[outputOffset + 2] =
				g_base64EncodingAlphabet[(source[inputOffset + 1] & 0xf) << 2];
			((unsigned char *)destination)[outputOffset + 3] = '=';
			outputOffset += 4;
		}
	}
	else
	{
		((unsigned char *)destination)[outputOffset] =
			g_base64EncodingAlphabet[
				((const unsigned char *)source)[inputOffset] >> 2];
		((unsigned char *)destination)[outputOffset + 1] =
			g_base64EncodingAlphabet[(source[inputOffset] & 3) << 4];
		((unsigned char *)destination)[outputOffset + 2] = '=';
		((unsigned char *)destination)[outputOffset + 3] = '=';
		outputOffset += 4;
	}

	((unsigned char *)destination)[outputOffset] = 0;
}
