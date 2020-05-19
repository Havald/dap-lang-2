#include "Triangle.cpp"

double randomNumber() {
	return ((double) rand() / (RAND_MAX));	
}

int main(int argc, char *argv[]) {
	double x1, x2, x3, y1, y2, y3;
	try{
		if(argc != 1 && argc != 7) { 
			throw "Usage: dr [ x1 y1 x2 y2 x3 y3 ]";
		}else if(argc == 7) {
			if (!(istringstream(argv[1]) >> dec >> x1)){
				throw "First Parameter x1 must be double.";
			} 
			if (!(istringstream(argv[2]) >> dec >> y1)){
				throw "Second Parameter y1 must be double.";
			} 
			if (!(istringstream(argv[3]) >> dec >> x2)){
				throw "Third Parameter x2 must be double.";
			} 
			if (!(istringstream(argv[4]) >> dec >> y2)){
				throw "Fourth Parameter y2 must be double.";
			} 
			if (!(istringstream(argv[5]) >> dec >> x3)){
				throw "Fifth Parameter x3 must be double.";
			} 
			if (!(istringstream(argv[6]) >> dec >> y3)){
				throw "Last Parameter y3 must be double.";
			} 
			
		} else {
			
	srand(time(nullptr));
			x1 = randomNumber();
			y1 = randomNumber();
			x2 = randomNumber();
			y2 = randomNumber();
			x3 = randomNumber();
			y3 = randomNumber();
		}
		PointArray PA = PointArray{Point{x1,y1},Point{x2,y2},Point{x2,y3}};
		Triangle TheTriangle(Simplex(PointArray{Point{x1,y1},Point{x2,y2},Point{x2,y3}}));
		cout << setprecision(2) << TheTriangle << endl;
	} catch (const char *Reason) {
		cerr << Reason << endl; // Handle Exception
		exit(1);
	}
	return 0;
}
// 0.33,0.62)(0.68,0.57)(0.26,0.85