// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native29A224..29A23E returns a full32-bit0/1 when the argument is the
// non-null radar window at1430. The command-hint caller checks the low byte.
// Named from ZH Radar::isRadarWindow (same compare, called from the command
// hint as in ZH InGameUI); keeps the measured int result.
class GameWindow;
class Radar {public:char pad10[0x10];bool hidden,forced;char pad12[0x1430-0x12];GameWindow *window;int isRadarWindow(GameWindow *);};
int Radar::isRadarWindow(GameWindow *value) { GameWindow *gameWindow=window; if(gameWindow==value && gameWindow) return 1; return 0; }
