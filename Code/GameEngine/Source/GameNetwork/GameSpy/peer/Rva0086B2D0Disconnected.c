// cl: /DNDEBUG /MD

// _Rva0086B2D0Disconnected @ 0x006AAB50 (29B)
// BFME1 donor: Rva0086B2D0Disconnected.c at 0x0086B2D0, submodule revision
// cd32c8ef06dfb0d995b2f47e93e41622e4447092. This is a peer disconnect
// reconstruction, not vendored SDK text. Retail bytes set one byte at +0x1F04
// and call the matched piAddDisconnectedCallback body at 0x0069FA52
// (two bytes into its verified 0x0069FA50 entry). The target starts after an
// int3 run. The struct field name/layout is carried from the donor; retail
// independently verifies only the byte write and callback relationship.

typedef struct Rva0086B2D0Connection
{
    char pad[0x1F04];
    int disconnected;
} Rva0086B2D0Connection;

void piAddDisconnectedCallback(void *peer, const char *reason);

void Rva0086B2D0Disconnected(void *unused, const char *reason,
    Rva0086B2D0Connection *connection)
{
    connection->disconnected = 1;
    piAddDisconnectedCallback(connection, reason);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_piChatDisconnectedA=_Rva0086B2D0Disconnected")
