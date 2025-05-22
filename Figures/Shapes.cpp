#include "Shapes.h"
#include <iostream>;
#include <cmath>
#include <set>;
#include <fstream>;

const double PI = 4.0 * atan(1.0);

// Circle
Circle::Circle(double x, double y, double r)
    : center_x(x), center_y(y), radius(r) {
}

double Circle::calc_area() {
    return PI * radius * radius;
}

double Circle::calc_perimetr() {
    return 2 * PI * radius;
}

void Circle::name() {
    cout << "Circle"<<endl;
}


// Triangle

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    side_a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    side_b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    side_c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    
}
    


Triangle::Triangle(double a, double b, double c){
    try {
        if (a < 0 || b < 0 || c < 0)
            throw runtime_error("The sides should be positive!");
        else if ((a + b < c) || (a + c < b) || (c + b < a))
            throw runtime_error("There is no triangle with these sides!");


        side_a = a;
        side_b = b;
        side_c = c;
    }
    catch (const runtime_error& ex) {
        cerr << ex.what() << endl;
    }
}

double Triangle:: calc_area() {

    double p = calc_perimetr() / 2;
    return sqrt(p * (p - side_a) * (p - side_b) * (p - side_c));
    
}


double Triangle::calc_perimetr() {
    return side_a + side_b + side_c;  
}

void Triangle::name() {
    cout << "Triangle"<<endl;
}

// Rectangle 

Rectangle::Rectangle(double w, double h) {
    try {
        if (w < 0 or h < 0)
            throw runtime_error("The sides should be positive!");
        width = w;
        height = h;
    }
    catch (const runtime_error& ex) {
        cerr << ex.what()<<endl;
    }
}

Rectangle::Rectangle(double x1, double y1, double x2, double y2,
    double x3, double y3, double x4, double y4) : x1(x1), y1(y1), x2(x2), y2(y2), x3(y3), y3(y3), x4(x4), y4(y4) {


    set<double> xCoords = { x1,x2,x3,x4 };
    set<double> yCoords = { y1,y2,y3,y4 };

    width = *(prev(xCoords.end())) - *(xCoords.begin());
    height = *(prev(yCoords.end())) - *(yCoords.begin());
}
        


double Rectangle::calc_area() {
    return width * height;
}

double Rectangle::calc_perimetr() {
    return 2 * (width + height);
}

void Rectangle::name() {
    cout << "Rectangle"<<endl;
}

// Ellips 
Ellipse::Ellipse(double x, double y, double a, double b) {
    try {
        if (a <= 0 || b <= 0)
            throw runtime_error("Axes should be positive");
        center_x = x;
        center_y = y;
        semi_major = a;
        semi_minor = b;
    }
    catch(const runtime_error& ex){
        cerr << ex.what() << endl;
    }

}

double Ellipse::calc_area()  {
    return PI * semi_major * semi_minor;
}

double Ellipse::calc_perimetr() {
    double h = ((semi_major - semi_minor) * (semi_major - semi_minor))/((semi_major + semi_minor) * (semi_major + semi_minor));
    return PI * (semi_major + semi_minor) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
}

void Ellipse::name() {
    cout << "Ellips"<<endl;
}

// Polygon 

Polygon::Polygon(const vector<pair<double,double>>& vec) {
    try {
        if (vec.size() < 3)
            throw runtime_error("polygon requires at least 3 vertices");

        coords = vec;
    }
    catch (const runtime_error& ex) {
        cerr << ex.what()<<endl;
    }
    

    
}

Polygon::Polygon(const string& filename) {
    ifstream file(filename);
    try {
        if (!file.is_open())
            throw runtime_error("file opening error");

        double x, y;
        string firstStr;
        getline(file, firstStr);
        while (file >> x >> y) {
            coords.emplace_back(x, y);
        }
    }
    catch (const runtime_error& ex) {
        cerr << ex.what() << endl;
    }
}

double Polygon::calc_area() {
    double area = 0.0;
    for (size_t i = 0; i < coords.size(); ++i) {
        size_t j = (i + 1) % coords.size();
        area += coords[i].first * coords[j].second;
        area -= coords[j].first * coords[i].second;
    }
    return abs(area) / 2.0;
}

double Polygon::calc_perimetr() {
    double perimeter = 0.0;
    for (size_t i = 0; i < coords.size(); ++i) {
        size_t j = (i + 1) % coords.size();
        double dx = coords[j].first - coords[i].first;
        double dy = coords[j].second - coords[i].second;
        perimeter += sqrt(dx * dx + dy * dy);
    }
    return perimeter;
}

void Polygon::name() {
    cout << "Polygon" << endl;
}


