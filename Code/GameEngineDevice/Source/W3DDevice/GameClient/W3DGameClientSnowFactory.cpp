// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour/BFME1 W3DGameClient::createSnowManager with target object extent.
// Only the verified destructor/init virtual prefix is represented here.
class SnowManager {
public:
    virtual ~SnowManager();
    virtual void init();
private:
    unsigned char m_targetBase[0x70];
};

class W3DSnowManager : public SnowManager {
public:
    W3DSnowManager();
    virtual ~W3DSnowManager();
    virtual void init();
private:
    unsigned char m_targetDerived[0x3C];
};

typedef char SnowBaseSizeCheck[sizeof(SnowManager) == 0x74 ? 1 : -1];
typedef char W3DSnowSizeCheck[sizeof(W3DSnowManager) == 0xB0 ? 1 : -1];

class W3DGameClient {
protected:
    virtual SnowManager *createSnowManager();
};

inline SnowManager *W3DGameClient::createSnowManager()
{
    return new W3DSnowManager;
}

// createSnowManager is a header inline: other units emit select-any copies
// of it, so a strong definition here was a duplicate symbol in the linked
// build. This anchor only makes this unit emit its copy for the ledger row;
// it is not retail code. The qualified call emits the copy without a virtual
// dispatch (a plain virtual call would not emit it).
struct W3DGameClientSnowEmitter : public W3DGameClient {
    static void emit(W3DGameClientSnowEmitter *p);
};
#pragma inline_depth(0)
// ?emit@W3DGameClientSnowEmitter@@SAXPAU1@@Z present-unmatched
void W3DGameClientSnowEmitter::emit(W3DGameClientSnowEmitter *w3DGameClientSnowEmitter)
{
    w3DGameClientSnowEmitter->W3DGameClient::createSnowManager();
}
#pragma inline_depth()
