// cl: /O2 /DNDEBUG /MD
// Retail 0x0073B670 (49 B, ret 0xC), among the shroud-raster helpers
// (0x0073B600 ShroudManagerImpl element ctor, 0x0073BAA0 range updaters):
// initialises an 8.8 fixed-point stepper for walking `steps` cells from
// `from` to `to`. It stores the count and, when positive, the per-step
// increment ((to - from) << 8) / steps and the start value (from << 8) plus
// half a step. Owner and member names are address-derived.
class Rva0073B670Stepper
{
public:
	void init(int from, int to, int steps);
	int advance();
private:
	int m_value;
	int m_step;
	int m_steps;
};
void Rva0073B670Stepper::init(int from, int to, int steps)
{
	m_steps = steps;
	if (steps > 0)
	{
		m_step = ((to - from) << 8) / steps;
		m_value = (from << 8) + m_step / 2;
	}
}

// Retail 0x0073B6B0 (26 B): the stepper's advance -- add the increment to the
// value and report whether steps remain after counting one down.
int Rva0073B670Stepper::advance()
{
	m_value += m_step;
	return --m_steps > 0;
}

// Retail 0x0073B6D0 (20 B) and 0x0073B6F0 (14 B): the cyclic successor and
// predecessor of an index in [0, count) that follow the stepper. Names are
// address-derived.
int Rva0073B6D0NextIndex(int index, int count)
{
	++index;
	return index == count ? 0 : index;
}

int Rva0073B6F0PrevIndex(int index, int count)
{
	if (index == 0)
		index = count;
	return index - 1;
}
