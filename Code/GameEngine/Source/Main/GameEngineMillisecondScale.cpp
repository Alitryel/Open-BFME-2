// cl: /MD /EHsc
//
// BFME2 GameEngine frame-loop timing scale, RVA 0x007C6E68 (.rdata, double 0.001).
// GameEngine::update (0x00225DA9) multiplies the elapsed timeGetTime() milliseconds
// (as a float) by this constant to get seconds for its frames-per-second statistic.
// Retail reads it from memory as an operand (the product stays in double precision),
// so it is a datum the body references, not an inlined literal. Neutral name, no
// EA identifier recovered.
extern const double g_bfmeMillisecondsToSeconds = 0.001;
