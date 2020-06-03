#include "Line.cpp"

// algorithm jarvis(S) is
// // S is the set of points
//// P will be the set of points which form the convex hull. Final set size is i.
// pointOnHull = leftmost point in S // which is guaranteed to be part of the CH(S)
// i := 0
// repeat
// P[i] := pointOnHull
// endpoint := S[0]      // initial endpoint for a candidate edge on the hull
// for j from 0 to |S| do
//   // endpoint == pointOnHull is a rare case and can happen only when j == 1 and a better endpoint has not yet been set for the loop
// if (endpoint == pointOnHull) or (S[j] is on left of line from P[i] to endpoint) then
// endpoint := S[j]   // found greater left turn, update endpoint
// i := i + 1
// pointOnHull = endpoint
// until endpoint = P[0]      // wrapped around to first hull point

PointArray CalculateHull2(const PointArray &AllPoints) {
	unsigned int i;
	PointArray hullPoints = PointArray{};
	Point pointOnHull = AllPoints[0];
	
	for(i = 1; i < AllPoints.size(); i++) {
		if(pointOnHull[0] > AllPoints[i][0]) {
			pointOnHull = AllPoints[i];
		}
	}
	i = 0;
	Point endPoint = Point{};
	do {
		hullPoints.push_back(pointOnHull);
		// cout << hullPoints[i] << endl;
		endPoint = AllPoints[0];
		// cout << endPoint << endl;
		for(unsigned int j = 0; j < AllPoints.size(); j++) {
			Point testpoint = AllPoints[j];
			Line templinePQ(hullPoints[i], endPoint);
			// cout << "Durchlauf " << j << ": " << testpoint << endl;
			// cout << "Line from " << hullPoints[i] << " to " << endPoint << " isLeft? returns: " << templinePQ.PointLeft(AllPoints[j]) << endl << endl;
			if((endPoint == pointOnHull) || templinePQ.PointLeft(AllPoints[j])) {
				
				// cout << pointOnHull << ", " << endPoint << ", " << testpoint << endl;
				endPoint = AllPoints[j];
			}
		}
		i++;
		pointOnHull = endPoint;
	} while(endPoint != hullPoints[0] && i < AllPoints.size());
	return hullPoints;
}



PointArray CalculateHull(const PointArray &AllPoints) {
	
	PointArray hullPoints = PointArray{};
	bool valid;
	for(unsigned int p = 0; p < AllPoints.size(); p++) {
		for(unsigned int q = 1; q < AllPoints.size(); q++) {
			if(q != p) {
				valid = true;
				Line templinePQ(AllPoints[p], AllPoints[q]);
				for(unsigned int r = 0; r < AllPoints.size(); r++) {
					if(r != p && r != q) {
						Point tempPointR(AllPoints[r]);
						if(templinePQ.PointLeft(tempPointR)) {
							valid = false;
						}
					}
				}
			}
			if(valid) {
				Point a = AllPoints.at(p);
				Point b = AllPoints.at(q);
				cout << a << endl << b << endl << endl;
				hullPoints.push_back(AllPoints[p]);
				hullPoints.push_back(AllPoints[q]);
			}
		}
	}
	cout << "5" << endl;
	return hullPoints;
}

int main(int argc, char *argv[]) {
	int paramAmount;
	vector<double> coordinates;
	PointArray allPoints = PointArray{};
	srand(time(nullptr));
	
	try{
		if(argc < 2) { 
			throw "Usage: ConvexHull n | { x1 y1 x2 y2 x3 y3 ... }";
		}else if(argc == 2) {
			if (!(istringstream(argv[1]) >> dec >> paramAmount) || paramAmount <= 0){
				throw "Parameter n must be positive Integer.";
			}
				
			for(unsigned int i = 0; i < paramAmount; i++) {
				allPoints.push_back(Point{((double) (2*rand()) / (RAND_MAX)) - 1, ((double) (2*rand()) / (RAND_MAX)) - 1});
			}
		} else if(argc % 2 == 1) {
			coordinates.resize(argc - 1);
			for(unsigned int i = 1; i < (unsigned int)argc; i++) {
				if (!(istringstream(argv[i]) >> dec >> coordinates.at(i - 1))){
					throw "All Point Coordinates must be of type double. \n Usage: dr [ x1 y1 x2 y2 x3 y3 ]";
				} 
			}
			
			for(unsigned int i = 0; i < coordinates.size(); i += 2) {
				allPoints.push_back(Point{coordinates.at(i), coordinates.at(i + 1)});
			}
		} else {
			throw "Usage: ConvexHull n | { x1 y1 x2 y2 x3 y3 ... }";
		}
		PointArray ConvexHull = CalculateHull2(allPoints);
		cout << "Set of " << allPoints.size() << " points is:" << endl;
		cout << allPoints << endl << endl;
		
		if(ConvexHull.size() > 1) {
			cout << "Convex hull is built clockwise from the following " << ConvexHull.size() << " points:" << endl;
			cout << ConvexHull << endl;
		} else {
			cout << "Hull needs at least 2 points to build." << endl;
		}
	} catch (const char *Reason) {
		cerr << Reason << endl; // Handle Exception
		exit(1);
	}
	return 0;
}