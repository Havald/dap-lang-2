#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <assert.h>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <cstring>
#include <initializer_list> // Important!

using namespace std;

class Point : public vector<double> {
private:
	unsigned int dimension;
public:
	Point(initializer_list<double> args) {
		dimension = args.size();
		try {
			for(auto iter = args.begin(); iter != args.end(); ++iter) 
				push_back(*iter);
		} catch(...) {
			throw "Out of Memory!";
		}
	}
	double getDimension() {
		return dimension;
	}
	
	double EuclidDistanceTo(const Point &Other) {
		if(dimension != Other.dimension) {
			throw "Ungleiche Dimension";
		}
		double distance = 0;
		for(unsigned int i = 0; i < dimension; i++) {
			distance += (Other[i] - this->at(i)) * (Other[i] - this->at(i));
		}
		return sqrt(distance);
	}
	
	friend ostream& operator<<(ostream &TheOstream, Point &me) {
		TheOstream << "(";
		for(unsigned int i = 0; i < me.getDimension(); i++) {
			TheOstream << me.at(i); 
			(i < me.getDimension() - 1) ? TheOstream << ", " : TheOstream << ")" ;
		}
		return TheOstream;
	}
};