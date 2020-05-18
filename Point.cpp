#pragma once
#include <iostream>
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
public:
	Point(initializer_list<double> args) {
		for(auto iter = args.begin(); iter != args.end(); ++iter)
			push_back(*iter);
	}
	double EuclidDistanceTo(const Point &Other);
	
// Alle anderen Methoden Ihrer Wahl fehlen noch!
};