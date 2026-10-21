// ?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z
// partial score=0.99 date=2026-10-21
// ?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z
// partial score=0.99 date=2026-10-20
// ?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z
// Bank for 0x0005BE59 (789 B, RET 0xC; WB twin 0x0079F2C0), BFME 2's
// view-scoped Zero Hour adjustVolumeOfPlayingAudio, in
// Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp.
// Below is the diff against that unit (as of 2026-10-12) that compiles to
// 782 B with every call, the EH frame and all register roles of retail.
// Levers that got it there:
//  * a visible __declspec(noinline) in-class copy of rva0005A9F8 that reads
//    the playing pointer BY VALUE (a `*&` reference binding counts as
//    retaining the address): only then does cl keep the PlayingAudioRef's
//    pointer in EBX (EBX=0 doubling as its initial value) across the calls,
//    as retail does;
//  * the 3D loop alone reads the event into a local and compares through the
//    inline getViewType() (retail: event in EDI, iterator spilled to memory);
//  * a `MusicStack &stack` local (begin/end copies from +0, not +0x10) and a
//    queued loop whose end is cached in the for-initialiser.
// Remaining 7 B: retail rotates the music-stack inner loop (cmp [ebp-0x30],
// esi; je at the top, with EAX carrying viewType to both exits) where cl
// emits init; jmp cond. while/do/if-break/_M_cur/!(==)/post-increment/
// end-first (0x55FCA's form)/row pointer/typed (const AsciiString&,float,int)
// signature all keep the jmp form; the volume/pan stack slots are also swapped
// (retail volume and sample3D at -0x18, pan at -0x20).
// 2026-10-20, 789 B with 0 structural regions: against the unit at c1701c17f3,
// which already carries the visible rva0005A9F8 copy and both AIL imports, the
// body only needs the appended definition below. Computing the queued loop's
// end() before its begin() makes viewType's last use the begin index, so cl
// keeps viewType in EAX across the music loops; the inner deque loop is then
// rotated with retail's natural-exit reload (mov eax,[ebp+0x10]).
// Remaining: 6 instructions in the 2D and 3D blocks use swapped frame slots
// (retail: volume, sample3D and the music counter at -0x18, pan alone at -0x20;
// ours: pan and the counter at -0x18, volume and sample3D at -0x20). A
// function-scope pan (Zero Hour's spelling) gives retail's slot grouping but
// drops the EBX PlayingAudioRef cache (766 B, 18 regions); see
// reverse/attempt_support/miles-5be59-queued-end-first-20261020.md.
#if 0
6787a6788,6862
> 
> // Retail 0x0005BE59 (pinned, RET 0xC; WorldBuilder twin 0x0079F2C0): BFME 2's
> // view-scoped form of Zero Hour's adjustVolumeOfPlayingAudio. For every
> // playing sound, 3D sound and non-music stream of the view type whose event
> // name matches (an empty name matches all) it refreshes the event's volume
> // (0x592B8) and hands the recomputed level (0x5A9F8) to the sample or stream;
> // matching music on the view's two stacks and matching queued events only get
> // the refresh (the queued loop passes the last playing event, as retail does).
> // The float argument is unused.
> void MilesAudioManager::rva0005BE59(void *slot, float value, void *index)
> {
>     const AsciiString &eventName = *reinterpret_cast<const AsciiString *>(slot);
>     int viewType = reinterpret_cast<int>(index);
>     PlayingAudioRef playing;
>     PlayingAudioList::iterator it;
>     for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
>         playing = *it;
>         if (playing.get()
>             && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                 || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
>             && playing->m_event->m_viewType == viewType) {
>             void *sample = get2DSampleHandleForPlayingAudio(&playing);
>             if (sample) {
>                 rva000592B8(playing->m_event.get());
>                 float pan;
>                 float volume = rva0005A9F8(&playing, 1, 1);
>                 AIL_sample_volume_pan(sample, 0, &pan);
>                 AIL_set_sample_volume_pan(sample, volume, pan);
>             }
>         }
>     }
>     for (PlayingAudioList::iterator it3D = m_playing3DSounds.begin(); it3D != m_playing3DSounds.end(); ++it3D) {
>         playing = *it3D;
>         if (playing.get()
>             && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                 || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)) {
>             AudioEventRTS *event = playing->m_event.get();
>             if (event->getViewType() == viewType) {
>                 void *sample3D = get3DSampleHandleForPlayingAudio(playing);
>                 if (sample3D) {
>                     rva000592B8(event);
>                     AIL_set_3D_sample_volume(sample3D, rva0005A9F8(&playing, 1, 1));
>                 }
>             }
>         }
>     }
>     for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
>         playing = *it;
>         if (playing.get()
>             && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                 || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
>             && playing->m_event->m_viewType == viewType
>             && playing->m_event->m_info->m_atB0 != 3) {
>             rva000592B8(playing->m_event.get());
>             ((Rva000A8AEE *)&playing->m_at0C)->rva000A8AEE(rva0005A9F8(&playing, 1, 1));
>         }
>     }
>     for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
>         MusicStack &stack = m_musicStack[viewType][musicSystem];
>         for (MusicStack::iterator music = stack.begin(), end = stack.end(); music != end; ++music) {
>             playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
>             if (playing.get()
>                 && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                     || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
>                 && playing->m_event->m_viewType == viewType)
>                 rva000592B8(playing->m_event.get());
>         }
>     }
>     QueuedAudioEvents::iterator queuedEnd = m_queuedEvents[viewType].end();
>     for (QueuedAudioEvents::iterator event = m_queuedEvents[viewType].begin(); event != queuedEnd; ++event) {
>         if (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>             || reinterpret_cast<const BfmeAudioEventInfoNameView *>(event->m_info)->getEventName() == eventName)
>             rva000592B8(playing->m_event.get());
>     }
> }
#endif
