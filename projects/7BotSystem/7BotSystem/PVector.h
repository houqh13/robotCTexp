#pragma once

// 3-Dimension Vector Class

class PVector {
public:
	/* Global Variables */
	double x, y, z;
	// constructor
	PVector();
	PVector(double _x, double _y, double _z);
	// function
	void add(PVector p);
	void normalize();
	double dot(PVector p);
	double dist(PVector p);
};


