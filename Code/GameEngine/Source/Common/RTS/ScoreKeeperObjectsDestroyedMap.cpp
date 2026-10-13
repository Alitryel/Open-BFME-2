// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ScoreKeeper::getObjectsDestroyedMap, retail 0x0039C3AC..0x0039C40A (94
// bytes). Returns the per-player-index count map from the twenty-entry
// array at +0x1FC (stride 12); an out-of-range index returns a function-
// local static empty map (0x00E02838, guard 0x00E02844). Callers include
// the rowed LivingWorldScoreKeeper fold at 0x004EE950. The plain STLport
// allocator gives the native tree base; /EHs gives the native frame.
#include <map>
class ThingTemplate;
// The tree units (ScoreKeeper.cpp, ScoreKeeper_insert_unique.cpp) keep these
// node allocators out of line under /O2; this /O1 unit calls them rather
// than emitting its own differing copy first in link order.
namespace _STL {
template <> _Rb_tree_node<pair<const ThingTemplate *const, int> > *
allocator<_Rb_tree_node<pair<const ThingTemplate *const, int> > >::allocate(size_t, const void *) const;
template <> _Rb_tree_node<pair<const ThingTemplate *const, int> > *
_STLP_alloc_proxy<_Rb_tree_node<pair<const ThingTemplate *const, int> > *,
    _Rb_tree_node<pair<const ThingTemplate *const, int> >,
    allocator<_Rb_tree_node<pair<const ThingTemplate *const, int> > > >::allocate(size_t);
}
typedef _STL::map<const ThingTemplate*,int> ScoreCountMap;
class ScoreKeeper {
 char pad00[0x1fc];
 ScoreCountMap objectsDestroyed[20];
public: ScoreCountMap *getObjectsDestroyedMap(int);
};
ScoreCountMap *ScoreKeeper::getObjectsDestroyedMap(int index) {
 if(index>=0 && (unsigned)index<20) return &objectsDestroyed[index];
 static ScoreCountMap emptyMap;
 return &emptyMap;
}
