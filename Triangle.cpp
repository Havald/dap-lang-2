#pragma once
#include "Simplex.cpp"

class Triangle : public Simplex {
public:
	Triangle(const Simplex &TheSimplex):Simplex(TheSimplex){
		if(TheSimplex.size() != 3) {
			throw "Could not initialize triangle: wrong dimension";
		}
	}
	double Girth() {
		Point firstPoint = this->at(0), secondPoint = this->at(1), thirdPoint = this->at(2);
		return firstPoint.EuclidDistanceTo(secondPoint) + secondPoint.EuclidDistanceTo(thirdPoint) + thirdPoint.EuclidDistanceTo(firstPoint);
	}
	
	friend ostream& operator<<(ostream &TheOstream, Triangle &me) {
		TheOstream << "Triangle {";
		for(unsigned int i = 0; i < me.size(); i++) {
			TheOstream << me.at(i);
			(i < me.size() - 1) ? TheOstream << ", " : TheOstream << "";
		}
	TheOstream << "} has Girth " << me.Girth();
		return TheOstream;
	}
};
