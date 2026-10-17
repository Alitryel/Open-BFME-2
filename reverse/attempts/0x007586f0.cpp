// ?rva007586F0@Rva007586F0@@QAEXXZ
// partial score=0.491 date=2026-10-17
// ?rva007586F0@Rva007586F0@@QAEXXZ
// partial score=0.699 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva007586F0@Rva007586F0@@QAEXXZ
// partial score=0.69872 date=2026-10-14
// cl: /O2 /G6 /MD
// Unverified reconstruction of retail 0x007586F0 (460B), WB 0x1802EC0.
// Neither build names this method. Structural names below are descriptive,
// not original identities. Node links/key and table size are retail evidence.
// BF1 a7c38d3b BfmeConv597.cpp has adjacent collision-manager record offsets
// but does not implement this sorting method; it is not its semantic donor.
struct SortNode {
    SortNode *previous, *next;
    unsigned unknown08, unknown0c;
    float key;
};
struct SortChain {
    SortNode *head, *tail;
    unsigned count;
    void prepend(SortNode *n) { SortNode *old=head; head=n; n->next=old; ++count; }
    SortNode *pop() { --count; SortNode *n=head; head=n->next; return n; }
    void append(SortNode *n) {
        if(count==0) { head=tail=n; count=1; }
        else { tail->next=n; tail=n; ++count; }
    }
};
class Rva007586F0 {
public:
    void rva007586F0();
    char unknown00[12];
    SortNode *heads[(0xc068-12)/4];
    unsigned count;
};
void Rva007586F0::rva007586F0()
{
    for(unsigned index=0;index<count;++index) {
        SortChain lists[4];
        unsigned side=0;
        lists[0].count=lists[1].count=0;
        lists[0].head=0;
        SortNode *node=heads[index];
        while(node) {
            SortNode *next=node->next;
            SortNode *old=lists[side].head;
            lists[side].head=node;
            node->next=old;
            ++lists[side].count;
            side ^= 1;
            _ReadWriteBarrier();
            _ReadWriteBarrier();
            node=next;
        }
        unsigned source=0;
        unsigned run=1;
        while((source ? lists[source+1].count : lists[source+1].count)) {
            _ReadWriteBarrier();
            SortChain *a=&lists[source], *b=&lists[source+1];
            source^=2;
            lists[source].count=lists[source+1].count=0;
            unsigned output=source;
            while(a->count) {
                unsigned left=run, right=run;
                for(;;) {
                    SortChain *chosen;
                    if(left && a->count) {
                        if(right && b->count && b->head->key<a->head->key) {
                            --right; chosen=b;
                        } else { --left; chosen=a; }
                    } else {
                        if(!right || !b->count) break;
                        --right; chosen=b;
                    }
                    SortNode *picked=chosen->pop();
                    SortChain &destination=lists[output];
                    destination.append(picked);
                }
                output^=1;
                _ReadWriteBarrier();
            }
            run<<=1;
        }
        if(lists[source].count>1) lists[source].tail->next=0;
        heads[index]=lists[source].head;
        heads[index]->previous=0;
        for(SortNode *p=heads[index];p->next;p=p->next)
            p->next->previous=p;
    }
}
