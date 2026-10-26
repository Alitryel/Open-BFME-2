# NetPacket composition boundary, 2026-10-26 (codexb)

The inherited NetPacket trial was interrupted without a verdict. A fresh
ordinary `tu_skeleton.py --merge
Code/GameEngine/Source/GameNetwork/NetPacket.cpp --dry-run` completed against
`0bdd549334`: 136 approved rows, no accepted files, twenty rejected donors.
Current GameNetwork parent naming evidence and --plan were reviewed. No
source, ledger or routing changes were made; the temporary destination claim
was released. `build/sol-netpacket-{plan,trial}.txt` hold the local receipts.

The serializer views are incompatible with the existing seed: raw
NetWrapperCommandMsg views require m_w0/m_w1/m_w2 and a derived message pointer,
where the seed has different named wrapper storage and NetCommandMsg *.
Progress serializers can replace the seed's inheritance-bearing type with
an incomplete view lacking base getters. Other donors fail on NetCommandRef
declaration order, missing NetGameCommandMsg::addArgument, or NetPacketO1's
ICoord2D/BaseType redefinitions. Rva00592520Read fails byte verification.

This is a completed scope trial, not evidence of a standalone row regression.
A coherent command/reference class prerequisite should be tested before
retrying these donors. Five mixed Common/WWLib files remain untouched. The
blocked verdict is tool-recorded in re_attempts.log against init at 0x0058D10A.

The outgoing source batch is the in-place font data repair 0466001e3f, with
no path moves. `git log origin/master..HEAD` identifies outgoing commits;
the two-dot name diff also contains inverse incoming changes while origin
advances. The three-dot source diff confirms no outgoing path move or new
consumer repoint is needed. This evidence/log commit adds no source changes.
No byte growth, file reduction, identity retirement or linking gain is claimed
for NetPacket. No maintainer-only runner was started.
