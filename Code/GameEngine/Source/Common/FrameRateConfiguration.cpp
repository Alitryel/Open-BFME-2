// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native238895..238954,191B; RET0. Frame-rate arithmetic and existing named
// globals establish purpose; the original function name remains unknown.
// BF1 a7c38d3b GameCommonConvertThunk.cpp and ZH Common/GameCommon.h supply
// the semantic units. BFME2 permits a configurable logic/client rate pair.
extern int BfmeLogicFramesPerSecond, BfmeClientFramesPerSecond;
extern float g_parseDurationMsecScale, g_00DBA4F0, g_00DBA4F4;
extern float g_secondsPerLogicFrame, g_00DBA4FC, BfmeClientFramesPerMillisecond;
extern float opacityLogicStepSeconds;
// Retail9BA504 initial30.0f is the real-valued client rate between the
// per-millisecond rate9BA500 and seconds-per-client-frame9BA508.
float BfmeClientFrameRateReal = 30.0f;
void Rva00238895SetFrameRates(int logic, int client)
{
    logic = logic < 1 ? 1 : logic;
    client = client < 1 ? 1 : client;
    client = client < logic ? logic : client;
    if (client / logic > 6)
        client = logic * 6;
    BfmeLogicFramesPerSecond = logic;
    BfmeClientFramesPerSecond = client;
    g_parseDurationMsecScale = logic * 0.001f;
    g_00DBA4F0 = 1000.0f / logic;
    g_00DBA4F4 = (float)logic;
    g_secondsPerLogicFrame = 1.0f / g_00DBA4F4;
    g_00DBA4FC = 1000.0f / client;
    BfmeClientFramesPerMillisecond = client * 0.001f;
    BfmeClientFrameRateReal = (float)client;
    opacityLogicStepSeconds = 1.0f / BfmeClientFrameRateReal;
}
