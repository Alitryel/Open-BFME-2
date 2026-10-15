// _LoopDeringBlock
// partial score=0.880916030534351 date=2026-10-15
// cl: /O2 /DNDEBUG /MD /ICode/Libraries/Source/VP6 /ICode
// Clean-Room: reverse/vp6_cleanroom/specs/001d8b40.md
// Native 1D8B40..1D8DCF: complete 655-byte cdecl leaf; no relocations.
// Implemented from the approved spec, retail and this repository only.
// Intended home: Code/Libraries/Source/VP6/LoopFilter.cpp; extend its existing
// Vp6LoopFilterInstance through +453C with the 256-entry threshold table.
// Removed the prior uninitialized threshold condition, equal-arm expressions
// and barriers. A volatile local retains the intermediate max-table value;
// this is a compiler-shape inference, not evidence of an original qualifier.
// Current measured aligned-byte score: 577/655 (.880916), versus 572/655
// for the old bank; remaining differences are threshold/row register homes,
// pixel-load scheduling and loop alignment. Equal extent is not exactness.
// 196 cases compare candidate, native and an independent spec oracle:
// dimensions 0/1/2/7/8/15/16, pitches 32/64, constant/random/alternating data;
// full image buffer, context, cdecl stack and callee-saved registers checked.
// No production source, pin, alias, header or gate changes.
#include <stdlib.h>
#include <string.h>
struct Vp6LoopFilterInstance {
    unsigned char prefix[0x453C];
    unsigned int deringThreshold[256];
};

extern "C" void LoopDeringBlock(Vp6LoopFilterInstance *context,unsigned char *buffer,unsigned int stride,unsigned int width,unsigned int height)
{
    unsigned int x,y;
    unsigned char minimum=255,maximum=0;
    unsigned char *scan=buffer;
    unsigned int high; volatile unsigned int level;
    int threshold;
    unsigned char temp[16];
    unsigned char *row;
    for (y=0;y<height;++y) {
        for (x=0;x<width;++x) {
            unsigned char pixel=*scan;
            if(pixel<minimum)minimum=pixel;
            if(pixel>maximum)maximum=pixel;
            ++scan;
        }
        scan+=stride-width;
    }
    high=context->deringThreshold[maximum];
    level=context->deringThreshold[255-minimum];
    if(level<=high)level=high;
    threshold=(int)level+((maximum-minimum)>>5);
    row=buffer;
    for (y=0;y<height;++y) {
        unsigned char *current=row;
            for (x=0;x<width;++x) {
            int diffRight=abs(current[0]-current[1]);
            int diffLeft=abs(current[0]-current[-1]);
            unsigned int sum=2*current[0];
            if(diffLeft<=threshold)sum+=current[-1]; else sum+=current[0];
            if(diffRight<=threshold)sum+=current[1]; else sum+=current[0];
            temp[x]=(unsigned char)((sum+2)>>2);
            ++current;
        }
        memcpy(row,temp,width);
        row+=stride;
    }
    for (x=0;x<width;++x) {
        unsigned char *current=buffer+x;
        unsigned char *above=current-stride;
        unsigned char *below=current+stride;
        unsigned char *destination;
        for (y=0;y<height;++y) {
            int diffBottom=abs(*current-*below);
            int diffTop=abs(*current-*above);
            int sum=2*(*current);
            if(diffTop<=threshold)sum+=*above; else sum+=*current;
            if(diffBottom<=threshold)sum+=*below; else sum+=*current;
            temp[y]=(unsigned char)((sum+2)>>2);
            above+=stride;
            current+=stride;
            below+=stride;
        }
        destination=buffer+x;
        for (y=0;y<height;++y) {
            *destination=temp[y];
            destination+=stride;
        }
    }
}
