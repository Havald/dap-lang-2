#pragma once
#include "PointArray.cpp"

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
		// cout << "TPLOMm: " << d << (d > 0.000000001 ? " true" : " false") << endl;
		return d > 0.000000001;
	}
	bool PointLeft(const Point &To) {
		// triangle_ABC= (A.y-B.y)*C.x + (B.x-A.x)*C.y + (A.x*B.y-B.x*A.y)
		// A = P1, B = P2, C = To 
		double value = ((*this)[0][1] - (*this)[1][1]) * To[0] + 
					((*this)[1][0] - (*this)[0][0]) * To[1] +
					((*this)[0][0]*(*this)[1][1]-(*this)[1][0]*(*this)[0][1]);
					// cout << "PL: " << value << (value > 0.00000001 ? " true" : " false") <<endl << endl;
		return (value > 0.00000001 ? true : false);
	}
}; 
