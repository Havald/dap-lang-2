#include "Line.cpp"


PointArray CalculateHull(const PointArray &AllPoints) { 
	size_t i;
	size_t collinCount = 0;
	PointArray hullPoints = PointArray{}; // Speichert die Punkte der konvexen Hülle
	Point pointOnHull = AllPoints[0]; // Zwischenspeicher für den nächsten Punkt der Hülle
	
	for(i = 1; i < AllPoints.size(); i++) { // Der Punkt mit der kleinsten X-Koordinate muss auf der Hülle liegen
		if(pointOnHull[0] > AllPoints[i][0]) {
			pointOnHull = AllPoints[i];
		}
	}
	i = 0;
	Point endPoint = Point{}; // Der aktuelle Hüllenkandidat wird zwischengespeichert
	do {
		hullPoints.push_back(pointOnHull);
		if(collinCount == AllPoints.size()) break; // Abbruch falls alle Punkte eine Linie sind
		endPoint = AllPoints[0];
		for(size_t j = 0; j < AllPoints.size(); j++) { // Vom aktuellen Punkt aus (liegt auf der Hülle) den nächsten Punkt auf der Hülle suchen
			Line templinePQ(hullPoints[i], endPoint);
			int isLeft = templinePQ.PointLeft(AllPoints[j]);
			if((endPoint == pointOnHull) || isLeft == 1) { // Wenn der überprüfte Punkt links vom aktuellen Hüllenkandidat liegt, ist er besser.
				endPoint = AllPoints[j]; 
			}
			if(isLeft == 0) { 
				if(i == 0) collinCount++; // Kollinearität mitzählen, um im seltenen Fall, dass alle Punkte auf einer Linie liegen, abbrechen zu können.
				if(AllPoints[j] - hullPoints[i] > endPoint - hullPoints[i]) endPoint = AllPoints[j]; // Wenn der kollineare Punkt weiter entfernt ist, aktualisieren.
			}
		}
		i++;
		
		pointOnHull = endPoint;
	} while(endPoint != hullPoints[0]); // Solange neue Punkte suchen, bis der Ausgangspunkt wieder erreicht wird
	return hullPoints;
}

int main(int argc, char *argv[]) {
	int paramAmount; // Anzahl der zu generierenden Punkte n
	vector<double> coordinates; // Speichert Koordinaten, falls sie direkt angegeben werden.
	PointArray allPoints = PointArray{};
	srand(time(nullptr));
	
	try{
		if(argc < 2) { // Input parsen
			throw "Usage: ConvexHull n | { x1 y1 x2 y2 x3 y3 ... }";
		}else if(argc == 2) {
			if (!(istringstream(argv[1]) >> dec >> paramAmount) || paramAmount <= 0){
				throw "Parameter n must be positive Integer.";
			}
				
			for(size_t i = 0; i < (size_t)paramAmount; i++) { // Fall 1: n 2-D punkte werden zufällig erstellt
				allPoints.push_back(Point{((double) (2*rand()) / (RAND_MAX)) - 1, ((double) (2*rand()) / (RAND_MAX)) - 1});
			}
		} else if(argc % 2 == 1) {
			try{
				coordinates.resize(argc - 1); //1.argument = aufruf
			} catch(...) {
				throw "No Memory to resize.";
			}
			for(size_t i = 1; i < (size_t)argc; i++) {
				if (!(istringstream(argv[i]) >> dec >> coordinates.at(i - 1))){
					throw "All Point Coordinates must be of type double. \n Usage: ConvexHull n | { x1 y1 x2 y2 x3 y3 ... }";
				} 
			}
			
			for(size_t i = 0; i < coordinates.size(); i += 2) { // Fall 2: punkte werden übergeben
				allPoints.push_back(Point{coordinates.at(i), coordinates.at(i + 1)});
			}
		} else {
			throw "Number of coordinates has to be even\n Usage: ConvexHull n | { x1 y1 x2 y2 x3 y3 ... }";
		}
		
		PointArray ConvexHull = CalculateHull(allPoints); // Konvexe Hülle erstellen
		
		cout << "Set of " << allPoints.size() << " points is:" << endl; // Ausgabe der gegebenen Punkte
		cout << allPoints << endl << endl;
		
		if(ConvexHull.size() > 2) { // Ausgabe der erstellten konvexen Hülle
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