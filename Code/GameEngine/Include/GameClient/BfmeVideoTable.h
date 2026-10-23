#pragma once

// Native video-table storage, VA 0x00E0ABB4: begin/end/capacity at +0/+4/+8.
// getVideo and the count/index readers independently establish begin/end;
// addVideo and the verified 28-byte vector overflow establish capacity.
// All 12 loaded bytes are zero in game.dat. This is a shared ABI view of
// retail's STLport vector storage; its original global name is unknown.
struct BfmeVideoTableStorage
{
    void *begin;
    void *end;
    void *capacity;
};
extern BfmeVideoTableStorage g_bfmeVideoTableStorage;
