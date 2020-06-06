#pragma once
#include "Simplex.cpp"

class Triangle : public Simplex { 
public:
	Triangle(const Simplex &TheSimplex):Simplex(TheSimplex){
		if(TheSimplex.size() != 3) { //drei punkte gegeben?
			throw "Could not initialize triangle: wrong dimension";
		}
		if((this->at(0) == this->at(1)) || (this->at(0) == this->at(2)) || (this->at(1) == this->at(2))) { //verschiedene punkte gegeben?
			throw "Could not initialize triangle: All Points need to be different";
		}
	}

	double Girth() {
		Point firstPoint = this->at(0), secondPoint = this->at(1), thirdPoint = this->at(2);
		return firstPoint.EuclidDistanceTo(secondPoint) + secondPoint.EuclidDistanceTo(thirdPoint) + thirdPoint.EuclidDistanceTo(firstPoint); //umfang = addition der seitenlängen
	}
	
	friend ostream& operator<<(ostream &TheOstream, Triangle &me) {
		TheOstream << "Triangle {";
		for(size_t i = 0; i < me.size(); i++) { //gib die punkte durch , getrennt aus
			TheOstream << me.at(i);
			(i < me.size() - 1) ? TheOstream << ", " : TheOstream << "";
		}
		TheOstream << "} has Girth " << me.Girth(); //gib den umfang des dreiecks aus
		return TheOstream;
	}
};
