#pragma once
// TU-scoped BFME2 override of reference/open-bfme-1/.../GameClient/game_window.h for window_video_manager.cpp.
// BFME2 GameWindow::winIsHidden returns bool (ledger row ?winIsHidden@GameWindow@@QAE_NXZ at 0x313CD9;
// WindowVideoManager::update 0x53F53C tests al after the call).
class VideoBuffer;
class WinInstanceData { public: void setVideoBuffer(VideoBuffer*); };
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow {
public:
	WinInstanceData* winGetInstanceData(void);
	bool winIsHidden(void);
};
