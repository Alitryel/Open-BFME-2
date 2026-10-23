#pragma once
// TU-scoped BFME2 override of reference/open-bfme-1/.../GameClient/display.h for window_video_manager.cpp.
// BFME2 retail playMovie (0x53F63D) calls TheDisplay through vtable +0xA4 with one argument
// (W3DDisplay::createVideoBuffer(bool), see W3DVideoBufferCtorBfme.cpp).
class VideoBuffer;
class DisplayInterface {
public:
	virtual void displaySlot00( void ) = 0;
	virtual void displaySlot01( void ) = 0;
	virtual void displaySlot02( void ) = 0;
	virtual void displaySlot03( void ) = 0;
	virtual void displaySlot04( void ) = 0;
	virtual void displaySlot05( void ) = 0;
	virtual void displaySlot06( void ) = 0;
	virtual void displaySlot07( void ) = 0;
	virtual void displaySlot08( void ) = 0;
	virtual void displaySlot09( void ) = 0;
	virtual void displaySlot10( void ) = 0;
	virtual void displaySlot11( void ) = 0;
	virtual void displaySlot12( void ) = 0;
	virtual void displaySlot13( void ) = 0;
	virtual void displaySlot14( void ) = 0;
	virtual void displaySlot15( void ) = 0;
	virtual void displaySlot16( void ) = 0;
	virtual void displaySlot17( void ) = 0;
	virtual void displaySlot18( void ) = 0;
	virtual void displaySlot19( void ) = 0;
	virtual void displaySlot20( void ) = 0;
	virtual void displaySlot21( void ) = 0;
	virtual void displaySlot22( void ) = 0;
	virtual void displaySlot23( void ) = 0;
	virtual void displaySlot24( void ) = 0;
	virtual void displaySlot25( void ) = 0;
	virtual void displaySlot26( void ) = 0;
	virtual void displaySlot27( void ) = 0;
	virtual void displaySlot28( void ) = 0;
	virtual void displaySlot29( void ) = 0;
	virtual void displaySlot30( void ) = 0;
	virtual void displaySlot31( void ) = 0;
	virtual void displaySlot32( void ) = 0;
	virtual void displaySlot33( void ) = 0;
	virtual void displaySlot34( void ) = 0;
	virtual void displaySlot35( void ) = 0;
	virtual void displaySlot36( void ) = 0;
	virtual void displaySlot37( void ) = 0;
	virtual void displaySlot38( void ) = 0;
	virtual void displaySlot39( void ) = 0;
	virtual void displaySlot40( void ) = 0;
	virtual VideoBuffer* createVideoBuffer( bool flag ) = 0;
};
extern DisplayInterface* TheDisplay;
