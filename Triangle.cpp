#pragma once
#include "Simplex.cpp"

class Triangle : public Simplex {
public:
	Triangle(const Simplex &TheSimplex):Simplex(TheSimplex){;}
	double Girth();
};