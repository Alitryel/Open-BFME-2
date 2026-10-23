#pragma once
// TU-scoped BFME2 override of reference/open-bfme-1/.../GameClient/video_player.h for window_video_manager.cpp.
// BFME2 retail calls VideoStreamInterface through its vtable:
//   +0x1C close()            (WindowVideo dtor 0x53F10E, playMovie 0x53F63D failure path)
//   +0x38 attach(VideoBuffer*) -> bool (playMovie 0x53F69E)
//   +0x3C getVideoBuffer()   (WindowVideo::getVideoBuffer 0x53F0BF, setWindowState 0x53F06C, init 0x53F165)
// The remaining slot names are placeholders for the (still unmatched) update/playMovie bodies.
#include "ascii_string.h"
class VideoBuffer {
public:
	int allocate(unsigned int w, unsigned int h);
	void close(void);
	unsigned int width(void);
	unsigned int height(void);
};
class VideoStreamInterface {
public:
	virtual void streamSlot00( void ) = 0;
	virtual void update( void ) = 0;
	virtual int isFrameReady( void ) = 0;
	virtual void frameDecompress( void ) = 0;
	virtual void frameRender( VideoBuffer *buffer ) = 0;
	virtual void frameNext( void ) = 0;
	virtual int frameUpdate( int flags ) = 0;
	virtual void close( void ) = 0;
	virtual int frameIndex( void ) = 0;
	virtual unsigned int width( void ) = 0;
	virtual unsigned int height( void ) = 0;
	virtual void streamSlot11( void ) = 0;
	virtual void streamSlot12( void ) = 0;
	virtual void streamSlot13( void ) = 0;
	virtual bool attach( VideoBuffer *buffer ) = 0;
	virtual VideoBuffer *getVideoBuffer( void ) = 0;
};
// BFME2 retail: WindowVideoManager::playMovie (0x53F63D) opens through vtable +0x44 with (AsciiString, 0)
class VideoPlayerInterface {
public:
	virtual void playerSlot00( void ) = 0;
	virtual void playerSlot01( void ) = 0;
	virtual void playerSlot02( void ) = 0;
	virtual void playerSlot03( void ) = 0;
	virtual void playerSlot04( void ) = 0;
	virtual void playerSlot05( void ) = 0;
	virtual void playerSlot06( void ) = 0;
	virtual void playerSlot07( void ) = 0;
	virtual void playerSlot08( void ) = 0;
	virtual void playerSlot09( void ) = 0;
	virtual void playerSlot10( void ) = 0;
	virtual void playerSlot11( void ) = 0;
	virtual void playerSlot12( void ) = 0;
	virtual void playerSlot13( void ) = 0;
	virtual void playerSlot14( void ) = 0;
	virtual void playerSlot15( void ) = 0;
	virtual void playerSlot16( void ) = 0;
	virtual VideoStreamInterface* open( AsciiString movieTitle, int flags ) = 0;
};
extern VideoPlayerInterface* TheVideoPlayer;
