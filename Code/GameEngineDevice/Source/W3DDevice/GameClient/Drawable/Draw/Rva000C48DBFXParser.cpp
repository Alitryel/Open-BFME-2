// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// Parser and its shared constructor live beside the scripted event updater.
class INI;
void rva000C48DB(void*,void*,void*,void*);

// The two "FXEvent" FieldParse parsers that feed the reader above, as the
// clean BF1 ParseFXEvent.cpp donor (575ba2b0) shapes them: reject a null
// block, then pass three interior slots. 0x000C4B8A is the animation-state
// table's entry (beside "Animation", "ParticleSysBone", "LuaEvent"), the
// donor's parseFXEvent: slots +0x78, +0x84 and +0x74. 0x000C4B61 is the
// model-condition-state table's (beside "ParticleSysBone", "OverrideTooltip",
// "RetainSubObjects"): the same three slots at +0xB8, +0xC4 and +0xB4.
void rva000C4B61(INI *ini, void *instance, void *store, const void *userData)
{
 char *state=(char *)instance;
 if(state==0)
  return;
 rva000C48DB(ini,state+0xB8,state+0xC4,state+0xB4);
}

void parseFXEvent(INI *ini, void *instance, void *store, const void *userData)
{
 char *state=(char *)instance;
 if(state==0)
  return;
 rva000C48DB(ini,state+0x78,state+0x84,state+0x74);
}
