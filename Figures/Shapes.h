#ifndef SHAPES_H;
#define SHAPES_H
using namespace std;
#include<vector>;
#include <utility>;
#include <string>;



class Shape {
public:
	virtual double calc_area() = 0;
	virtual double calc_perimetr() = 0;
	virtual void  name() = 0;
};

class Triangle : public Shape {
	double x1, y1, x2, y2, x3, y3; 
	double side_a, side_b, side_c; 
	bool by_sides;
public:

	Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
	Triangle(double a, double b, double c);
	double calc_area() override;
	double calc_perimetr() override;
	void name() override;
	
};

class Circle : public Shape {
	double center_x, center_y;
	double radius;
public:
	Circle(double x, double y, double r);
	double calc_area() override;
	double calc_perimetr() override;
	void name() override;
};

class Ellipse : public Shape {
	double center_x, center_y;
	double semi_major, semi_minor;
public:
	Ellipse(double x, double y, double a, double b);
	double calc_area() override;
	double calc_perimetr() override;
	void name()  override;
};

class Rectangle : public Shape {
	double x1, x2,x3,x4,y1,y2,y3,y4;
	double width, height;
	bool by_sides;
public:
	Rectangle(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);		
	Rectangle(double w, double h);
	double calc_area() override;
	double calc_perimetr() override;
	void name() override;
};

class Polygon : public Shape {
	
	vector<pair<double, double>> coords;
public:
	Polygon(const vector<pair<double, double>>& vec);
	Polygon(const string& filename);
	double calc_area()  override;
	double calc_perimetr() override;
	void name() override;
};

#endif 
