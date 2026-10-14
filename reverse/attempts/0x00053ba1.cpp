// ?shouldPlayLocally@MilesAudioManager@@QAE_NPBVAudioEventRTS@@@Z
// partial score=0.8217 date=2026-10-14
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <math.h>
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <deque>
#include <list>
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <hash_map>
#include <hash_set>
#include <set>
#include <map>
#include <vector>
#include <limits>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Common/Snapshot.h"
struct XferVersion {
    unsigned char m_version;
    unsigned char m_currentVersion;
};
class Xfer {
public:
    virtual ~Xfer();
    virtual bool isLoading();
    virtual void slot02(); virtual bool isCRC(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
    virtual void xferVersion(XferVersion *version); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
    virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
    virtual void slot26(); virtual void slot27(); virtual Xfer &xferReal(float *value); virtual void slot29();
    virtual Xfer &xferUnsignedInt(unsigned int *value);
    virtual Xfer &xferInt(int *value); virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual void slot35();
    virtual Xfer &xferBool(bool *value);
};
enum INILoadType
{
    INI_LOAD_INVALID,
    INI_LOAD_OVERWRITE,
    INI_LOAD_CREATE_OVERRIDES,
    INI_LOAD_MULTIFILE
};
class Rva00601BBCHelper
{
public:
    Rva00601BBCHelper();
    virtual ~Rva00601BBCHelper();
private:
    char m_body[0x30];
};
class INI
{
public:
    INI();
    ~INI();
    unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);
private:
    void *m_file;
    AsciiString m_filename;
public:
    unsigned int m_at08;
private:
    unsigned int m_readBufferUsed;
    unsigned int m_lineNum;
    char m_buffer[0x418 - 0x14];
    const char *m_seps;
    const char *m_sepsPercent;
    const char *m_sepsColon;
    const char *m_sepsQuote;
    const char *m_blockEndToken;
    const char *m_endScriptToken;
    unsigned char m_endOfFile;
    char m_curBlockStart[0x838 - 0x431];
    Rva00601BBCHelper m_helper;
    AsciiString m_str86C;
    _STL::vector<AsciiString> m_vec870;
};
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    bool rva00050EFA(void);  // add a reference unless the count already reached zero (0x00050EFA)
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref();
private:
    long refs;
};
struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    OpaqueRefElement4() : referent(0) {}
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
typedef _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> > MusicStack;
enum MusicSystem { MUSIC_SYSTEM_0, MUSIC_SYSTEM_1 };
inline MusicSystem &operator--(MusicSystem &ms, int) { ms = (MusicSystem)(ms - 1); return ms; }
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
namespace _STL { template <> UnicodeString * __uninitialized_copy<UnicodeString *, UnicodeString *>(UnicodeString *, UnicodeString *, UnicodeString *, __false_type const &); }
namespace _STL { template <> UnicodeString * __uninitialized_fill_n<UnicodeString *, unsigned int, UnicodeString>(UnicodeString *, unsigned int, UnicodeString const &, __false_type const &); }
namespace _STL { template <> _List_node<void *> * list<void *, allocator<void *> >::_M_create_node(void *const &); }
namespace _STL { template <> void vector<UnicodeString, allocator<UnicodeString> >::_M_insert_overflow(UnicodeString *, UnicodeString const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> UnicodeString * vector<UnicodeString, allocator<UnicodeString> >::erase(UnicodeString *, UnicodeString *); }
namespace _STL { template <> void vector<UnicodeString, allocator<UnicodeString> >::push_back(const UnicodeString &); }
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::reserve(size_t);
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}
struct AudioEventChannelVolume {
    int m_channel;
    float m_volume;
};
struct RvaPair001D9F62 { AsciiString m_key; int m_value; ~RvaPair001D9F62(); };
struct AudioEventInfo {
    const _STL::vector<RvaPair001D9F62> &getSoundsVector(void) const;
    int getVolumeSlider(void);
    bool isTightlyCoupledSound(void) const;
    char at00[0x08];
    AsciiString m_audioName;                 // +0x08
    char at0C[0x1C - 0x0C]; float m_at1C; char at20[0x30 - 0x20];
    float m_at30;                            // +0x30, playAudioEvent drops a sound effect when a random draw exceeds it
    char at34[0x38 - 0x34];
    int m_at38;                              // +0x38, playAudioEvent compares it with g_00DBA4FC
    char at3C[0x44 - 0x3C];
    int m_priority;                          // +0x44
    unsigned int m_type;                     // +0x48, bit 3 global
    unsigned int m_control;                  // +0x4C, Zero Hour's AudioControl bits (AC_LOOP = 1)
    char at50[0x90 - 0x50];
    float m_at90;                            // +0x90, occlusion factor when positive
    float m_maxDistance;                     // +0x94
    float m_minDistance;                     // +0x98
    char at9C[0xA4 - 0x9C];
    float m_atA4;                            // +0xA4, distance occlusion weight
    float m_reverbWetLevel;                  // +0xA8, wet level scaled by the global reverb multiplier (0x52FA0)
    float m_reverbDryLevel;                  // +0xAC, dry level passed with it (0x52FA0)
    int m_atB0;                              // +0xB0, processRequest preloads a file when 2
    char atB4[0xB8 - 0xB4];
    _STL::vector<AudioEventChannelVolume> m_channelVolumes;  // +0xB8
};
class AudioEventRTS;
struct BfmePoolHolder88;
class BfmePoolRef10 {
public:
    BfmePoolRef10() : m_ptr(0) {}
    __declspec(noinline) BfmePoolRef10(BfmePoolHolder88 *p) : m_ptr(reinterpret_cast<AudioEventRTS *>(p)) { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Add_Ref(); }
    __declspec(noinline) BfmePoolRef10(const BfmePoolRef10 &other) : m_ptr(other.m_ptr) { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Add_Ref(); }
    ~BfmePoolRef10() { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Release_Ref(); }
    AudioEventRTS *operator->(void) const { return m_ptr; }
    AudioEventRTS *get(void) const { return m_ptr; }
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva00053D26(BfmePoolHolder88 *p);  // assign from a raw event (0x00053D26)
    void rva000519BD(void);                 // release then null (0x000519BD)
private:
    AudioEventRTS *m_ptr;
};
class AudioEventRTS {
public:
    bool isPositionalAudio(void) const;
    ObjectID getObjectID(void);
    unsigned int getSoundClass(void) const;
    bool hasMoreLoops(void) const;
    void generatePlayInfo(void);
    void rva002D9ADC(void);
    void advanceNextPlayPortion(void);
    int getNextPlayPortion(void) const { return m_portionToPlayNext; }
    const AudioEventInfo *getAudioEventInfo(void) const { return m_info; }
    AsciiString getFilename(void);
    void decrementNumberOfEventsNeedingToBeDoneBeforeReplaying(void) { --m_at14; }
    void setNumberOfTimesToPlayMusicOrMultisound(int times) { m_loopCount = times; }
    const AsciiString &getAt84(void) const { return *reinterpret_cast<const AsciiString *>(m_at84); }
    char at00[0x08];
    AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
    int m_playingHandle;     // +0x0C, copied into a requeued loop's request
    AudioEventRTS *m_at10;   // +0x10, owning reference to the event waiting on this one (0x002D9AD4 sets it)
    int m_at14;              // +0x14, events still to finish before that one replays
    char at18[0x2C - 0x18];
    float m_at2C;            // +0x2C, volume (kept across 0x000563FE's event xfer)
    int m_viewType;          // +0x30
    int getViewType(void) const { return m_viewType; }
    char at34[0x38 - 0x34];
    int m_ownerType;         // +0x38, 2 when object-owned (getObjectID's test)
    char at3C[0x4A - 0x3C];
    bool m_at4A;             // +0x4A, playAudioEvent tests it on type-1 streams
    bool m_at4B;             // +0x4B
    bool m_at4C;             // +0x4C, the loop-buffer thread's decay/loop test
    char at4D[0x4F - 0x4D];
    bool m_at4F;             // +0x4F, cleared by playAudioEvent
    bool m_at50;             // +0x50, set once a sample starts playing
    char at51[0x52 - 0x51];
    bool m_at52;             // +0x52, playAudioEvent tests it after starting a stream
    bool m_at53;
    char at54[0x64 - 0x54];
    float m_at64;            // +0x64, compared with AudioSettings +0xB4 and one frame
    char at68[0x74 - 0x68];
    int m_portionToPlayNext; // +0x74, the portion advanceNextPlayPortion steps
    MusicSystem m_musicSystem; // +0x78
    int m_loopCount;         // +0x7C, -12345 loops forever (0x00051E7D)
    int m_at80;              // +0x80, holds against a stop request (0x000562CF adds one)
    char m_at84[4];          // +0x84, an AsciiString (see getAt84)
};
struct MilesSoundInfo {
    int m_format;                        // +0x00
    const void *m_dataPtr;               // +0x04, AILSOUNDINFO data_ptr
    unsigned int m_dataLen;              // +0x08, AILSOUNDINFO data_len
    unsigned int m_rate;                 // +0x0C
    unsigned int m_bits;                 // +0x10
    int m_channels;                      // +0x14
    char at18[0x24 - 0x18];
};
struct OpenAudioFile {
    AsciiString m_fileName;              // +0x00
    char at04[0x08 - 0x04];
    MilesSoundInfo m_soundInfo;          // +0x08
    void *m_fileImage;                   // +0x2C
    char at30[0x3C - 0x30];
    int m_at3C;                          // +0x3C, re-requested by name while below 2
};
class Rva000A8A6C {
public:
    void rva000A8A6C(void);
    bool isOpen(void) const { return m_ptr != 0; }
    int getAt3C(void) const { return m_ptr ? m_ptr->m_at3C : 0; }
    const AsciiString &getFileName(void) const { return m_ptr ? m_ptr->m_fileName : AsciiString::TheEmptyString; }
    const MilesSoundInfo *getMilesSoundInfo(void) const { return m_ptr ? &m_ptr->m_soundInfo : 0; }
    void *getFileImage(void) const { return m_ptr ? m_ptr->m_fileImage : 0; }
private:
    OpenAudioFile *m_ptr;
};
class Rva000A8B04 {
public:
    void rva000A8B04(float first, float second);
};
class Rva000A8B23 { public: void rva000A8B23(int loopCount); };
class Rva000A8AB4 { public: void rva000A8AB4(void); };
class Rva000A8B59 { public: bool rva000A8B59(int x); };
struct Rva0010FFA2Packet;
class Rva000A8B4B { public: void rva000A8B4B(int callback); };
class Rva000A8C6E { public: void rva000A8C6E(const Rva0010FFA2Packet *packet); };
class Rva000A8B31 { public: void rva000A8B31(float position, int arg); };
class Rva000A8ACC { public: void rva000A8ACC(void); };
class MilesStreamRef { public: void rva000A8AC0(void); };
class Rva000A8AD8 { public: void rva000A8AD8(float level); };
class Rva000A8D0B { public: void rva000A8D0B(void *owner, const AsciiString &file, int arg); };
struct PlayingAudio {
    void *vfptr;
    long refs;
    int m_handle;                        // +0x08 loop-buffer / handle-state index
    Rva000A8B04 m_at0C;                  // +0x0C, type-4 receiver of the reverb level pair (0x52FA0)
    char at0D[0x14 - 0x0D];
    int m_type;                          // +0x14
    int m_status;                        // +0x18
    BfmePoolRef10 m_event;            // +0x1C
    Rva000A8A6C m_file;                  // +0x20
    Coord3D m_at24;                      // +0x24, last position 0x55C5D tested
    float m_at30;                        // +0x30, compared with settings +0x78 (0x59CE6)
    float m_at34;                        // +0x34, scales the 3D effects level (0x52FA0)
    int m_at38;                          // +0x38, area index 0x55C5D starts from
    float m_at3C;                        // +0x3C, extra volume handed to a requeued loop
    float m_at40;                        // +0x40, cleared once that volume is handed on
    bool m_at44;                         // +0x44, tested with +0x46 by checkForNaturalSoundCompletion
    bool m_at45;                         // +0x45, set when a pushed track resumes
    bool m_at46;                         // +0x46
    bool m_at47;                         // +0x47, fade-up-from-shroud flag (processFade)
    bool m_at48;                         // +0x48, overrides +0x44/+0x46 in that test
    bool m_at49;                         // +0x49
    bool m_at4A;                         // +0x4A
    bool m_at4B;                         // +0x4B, set by 0x000535A6
    bool m_at4C;
    bool m_at4D;                         // +0x4D, raise the event's script flag on release (0x5FDCA)
    bool m_at4E;                         // +0x4E, m_at24 holds a position
    bool m_at4F;                         // +0x4F, set when 0x5634C hands on a new extra volume
};
class Rva000A8C9B {
public:
    __declspec(noinline) void clear(void)
    {
        if (m_ptr) {
            m_ptr->Release_Ref();
            m_ptr = 0;
        }
    }
    void rva000A8CE5(OpaqueRefCounted *value);
private:
    OpaqueRefCounted *m_ptr;
};
class PlayingAudioRef {
public:
    PlayingAudioRef() : m_ptr(0) {}
    PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr) { if (m_ptr) asRefCounted()->Add_Ref(); }
    PlayingAudioRef(PlayingAudio *playing);
    ~PlayingAudioRef() { if (m_ptr) asRefCounted()->Release_Ref(); }
    PlayingAudioRef &operator=(const PlayingAudioRef &other)
    {
        if (this != &other) {
            if (other.m_ptr)
                other.asRefCounted()->Add_Ref();
            if (m_ptr)
                asRefCounted()->Release_Ref();
            m_ptr = other.m_ptr;
        }
        return *this;
    }
    PlayingAudio *operator->(void) const { return m_ptr; }
    PlayingAudio *get(void) const { return m_ptr; }
    void clear(void) { if (m_ptr) { asRefCounted()->Release_Ref(); m_ptr = 0; } }
    void set(PlayingAudio *playing)
    {
        reinterpret_cast<Rva000A8C9B *>(this)->rva000A8CE5(reinterpret_cast<OpaqueRefCounted *>(playing));
    }
private:
    OpaqueRefCounted *asRefCounted(void) const { return reinterpret_cast<OpaqueRefCounted *>(m_ptr); }
    PlayingAudio *m_ptr;
};
inline bool operator==(const PlayingAudioRef &left, const PlayingAudioRef &right)
{
    return left.get() == right.get();
}
class Rva002D9AD4 {
public:
    BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other);
};
PlayingAudioRef::PlayingAudioRef(PlayingAudio *playing) : m_ptr(playing)
{
    if (m_ptr)
        asRefCounted()->Add_Ref();
}
struct Rva00051107AudioRequest {
    int m_request;
    BfmePoolRef10 m_pendingEvent;         // +0x04
    unsigned int m_at08;                  // +0x08 (target stores one argument)
    Rva000A8A6C m_file;                   // +0x0C, preloaded by processRequest
    bool m_at10;                             // +0x10
    bool m_at11;
    bool m_at12;
    bool m_at13;
    bool m_at14;
    char at15[0x18 - 0x15];
};
typedef _STL::list<Rva00051107AudioRequest *> Rva00051107AudioRequestList;
struct Rva00051B89Hash {
    unsigned int operator()(const Rva00051107AudioRequest *req) const
    {
        unsigned int handle = reinterpret_cast<unsigned int>(req);
        if (req)
            handle = req->m_at08;
        return handle;
    }
    unsigned int operator()(const struct Rva00051B89Keyed *req) const
    {
        return (*this)(reinterpret_cast<const Rva00051107AudioRequest *>(req));
    }
};
struct Rva00050E1CEqualTo {
    bool operator()(const Rva00051107AudioRequest *left, const Rva00051107AudioRequest *right) const
    {
        if (left && right)
            return left->m_at08 == right->m_at08;
        return left == right;
    }
};
typedef _STL::hash_set<Rva00051107AudioRequest *, Rva00051B89Hash, Rva00050E1CEqualTo>
    Rva00051107AudioRequestSet;
class Rva00691040Handle {
public:
    Rva00691040Handle &operator=(const Rva00691040Handle &other);
private:
    void *m_target;
};
class AudioFileContainer {
public:
    AudioFileContainer();
    ~AudioFileContainer();
    bool isValid(void) const { return m_target != 0; }
    operator const Rva00691040Handle &() const { return *reinterpret_cast<const Rva00691040Handle *>(this); }
    const AsciiString &getFileName(void) const { return m_target ? m_target->m_fileName : AsciiString::TheEmptyString; }
    const MilesSoundInfo *getMilesSoundInfo(void) const { return m_target ? &m_target->m_soundInfo : 0; }
    void *getFileImage(void) const { return m_target ? m_target->m_fileImage : 0; }
private:
    OpenAudioFile *m_target;
};
AudioFileContainer::AudioFileContainer() : m_target(0)
{
}
class Rva00690FF0Handle {
public:
    Rva00690FF0Handle();
    ~Rva00690FF0Handle();
    bool isValid(void) const { return m_target != 0; }
    operator const Rva00691040Handle &() const { return *reinterpret_cast<const Rva00691040Handle *>(this); }
    const AsciiString &getFileName(void) const { return m_target ? m_target->m_fileName : AsciiString::TheEmptyString; }
    const MilesSoundInfo *getMilesSoundInfo(void) const { return m_target ? &m_target->m_soundInfo : 0; }
    void *getFileImage(void) const { return m_target ? m_target->m_fileImage : 0; }
    int getAt3C(void) const { return m_target ? m_target->m_at3C : 0; }
    AudioFileContainer rva000A89E3(void) const;  // a new reference once ready (0x000A89E3)
private:
    OpenAudioFile *m_target;
};
class AudioFileCache {
public:
    Rva00690FF0Handle requestFile(const BfmePoolRef10 &event, int shortSound);
    Rva00690FF0Handle requestFile(const AsciiString &fileName, int priority);
};
class Rva00050DBD { public: bool rva00050DBD(); };
class Rva00050DD0 { public: bool rva00050DD0(); };
class Rva002D94FEDwordSlot { public: void set(int value); };
struct Rva0005E13CArg;
class Rva0005E13CHost {
public:
    bool rva0005E13C(const Rva0005E13CArg *request);
};
class Rva000CB12FByteField {
public:
    unsigned char get(void) const;
};
class Rva0051D93 {
public:
    Rva0051D93(const OpaqueRefElement4 &reference, int value30);
    Rva0051D93(const struct BfmeAudioEventPrefix136 &source);
private:
    char opaque[0x90];
};
class Rva002D94CE { public: void rva002D94CE(int value); };
class Weapon { public: void setLeechRangeActive(bool value); };
class Rva002D9BDC { public: void rva002D9BDC(float lo, float hi); };
class Rva00481FAFFloatSlot { public: void store(float value); };
class Rva002D9FD9Arg;
class Rva002D9FD9Owner { public: void rva002D9FD9(Rva002D9FD9Arg *xfer); };
class Rva002DA153 { public: float rva002DA153(void); };
class Rva002D94DD { public: float rva002D94DD(void) const; };
class PolygonTrigger {
public:
    bool rva002E3A39(const Coord3D &pos);
    int getID(void) const { return m_triggerID; }
private:
    char at00[0x44];
    int m_triggerID;
};
class Object { public: bool isInside(PolygonTrigger *trigger); };
extern GameLogic *TheGameLogic;
inline float sqr(float value) { return value * value; }
class Coord2D
{
public:
    Coord2D() {}
    Coord2D(const Coord3D &that) : x(that.x), y(that.y) {}
    Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
    ~Coord2D() {}
    Coord2D &Sub(const Coord3D &that) { x -= that.x; y -= that.y; return *this; }
    float GetLengthSqrd() const { return x * x + sqr(y); }
    float x;
    float y;
};
struct LineSegment2D {
    LineSegment2D(const Coord2D &start, const Coord2D &end);
    Coord2D m_start;
    Coord2D m_end;
};
Coord2D ClosestPointOnLineSegment(const LineSegment2D &segment, const Coord2D &point);
struct AudioAreaCorner {
    Coord3D m_pos;
    bool m_valid;                        // +0x0C
};
class Rva00051CA2 {
public:
    Rva00051CA2();
    ~Rva00051CA2();
private:
    float x, y, z;
    bool active;
};
class Rva0005276C {
public:
    Rva0005276C();
    ~Rva0005276C() {}
private:
    Rva00051CA2 slots[5];
};
class Rva00051CF1 { public: bool rva00051CF1(Rva00051CF1 &other); };
struct AudioTriggerArea {
    PolygonTrigger *m_trigger;
    float m_level;
};
struct AudioTriggerAreaSave {
    int m_triggerID;
    float m_level;
};
template<> void _STL::vector<AudioTriggerAreaSave, _STL::allocator<AudioTriggerAreaSave> >::push_back(const AudioTriggerAreaSave &value);
struct BfmeEventPositionView : public Coord3D {};
struct Rva0005BA08InfoRef;
struct MicrophoneSettings {
    float m_at00;                        // +0x00, fraction past the far limit
    float m_at04;                        // +0x04, squared-distance scale
    float m_at08;                        // +0x08, numerator between the limits
    float m_at0C;                        // +0x0C, near squared limit
    float m_at10;                        // +0x10, numerator past the far limit
    float m_at14;                        // +0x14, far squared limit
    float m_at18;                        // +0x18, pull toward corner 0
    float m_at1C;                        // +0x1C, attenuation start distance
    float m_at20;                        // +0x20, squared distance below which nothing attenuates
    float m_at24;                        // +0x24, attenuation end distance
    float m_at28;                        // +0x28, squared end distance
    float m_at2C;                        // +0x2C, maximum attenuation
    float m_at30;                        // +0x30
    float m_at34;                        // +0x34
    float m_at38;                        // +0x38, outer corner distance
    float m_at3C;                        // +0x3C, outer squared limit
    float m_at40;                        // +0x40, inner corner distance
    float m_at44;                        // +0x44, inner squared limit
};
struct AudioSettings {
    char at00[0x30];
    float m_at30[5];                     // +0x30, init()'s per-index 0x524EE volumes
    char at44[0x64 - 0x44];
    int m_at64;                          // +0x64, with +0x68 init()'s loop-buffer count
    int m_at68;                          // +0x68
    char at6C[0x74 - 0x6C];
    int m_at74;
    int m_at78;                          // +0x78, compared with a loop's +0x30 (0x59CE6)
    int m_at7C;
    unsigned int m_at80;                 // +0x80, handed to the file cache's 0xA77D9
    char at84[0x8C - 0x84];
    unsigned int m_at8C;                 // +0x8C, over +0x90 the loop-buffer thread's sleep
    unsigned int m_at90;                 // +0x90
    char at94[0xA8 - 0x94];
    int m_atA8;                          // +0xA8, seconds before 0x61C87 reopens the device
    int m_atAC;                          // +0xAC, seconds before the update reopens the device
    float m_atB0;                        // +0xB0, position change 0x55C5D ignores
    int m_atB4;                          // +0xB4, processRequest's preload limit
    float m_atB8;
    bool m_atBC;                         // +0xBC, disables occlusion
    char atBD[0xC0 - 0xBD];
    float m_atC0;                        // +0xC0, occlusion floor
    char atC4[0x12C - 0xC4];
    MicrophoneSettings m_microphoneSettings[3]; // +0x12C
};
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_distances(void *sample, float maxDistance, float minDistance);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(void *sample, float x, float y, float z);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_orientation(void *obj, float xFace, float yFace, float zFace, float xUp, float yUp, float zUp);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_volume(void *sample, float volume);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_reverb_levels(void *sample, float dry, float wet);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_effects_level(void *sample3D, float level);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_occlusion(void *sample3D, float occlusion);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_playback_rate(void *sample);
typedef void (__stdcall *MilesSampleCallback)(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_init_sample(void *sample);
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_info(void *sample3D, const MilesSoundInfo *info);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_type(void *sample, int format, unsigned int flags);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_address(void *sample, const void *start, unsigned int len);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_playback_rate(void *sample, int rate);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_loop_count(void *sample, int loops);
extern "C" __declspec(dllimport) MilesSampleCallback __stdcall AIL_register_EOS_callback(void *sample, MilesSampleCallback callback);
extern "C" __declspec(dllimport) int __stdcall AIL_set_sample_file(void *sample, const void *fileImage, int block);
extern "C" __declspec(dllimport) void __stdcall AIL_start_sample(void *sample);
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_file(void *sample, const void *fileImage);
extern "C" __declspec(dllimport) MilesSampleCallback __stdcall AIL_register_3D_EOS_callback(void *sample, MilesSampleCallback callback);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_loop_count(void *sample, int loops);
extern "C" __declspec(dllimport) void __stdcall AIL_start_3D_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_playback_rate(void *sample, int rate);
extern float g_00DBA4FC;
extern float g_Va00BBDA30;
struct Rva0005A084Element { int m_value; };
typedef _STL::vector<Rva0005A084Element> Rva0005A084Vector;
extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex();
extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex();
class NameKeyGenerator
{
public:
    class KeyToBucketMap
    {
    public:
        struct value_type
        {
            value_type(unsigned int f, void *s) : first(f), second(s) {}
            value_type(const unsigned int &a, const unsigned int &b) : first(a), second(reinterpret_cast<void *>(b)) {}
            unsigned int first;
            void *second;
        };
        struct insert_result
        {
            void *first;
            KeyToBucketMap *second;
            bool inserted;
        };
        struct equal_result
        {
            void *node;
            KeyToBucketMap *table;
        };
        insert_result insert(const value_type &value);
        equal_result rva00057C5C(const value_type &value);
    };
};
typedef _STL::hash_multimap<unsigned int, int> MilesKeyAliases;
typedef _STL::hash_map<unsigned int, int> MilesPhysicalHandles;
class AILMutexScope {
public:
    AILMutexScope() { AIL_lock_mutex(); m_locked = true; }
    ~AILMutexScope() { if (m_locked) AIL_unlock_mutex(); }
    void unlock(void) { if (m_locked) { AIL_unlock_mutex(); m_locked = false; } }
private:
    bool m_locked;
};
typedef MilesKeyAliases::iterator::_Node MilesAliasNode;
typedef MilesKeyAliases::iterator::_Hashtable MilesAliasTable;
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<MilesAliasNode>::deallocate(MilesAliasNode *p, size_t n) const
{ if (p != 0) ::free((void *)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<unsigned int, MilesAliasNode, allocator<MilesAliasNode> >::deallocate(MilesAliasNode *p, size_t n)
{ static_cast<allocator<MilesAliasNode>&>(*this).deallocate(p, n); }
template<> __declspec(dllimport) __forceinline
void MilesAliasTable::_M_delete_node(MilesAliasNode *p)
{ _Destroy(&p->_M_val); _M_num_elements.deallocate(p, 1); }
}
typedef _STL::hash_map<unsigned int, void *> MilesHandleMap;
namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(T value) const;
	};
	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}
enum NameKeyType;
class DamageFX { public: int m_valueWords[0x1E0]; };
typedef _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ExistingRangeErase;
namespace _STL { template<> void ExistingRangeErase::erase(ExistingRangeErase::iterator, ExistingRangeErase::iterator); }
typedef _STL::hash_map<AsciiString, UnicodeString,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > MilesFileTextMap;
class MilesMutexGuard {
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
    bool rva00041037(int timeout);       // waits up to timeout ms for the lock
private:
    void *m_mutex;
    bool m_held;
};
struct AudioLODSettings {
    unsigned short m_maxAmbientStreams;
    char at02[2];
    unsigned char m_at04;    // +0x04, Dolby provider allowed (0x51525)
    char at05[3];
};
class GameLODManager {
public:
    char at0000[0x218];
    AudioLODSettings m_audioLODSettings[2];  // +0x218
    char at0228[0x1770 - 0x228];
    int m_audioLOD;                          // +0x1770
};
extern GameLODManager *TheGameLODManager;
struct BfmePod8 {
    int m_at00;
    int m_viewType;
};
namespace _STL {
template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *);
}
class Rva00056CF8 {
public:
    void rva00057B74(void);
    unsigned int rva0005B633(const AsciiString &key);
    ~Rva00056CF8();
private:
    char opaque[0x10];
};
struct Rva000515E4Key {
    int a;
    float b;
};
bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y);
typedef _STL::list<PlayingAudioRef> PlayingAudioList;
typedef _STL::list<OpaqueRefElement4> OpaqueRefList;
struct BfmeStringTailRecord144 {
    virtual ~BfmeStringTailRecord144();
    char at04[0x08 - 0x04];
    AudioEventInfo *m_info;                // +0x08, named by the 0x000609A1 sweep
    unsigned int m_playingHandle;  // +0x0C
    char at10[0x88 - 0x10];
    float m_at88;
    bool m_at8C;
    char at8D[3];
};
typedef _STL::vector<BfmeStringTailRecord144> QueuedAudioEvents;
template<> QueuedAudioEvents::iterator QueuedAudioEvents::erase(iterator first, iterator last);
class AudioEventInfoRef {
public:
    __declspec(noinline) AudioEventInfoRef(const AudioEventInfo *info) : m_ptr(reinterpret_cast<OpaqueRefCounted *>(const_cast<AudioEventInfo *>(info))) { if (m_ptr) m_ptr->Add_Ref(); }
    ~AudioEventInfoRef() { if (m_ptr) m_ptr->Release_Ref(); }
    AudioEventInfo *get(void) const { return (AudioEventInfo *)m_ptr; }
private:
    OpaqueRefCounted *m_ptr;
};
class Rva002D9508 {
public:
    void rva002D9508(const void *value);
};
class Rva002D9576 {
public:
    int rva002D9576(void);
};
class Rva00059FBBMap {
public:
    AudioEventInfo *&rva00059FBB(const AsciiString &name);
private:
    char opaque[0x14];
};
class Rva001F8437 {
public:
    void *rva001F8437(const AsciiString &key);
};
struct BfmeNode1105;
BfmeNode1105 *__cdecl bfmeNext1105(BfmeNode1105 *node);
class Rva0005F279Host { public: void rva0005F279(void); };
class SubsystemInterface {
public:
    virtual ~SubsystemInterface();
private:
    bool m_flag;
    AsciiString m_name;
};
class MilesAudioManager : public SubsystemInterface, public Snapshot {
public:
    virtual void init(); virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
    virtual void rva00062690(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void rva00061C87(unsigned int viewMask);
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
    virtual void slot25(); virtual void removePlayingAudio(const AsciiString &eventName, int viewType); virtual void slot27();
    virtual bool killAudioEventImmediately(unsigned int handle); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
    virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
    virtual void slot55(); virtual bool slot56(unsigned int soundClass); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
    virtual void slot65(); virtual void slot66(); virtual void rva000533CB(); virtual void slot68(); virtual void slot69();
    virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
    virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &name) const;
    virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79(); virtual void slot80();
    virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
    virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89(); virtual void slot90();
    virtual void slot91(); virtual void slot92();
    virtual void rva0005824D(PolygonTrigger *trigger, float level);
    virtual void rva000551C2(PolygonTrigger *trigger);
    virtual void slot95();
    virtual void slot96(); virtual void slot97();
    virtual void onAudioLODChanged(void);
    virtual void slot99(); virtual void slot100();
    virtual void slot101(); virtual void slot102(); virtual void slot103(); virtual void slot104();
    virtual void slot105(Coord3D *cameraPos);
    virtual void slot106(Rva0005276C *corners);
    virtual bool rva000516EF(const Coord3D *pos);
    virtual bool slot108(AudioEventRTS *); virtual float slot109();
    virtual void rva000541DB(void);
    bool rva00055FCA(int key, void **result, PlayingAudioRef *playingOut);
    bool rva00055E6C(const AsciiString &name, int streamArg, int viewType, int musicSystem);
    bool rva0005623E(int key, void **result, int flags);
    void rva000563FE(Xfer *xfer, int handle);
    void rva0005634C(int handle, float volume, int mode);
    bool rva00054899(ObjectID objectID, int otherID);
    bool rva00056670(ObjectID objectID);
    bool rva00055426(int objectID);
    float getGlobalReverbMultiplier(void);
    void rva00053AFA(void *pendingSlot);
    void rva000562CF(int key);
    void friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef);
    void rva000562A2(int key, const void *value);
    void rva0005A92A(int key, Rva0005A084Vector *output);
    void rva0005AE2B(int type, Rva0005A084Vector *output);
    void rva0005AEDD(int type, Rva0005A084Vector *output);
    void rva0005B137(void);
    void recalculateMicrophone(void);
    bool rva0005538C(void);
    void rva0005BE59(void *slot, float value, void *index);
    void rva0005E377(const AsciiString &key, int viewType);
    void rva0005DAFC(int viewType);
    int rva0005A7BE(AudioEventRTS *event, int arg1);
    void rva0005AF92(AudioEventInfo *info);
    AsciiString rva0005B19E(const AsciiString &key);
    AsciiString rva0005B1FA(const AsciiString &key);
    void rva0005407E(INI *ini);
    void rva000540A7(INI *ini);
    unsigned char rva00054120(INI *ini);
    bool rva00061BD2(int unused);
    void rva0006179C(int opaque);
    AsciiString rva00054714(void);
    PlayingAudioList::iterator rva000544CB(int viewType, int musicSystem, int filter);
    PlayingAudioList::iterator rva0005442A(int viewType, int musicSystem, int filter);
    void rva00057297(Rva00051107AudioRequest &request);
    bool rva000570C8(AudioEventRTS *event);
    void addUnownedAudioEventInfo(AudioEventInfo *eventInfo);
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
    bool killLowestPrioritySoundImmediately(AudioEventRTS *event);
    int rva00054596(void);
    int rva0005456B(void);
    float rva0005A9F8(void *ref, int a, int b);
    float rva00059AD0(void *event, int a);
    void unmapPhysicalHandle(unsigned int handle);  // WorldBuilder name (0x000578B3)
    void mapLogicalHandleToPhysicalHandle(unsigned int logical, unsigned int physical);
    void rva00057948(const void *input);
    void rva000577E3(unsigned int affect, unsigned int viewMask, bool value);
    class GlobalVolumeData {
    public:
        static void setGlobalSystemVolume(int volumeType, float volume);
        void reset(void);
        void rva00052048(int index);
        void rva00052015(int arg);
        unsigned char rva000520F4(const AudioEventInfoRef &, int);
        float rva0005910F(AudioEventRTS *event);
        void refreshAll(void);
        void rva0005213E(const MicrophoneSettings *settings, const Coord3D *delta);
        void rva0005CE7E(Xfer *transfer);
        void rva000521F4(float elapsed);
        void rva000520C6(void);
        int m_myViewFocus;                         // +0x00 (WB assert name)
        float m_volumes[6][2];                     // +0x04
        float m_product[6];                        // +0x34
        _STL::vector<BfmePod8> m_requests[6];      // +0x4C
        float m_at94;                              // +0x94
        float m_at98;
        float m_at9C;                              // +0x9C
        _STL::set<AsciiString> m_names;            // +0xA0
        char atAC[0xC4 - 0xAC];
        bool m_atC4;                               // +0xC4
        char atC5[0x1B8 - 0xC5];
        Rva00056CF8 m_at1B8;                       // +0x1B8
    };
    void setMaxAmbientStreams(void);
    void notifyOf2DSampleCompletion();
    void notifyOf3DSampleCompletion();
    void internalSetReverbRoomType(int roomType);
    bool shouldUseDolbyProvider();
    void rva0005452B(void);
    void rva000606CE(bool accelerated);
    void rva00060123(unsigned int viewMask);
    void rva00056FD9(unsigned int viewMask);
    void rva0005B256(Xfer *xfer, PlayingAudioRef &playing, int *unused);
    bool rva000613A9(unsigned int handle);
    bool rva006AD9B0(void);    // 0x00059646, cached reinitialize setting
    void rva0005E0A4(void);    // 0x0005E0A4 (pinned), called by the update
    void rva0005B708(void);    // 0x0005B708 (rowed in MilesAudioSubtitleDrain.cpp)
    void rva0005F2BB(class Rva00052B3D *state);
    void processAmbientStreams(PlayingAudioList::iterator *streams);
    void rva00060309(void);
    void rva000583BA(unsigned int affect, unsigned int viewMask, int arg);
    void rva00058591(unsigned int affect, unsigned int viewMask, int keepMasks);
    void rva0006047C(void);
    void rva000603ED(void);
    void rva000544EB(void);
    void startPendingMusicTracks(void);
    void processPlayingList(Rva00052B3D *streams);
    int rva00052F1E(void *);
    void adjustPlayingVolume(void *ref);
    bool processFade(PlayingAudioRef &playing);
    void openDevice(void);
    void removeCurrentlyPlayingMusic(int viewType, int arg);
    void rva00057151(int viewType, int musicSystem, int resume);
    void moveDownMusicSystems(int viewType, MusicSystem newMusicSystem, int arg, int resume);
    void rva0005774F(int viewType, int musicSystem, int arg);
    void rva0005876E(int viewType, int musicSystem, int arg, int resume);
    bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
    int pushMusicEventInternal(AudioEventRTS *event, int arg1, int arg2, int append);
    int addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int arg4, int arg5);
    BfmePoolRef10 rva0005286A(AudioEventRTS *event, int arg);
    void rva000592B8(AudioEventRTS *event);
    bool shouldPlayLocally(const AudioEventRTS *event);
    void rva00055A58(int viewType, int musicSystem, int arg, int flag);
    void rva00055B40(int viewType, int musicSystem, int arg);
    void rva000567F4(int viewType, int musicSystem, int arg);
    void rva000568CE(int viewType, int musicSystem, int arg);
    void rva000569A8(int viewType, int musicSystem, int arg, int flag);
    Rva00051107AudioRequest *rva00051107(void);
    void processRequest(Rva00051107AudioRequest *req, bool *removeRequest);
    void processRequestList(void);
    void deleteAudioRequest(void *req);
    bool rva00053606(Rva00051107AudioRequest *req);
    void rva00053646(Rva00051107AudioRequest *req, bool *removeRequest);
    void playAudioEvent(Rva00051107AudioRequest *req);
    void rva0005FA3C(unsigned int handle);
    void processPushMusicRequest(Rva00051107AudioRequest *req);
    PlayingAudioRef allocatePlayingAudio(void);
    void processPopMusicRequest(Rva00051107AudioRequest *req);
    void onPlayingAudioDeleted(PlayingAudio &playingAudioBeingDeleted);
    void releaseMilesHandles(PlayingAudio &playing);
    void moveUpMusicSystems(int newMusicSystem, int viewType, int arg);
    void rva0005AC61(int viewType, int newMusicSystem, int arg);
    bool startNextLoop(PlayingAudioRef &looping);
    void getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &playing, void **sample, void **sample3D);
    void *get2DSampleHandleForPlayingAudio(void *playing);
    void *get3DSampleHandleForPlayingAudio(PlayingAudioRef &playing);
    void prep3DSample(PlayingAudioRef &playing, const Coord3D *pos);
    void initFilters3D(PlayingAudioRef &playing, const Coord3D *pos);
    void setOcclusionLevels(PlayingAudioRef &playing, const Coord3D *pos);
    float rva00053854(const Coord3D *pos);
    void rva00055C5D(PlayingAudioRef &playing, bool *result);
    void rva00052FA0(PlayingAudioRef &playing);
    void rva000581FA(const Rva0005BA08InfoRef &info, int viewType);
    void rva000535A6(PlayingAudioRef &playing);
    void pauseResumeSound(PlayingAudioRef &playing);
    void prepSample(void *playing);
    BfmeEventPositionView Rva0005160FGet(AudioEventRTS *event, bool &valid);
    bool playSample(PlayingAudioRef &playing);
    bool playSample3D(PlayingAudioRef &playing);
    bool playSample2DOr3DUsingCallbackBuffers(PlayingAudioRef &playing, void *sample, void *sample3D);
    void rva000564C0(unsigned int sample);
    void rva0005653C(unsigned int sample3D);
    void rva0005DB6C(const AsciiString &fileName);
    void rva000565B8(unsigned int stream);
    struct LoopBuffer;
    void transferBytesToPlayBuffer(LoopBuffer &buffer, unsigned int position);
    void putFileIntoLoopBuffer(LoopBuffer *buffer, const AudioFileContainer &file, int arg);
    void cleanUpLoopBuffer(LoopBuffer *buffer);
    void checkForNaturalSoundCompletion(PlayingAudioRef &playing);
    unsigned int addOrResumeAudioEvent(AudioEventRTS *event, int a, int b, int c, int d);
    void processAudioCompletion(PlayingAudioRef &completedAudio);
    void playAndStoreStream(PlayingAudioRef &playing, const Rva0010FFA2Packet *resumePosition);
    void rva0005EFE9(void);
    void putPlayingMusicOnStack(int viewType, int arg);
    void rva00059CE6(PlayingAudioRef &looping);
    void rva0005AA72(PlayingAudioRef &playing);
private:
    void unselectProvider(void);
    void selectProvider(bool accelerated);
public:
    unsigned int getProviderIndex(const AsciiString &providerName) const;
    void init3DSamplePools();
    void createListener();
protected:
    virtual void loadPostProcess(void);
public:
    virtual void xfer(Xfer *transfer);
private:
    AudioSettings *m_audioSettings;      // +0x10 (Zero Hour name)
    char at14[0x18 - 0x14];
    Coord3D m_micPos;                    // +0x18, Miles listener position
    Coord3D m_micDir;                    // +0x24, Miles listener facing
    Coord3D m_cameraPos;                 // +0x30, camera at the last recalculation
    AudioAreaCorner m_corners[5];        // +0x3C, entries 1..4 used by 0x53854
    float m_at8C;                        // +0x8C, distance occlusion scale
    float m_at90;                        // +0x90, zeroed by every xfer
    int m_at94;                          // +0x94, zeroed by 0x61C87
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    Rva00051107AudioRequestSet m_requestSet;        // +0x9C
    char atB0[0xBC - 0xB0];
    Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
    unsigned int m_nextHandle;           // +0xD0, next playing handle (0x0005B256)
    unsigned int allocateNewHandle(void) { return m_nextHandle++; }
    char atD4[0xE0 - 0xD4];
    QueuedAudioEvents m_queuedEvents[3];  // +0xE0, per view type (0x60123)
    MilesKeyAliases m_handleAliases;       // +0x104
    MilesPhysicalHandles m_physicalHandles; // +0x118
    char m_volumeData[3][0x1C4];         // +0x12C
    int m_at678;                         // +0x678, compared with event view types
    char at67C[0x684 - 0x67C];
    int m_num2DSamplesPlaying;           // +0x684, counted up by playAudioEvent
    int m_num3DSamplesPlaying;           // +0x688, counted up by playAudioEvent
    int m_at68C;                         // +0x68C, zeroed by 0x60309
    unsigned int m_at690;                // +0x690, per-view-type bits 0x61C87 clears
    unsigned int m_at694;                // +0x694, view types whose music is paused for affect bit 0x20 (0x583BA)
    unsigned int m_at698;                // +0x698, per-view-type bits processAudioCompletion clears
    unsigned short m_maxAmbientStreams;  // +0x69C
    char at69E[0x6A4 - 0x69E];
    bool m_at6A4;                        // +0x6A4
    bool m_at6A5;                        // +0x6A5, marks a view-type change (0x5DAFC, xfer)
    bool m_forceHeadphones;             // +0x6A6, provider speaker override
    bool m_at6A7;                        // +0x6A7, read by 0x52F4C and 0x53AFA
    bool m_at6A8;                        // +0x6A8, cleared by the update
    bool m_at6A9;                        // +0x6A9, set by the update when areas need a retest
    bool m_at6AA;                        // +0x6AA, retest areas on every call (0x55C5D)
    bool m_at6AB;                        // +0x6AB, set by loadPostProcess
    bool m_at6AC;                        // +0x6AC, cleared by loadPostProcess
    char at6AD[0x6B0 - 0x6AD];
    int m_at6B0;                         // +0x6B0, zeroed by a loading xfer
    unsigned int m_at6B4[3];             // +0x6B4 per-view-type affect masks
    unsigned int m_at6C0[3];             // +0x6C0
    struct ProviderInfo { AsciiString name; void *id; int isValid; };
    ProviderInfo m_provider3D[64];       // +0x6CC
    unsigned int m_providerCount;        // +0x9CC
    unsigned int m_selectedProvider;     // +0x9D0, -1 when none
    void *m_mutex;                       // +0x9D4
    char at9D8[0x9E0 - 0x9D8];
    void *m_listener;                    // +0x9E0 (Zero Hour name), unselectProvider closes it
    char at9E4[0x9E8 - 0x9E4];
    MilesFileTextMap m_fileText;         // +0x9E8
    _STL::vector<UnicodeString> m_pendingFileText;  // +0x9FC
    _STL::vector<AsciiString> m_unknownFileNames;   // +0xA08
    _STL::set<AsciiString> m_atA14[3];   // +0xA14, per view type (0x61C87)
    _STL::list<void *> m_availableSamples;    // +0xA38 (Zero Hour's name)
    _STL::list<void *> m_available3DSamples;  // +0xA3C (Zero Hour's name)
    PlayingAudioList m_playingSounds;    // +0xA40
    PlayingAudioList m_playing3DSounds;  // +0xA44
    PlayingAudioList m_playingStreams;   // +0xA48
    MusicStack m_musicStack[3][2];       // +0xA4C
    MusicSystem m_activeMusicSystem[3];  // +0xB3C
    PlayingAudioRef m_playingMusic[3];   // +0xB48, the active system's stream per view type
    _STL::vector<AudioTriggerArea> m_triggerAreas;  // +0xB54, scanned by 0x55C5D
    _STL::vector<AudioTriggerAreaSave> m_savedTriggerAreas;  // +0xB60, resolved by loadPostProcess
    char atB6C[0xB78 - 0xB6C];           // +0xB6C, cleared through the rowed 0x00054B9A
    char atB78[0xB8C - 0xB78];           // +0xB78, cleared through the rowed 0x00056DA2
    AudioFileCache *m_audioFileCache;    // +0xB8C (WorldBuilder requestFile receiver)
    void *m_atB90;                       // +0xB90, handed to the stream opener 0x000A8D0B
    PlayingAudioList m_completedAudio;   // +0xB94, filled by the EOS handlers
    MilesHandleMap m_sampleMap;          // +0xB98
    MilesHandleMap m_3DSampleMap;        // +0xBAC
    MilesHandleMap m_streamMap;          // +0xBC0
    LoopBuffer *m_loopBuffers;           // +0xBD4 (WB assert name)
    int m_numLoopBuffers;                // +0xBD8
    void *m_loopBufferThread;            // +0xBDC, CreateThread handle
    bool m_atBE0;                        // +0xBE0, stops the 0x5EFE9 thread loop
    char atBE1[0xBE4 - 0xBE1];
    int m_atBE4;                         // +0xBE4, reverb room type (0x530DF zeroes it)
    class SubTitleWindow *m_subTitleWindow; // +0xBE8, deleted by the update once finished
    unsigned int m_atBEC;                // +0xBEC, view types reset since the last update
    int m_selectedSpeakerType;          // +0xBF0, provider-selection speaker type
    char atBF4[0xBF8 - 0xBF4];
    __int64 m_atBF8;                     // +0xBF8, _time64 of the last device open
    bool m_atC00;                        // +0xC00, view type 2 is transferred when set (version 3+)
};
class Rva002D9AC3 { public: const char *rva002D9AC3(); };



class Rva0036CA00Str {
public:
    // The select-any copy 0x000A8C7C (Rva0036CA00StrCopy.cpp), visible here
    // so cl knows the copy keeps no pointer to itself.
    __declspec(noinline) Rva0036CA00Str(const Rva0036CA00Str &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Add_Ref();
    }
    ~Rva0036CA00Str() { reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Release_Ref(); }
    PlayingAudio *operator->(void) const { return m_ptr; }
    PlayingAudio *get(void) const { return m_ptr; }
private:
    PlayingAudio *m_ptr;
};

// MilesAudioManager::shouldPlayLocally, retail 0x00053BA1 (320 B; WB 0x007A88A0,
// MilesAudioManager.cpp:14080..14109). Zero Hour's AudioManager test with
// BFME's two owner kinds: music (+0xB0 sound type 0) and type 3, sounds with
// no player restriction (+0x48 bits 0x20/0x40/0x80/0x100) and "everyone"
// sounds always play. A game-owned event (+0x30 kind 0) compares its owning
// player with the local one (the player bit when they are the same, else
// the allies or enemies bit by relationship to the local default team); a
// living-world event (kind 1) compares its owner with the living-world local
// player and its alliance test. The info reference (+0x08) is held counted.
class BfmeMemberRV;
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(void); };
class Team;
enum Relationship { REL_ENEMIES, REL_NEUTRAL, REL_ALLIES };
class Player
{
public:
    Relationship getRelationship(const Team *that) const;
    char at000[0x2EC];
    Team *m_defaultTeam;    // +0x2EC
};
class PlayerList { public: Player *getNthPlayer(int index); };
extern PlayerList *ThePlayerList;
class Rva002DA414 { public: void *rva002DA414(void); };
class Rva002D9C7A { public: int rva002D9C7A(void); };
class Rva002B2B66 { public: int rva002B2B66(void); };
class Rva002E071E { public: int rva002E0BC0(int playerID); };
struct LivingWorldLogicAudioView
{
    char at00[0x98];
    Rva002E071E *m_localPlayer;     // +0x98
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

bool MilesAudioManager::shouldPlayLocally(const AudioEventRTS *event)
{
    Rva0036CA00Str infoRef(*reinterpret_cast<const Rva0036CA00Str *>(&event->m_info));
    const AudioEventInfo *ei = reinterpret_cast<const AudioEventInfo *>(infoRef.get());

    if (ei->m_atB0 == 0 || ei->m_atB0 == 3 || (ei->m_type & 0x1E0) == 0 || (ei->m_type & 0x100))
        return true;

    if (event->m_viewType == 0)
    {
        if (!ThePlayerList)
            return true;
        Player *localPlayer = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
        Player *owningPlayer = ThePlayerList->getNthPlayer((int)((Rva002DA414 *)event)->rva002DA414());
        if ((ei->m_type & 0x20) && (ei->m_type & 1) && owningPlayer == 0)
            return true;
        if (owningPlayer == 0 || localPlayer == 0 || localPlayer->m_defaultTeam == 0)
            return false;
        if (owningPlayer == localPlayer)
            return (ei->m_type >> 5) & 1;
        if (owningPlayer->getRelationship(localPlayer->m_defaultTeam) == REL_ALLIES)
            return (ei->m_type >> 6) & 1;
        return (ei->m_type >> 7) & 1;
    }
    if (event->m_viewType == 1)
    {
        int owner = ((Rva002D9C7A *)event)->rva002D9C7A();
        if (((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66() == owner)
            return (ei->m_type >> 5) & 1;
        Rva002E071E *local = ((LivingWorldLogicAudioView *)TheLivingWorldLogic)->m_localPlayer;
        if (local && (unsigned char)local->rva002E0BC0(owner))
            return (ei->m_type >> 6) & 1;
        return (ei->m_type >> 7) & 1;
    }
    return true;
}
