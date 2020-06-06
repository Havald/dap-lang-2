#include "Line.cpp"


PointArray CalculateHull(const PointArray &AllPoints) { // Nach JarvisMarch
	size_t i;
	size_t collinCount = 0;
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
		if(collinCount == AllPoints.size()) break; // Abbruch falls alle Punkte eine linie sind
		endPoint = AllPoints[0];
		for(size_t j = 0; j < AllPoints.size(); j++) {
			Line templinePQ(hullPoints[i], endPoint);
			int isLeft = templinePQ.PointLeft(AllPoints[j]);
			if((endPoint == pointOnHull) || isLeft == 1) {
				cout << isLeft << ":" << AllPoints[j] - hullPoints[0] << ":" << endPoint - hullPoints[0] << endl;
				endPoint = AllPoints[j];
			}
			if(isLeft == 0) { 
				if(i == 0) collinCount++; // Kollinearität mitzählen, um im seltenen Fall, dass alle Punkte auf einer Linie liegen, abbrechen zu können.
				if(AllPoints[j] - hullPoints[i] > endPoint - hullPoints[i]) endPoint = AllPoints[j]; // Wenn der kollineare Punkt weiter entfernt ist, aktualisieren.
			}
		}
		i++;
		
		pointOnHull = endPoint;
	} while(endPoint != hullPoints[0]);
	return hullPoints;
}

int main(int argc, char *argv[]) {
	size_t paramAmount;
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
				
			for(size_t i = 0; i < paramAmount; i++) { //fall 1: n 2-D punkte werden zufällig erstellt
				allPoints.push_back(Point{((double) (2*rand()) / (RAND_MAX)) - 1, ((double) (2*rand()) / (RAND_MAX)) - 1});
			}
		} else if(argc % 2 == 1) {
			coordinates.resize(argc - 1); //1.argument = aufruf
			for(size_t i = 1; i < (size_t)argc; i++) {
				if (!(istringstream(argv[i]) >> dec >> coordinates.at(i - 1))){
					throw "All Point Coordinates must be of type double. \n Usage: ConvexHull { x1 y1 x2 y2 x3 y3 ... }";
				} 
			}
			
			for(size_t i = 0; i < coordinates.size(); i += 2) { //fall 2: punkte werden übergeben
				allPoints.push_back(Point{coordinates.at(i), coordinates.at(i + 1)});
			}
		} else {
			throw "Number of points has to be even";
		}
		PointArray ConvexHull = CalculateHull(allPoints);
		cout << "Set of " << allPoints.size() << " points is:" << endl;
		cout << allPoints << endl << endl;
		
		if(ConvexHull.size() > 2) {
			cout << "Convex hull is built clockwise from the following " << ConvexHull.size() << " points:" << endl;
			cout << ConvexHull << endl;
		} else if(ConvexHull.size() == 2) {
			cout << "All Points are collinear. Start + Endpoint of Line are: " << endl;
			cout << ConvexHull << endl;
		} else {
			cout << "Hull needs at least 2 different points to build." << endl;
		}
	} catch (const char *Reason) {
		cerr << Reason << endl;
		exit(1);
	}
	return 0;
}