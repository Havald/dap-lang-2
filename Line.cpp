#pragma once
#include "PointArray.cpp"

#define ACC 1e-9
// #define SGN(x) ((x)<−ACC ? −1 :(x)>ACC ? 1 : 0 )
#define SGN(x) ((x)< -ACC ? -1 : (x) > ACC ? 1 : 0)
class Line : private PointArray {
public:
	using PointArray::operator[];
	using PointArray::at;
	
	Line(const Point &P1, const Point &P2) :PointArray({P1,P2}) {
		if((*this)[0].getDimension() != 2) throw "Could not create line: Wrong Dimension (must be 2)";
	}
	double Length() {
		return ((*this)[0] - (*this)[1]); 
	}
	
	bool ThisfPointLeftOfMe(const Point &To) {
		Point S0=Point{(*this)[0][0]-To[0],(*this)[0][1]-To[1]};
		Point S1=Point{(*this)[1][0]-To[0],(*this)[1][1]-To[1]};
		double ax = S1[0] - S0[0];
		double ay = S1[1] - S0[1]; 
		double d = ay*S0[0] - ax*S0[1];
		return d <= 0.0;
	}
	
	int PointLeft(const Point &To) { // Berechnet, ob ein Punkt Links von der gerichteten Linie P1->P2 liegt (ähnlich ThisPointLeftOfMe, dort allerdings links von P2->P1).  
	
		double value = ((*this)[0][1] - (*this)[1][1]) * To[0] + 	// Die Berechnung erfolgt über den Umlaufsinn, den das Dreieck aus der Linie und dem Punkt To hat.
					((*this)[1][0] - (*this)[0][0]) * To[1] + 		// Wenn Value Positiv ist, wird das Dreieck mathematisch positiv durchlaufen, To liegt also links.
					((*this)[0][0]*(*this)[1][1]-(*this)[1][0]*(*this)[0][1]); // Ist Value 0, sind sie kollinear.
					
		return SGN(value); // Die Überprüfung findet mit einer Bestimmten genauigkeit statt, um die Ungenauigkeit von doubles auszugleichen. 
	}
}; 
