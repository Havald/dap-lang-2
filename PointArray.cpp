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
			if(this->at(0).getDimension() != p.getDimension()) { // Über Push_back dürfen nachträglich keine Punkte falscher Dimension hinzugefügt werden
				throw "Cannot add point to Array: wrong dimension";
			} 
		}
		try {
			vector::push_back(p);
		} catch(...) {
			throw "Memory allocation failed while trying to add the point";
		}
	}
	
	friend ostream& operator<<(ostream &TheOstream, PointArray &me) {
		for(size_t i = 0; i < me.size(); i++) {
			TheOstream << me.at(i);
			(i < me.size() - 1) ? TheOstream << ", " : TheOstream << "";
			TheOstream << endl;
		}
		return TheOstream;
	}
};