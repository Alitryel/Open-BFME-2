// cl: /Od /Ob1
// stlport
//
// Two one-off helpers from the 0x00025B00 neighbourhood, just past
// stlport_vector_voidptr's max_size/get_allocator cluster. 0x00025B00 is an
// unsigned count fill loop; 0x00025B50 is a bool
// inequality against two dereferenced ints. The inequality snapshots both
// inputs and uses unsigned arithmetic and a byte conversion for its two
// boolean normalizations. STLport's POD dispatch supplies the fill loop's
// empty tag temporary; explicit inline expansion preserves its native frame.

#include <memory>

int *rva0025B00Fill(int *first, unsigned count, const int *value)
{
	return _STL::uninitialized_fill_n(first, count, *value);
}

bool rva0025B50NotEqual(const int *a, const int *b)
{
	struct Values
	{
		int right;
		int left;
	} values;
	values.left = *a;
	values.right = *b;
	return !static_cast<unsigned char>(static_cast<unsigned>(!(static_cast<unsigned>(values.left) - static_cast<unsigned>(values.right))));
}
