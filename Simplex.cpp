#include "PointArray.cpp"

class Simplex : private PointArray {
public:
	using PointArray::size;
	using PointArray::operator[];
	
	Simplex(const PointArray &ThePointArray)
		:PointArray(ThePointArray)
		{;}
// Alle anderen Methoden Ihrer Wahl fehlen noch!
};