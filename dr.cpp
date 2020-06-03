#include "Triangle.cpp"


int main(int argc, char *argv[]) {
	double coordinates[6];
	try{
		if(argc != 1 && argc != 7) { 
			throw "Usage: dr [ x1 y1 x2 y2 x3 y3 ]";
		}else if(argc == 7) {
			for(size_t i = 1; i < (size_t)argc; i++) {
				if (!(istringstream(argv[i]) >> dec >> coordinates[i - 1])){
					throw "All Parameters must be of type double. \n Usage: dr [ x1 y1 x2 y2 x3 y3 ]";
				} 
			}
		} else {
			srand(time(nullptr));
			for(size_t i = 0; i < 6; i++) {
				coordinates[i] = ((double) rand() / (RAND_MAX));
			}
		}
		Triangle TheTriangle(Simplex(PointArray{Point{coordinates[0], coordinates[1]},
												Point{coordinates[2], coordinates[3]},
												Point{coordinates[4], coordinates[5]}}));
												
		cout <<setiosflags(ios::fixed) << setprecision(2) << TheTriangle << endl << distance << endl;
	} catch (const char *Reason) {
		cerr << Reason << endl; // Handle Exception
		exit(1);
	}
	return 0;
}
// 0.33,0.62)(0.68,0.57)(0.26,0.85