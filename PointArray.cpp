#pragma once
#include "Point.cpp"

class PointArray : private vector<Point> {
public:
	using vector<Point>::size;
	using vector<Point>::operator[];

	PointArray(initializer_list<Point> args) {	
		for (auto iter = args.begin(); iter!=args.end();++iter)
			push_back(*iter);
// Alle anderen Methoden Ihrer Wahl fehlen noch!
};