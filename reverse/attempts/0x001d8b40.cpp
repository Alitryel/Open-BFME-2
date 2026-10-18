// _LoopDeringBlock
// partial score=0.9908396946564886 date=2026-10-18
// cl: /O2 /G6 /DNDEBUG /MD
// Clean-Room: reverse/vp6_cleanroom/specs/001d8b40.md
// Spec, retail and this repository's bank only. No decoder reference source.
#include <stdlib.h>
#include <string.h>
struct Vp6DeringThresholds {
    unsigned char unknown[0x453c];
    unsigned int deringThreshold[256];
};
extern "C" void __cdecl LoopDeringBlock(void *instance,unsigned char *buffer,unsigned int stride,unsigned int width,unsigned int height)
{
    unsigned int x,y;
    unsigned char minimum=255,maximum=0;
    unsigned char *scan=buffer;
    unsigned int high;
    int threshold;
    unsigned char temp[16];
    const struct Vp6DeringThresholds *context;
    int range;

    for (y=0;y<height;++y) {
        for (x=0;x<width;++x) {
            unsigned char pixel=*scan;
            if(pixel<minimum)minimum=pixel;
            if(pixel>maximum)maximum=pixel;
            ++scan;
        }
        scan+=stride-width;
    }
    context=(const struct Vp6DeringThresholds *)instance;
    high=context->deringThreshold[maximum];
    threshold=(int)context->deringThreshold[255-minimum];
    if((unsigned int)threshold<=high)threshold=(int)high;
    range=maximum-minimum;
    threshold=(int)((unsigned int)*(volatile int *)&threshold+(unsigned int)(range>>5));

    instance=buffer;
    for (y=0;y<height;++y) {

        if (width>0) {
        unsigned char *current=((unsigned char *)instance);
        for (x=0;x<width;++x) {
            int diffRight=abs(current[0]-current[1]);
            int diffLeft=abs(current[0]-current[-1]);
            int sum=2*(*(volatile unsigned char *)current);
            if(diffLeft<=threshold)sum+=current[-1]; else sum+=current[0];
            if(diffRight<=threshold)sum+=current[1]; else sum+=current[0];
            temp[x]=(unsigned char)((sum+2)>>2);
            ++current;
        }
        }
        memcpy(instance,temp,width);
        instance=((unsigned char *)instance)+stride;
    }
    for (x=0;x<width;++x) {
        unsigned char *above;
        unsigned char *below;
        unsigned char *destination;
        instance=buffer+x;
        above=((unsigned char *)instance)-stride;
        below=((unsigned char *)instance)+stride;
        for (y=0;y<height;++y) {
            int diffBottom=abs(*((unsigned char *)instance)-*below);
            int diffTop=abs(*((unsigned char *)instance)-*above);
            int sum=2*(*((unsigned char *)instance));
            if(diffTop<=threshold)sum+=*above; else sum+=*((unsigned char *)instance);
            if(diffBottom<=threshold)sum+=*below; else sum+=*((unsigned char *)instance);
            temp[y]=(unsigned char)((sum+2)>>2);
            above+=stride;
            instance=((unsigned char *)instance)+stride;
            below+=stride;
        }
        destination=buffer+x;
        for (y=0;y<height;++y) {
            *destination=temp[y];
            destination+=stride;
        }
    }
}
