// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ??1VideoPlayer@@UAE@XZ: Code/GameEngine/Source/GameClient/VideoPlayer.cpp

// Open-BFME5: VideoPlayer destructor ? clear global singleton then chain bases

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class VideoPlayerBase : public SubsystemInterface
{
public:
	virtual ~VideoPlayerBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/VideoPlayer.h
class VideoPlayer : public VideoPlayerBase
{
public:
	virtual ~VideoPlayer();
};

extern class VideoPlayerInterface *TheVideoPlayer;

// empty intermediate so MSVC emits its vtbl store then jumps to SubsystemInterface
// ??1VideoPlayerBase@@ present-unmatched
VideoPlayerBase::~VideoPlayerBase()
{
}

// ??1VideoPlayer@@UAE@XZ
inline VideoPlayer::~VideoPlayer()
{
	if (this == ((VideoPlayer *)TheVideoPlayer))
		(*(VideoPlayer **)&TheVideoPlayer) = 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeVideoPlayerInlineAnchor@@YAXPAVVideoPlayer@@@Z absent-from-retail
void _bfmeVideoPlayerInlineAnchor(VideoPlayer *p)
{
    p->VideoPlayer::~VideoPlayer();
}
#pragma inline_depth()
