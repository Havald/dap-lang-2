#pragma once
#include "Point.cpp"

class PointArray : private vector<Point> {
public:
	using vector<Point>::size;
	using vector<Point>::operator[];
	using vector<Point>::at;

	PointArray(initializer_list<Point> args) {	
			for(auto iter = args.begin(); iter != args.end(); ++iter) 
			push_back(*iter);
	}
	void push_back(Point p) {
		if(this->size() > 0) {
			if(this->at(0).getDimension() != p.getDimension()) {
				throw "Cannot add point to Array: wrong dimension";
			} 
		}
		try {
			vector::push_back(p);
		} catch(...) {
			throw "Ran out of Memory while trying to add the point";
		}
	}
	
	friend ostream& operator<<(ostream &TheOstream, PointArray &me) {
		for(unsigned int i = 0; i < me.size(); i++) {
			TheOstream << me.at(i);
			(i < me.size() - 1) ? TheOstream << ", " : TheOstream << "";
			TheOstream << endl;
		}
		return TheOstream;
	}
};