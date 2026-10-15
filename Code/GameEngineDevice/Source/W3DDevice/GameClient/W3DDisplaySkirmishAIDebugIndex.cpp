// cl: /G7 /MD /EHsc /DNDEBUG
//
// BFME2 skirmish-AI debug selector, VA 0x00DB3BD8 (RVA 0x009B3BD8, .data).
// W3DDisplay::gatherSkirmishAIStats (0x0004AA4A) reads this int once per player
// loop and compares it with the running AI index to decide which skirmish AI's
// stats block is drawn; -1 (the retail initial value) selects none of them.
// No EA identifier is recovered, so the name is neutral and descriptive.
int g_bfmeSkirmishAIDebugIndex = -1;
