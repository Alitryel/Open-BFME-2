#pragma once
class GameWindow;
class WinInstanceData;

// Native script factories use one 52-byte record at VA E012D4.
// The dispatch table and callback stores establish the five named slots.
struct WindowScriptCreateRecord
{
    GameWindow *parent;
    unsigned int status;
    int x, y, width, height;
    void *winClass;
    void *system;
    void *input;
    void *draw;
    void *tooltip;
    void *unknown2c;
    WinInstanceData *instance;
};
extern WindowScriptCreateRecord g_windowScriptCreateRecord;
