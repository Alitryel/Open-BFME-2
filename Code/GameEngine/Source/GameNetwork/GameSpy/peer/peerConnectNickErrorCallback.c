// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piConnectNickErrorCallbackA, 44 bytes.
   Carried from the Open-BFME-1 donor at submodule revision 77db49c3
   (game/GameEngine/Source/GameNetwork/GameSpy/peer/peerOperations.c). Target
   evidence: the body is byte-identical at BFME2 0x006A0180 (donor b1
   0x0085F280). The name and the piOperation field offsets are donor
   assertions; it lives in its own TU because peerOperations.c here already
   holds this file's other recovered bodies. */

typedef void *PEER;

typedef struct piOperation
{
	PEER peer;					/* +0x00 */
	int type;					/* +0x04 */
	void *owned08;					/* +0x08 */
	int ID;						/* +0x0C */
	void *callback;					/* +0x10 */
	unsigned char pad14[0x18 - 0x14];
	void *param;					/* +0x18 */
} piOperation;

void piAddNickErrorCallback(PEER peer, int type, const char *nick,
		int numSuggestedNicks, char **suggestedNicks, void *param, int ID);

void piConnectNickErrorCallbackA(PEER peer, int type, const char *nick,
		int numSuggestedNicks, const char **suggestedNicks, void *param)
{
	piOperation *operation = (piOperation *)param;
	piAddNickErrorCallback(operation->peer, type, nick, numSuggestedNicks,
		(char **)suggestedNicks, operation->param, operation->ID);
}
