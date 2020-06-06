#pragma once
#include "PointArray.cpp"

class Simplex : private PointArray {
private:
public:
	using PointArray::size;
	using PointArray::operator[];
	using PointArray::at;
	
	Simplex(const PointArray &ThePointArray)
		: PointArray(ThePointArray)
		{
			Point i = ThePointArray[0];
			if(ThePointArray.size() != i.getDimension() + 1) { //Ein Simplex der Dimension n hat immer n+1 Punkte
				throw "Could not initialize Simplex: Dimensions of Pointarray do not fit (size has to be dimension + 1).";
			}
		}
};